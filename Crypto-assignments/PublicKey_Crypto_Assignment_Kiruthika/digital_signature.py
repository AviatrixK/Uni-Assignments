"""
Q2: Digital Signatures using RSA/DSA
Author: Your Name
Date: 2024
"""

import os
from Crypto.PublicKey import RSA, DSA
from Crypto.Signature import pkcs1_15, DSS
from Crypto.Hash import SHA256
from Crypto.Random import get_random_bytes
import time

class DigitalSignatureDemo:
    """Digital Signature Generation and Verification"""
    
    def __init__(self, algorithm='RSA'):
        self.algorithm = algorithm
        self.private_key = None
        self.public_key = None
        
    def generate_keys(self, key_size=2048):
        """Generate key pair for signing"""
        print(f"\nGenerating {key_size}-bit {self.algorithm} key pair...")
        
        if self.algorithm == 'RSA':
            self.private_key = RSA.generate(key_size)
            self.public_key = self.private_key.publickey()
        elif self.algorithm == 'DSA':
            self.private_key = DSA.generate(key_size)
            self.public_key = self.private_key.publickey()
        
        # Save keys
        os.makedirs('keys', exist_ok=True)
        
        with open(f'keys/{self.algorithm.lower()}_signing_private.pem', 'wb') as f:
            f.write(self.private_key.export_key())
        
        with open(f'keys/{self.algorithm.lower()}_signing_public.pem', 'wb') as f:
            f.write(self.public_key.export_key())
            
        print(f"Keys saved to 'keys/' directory")
    
    def sign_message(self, message):
        """Sign a message with private key"""
        # Hash the message
        h = SHA256.new(message)
        
        # Sign with appropriate algorithm
        if self.algorithm == 'RSA':
            signature = pkcs1_15.new(self.private_key).sign(h)
        elif self.algorithm == 'DSA':
            signature = DSS.new(self.private_key, 'fips-186-3').sign(h)
            
        return signature, h
    
    def verify_signature(self, message, signature, public_key=None):
        """Verify signature with public key"""
        if public_key is None:
            public_key = self.public_key
            
        # Hash the message
        h = SHA256.new(message)
        
        try:
            if self.algorithm == 'RSA':
                pkcs1_15.new(public_key).verify(h, signature)
            elif self.algorithm == 'DSA':
                DSS.new(public_key, 'fips-186-3').verify(h, signature)
            return True
        except (ValueError, TypeError):
            return False
    
    def demo(self):
        """Run digital signature demo"""
        print("\n" + "="*60)
        print(f"{self.algorithm} DIGITAL SIGNATURE DEMO")
        print("="*60)
        
        # Generate keys
        self.generate_keys()
        
        # Test messages
        messages = [
            b"This is an authentic message from Alice",
            b"Contract Agreement: Terms and Conditions Apply",
            b"Transaction ID: 12345, Amount: $1000.00"
        ]
        
        for i, message in enumerate(messages, 1):
            print(f"\n--- Message {i} ---")
            print(f"Original: {message.decode()}")
            
            # Sign
            start_time = time.time()
            signature, msg_hash = self.sign_message(message)
            sign_time = time.time() - start_time
            
            print(f"Message hash: {msg_hash.hexdigest()[:32]}...")
            print(f"Signature: {signature.hex()[:64]}...")
            print(f"Signing time: {sign_time:.6f} seconds")
            
            # Verify
            start_time = time.time()
            is_valid = self.verify_signature(message, signature)
            verify_time = time.time() - start_time
            
            print(f"Verification result: {'✓ VALID' if is_valid else '✗ INVALID'}")
            print(f"Verification time: {verify_time:.6f} seconds")
            
            # Test tampering
            tampered_message = message + b" TAMPERED"
            is_valid_tampered = self.verify_signature(tampered_message, signature)
            print(f"Tampered message verification: {'✓ VALID' if is_valid_tampered else '✗ INVALID'}")

class SignatureProperties:
    """Demonstrate properties of digital signatures"""
    
    @staticmethod
    def demonstrate_properties():
        print("\n" + "="*60)
        print("DIGITAL SIGNATURE PROPERTIES")
        print("="*60)
        
        print("""
1. AUTHENTICITY
   - Verifies the identity of the message sender
   - Only the holder of the private key can create valid signature
   - Public key verification proves sender's identity

2. INTEGRITY
   - Any modification to the message invalidates the signature
   - Ensures message hasn't been altered in transit
   - Based on cryptographic hash functions

3. NON-REPUDIATION
   - Sender cannot deny having signed the message
   - Signature is mathematically bound to both message and signer
   - Provides legal evidence of agreement/transaction

4. USE CASES
   - Email authentication (PGP/S-MIME)
   - Software distribution (code signing)
   - Financial transactions
   - Legal documents and contracts
   - Blockchain transactions
        """)

def compare_signature_algorithms():
    """Compare RSA and DSA signatures"""
    print("\n" + "="*60)
    print("RSA vs DSA SIGNATURE COMPARISON")
    print("="*60)
    
    # Test both algorithms
    test_message = b"Performance comparison test message"
    
    # RSA Signature
    print("\n--- RSA Signature ---")
    rsa_demo = DigitalSignatureDemo('RSA')
    rsa_demo.generate_keys(2048)
    
    start = time.time()
    rsa_sig, _ = rsa_demo.sign_message(test_message)
    rsa_sign_time = time.time() - start
    
    start = time.time()
    rsa_demo.verify_signature(test_message, rsa_sig)
    rsa_verify_time = time.time() - start
    
    # DSA Signature
    print("\n--- DSA Signature ---")
    dsa_demo = DigitalSignatureDemo('DSA')
    dsa_demo.generate_keys(2048)
    
    start = time.time()
    dsa_sig, _ = dsa_demo.sign_message(test_message)
    dsa_sign_time = time.time() - start
    
    start = time.time()
    dsa_demo.verify_signature(test_message, dsa_sig)
    dsa_verify_time = time.time() - start
    
    # Results
    print("\n" + "="*60)
    print("PERFORMANCE RESULTS")
    print("="*60)
    print(f"RSA Signing Time: {rsa_sign_time:.6f} seconds")
    print(f"RSA Verification Time: {rsa_verify_time:.6f} seconds")
    print(f"RSA Signature Size: {len(rsa_sig)} bytes")
    print(f"\nDSA Signing Time: {dsa_sign_time:.6f} seconds")
    print(f"DSA Verification Time: {dsa_verify_time:.6f} seconds")
    print(f"DSA Signature Size: {len(dsa_sig)} bytes")

def main():
    """Main execution function"""
    # RSA Digital Signature Demo
    rsa_demo = DigitalSignatureDemo('RSA')
    rsa_demo.demo()
    
    # DSA Digital Signature Demo
    dsa_demo = DigitalSignatureDemo('DSA')
    dsa_demo.demo()
    
    # Properties demonstration
    SignatureProperties.demonstrate_properties()
    
    # Algorithm comparison
    compare_signature_algorithms()

if __name__ == "__main__":
    main()