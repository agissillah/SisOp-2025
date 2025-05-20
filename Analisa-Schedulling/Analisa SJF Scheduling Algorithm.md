# Analisis Algoritma SJF Dengan Waktu Kedatangan (Non-Preemptive)

## Deskripsi Algoritma

Algoritma penjadwalan Shortest Job First (SJF) dengan waktu kedatangan (non-preemptive) bekerja sebagai berikut:

1. Proses-proses memiliki waktu kedatangan yang bervariasi
2. CPU menjadwalkan proses berdasarkan waktu burst terpendek di antara proses-proses yang sudah tiba
3. Setelah proses mulai dieksekusi, proses tersebut akan berjalan hingga selesai (non-preemptive)
4. Ketika proses selesai, CPU memilih proses dengan waktu burst terpendek dari proses-proses yang telah tiba namun belum dieksekusi

## Komponen Utama Kode

Implementasi yang diberikan:

- Menggunakan struktur `proc` untuk menyimpan detail proses:
  - `no`: Nomor proses
  - `at`: Arrival time (waktu kedatangan)
  - `bt`: Burst time (waktu eksekusi)
  - `it`: Initial time (waktu mulai eksekusi)
  - `ct`: Completion time (waktu penyelesaian)
  - `tat`: Turnaround time (waktu turnaround)
  - `wt`: Waiting time (waktu tunggu)
- Mengurutkan proses berdasarkan waktu kedatangan menggunakan bubble sort
- Memilih proses dengan burst time terpendek di antara proses-proses yang telah tiba
- Menghitung waktu penyelesaian, waktu turnaround, dan waktu tunggu untuk setiap proses
- Menghitung dan menampilkan rata-rata waktu turnaround dan waktu tunggu

## Alur Eksekusi

1. Pengguna memasukkan jumlah proses, waktu kedatangan, dan waktu burst mereka
2. Proses diurutkan berdasarkan waktu kedatangan (arrival time)
3. Jika beberapa proses tiba pada waktu yang sama dengan proses pertama, pilih yang memiliki burst time terkecil
4. Untuk proses berikutnya:
   - Identifikasi semua proses yang telah tiba (arrival time ≤ completion time proses sebelumnya)
   - Pilih proses dengan burst time terkecil dari kumpulan tersebut
   - Jika tidak ada proses yang telah tiba, CPU menganggur hingga proses berikutnya tiba
5. Untuk setiap proses, algoritma menghitung:
   - Initial time (IT) = max(AT, CT dari proses sebelumnya)
   - Completion time (CT) = IT + BT
   - Turnaround time (TAT) = CT - AT
   - Waiting time (WT) = TAT - BT
   - Response time (RT) = WT (dalam implementasi ini)

## Analisis Lebih Lanjut

### Langkah-langkah Detail Algoritma

1. Urutkan semua proses berdasarkan waktu kedatangan
2. Untuk proses pertama (atau beberapa proses yang tiba secara bersamaan di awal):
   - Jika beberapa proses tiba pada waktu yang sama, pilih yang memiliki burst time terkecil
   - Jadwalkan proses ini untuk dieksekusi pertama
3. Untuk setiap langkah penjadwalan berikutnya:
   - Identifikasi semua proses yang telah tiba tetapi belum dieksekusi
   - Dari kumpulan proses tersebut, pilih yang memiliki burst time terkecil
   - Jika tidak ada proses yang tersedia, CPU menganggur hingga proses berikutnya tiba

### Implementasi Kode Detail

```
1. Input jumlah proses n
2. Input arrival time dan burst time untuk setiap proses
3. Urutkan proses berdasarkan arrival time (ascending)
4. Pilih proses pertama (jika beberapa proses memiliki arrival time sama, pilih yang memiliki burst time terkecil)
5. Untuk i=1 hingga n-1:
   a. Identifikasi semua proses j dimana j>i dan arrival time[j] <= completion time[i-1]
   b. Pilih proses dengan burst time terkecil dari kumpulan tersebut
   c. Jika ada proses tersebut, tukar dengan posisi i
   d. Jika arrival time[i] <= completion time[i-1]
      initial time[i] = completion time[i-1]
   Jika tidak
      initial time[i] = arrival time[i]
   e. completion time[i] = initial time[i] + burst time[i]
6. Hitung turnaround time dan waiting time untuk setiap proses
7. Hitung rata-rata turnaround time dan waiting time
8. Tampilkan hasil
```

## Kelebihan SJF dengan Waktu Kedatangan

