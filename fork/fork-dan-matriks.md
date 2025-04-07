# Fork: Parent-Child Process dan Perkalian Matriks

## 1. Fork: Parent-Child Process

### Konsep Fork dalam Pemrograman C

Fork adalah sistem call pada sistem operasi UNIX/Linux yang digunakan untuk menciptakan proses baru (child process) yang merupakan salinan dari proses yang memanggilnya (parent process). Ketika fork() dipanggil, sistem operasi menciptakan salinan hampir identik dari proses yang ada, termasuk code segment, data segment, heap, dan stack. Perbedaan utamanya adalah bahwa nilai kembalian dari fork() di parent process adalah PID (Process ID) dari child process yang baru dibuat, sedangkan nilai kembalian fork() di child process adalah 0. Jika fork() gagal, maka akan mengembalikan nilai -1.

Setelah fork() berhasil dieksekusi, kedua proses (parent dan child) akan melanjutkan eksekusi dari instruksi setelah pemanggilan fork(). Ini memungkinkan kita untuk membuat program parallel di mana beberapa proses berjalan secara bersamaan dan dapat menjalankan tugas yang berbeda. Proses child mewarisi hampir semua properti dari parent, tetapi memiliki ruang alamat terpisah, sehingga modifikasi pada variabel di salah satu proses tidak akan memengaruhi proses lainnya. Fork sering digunakan dalam pemrograman sistem untuk membuat daemon, server concurrent, atau memanfaatkan kemampuan multicore pada proses komputer modern.


### Akses dan Cloning Repository

```bash
git clone https://github.com/ferryastika/operatingsystem.git
cd operatingsystem
```

### Deskripsi dan Visualisasi Pohon Proses

#### fork01.c

Program `fork01.c` membuat satu proses child dengan satu panggilan fork(). Parent dan child mencetak pesan masing-masing.

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    
    printf("Fork returned: %d\n", pid);
    
    if (pid == 0) {
        printf("I am the child process.\n");
    } else if (pid > 0) {
        printf("I am the parent process.\n");
    } else {
        printf("Fork failed!\n");
    }
    
    return 0;
}
```

Penjelasan:
fork() dipanggil satu kali, maka akan ada 2 proses yang mengeksekusi printf(), yaitu parent dan child. Output "Hello world!" akan dicetak dua kali.

Visualisasi :
Parent
 └── Child


#### fork02.cPenjelasan:
Dengan tiga fork(), jumlah proses menjadi 2^3 = 8 proses.

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

Penjelasan:
Dua fork() berarti akan terjadi 2 kali percabangan proses:

Pertama, dari 1 proses menjadi 2.

Kedua, setiap proses aktif memanggil fork() lagi, total jadi 4 proses.

Visualisasi :
P0
├── C1
│   └── C3
└── C2
    └── C4



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

Penjelasan:
Dengan tiga fork(), jumlah proses menjadi 2^3 = 8 proses.

Visualisasi :
P0
├── P1
│   ├── P3
│   │   └── P7
│   └── P4
└── P2
    ├── P5
    └── P6


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
Penjelasan:
Sama seperti fork02.c, akan ada 4 proses yang mencetak PID-nya masing-masing.

Visualisasi :
P0
├── P1  ← hasil fork 1
│   └── P3  ← hasil fork 2 dari P1
└── P2  ← hasil fork 2 dari P0



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

Penjelasan:

Pertama fork() menghasilkan 2 proses → keduanya mencetak "A".

Kedua fork() dijalankan oleh masing-masing → total 4 proses mencetak "B".

Visualisasi :
P0
├── P1
│   └── P3
└── P2
    └── P4


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

Penjelasan: Tiga fork() lagi, jadi akan muncul 8 proses yang mencetak PID-nya.

Visualisasi :
P0
├── P1
│   ├── P3
│   │   └── P7
│   └── P4
└── P2
    ├── P5
    └── P6
