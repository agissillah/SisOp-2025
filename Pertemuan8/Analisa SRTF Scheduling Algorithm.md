# Analisis Algoritma SRTF (Shortest Remaining Time First)

## Deskripsi Algoritma

Shortest Remaining Time First (SRTF) adalah versi preemptive dari algoritma penjadwalan SJF (Shortest Job First). Algoritma ini bekerja sebagai berikut:

1. Pada setiap titik waktu, CPU mengeksekusi proses dengan sisa waktu eksekusi terpendek
2. Jika proses baru tiba dan memiliki waktu burst lebih pendek daripada sisa waktu proses yang sedang dieksekusi, proses yang sedang berjalan akan diinterupsi (preempted)
3. Proses yang diinterupsi akan dilanjutkan kembali ketika tidak ada proses lain dengan sisa waktu eksekusi yang lebih pendek

SRTF merupakan algoritma penjadwalan yang optimal dalam hal meminimalkan waktu tunggu rata-rata untuk semua proses.

## Komponen Utama Kode

Implementasi yang diberikan:

- Menggunakan struktur `proc` untuk menyimpan detail proses:
  - `no`: Nomor proses
  - `at`: Arrival time (waktu kedatangan)
  - `bt`: Burst time (waktu eksekusi total)
  - `rt`: Remaining time (sisa waktu eksekusi)
  - `ct`: Completion time (waktu penyelesaian)
  - `tat`: Turnaround time (waktu turnaround)
  - `wt`: Waiting time (waktu tunggu)
- Mengurutkan proses berdasarkan waktu kedatangan menggunakan bubble sort
- Menggunakan konstanta `MAX` (9999) sebagai nilai awal untuk perbandingan
- Menjalankan simulasi dengan granularitas waktu 1 unit
- Menghitung dan menampilkan waktu penyelesaian, waktu turnaround, dan waktu tunggu

## Alur Eksekusi Algoritma

1. Pengguna memasukkan jumlah proses, waktu kedatangan, dan waktu burst
2. Proses diurutkan berdasarkan waktu kedatangan
3. Simulasi dijalankan dari waktu t=0 dengan langkah-langkah:
   - Untuk setiap unit waktu, identifikasi proses dengan sisa waktu eksekusi terpendek di antara proses-proses yang telah tiba
   - Kurangi sisa waktu (rt) proses tersebut sebanyak 1 unit
   - Jika sisa waktu mencapai 0, proses selesai:
     - Hitung completion time (ct) = waktu saat ini + 1
     - Hitung turnaround time (tat) = ct - at
     - Hitung waiting time (wt) = tat - bt
   - Lanjutkan sampai semua proses selesai

## Contoh Kasus

Misalkan terdapat 4 proses dengan detail berikut:
- P1: AT=0, BT=8
- P2: AT=1, BT=4
- P3: AT=2, BT=9
- P4: AT=3, BT=5

Berikut adalah simulasi langkah demi langkah:

### Simulasi SRTF

| Waktu | Proses yang Dijalankan | Proses yang Tersedia | Sisa Waktu Setelah Eksekusi |
|-------|------------------------|----------------------|------------------------------|
| 0     | P1                     | P1                   | P1=7, P2=4, P3=9, P4=5      |
| 1     | P2                     | P1, P2              | P1=7, P2=3, P3=9, P4=5      |
| 2     | P2                     | P1, P2, P3          | P1=7, P2=2, P3=9, P4=5      |
| 3     | P2                     | P1, P2, P3, P4      | P1=7, P2=1, P3=9, P4=5      |
| 4     | P2                     | P1, P2, P3, P4      | P1=7, P2=0, P3=9, P4=5      |
| 5     | P4                     | P1, P3, P4          | P1=7, P2=0, P3=9, P4=4      |
| 6     | P4                     | P1, P3, P4          | P1=7, P2=0, P3=9, P4=3      |
| 7     | P4                     | P1, P3, P4          | P1=7, P2=0, P3=9, P4=2      |
| 8     | P4                     | P1, P3, P4          | P1=7, P2=0, P3=9, P4=1      |
| 9     | P4                     | P1, P3, P4          | P1=7, P2=0, P3=9, P4=0      |
| 10    | P1                     | P1, P3              | P1=6, P2=0, P3=9, P4=0      |
| 11    | P1                     | P1, P3              | P1=5, P2=0, P3=9, P4=0      |
| 12    | P1                     | P1, P3              | P1=4, P2=0, P3=9, P4=0      |
| 13    | P1                     | P1, P3              | P1=3, P2=0, P3=9, P4=0      |
| 14    | P1                     | P1, P3              | P1=2, P2=0, P3=9, P4=0      |
| 15    | P1                     | P1, P3              | P1=1, P2=0, P3=9, P4=0      |
| 16    | P1                     | P1, P3              | P1=0, P2=0, P3=9, P4=0      |
| 17    | P3                     | P3                  | P1=0, P2=0, P3=8, P4=0      |
| 18    | P3                     | P3                  | P1=0, P2=0, P3=7, P4=0      |
| ...   | ...                    | ...                 | ...                         |
| 25    | P3                     | P3                  | P1=0, P2=0, P3=0, P4=0      |

### Hasil Akhir

| Proses | AT | BT | CT | TAT | WT |
|--------|----|----|----|----|-----|
| P1     | 0  | 8  | 17 | 17 | 9  |
| P2     | 1  | 4  | 5  | 4  | 0  |
| P3     | 2  | 9  | 26 | 24 | 15 |
| P4     | 3  | 5  | 10 | 7  | 2  |

