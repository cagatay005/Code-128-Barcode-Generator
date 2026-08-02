#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/code128.h"
#include "../include/bmp.h"

int main () {
    char input[256];

    printf("===========================================\n");
    printf("       Code 128 Barkod Olusturucu          \n");
    printf("===========================================\n\n");

    printf("Barkoda donusturulecek metni giriniz: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
       printf("Hata: Metin Okunamadi.\n");
       return 1;
    }

    // fgets enter karakterini de okur, onu temizleyecegim.
    input[strcspn(input, "\n")] = 0;
    
    if (strlen(input) == 0) {
       printf("Hata: Bos bir metin girdiniz.\n");
       return 1;
    }

    // Metni Code 128 formatina cevir

    Code128Data *barcode = generate_code128(input);
    if (!barcode) {
       printf("Hata: Barkod uretilemedi. \n");
       return 1;
    }

    // Olusan diziyi BMP olarak kaydet.
   
    const char *filepath = "output/barkod.bmp";
    int height = 100;
    int scale  = 2;

    if (save_bmp(filepath, barcode, height, scale)) {
        printf("\nBasarili! Barkod '%s' konumuna kaydedildi.\n", filepath);
        printf("Kullanilan bit deseni uzunlugu: %lu\n", (unsigned long)barcode->length);
    } else{
        printf("\nHata: BMP dosyasi kaydedilemedi.\n");
    }

    // Hafizayi bosaltma

    free_code128_data(barcode);

    printf("\nCikmak icin ENTER tusuna basin ....");
    getchar();
    
    return 0;
}
