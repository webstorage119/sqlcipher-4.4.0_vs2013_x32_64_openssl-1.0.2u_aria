#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char Byte;

//void DL(const Byte *i, Byte *o);	// Diffusion Layer
//void RotXOR(const Byte *s, int n, Byte *t);	// Right-rotate 128 bit source string s by n bits and XOR it to target string t

void printBlockOfLength(Byte *b, int len);
//void printBlock(Byte *b);

// Encryption round key generation rountine
// w0 : master key, e : encryption round keys
int EncKeySetup(const Byte *w0, Byte *e, int keyBits);

// Decryption round key generation rountine
// w0 : maskter key, d : decryption round keys
int DecKeySetup(const Byte *w0, Byte *d, int keyBits);

// Encryption and decryption rountine
// p: plain text, e: round keys, c: ciphertext
void Crypt(const Byte *p, int R, const Byte *e, Byte *c);

void ARIA_test();