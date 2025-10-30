# Hash a file using MD5, SHA1, SHA256 and print results.

import hashlib

def hash_file(path):
    # read file in chunks to support large files
    h_md5 = hashlib.md5()
    h_sha1 = hashlib.sha1()
    h_sha256 = hashlib.sha256()
    with open(path, 'rb') as f:
        while True:
            chunk = f.read(8192)
            if not chunk:
                break
            h_md5.update(chunk)
            h_sha1.update(chunk)
            h_sha256.update(chunk)
    return h_md5.hexdigest(), h_sha1.hexdigest(), h_sha256.hexdigest()

def main():
    path = "sample_inputs.txt"
    md5, sha1, sha256 = hash_file(path)
    print("File:", path)
    print(" MD5:   ", md5)
    print(" SHA-1: ", sha1)
    print(" SHA-256:", sha256)
    print("\nCollision resistance:")
    print("- MD5: broken; collisions feasible (dont use for security)")
    print("- SHA-1: collision demonstrated; avoid for new systems")
    print("- SHA-256: currently secure and recommended")
    print("\nImplication for signatures: If hash is weak (collisions), attacker can forge content with same hash -> invalidates digital signatures.")

if __name__ == "__main__":
    main()
