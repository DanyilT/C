# ROT13 Cipher

A simple implementation of the ROT13 cipher in C, built using the Caesar cipher algorithm with a fixed shift of 13.

## What is ROT13 Cipher?

ROT13 ("rotate by 13 places") is a simple letter substitution cipher that replaces each letter with the letter 13 positions after it in the alphabet. ROT13 is a special case of the Caesar cipher with a fixed shift of 13. Since there are 26 letters in the English alphabet, applying ROT13 twice returns the original text, making ROT13 its own inverse.

## Features

- **Encryption/Decryption**: ROT13 encryption and decryption are the same operation
- **Self-Inverse**: Applying ROT13 twice returns the original text
- **Command Line Support**: Run with command line arguments for automated use
- **Interactive Mode**: User-friendly prompts for manual operation

## Compilation

```bash
gcc -o rot13_cipher rot13_cipher.c
```

## Usage

### Interactive Mode

Run the program without arguments:

```bash
./rot13_cipher
```

Follow the prompt to enter your text.

### Command Line Mode

```bash
./rot13_cipher "your text here"
```

**Examples:**

```bash
# Encrypt/decrypt text
./rot13_cipher "Hello World"

# Interactive mode
./rot13_cipher
```

## How It Works

ROT13 shifts each letter by exactly 13 positions in the alphabet:
- A becomes N, B becomes O, C becomes P, etc.
- N becomes A, O becomes B, P becomes C, etc.

Since the English alphabet has 26 letters, shifting by 13 places twice (13 + 13 = 26) brings you back to the original letter.

## Examples

**ROT13 Applied:**
- Original: `Hello World`
- ROT13: `Uryyb Jbeyq`

**ROT13 Applied Again (returns original):**
- ROT13: `Uryyb Jbeyq`
- Original: `Hello World`

## Notes

- The program preserves case (uppercase/lowercase)
- Non-alphabetic characters (numbers, punctuation, spaces) remain unchanged
- ROT13 encryption and decryption are identical operations
- Maximum input length is 255 characters _(can be adjusted in the code if needed)_
  - To change the maximum input length, modify the `MAX_INPUT_LENGTH` constant in the code (line 16: `#define MAX_INPUT_LENGTH 256`).

## Relationship to Caesar Cipher

ROT13 is essentially a Caesar cipher with a fixed key of 13. This implementation reuses the Caesar cipher encryption function with `ROT13_KEY` set to 13.

## License

MIT License - see [LICENSE](/LICENSE) file for details
