# Monoalphabetic Substitution Cipher

A simple implementation of the Monoalphabetic Substitution cipher encryption and decryption algorithm in C, with random key generation capability.

## What is Monoalphabetic Substitution Cipher?

The Monoalphabetic Substitution cipher is a type of substitution cipher where each letter in the plaintext is replaced by another letter from the alphabet. Unlike the Caesar cipher which uses a fixed shift, this cipher uses a complete alphabet permutation as the key. Each letter of the alphabet is mapped to exactly one other letter, creating a one-to-one correspondence.

## Features

- **Encryption**: Encrypt plaintext using a 26-character substitution key
- **Decryption**: Decrypt ciphertext using the same substitution key
- **Random Key Generation**: Automatically generate a secure random substitution key
- **Key Validation**: Ensures the provided key contains exactly 26 unique letters
- **Command Line Support**: Run with command line arguments for automated use
- **Interactive Mode**: User-friendly prompts for manual operation

## Compilation

```bash
gcc -o monoalphabetic_cipher monoalphabetic_cipher.c
```

## Usage

### Interactive Mode

Run the program without arguments:

```bash
./monoalphabetic_cipher
```

Follow the prompts to:
1. Enter a substitution key or press Enter to generate a random one
2. Choose operation (encrypt/decrypt)
3. Enter your text

### Command Line Mode

```bash
./monoalphabetic_cipher <key> <operation>
```

**Parameters:**
- `<key>`: 26-character string with unique letters, or `rand`/`random`/`generate` for random key
- `<operation>`:
  - `e`, `encrypt`, or `encryption` for encryption
  - `d`, `decrypt`, or `decryption` for decryption

**Examples:**

```bash
# Encrypt with custom key
./monoalphabetic_cipher zyxwvutsrqponmlkjihgfedcba e

# Decrypt with custom key
./monoalphabetic_cipher zyxwvutsrqponmlkjihgfedcba d

# Generate random key and encrypt
./monoalphabetic_cipher random e

# Interactive mode
./monoalphabetic_cipher
```

## How It Works

### Encryption
Each letter in the plaintext is replaced by the corresponding letter at the same position in the substitution key. For example, if the key is "zyxwvutsrqponmlkjihgfedcba", then 'a' becomes 'z', 'b' becomes 'y', etc.

### Decryption
Each letter in the ciphertext is mapped back to its original position in the alphabet using the same substitution key.

### Key Requirements
- Must be exactly 26 characters long
- Must contain each letter of the alphabet exactly once
- Case is preserved during encryption/decryption

## Examples

**Encryption:**
- Key: `zyxwvutsrqponmlkjihgfedcba`
- Plaintext: `Hello World`
- Ciphertext: `Svool Dliow`

**Decryption:**
- Key: `zyxwvutsrqponmlkjihgfedcba`
- Ciphertext: `Svool Dliow`
- Plaintext: `Hello World`

**Random Key Generation:**
- Generated key: `qwertyuiopasdfghjklzxcvbnm`
- The program automatically creates a secure random permutation of the alphabet

## Security Notes

- More secure than Caesar cipher due to larger key space (26! possible keys)
- Random key generation uses Fisher-Yates shuffle algorithm for uniform distribution
- Each letter maps to exactly one other letter, preventing frequency analysis patterns
- Case is preserved, and non-alphabetic characters remain unchanged

## Notes

- The program preserves case (uppercase/lowercase)
- Non-alphabetic characters (numbers, punctuation, spaces) remain unchanged
- Random key generation is seeded with current time for uniqueness
- Maximum input length is 255 characters _(can be adjusted in the code if needed)_
  - To change the maximum input length, modify the `MAX_INPUT_LENGTH` constant in the code (line 17: `#define MAX_INPUT_LENGTH 256`).

## License

MIT License - see [LICENSE](/LICENSE) file for details
