import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

times = {}
with open("task3_times.txt") as f:
    for line in f:
        tpb, n, ms = line.split()
        times.setdefault(int(tpb), ([], []))
        times[int(tpb)][0].append(int(n))
        times[int(tpb)][1].append(float(ms))

fig, ax = plt.subplots(figsize=(7, 5))
for tpb in sorted(times, reverse=True):
    n, ms = times[tpb]
    ax.plot(n, ms, "o-", label=f"{tpb} threads/block")
ax.set_xscale("log", base=2)
ax.set_yscale("log")
ax.set_xlabel("n")
ax.set_ylabel("Time (ms)")
ax.set_title("vscale kernel time vs. n")
ax.legend()
ax.grid(True, which="both", alpha=0.4)
fig.tight_layout()
fig.savefig("task3.pdf")
