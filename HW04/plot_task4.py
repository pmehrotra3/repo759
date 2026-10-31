import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

policies = ["static", "dynamic", "guided"]
times = {p: ([], []) for p in policies}
with open("task4_times.txt") as f:
    for line in f:
        policy, t, ms = line.split()
        times[policy][0].append(int(t))
        times[policy][1].append(float(ms))

# one plot per scheduling policy, time vs. num_threads, linear axes
fig, axes = plt.subplots(3, 1, figsize=(7, 12))
for ax, policy in zip(axes, policies):
    t, ms = times[policy]
    ax.plot(t, ms, "o-")
    ax.set_xticks(range(1, 9))
    ax.set_xlabel("num_threads")
    ax.set_ylabel("Time (ms)")
    ax.set_title(f"N-body, schedule({policy}), N = 1000, end time = 100")
    ax.grid(True)

fig.tight_layout()
fig.savefig("task4.pdf")
