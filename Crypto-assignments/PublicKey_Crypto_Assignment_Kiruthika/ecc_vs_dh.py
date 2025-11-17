"""
Q4: Key Exchange Protocol Comparison - DH vs ECDH
Author: Your Name
Date: 2024
"""

import time
import random
import hashlib
import os
from tinyec import registry
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import dh, ec
from cryptography.hazmat.backends import default_backend

# Try to import matplotlib, but don't fail if it's not available
try:
    import matplotlib.pyplot as plt
    import numpy as np
    MATPLOTLIB_AVAILABLE = True
except ImportError:
    MATPLOTLIB_AVAILABLE = False
    print("Note: matplotlib not found. Graphs will not be generated.")
    print("Install with: pip install matplotlib numpy\n")

class ClassicDiffieHellman:
    """Classic Diffie-Hellman Implementation"""
    
    def __init__(self, key_size=2048):
        self.key_size = key_size
        self.parameters = None
        self.generate_parameters()
        
    def generate_parameters(self):
        """Generate DH parameters"""
        print(f"Generating {self.key_size}-bit DH parameters...")
        self.parameters = dh.generate_parameters(
            generator=2,
            key_size=self.key_size,
            backend=default_backend()
        )
        
    def generate_private_key(self):
        """Generate private key"""
        # Fixed: removed backend parameter
        return self.parameters.generate_private_key()
    
    def perform_key_exchange(self):
        """Perform complete key exchange"""
        # Alice generates private key
        alice_private = self.generate_private_key()
        alice_public = alice_private.public_key()
        
        # Bob generates private key
        bob_private = self.generate_private_key()
        bob_public = bob_private.public_key()
        
        # Exchange and compute shared secrets
        alice_shared = alice_private.exchange(bob_public)
        bob_shared = bob_private.exchange(alice_public)
        
        # Derive keys from shared secrets
        alice_key = hashlib.sha256(alice_shared).hexdigest()
        bob_key = hashlib.sha256(bob_shared).hexdigest()
        
        return alice_key, bob_key, len(alice_shared) * 8

class EllipticCurveDiffieHellman:
    """Elliptic Curve Diffie-Hellman Implementation"""
    
    def __init__(self, curve_name='secp256r1'):
        self.curve_name = curve_name
        
        # Map curve names for different libraries
        if curve_name == 'secp256r1':
            self.crypto_curve = ec.SECP256R1()
            self.tinyec_curve = registry.get_curve('secp256r1')
        elif curve_name == 'secp384r1':
            self.crypto_curve = ec.SECP384R1()
            self.tinyec_curve = registry.get_curve('secp384r1')
        else:
            self.crypto_curve = ec.SECP521R1()
            self.tinyec_curve = registry.get_curve('secp521r1')
            
    def generate_private_key(self):
        """Generate private key"""
        # Check cryptography version and use appropriate method
        try:
            # Try newer version first (without backend)
            return ec.generate_private_key(self.crypto_curve)
        except TypeError:
            # Fall back to older version (with backend)
            return ec.generate_private_key(self.crypto_curve, backend=default_backend())
    
    def perform_key_exchange(self):
        """Perform complete ECDH key exchange"""
        # Alice generates private key
        alice_private = self.generate_private_key()
        alice_public = alice_private.public_key()
        
        # Bob generates private key
        bob_private = self.generate_private_key()
        bob_public = bob_private.public_key()
        
        # Exchange and compute shared secrets
        alice_shared = alice_private.exchange(ec.ECDH(), bob_public)
        bob_shared = bob_private.exchange(ec.ECDH(), alice_public)
        
        # Derive keys from shared secrets
        alice_key = hashlib.sha256(alice_shared).hexdigest()
        bob_key = hashlib.sha256(bob_shared).hexdigest()
        
        return alice_key, bob_key, len(alice_shared) * 8
    
    def perform_tinyec_exchange(self):
        """Perform ECDH using tinyec library"""
        # Alice's keys
        alice_private = random.randint(1, self.tinyec_curve.field.n - 1)
        alice_public = alice_private * self.tinyec_curve.g
        
        # Bob's keys
        bob_private = random.randint(1, self.tinyec_curve.field.n - 1)
        bob_public = bob_private * self.tinyec_curve.g
        
        # Compute shared secrets
        alice_shared = alice_private * bob_public
        bob_shared = bob_private * alice_public
        
        # Derive keys
        alice_key = hashlib.sha256(str(alice_shared.x).encode()).hexdigest()
        bob_key = hashlib.sha256(str(bob_shared.x).encode()).hexdigest()
        
        return alice_key, bob_key

