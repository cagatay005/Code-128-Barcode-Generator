#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include "code128.h"

// Derleyicinin struct içerisine fazladan boşluk eklemesini engellemek lazım.
#pragma pack(push,1)

// BMP Dosya başlığı (14 Byte)
typedef struct {
     uint16_t bfType;
     uint32_t bfSize;
     uint16_t bfReversed1;
     uint16_t bfReversed2;
     uint32_t bfOffBits;
} BMPFileHeader;

// BMP bilgi baslıgı (40 byte)
typedef struct {
     uint32_t biSize;
     int32_t  biWidth;
     int32_t  biHeight;
     uint16_t biPlanes;
     uint16_t biBitCount;
     uint32_t biCompression;
     uint32_t biSizeImage;
     int32_t  biXPelsPerMeter;
     int32_t  biYPelsPerMeter;
     uint32_t biClrUsed;
     uint32_t biClrImportant;
} BMPInfoHeader;

#pragma pack(pop)

// Fonksiyon prototipi

int save_bmp(const char *filepath, const Code128Data *barcode, int height, int scale);

#endif // BMP_H
