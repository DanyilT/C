# Atbash Cipher

A simple implementation of the Atbash cipher encryption and decryption algorithm in C.

## What is Atbash Cipher?

The Atbash cipher is a substitution cipher originally used for the Hebrew alphabet, but commonly applied to the Latin alphabet. It works by replacing each letter with its corresponding letter from the reverse alphabet. For example:
- A ↔ Z, B ↔ Y, C ↔ X, D ↔ W, E ↔ V, etc.

The cipher is symmetric, meaning the same process is used for both encryption and decryption.

## Features

- **Encryption/Decryption**: Atbash encryption and decryption are the same operation
- **Self-Inverse**: Applying Atbash twice returns the original text
- **Command Line Support**: Run with command line arguments for automated use
- **Interactive Mode**: User-friendly prompts for manual operation

## Compilation

```bash
gcc -o atbash_cipher atbash_cipher.c
```

## Usage

### Interactive Mode

Run the program without arguments:

```bash
./atbash_cipher
```

Follow the prompt to enter your text.

### Command Line Mode

```bash
./atbash_cipher "your text here"
```

**Examples:**

```bash
# Encrypt/decrypt text
./atbash_cipher "Hello World"

# Interactive mode
./atbash_cipher
```

## How It Works

The Atbash cipher maps each letter to its position from the opposite end of the alphabet:

| Original   | A     | B     | C     | D     | E     | F     | G     | H     | I     | J     | K     | L     | M     | N     | O     | P     | Q     | R     | S     | T     | U     | V     | W     | X     | Y     | Z     |
|------------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
| **Atbash** | **Z** | **Y** | **X** | **W** | **V** | **U** | **T** | **S** | **R** | **Q** | **P** | **O** | **N** | **M** | **L** | **K** | **J** | **I** | **H** | **G** | **F** | **E** | **D** | **C** | **B** | **A** |

## Examples

**Encryption:**
- Plaintext: `Hello World`
- Ciphertext: `Svool Dliow`

**Decryption (same as encryption):**
- Ciphertext: `Svool Dliow`
- Plaintext: `Hello World`

## Security Notes

- The Atbash cipher is cryptographically very weak
- It's a simple substitution cipher vulnerable to frequency analysis
- No key is required, making it unsuitable for secure communication

## Notes

- The program preserves case (uppercase/lowercase)
- Non-alphabetic characters (numbers, punctuation, spaces) remain unchanged
- Atbash encryption and decryption are identical operations
- Maximum input length is 255 characters _(can be adjusted in the code if needed)_
  - To change the maximum input length, modify the `MAX_INPUT_LENGTH` constant in the code (line 15: `#define MAX_INPUT_LENGTH 256`).

## Historical Context

- Originally used in Hebrew texts (6th-5th century BCE)
- Found in the Hebrew Bible (Old Testament)
- Name comes from Hebrew letters: Aleph-Taw-Beth-Shin (ATBŠ)
- One of the oldest known ciphers

## License

MIT License - see [LICENSE](/LICENSE) file for details
