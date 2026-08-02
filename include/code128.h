#ifndef CODE128_H
#define CODE128_H

#include <stddef.h>

// Code 128 Ozel Karakter (Sembol) Değerleri
#define CODE128_START_A 103
#define CODE128_START_B 104
#define CODE128_START_C 105
#define CODE128_STOP    106

// Barkod verisini tasiyacak yapi
typedef struct {
    char *pattern;
    size_t length;
} Code128Data;

// Fonksiyon Prototipleri

Code128Data* generate_code128(const char *text);
void free_code128_data(Code128Data *barcode);

#endif // CODE128_H
