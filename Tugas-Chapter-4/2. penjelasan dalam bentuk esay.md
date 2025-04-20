# Implementasi Thread pada Berbagai Platform: Java, Linux, dan Windows

Thread merupakan unit eksekusi dasar yang dikelola oleh penjadwal sistem operasi. Berbeda dengan proses, thread dalam satu proses berbagi ruang alamat dan resource lainnya. Implementasi thread dapat bervariasi antar platform dan bahasa pemrograman. Dalam esai ini, kita akan menganalisis implementasi thread pada tiga platform berbeda berdasarkan kode dari [repository GitHub osc10e](https://github.com/ferryastika/osc10e/tree/master/ch4): Java (dengan framework Fork/Join), Linux (dengan POSIX threads), dan Windows (dengan Windows API).

## Pemahaman Umum Thread

Thread atau lightweight process memungkinkan sebuah program menjalankan beberapa alur eksekusi secara bersamaan dalam satu proses. Setiap thread memiliki:
- Program counter
- Register set
- Stack

Sementara thread dalam satu proses berbagi:
- Code segment
- Data segment
- Resource lain seperti file descriptor dan signal handler

Multithreading memberikan beberapa keuntungan:
- Responsivitas aplikasi
- Efisiensi resource
- Pemanfaatan arsitektur multiprosesor
- Berbagi data lebih efisien dibandingkan komunikasi antar proses

## Implementasi Thread di Java (SumTask.java)

Java mengimplementasikan thread melalui dua pendekatan utama: menggunakan `Thread` class dan `Runnable` interface untuk thread dasar, atau framework khusus seperti Fork/Join untuk pengolahan paralel. Contoh [SumTask.java](https://github.com/ferryastika/osc10e/tree/master/ch4/SumTask.java) mendemonstrasikan penggunaan framework Fork/Join untuk menghitung jumlah elemen array secara paralel.

Framework Fork/Join, diperkenalkan di Java 7, sangat ideal untuk pola "divide and conquer" yang diterapkan pada masalah rekursif. Kerangka kerja ini menerapkan workload balancing dengan algoritma "work stealing", di mana thread yang menganggur dapat "mencuri" tugas dari thread yang masih sibuk.

```java
public class SumTask extends RecursiveTask<Integer>
{
    static final int SIZE = 10000;
    static final int THRESHOLD = 1000;

    private int begin;
    private int end;
    private int[] array;
    
    // ...konstruktor dan method lainnya...
    
    protected Integer compute() {
        if (end - begin < THRESHOLD) {
            // conquer stage 
            int sum = 0;
            for (int i = begin; i <= end; i++)
                sum += array[i];

            return sum;
        }
        else {
            // divide stage 
            int mid = begin + (end - begin) / 2;
            
            SumTask leftTask = new SumTask(begin, mid, array);
            SumTask rightTask = new SumTask(mid + 1, end, array);

            leftTask.fork();
            rightTask.fork();

            return rightTask.join() + leftTask.join();
        }
    }
    
    // ...method main dan lainnya...
}
```

Dalam contoh ini:

1. **Inheritance dari RecursiveTask**: `SumTask` memperluas `RecursiveTask<Integer>`, yang menyediakan kerangka untuk tugas yang mengembalikan hasil.

2. **Compute Method**: Method ini berisi logika utama yang mengimplementasikan strategi divide-and-conquer:
   - Jika ukuran array di bawah THRESHOLD, hitung sum secara langsung (conquer)
   - Jika tidak, bagi array menjadi dua bagian, buat dua subtask, dan proses secara paralel (divide)

3. **Fork dan Join Operations**:
   - `leftTask.fork()` dan `rightTask.fork()` memulai eksekusi asinkron dari subtask
   - `leftTask.join()` dan `rightTask.join()` menunggu hasil dari subtask dan menggabungkannya

4. **ForkJoinPool**: Di method `main()`, `ForkJoinPool` dibuat untuk mengelola thread worker:
   ```java
   ForkJoinPool pool = new ForkJoinPool();
   int sum = pool.invoke(task);
   ```

Framework Fork/Join menyediakan abstraksi tingkat tinggi yang menyembunyikan detail thread management, memungkinkan developer fokus pada pembagian tugas secara logis.

## Implementasi Thread di Linux (thrd-posix.c)

Linux mengimplementasikan thread melalui POSIX Threads (Pthreads), sebuah standar IEEE untuk pemrograman thread pada sistem UNIX-like. File [thrd-posix.c](https://github.com/ferryastika/osc10e/tree/master/ch4/thrd-posix.c) menunjukkan implementasi dasar pthread.

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */
    
    // ...validasi input...
    
    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the thread */
    pthread_create(&tid, &attr, runner, argv[1]);

    /* now wait for the thread to exit */
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
}

/**
 * The thread will begin control in this function
 */
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

Komponen penting dalam implementasi POSIX threads meliputi:

1. **Fungsi Thread**: Fungsi `runner()` berjalan dalam thread terpisah dan menerima parameter melalui pointer void.

2. **Thread Creation**: `pthread_create()` membuat thread baru dengan atribut tertentu. Parameter fungsi ini meliputi:
   - Pointer ke thread ID
   - Atribut thread
   - Fungsi yang akan dijalankan
   - Argumen untuk fungsi thread

3. **Thread Synchronization**: `pthread_join()` menunggu thread tertentu untuk menyelesaikan eksekusinya, mirip dengan `wait()` untuk proses.

4. **Thread Termination**: `pthread_exit()` mengakhiri thread dengan status tertentu.

5. **Shared Memory**: Variabel `sum` dapat diakses oleh semua thread dalam proses.

POSIX threads lebih "low-level" dibandingkan implementasi Java, memberikan kontrol detail atas thread tetapi memerlukan lebih banyak manajemen manual.

## Implementasi Thread di Windows (thrd-win32.c)

Windows mengimplementasikan thread melalui Windows API, yang memiliki pendekatan berbeda dari POSIX. File [thrd-win32.c](https://github.com/ferryastika/osc10e/tree/master/ch4/thrd-win32.c) mendemonstrasikan fitur dasar thread di Windows.

```c
#include <stdio.h>
#include <windows.h>

DWORD Sum; /* data is shared by the thread(s) */

/* the thread runs in this separate function */
DWORD WINAPI Summation(PVOID Param)
{
    DWORD Upper = *(DWORD *)Param;

    for (DWORD i = 0; i <= Upper; i++)
        Sum += i;

    return 0;
}

int main(int argc, char *argv[])
{
    DWORD ThreadId;
    HANDLE ThreadHandle;
    int Param;
    
    // ...validasi input...
    
    // create the thread
    ThreadHandle = CreateThread(NULL, 0, Summation, &Param, 0, &ThreadId);

    if (ThreadHandle != NULL) {
        WaitForSingleObject(ThreadHandle, INFINITE);
        CloseHandle(ThreadHandle);
        printf("sum = %d\n", Sum);
    }
}
```

Karakteristik utama thread Windows meliputi:

1. **Thread Function**: Fungsi `Summation()` menggunakan deklarasi `DWORD WINAPI` yang menunjukkan calling convention dan return type khusus Windows.

2. **Thread Parameters**: Parameter dilewatkan melalui pointer void, serupa dengan pthread.

3. **Thread Creation**: `CreateThread()` menciptakan thread baru dengan parameter:
   - Security attributes
   - Stack size
   - Fungsi thread
   - Parameter untuk fungsi thread
   - Creation flags
   - Pointer ke variabel untuk thread ID

4. **Thread Synchronization**: `WaitForSingleObject()` menunggu thread selesai, mirip dengan `pthread_join()`.

5. **Resource Management**: `CloseHandle()` melepaskan resource yang terkait dengan thread, penting untuk mencegah memory leak.

Windows thread API dirancang sesuai dengan filosofi Windows yang lebih berorientasi pada handle dan mendukung fitur khusus Windows seperti security descriptors dan COM.

## Perbandingan Implementasi Thread

Berikut adalah perbandingan ketiga implementasi thread:

| Aspek | Java (Fork/Join) | Linux (POSIX) | Windows |
|-------|------------------|---------------|---------|
| Level Abstraksi | Tinggi | Menengah | Menengah |
| Manajemen Thread | Otomatis | Manual | Manual |
| Tipe Thread | User dan Kernel level (JVM-dependent) | Kernel-level | Kernel-level |
| Portabilitas | Tinggi | Sistem UNIX-like | Windows-only |
| Berbagi Data | Melalui objek bersama | Memori global | Memori global |
| Sinkronisasi | synchronized, locks, barriers | Mutex, semaphore, condition variables | Critical sections, mutex, semaphores, events |
| Penanganan Error | Exception | Return values | GetLastError() |
| Work Load Balancing | Ya (work-stealing) | Tidak | Tidak |

## Analisis dan Kesimpulan

Ketiga implementasi thread memiliki pendekatan berbeda yang mencerminkan prioritas dan filosofi desain platform masing-masing:

1. **Java dengan Fork/Join** menawarkan abstraksi tingkat tinggi yang menyembunyikan kompleksitas manajemen thread. Ini memungkinkan developer fokus pada pemecahan masalah algoritmik tanpa harus mengkhawatirkan detail rendah thread. Implementasi ini sangat tepat untuk aplikasi yang membutuhkan paralelisme dan load balancing otomatis.

2. **POSIX threads (Linux)** memberikan kontrol langsung atas thread dengan overhead minimal. API yang sederhana dan langsung memungkinkan manajemen thread yang efisien tetapi membutuhkan perhatian detail dari pengembang. Pendekatan ini ideal untuk aplikasi sistem yang membutuhkan performa optimal.

3. **Windows threads** menawarkan integrasi mendalam dengan ekosistem Windows. API ini memungkinkan akses ke semua fitur spesifik Windows tetapi kurang portabel dibandingkan implementasi lainnya. Ini sangat cocok untuk pengembangan aplikasi Windows native.

Pilihan implementasi thread sebaiknya didasarkan pada kebutuhan aplikasi:
- Untuk aplikasi umum dengan abstraksi tinggi, Java Thread atau Fork/Join ideal
- Untuk aplikasi sistem UNIX dengan kinerja tinggi, POSIX threads lebih tepat
- Untuk aplikasi Windows native, Windows thread API adalah pilihan terbaik

Memahami perbedaan implementasi thread ini penting bagi pengembang untuk memilih teknologi yang tepat dan mengoptimalkan kinerja aplikasi multithread mereka.

## Referensi

1. [Repository GitHub OSC10e Chapter 4](https://github.com/ferryastika/osc10e/tree/master/ch4)
2. Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). Operating System Concepts (10th ed.). Wiley.
3. Java Documentation: Fork/Join Framework
4. POSIX Thread Programming Guide
5. Microsoft Documentation: Thread Functions (Windows)
