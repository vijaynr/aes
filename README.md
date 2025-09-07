# Simplified AES Implementation in C

A simplified version of the Advanced Encryption Standard (AES) algorithm implemented in C. This is an educational implementation that demonstrates the core concepts of AES encryption and decryption using 16-bit blocks and keys.

## Features

- **Simplified AES (S-AES)**: Operates on 16-bit plaintext blocks with 16-bit keys
- **Complete encryption/decryption cycle**: Includes all main AES operations:
  - SubBytes/InvSubBytes transformation
  - ShiftRows/InvShiftRows transformation  
  - MixColumns/InvMixColumns transformation
  - AddRoundKey operation
- **Key schedule generation**: Automatic round key generation from master key
- **Interactive interface**: Command-line interface for testing encryption/decryption

## Algorithm Details

This simplified AES implementation uses:
- **Block size**: 16 bits (4 nibbles)
- **Key size**: 16 bits 
- **Rounds**: 2 full rounds + initial round
- **S-box**: 4-bit substitution box
- **Default key**: 0x4AF5 (can be modified in source)

## Building

### Prerequisites
- GCC compiler
- Standard C library with math functions

### Compilation
```bash
# Using the provided Makefile (recommended)
make

# Or compile manually
gcc -Wall -Wextra -std=c99 -o aes enc.c -lm
```

### Available Make Targets
- `make` or `make all` - Build the program
- `make clean` - Remove build artifacts
- `make test` - Run basic functionality tests
- `make install` - Install to /usr/local/bin
- `make help` - Show all available targets

## Usage

### Interactive Mode
```bash
./aes
Type Your Message    : 1234
----------------------------------------------------------------------------------------
Plain text           : 1234
Encoded Cipher Text  : F4B1
----------------------------------------------------------------------------------------

Cipher Text          : F4B1
Decoded Plain Text   : 1234
----------------------------------------------------------------------------------------
```

### Input Format
- Enter hexadecimal values (e.g., 1234, ABCD, FFFF)
- Input range: 0000 to FFFF (16-bit values)

## Example Sessions

```bash
# Test with different inputs
echo "1234" | ./aes  # Encrypts 0x1234
echo "ABCD" | ./aes  # Encrypts 0xABCD
echo "0000" | ./aes  # Encrypts 0x0000
echo "FFFF" | ./aes  # Encrypts 0xFFFF
```

## Code Structure

- `aes.h` - Header file with function declarations and constants
- `aes.c` - Core AES algorithm implementation
- `enc.c` - Main program and user interface
- `Makefile` - Build configuration

### Key Functions
- `keygen()` - Generate round keys from master key
- `subnib()` / `subnib1()` - SubBytes transformation
- `roundnib()` / `roundnib1()` - ShiftRows transformation
- `mixcol()` - MixColumns transformation
- `ark()` - AddRoundKey operation
- `round0()`, `round1()`, `round2()` - Encryption rounds
- `dround0()`, `dround1()`, `dround2()` - Decryption rounds

## Educational Purpose

This implementation is designed for educational purposes to understand:
- How symmetric encryption algorithms work
- The structure of the AES algorithm
- Key scheduling and round operations
- Finite field arithmetic (GF(2^4) operations)

**Note**: This is a simplified version for learning. For production use, implement full AES-128/192/256.

## Contributing

Feel free to submit issues and enhancement requests!

## License

This project is open source. See the repository for license details.
