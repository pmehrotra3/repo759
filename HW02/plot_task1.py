import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

n, t = [], []
with open("task1_times.txt") as f:
    for line in f:
        a, b = line.split()
        n.append(int(a))
        t.append(float(b))

plt.plot(n, t, "o-")
plt.xscale("log", base=2)
plt.yscale("log")
plt.xlabel("n (array size)")
plt.ylabel("Time (ms)")
plt.title("Scaling analysis of inclusive scan")
plt.grid(True)
plt.savefig("task1.pdf")
