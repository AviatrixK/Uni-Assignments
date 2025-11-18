"""
Q2: Secure Email Using PGP/GPG
Demonstrates PGP-style encryption, decryption, and digital signatures
"""

import base64
import os
import datetime

from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes


class PGPSimulator:
    """Simulates PGP encryption, signing, decryption, and verification"""

    def __init__(self):
        self.private_keys = {}
        self.public_keys = {}
        print(" PGP Simulator Initialized")

    def generate_keypair(self, name, email):
        """Generate RSA keypair for a user"""
        private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=2048,
            backend=default_backend()
        )
        public_key = private_key.public_key()

        user_id = f"{name} <{email}>"
        self.private_keys[user_id] = private_key
        self.public_keys[user_id] = public_key

        print(f" Key pair generated for {user_id}")

        private_pem = private_key.private_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PrivateFormat.PKCS8,
            encryption_algorithm=serialization.NoEncryption()
        )

        public_pem = public_key.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        )

        return {
            'user_id': user_id,
            'private_key': private_pem.decode(),
            'public_key': public_pem.decode()
        }

    # ------------------------------------------------------------------
    # HYBRID AES + RSA ENCRYPTION
    # ------------------------------------------------------------------

    def encrypt_email(self, message, recipient_id):
        """Encrypt large message using hybrid RSA + AES"""
        if recipient_id not in self.public_keys:
            raise ValueError(f"No public key for {recipient_id}")

        public_key = self.public_keys[recipient_id]

        # 1. Generate AES key + IV
        aes_key = os.urandom(32)  # 256-bit AES
        iv = os.urandom(16)

        # 2. AES encrypt message
        cipher = Cipher(algorithms.AES(aes_key), modes.CFB(iv))
        encryptor = cipher.encryptor()
        ciphertext = encryptor.update(message.encode()) + encryptor.finalize()

        # 3. RSA encrypt AES key
        encrypted_key = public_key.encrypt(
            aes_key,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None
            )
        )

        pgp_message = f"""-----BEGIN PGP MESSAGE-----
Version: PGPSimulator 1.0

{base64.b64encode(encrypted_key).decode()}
{base64.b64encode(iv).decode()}
{base64.b64encode(ciphertext).decode()}
-----END PGP MESSAGE-----"""

        print(f" Message encrypted for {recipient_id}")
        return pgp_message

    # ------------------------------------------------------------------
    # HYBRID DECRYPTION
    # ------------------------------------------------------------------

    def decrypt_email(self, encrypted_message, recipient_id):
        """Decrypt hybrid AES+RSA encrypted message"""
        if recipient_id not in self.private_keys:
            raise ValueError(f"No private key for {recipient_id}")

        private_key = self.private_keys[recipient_id]

        lines = encrypted_message.split("\n")
        data = [l for l in lines if not l.startswith("-----") and not l.startswith("Version") and l.strip()]

        encrypted_key = base64.b64decode(data[0])
        iv = base64.b64decode(data[1])
        ciphertext = base64.b64decode(data[2])

        # RSA decrypt AES key
        aes_key = private_key.decrypt(
            encrypted_key,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None
            )
        )

        # AES decrypt message
        cipher = Cipher(algorithms.AES(aes_key), modes.CFB(iv))
        decryptor = cipher.decryptor()
        plaintext = decryptor.update(ciphertext) + decryptor.finalize()

        print(f" Message decrypted by {recipient_id}")
        return plaintext.decode()

    # ------------------------------------------------------------------
    # SIGNING
    # ------------------------------------------------------------------

    def sign_message(self, message, signer_id):
        """Create digital signature"""
        if signer_id not in self.private_keys:
            raise ValueError(f"No private key for {signer_id}")

        private_key = self.private_keys[signer_id]

        signature = private_key.sign(
            message.encode(),
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )

        signature_b64 = base64.b64encode(signature).decode()

        signed_message = f"""-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA256

{message}
-----BEGIN PGP SIGNATURE-----

{signature_b64}
-----END PGP SIGNATURE-----"""

        print(f"  Message signed by {signer_id}")
        return signed_message

    # ------------------------------------------------------------------
    # VERIFICATION
    # ------------------------------------------------------------------

    def verify_signature(self, signed_message, signer_id):
        """Verify digital signature"""
        if signer_id not in self.public_keys:
            raise ValueError(f"No public key for {signer_id}")

        public_key = self.public_keys[signer_id]

        lines = signed_message.split("\n")
        message_lines = []
        signature_lines = []
        in_message = False
        in_signature = False

        for line in lines:
            if line.startswith("-----BEGIN PGP SIGNED MESSAGE"):
                in_message = True
                continue
            elif line.startswith("-----BEGIN PGP SIGNATURE"):
                in_message = False
                in_signature = True
                continue
            elif line.startswith("-----END"):
                in_signature = False
                continue
            elif line.startswith("Hash:"):
                continue

            if in_message and line:
                message_lines.append(line)
            elif in_signature:
                signature_lines.append(line)

        message = "\n".join(message_lines)
        signature = base64.b64decode("".join(signature_lines))

        try:
            public_key.verify(
                signature,
                message.encode(),
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )
            print(f" Signature verified for {signer_id}")
            return True, message

        except Exception as e:
            print(f" Signature verification failed: {e}")
            return False, None

    # ------------------------------------------------------------------
    # COMBINED OPERATION
    # ------------------------------------------------------------------

    def encrypt_and_sign(self, message, sender_id, recipient_id):
        """Sign first, then encrypt (PGP workflow)"""
        signed = self.sign_message(message, sender_id)
        encrypted = self.encrypt_email(signed, recipient_id)
        print(f" Message encrypted and signed: {sender_id} → {recipient_id}")
        return encrypted


# ----------------------------------------------------------------------
# DEMO FUNCTION
# ----------------------------------------------------------------------

def demonstrate_pgp():
    print("=" * 70)
    print("PGP SECURE EMAIL DEMONSTRATION")
    print("=" * 70)

    pgp = PGPSimulator()

    # Generate key pairs
    alice_keys = pgp.generate_keypair("Alice Smith", "alice@example.com")
    bob_keys = pgp.generate_keypair("Bob Jones", "bob@example.com")

    alice_id = alice_keys['user_id']
    bob_id = bob_keys['user_id']

    print("\n" + "=" * 70)
    print("ENCRYPTION DEMO")
    print("=" * 70)

    email_message = """Subject: Confidential Project Update
From: Alice <alice@example.com>
To: Bob <bob@example.com>

Dear Bob,

The project deadline has been moved to next Friday.
Please ensure all deliverables are updated before the new deadline.

Best regards,
Alice
"""

    encrypted = pgp.encrypt_and_sign(email_message, alice_id, bob_id)
    print("\nEncrypted message:\n", encrypted)

    decrypted = pgp.decrypt_email(encrypted, bob_id)
    print("\nDecrypted (signed) message:\n", decrypted)

    verified, original = pgp.verify_signature(decrypted, alice_id)
    print("\nSignature verified:", verified)
    if verified:
        print("\nOriginal message:\n", original)

    print("\nDemo complete.")


if __name__ == "__main__":
    demonstrate_pgp()
