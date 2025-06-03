#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <errno.h>

#define N 4 
#define CHECK_ERROR(x, msg) do { \
    if (x) { \
        perror(msg); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

int main() {
    int A[N][N], B[N][N];
    
    srand((unsigned)time(NULL));
    printf("Matriks A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMatriks B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = rand() % 10;
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    
    int shmid = shmget(IPC_PRIVATE, N * N * sizeof(int), IPC_CREAT | 0666);
    CHECK_ERROR(shmid < 0, "shmget failed");
    
    int (*result)[N] = shmat(shmid, NULL, 0);
    CHECK_ERROR(result == (void *)-1, "shmat failed");
    
    memset(result, 0, N * N * sizeof(int));
    
    pid_t pids[N];
    for (int i = 0; i < N; i++) {
        pids[i] = fork();
        CHECK_ERROR(pids[i] < 0, "fork failed");
        
        if (pids[i] == 0) { // child process
            printf("Child process %d (PID: %d) menghitung baris %d\n", i, getpid(), i);
            
            for (int j = 0; j < N; j++) {
                result[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
            
            // Detach shared memory in child
            CHECK_ERROR(shmdt(result) == -1, "shmdt failed in child");
            exit(EXIT_SUCCESS);
        }
    }
    
    for (int i = 0; i < N; i++) {
        int status;
        waitpid(pids[i], &status, 0);
        if (!WIFEXITED(status)) {
            fprintf(stderr, "Child %d terminated abnormally\n", i);
        }
    }
    
    printf("\nHasil perkalian matriks A * B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    CHECK_ERROR(shmdt(result) == -1, "shmdt failed in parent");
    CHECK_ERROR(shmctl(shmid, IPC_RMID, NULL) == -1, "shmctl failed");
    
    return EXIT_SUCCESS;
}