#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

// Function declarations for Simplified AES operations

// Substitution operations
unsigned char subnib(unsigned char);              // 8-bit SubBytes
unsigned short int subnib1(unsigned short int, unsigned char const box[]); // 16-bit SubBytes

// Row shifting operations  
unsigned char roundnib(unsigned char);            // 8-bit ShiftRows
unsigned short int roundnib1(unsigned short int); // 16-bit ShiftRows

// Key operations
unsigned short int ark(unsigned short int, unsigned short int); // AddRoundKey (XOR)

// Column mixing operations
unsigned short int mixcol(unsigned short int, unsigned char const m[][2]); // MixColumns
unsigned short int bitmul(unsigned short int, unsigned short int);        // GF(2^4) multiplication
unsigned short int gmul(unsigned short int, unsigned short int);          // Polynomial multiplication

// Round functions
void round0();   // Initial round (AddRoundKey only)
void round1();   // Full round (SubBytes, ShiftRows, MixColumns, AddRoundKey) 
void round2();   // Final round (SubBytes, ShiftRows, AddRoundKey)

// Decryption round functions
void dround0();  // Initial decryption round
void dround1();  // Full decryption round
void dround2();  // Final decryption round

// Key generation
void roundkey(); // Generate round keys from expanded key
void keygen();   // Expand master key into round keys

// Utility
void line();     // Print separator line

// S-AES Constants

// 4-bit S-box for SubBytes transformation
unsigned char const sbox[] = {0x09,0x04,0x0a,0x0b,0x0d,0x01,0x08,0x05,
                              0x06,0x02,0x00,0x03,0x0c,0x0e,0x0f,0x07};

// Inverse S-box for InvSubBytes transformation                              
unsigned char const ibox[] = {0x0a,0x05,0x09,0x0b,0x01,0x07,0x08,0x0f,
                              0x06,0x00,0x02,0x03,0x0c,0x04,0x0d,0x0e};

// Round constants for key expansion
unsigned char const rcon[] = {0x80,0x00,0x30};

// MixColumns matrix for encryption
unsigned char const mix[2][2] = {{1,4},{4,1}};

// InvMixColumns matrix for decryption
unsigned char const imix[2][2] = {{9,2},{2,9}};

// Global variables (Note: In production code, these should be passed as parameters)
unsigned short int key = 0x4af5;           // Master key (16-bit)
unsigned short int ciph, msg, dmsg;        // Cipher text, message, decrypted message
unsigned short int skey[3] = {0,0,0};      // Round keys
unsigned char wkey[6] = {0,0,0,0,0,0};     // Expanded key bytes

#endif // AES_H_INCLUDED
