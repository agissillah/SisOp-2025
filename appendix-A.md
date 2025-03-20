**Nama**: Muhammad Aghiitsillah  
**Kelas**: Teknik Informatika A  
**NRP**: 3124521028  

Setelah memahami konsep dasar sistem operasi (seperti penjadwalan CPU, manajemen memori, proses, dan sebagainya), kita dapat melihat bagaimana konsep-konsep ini diterapkan dalam beberapa sistem operasi lama yang sangat berpengaruh. Beberapa sistem ini (seperti XDS-940 dan sistem THE) adalah sistem unik, sementara yang lain (seperti OS/360) digunakan secara luas. Urutan presentasi ini menekankan kesamaan dan perbedaan antara sistem-sistem tersebut, bukan berdasarkan kronologi atau tingkat kepentingan. Setiap mahasiswa yang serius mempelajari sistem operasi harus familiar dengan semua sistem ini.

## A.1 Migrasi Fitur

Salah satu alasan untuk mempelajari arsitektur dan sistem operasi lama adalah bahwa fitur yang sebelumnya hanya berjalan pada sistem besar mungkin suatu hari akan diterapkan pada sistem yang lebih kecil. Misalnya, banyak fitur yang awalnya hanya tersedia di mainframe telah diadopsi untuk mikrokomputer. Konsep sistem operasi yang sama berlaku untuk berbagai kelas komputer: mainframe, minikomputer, mikrokomputer, dan perangkat genggam. Untuk memahami sistem operasi modern, kita perlu mengenali tema migrasi fitur dan sejarah panjang dari banyak fitur sistem operasi.

Contoh migrasi fitur yang baik dimulai dengan sistem operasi **MULTICS** (Multiplexed Information and Computing Services). MULTICS dikembangkan pada tahun 1960-an sebagai sistem operasi yang sangat canggih untuk mainframe. Banyak fitur MULTICS, seperti manajemen memori virtual dan sistem file hierarkis, akhirnya diadopsi oleh sistem operasi modern seperti UNIX dan turunannya.

## A.2 Sistem Awal

Komputer awal adalah mesin fisik yang sangat besar yang dioperasikan dari konsol. Programmer, yang juga merupakan operator sistem, akan menulis program dan kemudian mengoperasikannya langsung dari konsol. Program dimuat secara manual ke memori melalui saklar panel depan, pita kertas, atau kartu berlubang. Setelah program dimuat, tombol yang sesuai akan ditekan untuk memulai eksekusi program. Jika terjadi kesalahan, programmer dapat menghentikan program, memeriksa isi memori dan register, dan melakukan debugging langsung dari konsol.

### A.2.1 Sistem Komputer Dedikasi

Seiring waktu, perangkat lunak dan perangkat keras tambahan dikembangkan. Pembaca kartu, pencetak baris, dan pita magnetik menjadi umum. Assembler, loader, dan linker dirancang untuk memudahkan tugas pemrograman. Perpustakaan fungsi umum dibuat, memungkinkan fungsi-fungsi tersebut digunakan kembali dalam program baru.

### A.2.2 Sistem Komputer Bersama

Untuk mengurangi waktu setup, operator komputer profesional dipekerjakan. Programmer tidak lagi mengoperasikan mesin secara langsung. Selain itu, pekerjaan dengan kebutuhan serupa dikelompokkan dan dijalankan sebagai batch untuk mengurangi waktu setup. Sistem batch dengan urutan pekerjaan otomatis dikembangkan, dan sistem operasi awal mulai muncul.

## A.3 Atlas

Sistem operasi **Atlas** dirancang di Universitas Manchester, Inggris, pada akhir 1950-an dan awal 1960-an. Banyak fitur dasarnya yang pada saat itu dianggap baru, kini menjadi bagian standar dari sistem operasi modern. Atlas menggunakan **spooling** untuk menjadwalkan pekerjaan berdasarkan ketersediaan perangkat periferal. Fitur paling menonjol dari Atlas adalah manajemen memorinya, yang menggunakan **demand paging** untuk mentransfer informasi antara memori inti dan drum secara otomatis.

## A.4 XDS-940

Sistem operasi **XDS-940** dirancang di Universitas California, Berkeley, pada awal 1960-an. Sistem ini menggunakan paging untuk manajemen memori, tetapi tidak untuk demand paging. XDS-940 adalah sistem **time-sharing**, di mana beberapa proses pengguna dapat berada di memori secara bersamaan. Sistem ini juga menyediakan panggilan sistem untuk membuat, memulai, menangguhkan, dan menghancurkan subproses.

## A.5 THE

