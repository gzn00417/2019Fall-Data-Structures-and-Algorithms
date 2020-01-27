import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

heap_n = [10000, 50000, 100000, 200000, 300000]
heap_t = [0.001575, 0.008575, 0.016, 0.03555, 0.051975]
slct_n = [10000, 50000, 100000, 200000, 300000]
slct_t = [0.01095, 0.257425, 1.054325, 4.168375, 9.321475]

plt.rcParams["figure.figsize"] = (10.0, 6.0)
fig = plt.figure()
style = ["darkgrid", "dark", "white", "whitegrid", "ticks"]
sns.set_style(style[2])

ax1 = fig.add_subplot(111)
ax1.set_ylim([0, 1])
ax1.plot(heap_n, heap_t, "c", ms=10, lw=1, marker="o")  # 设置线粗细，节点样式
ax1.set_ylabel("Heap_time", fontsize="20")
ax1.tick_params(labelsize=10)
for x, y in zip(heap_n, heap_t):  # # 添加数据标签
    plt.text(
        x, y + 0.01, str(y) + "s", ha="center", va="bottom", fontsize=8, rotation=0
    )
# plt.plot(heap_t, label="heap")
# plt.legend(bbox_to_anchor=(0.15, 1.0))

ax2 = ax1.twinx()
ax2.set_ylim([0, 10])
ax2.plot(slct_n, slct_t, "darkviolet", ms=7, lw=1, marker="o")  # 设置线粗细，节点样式
ax2.set_ylabel("Select_time", fontsize="20")
ax2.tick_params(labelsize=10)
for x, y in zip(slct_n, slct_t):  # # 添加数据标签
    plt.text(x, y + 0.1, str(y) + "s", ha="center", va="bottom", fontsize=8, rotation=0)
# plt.plot(slct_t, label="slct")
"""
plt.legend(
    bbox_to_anchor=(0.0, 1.02, 1.0, 0.102),
    loc=0,
    ncol=3,
    mode="expand",
    borderaxespad=0.0,
)
"""
plt.savefig(r"D:\GZN\HIT\个人文件\2019秋数据结构与算法\Lab5\1.png", dpi=1000, bbox_inches="tight")
plt.grid()
plt.show()
