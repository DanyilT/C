# XOR Cipher

A comprehensive implementation of the XOR cipher encryption and decryption algorithm in C, with multiple key types and brute force attack capability.

## What is XOR Cipher?

The XOR cipher is a simple encryption technique that uses the XOR (exclusive OR) bitwise operation to encrypt and decrypt data. Each byte of the plaintext is XORed with a key byte. The same operation is used for both encryption and decryption, making XOR ciphers symmetric. XOR ciphers can use single bytes, characters, strings, or byte sequences as keys.

## Features

- **Encryption**: Encrypt plaintext using specified key
- **Decryption**: Decrypt ciphertext using known key  
- **Brute Force**: Attempt to decrypt ciphertext by trying all possible single byte/char keys
- **Flexible Input**: Supports binary (0b), hexadecimal (0x), and decimal input formats for key and ciphertext
- **Multiple Key Types**: Supports byte (0-255), printable character (33-126), string, and byte sequence keys
- **Key Validation**: Ensures keys are within valid ranges and formats
- **Random Key Generation**: Generate random keys of any supported type
- **Command Line Support**: Run with command line arguments for automated use
- **Interactive Mode**: User-friendly prompts for manual operation

## Compilation

```bash
gcc -o xor_cipher xor_cipher.c
```

## Usage

### Interactive Mode

Run the program without arguments:

```bash
./xor_cipher
```

Follow the prompts to:
1. Enter or generate a key
2. Choose key type (byte/char/string/byte sequence)
   - Add type to the end of the key input, or it will automatically detect the type (for random key it defaults to byte)
   - `--byte/-b`, `--char/-c`, `--string/-s`, or `--byte_sequence/-bs` for specific types
3. Choose operation (encrypt/decrypt/brute force)
4. Enter your text

### Command Line Mode

```bash
./xor_cipher <key> [type] [operation]
```

**Parameters:**
- `<key>`: Key value or "rand"/"random"/"generate" for random key
- `[type]`: Key type (optional)
  - `--byte` or `-b` for byte key (0-255)
  - `--char` or `-c` for character key (33-126)
  - `--string` or `-s` for string key (2-99 printable ASCII characters)
  - `--byte_sequence` or `-bs` for byte sequence key (2-99 bytes, values 0-255)
- `[operation]`: Operation type (optional)
  - `e`, `encrypt`, or `encryption` for encryption
  - `d`, `decrypt`, or `decryption` for decryption
  - `bf` or `brute-force` for brute force decryption

_Note: The <key> must be the first argument, but the type and operation can be in any order or omitted. If no type is specified, the program will attempt to auto-detect the key type based on the input format._

**Examples:**

```bash
# Encrypt with byte key 65
./xor_cipher 65 -b e
# Can automatically detect this key type, so the following is also valid:
./xor_cipher 65 e

# Decrypt with character key 'A'
./xor_cipher A -c d
# Can automatically detect this key type, so the following is also valid:
./xor_cipher A d

# Encrypt with string key "keyword"
./xor_cipher keyword -s e
# Can automatically detect this key type, so the following is also valid:
./xor_cipher keyword e

# Encrypt with byte sequence "0xFF,0x00,0x41"
./xor_cipher "0xFF,0x00,0x41" -bs e
# Can automatically detect this key type, so the following is also valid:
./xor_cipher "0xFF,0x00,0x41" e

# Generate random string key and encrypt
./xor_cipher rand -s e
# If no type is specified, it defaults to byte key
./xor_cipher rand e

# Brute force decrypt
./xor_cipher 0 bf
```

## How it Works

### Encryption
Each byte of the plaintext is XORed with the corresponding byte of the key. If the key is shorter than the plaintext, it repeats until the entire plaintext is processed.

### Decryption
The decryption process is identical to encryption. The ciphertext is XORed with the same key to retrieve the original plaintext. (Input for decryption must be a comma/space-separated byte sequence in decimal, hexadecimal, or binary format.)

### Brute Force