Rata-rata TAT = (17 + 4 + 24 + 7) / 4 = 13
Rata-rata WT = (9 + 0 + 15 + 2) / 4 = 6.5

## Detail Algoritma SRTF

### Analisis Langkah-Langkah Eksekusi

Algoritma SRTF bekerja dengan simulasi berbasis waktu:

1. Mulai dari t=0
2. Pada setiap unit waktu:
   - Identifikasi semua proses yang telah tiba (AT ≤ t)
   - Pilih proses dengan remaining time (RT) terkecil
   - Kurangi RT proses tersebut sebanyak 1 unit
   - Jika RT mencapai 0, proses selesai dan hitung metrik kinerja
3. Jika proses baru tiba dan memiliki RT lebih kecil daripada proses yang sedang dieksekusi, proses baru tersebut akan mengambil alih CPU (preemption)

### Implementasi Kode Detail

```
1. Input jumlah proses n
2. Input arrival time dan burst time untuk setiap proses
3. Set remaining time = burst time untuk setiap proses
4. Urutkan proses berdasarkan arrival time (ascending)
5. Inisialisasi dummy process dengan RT = MAX (9999)
6. Untuk time=0; sampai semua proses selesai; time++:
   a. s = indeks dummy process (9)
   b. Untuk setiap proses i:
      Jika (AT[i] ≤ time) DAN (RT[i] < RT[s]) DAN (RT[i] > 0)
         s = i
   c. RT[s]--
   d. Jika RT[s] == 0:
      - Proses s selesai
      - Increment jumlah proses yang selesai
      - CT[s] = time + 1
      - TAT[s] = CT[s] - AT[s]
      - WT[s] = TAT[s] - BT[s]
7. Hitung rata-rata TAT dan WT
8. Tampilkan hasil
```

## Kelebihan Algoritma SRTF

- Optimal untuk meminimalkan waktu tunggu rata-rata
- Responsif terhadap proses dengan kebutuhan CPU pendek
- Memprioritaskan proses-proses kecil, sehingga meningkatkan throughput
- Dapat beradaptasi dengan kedatangan proses baru yang lebih pendek
- Cocok untuk sistem time-sharing di mana waktu respons cepat adalah prioritas

## Keterbatasan Implementasi

1. Membutuhkan pengetahuan tentang waktu burst sebelumnya, yang sulit dalam sistem nyata
2. Overhead komputasi tinggi karena keputusan preemptive pada setiap unit waktu
3. Implementasi bubble sort untuk mengurutkan proses tidak efisien untuk dataset yang besar
4. Dapat menyebabkan kelaparan (starvation) untuk proses dengan waktu burst panjang
5. Response time (RT) tidak dihitung dalam implementasi ini (seharusnya waktu dari kedatangan hingga pertama kali dieksekusi)

## Perbandingan dengan Algoritma Lain

| Aspek | FCFS | SJF | SRTF |
|-------|------|-----|------|
| Jenis | Non-preemptive | Non-preemptive | Preemptive |
| Waktu tunggu rata-rata | Tinggi | Sedang | Terendah |
| Kompleksitas | Rendah | Sedang | Tinggi |
| Risiko starvation | Tidak | Ya | Ya |
| Overhead | Rendah | Sedang | Tinggi |
| Waktu respons | Buruk | Sedang | Baik |
| Optimal | Tidak | Tidak | Ya (untuk waktu tunggu) |

## Implikasi Kinerja

SRTF memiliki karakteristik kinerja:

- Menghasilkan waktu tunggu rata-rata minimum di antara semua algoritma penjadwalan
- Mengoptimalkan waktu respons untuk proses-proses pendek
- Proses-proses panjang mungkin mengalami kelaparan jika proses-proses pendek terus berdatangan
- Membutuhkan overhead karena context switching yang sering terjadi
- Sulit diimplementasikan dalam sistem nyata karena membutuhkan prediksi waktu burst yang akurat

## Implementasi Praktis

Dalam sistem operasi nyata:
- Estimasi waktu burst menggunakan metode prediksi seperti exponential averaging
- Penggunaan quantum waktu untuk membatasi waktu eksekusi
- Kombinasi dengan algoritma prioritas untuk menghindari starvation
- Implementasi struktur data yang efisien untuk pemilihan proses

## Kesimpulan

Shortest Remaining Time First (SRTF) adalah algoritma penjadwalan preemptive yang optimal untuk meminimalkan waktu tunggu rata-rata. Algoritma ini sangat responsif terhadap proses-proses dengan kebutuhan CPU rendah, yang membuatnya cocok untuk sistem interaktif. Namun, kompleksitasnya yang tinggi dan kebutuhan untuk memprediksi waktu burst menjadikannya sulit untuk diimplementasikan dalam sistem nyata. Selain itu, kelaparan proses-proses panjang menjadi perhatian utama yang perlu diatasi dengan mekanisme tambahan seperti aging atau mengombinasikannya dengan algoritma penjadwalan lain.

Implementasi yang dianalisis menunjukkan simulasi SRTF yang efektif, tetapi dalam pengembangan sistem operasi modern, pendekatan hibrida dan mekanisme estimasi yang lebih canggih biasanya digunakan untuk mencapai keseimbangan antara efisiensi, keadilan, dan kepraktisan.
