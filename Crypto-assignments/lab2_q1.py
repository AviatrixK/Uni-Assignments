# Purpose: Encrypt a plaintext using DES, 3DES and AES, show ciphertexts and timing.

import time
import base64
from Crypto.Cipher import DES, DES3, AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

PLAINTEXT = b"Confidential Transaction"

def b64(x: bytes) -> str:
    return base64.b64encode(x).decode()

def time_encrypt(cipher_obj, data, block_size, runs=2000):
    # Run encryption many times and return average time.
    start = time.perf_counter()
    for _ in range(runs):
        _ = cipher_obj.encrypt(pad(data, block_size))
    end = time.perf_counter()
    return (end - start) / runs

def run_des(plaintext):
    key = get_random_bytes(8)  # DES key size: 8 bytes
    iv = get_random_bytes(8)   # block size 8
    cipher = DES.new(key, DES.MODE_CBC, iv)
    ct = cipher.encrypt(pad(plaintext, DES.block_size))
    # measure (recreate cipher each run to simulate real usage)
    avg_time = time.perf_counter()
    runs = 2000
    t0 = time.perf_counter()
    for _ in range(runs):
        c = DES.new(key, DES.MODE_CBC, iv).encrypt(pad(plaintext, DES.block_size))
    t1 = time.perf_counter()
    avg_time = (t1 - t0) / runs
    return {
        'name': 'DES',
        'key': b64(key),
        'iv': b64(iv),
        'ciphertext': b64(ct),
        'time': avg_time
    }

def run_3des(plaintext):
    # keep trying until key is accepted
    while True:
        key = get_random_bytes(24)  # 3DES 24 bytes (3 x 8)
        try:
            iv = get_random_bytes(8)
            cipher = DES3.new(key, DES3.MODE_CBC, iv)
            ct = cipher.encrypt(pad(plaintext, DES3.block_size))
            break
        except ValueError:
            continue
    runs = 2000
    t0 = time.perf_counter()
    for _ in range(runs):
        _ = DES3.new(key, DES3.MODE_CBC, iv).encrypt(pad(plaintext, DES3.block_size))
    t1 = time.perf_counter()
    return {
        'name': '3DES',
        'key': b64(key),
        'iv': b64(iv),
        'ciphertext': b64(ct),
        'time': (t1 - t0) / runs
    }

def run_aes(plaintext):
    key = get_random_bytes(16)  # AES-128
    iv = get_random_bytes(16)
    cipher = AES.new(key, AES.MODE_CBC, iv)
    ct = cipher.encrypt(pad(plaintext, AES.block_size))
    runs = 2000
    t0 = time.perf_counter()
    for _ in range(runs):
        _ = AES.new(key, AES.MODE_CBC, iv).encrypt(pad(plaintext, AES.block_size))
    t1 = time.perf_counter()
    return {
        'name': 'AES-128',
        'key': b64(key),
        'iv': b64(iv),
        'ciphertext': b64(ct),
        'time': (t1 - t0) / runs
    }

def main():
    print("Plaintext:", PLAINTEXT.decode())
    for fn in (run_des, run_3des, run_aes):
        r = fn(PLAINTEXT)
        print("\n" + r['name'])
        print(" Key (base64):", r['key'])
        print(" IV  (base64):", r['iv'])
        print(" Ciphertext (base64):", r['ciphertext'])
        print(" Avg encrypt time (s):", "{:.8f}".format(r['time']))
    print("\nNote: Times are average over many runs; results vary by machine.")

if __name__ == "__main__":
    main()
