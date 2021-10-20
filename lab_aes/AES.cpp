#include <iostream>
#include <string>
using namespace std;
int AES_ALLROUND = 10;
int AES_NOWROUND = 0;

int mul2(int x)
{
    x <<= 1;
    if(x >= 0x100)
    {
        x %= 0x100;
        x ^= 0x1b;
    }
    return x;
}
int mul3(int x)
{
    int y = x;
    x <<= 1;
    x ^= y;
    if(x >= 0x100)
    {
        x %= 0x100;
        x ^= 0x1b;
    }

    return x;
}
int sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
    };

int invsbox[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};
inline void prt(int a[16])
{
    for(int index = 0 ; index < 16 ; index++)
    {
        cout.width(2);
        cout.fill('0');
        cout << hex  << uppercase << a[index] << " ";
        if((index + 1) % 4 == 0)
        cout << endl;
    }
    cout << endl;
}
inline void addroundkey(int s[16], int k[16])
{
    for(int index = 0 ; index < 16 ; index++)
    s[index] ^= k[index];
}
inline void subbyte(int s[16])
{
    for(int index = 0 ; index < 16 ; index++)
    s[index] = sbox[s[index]];
}
inline void shiftrows(int s[16])
{
    int bak[2];
    
    bak[0] = s[4 + 0];              // 2번째줄 1 Shift
    for(int i = 0 ; i < 3 ; i++)
    s[4 + i] = s[5 + i];
    s[7] = bak[0];

    for(int i = 0 ; i < 4 ; i++)    // 3번째줄 2 Shift 최적화
    {   if(i < 2)
        {
            bak[i] = s[8 + i];
            s[8 + i] = s[10 + i];
        }
        else    s[8 + i] = bak[i - 2];
    }
    
    bak[0] = s[12 + 3];            // 4번째줄 3 shift 최적화
    for(int i = 0 ; i < 4 ; i++)
    s[15 - i] = s[14 - i];
    s[12] = bak[0];
    

    /*
    bak[0] = s[8 + 0];             // 3번째줄 2 shift
    bak[1] = s[8 + 1];
    s[8 + 0] = s[8 + 2];
    s[8 + 1] = s[8 + 3];
    s[8 + 2] = bak[0];
    s[8 + 3] = bak[1];

    bak[0] = s[12 + 3];            // 4번째줄 3 shift
    s[12 + 3] = s[12 + 2];
    s[12 + 2] = s[12 + 1];
    s[12 + 1] = s[12 + 0];
    s[12 + 0] = bak[0];
    */
}
inline void mixcolumns(int s[16])
{
    int stay[16];
    for(int index = 0 ; index < 16 ; index++)
    stay[index] = s[index];
    
    for(int r = 0 ; r < 4 ; r++)
    {
        s[r] = mul2(stay[r])^mul3(stay[4 + r])^stay[8 + r]^stay[12 + r];
        s[r + 4] =  stay[r]^mul2(stay[4 + r])^mul3(stay[8 + r])^stay[12 + r];
        s[r + 8] =  stay[r]^stay[4 + r]^mul2(stay[8 + r])^mul3(stay[12 + r]);
        s[r + 12] =  mul3(stay[r])^stay[4 + r]^stay[8 + r]^mul2(stay[12 + r]);
    }

    /* row W1 Process
    s[0] = mul2(stay[0])^mul3(stay[4])^stay[8]^stay[12];
    s[1] = mul2(stay[0 + 1])^mul3(stay[4 + 1])^stay[8 + 1]^stay[12 + 1];
    s[2] = mul2(stay[0 + 2])^mul3(stay[4 + 2])^stay[8 + 2]^s[12 + 2];
    s[3] = mul2(s[0 + 3])^mul3(s[4 + 3])^s[8 + 3]^s[12 + 3];
    */
}
inline void keyexpansion(int k[16])
{
    int rcon[14] = {
    0x01, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x40, 0x80, 0x1B, 0x36,
    0x6C, 0xD8, 0xA8, 0xAB
    };
    int w[4];
    int orikey[16];
    for(int i = 0 ; i < 16 ; i++)
    orikey[i] = k[i];

    // w에 RotWord 저장
    for(int i = 2 ; i < 5 ; i++)
    w[i - 2] = k[4 * i - 1];
    w[3] = k[3];
    
    // w에 SubWord 저장
    for(int s = 0 ; s < 4 ; s++)
    w[s] = sbox[w[s]];

    // W[i-4], W[i] XOR
    for(int index = 0 ; index < 4 ; index++)
    k[4 * index] = orikey[4 * index]^w[index];

    // RCON 적용
    k[0] ^= rcon[AES_NOWROUND - 1];

    // 나머지 연산 
    for(int i = 0 ; i < 16 ; i++)
    {
        if((i + 1) % 4 == 0)    continue;
        else    k[i + 1] = orikey[i + 1]^k[i];
    }
}

inline void prts(int a[16])
{
    for(int i = 0 ; i < 4 ; i++)
    {
        cout.width(2);
        cout.fill('0');
        cout << hex << uppercase << a[i + 0];
        cout.width(2);
        cout.fill('0');
        cout << hex << uppercase << a[i + 4];
        cout.width(2);
        cout.fill('0');
        cout << hex << uppercase << a[i + 8];
        cout.width(2);
        cout.fill('0');
        cout << hex << uppercase << a[i + 12];
    }
}

// AES, Key size - 128bit;
int main() 
{
    int state[2][16] = {
    {
    0x6e, 0x74, 0x77, 0x68,
    0x6f, 0x74, 0x68, 0x61,
    0x6d, 0x65, 0x61, 0x70,
    0x61, 0x72, 0x74, 0x70
    }, 
    {
    0x65, 0x0D, 0x0D, 0x0D,
    0x6e, 0x0D, 0x0D, 0x0D,
    0x73, 0x0D, 0x0D, 0x0D,
    0x0D, 0x0D, 0x0D, 0x0D
    }
    };
    int key[16] = {
    0x64, 0x6C, 0x73, 0x6c,
    0x6f, 0x6f, 0x6d, 0x03,
    0x6e, 0x6f, 0x61, 0x03,
    0x74, 0x6b, 0x6c, 0x03
    };

    int size;
    cout << "128, 192, 256 >> ";
    cin >> size;
    if(size == 128)      AES_ALLROUND = 10;
    else if(size == 192) AES_ALLROUND = 12;
    else if(size == 256) AES_ALLROUND = 14;
    else return 0;
    cout << "Plaintext : ";
    for(int i = 0 ; i < 2 ; i++)
    prts(state[i]);
    cout << endl;
    cout << "Key : ";
    prts(key);
    cout << endl;
    cout << "Ciphertext : ";
    int S_INDEX = 0;
    for(S_INDEX = 0 ; S_INDEX < 2 ; S_INDEX++)
    {
    addroundkey(state[S_INDEX], key);
    for(AES_NOWROUND = 1 ; AES_NOWROUND < AES_ALLROUND  ; AES_NOWROUND++)
    {   
        keyexpansion(key);
        subbyte(state[S_INDEX]);
        shiftrows(state[S_INDEX]);
        mixcolumns(state[S_INDEX]);
        addroundkey(state[S_INDEX], key);
    }
    keyexpansion(key);
    subbyte(state[S_INDEX]);
    shiftrows(state[S_INDEX]);
    addroundkey(state[S_INDEX], key);
 
    prts(state[S_INDEX]);
    }
    cout << endl;
} 


