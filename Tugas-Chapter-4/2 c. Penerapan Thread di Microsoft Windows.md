# Penerapan Thread di Microsoft Windows (thrd-win32.c)

## Pendahuluan

Microsoft Windows mengimplementasikan threading melalui Windows API, yang menyediakan sekumpulan fungsi untuk pembuatan dan pengelolaan thread. Berbeda dengan POSIX threads di Linux, Windows API memiliki pendekatan yang unik dalam menangani konkurensi. File `thrd-win32.c` mendemonstrasikan implementasi dasar thread di Windows yang melakukan perhitungan jumlah dari 0 hingga nilai integer yang diberikan.

## Analisis Kode `thrd-win32.c`

Mari kita analisis kode `thrd-win32.c` secara terperinci:

### 1. Header Files dan Deklarasi Variabel Global

```c
#include <stdio.h>
#include <windows.h>

DWORD Sum; /* data is shared by the thread(s) */
```

- `windows.h` adalah header file utama yang berisi definisi, fungsi, dan tipe data untuk Windows API
- `Sum` adalah variabel global bertipe `DWORD` (32-bit unsigned integer di Windows) yang akan diakses oleh thread untuk menyimpan hasil penjumlahan

### 2. Fungsi Thread `Summation()`

```c
DWORD WINAPI Summation(PVOID Param)
{
    DWORD Upper = *(DWORD *)Param;

    for (DWORD i = 0; i <= Upper; i++)
        Sum += i;

    return 0;
}
```

Fungsi `Summation()` adalah fungsi yang akan dijalankan oleh thread:

1. **Deklarasi Fungsi**: 
   - `DWORD WINAPI`: Menentukan tipe return dan calling convention khusus Windows
   - `PVOID Param`: Parameter generic (void pointer) yang akan diteruskan ke thread

2. **Konversi Parameter**:
   - `DWORD Upper = *(DWORD *)Param`: Mengonversi void pointer ke DWORD melalui type casting

3. **Perhitungan**:
   - Melakukan penjumlahan dari 0 hingga `Upper` dan menyimpan hasilnya di variabel global `Sum`

4. **Return Value**:
   - Mengembalikan 0 untuk menandakan keberhasilan eksekusi

### 3. Fungsi `main()`

```c
int main(int argc, char *argv[])
{
    DWORD ThreadId;
    HANDLE ThreadHandle;
    int Param;

    // do some basic error checking
    if (argc != 2) {
        fprintf(stderr,"An integer parameter is required\n");
        return -1;
    }

    Param = atoi(argv[1]);

    if (Param < 0) {
        fprintf(stderr, "an integer >= 0 is required \n");
        return -1;
    }

    // create the thread
    ThreadHandle = CreateThread(NULL, 0, Summation, &Param, 0, &ThreadId);

    if (ThreadHandle != NULL) {
        WaitForSingleObject(ThreadHandle, INFINITE);
        CloseHandle(ThreadHandle);
        printf("sum = %d\n",Sum);
    }
}
```

Fungsi `main()` melakukan beberapa langkah penting:

1. **Deklarasi Variabel Thread**:
   - `DWORD ThreadId`: Variabel untuk menyimpan identifier thread
   - `HANDLE ThreadHandle`: Handle untuk thread (abstraksi Windows untuk resource system)

2. **Validasi Input**:
   - Memastikan program menerima tepat satu argumen
   - Memastikan argumen tersebut merupakan bilangan non-negatif

3. **Pembuatan Thread**:
   - `CreateThread(NULL, 0, Summation, &Param, 0, &ThreadId)`:
     - Parameter 1: Security attributes (NULL untuk default)
     - Parameter 2: Stack size (0 untuk default)
     - Parameter 3: Fungsi thread yang akan dijalankan
     - Parameter 4: Parameter untuk fungsi thread
     - Parameter 5: Creation flags (0 untuk thread yang langsung dijalankan)
     - Parameter 6: Pointer ke variabel yang akan menerima thread ID

4. **Menunggu Thread Selesai**:
   - `WaitForSingleObject(ThreadHandle, INFINITE)`: Menunggu thread hingga selesai
   - INFINITE menunjukkan bahwa fungsi akan menunggu tanpa batasan waktu

5. **Membersihkan Resource**:
   - `CloseHandle(ThreadHandle)`: Melepaskan handle thread dan resource terkait

6. **Menampilkan Hasil**:
   - Setelah thread selesai, nilai `Sum` dicetak

## Konsep Penting dalam Threading Windows

### 1. Model Threading di Windows

Windows implementasi threading menggunakan model kernel-level threading, di mana setiap thread pengguna dipetakan ke satu thread kernel. Keunggulan model ini meliputi:

- Paralelisme sejati pada sistem multiprocessor
- Penanganan kode kernel secara efisien
- Akses ke fitur kernel sistem operasi

### 2. Windows Thread Objects