class SimpleDiffieHellman:
    """Simple DH implementation for demonstration (faster)"""
    
    def __init__(self):
        # Using smaller pre-generated safe prime for demonstration
        self.p = 0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A63637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA18217C32905E462E36CE3BE39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9DE2BCBF6955817183995497CEA956AE515D2261898FA051015728E5A8AACAA68FFFFFFFFFFFFFFFF
        self.g = 2
        
    def perform_key_exchange(self):
        """Perform simple DH key exchange"""
        # Alice's keys
        alice_private = random.randint(2, self.p - 2)
        alice_public = pow(self.g, alice_private, self.p)
        
        # Bob's keys
        bob_private = random.randint(2, self.p - 2)
        bob_public = pow(self.g, bob_private, self.p)
        
        # Compute shared secrets
        alice_shared = pow(bob_public, alice_private, self.p)
        bob_shared = pow(alice_public, bob_private, self.p)
        
        # Convert to hex keys
        alice_key = hashlib.sha256(str(alice_shared).encode()).hexdigest()
        bob_key = hashlib.sha256(str(bob_shared).encode()).hexdigest()
        
        return alice_key, bob_key

class ProtocolComparison:
    """Compare DH and ECDH protocols"""
    
    def __init__(self):
        self.results = {
            'dh': {'times': [], 'key_sizes': []},
            'ecdh': {'times': [], 'curves': []}
        }
        
    def benchmark_classic_dh_simple(self, iterations=10):
        """Benchmark with simple DH implementation (faster)"""
        print("\n" + "="*60)
        print("BENCHMARKING CLASSIC DIFFIE-HELLMAN (Simplified)")
        print("="*60)
        
        print("\nUsing pre-generated 2048-bit safe prime for faster execution")
        
        simple_dh = SimpleDiffieHellman()
        
        times = []
        for i in range(iterations):
            start = time.time()
            alice_key, bob_key = simple_dh.perform_key_exchange()
            end = time.time()
            times.append(end - start)
            
            if i == 0:  # Verify only once
                assert alice_key == bob_key, "Key mismatch!"
                
        avg_time = sum(times) / len(times)
        self.results['dh']['times'].append(avg_time)
        self.results['dh']['key_sizes'].append(2048)
        
        print(f"  Average time: {avg_time:.4f} seconds")
        print(f"  Keys match: ✓")
        
    def benchmark_classic_dh(self, iterations=10):
        """Benchmark classic Diffie-Hellman"""
        print("\n" + "="*60)
        print("BENCHMARKING CLASSIC DIFFIE-HELLMAN")
        print("="*60)
        
        # Use only one key size for faster execution
        key_sizes = [2048]  # Reduced for much faster execution
        
        for key_size in key_sizes:
            print(f"\nTesting {key_size}-bit DH...")
            
            try:
                dh_instance = ClassicDiffieHellman(key_size)
                
                times = []
                for i in range(min(iterations, 2)):  # Limit to 2 iterations for DH
                    start = time.time()
                    alice_key, bob_key, shared_size = dh_instance.perform_key_exchange()
                    end = time.time()
                    times.append(end - start)
                    
                    if i == 0:  # Verify only once
                        assert alice_key == bob_key, "Key mismatch!"
                        
                avg_time = sum(times) / len(times)
                self.results['dh']['times'].append(avg_time)
                self.results['dh']['key_sizes'].append(key_size)
                
                print(f"  Average time: {avg_time:.4f} seconds")
                print(f"  Shared secret size: {shared_size} bits")
                print(f"  Keys match: ✓")
                
            except Exception as e:
                print(f"  Error with {key_size}-bit DH: {e}")
                print("  Using simplified DH instead...")
                self.benchmark_classic_dh_simple(iterations)
                break
            
    def benchmark_ecdh(self, iterations=10):
        """Benchmark Elliptic Curve Diffie-Hellman"""
        print("\n" + "="*60)
        print("BENCHMARKING ELLIPTIC CURVE DIFFIE-HELLMAN")
        print("="*60)
        
        curves = [
            ('secp256r1', 256),
            ('secp384r1', 384),
            ('secp521r1', 521)
        ]
        
        for curve_name, curve_bits in curves:
            print(f"\nTesting {curve_name} ({curve_bits} bits)...")
            ecdh_instance = EllipticCurveDiffieHellman(curve_name)
            
            times = []
            for i in range(iterations):
                start = time.time()
                alice_key, bob_key, shared_size = ecdh_instance.perform_key_exchange()
                end = time.time()
                times.append(end - start)
                
                if i == 0:  # Verify only once
                    assert alice_key == bob_key, "Key mismatch!"
                    
            avg_time = sum(times) / len(times)
            self.results['ecdh']['times'].append(avg_time)
            self.results['ecdh']['curves'].append(curve_name)
            
            print(f"  Average time: {avg_time:.4f} seconds")
            print(f"  Shared secret size: {shared_size} bits")
            print(f"  Keys match: ✓")
            
    def compare_security_levels(self):
        """Compare security levels of DH and ECDH"""
        print("\n" + "="*60)
        print("SECURITY LEVEL COMPARISON")
        print("="*60)
        
        comparison = """
        ┌─────────────────┬────────────────┬──────────────────────┐
        │ Security Level  │ DH Key Size    │ ECC Key Size         │
        ├─────────────────┼────────────────┼──────────────────────┤
        │ 80 bits         │ 1024 bits      │ 160-223 bits         │
        │ 112 bits        │ 2048 bits      │ 224-255 bits         │
        │ 128 bits        │ 3072 bits      │ 256-383 bits         │
        │ 192 bits        │ 7680 bits      │ 384-511 bits         │
        │ 256 bits        │ 15360 bits     │ 512+ bits            │
        └─────────────────┴────────────────┴──────────────────────┘
        
        Key Observations:
        • ECC provides equivalent security with much smaller key sizes
        • 256-bit ECC ≈ 3072-bit DH in terms of security
        • Smaller keys = faster computation, less bandwidth, less storage
        """
        print(comparison)
        
    def display_results_table(self):
        """Display results in a table format instead of plot"""
        print("\n" + "="*60)
        print("PERFORMANCE RESULTS TABLE")
        print("="*60)
        
        if self.results['dh']['times']:
            # DH Results
            print("\nClassic Diffie-Hellman Performance:")
            print("┌──────────────┬──────────────────┐")
            print("│ Key Size     │ Avg Time (sec)   │")
            print("├──────────────┼──────────────────┤")
            for size, time_val in zip(self.results['dh']['key_sizes'], self.results['dh']['times']):
                print(f"│ {size:4d} bits   │ {time_val:8.4f}         │")
            print("└──────────────┴──────────────────┘")
        
        if self.results['ecdh']['times']:
            # ECDH Results
            print("\nElliptic Curve Diffie-Hellman Performance:")
            print("┌──────────────┬──────────────────┐")


if __name__ == "__main__":
    pc = ProtocolComparison()
    pc.benchmark_classic_dh()
    pc.benchmark_ecdh()
    pc.compare_security_levels()
    pc.display_results_table()

            