#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bmp.h"

int save_bmp(const char *filepath, const Code128Data *barcode, int height, int scale) {
    if (!barcode || !barcode->pattern) return 0;

    // Resmin toplam genisligi: (Modul Sayisi * Her bir modulun genisligi)
    int width = (int)barcode->length * scale;
    
    // BMP formati geregi, her satirin bayt uzunlugu 4'un kati olmalidir.
    // 24-bit RGB (3 bayt/piksel) kullanildi. Padding hesabini yapildi.
    int row_size = (width * 3 + 3) & (~3); 
    int data_size = row_size * height;
    
    // Dosya Basligini (14 Bayt) dolduruldu.
    BMPFileHeader fileHeader = {0};
    fileHeader.bfType = 0x4D42; // Hex olarak "BM" karakterlerine karsilik gelir
    fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + data_size;
    fileHeader.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    
    // Bilgi Basligini (40 Bayt) dolduruldu.
    BMPInfoHeader infoHeader = {0};
    infoHeader.biSize = sizeof(BMPInfoHeader);
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24;      // Her piksel icin 3 bayt (R, G, B)
    infoHeader.biSizeImage = data_size;
    
    // Dosyayi ikili (binary) yazma modunda ac
    FILE *file = fopen(filepath, "wb");
    if (!file) {
        printf("Hata: Dosya olusturulamadi veya erisim engellendi -> %s\n", filepath);
        return 0;
    }
    
    // Basliklari diske yaz (struct padding kapattildigi icin tam 54 bayt yazilacak)
    fwrite(&fileHeader, sizeof(BMPFileHeader), 1, file);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, file);
    
    // Performans icin: Barkodun her satiri aynidir. 
    // Tum resmi tek tek hesaplamak yerine 1 satir olusturup bu 'height' kere yazdirilacak.
    unsigned char *row_buffer = (unsigned char *)calloc(row_size, 1);
    
    int byte_index = 0;
    for (size_t i = 0; i < barcode->length; i++) {
        // pattern '1' ise siyah (RGB: 0,0,0), '0' ise beyaz (RGB: 255,255,255) cizilecek.
        // Dikkat: BMP formatinda renkler RGB degil, BGR (Mavi, Yesil, Kirmizi) sirasiyla yazilir.
        // Ancak siyah(0) ve beyaz(255) icin sira fark etmiyor.
        unsigned char color = (barcode->pattern[i] == '1') ? 0 : 255;
        
        // Bir cizginin kalinligi (scale) kadar ayni pikseli yan yana koy
        for (int s = 0; s < scale; s++) {
            row_buffer[byte_index++] = color; // Blue
            row_buffer[byte_index++] = color; // Green
            row_buffer[byte_index++] = color; // Red
        }
    }
    
    // BMP dosyalari resmi asagidan yukariya dogru cizer.
    // Barkod dikey bir yapi oldugu icin siralamanin bizim icin onemi yok.
    for (int h = 0; h < height; h++) {
        fwrite(row_buffer, 1, row_size, file);
    }
    
    free(row_buffer);
    fclose(file);
    
    return 1;
}