- Meminimalkan waktu tunggu rata-rata dibandingkan dengan algoritma FCFS
- Mempertimbangkan waktu kedatangan sehingga lebih realistis untuk sistem nyata
- Menangani kasus di mana proses tiba pada waktu yang berbeda
- Dapat mengurangi waktu respons sistem secara keseluruhan

## Keterbatasan Implementasi

1. Masih bersifat non-preemptive, sehingga proses panjang yang sudah mulai dieksekusi akan menunda proses pendek yang baru tiba
2. Implementasi bubble sort untuk mengurutkan proses tidak efisien untuk dataset yang besar
3. Dalam kode ini, response time (RT) dihitung sama dengan waiting time (WT), yang mungkin tidak sesuai definisi standar (RT seharusnya waktu dari kedatangan hingga pertama kali dieksekusi)
4. Tetap membutuhkan pengetahuan tentang waktu burst di awal, yang sulit dalam sistem nyata

## Implikasi Kinerja

SJF dengan waktu kedatangan memiliki karakteristik kinerja:

- Lebih realistis dibandingkan SJF tanpa waktu kedatangan
- Dapat menyebabkan kelaparan (starvation) untuk proses dengan burst time panjang jika proses-proses pendek terus berdatangan
- Dalam implementasi non-preemptive, proses pendek yang baru tiba harus menunggu proses yang sedang berjalan selesai
- Dalam sistem nyata, membutuhkan algoritma estimasi untuk memprediksi burst time

## Contoh Kasus

Misalkan terdapat 4 proses dengan detail berikut:
- P1: AT=0, BT=6
- P2: AT=1, BT=3
- P3: AT=2, BT=8
- P4: AT=3, BT=2

Pelaksanaan:
1. Pada t=0, hanya P1 yang tersedia. P1 mulai dieksekusi.
2. P1 selesai pada t=6. Pada titik ini, P2, P3, dan P4 semua telah tiba.
   Dari ketiganya, P4 memiliki BT terkecil, sehingga dieksekusi berikutnya.
3. P4 selesai pada t=8. P2 dan P3 tersedia; P2 memiliki BT lebih kecil.
4. P2 selesai pada t=11. Hanya P3 yang tersisa.
5. P3 selesai pada t=19.

| Proses | AT | BT | IT | CT | TAT | WT |
|--------|----|----|----|----|-----|----| 
| P1     | 0  | 6  | 0  | 6  | 6   | 0  |
| P4     | 3  | 2  | 6  | 8  | 5   | 3  |
| P2     | 1  | 3  | 8  | 11 | 10  | 7  |
| P3     | 2  | 8  | 11 | 19 | 17  | 9  |

Rata-rata TAT = (6 + 5 + 10 + 17) / 4 = 9.5
Rata-rata WT = (0 + 3 + 7 + 9) / 4 = 4.75

## Perbandingan dengan SJF Tanpa Waktu Kedatangan

| Aspek | SJF Tanpa Waktu Kedatangan | SJF Dengan Waktu Kedatangan |
|-------|----------------------------|------------------------------|
| Asumsi | Semua proses tiba pada waktu 0 | Proses tiba pada waktu berbeda |
| Kompleksitas | Lebih sederhana | Lebih kompleks |
| Realisme | Kurang realistis | Lebih realistis |
| Implementasi | Lebih mudah | Lebih sulit |
| Optimalisasi | Optimal untuk proses bersamaan | Optimal dengan pertimbangan waktu kedatangan |

## Kesimpulan

Algoritma SJF dengan waktu kedatangan merupakan peningkatan dari SJF tanpa waktu kedatangan karena lebih mencerminkan kondisi nyata di mana proses tidak selalu tersedia secara bersamaan. Implementasi non-preemptive tetap memiliki keterbatasan karena proses panjang yang telah mulai dieksekusi tidak dapat diinterupsi oleh proses pendek yang baru tiba. Untuk mengatasi keterbatasan tersebut, versi preemptive dari algoritma ini (SRTF - Shortest Remaining Time First) lebih disarankan dalam lingkungan yang memerlukan waktu respons yang lebih baik.

Tantangan utama dalam mengimplementasikan algoritma SJF dalam sistem nyata adalah kesulitan dalam memperkirakan waktu burst sebelum eksekusi. Oleh karena itu, sistem operasi modern sering menggunakan pendekatan heuristik untuk memperkirakan waktu burst berdasarkan riwayat eksekusi proses sebelumnya.