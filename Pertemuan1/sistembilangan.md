# Tugas Matkul Sistem Operasi (Sistem Bilangan)

# NAMA : Muhammad Aghiitsillah
# KELAS : Teknik Informatika (A)
# NRP : 3124521028

## 1. Bilangan Biner dan Heksadesimal
- a. Bilangan biner adalah bilangan yang berbasis **dua**.
- b. Bilangan heksadesimal adalah bilangan yang berbasis **enam belas**.

## 2. Konversi Bilangan Desimal ke Biner
- a. **1234 (10)**
  - Langkah-langkah:
    - 1234 ÷ 2 = 617 sisa 0
    - 617 ÷ 2 = 308 sisa 1
    - 308 ÷ 2 = 154 sisa 0
    - 154 ÷ 2 = 77 sisa 0
    - 77 ÷ 2 = 38 sisa 1
    - 38 ÷ 2 = 19 sisa 0
    - 19 ÷ 2 = 9 sisa 1
    - 9 ÷ 2 = 4 sisa 1
    - 4 ÷ 2 = 2 sisa 0
    - 2 ÷ 2 = 1 sisa 0
    - 1 ÷ 2 = 0 sisa 1
  - Hasil: **10011010010**

## 3. Konversi Bilangan Biner ke Desimal
- a. **10101010**
  - Perhitungan:
    - 1 × 2^7 + 0 × 2^6 + 1 × 2^5 + 0 × 2^4 + 1 × 2^3 + 0 × 2^2 + 1 × 2^1 + 0 × 2^0
    - = 128 + 0 + 32 + 0 + 8 + 0 + 2 + 0
  - Hasil: **170**

## 4. Konversi Bilangan Biner ke Oktal
- a. **1010111111001**
  - Konversi:
    - 101 = 5
    - 011 = 3
    - 111 = 7
    - 001 = 1
  - Hasil: **5371 (8)**

## 5. Konversi Bilangan Oktal ke Biner
- a. **2170 (8)**
  - Konversi:
    - 2 = 010
    - 1 = 001
    - 7 = 111
    - 0 = 000
  - Hasil: **010001111000**

## 6. Konversi Bilangan Desimal ke Heksadesimal
- a. **1780 (10)**
  - Langkah-langkah:
    - 1780 ÷ 16 = 111 sisa 4
    - 111 ÷ 16 = 6 sisa 15 (F)
    - 6 ÷ 16 = 0 sisa 6
  - Hasil: **06F4**

## 7. Konversi Bilangan Heksadesimal ke Desimal
- a. **ABCD (16)**
  - Perhitungan:
    - A × 16^3 + B × 16^2 + C × 16^1 + D × 16^0
    - = 10 × 4096 + 11 × 256 + 12 × 16 + 13 × 1
    - = 40960 + 2816 + 192 + 13
  - Hasil: **43981**

## 8. Konversi Bilangan Pecahan Desimal ke Biner
- a. **0,3125 (10)**
  - Langkah-langkah:
    - 0,3125 × 2 = 0,625 → 0
    - 0,625 × 2 = 1,25 → 1
    - 0,25 × 2 = 0,5 → 0
    - 0,5 × 2 = 1,0 → 1
  - Hasil: **0,0101**

## 9. Konversi Bilangan Desimal ke Biner
- a. **11,625 (10)**
  - Langkah-langkah:
    - Bagian bulat: 11 (10) = 1011 (2)
    - Bagian pecahan: 0,625 (10) = 0,101 (2)
  - Hasil: **1011,101 (2)**

## 10. Konversi Bilangan Desimal ke Heksadesimal
- a. **348,654 (10)**
  - Langkah-langkah:
    - Bagian bulat: 348 ÷ 16 = 21 sisa 12 (C)
    - 21 ÷ 16 = 1 sisa 5
    - 1 ÷ 16 = 0 sisa 1
    - Bagian pecahan: 0,654 × 16 = 10,464 → 10 (A)
  - Hasil: **15C,A76 (16)**

## 11. Konversi Bilangan ke Desimal
- a. **010100011,001111101 (2)**
  - Perhitungan:
    - 0 × 2^11 + 1 × 2^10 + 0 × 2^9 + 1 × 2^8 + 0 × 2^7 + 0 × 2^6 + 0 × 2^5 + 1 × 2^4 + 1 × 2^3 + 0 × 2^2 + 1 × 2^1 + 0 × 2^0
    - = 163,245
  - Hasil: **163,245 (10)**

## 12. Rubahlah Bilangan Biner ke BCD
- a. **10100110000111 (2)**
  - Langkah-langkah:
    - Pisahkan menjadi digit desimal: 1010 (10) = 10, 0110 (6) = 6, 0001 (1) = 1, 0111 (7) = 7
  - Hasil: **2987 (BCD)**

## 13. Rubahlah BCD ke Bilangan Biner
- a. **1987**
  - Langkah-langkah:
    - 1 = 0001
    - 9 = 1001
    - 8 = 1000
    - 7 = 0111
  - Hasil: **0001100100000111 (2)**

## 14. Rubahlah Bilangan Biner ke BCO
- a. **11111101001 (2)**
  - Kelompokkan dari kanan:
    - 1 111 110 100 1
  - Konversi:
    - 1 = 1
    - 111 = 7
    - 110 = 6
    - 100 = 4
    - 1 = 1
  - Hasil: **3751 (BCO)**

## 15. Rubahlah Bilangan Biner ke BCH
- a. **1101111100101110 (2)**
  - Kelompokkan dari kanan:
    - 1101 1110 0010 1110
  - Konversi:
    - 1101 = D
    - 1110 = E
    - 0010 = 2
    - 1110 = E
  - Hasil: **DE2E (BCH)**

## 16. Rubahlah BCH ke Heksadesimal
- a. **F0DE**
  - Langkah-langkah:
    - F = 1111
    - 0 = 0000
    - D = 1101
    - E = 1110
  - Hasil: **1111000011011110 (2)**

## 17. Nyatakan Positif atau Negatif Bilangan Biner
- a. **01111111**
  - Hasil: **Positif 127**

## 18. Nyatakan Bilangan Biner Negatif ke Desimal
- a. **10001000**
  - Hasil: **-120**

## 19. Nyatakan ASCII Code dalam Karakter
- a. **41 (16)**
  - Hasil: **A**

## 20. Nyatakan Karakter dalam ASCII Code
- a. **a**
  - Hasil: **61 (16)**

## 21. Keluaran pada Keyboard
- a. **PRINT X**
  - Hasil:
    - P (101 0000)
    - R (101 0010)
    - I (100 1001)
    - N (100 1110)
    - T (101 0100)
    - space (010 0000)
    - X (101 1000)
