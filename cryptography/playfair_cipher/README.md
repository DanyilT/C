# Playfair Cipher

A comprehensive implementation of the Playfair cipher encryption and decryption algorithm in C, with random key generation capability.

## What is Playfair Cipher?

The Playfair cipher is a digraph substitution cipher, meaning it encrypts pairs of letters (digraphs) rather than individual letters. Invented by Charles Wheatstone in 1854 but popularized by Lord Playfair, it uses a 5×5 grid of letters as the key. The cipher was notably used during the Boer War and World War I. Unlike simple substitution ciphers, Playfair operates on letter pairs, making it significantly more secure against frequency analysis.

## Features

- **Encryption**: Encrypt plaintext using a keyword-based 5×5 grid
- **Decryption**: Decrypt ciphertext using the same keyword
- **Random Key Generation**: Automatically generate secure random keywords
- **Key Validation**: Ensures keywords contain only alphabetic characters
- **Automatic Text Preprocessing**: Handles duplicate letters and odd-length text
- **Command Line Support**: Run with command line arguments for automated use
- **Interactive Mode**: User-friendly prompts for manual operation

## Compilation

```bash
gcc -o playfair_cipher playfair_cipher.c
```

## Usage

### Interactive Mode

Run the program without arguments:

```bash
./playfair_cipher
```

Follow the prompts to:
1. Enter a keyword or press Enter to generate a random one
2. Choose operation (encrypt/decrypt)
3. Enter your text

### Command Line Mode

```bash
./playfair_cipher <key> <operation>
```

**Parameters:**
- `<key>`: Alphabetic string (max 99 characters), or `rand`/`random`/`generate` for random key
- `<operation>`:
  - `e`, `encrypt`, or `encryption` for encryption
  - `d`, `decrypt`, or `decryption` for decryption

**Examples:**

```bash
# Encrypt with custom key
./playfair_cipher MONARCHY e

# Decrypt with custom key
./playfair_cipher MONARCHY d

# Generate random key and encrypt
./playfair_cipher random e

# Interactive mode
./playfair_cipher
```

## How It Works

### Key Grid Generation
1. Remove duplicate letters from the keyword
2. Fill a 5×5 grid with the keyword letters first, then remaining alphabet letters
3. Combine I and J into a single cell (I/J are treated as the same letter)

### Text Preprocessing
- Convert to uppercase
- Replace J with I
- Insert 'X' between duplicate letters in pairs
- Add 'X' at the end if text length is odd

### Encryption Rules
For each pair of letters:
1. **Same row**: Replace each letter with the one to its right (wrapping around)
2. **Same column**: Replace each letter with the one below it (wrapping around)
3. **Rectangle**: Replace each letter with the one in the same row but in the other letter's column

### Decryption Rules
Reverse of encryption:
1. **Same row**: Replace each letter with the one to its left (wrapping around)
2. **Same column**: Replace each letter with the one above it (wrapping around)
3. **Rectangle**: Same as encryption (swap columns)

## Example

**Key**: `MONARCHY`

**Generated 5×5 Grid**:
```
M O N A R
C H Y B D
E F G I/J K
L P Q S T
U V W X Z
```

**Encryption**:
- Plaintext: `HELLO WORLD`
- Preprocessed: `HELXLOWORLDX`
- Pairs: `HE LX LO WO RL DX`
- Ciphertext: `CHPXKQTQSKDX`

**Decryption**:
- Ciphertext: `CHPXKQTQSKDX`
- Pairs: `CH PX KQ TQ SK DX`
- Plaintext: `HELXLOWORLDX`

## Key Requirements

- Must contain only alphabetic characters (a-z, A-Z)
- Maximum length: 99 characters _(adjustable via MAX_KEY_LENGTH)_
- Minimum length: 1 character
- Duplicate letters in the keyword are automatically removed
- Case doesn't matter (converted to uppercase)

## Security Notes

- Much more secure than monoalphabetic ciphers due to digraph encryption
- Resistant to simple frequency analysis of individual letters
- Vulnerable to bigram frequency analysis with sufficient ciphertext
- Key length and randomness affect security strength
- Historically considered very secure for field use

## Security Notes and Brute Force Attacks

- **Frequency Analysis**: The Playfair cipher is vulnerable to frequency analysis of digrams (letter pairs)
- **Key Space**: With a 25-letter alphabet, there are 25! ≈ 1.5 × 10²⁵ possible keys, making brute force computationally infeasible
- **Cryptanalysis Methods**:
  - **Frequency analysis of bigrams**: Common English digrams like "TH", "HE", "IN" can reveal patterns
  - **Known plaintext attacks**: If part of the plaintext is known, the key can often be recovered
  - **Hill climbing algorithms**: Can optimize key guesses based on text statistics
- **Historical Breaking**: Successfully cryptanalyzed during WWI and WWII using manual techniques
- **Modern Security**: Considered cryptographically weak by today's standards
- **Recommended Attack Vector**: Frequency analysis of digrams rather than brute force due to the large key space

### Brute Force Considerations
- **Single character brute force**: Not applicable (uses 5×5 grid key)
- **Full key brute force**: Computationally infeasible (25! possible permutations)
- **Practical attacks**: Focus on statistical analysis and known plaintext rather than exhaustive key search
- **Key recovery**: Often possible with sufficient ciphertext (typically 100+ characters) using digram frequency analysis

## Notes

- I and J are treated as the same letter (standard Playfair convention)
- Non-alphabetic characters are removed during preprocessing
- X is used as a filler character for duplicate pairs and odd-length text
- The output shows both the processed text and the final result
- Random key generation is seeded with current time for uniqueness
- Maximum input length is 255 characters _(adjustable via MAX_INPUT_LENGTH)_
  - To change the maximum input length, modify the `MAX_INPUT_LENGTH` constant in the code (line 17: `#define MAX_INPUT_LENGTH 256`).
- Maximum key length is 99 characters _(adjustable via MAX_KEY_LENGTH)_
  - To change the maximum key length, modify the `MAX_KEY_LENGTH` constant in the code (line 18: `#define MAX_KEY_LENGTH 100`).

## Historical Context

- Invented by Charles Wheatstone in 1854
- Popularized by Lord Playfair, hence the name
- Used extensively in World War I by British forces
- First literal digraph substitution cipher to be used practically
- Considered unbreakable for decades after its invention

## License

MIT License - see [LICENSE](/LICENSE) file for details
