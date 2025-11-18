"""
Q1: Key Management and Distribution System
Simulates a Key Distribution Center (KDC) for symmetric key distribution
"""

import os
import json
import time
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.backends import default_backend
import base64

class KeyDistributionCenter:
    """Simulates a trusted KDC for key management"""
    
    def __init__(self):
        self.registered_users = {}
        self.session_keys = {}
        self.key_versions = {}  # For key rotation
        print(" Key Distribution Center Initialized")
    
    def register_user(self, user_id, master_key):
        """Register a user with their master key"""
        self.registered_users[user_id] = master_key
        self.key_versions[user_id] = 1
        print(f" User '{user_id}' registered with KDC")
    
    def generate_session_key(self, user_a, user_b):
        """Generate a session key for communication between two users"""
        if user_a not in self.registered_users or user_b not in self.registered_users:
            raise ValueError("One or both users not registered!")
        
        # Generate random session key
        session_key = os.urandom(32)  # 256-bit key
        session_id = f"{user_a}_{user_b}_{int(time.time())}"
        
        # Encrypt session key with each user's master key
        encrypted_for_a = self.encrypt_with_master_key(session_key, user_a)
        encrypted_for_b = self.encrypt_with_master_key(session_key, user_b)
        
        self.session_keys[session_id] = {
            'session_key': session_key,
            'created_at': time.time(),
            'users': [user_a, user_b]
        }
        
        print(f" Session key generated for {user_a} ↔ {user_b}")
        return {
            'session_id': session_id,
            'key_for_a': encrypted_for_a,
            'key_for_b': encrypted_for_b
        }
    
    def encrypt_with_master_key(self, data, user_id):
        """Encrypt data using user's master key (AES-256)"""
        master_key = self.registered_users[user_id]
        iv = os.urandom(16)
        cipher = Cipher(algorithms.AES(master_key), modes.CBC(iv), backend=default_backend())
        encryptor = cipher.encryptor()
        
        # Pad data to 16-byte boundary
        padded_data = data + b'\x00' * (16 - len(data) % 16)
        encrypted = encryptor.update(padded_data) + encryptor.finalize()
        
        return base64.b64encode(iv + encrypted).decode()
    
    def decrypt_with_master_key(self, encrypted_data, user_id):
        """Decrypt data using user's master key"""
        master_key = self.registered_users[user_id]
        decoded = base64.b64decode(encrypted_data)
        iv = decoded[:16]
        ciphertext = decoded[16:]
        
        cipher = Cipher(algorithms.AES(master_key), modes.CBC(iv), backend=default_backend())
        decryptor = cipher.decryptor()
        decrypted = decryptor.update(ciphertext) + decryptor.finalize()
        
        return decrypted.rstrip(b'\x00')
    
    def rotate_key(self, user_id):
        """Simulate key rotation for a user"""
        if user_id not in self.registered_users:
            raise ValueError("User not registered!")
        
        old_version = self.key_versions[user_id]
        new_master_key = os.urandom(32)
        
        # Archive old key (in real system, you'd have proper key archival)
        old_key = self.registered_users[user_id]
        
        self.registered_users[user_id] = new_master_key
        self.key_versions[user_id] += 1
        
        print(f" Key rotated for '{user_id}': v{old_version} → v{self.key_versions[user_id]}")
        return new_master_key

