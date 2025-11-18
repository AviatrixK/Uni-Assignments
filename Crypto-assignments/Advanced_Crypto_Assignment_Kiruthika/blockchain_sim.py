"""
Q4: Blockchain Cryptography Simulation
Demonstrates hashing, digital signatures, block chaining, and tamper-proofing
"""

import hashlib
import json
import time
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.backends import default_backend
import base64


class MerkleTree:
    """Implements Merkle Tree for efficient transaction verification"""
    
    @staticmethod
    def hash_data(data):
        """Hash a piece of data"""
        return hashlib.sha256(data.encode() if isinstance(data, str) else data).hexdigest()
    
    @staticmethod
    def build_tree(transactions):
        """Build Merkle tree from transactions"""
        if not transactions:
            return None
        
        # Hash all transactions
        current_level = [MerkleTree.hash_data(tx) for tx in transactions]
        
        # Build tree bottom-up
        tree = [current_level[:]]
        
        while len(current_level) > 1:
            next_level = []
            
            # Process pairs
            for i in range(0, len(current_level), 2):
                left = current_level[i]
                right = current_level[i + 1] if i + 1 < len(current_level) else left
                
                combined = left + right
                parent_hash = MerkleTree.hash_data(combined)
                next_level.append(parent_hash)
            
            tree.append(next_level)
            current_level = next_level
        
        return tree
    
    @staticmethod
    def get_root(tree):
        """Get Merkle root (top of tree)"""
        return tree[-1][0] if tree else None
    
    @staticmethod
    def get_proof(tree, transaction_index):
        """Get Merkle proof for a transaction"""
        proof = []
        index = transaction_index
        
        for level in tree[:-1]:
            if index % 2 == 0:
                sibling_index = index + 1
                if sibling_index < len(level):
                    proof.append(('right', level[sibling_index]))
            else:
                sibling_index = index - 1
                proof.append(('left', level[sibling_index]))
            
            index = index // 2
        
        return proof


class Block:
    """Represents a single block in the blockchain"""
    
    def __init__(self, index, transactions, previous_hash, timestamp=None):
        self.index = index
        self.timestamp = timestamp or time.time()
        self.transactions = transactions
        self.previous_hash = previous_hash
        self.nonce = 0
        self.merkle_root = self._calculate_merkle_root()
        self.hash = self.calculate_hash()
    
    def _calculate_merkle_root(self):
        """Calculate Merkle root of transactions"""
        if not self.transactions:
            return "0" * 64
        
        tree = MerkleTree.build_tree([json.dumps(tx, sort_keys=True) for tx in self.transactions])
        return MerkleTree.get_root(tree)
    
    def calculate_hash(self):
        """Calculate block hash"""
        block_string = json.dumps({
            "index": self.index,
            "timestamp": self.timestamp,
            "transactions": self.transactions,
            "previous_hash": self.previous_hash,
            "merkle_root": self.merkle_root,
            "nonce": self.nonce
        }, sort_keys=True)
        
        return hashlib.sha256(block_string.encode()).hexdigest()
    
    def mine_block(self, difficulty):
        """Proof of Work mining"""
        target = "0" * difficulty
        
        print(f"⛏️  Mining block {self.index}...", end="")
        start_time = time.time()
        
        while self.hash[:difficulty] != target:
            self.nonce += 1
            self.hash = self.calculate_hash()
        
        elapsed = time.time() - start_time
        print(f" Mined! Hash: {self.hash} (Nonce: {self.nonce}, Time: {elapsed:.2f}s)")
    
    def to_dict(self):
        """Convert block to dictionary"""
        return {
            "index": self.index,
            "timestamp": self.timestamp,
            "transactions": self.transactions,
            "previous_hash": self.previous_hash,
            "merkle_root": self.merkle_root,
            "nonce": self.nonce,
            "hash": self.hash
        }


class Wallet:
    """Cryptocurrency wallet with public/private key pair"""
    
    def __init__(self, name):
        self.name = name
        self.private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=2048,
            backend=default_backend()
        )
        self.public_key = self.private_key.public_key()
        self.address = self._generate_address()
    
    def _generate_address(self):
        """Generate wallet address from public key"""
        public_bytes = self.public_key.public_bytes(
            encoding=serialization.Encoding.DER,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        )
        return hashlib.sha256(public_bytes).hexdigest()[:40]
    
    def sign_transaction(self, transaction):
        """Sign a transaction"""
        tx_string = json.dumps(transaction, sort_keys=True)
        signature = self.private_key.sign(
            tx_string.encode(),
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )
        return base64.b64encode(signature).decode()
    
    @staticmethod
    def verify_signature(public_key, transaction, signature):
        """Verify transaction signature"""
        try:
            tx_string = json.dumps(transaction, sort_keys=True)
            public_key.verify(
                base64.b64decode(signature),
                tx_string.encode(),
                padding.PSS(
                    mgf=padding.MGF1(hashes.SHA256()),
                    salt_length=padding.PSS.MAX_LENGTH
                ),
                hashes.SHA256()
            )
            return True
        except:
            return False


