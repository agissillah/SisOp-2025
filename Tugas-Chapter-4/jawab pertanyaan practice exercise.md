# Jawaban Practice Exercises Chapter 4: Threads & Concurrency

## 4.1 Tiga Contoh Pemrograman Multithreading yang Lebih Efisien
1. **Server Web**  
   - **Contoh**: Server web menangani banyak permintaan klien secara bersamaan.  
   - **Keuntungan**: Setiap thread menangani satu permintaan, meningkatkan throughput dan mengurangi latency.  

2. **Pemrosesan Gambar**  
   - **Contoh**: Aplikasi pembuat thumbnail dari koleksi gambar.  
   - **Keuntungan**: Setiap thread memproses gambar secara paralel, mempercepat eksekusi.  

3. **Aplikasi dengan Antarmuka Pengguna (UI)**  
   - **Contoh**: Pengolah kata yang memeriksa ejaan di latar belakang.  
   - **Keuntungan**: UI tetap responsif saat tugas berat dijalankan di thread terpisah.

---

## 4.2 Perhitungan Speedup Menggunakan Hukum Amdahl
**Rumus**:  
\[ \text{Speedup} \leq \frac{1}{S + \frac{(1-S)}{N}} \]  
Dimana:  
- \( S \) = bagian serial (60% atau 0.6)  
- \( N \) = jumlah core  

### (a) Dua Core (\( N = 2 \))  
\[ \text{Speedup} \leq \frac{1}{0.6 + \frac{0.4}{2}} = \frac{1}{0.6 + 0.2} = 1.25 \times \]  

### (b) Empat Core (\( N = 4 \))  
\[ \text{Speedup} \leq \frac{1}{0.6 + \frac{0.4}{4}} = \frac{1}{0.6 + 0.1} \approx 1.43 \times \]  

---

## 4.3 Jenis Paralelisme pada Multithreaded Web Server
- **Task Parallelism**  
  Server menggunakan thread terpisah untuk menangani setiap permintaan klien, di mana setiap thread menjalankan tugas yang independen (misalnya, memproses HTTP request).

---

## 4.4 Perbedaan User-Level Threads vs Kernel-Level Threads
| **Aspek**               | **User-Level Threads**                          | **Kernel-Level Threads**                     |
|-------------------------|------------------------------------------------|---------------------------------------------|
| **Manajemen**           | Ditangani library pengguna (contoh: Pthreads)  | Ditangani langsung oleh OS                  |
| **Overhead**            | Rendah (tidak butuh system call)               | Tinggi (butuh system call)                  |
| **Blokir Sistem**       | Seluruh proses terblokir jika satu thread blokir | Thread lain tetap berjalan                  |
| **Contoh Penggunaan**   | Aplikasi dengan banyak tugas ringan            | Aplikasi yang butuh skalabilitas pada multicore |

**Kapan Memilih?**  
- **User-Level**: Cocok untuk aplikasi dengan banyak thread dan minim interaksi kernel.  
- **Kernel-Level**: Cocok untuk aplikasi yang membutuhkan paralelisme sejati (misalnya, pada CPU multicore).

---

## 4.5 Langkah-Langkah Context Switch Kernel-Level Threads
1. **Simpan Konteks**: Simpan register, PC, dan state thread yang sedang berjalan.  
2. **Update PCB**: Simpan info thread ke Process Control Block (PCB).  
3. **Jadwalkan Thread Baru**: Pilih thread berikutnya dari ready queue.  
4. **Restore Konteks**: Muat register, PC, dan state thread baru dari PCB-nya.  
5. **Lanjutkan Eksekusi**: Thread baru dijalankan.

---

## 4.6 Sumber Daya untuk Pembuatan Thread vs Proses
| **Sumber Daya**       | **Thread**                          | **Proses**                          |
|-----------------------|------------------------------------|------------------------------------|
| **Memori**            | Hanya stack kecil (MB)             | Heap, data segment, stack (GB)     |
| **PCB**               | Tidak ada PCB terpisah             | PCB lengkap                        |
| **Resource Sharing**  | Berbagi memori proses induk        | Isolasi memori (tidak berbagi)     |

**Contoh**:  
- Thread hanya butuh alokasi stack dan register.  
- Proses butuh alokasi memori independen, file descriptor, dll.

---

## 4.7 Real-Time Threads dan LWP pada Many-to-Many Model
- **Perlu Binding ke LWP?** **Ya**.  
- **Alasan**:  
  Thread real-time membutuhkan jaminan deterministik (contoh: prioritas tinggi). Dengan membinding ke LWP, kernel bisa menjadwalkannya langsung ke core fisik, menghindari penundaan akibat multiplexing.