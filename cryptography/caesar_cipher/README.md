# Caesar Cipher

A simple implementation of the Caesar cipher encryption and decryption algorithm in C, with brute force attack capability.

## What is Caesar Cipher?

The Caesar cipher is one of the simplest and most widely known encryption techniques. It is a type of substitution cipher where each letter in the plaintext is shifted by a fixed number of positions in the alphabet. For example, with a shift of 3, 'A' becomes 'D', 'B' becomes 'E', and so on.

## Features

- **Encryption**: Encrypt plaintext using a specified shift value (key)
- **Decryption**: Decrypt ciphertext using a known shift value (key)
- **Brute Force**: Attempt to decrypt ciphertext by trying all possible keys (0-25)
- **Command Line Support**: Run with command line arguments for automated use
- **Interactive Mode**: User-friendly prompts for manual operation

## Compilation

```bash
gcc -o caesar_cipher caesar_cipher.c
```

## Usage

### Interactive Mode

Run the program without arguments:

```bash
./caesar_cipher
```

Follow the prompts to:
1. Enter the shift value (key)
2. Choose operation (encrypt/decrypt/brute force)
3. Enter your text

### Command Line Mode

```bash
./caesar_cipher <key> <operation>
```

**Parameters:**
- `<key>`: Integer shift value
- `<operation>`:
    - `e`, `encrypt`, or `encryption` for encryption
    - `d`, `decrypt`, or `decryption` for decryption
    - `bf` or `brute-force` for brute force decryption

**Examples:**

```bash
# Encrypt with key 3
./caesar_cipher 3 e

# Decrypt with key 5
./caesar_cipher 5 d

# Brute force decrypt (key not needed for brute force)
./caesar_cipher 0 bf
```

## How It Works

### Encryption
Each letter is shifted forward in the alphabet by the key value. Non-alphabetic characters remain unchanged.

### Decryption
Each letter is shifted backward in the alphabet by the key value (equivalent to encrypting with negative key).

### Brute Force
Tries all possible keys (0-25) and displays each result, allowing you to identify the correct plaintext.

## Examples

**Encryption:**
- Plaintext: `Hello World`
- Key: `3`
- Ciphertext: `Khoor Zruog`

**Decryption:**
- Ciphertext: `Khoor Zruog`
- Key: `3`
- Plaintext: `Hello World`

**Brute Force:**
- Ciphertext: `Khoor Zruog`
- Output: All 26 possible decryptions with their corresponding keys

## Notes

- The program preserves case (uppercase/lowercase)
- Non-alphabetic characters (numbers, punctuation, spaces) remain unchanged
- Keys can be negative or greater than 25 (they wrap around)
- Maximum input length is 255 characters _(can be adjusted in the code if needed)_
  - To change the maximum input length, modify the `MAX_INPUT_LENGTH` constant in the code (line 6: `#define MAX_INPUT_LENGTH 256`).

## License

MIT License - see [LICENSE](LICENSE) file for details