class Blockchain:
    """Simple blockchain implementation"""
    
    def __init__(self, difficulty=4):
        self.chain = []
        self.difficulty = difficulty
        self.pending_transactions = []
        self.mining_reward = 50
        self.wallets = {}
        
        # Create genesis block
        self.create_genesis_block()
    
    def create_genesis_block(self):
        """Create the first block"""
        genesis_block = Block(0, [{"type": "genesis", "data": "Genesis Block"}], "0")
        genesis_block.mine_block(self.difficulty)
        self.chain.append(genesis_block)
        print(f" Genesis block created: {genesis_block.hash}")
    
    def get_latest_block(self):
        """Get the most recent block"""
        return self.chain[-1]
    
    def add_transaction(self, transaction):
        """Add a transaction to pending transactions"""
        self.pending_transactions.append(transaction)
        print(f" Transaction added: {transaction['from'][:10]} → {transaction['to'][:10]} ({transaction['amount']} coins)")
    
    def mine_pending_transactions(self, miner_address):
        """Mine pending transactions into a new block"""
        # Create new block with pending transactions
        block = Block(
            index=len(self.chain),
            transactions=self.pending_transactions,
            previous_hash=self.get_latest_block().hash
        )
        
        # Mine the block
        block.mine_block(self.difficulty)
        
        # Add to chain
        self.chain.append(block)
        
        # Reset pending transactions and add mining reward
        self.pending_transactions = [
            {
                "from": "NETWORK",
                "to": miner_address,
                "amount": self.mining_reward,
                "type": "mining_reward"
            }
        ]
        
        print(f" Block {block.index} added to chain")
    
    def is_chain_valid(self):
        """Validate entire blockchain"""
        for i in range(1, len(self.chain)):
            current_block = self.chain[i]
            previous_block = self.chain[i - 1]
            
            # Check hash integrity
            if current_block.hash != current_block.calculate_hash():
                print(f" Block {i} has been tampered with!")
                return False
            
            # Check chain linkage
            if current_block.previous_hash != previous_block.hash:
                print(f" Block {i} previous_hash doesn't match!")
                return False
            
            # Check proof of work
            if not current_block.hash.startswith("0" * self.difficulty):
                print(f" Block {i} doesn't meet difficulty requirement!")
                return False
        
        print(" Blockchain is valid!")
        return True
    
    def get_balance(self, address):
        """Calculate balance for an address"""
        balance = 0
        
        for block in self.chain:
            for transaction in block.transactions:
                if transaction.get('from') == address:
                    balance -= transaction.get('amount', 0)
                if transaction.get('to') == address:
                    balance += transaction.get('amount', 0)
        
        return balance
    
    def demonstrate_tampering(self):
        """Show what happens when blockchain is tampered with"""
        print("\n" + "=" * 70)
        print("TAMPER DETECTION DEMONSTRATION")
        print("=" * 70)
        
        print("\n Original blockchain state:")
        self.print_chain()
        
        print("\n Tampering with block 1...")
        # Try to change a transaction in block 1
        if len(self.chain) > 1:
            original_tx = self.chain[1].transactions[0].copy()
            self.chain[1].transactions[0]['amount'] = 999999
            
            print(f"   Changed amount from {original_tx.get('amount')} to 999999")
            print("\n Validating blockchain after tampering...")
            
            self.is_chain_valid()
            
            # Restore
            self.chain[1].transactions[0] = original_tx
    
    def print_chain(self):
        """Print blockchain summary"""
        print(f"\n{'Block':<8} {'Hash':<20} {'Previous Hash':<20} {'Transactions':<15}")
        print("-" * 70)
        for block in self.chain:
            print(f"{block.index:<8} {block.hash[:16]:<20} {block.previous_hash[:16]:<20} {len(block.transactions):<15}")


