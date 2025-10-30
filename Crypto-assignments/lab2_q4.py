# Compute HMAC-SHA256 for a file, then show that modifying the file changes HMAC (integrity check).

import hmac
import hashlib

def hmac_of_file(path, key):
    h = hmac.new(key, digestmod=hashlib.sha256)
    with open(path, 'rb') as f:
        while True:
            chunk = f.read(8192)
            if not chunk:
                break
            h.update(chunk)
    return h.hexdigest()

def main():
    path = "sample_inputs.txt"
    key = b'secret_shared_key_123'  # in real world use a strong random key stored securely
    original_hmac = hmac_of_file(path, key)
    print("Original HMAC (SHA-256):", original_hmac)

    # Simulate file tampering: read, modify, and compute hmac of modified bytes (without changing disk)
    with open(path, 'rb') as f:
        data = f.read()
    tampered = data + b"\n# tampered"
    h_tampered = hmac.new(key, tampered, hashlib.sha256).hexdigest()
    print("HMAC after tampering:", h_tampered)
    print("Match after tampering?:", h_tampered == original_hmac)
    print("\nConclusion: HMAC fails on tampered data -> detects modification.")
    print("HMAC uses a secret key; prevents attackers from forging valid tag without key.")

if __name__ == "__main__":
    main()
