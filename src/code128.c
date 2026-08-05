#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/code128.h"

// 0'dan 106'ya kadar olan tum Code 128 sembollerinin bit desenleri
// 1: Siyah cizgi, 0: Beyaz bosluk
const char *CODE128_PATTERNS[] = {
    "11011001100", "11001101100", "11001100110", "10010011000", "10010001100",
    "10001001100", "10011001000", "10011000100", "10001100100", "11001001000",
    "11001000100", "11000100100", "10110011100", "10011011100", "10011001110",
    "10111001100", "10011101100", "10011100110", "11001110010", "11001011100",
    "11001001110", "11011100100", "11001110100", "11101101110", "11101001100",
    "11100101100", "11100100110", "11101100100", "11100110100", "11100110010",
    "11011011000", "11011000110", "11000110110", "10100011000", "10001011000",
    "10001000110", "10110001000", "10001101000", "10001100010", "11010001000",
    "11000101000", "11000100010", "10110111000", "10110001110", "10001101110",
    "10111011000", "10111000110", "10001110110", "11101110110", "11010001110",
    "11000101110", "11011101000", "11011100010", "11011101110", "11101011000",
    "11101000110", "11100010110", "11101101000", "11101100010", "11100011010",
    "11101111010", "11001000010", "11110001010", "10100110000", "10100001100",
    "10010110000", "10010000110", "10000101100", "10000100110", "10110010000",
    "10110000100", "10011010000", "10011000010", "10000110100", "10000110010",
    "11000010010", "11001010000", "11110111010", "11000010100", "10001111010",
    "10100111100", "10010111100", "10010011110", "10111100100", "10011110100",
    "10011110010", "11110100100", "11110010100", "11110010010", "11011011110",
    "11011110110", "11110110110", "10101111000", "10100011110", "10001011110",
    "10111101000", "10111100010", "11110101000", "11110100010", "10111011110",
    "10111101110", "11101011110", "11110101110", "11010000100", "11010010000",
    "11010011100", "1100011101011" // 106 - STOP (Digerleri 11 bit iken, bu ozel olarak 13 bittir)
};

Code128Data* generate_code128(const char *text) {
    if (!text || strlen(text) == 0) return NULL;

    size_t text_len = strlen(text);
    
    // Bellek boyutu hesabi:
    // Start B (11 bit) + Text (KarakterSayisi * 11 bit) + Checksum (11 bit) + Stop (13 bit) + Null Terminator (1 bit)
    size_t total_bits = 11 + (text_len * 11) + 11 + 13;
    
    // Struct icin bellek ayirma
    Code128Data *barcode = (Code128Data*)malloc(sizeof(Code128Data));
    if (!barcode) return NULL;
    
    // 1 ve 0 dizisi icin bellek ayirma
    barcode->pattern = (char*)malloc(total_bits + 1);
    if (!barcode->pattern) {
        free(barcode);
        return NULL;
    }
    
    barcode->pattern[0] = '\0'; // strcat ile ekleme yapabilmek icin stringi baslatir
    barcode->length = total_bits;

    // START B sembolunu ekle (Deger: 104)
    strcat(barcode->pattern, CODE128_PATTERNS[CODE128_START_B]);
    
    // Metni isleme ve Checksum hesabi
    // Checksum baslangic degeri Start sembolunun degeriyle baslar
    int checksum = CODE128_START_B; 
    
    for (size_t i = 0; i < text_len; i++) {
        // Code 128 Set B'de ASCII 32(bosluk) ile 127 arasi desteklenir
        if (text[i] < 32 || text[i] > 127) {
            printf("Uyari: Desteklenmeyen karakter atlandi -> %c\n", text[i]);
            continue; 
        }
        
        // Code 128 Tablo B degerini bulmak icin ASCII degerinden 32 cikartilir
        int value = text[i] - 32;
        
        // Ilgili sembolun cizgi desenini diziye yapistir
        strcat(barcode->pattern, CODE128_PATTERNS[value]);
        
        // Checksum formulu: (Deger * Pozisyon) -> Pozisyonlar 1'den baslar
        checksum += value * (i + 1);
    }
    
    // Checksum mod 103 hesabi yapilir ve barkoda eklenir
    checksum = checksum % 103;
    strcat(barcode->pattern, CODE128_PATTERNS[checksum]);
    
    // STOP sembolunu ekle (Deger: 106)
    strcat(barcode->pattern, CODE128_PATTERNS[CODE128_STOP]);
    
    return barcode;
}

void free_code128_data(Code128Data *barcode) {
    if (barcode) {
        if (barcode->pattern) {
            free(barcode->pattern);
        }
        free(barcode);
    }
}
