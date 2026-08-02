# Code128Generator

🇬🇧 [Read in English](README.en.md)

Girilen metni **Code 128 (Set B)** barkoduna çevirip `.bmp` dosyası olarak kaydeden, C ile yazılmış basit bir komut satırı uygulaması.

## Örnek Çıktı

![Örnek Barkod](output/barkod.bmp)

## Özellikler

- Code 128 Set B kodlaması (ASCII 32–127 arası karakterler desteklenir)
- Checksum (mod 103) hesaplaması
- Sonucu `output/barkod.bmp` dosyasına siyah-beyaz BMP olarak kaydeder
- Harici kütüphane bağımlılığı yok

## Derleme ve Çalıştırma

```powershell
.\build.ps1
```

Bu betik projeyi `gcc` ile derler, `Code128Gen.exe` dosyasını oluşturur ve programı otomatik olarak çalıştırır.

Manuel derlemek isterseniz:

```powershell
gcc -Wall -Iinclude src\main.c src\code128.c src\bmp.c -o Code128Gen.exe
```

## Kullanım

Programı çalıştırıp barkoda çevrilecek metni girin:

```
===========================================
       Code 128 Barkod Olusturucu
===========================================

Barkoda donusturulecek metni giriniz: MERHABA123
```

Barkod `output/barkod.bmp` konumuna kaydedilir.

## Proje Yapısı

```
Code128Generator/
├── include/        # Başlık dosyaları (code128.h, bmp.h)
├── src/            # Kaynak kodlar (main.c, code128.c, bmp.c)
├── output/         # Üretilen BMP barkodları
└── build.ps1       # Derleme ve çalıştırma betiği
```
