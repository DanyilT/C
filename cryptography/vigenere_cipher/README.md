# Vigenère Cipher

A simple implementation of the Vigenère cipher encryption and decryption algorithm in C, with random key generation capability.

## What is Vigenère Cipher?

The Vigenère cipher is a polyalphabetic substitution cipher that uses a keyword to encrypt text. Unlike the Caesar cipher which uses a single shift for all letters, the Vigenère cipher uses different shifts for each letter based on the repeating keyword. Each letter of the keyword determines the shift value for the corresponding position in the text. For example, with keyword "KEY", the first letter uses shift K(10), second uses E(4), third uses Y(24), fourth uses K(10) again, and so on. This makes it much more secure than simple substitution ciphers because the same letter can be encrypted differently depending on its position.

> **Cipher Type**: Substitution Cipher
> - Encrypts using a keyword
> - Key required (alphabetic keyword)

## Features

- **Encryption**: Encrypt plaintext using an alphabetic keyword
- **Decryption**: Decrypt ciphertext using the same keyword
- **Random Key Generation**: Automatically generate a secure random keyword
- **Key Validation**: Ensures the provided key contains only alphabetic characters, max 99 characters (can be changed in code: `#define MAX_KEY_LENGTH 100`)
- **Command Line Support**: Run with command line arguments for automated use
- **Interactive Mode**: User-friendly prompts for manual operation

## Compilation

```bash
gcc -o vigenere_cipher vigenere_cipher.c
```

## Usage

### Interactive Mode

Run the program without arguments:

```bash
./vigenere_cipher
```

Follow the prompts to:
1. Enter a keyword or press Enter to generate a random one
2. Choose operation (encrypt/decrypt)
3. Enter your text

### Command Line Mode

```bash
./vigenere_cipher <key> <operation>
```

**Parameters:**
- `<key>`: Alphabetic string (max 99 characters), or `rand`/`random`/`generate` for random key
- `<operation>`:
  - `e`, `encrypt`, or `encryption` for encryption
  - `d`, `decrypt`, or `decryption` for decryption

**Examples:**

```bash
# Encrypt with custom key
./vigenere_cipher KEY e

# Decrypt with custom key
./vigenere_cipher KEY d

# Generate random key and encrypt
./vigenere_cipher random e

# Interactive mode
./vigenere_cipher
```

## How It Works

### Encryption
Each letter in the plaintext is shifted by the corresponding letter in the keyword. The keyword repeats cyclically throughout the text. For example, with key "KEY":
- 1st letter: shift by K (10 positions)
- 2nd letter: shift by E (4 positions)
- 3rd letter: shift by Y (24 positions)
- 4th letter: shift by K (10 positions) again

### Decryption
Uses an inverse key where each character is calculated as `26 - original_shift` to reverse the encryption process.

### Key Requirements
- Must contain only alphabetic characters (a-z, A-Z)
- Maximum length: 99 characters (can be changed in code: `#define MAX_KEY_LENGTH 100`)
- Minimum length: 1 character
- Key repeats cyclically if shorter than the text

## Examples

**Encryption with key "KEY":**
- Key: `KEY`
- Plaintext: `Hello World`
- Ciphertext: `Rijvs Uyvjn`

**Decryption:**
- Key: `KEY`
- Ciphertext: `Rijvs Uyvjn`
- Plaintext: `Hello World`

**Random Key Generation:**
- Generated key: `cryptography` (example)
- Random length between 3 and 99 characters
- Contains only lowercase letters a-z (but the case doesn't matter)

## Security Notes

- Much more secure than Caesar cipher due to polyalphabetic nature
- Keyword length and randomness affect security strength
- Longer, more random keywords provide better security
- Historically known as "le chiffre indéchiffrable" (the indecipherable cipher)
- Vulnerable to frequency analysis if keyword is too short relative to text length

## Notes

- The program preserves case (uppercase/lowercase)
- Non-alphabetic characters (numbers, punctuation, spaces) remain unchanged
- Random key generation is seeded with current time for uniqueness
- Maximum input length is 255 characters _(can be adjusted in the code if needed)_
  - To change the maximum input length, modify the `MAX_INPUT_LENGTH` constant in the code (line 17: `#define MAX_INPUT_LENGTH 256`).
- Maximum key length is 99 characters _(can be adjusted in the code if needed)_
  - To change the maximum key length, modify the `MAX_KEY_LENGTH` constant in the code (line 18: `#define MAX_KEY_LENGTH 100`).

## License

MIT License - see [LICENSE](/LICENSE) file for details
