#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     
#include <sys/wait.h>   
#include <sys/time.h> 
#include <fcntl.h>    
#include <math.h>     
#include <string.h>     

#define OUTPUT_FILE "prime.txt"

int isprime(int num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0; 

    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

long gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int main(int argc, char *argv[]) {
    int rl, rh, n;
    int i;
    pid_t pid;

    if (argc == 4) {
        rl = atoi(argv[1]);
        rh = atoi(argv[2]);
        n = atoi(argv[3]);
        
        if (rl > rh) {
            fprintf(stderr, "Error: Lower bound (rl) cannot be greater than upper bound (rh).\n");
            return 1;
        }
        if (n <= 0) {
            fprintf(stderr, "Error: Number of processes must be positive.\n");
            return 1;
        }
    } else {
        printf("enter lower range (rl): ");
        if (scanf("%d", &rl) != 1) return 1;

        printf("enter higher range (rh): ");
        if (scanf("%d", &rh) != 1) return 1;

        printf("enter number of child processes: ");
        if (scanf("%d", &n) != 1) return 1;
        
        printf("\nsystem cpu information:\n");
        if (system("lscpu | grep 'CPU(s):' | head -1") != 0) {
            system("sysctl -n hw.ncpu | awk '{print \"CPU(s): \" $1}'");
        }
    }
    int fd = open(OUTPUT_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error clearing output file");
        return 1;
    }
    close(fd);

    int range = (rh - rl + 1) / n;

    long start = gettime();

    for (i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0) {  
            int startrange = rl + i * range;
            int endrange;

            if (i == n - 1)
                endrange = rh;
            else
                endrange = startrange + range - 1;

            int fd_child = open(OUTPUT_FILE, O_WRONLY | O_APPEND);
            if (fd_child < 0) {
                perror("Child failed to open file");
                exit(1);
            }

            int num;
            char buffer[256]; 
            
            for (num = startrange; num <= endrange; num++) {
                if (isprime(num)) {
                    int len = sprintf(buffer, "%d\n", num);
                    if (write(fd_child, buffer, len) < 0) {
                        perror("Write failed");
                    }
                }
            }

            close(fd_child);
            exit(0); 
    }

    for (i = 0; i < n; i++) {
        wait(NULL);
    }

    long end = gettime();
    
    printf("\nEXECUTION_TIME_US: %ld\n", end - start);
    
    if (argc != 4) {
        printf("Time taken: %ld microseconds\n", end - start);
        printf("Prime numbers stored in %s\n", OUTPUT_FILE);
    }

    return 0;
}
}