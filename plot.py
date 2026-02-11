import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("result_roll_45/results.csv")

# Clean + convert to numbers
df.columns = df.columns.str.strip()
df["processes"] = pd.to_numeric(df["processes"], errors="coerce")
df["time_us"] = pd.to_numeric(df["time_us"], errors="coerce")
df = df.dropna(subset=["processes", "time_us"]).sort_values("processes")

df["time_ms"] = df["time_us"] / 1000.0

t1 = float(df.loc[df["processes"] == 1, "time_ms"].iloc[0])
df["speedup"] = t1 / df["time_ms"]

# Time vs Processes
plt.figure()
plt.plot(df["processes"], df["time_ms"], marker="o")
plt.xlabel("Number of child processes")
plt.ylabel("Time (ms)")
plt.title("Prime Generator: Time vs Processes")
plt.grid(True)
plt.savefig("result_roll_45/time_vs_processes.png", dpi=200)

# Speedup vs Processes
plt.figure()
plt.plot(df["processes"], df["speedup"], marker="o")
plt.xlabel("Number of child processes")
plt.ylabel("Speedup (T1 / Tp)")
plt.title("Prime Generator: Speedup vs Processes")
plt.grid(True)
plt.savefig("result_roll_45/speedup_vs_processes.png", dpi=200)

print("Saved graphs in result_roll_45/")

