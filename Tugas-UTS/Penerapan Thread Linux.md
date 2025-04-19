# Penerapan Thread di Linux (thrd-posix.c)

## Pendahuluan

Sistem operasi Linux mengimplementasikan thread melalui POSIX Threads (Pthreads), sebuah standar API untuk pemrograman multithreading. File `thrd-posix.c` merupakan contoh implementasi dasar thread di Linux yang melakukan perhitungan jumlah dari 1 hingga nilai integer yang diberikan. Dalam analisis ini, kita akan mengeksplorasi bagaimana thread diterapkan dalam lingkungan Linux menggunakan kode contoh tersebut.

## Analisis Kode `thrd-posix.c`

Berikut adalah analisis langkah demi langkah dari kode `thrd-posix.c`:

### 1. Header Files dan Deklarasi Variabel Global

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */

void *runner(void *param); /* the thread */
```

- `pthread.h` adalah header file yang berisi definisi fungsi dan tipe data yang dibutuhkan untuk pemrograman POSIX threads
- `sum` adalah variabel global yang akan diakses oleh thread untuk menyimpan hasil penjumlahan
- `runner` adalah fungsi yang akan dijalankan oleh thread

### 2. Fungsi `main()`

```c
int main(int argc, char *argv[])
{
pthread_t tid; /* the thread identifier */
pthread_attr_t attr; /* set of attributes for the thread */

if (argc != 2) {
    fprintf(stderr,"usage: a.out <integer value>\n");
    /*exit(1);*/
    return -1;
}

if (atoi(argv[1]) < 0) {
    fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
    /*exit(1);*/
    return -1;
}

/* get the default attributes */
pthread_attr_init(&attr);

/* create the thread */
pthread_create(&tid, &attr, runner, argv[1]);

/* now wait for the thread to exit */
pthread_join(tid, NULL);

printf("sum = %d\n", sum);
}
```

Fungsi `main()` melakukan beberapa langkah penting:

1. **Deklarasi Variabel Thread**:
   - `pthread_t tid`: Variabel untuk menyimpan identifier thread
   - `pthread_attr_t attr`: Struktur untuk menyimpan atribut-atribut thread

2. **Validasi Input**:
   - Memastikan program menerima tepat satu argumen
   - Memastikan argumen tersebut merupakan bilangan non-negatif

3. **Inisialisasi Atribut Thread**:
   - `pthread_attr_init(&attr)`: Menginisialisasi atribut thread dengan nilai default

4. **Pembuatan Thread**:
   - `pthread_create(&tid, &attr, runner, argv[1])`: 
     - Parameter 1: Pointer ke thread ID
     - Parameter 2: Atribut thread
     - Parameter 3: Fungsi yang akan dijalankan
     - Parameter 4: Argumen untuk fungsi (nilai batas atas)

5. **Menunggu Thread Selesai**:
   - `pthread_join(tid, NULL)`: Menunggu thread dengan ID `tid` menyelesaikan eksekusinya
   - Program utama (main thread) akan diblokir sampai thread yang dibuat selesai

6. **Menampilkan Hasil**:
   - Setelah thread selesai, nilai `sum` dicetak

### 3. Fungsi Thread `runner()`

```c
void *runner(void *param) 
{
int i, upper = atoi(param);
sum = 0;

    if (upper > 0) {
        for (i = 1; i <= upper; i++)
            sum += i;
    }

    pthread_exit(0);
}
```

Fungsi `runner()` adalah fungsi yang dijalankan oleh thread:

1. **Konversi Parameter**:
   - `upper = atoi(param)`: Mengonversi parameter string menjadi integer

2. **Perhitungan**:
   - Melakukan penjumlahan dari 1 hingga `upper` dan menyimpan hasilnya di variabel global `sum`

3. **Terminasi Thread**:
   - `pthread_exit(0)`: Mengakhiri thread dengan status 0 (sukses)
   - Saat thread berakhir, kontrol akan kembali ke fungsi `main()` yang sedang menunggu di `pthread_join()`

## Konsep Penting dalam Pemrograman Thread POSIX

### 1. Model Thread di Linux

POSIX threads diimplementasikan di Linux menggunakan model 1:1, artinya setiap thread pengguna dipetakan ke satu thread kernel. Ini memberikan beberapa keuntungan:
- Paralelisme nyata pada sistem multiprosesor
- Thread yang terblokir tidak menghentikan thread lain
- Pemanfaatan multiple CPU cores

### 2. Atribut Thread

POSIX threads memungkinkan kustomisasi thread melalui atribut:
- **Stack Size**: Menentukan ukuran stack thread
- **Scheduling Policy**: Menentukan kebijakan penjadwalan thread (FIFO, Round Robin, dll.)
- **Priority**: Menentukan prioritas thread
- **Detach State**: Menentukan apakah thread berjalan dalam mode detached

### 3. Sinkronisasi Thread

Meskipun tidak digunakan dalam contoh ini, POSIX threads menyediakan beberapa mekanisme sinkronisasi:
- **Mutex (Mutual Exclusion)**: Untuk melindungi bagian kritis
- **Condition Variables**: Untuk komunikasi antar thread
- **Read-Write Locks**: Untuk skenario multiple reader/single writer
- **Barriers**: Untuk sinkronisasi titik pertemuan thread

### 4. Memori Bersama

Dalam contoh ini, `sum` adalah variabel global yang dapat diakses oleh semua thread. Ini menggambarkan model pemrograman thread di mana thread berbagi ruang alamat yang sama. Hal ini memungkinkan:
- Komunikasi mudah antar thread melalui memori bersama
- Potensi race condition jika tidak ada mekanisme sinkronisasi

## Langkah-langkah Eksekusi Program

1. Kompilasi program:
   ```bash
   gcc thrd-posix.c -lpthread -o thread_example
   ```

2. Jalankan program dengan argumen bilangan positif:
   ```bash
   ./thread_example 10
   ```

3. Program akan membuat thread untuk menghitung jumlah dari 1 hingga 10
4. Thread utama akan menunggu thread tersebut selesai
5. Setelah thread selesai, hasil perhitungan (55) akan ditampilkan

## Keunggulan dan Tantangan Thread di Linux

### Keunggulan

1. **Efisiensi Resource**: Thread berbagi sumber daya seperti memori dan file descriptor, menghasilkan overhead yang lebih rendah dibandingkan proses terpisah
2. **Paralelisme**: Memanfaatkan arsitektur multicore dengan menjalankan beberapa thread secara paralel
3. **Responsivitas**: Aplikasi dapat tetap responsif saat melakukan operasi yang membutuhkan waktu lama
4. **Berbagi Data**: Data dapat dibagikan antar thread tanpa mekanisme IPC yang kompleks

### Tantangan

1. **Race Conditions**: Akses bersamaan ke data bersama dapat menyebabkan hasil yang tidak terduga
2. **Deadlocks**: Thread yang saling menunggu dapat menyebabkan program terhenti
3. **Kompleksitas Debugging**: Bug terkait konkurensi sulit untuk direproduksi dan diperbaiki
4. **Overhead Sinkronisasi**: Mekanisme sinkronisasi dapat mengurangi keuntungan performa dari threading

## Kesimpulan

Contoh `thrd-posix.c` menunjukkan implementasi dasar threading di Linux menggunakan POSIX threads. Program ini menggambarkan konsep-konsep fundamental seperti pembuatan thread, pengelolaan atribut thread, eksekusi paralel, dan penggabungan thread. Meskipun sederhana, program ini menjadi dasar untuk pemahaman tentang pemrograman multithreading di lingkungan Linux.

POSIX threads menawarkan solusi standar, efisien, dan portabel untuk konkurensi di sistem UNIX-like. Dibandingkan dengan implementasi thread di platform lain seperti Java atau Windows, POSIX threads memberikan kontrol yang lebih detail dengan overhead yang minimal, menjadikannya pilihan yang baik untuk aplikasi sistem atau aplikasi yang membutuhkan kinerja tinggi.
