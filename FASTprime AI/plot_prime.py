import matplotlib.pyplot as plt
import csv
import sys
import os

def main():
    if len(sys.argv) < 2:
        print("Usage: python plot_prime.py <data_file.csv> [output_plot.png]")
        sys.exit(1)

    data_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else "execution_time_plot.png"

    n_values = []
    time_values = []

    try:
        with open(data_file, 'r') as csvfile:
            reader = csv.reader(csvfile)
            header = next(reader, None) # Skip header if present
            for row in reader:
                if len(row) >= 2:
                    try:
                        n = int(row[0])
                        t = int(row[1])
                        n_values.append(n)
                        time_values.append(t)
                    except ValueError:
                        continue
    except FileNotFoundError:
        print(f"Error: File {data_file} not found.")
        sys.exit(1)

    if not n_values:
        print("No valid data found in CSV.")
        sys.exit(1)

    plt.figure(figsize=(10, 6))
    plt.plot(n_values, time_values, marker='o', linestyle='-', color='b')
    plt.xlabel("Number of Child Processes (n)")
    plt.ylabel("Execution Time (microseconds)")
    plt.title(f"FASTprime: n vs Execution Time (Ankit's System)")
    plt.suptitle("Performance analysis on Ankit's machine", fontsize=10)
    plt.grid(True)
    
    # Annotate points
    for i, txt in enumerate(time_values):
        plt.annotate(f"{txt}us", (n_values[i], time_values[i]), textcoords="offset points", xytext=(0,10), ha='center')

    plt.savefig(output_file)
    print(f"Plot saved to {output_file}")

if __name__ == "__main__":
    main()
