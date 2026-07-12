// import header 
#include "../include/hash.h"

void hash_password(const char *password, char *output_hash) {
    uint32_t h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f, h5 = 0x9b05688c, h6 = 0x1f83d9ab, h7 = 0x5be0cd19;

    uint64_t bitlen = strlen(password) * 8;
    uint8_t msg[128] = {0}; 
    memcpy(msg, password, strlen(password));
    
    // Pad the message according to SHA-256 specifications
    msg[strlen(password)] = 0x80;
    msg[63] = bitlen;
    msg[62] = bitlen >> 8;

    uint32_t W[64];
    for (int t = 0; t < 16; t++) {
        W[t] = (msg[t*4] << 24) | (msg[t*4+1] << 16) | (msg[t*4+2] << 8) | (msg[t*4+3]);
    }
    for (int t = 16; t < 64; t++) {
        W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
    }

    uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;

    for (int t = 0; t < 64; t++) {
        uint32_t t1 = h + SIG1(e) + CH(e,f,g) + K[t] + W[t];
        uint32_t t2 = SIG0(a) + MAJ(a,b,c);
        h = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
    }

    h0 += a; h1 += b; h2 += c; h3 += d; h4 += e; h5 += f; h6 += g; h7 += h;

    // Convert binary numbers into readable 64-character hex string
    sprintf(output_hash, "%08x%08x%08x%08x%08x%08x%08x%08x", h0, h1, h2, h3, h4, h5, h6, h7);
}