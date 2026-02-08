# OS Assignment 1 - Parallel Prime Finder (Manual)

This is my manual implementation for the assignment. It uses `fork()` to create child processes and find prime numbers in a range.

## How to Compile
```bash
gcc prime.c -lm
```

## How to Run
You can run it in two ways.

1. **Interactive mode:**
   ```bash
   ./a.out
   ```

2. **Command line arguments:**
   ```bash
   ./a.out 1000 10000 4
   ```

## Files
- `prime.c`: The C code.
- `prime.txt`: Output file where primes are stored.
- `plot_prime.py`: Python script to make graphs.
- `results/`: Folder with the plots and data I generated.

## Plotting
To make a graph, I used the python script `plot_prime.py`.
Usage: `python3 plot_prime.py <csv_file> <output_image>`