#### Single Key Brute Force
1. **Byte keys (0-255)**: Tries all possible byte values
2. **Char keys (32-126)**: Tries only printable ASCII characters

#### Display Options
- **Printable only**: Shows only results containing printable characters
- **All results**: Shows both printable and non-printable results

## Key Types and Formats

### Byte Keys
- **Range**: 0-255
- **Format**: Decimal (255), hexadecimal (0xFF), or binary (0b11111111)
- **Example**: `65`, `0x41`, `0b01000001`

### Character Keys
- **Range**: Printable ASCII (33-126)
- **Format**: Single character (anything you can type on a keyboard)
- **Example**: `A`, `@`, `7`

### String Keys
- **Range**: 2-99 characters, printable ASCII only
- **Format**: Text string (array of anything you can type on a keyboard)
- **Example**: `password`, `secret`, `keyword`

### Byte Sequence Keys
- **Range**: 2-99 bytes, values 0-255
- **Format**: Comma/space-separated values in decimal, hex, or binary
- **Examples**:
  - `65,255,0,128`, `65 255 0 128`
  - `0x41,0xFF,0x00,0x80`, `0x41 0xFF 0x00 0x80`, `0x41FF0080`
  - `0b01000001,0b11111111,0b00000000,0b10000000`, `0b01000001 0b11111111 0b00000000 0b10000000`, `0b01000001111111110000000010000000`

## Input/Output Formats

### Text Input
- **Encryption**: Plain text string
- **Decryption**: Comma/space-separated byte values

### Output Formats
- **Encryption**: Byte sequence in decimal, hexadecimal, and binary
- **Decryption**: Plain text (if printable) and byte sequence
- **Brute Force**: Key information with decrypted result

## Examples

**Encryption with byte key:**
- Plaintext: `Hello`
- Key: `41` (0x29)
- Output: `(decimal: 97,76,69,69,70) (hex: 0x61,0x4C,0x45,0x45,0x46) (binary: 0b01100001,0b01001100,0b01000101,0b01000101,0b01000110)`

**Decryption with byte key:**
- Ciphertext: `97,76,69,69,70`
- Key: `42`
- Output: `Hello`

**Encryption with string key:**
- Plaintext: `I love u`
- Key: `KEYWORD`
- Output: `(decimal: 2,101,53,56,57,55,100,62) (hex: 0x02,0x65,0x35,0x38,0x39,0x37,0x64,0x3E) (binary: 0b00000010,0b01100101,0b00110101,0b00111000,0b00111001,0b00110111,0b01100100,0b00111110)`

**Brute Force:**
- Ciphertext: `97,76,69,69,70`
- Output: All possible decryptions with their keys, highlighting printable results

## Security Notes

- XOR cipher with single byte/char keys is cryptographically weak
- String keys provide better security but are still vulnerable to frequency analysis
- Brute force attacks are feasible for short keys

## Performance Considerations

- **Single key brute force**: Fast (256 attempts maximum)
- **String brute force**: Exponentially slower with longer keys
  - Length 3: ~857,375 combinations
  - Length 4: ~81,450,625 combinations
  - Length 5+: Use with caution

## Notes

- The program preserves case (uppercase/lowercase)
- Random key generation is seeded with the current time for uniqueness
- Non-printable output also displayed as byte sequences
- XOR operation is symmetric: encryption and decryption use the same process
- Binary and hexadecimal inputs support both continuous and separated formats
- Maximum input length is 255 characters _(adjustable via MAX_INPUT_LENGTH)_
  - To change the maximum input length, modify the `MAX_INPUT_LENGTH` constant in the code (line 17: `#define MAX_INPUT_LENGTH 256`).
- Maximum key length is 99 characters _(adjustable via MAX_KEY_LENGTH)_
  - To change the maximum key length, modify the `MAX_KEY_LENGTH` constant in the code (line 18: `#define MAX_KEY_LENGTH 100`).

## License

MIT License - see [LICENSE](/LICENSE) file for details
