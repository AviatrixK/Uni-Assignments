# A replay-attack demo.

import time
import hmac
import hashlib

# --------- Replay attack simulation ---------
# Simple token format: token = HMAC(key, username || timestamp)
def create_token(username, key, timestamp):
    msg = f"{username}|{timestamp}".encode()
    tag = hmac.new(key, msg, hashlib.sha256).hexdigest()
    return f"{username}|{timestamp}|{tag}"

def verify_token(token, key, max_age=30):
    # parse token, check timestamp age and HMAC
    try:
        user, ts_str, tag = token.split("|")
        ts = int(ts_str)
    except Exception:
        return False, "invalid format"
    # check age
    now = int(time.time())
    if abs(now - ts) > max_age:
        return False, "token expired"
    # recompute tag
    msg = f"{user}|{ts}".encode()
    expected = hmac.new(key, msg, hashlib.sha256).hexdigest()
    if not hmac.compare_digest(expected, tag):
        return False, "bad tag"
    return True, "ok"

def replay_demo():
    key = b'shared_key_demo'
    user = "alice"
    ts = int(time.time())
    token = create_token(user, key, ts)
    print("Original token:", token)
    # Attacker can replay token later:
    print("Simulating replay after 5 seconds...")
    time.sleep(5)
    ok, reason = verify_token(token, key, max_age=60)
    print("Replay verify:", ok, reason)
    # Prevention: use nonce or one-time token store, or very short expiry.
    print("If token reuse must be prevented, server tracks used nonces or short TTL or one-time tokens.")

def main():
    print("=== Replay attack demo ===")
    replay_demo()

if __name__ == "__main__":
    main()