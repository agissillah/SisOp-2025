# Fork: Parent-Child Process dan Perkalian Matriks

## 1. Fork: Parent-Child Process

### Konsep Fork dalam Pemrograman C

Fork adalah sistem call pada sistem operasi UNIX/Linux yang digunakan untuk menciptakan proses baru (child process) yang merupakan salinan dari proses yang memanggilnya (parent process). Ketika fork() dipanggil, sistem operasi menciptakan salinan hampir identik dari proses yang ada, termasuk code segment, data segment, heap, dan stack. Perbedaan utamanya adalah bahwa nilai kembalian dari fork() di parent process adalah PID (Process ID) dari child process yang baru dibuat, sedangkan nilai kembalian fork() di child process adalah 0. Jika fork() gagal, maka akan mengembalikan nilai -1.

Setelah fork() berhasil dieksekusi, kedua proses (parent dan child) akan melanjutkan eksekusi dari instruksi setelah pemanggilan fork(). Ini memungkinkan kita untuk membuat program parallel di mana beberapa proses berjalan secara bersamaan dan dapat menjalankan tugas yang berbeda. Proses child mewarisi hampir semua properti dari parent, tetapi memiliki ruang alamat terpisah, sehingga modifikasi pada variabel di salah satu proses tidak akan memengaruhi proses lainnya. Fork sering digunakan dalam pemrograman sistem untuk membuat daemon, server concurrent, atau memanfaatkan kemampuan multicore pada proses komputer modern.

![Fork Parent-Child Process Illustration](https://example.com/path/to/fork_illustration.png)

### Akses dan Cloning Repository

```bash
git clone https://github.com/ferryastika/operatingsystem.git
cd operatingsystem
```

### Deskripsi dan Visualisasi Pohon Proses

#### fork01.c

Program `fork01.c` membuat satu proses child dengan satu panggilan fork(). Parent dan child mencetak pesan masing-masing.

graph TD;
    A[Parent] --> B[Child];



#### fork02.c

Program `fork02.c` membuat satu proses child seperti fork01, tetapi menggunakan if/else untuk eksekusi kode yang berbeda antara parent dan child.

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("I am the child process (PID: %d)\n", getpid());
    } else if (pid > 0) {
        // Parent process
        printf("I am the parent process (PID: %d)\n", getpid());
        printf("My child's PID is: %d\n", pid);
    } else {
        // Fork failed
        printf("Fork failed!\n");
        return 1;
    }
    
    return 0;
}
```

![Process Tree for fork02.c](https://example.com/path/to/fork02_tree.png)

#### fork03.c

Program `fork03.c` membuat pohon proses dengan 2 level menggunakan dua panggilan fork() secara berurutan.

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    printf("Hello from process %d!\n", getpid());
    return 0;
}
```

![Process Tree for fork03.c](https://example.com/path/to/fork03_tree.png)

#### fork04.c

Program `fork04.c` membuat tree process dengan model lain, dengan menggunakan fork() dalam loop for.

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 2; i++) {
        fork();
        printf("i: %d, process ID: %d\n", i, getpid());
    }
    return 0;
}
```

![Process Tree for fork04.c](https://example.com/path/to/fork04_tree.png)

#### fork05.c

Program `fork05.c` membuat proses grandchild dengan cara spesifik dimana child membuat proses baru.

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) created\n", getpid());
        
        // Child creates grandchild
        pid_t grandchild_pid = fork();
        
        if (grandchild_pid == 0) {
            // Grandchild process
            printf("Grandchild process (PID: %d) created\n", getpid());
        } else {
            // Child process continues
            printf("Child process (PID: %d) created grandchild with PID: %d\n", getpid(), grandchild_pid);
            wait(NULL);
        }
    } else {
        // Parent process
        printf("Parent process (PID: %d) created child with PID: %d\n", getpid(), pid);
        wait(NULL);
    }
    
    return 0;
}
```

![Process Tree for fork05.c](https://example.com/path/to/fork05_tree.png)

#### fork06.c

Program `fork06.c` menciptakan proses lebih kompleks dengan fork berkelanjutan.

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    fork();
    printf("Hello from process %d!\n", getpid());
    sleep(1);
    return 0;
}
```

![Process Tree for fork06.c](https://example.com/path/to/fork06_tree.png)

## 2. Program Perkalian 2 Matriks [4 x 4] Menggunakan Fork()

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define N 4  // ukuran matriks 4x4

int main() {
    // Inisialisasi matriks A dan B
    int A[N][N], B[N][N];
    
    // Generate random values untuk matriks A dan B
    srand(time(NULL));
    printf("Matriks A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;  // nilai random 0-9
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMatriks B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = rand() % 10;  // nilai random 0-9
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    
    // Buat shared memory untuk hasil akhir perkalian
    int shmid;
    key_t key = IPC_PRIVATE;
    int (*result)[N];
    
    // Alokasi shared memory untuk hasil
    shmid = shmget(key, N * N * sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    
    // Attach shared memory
    result = shmat(shmid, NULL, 0);
    if (result == (int (*)[N]) -1) {
        perror("shmat");
        exit(1);
    }
    
    // Inisialisasi hasil dengan 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
        }
    }
    
    // Buat satu proses child untuk setiap baris matriks hasil
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            // Error handling
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Ini adalah child process
            // Setiap child process menangani satu baris dari matriks hasil
            printf("Child process %d (PID: %d) menghitung baris %d\n", i, getpid(), i);
            
            for (int j = 0; j < N; j++) {
                // Hitung elemen hasil[i][j]
                result[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
            
            // Child process selesai, exit
            exit(0);
        }
    }
    
    // Parent process menunggu semua child process selesai
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }
    
    // Tampilkan hasil perkalian matriks
    printf("\nHasil perkalian matriks A * B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    // Lepaskan dan hapus shared memory
    shmdt(result);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
```

### Penjelasan Program Perkalian Matriks

Program di atas melakukan perkalian dua matriks 4x4 menggunakan proses parallel dengan fork(). Berikut adalah penjelasan langkah-langkahnya:

1. Program menginisialisasi dua matriks A dan B dengan nilai random antara 0-9.

2. Program membuat shared memory untuk menyimpan hasil perkalian matriks, karena child process tidak bisa langsung berbagi memori dengan parent process.

3. Program melakukan fork sebanyak 4 kali (sesuai jumlah baris matriks hasil), sehingga terdapat 4 child process.

4. Setiap child process bertanggung jawab untuk menghitung satu baris dari matriks hasil.

5. Parent process menunggu hingga semua child process selesai menggunakan wait().

6. Setelah semua perhitungan selesai, parent process menampilkan hasil perkalian matriks.

7. Terakhir, shared memory dilepaskan dan dihapus.

Program ini memanfaatkan konsep fork untuk memparalelkan perhitungan perkalian matriks, di mana setiap baris dari matriks hasil dihitung oleh proses terpisah, meningkatkan efisiensi komputasi terutama pada sistem multicore.
