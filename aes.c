#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "aes.h"

//print line
void line(){
    printf("----------------------------------------------------------------------------------------\n");
}
//key generation
void keygen(){
    wkey[0]=(0xff00 & key)>>8;
    wkey[1]=(0x00ff & key);
    int i;
    for(i=2;i<5;i=i+2){
        wkey[i]=wkey[i-2]^rcon[i-2]^subnib(roundnib(wkey[i-1]));
        wkey[i+1]=wkey[i]^wkey[i-1];
    }
}
//substitute nibbles 8-bit
unsigned char subnib(unsigned char sub){
    unsigned char temp1,temp2;
    temp1=(sub & 0xf0)>>4;
    temp2=(sub & 0x0f);
    return (sbox[temp1]<<4 | sbox[temp2]);
}
//shift rows of nibbles 8-bit
unsigned char roundnib(unsigned char rot){
    return ((rot & 0xf0)>>4 | (rot & 0x0f)<<4);
}
//generating roundkeys
void roundkey(){
    skey[0]=(wkey[0]<<8 | wkey[1]);
    skey[1]=(wkey[2]<<8 | wkey[3]);
    skey[2]=(wkey[4]<<8 | wkey[5]);
}
//substitute nibbles 16-bit
unsigned short int subnib1(unsigned short int c,unsigned char const box[]){
    unsigned short int t1,t2,t3,t4;
    t1=(0xf000 & c)>>12;
    t2=(0x0f00 & c)>>8;
    t3=(0x00f0 & c)>>4;
    t4=(0x000f & c);
    return ((box[t1]<<12) | (box[t2]<<8) | (box[t3]<<4) | (box[t4]));
}
//shift rows nibbles 16-bit
unsigned short int roundnib1(unsigned short int c){
    return ((c & 0x0f00)>>8 | (c & 0x000f)<<8 | (c & 0xf0f0));
}
//add round key
unsigned short int ark(unsigned short int m,unsigned short int k){
    return (m^k);
}
//round0
void round0(){
    ciph=ark(msg,skey[0]);
}

void dround0(){
    dmsg=ark(ciph,skey[2]);
    //printf("d0");
}
//polynomial multiplication
unsigned int short gmul(unsigned int short m1,unsigned int short m2){
    unsigned short int res=0x0;
    unsigned short int j=0;
    while(m1){
        res=((m1&0x0001)*(m2<<j))^res;
        m1=m1>>1;
        j=j+1;
    }
}
//bitwise polynomial modulo 19 multiplication
unsigned short int bitmul(unsigned short int b1,unsigned short int b2){
    unsigned short int mul=gmul(b1,b2);
   // printf("%x  ",mul);
    unsigned short int shift=0;
    while(!(mul<=15)){
        shift=ceil(log(mul+1)/log(2))-ceil(log(0x13)/log(2));
        mul=mul^(0x13<<shift);
        //printf("%d",mul);
    }
    return mul;
}
//mix columns [1,4 ; 4,1] encoding
unsigned short int mixcol(unsigned short int c,unsigned const char m[][2]){
    unsigned short int s[4],st[4];
    s[0]=((0xf000 & c)>>12)&0x000f;
    s[1]=(0x0f00 & c)>>8;
    s[2]=(0x00f0 & c)>>4;
    s[3]=(0x000f & c);
    //printf("%X %X %X %X",s[0],s[1],s[2],s[3]);
    st[0]=bitmul(m[0][0],s[0])^bitmul(m[0][1],s[1]);
    //printf("%x",st[0]);
    st[1]=bitmul(m[0][1],s[0])^bitmul(m[0][0],s[1]);
    //printf("%x",st[1]);
    st[2]=bitmul(m[1][1],s[2])^bitmul(m[1][0],s[3]);
    //printf("%x",st[2]);
    st[3]=bitmul(m[1][0],s[2])^bitmul(m[1][1],s[3]);
    //printf("%x",st[3]);
    return ((st[0]<<12) | (st[1]<<8) | (st[2]<<4) | (st[3]));
}
//round1
void round1(){
    ciph=subnib1(ciph,sbox);
    ciph=roundnib1(ciph);
    ciph=mixcol(ciph,mix);
    ciph=ark(ciph,skey[1]);
}

void dround1(){
    dmsg=subnib1(dmsg,ibox);
    //printf("d10");
    dmsg=roundnib1(dmsg);
    //printf("d11");
    dmsg=ark(dmsg,skey[1]);
    //printf("%X",dmsg);
    dmsg=mixcol(dmsg,imix);
    //printf("%X        ",dmsg);

}
//final round
void round2(){
    //printf("d20");
    ciph=subnib1(ciph,sbox);
    //printf("d21");
    ciph=roundnib1(ciph);
    //printf("d23");
    ciph=ark(ciph,skey[2]);
    //printf("d24");
}

void dround2(){
    dmsg=subnib1(dmsg,ibox);
    dmsg=roundnib1(dmsg);
    dmsg=ark(dmsg,skey[0]);
}
