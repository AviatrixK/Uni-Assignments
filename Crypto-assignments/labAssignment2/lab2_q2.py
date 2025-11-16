# Show AES under different modes and how ciphertexts look.

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import base64

def b64(x: bytes) -> str:
    return base64.b64encode(x).decode()

def test_mode(mode_name, key, plaintext):
    if mode_name == 'ECB':
        cipher = AES.new(key, AES.MODE_ECB)
        ct = cipher.encrypt(pad(plaintext, AES.block_size))
        # decrypt
        dec = AES.new(key, AES.MODE_ECB).decrypt(ct)
        pt = unpad(dec, AES.block_size)
        return ct, pt
    elif mode_name == 'CBC':
        iv = get_random_bytes(16)
        cipher = AES.new(key, AES.MODE_CBC, iv)
        ct = cipher.encrypt(pad(plaintext, AES.block_size))
        dec = AES.new(key, AES.MODE_CBC, iv).decrypt(ct)
        pt = unpad(dec, AES.block_size)
        return iv + ct, pt  # prefix iv so we can show it
    elif mode_name == 'CFB':
        iv = get_random_bytes(16)
        cipher = AES.new(key, AES.MODE_CFB, iv)
        ct = cipher.encrypt(plaintext)  # CFB works on bytes directly
        dec = AES.new(key, AES.MODE_CFB, iv).decrypt(ct)
        return iv + ct, dec
    elif mode_name == 'OFB':
        iv = get_random_bytes(16)
        cipher = AES.new(key, AES.MODE_OFB, iv)
        ct = cipher.encrypt(plaintext)
        dec = AES.new(key, AES.MODE_OFB, iv).decrypt(ct)
        return iv + ct, dec
    elif mode_name == 'CTR':
        # use nonce parameter (recommended)
        nonce = get_random_bytes(8)
        cipher = AES.new(key, AES.MODE_CTR, nonce=nonce)
        ct = cipher.encrypt(plaintext)
        dec = AES.new(key, AES.MODE_CTR, nonce=nonce).decrypt(ct)
        return nonce + ct, dec

def main():
    key = get_random_bytes(16)
    # normal plaintext and repeated plaintext for pattern observation
    plain1 = b"Confidential Transaction"
    plain2 = (b"ATTACKATTACKATTACKATTACK")  # repeating pattern to visualize ECB weakness

    modes = ['ECB','CBC','CFB','OFB','CTR']
    for plain, name in ((plain1, 'Normal'), (plain2, 'Repeating')):
        print(f"\n--- {name} plaintext: {plain.decode(errors='ignore')} ---")
        for m in modes:
            ct, dec = test_mode(m, key, plain)
            print(f"\nMode: {m}")
            print(" Ciphertext (base64):", b64(ct))
            print(" Decrypted ok?:", dec == plain)

    print("\nObservation: ECB exposes repeated blocks in ciphertext; other modes mask patterns.")
    print("IV/nonce must be unique (and random for CBC/CFB/OFB). CTR uses nonce; do not reuse nonce with same key.")

if __name__ == "__main__":
    main()
