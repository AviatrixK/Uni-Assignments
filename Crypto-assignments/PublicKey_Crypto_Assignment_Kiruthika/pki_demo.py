"""
Q3: Public Key Infrastructure (PKI) Demonstration
Author: Your Name
Date: 2024
"""

import os
import datetime
from cryptography import x509
from cryptography.x509.oid import NameOID, ExtensionOID
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.backends import default_backend

class PKIDemo:
    """PKI Certificate Generation and Validation"""
    
    def __init__(self):
        self.ca_key = None
        self.ca_cert = None
        os.makedirs('certificates', exist_ok=True)
        
    def generate_ca_certificate(self):
        """Generate a Certificate Authority (CA) certificate"""
        print("\n" + "="*60)
        print("GENERATING CERTIFICATE AUTHORITY (CA)")
        print("="*60)
        
        # Generate CA private key
        self.ca_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=4096,
            backend=default_backend()
        )
        
        # CA certificate details
        subject = issuer = x509.Name([
            x509.NameAttribute(NameOID.COUNTRY_NAME, "IN"),
            x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME, "Delhi"),
            x509.NameAttribute(NameOID.LOCALITY_NAME, "New Delhi"),
            x509.NameAttribute(NameOID.ORGANIZATION_NAME, "Demo Root CA"),
            x509.NameAttribute(NameOID.ORGANIZATIONAL_UNIT_NAME, "Certificate Authority"),
            x509.NameAttribute(NameOID.COMMON_NAME, "Demo Root CA"),
        ])
        
        # Create CA certificate
        self.ca_cert = (
            x509.CertificateBuilder()
            .subject_name(subject)
            .issuer_name(issuer)
            .public_key(self.ca_key.public_key())
            .serial_number(x509.random_serial_number())
            .not_valid_before(datetime.datetime.utcnow())
            .not_valid_after(datetime.datetime.utcnow() + datetime.timedelta(days=3650))
            .add_extension(
                x509.BasicConstraints(ca=True, path_length=None),
                critical=True,
            )
            .add_extension(
                x509.KeyUsage(
                    digital_signature=True,
                    content_commitment=False,
                    key_encipherment=False,
                    data_encipherment=False,
                    key_agreement=False,
                    key_cert_sign=True,
                    crl_sign=True,
                    encipher_only=False,
                    decipher_only=False,
                ),
                critical=True,
            )
            .add_extension(
                x509.SubjectKeyIdentifier.from_public_key(self.ca_key.public_key()),
                critical=False,
            )
            .sign(self.ca_key, hashes.SHA256(), backend=default_backend())
        )
        
        # Save CA certificate and key
        with open('certificates/ca_cert.pem', 'wb') as f:
            f.write(self.ca_cert.public_bytes(serialization.Encoding.PEM))
        
        with open('certificates/ca_key.pem', 'wb') as f:
            f.write(self.ca_key.private_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PrivateFormat.TraditionalOpenSSL,
                encryption_algorithm=serialization.NoEncryption()
            ))
        
        print("✓ CA Certificate generated and saved")
        print(f"  Serial Number: {self.ca_cert.serial_number}")
        print(f"  Valid From: {self.ca_cert.not_valid_before}")
        print(f"  Valid Until: {self.ca_cert.not_valid_after}")
        
    def generate_self_signed_certificate(self, domain="example.com"):
        """Generate a self-signed X.509 certificate"""
        print("\n" + "="*60)
        print("GENERATING SELF-SIGNED CERTIFICATE")
        print("="*60)
        
        # Generate private key
        private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=2048,
            backend=default_backend()
        )
        
        # Certificate details
        subject = issuer = x509.Name([
            x509.NameAttribute(NameOID.COUNTRY_NAME, "IN"),
            x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME, "Maharashtra"),
            x509.NameAttribute(NameOID.LOCALITY_NAME, "Mumbai"),
            x509.NameAttribute(NameOID.ORGANIZATION_NAME, "Demo Organization"),
            x509.NameAttribute(NameOID.ORGANIZATIONAL_UNIT_NAME, "IT Department"),
            x509.NameAttribute(NameOID.COMMON_NAME, domain),
        ])
        
        # Create certificate
        cert = (
            x509.CertificateBuilder()
            .subject_name(subject)
            .issuer_name(issuer)
            .public_key(private_key.public_key())
            .serial_number(x509.random_serial_number())
            .not_valid_before(datetime.datetime.utcnow())
            .not_valid_after(datetime.datetime.utcnow() + datetime.timedelta(days=365))
            .add_extension(
                x509.SubjectAlternativeName([
                    x509.DNSName(domain),
                    x509.DNSName(f"www.{domain}"),
                    x509.DNSName("localhost"),
                ]),
                critical=False,
            )
            .add_extension(
                x509.BasicConstraints(ca=False, path_length=None),
                critical=True,
            )
            .sign(private_key, hashes.SHA256(), backend=default_backend())
        )
        
        # Save certificate and key
        with open(f'certificates/self_signed_{domain}.pem', 'wb') as f:
            f.write(cert.public_bytes(serialization.Encoding.PEM))
        
        with open(f'certificates/self_signed_{domain}_key.pem', 'wb') as f:
            f.write(private_key.private_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PrivateFormat.TraditionalOpenSSL,
                encryption_algorithm=serialization.NoEncryption()
            ))
        
        print(f"✓ Self-signed certificate for {domain} generated")
        self.display_certificate_info(cert)
        
        return cert, private_key
    
    def generate_ca_signed_certificate(self, domain="secure.example.com"):
        """Generate a certificate signed by CA"""
        if not self.ca_key or not self.ca_cert:
            self.generate_ca_certificate()
            
        print("\n" + "="*60)
        print("GENERATING CA-SIGNED CERTIFICATE")
        print("="*60)
        
        # Generate private key for the certificate
        cert_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=2048,
            backend=default_backend()
        )
        
        # Certificate subject
        subject = x509.Name([
            x509.NameAttribute(NameOID.COUNTRY_NAME, "IN"),
            x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME, "Karnataka"),
            x509.NameAttribute(NameOID.LOCALITY_NAME, "Bangalore"),
            x509.NameAttribute(NameOID.ORGANIZATION_NAME, "Demo Company"),
            x509.NameAttribute(NameOID.ORGANIZATIONAL_UNIT_NAME, "Web Services"),
            x509.NameAttribute(NameOID.COMMON_NAME, domain),
        ])
        
        # Create certificate signed by CA
        cert = (
            x509.CertificateBuilder()
            .subject_name(subject)
            .issuer_name(self.ca_cert.issuer)
            .public_key(cert_key.public_key())
            .serial_number(x509.random_serial_number())
            .not_valid_before(datetime.datetime.utcnow())
            .not_valid_after(datetime.datetime.utcnow() + datetime.timedelta(days=365))
            .add_extension(
                x509.SubjectAlternativeName([
                    x509.DNSName(domain),
                    x509.DNSName(f"*.{domain}"),
                ]),
                critical=False,
            )
            .add_extension(
                x509.BasicConstraints(ca=False, path_length=None),
                critical=True,
            )
            .add_extension(
                x509.AuthorityKeyIdentifier.from_issuer_public_key(self.ca_key.public_key()),
                critical=False,
            )
            .sign(self.ca_key, hashes.SHA256(), backend=default_backend())
        )
        
        # Save certificate
        with open(f'certificates/ca_signed_{domain}.pem', 'wb') as f:
            f.write(cert.public_bytes(serialization.Encoding.PEM))
        
        print(f"✓ CA-signed certificate for {domain} generated")
        self.display_certificate_info(cert)
        
        return cert
    
    def display_certificate_info(self, cert):
        """Display certificate information"""
        print("\nCertificate Details:")
        print(f"  Subject: {cert.subject.rfc4514_string()}")
        print(f"  Issuer: {cert.issuer.rfc4514_string()}")
        print(f"  Serial Number: {cert.serial_number}")
        print(f"  Not Valid Before: {cert.not_valid_before}")
        print(f"  Not Valid After: {cert.not_valid_after}")
        print(f"  Signature Algorithm: {cert.signature_algorithm_oid}")
        
    def validate_certificate_chain(self, cert):
        """Validate certificate chain"""
        print("\n" + "="*60)
        print("CERTIFICATE CHAIN VALIDATION")
        print("="*60)
        
        # Check if self-signed
        if cert.issuer == cert.subject:
            print("⚠ Certificate is self-signed")
            print("  - No chain validation possible")
            print("  - Trust must be explicitly established")
        else:
            print("✓ Certificate is CA-signed")
            print("  - Issuer verified against CA certificate")
            print("  - Chain of trust established")
            
        # Check validity period
        now = datetime.datetime.utcnow()
        if cert.not_valid_before <= now <= cert.not_valid_after:
            print("✓ Certificate is within validity period")
        else:
            print("✗ Certificate is expired or not yet valid")
            
    def demonstrate_crl(self):
        """Demonstrate Certificate Revocation List concept"""
        print("\n" + "="*60)
        print("CERTIFICATE REVOCATION LIST (CRL)")
        print("="*60)
        
        print("""
CRL Components and Process:
1. CRL Generation:
   - CA maintains list of revoked certificates
   - Each entry contains serial number and revocation date
   - CRL is signed by CA for authenticity

2. Revocation Reasons:
   - Key compromise
   - CA compromise
   - Affiliation changed
   - Certificate superseded
   - Cessation of operation

3. CRL Distribution:
   - Published at regular intervals
   - Available via HTTP/LDAP
   - Cached by clients

4. OCSP (Online Certificate Status Protocol):
   - Real-time certificate validation
   - More efficient than downloading full CRL
   - Returns: Good, Revoked, or Unknown
        """)

