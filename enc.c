#include "aes.c"

void encode();
void decode();

int main(){
    printf("=== Simplified AES Encryption/Decryption Demo ===\n");
    printf("Enter a 16-bit hexadecimal value (0000-FFFF)\n");
    printf("Type Your Message\t:");
    
    // Input validation
    if (scanf("%hx", &msg) != 1) {
        printf("Error: Invalid input. Please enter a hexadecimal value.\n");
        return 1;
    }
    
    keygen();
    roundkey();
    encode();
    
    line();
    printf("Plain text\t\t:%04X\nEncoded Cipher Text\t:%04X\n", msg, ciph);
    line();
    printf("\n");
    
    decode();
    
    line();
    printf("Cipher Text\t\t:%04X\nDecoded Plain Text\t:%04X\n", ciph, dmsg);
    line();
    
    // Verify decryption worked correctly
    if (msg == dmsg) {
        printf("✓ Encryption/Decryption successful!\n");
    } else {
        printf("✗ Error: Decryption failed! Original: %04X, Decrypted: %04X\n", msg, dmsg);
        return 1;
    }
    
    return 0;
}

void encode(){
    round0();
    round1();
    round2();
}

void decode(){
    dround0();
    dround1();
    dround2();
}
