import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

t, ms = [], []
with open("task2_times.txt") as f:
    for line in f:
        a, b = line.split()
        t.append(int(a))
        ms.append(float(b))

plt.plot(t, ms, "o-")
plt.xticks(range(1, 21))
plt.xlabel("t (number of threads)")
plt.ylabel("Time (ms)")
plt.title("Parallel convolve, n = 1024")
plt.grid(True)
plt.savefig("task2.pdf")
