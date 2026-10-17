import sys
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def read_times(path):
    x, ms = [], []
    with open(path) as f:
        for line in f:
            a, b = line.split()
            x.append(int(a))
            ms.append(float(b))
    return x, ms


# time vs. ts, log-scale x axis
ts, ms = read_times("task3_ts_times.txt")
plt.figure()
plt.plot(ts, ms, "o-")
plt.xscale("log", base=2)
plt.xlabel("ts (threshold)")
plt.ylabel("Time (ms)")
plt.title("Parallel msort, n = 10^6, t = 8")
plt.grid(True)
plt.savefig("task3_ts.pdf")

# time vs. t, linear axes
best_ts = sys.argv[1] if len(sys.argv) > 1 else "best"
t, ms = read_times("task3_t_times.txt")
plt.figure()
plt.plot(t, ms, "o-")
plt.xticks(range(1, 21))
plt.xlabel("t (number of threads)")
plt.ylabel("Time (ms)")
plt.title(f"Parallel msort, n = 10^6, ts = {best_ts}")
plt.grid(True)
plt.savefig("task3_t.pdf")
