from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256
import os
import json
from datetime import datetime

class RSADigitalSignature:
    """Complete RSA Digital Signature Implementation"""
    
    def __init__(self):
        self.private_key = None
        self.public_key = None
        self.keys_folder = "keys"
        self.signatures_folder = "signatures"
        
        # Create folders if they don't exist
        os.makedirs(self.keys_folder, exist_ok=True)
        os.makedirs(self.signatures_folder, exist_ok=True)
    
    # ============== KEY GENERATION ==============
    
    def generate_keys(self, key_size=2048):
        """Generate RSA key pair"""
        print(f"\n Generating {key_size}-bit RSA keys...")
        key = RSA.generate(key_size)
        self.private_key = key
        self.public_key = key.publickey()
        print("Keys generated successfully!")
        return self.private_key, self.public_key
    
    # ============== KEY STORAGE ==============
    
    def save_keys(self, private_filename="private_key.pem", public_filename="public_key.pem"):
        """Save keys to files"""
        if not self.private_key or not self.public_key:
            print(" No keys to save. Generate keys first!")
            return False
        
        try:
            # Save private key
            private_path = os.path.join(self.keys_folder, private_filename)
            with open(private_path, 'wb') as f:
                f.write(self.private_key.export_key())
            
            # Save public key
            public_path = os.path.join(self.keys_folder, public_filename)
            with open(public_path, 'wb') as f:
                f.write(self.public_key.export_key())
            
            print(f"\n✓ Keys saved:")
            print(f"   Private: {private_path}")
            print(f"   Public: {public_path}")
            return True
            
        except Exception as e:
            print(f" Error saving keys: {e}")
            return False
    
    def load_keys(self, private_filename="private_key.pem", public_filename="public_key.pem"):
        """Load keys from files"""
        try:
            # Load private key
            private_path = os.path.join(self.keys_folder, private_filename)
            with open(private_path, 'rb') as f:
                self.private_key = RSA.import_key(f.read())
            
            # Load public key
            public_path = os.path.join(self.keys_folder, public_filename)
            with open(public_path, 'rb') as f:
                self.public_key = RSA.import_key(f.read())
            
            print(f"\n Keys loaded successfully!")
            print(f"  Key size: {self.private_key.size_in_bits()} bits")
            return True
            
        except FileNotFoundError:
            print(f" Key files not found in '{self.keys_folder}/' folder")
            return False
        except Exception as e:
            print(f" Error loading keys: {e}")
            return False
    
    # ============== SIGNING ==============
    
    def sign_message(self, message):
        """Sign a message using private key"""
        if not self.private_key:
            print(" Private key not loaded. Generate or load keys first!")
            return None
        
        try:
            # Convert to bytes if string
            if isinstance(message, str):
                message_bytes = message.encode('utf-8')
            else:
                message_bytes = message
            
            # Hash the message
            hash_obj = SHA256.new(message_bytes)
            
            # Sign the hash
            signature = pkcs1_15.new(self.private_key).sign(hash_obj)
            
            print("\n Message signed successfully!")
            print(f"  Message Hash (SHA-256): {hash_obj.hexdigest()}")
            print(f"  Signature Length: {len(signature)} bytes")
            
            return signature
            
        except Exception as e:
            print(f" Signing failed: {e}")
            return None
    
    # ============== VERIFICATION ==============
    
    def verify_signature(self, message, signature):
        """Verify a signature using public key"""
        if not self.public_key:
            print(" Public key not loaded. Generate or load keys first!")
            return False
        
        try:
            # Convert to bytes if string
            if isinstance(message, str):
                message_bytes = message.encode('utf-8')
            else:
                message_bytes = message
            
            # Hash the message
            hash_obj = SHA256.new(message_bytes)
            
            # Verify signature
            pkcs1_15.new(self.public_key).verify(hash_obj, signature)
            
            print("\n SIGNATURE VALID - Message is authentic!")
            return True
            
        except (ValueError, TypeError):
            print("\n SIGNATURE INVALID - Message may be tampered!")
            return False
        except Exception as e:
            print(f" Verification failed: {e}")
            return False
    
    # ============== FILE OPERATIONS ==============
    
    def save_signature_to_file(self, message, signature, filename="signature.json"):
        """Save message and signature to JSON file"""
        try:
            filepath = os.path.join(self.signatures_folder, filename)
            
            data = {
                'message': message,
                'signature': signature.hex(),
                'timestamp': datetime.now().isoformat(),
                'hash_algorithm': 'SHA-256',
                'key_size': self.private_key.size_in_bits() if self.private_key else 'Unknown'
            }
            
            with open(filepath, 'w') as f:
                json.dump(data, f, indent=4)
            
            print(f"\n Signature saved to: {filepath}")
            return True
            
        except Exception as e:
            print(f" Error saving signature: {e}")
            return False
    
    def load_signature_from_file(self, filename="signature.json"):
        """Load message and signature from JSON file"""
        try:
            filepath = os.path.join(self.signatures_folder, filename)
            
            with open(filepath, 'r') as f:
                data = json.load(f)
            
            message = data['message']
            signature = bytes.fromhex(data['signature'])
            
            print(f"\n Signature loaded from: {filepath}")
            print(f"  Timestamp: {data.get('timestamp', 'N/A')}")
            print(f"  Key Size: {data.get('key_size', 'N/A')} bits")
            
            return message, signature
            
        except FileNotFoundError:
            print(f" File not found: {filepath}")
            return None, None
        except Exception as e:
            print(f" Error loading signature: {e}")
            return None, None
    
    # ============== DISPLAY INFO ==============
    
    def display_keys(self):
        """Display current keys information"""
        if self.private_key:
            print("\n" + "="*60)
            print("PRIVATE KEY:")
            print("="*60)
            print(self.private_key.export_key().decode())
            
        if self.public_key:
            print("\n" + "="*60)
            print("PUBLIC KEY:")
            print("="*60)
            print(self.public_key.export_key().decode())
        
        if not self.private_key and not self.public_key:
            print("\n  No keys loaded")