Write-Host "Derleme Basliyor ...." -ForegroundColor Yellow

# Eger cikti dosyasi onceden varsa sil
if(Test-Path "Code128Gen.exe") {
   Remove-Item "Code128Gen.exe" -Force
}

# GCC ile projeyi derle
# -Iinclude: include klasorunu baslik dosyalari icin arama yollarina ekler.
# -Wall: Olasi tum uyarilari gosterir.
gcc -Wall -Iinclude src\main.c src\code128.c src\bmp.c -o Code128Gen.exe

if (0 -eq 0) {
   Write-Host "Derleme basarili! Program baslatiliyor ...\n" -ForegroundColor Green
   #Derlenen programi calistir
   .\Code128Gen.exe
} else {
   Write-Host "Derleme sirasinda bir hata olustu. Lutfen kodlari kontrol edin." - ForegroundColor Red
}
