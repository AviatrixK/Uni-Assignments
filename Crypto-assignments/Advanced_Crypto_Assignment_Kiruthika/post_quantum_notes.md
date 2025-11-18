# Q5: Post-Quantum Cryptography - Emerging Trends

## Table of Contents
1. [Introduction](#introduction)
2. [NIST Post-Quantum Candidates](#nist-candidates)
3. [Algorithm Categories](#algorithm-categories)
4. [Detailed Analysis](#detailed-analysis)
5. [Implementation Example](#implementation)
6. [Impact on Current Systems](#impact)
7. [Migration Strategy](#migration)

---

## Introduction

### The Quantum Threat

Quantum computers threaten current public-key cryptography:

| Algorithm | Type | Quantum Vulnerable? | Post-Quantum Alternative |
|-----------|------|---------------------|-------------------------|
| RSA | Public-key encryption | ✅ Yes (Shor's algorithm) | Lattice-based (Kyber) |
| ECC | Public-key encryption | ✅ Yes (Shor's algorithm) | Lattice-based, Hash-based |
| DSA/ECDSA | Digital signatures | ✅ Yes (Shor's algorithm) | Dilithium, Falcon |
| AES-128 | Symmetric encryption | ⚠️ Weakened (Grover's) | AES-256 |
| SHA-256 | Hashing | ⚠️ Weakened (Grover's) | SHA-384, SHA-512 |

**Shor's Algorithm**: Efficiently factors large numbers and solves discrete logarithm
**Grover's Algorithm**: Provides quadratic speedup for search problems

---

## NIST Post-Quantum Candidates

### Selected Algorithms (2022)

#### 1. **CRYSTALS-Kyber** (Key Encapsulation)
- **Type**: Lattice-based (Module-LWE)
- **Status**: Selected for standardization
- **Use Case**: General encryption
- **Security Levels**: Kyber512, Kyber768, Kyber1024
- **Key Sizes**:
  - Public key: 800-1568 bytes
  - Private key: 1632-3168 bytes
- **Performance**: Fast, suitable for embedded devices

#### 2. **CRYSTALS-Dilithium** (Digital Signatures)
- **Type**: Lattice-based (Module-LWE/Module-SIS)
- **Status**: Selected for standardization
- **Use Case**: General-purpose signatures
- **Security Levels**: Dilithium2, Dilithium3, Dilithium5
- **Signature Size**: 2420-4595 bytes
- **Performance**: Fast verification

#### 3. **Falcon** (Digital Signatures)
- **Type**: Lattice-based (NTRU lattices)
- **Status**: Selected for standardization
- **Use Case**: Applications needing smaller signatures
- **Signature Size**: 666-1280 bytes (smaller than Dilithium)
- **Performance**: Slower signing, fast verification

#### 4. **SPHINCS+** (Digital Signatures)
- **Type**: Hash-based
- **Status**: Selected for standardization
- **Use Case**: Backup, conservative choice
- **Advantages**: Only relies on hash function security
- **Disadvantages**: Large signatures (7-49 KB)

### Alternate Candidates (Continued evaluation)

- **BIKE, HQC**: Code-based
- **SIKE**: Isogeny-based (broken in 2022)
- **Classic McEliece**: Code-based (very large keys)

---

## Algorithm Categories

### 1. Lattice-Based Cryptography

**Principle**: Based on hard problems in lattices (geometric structures in n-dimensional space)

**Hard Problems**:
- **Shortest Vector Problem (SVP)**: Find shortest non-zero vector in lattice
- **Learning With Errors (LWE)**: Solve linear equations with noise

**Example (Conceptual)**: