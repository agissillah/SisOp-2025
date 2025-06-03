# Penerapan Thread pada Berbagai Platform

## 1. Penerapan Thread pada Contoh SumTask.java

SumTask.java mengimplementasikan threading di Java menggunakan framework Fork/Join, sebuah kerangka kerja untuk komputasi paralel yang diperkenalkan pada Java 7. Framework ini dirancang khusus untuk tugas yang dapat dibagi menjadi bagian-bagian lebih kecil dan diproses secara paralel.

### Konsep Dasar Fork/Join

Fork/Join mengikuti paradigma "divide and conquer" dengan langkah-langkah:
1. **Fork**: Membagi masalah menjadi sub-masalah yang lebih kecil
2. **Compute**: Menyelesaikan sub-masalah secara paralel
3. **Join**: Menggabungkan hasil dari sub-masalah

### Implementasi dalam SumTask.java

```java
public class SumTask extends RecursiveTask<Integer>
{
    static final int SIZE = 10000;
    static final int THRESHOLD = 1000;

    private int begin;
    private int end;
    private int[] array;

    public SumTask(int begin, int end, int[] array) {
        this.begin = begin;
        this.end = end;
        this.array = array;
    }

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
}
```

### Analisis Kode:

1. **Kelas Dasar**: `SumTask` memperluas `RecursiveTask<Integer>`, bukan mengimplementasikan `Runnable` seperti pada thread tradisional. `RecursiveTask` memungkinkan metode mengembalikan nilai.

2. **Metode compute()**: Jantung implementasi threading, berisi logika untuk:
   - **Kasus dasar**: Jika ukuran data di bawah THRESHOLD, hitung sum secara langsung
   - **Kasus rekursif**: Jika ukuran data besar, bagi menjadi dua subtask dan proses secara paralel

3. **Fork dan Join Operations**:
   - `leftTask.fork()` dan `rightTask.fork()` memulai eksekusi asinkron dari subtask
   - `rightTask.join()` dan `leftTask.join()` menunggu hingga subtask selesai dan mengambil hasilnya

4. **ForkJoinPool**: Pool thread khusus yang mengelola thread worker untuk tugas Fork/Join:
   ```java
   ForkJoinPool pool = new ForkJoinPool();
   int sum = pool.invoke(task);
   ```

### Keunggulan Pendekatan Fork/Join:

1. **Work-Stealing Algorithm**: Thread yang menganggur dapat "mencuri" tugas dari thread lain yang sedang sibuk, meningkatkan efisiensi
2. **Pembagian Tugas Otomatis**: Framework menangani pembagian pekerjaan secara otomatis
3. **Skalabilitas**: Dapat memanfaatkan semua core CPU yang tersedia
4. **API Level Tinggi**: Menyembunyikan kompleksitas manajemen thread dari developer

## 2. Penerapan Thread di Linux (thrd-posix.c)

Linux mengimplementasikan thread menggunakan POSIX Threads (Pthreads), sebuah standar IEEE untuk pemrograman thread pada sistem UNIX/Linux.

### Karakteristik Pthread:

1. **API Native C**: Pthread diimplementasikan sebagai library C
2. **Kernel-Level Threading**: Thread dikelola oleh kernel Linux
3. **Portabilitas**: Bekerja di berbagai sistem UNIX-like

### Implementasi Dasar:

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum = 0; // Shared variable

// Thread function
void *runner(void *param) {
    int upper = *((int *)param);
    for (int i = 1; i <= upper; i++)
        sum += i;
    
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t tid; // Thread identifier
    pthread_attr_t attr; // Thread attributes
    
    // Set thread attributes
    pthread_attr_init(&attr);
    
    int upper = atoi(argv[1]);
    
    // Create the thread
    pthread_create(&tid, &attr, runner, &upper);
    
    // Wait for the thread to exit
    pthread_join(tid, NULL);
    
    printf("sum = %d\n", sum);
    
    return 0;
}
```

### Komponen Utama:

1. **pthread_t**: Tipe data yang menyimpan ID thread
2. **pthread_attr_t**: Struktur yang menyimpan atribut thread
3. **pthread_create()**: Membuat thread baru dan menjalankannya
4. **pthread_join()**: Menunggu thread tertentu selesai
5. **pthread_exit()**: Mengakhiri thread

### Langkah-langkah Pembuatan Thread:

1. Deklarasi variabel pthread_t untuk menyimpan ID thread
2. Inisialisasi atribut thread dengan pthread_attr_init()
3. Buat thread dengan pthread_create()
4. Tunggu thread selesai dengan pthread_join()

### Manajemen Resource:

- Thread berbagi ruang alamat proses induk
- Sinkronisasi diimplementasikan menggunakan mutex, semaphore, atau condition variables
- Thread dapat memiliki data private menggunakan thread-local storage

## 3. Penerapan Thread di Microsoft Windows (thrd-win32.c)

Windows mengimplementasikan thread menggunakan Windows API, yang berbeda dari POSIX threads baik dalam sintaks maupun perilaku.

### Karakteristik Thread Windows:

1. **Win32 API**: Menggunakan fungsi-fungsi API Windows
2. **Kernel-Level Threading**: Thread dikelola oleh kernel Windows
3. **HANDLE-Based**: Thread diidentifikasi menggunakan HANDLE

### Implementasi Dasar:

```c
#include <windows.h>
#include <stdio.h>

