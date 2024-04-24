#include "hash.h"

/* Random values to hash a byte */
static u32 byte_hash[256] = {
  0xEEAE7FDA, 0xD3395927, 0x4DD35D53, 0x30D67301, 0xBD397767, 0x16ADF05B, 0x436E841E, 0x4D4CEFEC,
  0x49BCFBB3, 0xFB7E1816, 0x5D60A901, 0xF22DDC89, 0x25CCADBE, 0x6FE4EE81, 0xEF42FD31, 0x57E385FF,
  0x3ED39511, 0xCF4CD8D4, 0x67D62B49, 0x39E8A08D, 0xCFCAF7C2, 0x2CED1929, 0x1CCCC1FB, 0x8B80EEF9,
  0x116B7BE7, 0xCCC3CF25, 0xEB5E6E0F, 0x1D6A7431, 0xCF79475C, 0x37A577DA, 0xD840F52F, 0xDD6E53B2,
  0x3D418231, 0xF7D4B6A3, 0xBAA9C2F9, 0xE63F8CB8, 0xF79FF9F0, 0xA483EC31, 0xA97B22AB, 0xB5E4B670,
  0xE742CFBD, 0xDC6A86A6, 0x8439AA08, 0x5E126F51, 0xEB8868CB, 0x4D49FF2D, 0x5A821FF7, 0x74BDA557,
  0x427EECFE, 0xA5EA7CC7, 0x617DE328, 0x263AEFB4, 0x627F69C0, 0x06FF54DC, 0x7683665C, 0x3FB86DD1,
  0xC7CF6434, 0x3F1E732F, 0xF757E2FE, 0x1CAEFF01, 0x123D1E23, 0xC14433E7, 0x5049FE4E, 0x74A8A9B0,
  0xD4F78FA1, 0x7DA2B0F8, 0xC790E436, 0x9EBD63E5, 0x8F2EDFDB, 0x8B9A5FC3, 0xDAA1E03A, 0x514F5BA7,
  0xE255EFF7, 0xCC392CF6, 0x536BEE85, 0x681B10C6, 0x8123DF1D, 0xDC7E29FA, 0x4887B4FF, 0xCC0F862C,
  0xE9B81C3B, 0x70B5F57C, 0x94FAE5E4, 0x599CAF5D, 0x69752EAE, 0x7DDD1BFD, 0x7A9F4A93, 0x0416CF76,
  0x26EA3D7B, 0x81115165, 0xBAAD1FBE, 0xA65CA2BF, 0x382AE3FB, 0xE604F959, 0xDBDC1A43, 0xFC813DF9,
  0x21C99FD9, 0x18AF57CC, 0x3777368D, 0xCFA15D62, 0x2FAE4BE8, 0x2A38BAEF, 0xF9315255, 0xAF8A3A3F,
  0xB11ADEDB, 0x9687E662, 0xFD04F32F, 0x23A901CA, 0xC9E3637C, 0x302A5D79, 0x4F864375, 0x6DB2680A,
  0x9F2CA5D3, 0xE2BA01D3, 0x7EF599F4, 0x99782F3A, 0xB4B612FD, 0xA4B4D51F, 0x0B0BC03F, 0xD616D516,
  0xBA937015, 0xB479A062, 0x524E46D2, 0xC0D991EE, 0x564A1FBF, 0x7CF3C948, 0xA4B37984, 0xAB7BD7DC,
  0x59A99CE8, 0x525D7D19, 0xFF54D6DF, 0xBF2D8A20, 0xA75AD6FD, 0x6D66A13D, 0xD299AD6E, 0x53C0FC7A,
  0x0E79357E, 0x5AD21E66, 0x58703079, 0x1EA4FFA7, 0xCFADCCD3, 0xCB66B728, 0x5ED447FE, 0xC9475BEC,
  0x6D843DBF, 0x657C76CC, 0xD9FFFAAE, 0x9B9D7839, 0x6022BFAB, 0x2C33F4D9, 0x0A76FF79, 0x12FFB354,
  0xD825C62F, 0x20F6A1DB, 0x49F36134, 0xA0ACECDD, 0xAA6100FD, 0xAEFF3E12, 0xEC39F716, 0x1859F595,
  0x4A7E112F, 0x0DB7628A, 0xC0637DFB, 0x02CA7492, 0x9E3CCC7A, 0xC5CD777E, 0x46946EF0, 0xCBFB7761,
  0x761BBDCA, 0x9BA3BDF4, 0x2AF77FAD, 0x67A2BBE3, 0xCA293C70, 0xA31829F8, 0xC96DCDBA, 0x5A181B2D,
  0xF116C9C0, 0x3FDC9E3E, 0x14EC5F93, 0x00B37CA4, 0x4EBD4A83, 0x9E8B8971, 0xF5DF633C, 0x9AFB4CDB,
  0x2F44CFB6, 0xE5DAF83B, 0x9AF13F2F, 0x835203EA, 0xB25C2EEA, 0x75071906, 0x8D3A47F7, 0x327C1BE5,
  0xEC7A5BFC, 0xC37E1F90, 0xCAFF5DCB, 0x6A9334B7, 0xBE96ED80, 0xBFA60639, 0xC1D6A1DA, 0x85855191,
  0xCDAB3C7E, 0x3D9AAB4A, 0xE16C8EA9, 0x1BDE28F5, 0xC623E578, 0x046C8D85, 0x2BCFD4F2, 0xFF7CC65D,
  0xEE343FEF, 0x3B870AF0, 0x6CF194A5, 0x1E03EEC9, 0x33FDE13D, 0x7FC6041C, 0x61CBEBFB, 0xC53E2BC2,
  0xFDDC9165, 0x028060A8, 0x2A27D908, 0x282AE930, 0x49319EC6, 0xDA9D1D49, 0xDE5E14BC, 0x07482362,
  0x5A1EE029, 0x1F9362CE, 0x9E7E10C6, 0x82E5E816, 0xED023B0C, 0x51F3A853, 0x3AB9FBA2, 0xF87647C1,
  0xA3417962, 0x9FA081C9, 0x8FE99CE9, 0xA8DD0894, 0x08585E61, 0x0F3CA1F5, 0x13A92FD5, 0x28A2B95E,
  0x5FECF8A2, 0xE7D9AF03, 0xB9296456, 0xD1439B1F, 0xBE43F197, 0xEFA69921, 0xD7EF180C, 0xBDB00401,
  0xB0FB7717, 0x26EB2FB1, 0xD3F7A737, 0xCC20DB21, 0xCE98D95A, 0xBB4FE919, 0xDBBDEE1B, 0x331E35FA,
};

/* Hashes are rotate and xor hashes of bytes, which allow them to be used as a
rolling hash */

u32 AppendHash(u32 hash, u8 byte)
{
  hash = (hash << 1) | (hash >> 31);
  return hash ^ byte_hash[byte];
}

u32 SkipHash(u32 hash, u8 byte, u32 size)
{
  u32 rotate = (size-1) % 32;
  u32 unhash = (byte_hash[byte] << rotate) | (byte_hash[byte] >> (32-rotate));
  return hash ^ unhash;
}

u32 Hash(void *data, u32 size)
{
  u32 i;
  u32 hash = 0;
  for (i = 0; i < size; i++) {
    hash = AppendHash(hash, ((u8*)data)[i]);
  }
  return hash;
}