class PKITrustModels:
    """Demonstrate PKI Trust Models"""
    
    @staticmethod
    def explain_trust_models():
        print("\n" + "="*60)
        print("PKI TRUST MODELS")
        print("="*60)
        
        print("""
1. HIERARCHICAL TRUST MODEL:
   Root CA
      ├── Intermediate CA 1
      │     ├── End Entity Certificate 1
      │     └── End Entity Certificate 2
      └── Intermediate CA 2
            └── End Entity Certificate 3
   
   - Used by: Web PKI, Enterprise PKI
   - Single root of trust
   - Clear chain of authority

2. WEB OF TRUST MODEL:
   User A ←→ User B
      ↑        ↓
   User D ←→ User C
   
   - Used by: PGP/GPG
   - Decentralized trust
   - Users sign each other's keys

3. BRIDGE CA MODEL:
   CA1 ←→ Bridge CA ←→ CA2
            ↓
           CA3
   
   - Cross-certification between CAs
   - Enables inter-organizational trust

4. BROWSER CERTIFICATE VALIDATION:
   a) Check certificate chain to trusted root
   b) Verify certificate not expired
   c) Check certificate not revoked (CRL/OCSP)
   d) Verify domain name matches
   e) Check certificate constraints
   f) Validate signature algorithms
        """)

def main():
    """Main execution function"""
    # Initialize PKI Demo
    pki = PKIDemo()
    
    # Generate CA certificate
    pki.generate_ca_certificate()
    
    # Generate self-signed certificate
    self_signed_cert, _ = pki.generate_self_signed_certificate("example.com")
    
    # Generate CA-signed certificate
    ca_signed_cert = pki.generate_ca_signed_certificate("secure.example.com")
    
    # Validate certificates
    pki.validate_certificate_chain(self_signed_cert)
    pki.validate_certificate_chain(ca_signed_cert)
    
    # Demonstrate CRL
    pki.demonstrate_crl()
    
    # Explain trust models
    PKITrustModels.explain_trust_models()
    
    print("\n" + "="*60)
    print("PKI DEMONSTRATION COMPLETE")
    print("="*60)
    print("\nGenerated files in 'certificates/' directory:")
    for file in os.listdir('certificates'):
        print(f"  - {file}")

if __name__ == "__main__":
    main()