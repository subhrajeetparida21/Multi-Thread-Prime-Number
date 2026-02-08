#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <math.h>

int isPrime(int num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;

    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int main() {
    int rl, rh, n;

    printf("enter range (rl rh): ");
    scanf("%d %d", &rl, &rh);

    printf("enter number of child processes: ");
    scanf("%d", &n);

    printf("\nCPU Info:\n");

    if (system("lscpu > /dev/null 2>&1") == 0) {
        system("lscpu");
    } else {
        system("sysctl -n hw.ncpu | awk '{print \"CPU(s): \" $1}'");
    }

    int fd = open("prime.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    close(fd);

    int total = rh - rl + 1;
    int chunk = total / n;

    long start = getTime();

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            int low = rl + i * chunk;
            int high = (i == n - 1) ? rh : low + chunk - 1;

            int fd_child = open("prime.txt", O_WRONLY | O_APPEND);

            for (int x = low; x <= high; x++) {
                if (isPrime(x)) {
                    char buf[20];
                    int len = sprintf(buf, "%d\n", x);
                    write(fd_child, buf, len);
                }
            }

            close(fd_child);
            exit(0);
        }
    }

    for (int i = 0; i < n; i++)
        wait(NULL);

    long end = getTime();

    printf("execution Time: %ld microseconds\n", end - start);
    return 0;
}



