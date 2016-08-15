#include "aes.c"
void encode();
void decode();
int main(){
	//main code
	printf("Type Your Message\t:");
	scanf("%x",&msg);
	keygen();
	roundkey();
	encode();
	line();
    printf("Plain text\t\t:%X\nEncoded Cipher Text\t:%X\n",msg,ciph);
	line();
	printf("\n\n");
	decode();
	line();
    printf("Cipher Text\t\t:%X\nDecoded Plain Text\t:%X\n",ciph,dmsg);
	line();
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