DWORD sum = 0; // Shared variable

// Thread function
DWORD WINAPI SumFunc(LPVOID param) {
    DWORD upper = *(DWORD*)param;
    
    for (DWORD i = 1; i <= upper; i++)
        sum += i;
    
    return 0;
}

int main(int argc, char *argv[]) {
    DWORD upper = atoi(argv[1]);
    DWORD threadId;
    HANDLE threadHandle;
    
    // Create the thread
    threadHandle = CreateThread(
        NULL,                   // Default security attributes
        0,                      // Default stack size
        SumFunc,                // Thread function
        &upper,                 // Parameter to thread function
        0,                      // Default creation flags
        &threadId               // Returns the thread identifier
    );
    
    // Wait for the thread to finish
    WaitForSingleObject(threadHandle, INFINITE);
    
    // Close the thread handle
    CloseHandle(threadHandle);
    
    printf("sum = %lu\n", sum);
    
    return 0;
}
```

### Komponen Utama:

1. **HANDLE**: Nilai yang mengidentifikasi thread
2. **DWORD WINAPI**: Konvensi pemanggilan untuk fungsi thread
3. **CreateThread()**: Menciptakan thread baru
4. **WaitForSingleObject()**: Menunggu thread selesai
5. **CloseHandle()**: Melepaskan resource system

### Langkah-langkah Pembuatan Thread:

1. Deklarasi variabel HANDLE untuk threadHandle
2. Buat thread dengan CreateThread()
3. Tunggu thread selesai dengan WaitForSingleObject()
4. Lepaskan resource dengan CloseHandle()

### Manajemen Resource:

- Thread berbagi ruang alamat proses induk
- Sinkronisasi menggunakan object kernel seperti mutex, semaphore, event, dll.
- Thread dapat memiliki data private menggunakan Thread Local Storage (TLS)

## Perbandingan Implementasi Thread

| Aspek | Java (SumTask.java) | Linux (Pthread) | Windows |
|-------|---------------------|-----------------|---------|
| API Level | Tingkat tinggi | Menengah | Menengah |
| Portabilitas | Sangat tinggi | Tinggi (sistem UNIX) | Terbatas (Windows) |
| Syntax | Object-oriented | Procedural (C) | Procedural (C) |
| Abstraksi | Fork/Join | Native threads | Native threads |
| Manajemen Memory | Otomatis | Manual | Manual |
| Sinkronisasi | Built-in | Primitif sinkronisasi | Object kernel |
| Keunggulan | Mudah digunakan, portabel | Performa, kontrol lebih baik | Integrasi dengan Windows |

## Kesimpulan

Ketiga implementasi thread menunjukkan pendekatan berbeda untuk masalah konkurensi, masing-masing dengan kelebihan dan kekurangan:

- **Java SumTask** menyediakan abstraksi tingkat tinggi melalui framework Fork/Join, menyembunyikan kompleksitas manajemen thread dan fokus pada pembagian tugas rekursif.

- **POSIX Thread** di Linux menawarkan kontrol lebih detail dengan overhead minimal, cocok untuk aplikasi sistem atau kinerja tinggi.

- **Windows Thread** mengintegrasikan threading dengan arsitektur Windows, memberikan akses ke fitur-fitur khusus Windows tetapi mengorbankan portabilitas.

Pemilihan implementasi thread sebaiknya berdasarkan kebutuhan aplikasi, platform target, dan pertimbangan performa. Java menawarkan kemudahan pengembangan, sementara implementasi native (POSIX dan Windows) memberikan kontrol dan performa yang lebih baik dengan kompleksitas yang lebih tinggi.