def demonstrate_blockchain():
    """Main blockchain demonstration"""
    
    print("=" * 70)
    print("BLOCKCHAIN CRYPTOGRAPHY DEMONSTRATION")
    print("=" * 70)
    
    # Create blockchain with difficulty 3 (for faster demo)
    blockchain = Blockchain(difficulty=3)
    
    # Create wallets
    alice = Wallet("Alice")
    bob = Wallet("Bob")
    miner = Wallet("Miner")
    
    print(f"\n Alice's address: {alice.address}")
    print(f" Bob's address: {bob.address}")
    print(f" Miner's address: {miner.address}")
    
    print("\n" + "=" * 70)
    print("TRANSACTION CREATION AND SIGNING")
    print("=" * 70)
    
    # Create and sign transaction
    transaction1 = {
        "from": alice.address,
        "to": bob.address,
        "amount": 30,
        "timestamp": time.time()
    }
    
    signature1 = alice.sign_transaction(transaction1)
    transaction1["signature"] = signature1
    
    print(f"  Alice signed transaction")
    print(f"   Signature: {signature1[:50]}...")
    
    # Verify signature
    verified = Wallet.verify_signature(alice.public_key, 
                                       {k: v for k, v in transaction1.items() if k != 'signature'}, 
                                       signature1)
    print(f"   Verification: {' Valid' if verified else ' Invalid'}")
    
    # Add transactions
    blockchain.add_transaction(transaction1)
    
    transaction2 = {
        "from": alice.address,
        "to": bob.address,
        "amount": 20,
        "timestamp": time.time()
    }
    blockchain.add_transaction(transaction2)
    
    # Mine block
    print("\n" + "=" * 70)
    print("MINING BLOCK")
    print("=" * 70)
    blockchain.mine_pending_transactions(miner.address)
    
    # Add more transactions
    transaction3 = {
        "from": bob.address,
        "to": alice.address,
        "amount": 10,
        "timestamp": time.time()
    }
    blockchain.add_transaction(transaction3)
    
    blockchain.mine_pending_transactions(miner.address)
    
    # Print blockchain
    print("\n" + "=" * 70)
    print("BLOCKCHAIN STATE")
    print("=" * 70)
    blockchain.print_chain()
    
    # Check balances
    print("\n" + "=" * 70)
    print("ACCOUNT BALANCES")
    print("=" * 70)
    print(f"Alice: {blockchain.get_balance(alice.address)} coins")
    print(f"Bob: {blockchain.get_balance(bob.address)} coins")
    print(f"Miner: {blockchain.get_balance(miner.address)} coins")
    
    # Validate blockchain
    print("\n" + "=" * 70)
    print("BLOCKCHAIN VALIDATION")
    print("=" * 70)
    blockchain.is_chain_valid()
    
    # Demonstrate tampering
    blockchain.demonstrate_tampering()
    
    # Merkle Tree demonstration
    print("\n" + "=" * 70)
    print("MERKLE TREE DEMONSTRATION")
    print("=" * 70)
    
    transactions = ["tx1", "tx2", "tx3", "tx4", "tx5"]
    tree = MerkleTree.build_tree(transactions)
    root = MerkleTree.get_root(tree)
    
    print(f"Transactions: {transactions}")
    print(f"Merkle Root: {root}")
    print(f"\nMerkle Tree Structure:")
    for i, level in enumerate(reversed(tree)):
        print(f"  Level {len(tree) - i - 1}: {level}")
    
    # Get proof for transaction
    proof = MerkleTree.get_proof(tree, 0)
    print(f"\nMerkle Proof for tx1: {proof}")
    
    print("\n" + "=" * 70)
    print("CONSENSUS MECHANISMS")
    print("=" * 70)
    
    consensus_info = """
    1. PROOF OF WORK (PoW) - Used by Bitcoin
       - Miners compete to solve cryptographic puzzle
       - First to solve gets to add block and receive reward
       - Difficulty adjusts to maintain block time
       - Pros: Secure, battle-tested
       - Cons: Energy intensive
    
    2. PROOF OF STAKE (PoS) - Used by Ethereum 2.0
       - Validators chosen based on stake amount
       - More energy efficient
       - Risk of "rich get richer"
       - Pros: Energy efficient, faster
       - Cons: Less proven, potential centralization
    
    3. DELEGATED PROOF OF STAKE (DPoS)
       - Token holders vote for delegates
       - Delegates validate blocks
       - Faster but more centralized
    
    4. PRACTICAL BYZANTINE FAULT TOLERANCE (PBFT)
       - Used in permissioned blockchains
       - Nodes reach consensus through voting
       - Fast but requires known validators
    """
    
    print(consensus_info)
    
    # Save blockchain to file
    print("\n Saving blockchain to file...")
    blockchain_data = {
        "chain": [block.to_dict() for block in blockchain.chain],
        "difficulty": blockchain.difficulty
    }
    
    with open("blockchain_data.json", "w") as f:
        json.dump(blockchain_data, f, indent=2)
    
    print(" Blockchain saved to blockchain_data.json")


if __name__ == "__main__":
    demonstrate_blockchain()