Thread di Windows direpresentasikan sebagai objek kernel yang diidentifikasi dengan `HANDLE`:

- Thread handle memungkinkan kontrol terhadap thread
- Thread ID bersifat unik dan digunakan untuk identifikasi thread
- Thread state dikelola oleh sistem operasi

### 3. Thread Priority dan Scheduling

Windows mendukung kontrol terperinci terhadap prioritas thread:

- Prioritas thread menentukan kapan thread dijadwalkan oleh CPU
- Kelas prioritas proses dan nilai prioritas thread menentukan prioritas absolut
- Windows scheduler mendukung preemptive multitasking

### 4. Thread Local Storage (TLS)

Windows mendukung Thread Local Storage untuk penyimpanan data yang unik per thread:

- Setiap thread dapat memiliki data privatnya sendiri
- TLS memungkinkan fungsi global mengakses data spesifik thread
- Mencegah race condition dalam akses data

### 5. Thread Synchronization

Windows menyediakan berbagai mekanisme sinkronisasi:

- **Critical Sections**: Sinkronisasi ringan untuk thread dalam satu proses
- **Mutex**: Mutual exclusion object untuk sinkronisasi antar proses
- **Semaphores**: Kontrol akses ke resource terbatas
- **Events**: Notifikasi antar thread/proses
- **Condition Variables**: Untuk skenario producer-consumer

## Perbedaan Utama dengan POSIX Threads

| Aspek | Windows Thread | POSIX Thread |
|-------|---------------|-------------|
| API | Windows API | POSIX API |
| Fungsi Pembuatan | CreateThread() | pthread_create() |
| Fungsi Pengakhiran | ExitThread() | pthread_exit() |
| Sinkronisasi | Critical Sections, Mutex, Semaphore, Event | Mutex, Condition Variables, Read-Write Locks |
| Thread ID | DWORD | pthread_t |
| Atribut Thread | Parameter di CreateThread() | pthread_attr_t |
| Penanganan Error | GetLastError() | Return nilai fungsi |
| Portabilitas | Windows-specific | Cross-platform di sistem UNIX-like |

## Langkah-langkah Eksekusi Program

1. Kompilasi program:
   ```bash
   cl thrd-win32.c
   ```

2. Jalankan program dengan argumen bilangan positif:
   ```bash
   thrd-win32.exe 10
   ```

3. Program akan membuat thread untuk menghitung jumlah dari 0 hingga 10
4. Thread utama akan menunggu thread tersebut selesai
5. Setelah thread selesai, hasil perhitungan (55) akan ditampilkan

## Keunggulan dan Tantangan Thread di Windows

### Keunggulan

1. **Integrasi dengan Sistem**: Thread Windows terintegrasi sangat baik dengan ekosistem Windows
2. **Fitur Lanjutan**: Mendukung fitur-fitur seperti thread pooling, fiber, dan I/O completion ports
3. **Debugging Tools**: Windows menyediakan alat debugging thread yang kuat seperti WinDbg
4. **Manajemen Resource**: Penanganan resource otomatis melalui HANDLE

### Tantangan

1. **Kompleksitas API**: Windows API cenderung lebih kompleks dibandingkan POSIX
2. **Error Handling**: Penanganan error di Windows menggunakan kode error global
3. **Portabilitas**: Kode thread Windows tidak bisa dijalankan di sistem non-Windows
4. **Memory Management**: Pengelolaan memori yang lebih manual

## Pengembangan Lebih Lanjut

Contoh dasar ini dapat dikembangkan untuk aplikasi yang lebih kompleks dengan menambahkan:

1. **Thread Pools**: Menggunakan kumpulan thread untuk menangani beberapa tugas
2. **Asynchronous I/O**: Menggabungkan thread dengan operasi I/O asinkron
3. **Fiber**: Menggunakan fiber (user-mode schedulable unit) untuk konkurensi cooperative
4. **I/O Completion Ports**: Untuk aplikasi dengan konkurensi I/O yang tinggi

## Kesimpulan

Contoh `thrd-win32.c` mendemonstrasikan implementasi dasar threading di Windows menggunakan Windows API. Meskipun memiliki tujuan yang sama dengan implementasi POSIX threads, pendekatan Windows memiliki karakteristik unik yang mencerminkan arsitektur sistem operasi yang berbeda.

Windows API menawarkan pendekatan yang komprehensif untuk threading, dengan integrasi yang kuat dengan fitur-fitur Windows lainnya. Meskipun kurang portabel dibandingkan POSIX threads, Windows threads lebih unggul dalam konteks pengembangan aplikasi Windows native, terutama untuk aplikasi yang membutuhkan akses ke fitur-fitur Windows-specific.

Memahami perbedaan antara implementasi thread di berbagai platform sangatlah penting bagi pengembang yang bekerja di lingkungan heterogen atau yang membutuhkan portabilitas antar sistem operasi.
