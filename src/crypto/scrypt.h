#ifndef SCRYPT_H
#define SCRYPT_H
#include <stdlib.h>
#include <stdint.h>

void scrypt_N_1_1_256(const char *input, char *output, unsigned char Nfactor);
void scrypt_N_1_1_256_sp_generic(const char *input, char *output, char *scratchpad, unsigned char Nfactor);

#if defined(USE_SSE2)
#include <string>
#if defined(_M_X64) || defined(__x86_64__) || defined(_M_AMD64) || (defined(MAC_OSX) && defined(__i386__))
#define USE_SSE2_ALWAYS 1
#define scrypt_N_1_1_256_sp(input, output, scratchpad, Nfactor) scrypt_N_1_1_256_sp_sse2((input), (output), (scratchpad), (Nfactor))
#else
#define scrypt_N_1_1_256_sp(input, output, scratchpad, Nfactor) scrypt_N_1_1_256_sp_detected((input), (output), (scratchpad), (Nfactor))
#endif

std::string scrypt_detect_sse2();
void scrypt_N_1_1_256_sp_sse2(const char *input, char *output, char *scratchpad, unsigned char Nfactor);
extern void (*scrypt_N_1_1_256_sp_detected)(const char *input, char *output, char *scratchpad, unsigned char Nfactor);
#else
#define scrypt_N_1_1_256_sp(input, output, scratchpad, Nfactor) scrypt_N_1_1_256_sp_generic((input), (output), (scratchpad), (Nfactor))
#endif

void
PBKDF2_SHA256(const uint8_t *passwd, size_t passwdlen, const uint8_t *salt,
    size_t saltlen, uint64_t c, uint8_t *buf, size_t dkLen);

static inline uint32_t le32dec(const void *pp)
{
        const uint8_t *p = (uint8_t const *)pp;
        return ((uint32_t)(p[0]) + ((uint32_t)(p[1]) << 8) +
            ((uint32_t)(p[2]) << 16) + ((uint32_t)(p[3]) << 24));
}

static inline void le32enc(void *pp, uint32_t x)
{
        uint8_t *p = (uint8_t *)pp;
        p[0] = x & 0xff;
        p[1] = (x >> 8) & 0xff;
        p[2] = (x >> 16) & 0xff;
        p[3] = (x >> 24) & 0xff;
}
#endif