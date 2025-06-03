# Analisis Algoritma SJF Tanpa Waktu Kedatangan (Non-Preemptive)

## Deskripsi Algoritma

Algoritma penjadwalan Shortest Job First (SJF) tanpa waktu kedatangan (non-preemptive) bekerja sebagai berikut:

1. Semua proses diasumsikan tiba pada waktu 0
2. CPU menjadwalkan proses berdasarkan urutan waktu burst mereka (yang terpendek terlebih dahulu)
3. Setelah proses mulai dieksekusi, proses tersebut akan berjalan hingga selesai (non-preemptive)

## Komponen Utama Kode

Implementasi yang diberikan:

- Menggunakan struktur `proc` untuk menyimpan detail proses:
  - `no`: Nomor proses
  - `bt`: Burst time (waktu eksekusi)
  - `ct`: Completion time (waktu penyelesaian)
  - `tat`: Turnaround time (waktu turnaround)
  - `wt`: Waiting time (waktu tunggu)
- Mengurutkan proses berdasarkan waktu burst menggunakan bubble sort
- Menghitung waktu penyelesaian, waktu turnaround, dan waktu tunggu untuk setiap proses
- Menghitung dan menampilkan rata-rata waktu turnaround dan waktu tunggu

## Alur Eksekusi

1. Pengguna memasukkan jumlah proses dan waktu burst mereka
2. Proses diurutkan dalam urutan naik berdasarkan waktu burst
3. Setiap proses dieksekusi satu per satu dalam urutan yang telah diurutkan
4. Untuk setiap proses, algoritma menghitung:
   - Waktu penyelesaian (CT) = Jumlah waktu burst hingga proses saat ini
   - Waktu turnaround (TAT) = CT (karena waktu kedatangan = 0)
   - Waktu tunggu (WT) = TAT - BT
   - Waktu respons (RT) = WT (dalam konteks ini, karena waktu kedatangan = 0)

## Pseudocode

```
1. Input jumlah proses n
2. Input burst time untuk setiap proses
3. Urutkan proses berdasarkan burst time (ascending)
4. Inisialisasi CT = 0
5. Untuk setiap proses i dari 1 hingga n:
   a. CT = CT + BT[i]
   b. TAT[i] = CT
   c. WT[i] = TAT[i] - BT[i]
6. Hitung rata-rata TAT dan WT
7. Tampilkan hasil
```

## Kelebihan SJF

- Meminimalkan rata-rata waktu tunggu dibandingkan dengan algoritma FCFS (First-Come-First-Served)
- Optimal untuk meminimalkan rata-rata waktu tunggu ketika semua proses tiba secara bersamaan
- Sederhana untuk diimplementasikan ketika waktu kedatangan tidak dipertimbangkan
- Menghasilkan rata-rata waktu tunggu yang lebih pendek dibanding algoritma lain

## Keterbatasan Implementasi

1. Kode mengasumsikan semua proses tiba pada waktu 0 (waktu kedatangan tidak dipertimbangkan)
2. Bersifat non-preemptive, artinya setelah proses dimulai, proses akan berjalan hingga selesai
3. Implementasi bubble sort untuk mengurutkan proses tidak efisien untuk dataset yang besar
4. Tidak memperhitungkan dinamika proses yang tiba pada waktu yang berbeda

## Implikasi Kinerja

SJF secara teoritis optimal untuk meminimalkan rata-rata waktu tunggu, tetapi memiliki keterbatasan praktis:

- Membutuhkan pengetahuan waktu burst di awal, yang biasanya tidak mungkin dalam sistem nyata
- Dapat menyebabkan kelaparan (starvation) pada proses yang lebih panjang jika proses yang lebih pendek terus berdatangan
- Dalam pengimplementasian yang lebih realistis, prediksi waktu burst harus dilakukan

## Contoh Kasus

Untuk contoh 3 proses dengan burst time:
- P1: 6 unit
- P2: 3 unit
- P3: 8 unit

Setelah pengurutan: P2, P1, P3

| Proses | BT | CT | TAT | WT | RT |
|--------|----|----|-----|----|----|
| P2     | 3  | 3  | 3   | 0  | 0  |
| P1     | 6  | 9  | 9   | 3  | 3  |
| P3     | 8  | 17 | 17  | 9  | 9  |

Rata-rata TAT = (3 + 9 + 17) / 3 = 9.67
Rata-rata WT = (0 + 3 + 9) / 3 = 4.00

## Kesimpulan

Algoritma SJF tanpa waktu kedatangan merupakan implementasi sederhana yang efektif untuk meminimalkan waktu tunggu rata-rata dan cocok untuk lingkungan di mana semua proses tersedia secara bersamaan pada awal eksekusi. Namun, dalam kasus yang lebih realistis, versi preemptive (SRTF - Shortest Remaining Time First) dan pertimbangan waktu kedatangan yang berbeda akan memberikan hasil yang lebih baik dalam lingkungan multiprogramming yang dinamis.
