# Rail Fence Cipher

A simple implementation of the Rail Fence cipher encryption and decryption algorithm in C, with random key generation capability.

## What is Rail Fence Cipher?

The Rail Fence cipher is a transposition cipher that writes the plaintext in a zigzag pattern across multiple "rails" (rows), then reads off the ciphertext row by row. The number of rails serves as the key. For example, with 3 rails, the text "HELLO WORLD" would be arranged like:

```
H   O   R  
 E L   O L 
  L   W   D
```

Reading row by row gives: `HOREL OLLWD`

## Features

- **Encryption**: Encrypt plaintext using a specified number of rails
- **Decryption**: Decrypt ciphertext using the same number of rails
- **Random Key Generation**: Automatically generate a random rail count
- **Key Validation**: Ensures rail count is within valid range (2-99)
- **Command Line Support**: Run with command line arguments for automated use
- **Interactive Mode**: User-friendly prompts for manual operation

## Compilation

```bash
gcc -o rail_fence_cipher rail_fence_cipher.c
```

## Usage

### Interactive Mode

Run the program without arguments:

```bash
./rail_fence_cipher
```

Follow the prompts to:
1. Enter number of rails or press Enter to generate a random one
2. Choose operation (encrypt/decrypt/brute-force)
3. Enter your text

### Command Line Mode

```bash
./rail_fence_cipher <rails> <operation> [visualize]
```

**Parameters:**
- `<rails>`(`key`): Number of rails (2-99), or `rand`/`random`/`generate` for random key
- `<operation>`:
  - `e`, `encrypt`, or `encryption` for encryption
  - `d`, `decrypt`, or `decryption` for decryption
  - `bf`, `brute-force` for brute force decryption
- `[visualize]`: `v`/`visualize` to visualize the rail fence cipher

**Examples:**

```bash
# Encrypt with 3 rails
./rail_fence_cipher 3 e

# Visualize
./rail_fence_cipher 3 e v
./rail_fence_cipher 3 v e

# Decrypt with 4 rails
./rail_fence_cipher 4 d

# Visualize
./rail_fence_cipher 4 d v
./rail_fence_cipher 4 v d

# Generate random rail count and encrypt
./rail_fence_cipher random e

# Visualize
./rail_fence_cipher random e visualize
./rail_fence_cipher random visualize e

# Brute force decrypt, can't be visualized (key not needed for brute force, but must be specified, because i don't want to fix this...)
./rail_fence_cipher 2 bf

# Interactive mode
./rail_fence_cipher
```

## How It Works

### Encryption
1. Arrange the plaintext in a zigzag pattern across the specified number of rails
2. Read off the characters row by row to form the ciphertext

### Decryption
1. Calculate the length of each rail based on the ciphertext length
2. Fill the rails with the ciphertext characters in the correct positions
3. Read the characters following the zigzag pattern to recover the plaintext

### Key Requirements
- Must be an integer between 2 and 99 (`MIN_RAILS`, `MAX_RAILS`)
- Cannot be 1 (would result in no encryption)
- Larger rail counts provide more scrambling but require longer texts to be effective

## Examples

**Encryption with 3 rails:**
- Rails: `3`
- Plaintext: `HELLO WORLD`
- Zigzag pattern:
  ```
  H...O...R..
  .E.L. .O.L.
  ..L...W...D
  ```
- Ciphertext: `HOREL OLLWD`

**Encryption with 4 rails:**
- Rails: `4`
- Plaintext: `I AM DANY AND I LOVE U`
- Zigzag pattern:
  ```
  I.....A.....D.....V...
  . ...D.N...N. ...O.E..
  ..A. ...Y.A...I.L... .
  ...M..... ..... .....U
  ```
- Ciphertext: `IADV DNN OEA YAIL M  U`

**Decryption:**
- Rails: `3`
- Ciphertext: `HOREL OLLWD`
- Recovered plaintext: `HELLO WORLD`

**Brute Force:**
- Ciphertext: `HOREL OLLWD`
- Output: All possible decryptions with their corresponding keys for text's length

## Security Notes

- The Rail Fence cipher is cryptographically weak
- Vulnerable to frequency analysis with sufficient ciphertext
- Pattern of rail arrangement can be detected through cryptanalysis
- Security increases with more rails, but remains fundamentally weak
- Suitable for educational purposes and simple obfuscation only

## Notes

- The program preserves all characters including spaces and punctuation
- Case is preserved during encryption/decryption
- Random rail generation creates keys between 2 and 10 for practical use
- Maximum input length is 255 characters _(adjustable via MAX_INPUT_LENGTH)_
  - To change the maximum input length, modify the `MAX_INPUT_LENGTH` constant in the code (line 17: `#define MAX_INPUT_LENGTH 256`).
- Maximum rail count is 99 _(adjustable via MAX_RAILS)_
  - To change the maximum rail count, modify the `MAX_RAILS` constant in the code (line 19: `#define MAX_RAILS 100`).

## Historical Context

- One of the oldest known ciphers, dating back to ancient times
- Used by soldiers to send messages by wrapping text around a cylindrical rod
- Simple transposition cipher that rearranges rather than substitutes characters
- Also known as "Zigzag Cipher" due to its characteristic pattern

## License

MIT License - see [LICENSE](/LICENSE) file for details
