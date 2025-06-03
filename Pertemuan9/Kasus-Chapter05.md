# Contoh Kasus Algoritma Scheduling - S10 Chapter 05

## 1. SJF (Shortest Job First) Scheduling Algorithm Without Arrival Time

### Deskripsi
SJF tanpa arrival time adalah algoritma scheduling non-preemptive dimana semua proses dianggap tiba pada waktu yang sama (arrival time = 0), dan proses dengan burst time terpendek akan dieksekusi terlebih dahulu.

### Contoh Kasus 1
**Data Proses:**
| Process | Burst Time |
|---------|------------|
| P1      | 6          |
| P2      | 8          |
| P3      | 7          |
| P4      | 3          |
| P5      | 4          |

**Langkah Penyelesaian:**
1. Urutkan proses berdasarkan burst time (ascending):
   - P4 (3) → P5 (4) → P1 (6) → P3 (7) → P2 (8)

2. Hitung Completion Time (CT):
   - P4: CT = 3
   - P5: CT = 3 + 4 = 7
   - P1: CT = 7 + 6 = 13
   - P3: CT = 13 + 7 = 20
   - P2: CT = 20 + 8 = 28

3. Hitung Turnaround Time (TAT) dan Waiting Time (WT):
   - TAT = CT - AT (AT = 0 untuk semua proses)
   - WT = TAT - BT

**Hasil:**
| Process | BT | CT | TAT | WT |
|---------|----|----|-----|-----|
| P1      | 6  | 13 | 13  | 7   |
| P2      | 8  | 28 | 28  | 20  |
| P3      | 7  | 20 | 20  | 13  |
| P4      | 3  | 3  | 3   | 0   |
| P5      | 4  | 7  | 7   | 3   |

**Gantt Chart:**
```
|  P4  |  P5  |    P1    |    P3    |      P2      |
0      3      7         13        20             28
```

**Rata-rata:**
- Average TAT = (13 + 28 + 20 + 3 + 7) / 5 = 14.2
- Average WT = (7 + 20 + 13 + 0 + 3) / 5 = 8.6

---

## 2. SJF (Shortest Job First) Scheduling Algorithm With Arrival Time

### Deskripsi
SJF dengan arrival time adalah algoritma scheduling non-preemptive dimana proses dipilih berdasarkan burst time terpendek dari proses yang sudah tiba.

### Contoh Kasus 2
**Data Proses:**
| Process | Arrival Time | Burst Time |
|---------|--------------|------------|
| P1      | 0            | 7          |
| P2      | 2            | 4          |
| P3      | 4            | 1          |
| P4      | 5            | 4          |
| P5      | 6            | 3          |

**Langkah Penyelesaian:**
1. Pada t=0: Hanya P1 yang tersedia → Eksekusi P1
2. Pada t=7: P1 selesai, P2, P3, P4, P5 sudah tiba
   - Pilih yang burst time terpendek: P3 (1)
3. Pada t=8: P3 selesai, pilih P5 (3)
4. Pada t=11: P5 selesai, pilih P2 atau P4 (sama-sama 4), pilih P2 (tiba lebih dulu)
5. Pada t=15: P2 selesai, eksekusi P4

**Hasil:**
| Process | AT | BT | CT | TAT | WT |
|---------|----|----|----|----|-----|
| P1      | 0  | 7  | 7  | 7  | 0   |
| P2      | 2  | 4  | 15 | 13 | 9   |
| P3      | 4  | 1  | 8  | 4  | 3   |
| P4      | 5  | 4  | 19 | 14 | 10  |
| P5      | 6  | 3  | 11 | 5  | 2   |

**Gantt Chart:**
```
|    P1    | P3 |  P5  |   P2   |   P4   |
0         7    8     11      15      19
```

**Rata-rata:**
- Average TAT = (7 + 13 + 4 + 14 + 5) / 5 = 8.6
- Average WT = (0 + 9 + 3 + 10 + 2) / 5 = 4.8

---

## 3. SRTF (Shortest Remaining Time First) Scheduling Algorithm

### Deskripsi
SRTF adalah versi preemptive dari SJF. Proses yang sedang berjalan dapat dihentikan jika ada proses baru yang tiba dengan remaining time lebih pendek.

### Contoh Kasus 3
**Data Proses:**
| Process | Arrival Time | Burst Time |
|---------|--------------|------------|
| P1      | 0            | 8          |
| P2      | 1            | 4          |
| P3      | 2            | 9          |
| P4      | 3            | 5          |
| P5      | 4            | 2          |

**Langkah Penyelesaian:**
1. t=0: P1 mulai (remaining=8)
2. t=1: P2 tiba (remaining=4) < P1 (remaining=7) → Preempt P1, jalankan P2
3. t=2: P3 tiba (remaining=9) > P2 (remaining=3) → Lanjutkan P2
4. t=3: P4 tiba (remaining=5) > P2 (remaining=2) → Lanjutkan P2
5. t=4: P5 tiba (remaining=2) = P2 (remaining=1) → Lanjutkan P2 (sedang berjalan)
6. t=5: P2 selesai, pilih P5 (remaining=2)
7. t=7: P5 selesai, pilih P4 (remaining=5)
8. t=12: P4 selesai, pilih P1 (remaining=7)
9. t=19: P1 selesai, pilih P3 (remaining=9)
10. t=28: P3 selesai

**Hasil:**
| Process | AT | BT | CT | TAT | WT |
|---------|----|----|----|----|-----|
| P1      | 0  | 8  | 19 | 19 | 11  |
| P2      | 1  | 4  | 5  | 4  | 0   |
| P3      | 2  | 9  | 28 | 26 | 17  |
| P4      | 3  | 5  | 12 | 9  | 4   |
| P5      | 4  | 2  | 7  | 3  | 1   |

**Gantt Chart:**
```
|P1|  P2  |P5|  P4  |   P1   |     P3     |
0  1     5  7     12      19           28
```

**Rata-rata:**
- Average TAT = (19 + 4 + 26 + 9 + 3) / 5 = 12.2
- Average WT = (11 + 0 + 17 + 4 + 1) / 5 = 6.6

---

## Kesimpulan Perbandingan

| Algorithm | Average TAT | Average WT |
|-----------|-------------|------------|
| SJF (No AT) | 14.2      | 8.6        |
| SJF (With AT) | 8.6     | 4.8        |
| SRTF      | 12.2        | 6.6        |

**Catatan:**
- SJF tanpa arrival time memberikan hasil optimal untuk semua proses yang tiba bersamaan
- SJF dengan arrival time lebih realistis tetapi tidak optimal
- SRTF memberikan response time yang lebih baik karena sifat preemptive-nya
- Semua algoritma ini rentan terhadap starvation untuk proses dengan burst time yang panjang
