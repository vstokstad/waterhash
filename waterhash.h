/*
    Original Author: Wang Yi <godspeed_china@yeah.net>
    Waterhash Variant Author: Tommy Ettinger <tommy.ettinger@gmail.com>
*/
#ifndef waterhash_version_1
#define waterhash_version_1
#include <stdint.h>
#include <string.h>
#include <math.h>
const uint32_t _waterp0 = 0xa0761d65ul, _waterp1 = 0xe7037ed1ul, _waterp2 = 0x8ebc6af1ul;
const uint32_t _waterp3 = 0x589965cdul, _waterp4 = 0x1d8e4e27ul, _waterp5 = 0xeb44accbul;

static inline uint32_t _watermum(uint64_t A, uint64_t B) {
    uint64_t r = A * B;
    return r - (r >> 32);
}

static inline uint32_t _waterr08(const uint8_t *p){ uint8_t  v; memcpy(&v, p, 1); return v; }
static inline uint32_t _waterr16(const uint8_t *p){ uint16_t v; memcpy(&v, p, 2); return v; }
static inline uint32_t _waterr32(const uint8_t *p){ uint32_t v; memcpy(&v, p, 4); return v; }
static inline uint32_t waterhash(const void* key, uint32_t len, uint32_t seed){
    const uint8_t *p = (const uint8_t*)key;
    uint32_t i;
    for (i = 0; i + 16 <= len; i += 16, p += 16)
    {
        seed = _watermum(_watermum(_waterr32(p) ^ _waterp1, _waterr32(p + 4) ^ _waterp2) + seed, _watermum(_waterr32(p + 8) ^ _waterp3, _waterr32(p + 12) ^ _waterp4));
    }
    seed += _waterp0;
    switch (len & 15) {
        case 1:  seed = _watermum(seed ^ _waterp2, _waterr08(p) ^ _waterp1); break;
        case 2:  seed = _watermum(seed ^ _waterp4, _waterr16(p) ^ _waterp2); break;
        case 3:  seed = _watermum(_waterr16(p) ^ seed, _waterr08(p + 2) ^ _waterp2); break;
        case 4:  seed = _watermum(_waterr16(p) ^ seed, _waterr16(p + 2) ^ _waterp3); break;
        case 5:  seed = _watermum(_waterr16(p) ^ seed, (_waterr16(p + 2) << 8 | _waterr08(p + 4)) ^ _waterp1); break;
        case 6:  seed = _watermum(_waterr32(p) ^ seed, _waterr16(p + 4) ^ _waterp1); break;
        case 7:  seed = _watermum(_waterr32(p) ^ seed, (_waterr16(p + 4) << 8 | _waterr08(p + 6)) ^ _waterp1); break;
        case 8:  seed = _watermum(_waterr32(p) ^ seed, _waterr32(p + 4) ^ _waterp2); break;
        case 9:  seed = _watermum(_waterr32(p) ^ seed, _waterr32(p + 4) ^ _waterp2) ^ _watermum(seed, _waterr08(p + 8) ^ _waterp3); break;
        case 10: seed = _watermum(_waterr32(p) ^ seed, _waterr32(p + 4) ^ _waterp2) ^ _watermum(seed, _waterr16(p + 8) ^ _waterp3); break;
        case 11: seed = _watermum(_waterr32(p) ^ seed, _waterr32(p + 4) ^ _waterp2) ^ _watermum(seed, ((_waterr16(p + 8) << 8) | _waterr08(p + 10)) ^ _waterp3); break;
        case 12: seed = _watermum(_waterr32(p) ^ seed, _waterr32(p + 4) ^ _waterp2) ^ _watermum(seed, _waterr32(p + 8) ^ _waterp3); break;
        case 13: seed = _watermum(_waterr32(p) ^ seed, _waterr32(p + 4) ^ _waterp2) ^ _watermum(seed ^ _waterr32(p + 8), (_waterr08(p + 12)) ^ _waterp4); break;
        case 14: seed = _watermum(_waterr32(p) ^ seed, _waterr32(p + 4) ^ _waterp2) ^ _watermum(seed ^ _waterr32(p + 8), (_waterr16(p + 12)) ^ _waterp4); break;
        case 15: seed = _watermum(_waterr32(p) ^ seed, _waterr32(p + 4) ^ _waterp2) ^ _watermum(seed ^ _waterr32(p + 8), (_waterr16(p + 12) << 8 | _waterr08(p + 14)) ^ _waterp4); break;
    }
    return _watermum(seed + _waterp5, len ^ _waterp5);   
}
#endif
