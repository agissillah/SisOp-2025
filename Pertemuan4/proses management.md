# Ringkasan 1.34 - 1.40

## **1.34 Transisi dari Mode Pengguna ke Mode Kernel**
- Sistem operasi menggunakan **timer** untuk mencegah proses berjalan tanpa batas.
- Timer disetel untuk menginterupsi komputer setelah periode waktu tertentu.
- OS menggunakan penghitung yang dikurangi oleh clock fisik.
- Jika penghitung mencapai nol, terjadi **interrupt**.
- Digunakan untuk mengendalikan proses yang berjalan terlalu lama atau melebihi batas waktu yang ditentukan.

## **1.35 Manajemen Proses**
- **Proses** adalah program yang sedang dieksekusi dan merupakan unit kerja dalam sistem.
- Proses memerlukan sumber daya seperti **CPU, memori, I/O, dan file** untuk menjalankan tugasnya.
- Jika proses berakhir, sumber daya yang digunakan harus dikembalikan.
- **Proses single-threaded** memiliki satu program counter, sedangkan **proses multi-threaded** memiliki satu program counter per thread.
- Sistem biasanya menjalankan banyak proses secara bersamaan dengan **multiplexing CPU**.

## **1.36 Aktivitas Manajemen Proses**
- OS bertanggung jawab untuk:
  - Membuat dan menghapus proses.
  - Menangguhkan dan melanjutkan proses.
  - Menyediakan mekanisme sinkronisasi dan komunikasi antarproses.
  - Menangani deadlock dalam sistem.

## **1.37 Manajemen Memori**
- Program yang dieksekusi harus dimuat ke dalam **memori**.
- OS bertanggung jawab untuk:
  - Melacak bagian memori yang sedang digunakan dan siapa yang menggunakannya.
  - Memutuskan proses dan data mana yang dimuat ke dalam memori.
  - Mengalokasikan dan membebaskan ruang memori sesuai kebutuhan.

## **1.38 Manajemen Sistem Berkas**
- OS menyediakan tampilan logis dari penyimpanan informasi dalam bentuk **file**.
- Setiap perangkat penyimpanan memiliki karakteristik unik, seperti kecepatan akses dan kapasitas.
- OS menangani:
  - Pembuatan dan penghapusan file serta direktori.
  - Mengelola hak akses pengguna.
  - Pemetaan file ke penyimpanan sekunder.
  - Backup data ke media penyimpanan yang stabil.

## **1.39 Manajemen Penyimpanan Massal**
- Hard disk digunakan untuk menyimpan data jangka panjang yang tidak dapat disimpan di memori utama.
- OS menangani:
  - **Mounting dan unmounting** perangkat penyimpanan.
  - Manajemen ruang kosong dan alokasi penyimpanan.
  - Penjadwalan disk untuk efisiensi akses data.
  - Partisi dan perlindungan data.
- Penyimpanan tersier seperti **optical storage dan magnetic tape** tetap memerlukan manajemen.

## **1.40 Caching**
- **Caching** adalah teknik menyimpan data sementara di penyimpanan yang lebih cepat untuk meningkatkan kinerja sistem.
- Data yang sering digunakan disalin dari penyimpanan lambat ke penyimpanan cepat (cache).
- Jika data yang dibutuhkan ada di cache, maka diambil langsung untuk mempercepat akses.
- Manajemen cache adalah tantangan utama dalam desain sistem, termasuk:
  - Ukuran cache yang optimal.
  - Kebijakan **penggantian cache** untuk memastikan efisiensi.