Sistem operasi **THE** dirancang di Technische Hogeschool Eindhoven, Belanda, pada pertengahan 1960-an. Sistem ini adalah sistem batch yang terkenal karena desainnya yang bersih, terutama struktur lapisannya, dan penggunaan proses bersamaan dengan semaphore untuk sinkronisasi. THE juga menggunakan algoritma penjadwalan CPU berbasis prioritas dan skema paging perangkat lunak untuk manajemen memori.

## A.6 RC 4000

Sistem **RC 4000** dirancang pada akhir 1960-an untuk komputer Denmark 4000. Tujuannya adalah menciptakan inti sistem operasi (kernel) yang dapat digunakan untuk membangun sistem operasi lengkap. Kernel RC 4000 mendukung kumpulan proses bersamaan dan menggunakan sistem pesan untuk komunikasi dan sinkronisasi antar proses.

## A.7 CTSS

Sistem **CTSS** (Compatible Time-Sharing System) dirancang di MIT sebagai sistem time-sharing eksperimental dan pertama kali muncul pada tahun 1961. CTSS sangat sukses dan digunakan hingga tahun 1972. Sistem ini menggunakan algoritma penjadwalan CPU multilevel feedback queue dan memori virtual untuk mendukung banyak pengguna secara interaktif.

## A.8 MULTICS

Sistem **MULTICS** dirancang dari tahun 1965 hingga 1970 di MIT sebagai perluasan dari CTSS. MULTICS dirancang untuk menjadi sistem time-sharing yang besar dengan sistem file hierarkis dan manajemen memori virtual. Meskipun MULTICS tidak mencapai kesuksesan komersial, banyak fiturnya memengaruhi sistem operasi modern seperti UNIX.

## A.9 IBM OS/360

Sistem **OS/360** adalah sistem operasi yang dirancang untuk keluarga komputer IBM/360 pada pertengahan 1960-an. OS/360 mencoba menjadi sistem yang serba bisa, tetapi akhirnya tidak melakukan tugasnya dengan sangat baik. Sistem ini menggunakan manajemen memori berbasis register dan memiliki overhead yang tinggi. Versi OS/360 yang lebih baru menambahkan dukungan untuk memori virtual.

## A.10 TOPS-20

Sistem **TOPS-20** adalah sistem operasi time-sharing yang dikembangkan oleh DEC pada tahun 1970-an. TOPS-20 memiliki interpreter baris perintah yang canggih dan menjadi sistem time-sharing paling populer pada masanya. Sistem ini menggunakan manajemen memori virtual dan mendukung banyak pengguna secara bersamaan.

## A.11 CP/M dan MS-DOS

**CP/M** (Control Program/Monitor) adalah sistem operasi awal untuk komputer pribadi 8-bit seperti Intel 8080. **MS-DOS** (Microsoft Disk Operating System) adalah sistem operasi yang mirip dengan CP/M tetapi dirancang untuk CPU 16-bit seperti Intel 8086. MS-DOS menjadi sistem operasi paling populer untuk komputer pribadi pada masanya.

## A.12 Sistem Operasi Macintosh dan Windows

Sistem operasi **Macintosh** dan **Windows** adalah sistem operasi yang dirancang untuk komputer pribadi dengan antarmuka pengguna grafis (GUI). Macintosh OS adalah sistem operasi pertama dengan GUI yang dirancang untuk pengguna rumahan, sementara Windows menjadi sistem operasi yang dominan di pasar PC.

## A.13 Mach

Sistem operasi **Mach** dirancang di Carnegie Mellon University (CMU) pada pertengahan 1980-an. Mach dirancang untuk menjadi sistem operasi modern yang mendukung banyak model memori, komputasi paralel, dan terdistribusi. Mach menggunakan kernel mikro yang kecil dan mendukung emulasi sistem operasi lain di tingkat pengguna.

## A.14 Sistem Berbasis Kemampuan – Hydra dan CAP

**Hydra** dan **CAP** adalah sistem operasi berbasis kemampuan yang menyediakan fleksibilitas dalam implementasi kebijakan perlindungan. Hydra menggunakan kemampuan untuk mengontrol akses ke objek, sementara CAP menggunakan dua jenis kemampuan: data capability dan software capability.

## A.15 Sistem Lainnya

Ada banyak sistem operasi lain yang memiliki properti menarik, seperti **MCP** untuk keluarga komputer Burroughs dan **SCOPE** untuk CDC 6600. Sejarah sistem operasi penuh dengan sistem yang sesuai untuk tujuan tertentu pada masanya, tetapi kemudian digantikan oleh sistem yang lebih baru dengan fitur yang lebih baik.
