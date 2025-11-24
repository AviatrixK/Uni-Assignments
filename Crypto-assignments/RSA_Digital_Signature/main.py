#!/usr/bin/env python3
"""
RSA Digital Signature System - CLI Version
Author: Your Name
"""

from rsa_signature import RSADigitalSignature
import sys

def print_banner():
    """Print application banner"""
    banner = """
    ╔════════════════════════════════════════════════════╗
    ║        RSA DIGITAL SIGNATURE SYSTEM             ║
    ║         Command Line Interface (CLI)               ║
    ╚════════════════════════════════════════════════════╝
    """
    print(banner)

def print_menu():
    """Print main menu"""
    menu = """
    ┌─────────────────────────────────────────────────┐
    │                  MAIN MENU                      │
    ├─────────────────────────────────────────────────┤
    │  1. Generate New RSA Keys                       │
    │  2. Load Existing Keys                          │
    │  3. Display Keys                                │
    │  4. Sign a Message                              │
    │  5. Verify a Signature                          │
    │  6. Save Signature to File                      │
    │  7. Load Signature from File                    │
    │  8. Complete Demo (Sign + Verify)               │
    │  0. Exit                                        │
    └─────────────────────────────────────────────────┘
    """
    print(menu)

def get_user_input(prompt):
    """Get user input with prompt"""
    return input(f"\n{prompt}: ").strip()

def main():
    """Main application loop"""
    print_banner()
    
    # Initialize RSA handler
    rsa = RSADigitalSignature()
    
    # Variables to store current signature
    current_message = None
    current_signature = None
    
    while True:
        print_menu()
        choice = get_user_input("Enter your choice")
        
        # ============== OPTION 1: Generate Keys ==============
        if choice == '1':
            print("\n" + "="*60)
            print("KEY GENERATION")
            print("="*60)
            key_size = get_user_input("Enter key size (1024/2048/4096) [default: 2048]")
            
            if key_size == '':
                key_size = 2048
            else:
                try:
                    key_size = int(key_size)
                    if key_size not in [1024, 2048, 4096]:
                        print(" Invalid size. Using 2048 bits.")
                        key_size = 2048
                except:
                    print(" Invalid input. Using 2048 bits.")
                    key_size = 2048
            
            rsa.generate_keys(key_size)
            
            # Ask to save
            save = get_user_input("Save keys to files? (y/n)")
            if save.lower() == 'y':
                rsa.save_keys()
        
        # ============== OPTION 2: Load Keys ==============
        elif choice == '2':
            print("\n" + "="*60)
            print("LOAD KEYS")
            print("="*60)
            rsa.load_keys()
        
        # ============== OPTION 3: Display Keys ==============
        elif choice == '3':
            rsa.display_keys()
        
        # ============== OPTION 4: Sign Message ==============
        elif choice == '4':
            print("\n" + "="*60)
            print("SIGN MESSAGE")
            print("="*60)
            
            print("\nEnter your message (press Enter twice to finish):")
            lines = []
            while True:
                line = input()
                if line == '':
                    break
                lines.append(line)
            
            message = '\n'.join(lines)
            
            if message:
                signature = rsa.sign_message(message)
                if signature:
                    current_message = message
                    current_signature = signature
                    
                    print(f"\n Message: {message[:50]}...")
                    print(f" Signature (hex): {signature.hex()[:80]}...")
            else:
                print("  No message entered")
        
        # ============== OPTION 5: Verify Signature ==============
        elif choice == '5':
            print("\n" + "="*60)
            print("VERIFY SIGNATURE")
            print("="*60)
            
            if current_message and current_signature:
                print(f"\nUsing current message and signature from memory")
                print(f"Message: {current_message[:100]}...")
                
                verify = get_user_input("Use current data? (y/n)")
                if verify.lower() == 'y':
                    rsa.verify_signature(current_message, current_signature)
                    continue
            
            # Manual input
            print("\nEnter message (press Enter twice to finish):")
            lines = []
            while True:
                line = input()
                if line == '':
                    break
                lines.append(line)
            
            message = '\n'.join(lines)
            
            sig_hex = get_user_input("\nEnter signature (hex)")
            
            try:
                signature = bytes.fromhex(sig_hex)
                rsa.verify_signature(message, signature)
            except ValueError:
                print(" Invalid signature format")
        
        # ============== OPTION 6: Save Signature ==============
        elif choice == '6':
            if current_message and current_signature:
                filename = get_user_input("Enter filename [default: signature.json]")
                if filename == '':
                    filename = "signature.json"
                
                if not filename.endswith('.json'):
                    filename += '.json'
                
                rsa.save_signature_to_file(current_message, current_signature, filename)
            else:
                print("  No signature in memory. Sign a message first!")
        
        # ============== OPTION 7: Load Signature ==============
        elif choice == '7':
            filename = get_user_input("Enter filename [default: signature.json]")
            if filename == '':
                filename = "signature.json"
            
            message, signature = rsa.load_signature_from_file(filename)
            if message and signature:
                current_message = message
                current_signature = signature
                
                print(f"\n Message: {message[:200]}...")
                print(f"  Signature: {signature.hex()[:80]}...")
        
        # ============== OPTION 8: Complete Demo ==============
        elif choice == '8':
            print("\n" + "="*60)
            print("COMPLETE DEMO: SIGN + VERIFY")
            print("="*60)
            
            # Generate keys if not present
            if not rsa.private_key:
                print("\n  No keys found. Generating new keys...")
                rsa.generate_keys(2048)
            
            # Sign message
            message = get_user_input("\nEnter message to sign")
            if message:
                signature = rsa.sign_message(message)
                
                if signature:
                    print("\n" + "-"*60)
                    print("Now verifying the signature...")
                    print("-"*60)
                    
                    # Verify
                    rsa.verify_signature(message, signature)
                    
                    # Test with tampered message
                    test_tamper = get_user_input("\nTest with tampered message? (y/n)")
                    if test_tamper.lower() == 'y':
                        tampered = message + " [TAMPERED]"
                        print(f"\n Tampered message: {tampered}")
                        rsa.verify_signature(tampered, signature)
        
        # ============== OPTION 0: Exit ==============
        elif choice == '0':
            print("\n Thank you for using RSA Digital Signature System!")
            print("="*60)
            sys.exit(0)
        
        else:
            print("\n Invalid choice. Please try again.")
        
        # Pause
        input("\n Press Enter to continue...")
        print("\n" * 2)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n  Program interrupted by user")
        sys.exit(0)