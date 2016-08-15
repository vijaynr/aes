#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED
//function declarations
    unsigned char subnib(unsigned char );
    unsigned short int subnib1(unsigned short int ,unsigned char const box[]);
    unsigned char roundnib(unsigned char );
    unsigned short int roundnib1(unsigned short int );
    unsigned short int ark(unsigned short int ,unsigned short int );
    unsigned short int mixcol(unsigned short int ,unsigned char const m[][2]);
    unsigned short int bitmul(unsigned short int ,unsigned short int );
    unsigned short int gmul(unsigned short int ,unsigned short int );
    void round0();
    void round1();
    void round2();
    void dround0();
    void dround1();
    void dround2();
    void droundkey();
    void keygen();
    void line();
//constant variables
    unsigned char const sbox[]={0x09,0x04,0x0a,0x0b,0x0d,0x01,0x08,0x05,0x06,0x02,0x00,0x03,0x0c,0x0e,0x0f,0x07};
    unsigned char const ibox[]={0x0a,0x05,0x09,0x0b,0x01,0x07,0x08,0x0f,0x06,0x00,0x02,0x03,0x0c,0x04,0x0d,0x0e};
    unsigned char const rcon[]={0x80,0x00,0x30};
    unsigned char const mix[2][2]={{1,4},{4,1}};
    unsigned char const imix[2][2]={{9,2},{2,9}};
    unsigned short int key=0x4af5;
    unsigned short int ciph,msg,dmsg,skey[3]={0,0,0};
    unsigned char wkey[6]={0,0,0,0,0,0};
#endif // AES_H_INCLUDED