class AsymmetricKeyDistribution:
    """Demonstrates asymmetric key distribution (PKI model)"""
    
    def __init__(self):
        self.public_keys = {}
        self.private_keys = {}
    
    def generate_key_pair(self, user_id):
        """Generate RSA key pair for a user"""
        private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=2048,
            backend=default_backend()
        )
        public_key = private_key.public_key()
        
        self.private_keys[user_id] = private_key
        self.public_keys[user_id] = public_key
        
        print(f" RSA key pair generated for '{user_id}'")
        return public_key
    
    def encrypt_message(self, message, recipient_id):
        """Encrypt message using recipient's public key"""
        if recipient_id not in self.public_keys:
            raise ValueError("Recipient's public key not available!")
        
        public_key = self.public_keys[recipient_id]
        encrypted = public_key.encrypt(
            message.encode(),
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None
            )
        )
        return base64.b64encode(encrypted).decode()
    
    def decrypt_message(self, encrypted_message, recipient_id):
        """Decrypt message using recipient's private key"""
        private_key = self.private_keys[recipient_id]
        encrypted = base64.b64decode(encrypted_message)
        
        decrypted = private_key.decrypt(
            encrypted,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None
            )
        )
        return decrypted.decode()


def demonstrate_key_distribution():
    """Main demonstration of key distribution systems"""
    
    print("=" * 70)
    print("SYMMETRIC KEY DISTRIBUTION WITH KDC")
    print("=" * 70)
    
    # Initialize KDC
    kdc = KeyDistributionCenter()
    
    # Register users with master keys
    alice_master = os.urandom(32)
    bob_master = os.urandom(32)
    
    kdc.register_user("Alice", alice_master)
    kdc.register_user("Bob", bob_master)
    
    # Generate session key
    session_info = kdc.generate_session_key("Alice", "Bob")
    
    # Alice decrypts her copy of the session key
    alice_session_key = kdc.decrypt_with_master_key(session_info['key_for_a'], "Alice")
    bob_session_key = kdc.decrypt_with_master_key(session_info['key_for_b'], "Bob")
    
    print(f" Alice's session key: {alice_session_key.hex()[:32]}...")
    print(f" Bob's session key:   {bob_session_key.hex()[:32]}...")
    print(f" Keys match: {alice_session_key == bob_session_key}")
    
    # Demonstrate key rotation
    print("\n" + "=" * 70)
    print("KEY ROTATION DEMONSTRATION")
    print("=" * 70)
    kdc.rotate_key("Alice")
    kdc.rotate_key("Alice")  # Rotate twice
    
    print("\n" + "=" * 70)
    print("ASYMMETRIC KEY DISTRIBUTION (PKI)")
    print("=" * 70)
    
    # Asymmetric key distribution
    pki = AsymmetricKeyDistribution()
    
    # Generate key pairs
    pki.generate_key_pair("Alice")
    pki.generate_key_pair("Bob")
    
    # Alice sends encrypted message to Bob
    message = "Hello Bob, this is a secret message!"
    encrypted = pki.encrypt_message(message, "Bob")
    print(f"\n Encrypted message: {encrypted[:50]}...")
    
    decrypted = pki.decrypt_message(encrypted, "Bob")
    print(f" Decrypted message: {decrypted}")
    
    print("\n" + "=" * 70)
    print("KEY MANAGEMENT CHALLENGES")
    print("=" * 70)
    print("""
    1. KEY ESCROW:
       - Allows authorized third parties to access encrypted data
       - Controversial due to privacy concerns
       - Used in some enterprise and government settings
    
    2. KEY ROTATION:
       - Regular key updates reduce exposure from compromised keys
       - Challenges: Coordinating updates across distributed systems
       - Best practice: Rotate keys every 90 days or after incidents
    
    3. LARGE-SCALE CHALLENGES (Cloud/IoT):
       - IoT: Limited computational resources for complex crypto
       - Cloud: Multi-tenancy requires strict key isolation
       - Scale: Managing millions of keys requires automation
       - Lifecycle: Key generation, distribution, storage, rotation, revocation
    """)


if __name__ == "__main__":
    demonstrate_key_distribution()

    print("\n Saving configuration...")
    config = {
        "kdc_type": "symmetric",
        "key_algorithm": "AES-256",
        "asymmetric_algorithm": "RSA-2048",
        "key_rotation_period": "90 days"
    }

    with open("key_config.json", "w") as f:
        json.dump(config, f, indent=2)

    print(" Configuration saved to key_config.json")



