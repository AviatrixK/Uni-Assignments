"""
Q1: RSA Encryption/Decryption and Diffie-Hellman Key Exchange
Author: Your Name
Date: 2024
"""

import os
import random
import hashlib
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Random import get_random_bytes
import time

class RSADemo:
    """RSA Encryption and Decryption Demonstration"""
    
    def __init__(self, key_size=2048):
        self.key_size = key_size
        self.private_key = None
        self.public_key = None
        
    def generate_keys(self):
        """Generate RSA key pair"""
        print(f"Generating {self.key_size}-bit RSA key pair...")
        self.private_key = RSA.generate(self.key_size)
        self.public_key = self.private_key.publickey()
        
        # Save keys to files
        os.makedirs('keys', exist_ok=True)
        
        with open('keys/rsa_private.pem', 'wb') as f:
            f.write(self.private_key.export_key())
        
        with open('keys/rsa_public.pem', 'wb') as f:
            f.write(self.public_key.export_key())
            
        print("Keys generated and saved to 'keys/' directory")
        
    def encrypt(self, message):
        """Encrypt message using public key"""
        cipher_rsa = PKCS1_OAEP.new(self.public_key)
        ciphertext = cipher_rsa.encrypt(message)
        return ciphertext
    
    def decrypt(self, ciphertext):
        """Decrypt message using private key"""
        cipher_rsa = PKCS1_OAEP.new(self.private_key)
        plaintext = cipher_rsa.decrypt(ciphertext)
        return plaintext
    
    def demo(self):
        """Run RSA encryption/decryption demo"""
        print("\n" + "="*60)
        print("RSA ENCRYPTION/DECRYPTION DEMO")
        print("="*60)
        
        # Generate keys
        self.generate_keys()
        
        # Test message
        message = b"This is a secure message encrypted with RSA!"
        print(f"\nOriginal message: {message.decode()}")
        
        # Encrypt
        start_time = time.time()
        ciphertext = self.encrypt(message)
        encrypt_time = time.time() - start_time
        print(f"Encrypted (hex): {ciphertext.hex()[:80]}...")
        print(f"Encryption time: {encrypt_time:.6f} seconds")
        
        # Decrypt
        start_time = time.time()
        decrypted = self.decrypt(ciphertext)
        decrypt_time = time.time() - start_time
        print(f"Decrypted: {decrypted.decode()}")
        print(f"Decryption time: {decrypt_time:.6f} seconds")
        
        return encrypt_time, decrypt_time

class DiffieHellmanDemo:
    """Diffie-Hellman Key Exchange Demonstration"""
    
    def __init__(self, bits=1024):
        self.bits = bits
        self.p = self._generate_prime()
        self.g = self._find_generator()
        
    def _generate_prime(self):
        """Generate a large prime number"""
        # For demonstration, using a pre-selected safe prime
        # In production, use proper prime generation
        return 0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA237327FFFFFFFFFFFFFFFF
    
    def _find_generator(self):
        """Find a generator for the group"""
        # For demonstration, using a common generator
        return 2
    
    def generate_private_key(self):
        """Generate a private key"""
        return random.randint(2, self.p - 2)
    
    def generate_public_key(self, private_key):
        """Generate public key from private key"""
        return pow(self.g, private_key, self.p)
    
    def compute_shared_secret(self, private_key, other_public_key):
        """Compute shared secret"""
        return pow(other_public_key, private_key, self.p)
    
    def demo(self):
        """Run Diffie-Hellman key exchange demo"""
        print("\n" + "="*60)
        print("DIFFIE-HELLMAN KEY EXCHANGE DEMO")
        print("="*60)
        
        print(f"Public parameters:")
        print(f"Prime (p): {hex(self.p)[:50]}...")
        print(f"Generator (g): {self.g}")
        
        # Alice's keys
        print("\n--- Alice's Side ---")
        start_time = time.time()
        alice_private = self.generate_private_key()
        alice_public = self.generate_public_key(alice_private)
        alice_time = time.time() - start_time
        print(f"Alice's public key: {hex(alice_public)[:50]}...")
        
        # Bob's keys
        print("\n--- Bob's Side ---")
        start_time = time.time()
        bob_private = self.generate_private_key()
        bob_public = self.generate_public_key(bob_private)
        bob_time = time.time() - start_time
        print(f"Bob's public key: {hex(bob_public)[:50]}...")
        
        # Compute shared secrets
        print("\n--- Shared Secret Computation ---")
        alice_shared = self.compute_shared_secret(alice_private, bob_public)
        bob_shared = self.compute_shared_secret(bob_private, alice_public)
        
        # Convert to usable key
        alice_key = hashlib.sha256(str(alice_shared).encode()).hexdigest()
        bob_key = hashlib.sha256(str(bob_shared).encode()).hexdigest()
        
        print(f"Alice's shared secret (SHA-256): {alice_key[:32]}...")
        print(f"Bob's shared secret (SHA-256): {bob_key[:32]}...")
        print(f"Secrets match: {alice_key == bob_key}")
        print(f"\nTotal key exchange time: {alice_time + bob_time:.6f} seconds")
        
        return alice_time + bob_time

def compare_algorithms():
    """Compare RSA and Diffie-Hellman"""
    print("\n" + "="*60)
    print("COMPARISON: RSA vs DIFFIE-HELLMAN")
    print("="*60)
    
    comparison = """
    ┌─────────────────┬───────────────────────────┬──────────────────────────┐
    │ Aspect          │ RSA                       │ Diffie-Hellman           │
    ├─────────────────┼───────────────────────────┼──────────────────────────┤
    │ Purpose         │ Encryption & Signatures   │ Key Exchange Only        │
    │ Key Size        │ 2048-4096 bits           │ 2048-4096 bits          │
    │ Security Basis  │ Factoring problem        │ Discrete log problem     │
    │ Speed           │ Slower                    │ Faster                   │
    │ Use Cases       │ Digital certificates,     │ Perfect forward secrecy, │
    │                 │ Email encryption          │ TLS key exchange         │
    │ Authentication  │ Built-in                  │ Requires additional      │
    └─────────────────┴───────────────────────────┴──────────────────────────┘
    """
    print(comparison)

def main():
    """Main execution function"""
    # RSA Demo
    rsa_demo = RSADemo()
    rsa_encrypt_time, rsa_decrypt_time = rsa_demo.demo()
    
    # Diffie-Hellman Demo
    dh_demo = DiffieHellmanDemo()
    dh_time = dh_demo.demo()
    
    # Comparison
    compare_algorithms()
    
    # Performance Summary
    print("\n" + "="*60)
    print("PERFORMANCE SUMMARY")
    print("="*60)
    print(f"RSA Encryption Time: {rsa_encrypt_time:.6f} seconds")
    print(f"RSA Decryption Time: {rsa_decrypt_time:.6f} seconds")
    print(f"DH Key Exchange Time: {dh_time:.6f} seconds")

if __name__ == "__main__":
    main()