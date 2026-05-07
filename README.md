# Computing-Network-Assignment13

计算机网络课程作业第13次作业，包含两个任务：路由表更新算法和迪杰斯特拉最短路径算法。

## 项目结构

```
Computing-Network-Assignment13/
├── Task1/          # 路由表更新算法
│   ├── main.cpp
│   ├── Task1.vcxproj
│   └── Task1.vcxproj.filters
├── Task2/          # 迪杰斯特拉算法实现
│   ├── main.cpp
│   ├── Task2.vcxproj
│   └── Task2.vcxproj.filters
├── .gitattributes
├── .gitignore
└── Computing-Network-Assignment13.slnx
```

## 任务说明

### Task1: 路由表更新算法

实现路由器路由表的动态更新功能。模拟R1路由器根据R2发来的路由表更新自己的路由表。

**题目要求：**
- 输入 R1 的路由表和 R2 发来的路由表
- 输出 R1 的新路由表

**初始路由表：**

| 网络 | 跳数 | 下一跳 |
|------|------|--------|
| N1 | 1 | R1 |
| N2 | 0 | 直接发送 |
| N3 | 6 | R4 |
| N4 | 8 | R5 |

**R2路由表：**

| 网络 | 跳数 | 下一跳 |
|------|------|--------|
| N2 | 2 | R5 |
| N3 | 3 | R6 |
| N4 | 7 | R7 |
| N5 | 3 | R8 |

**核心算法：**
- 使用距离向量算法（Distance Vector Algorithm）
- 当收到邻居路由器的路由信息时，更新原则：
  1. 如果目标网络不存在，添加新路由（跳数+1）
  2. 如果目标网络已存在且新路径更短，更新路由

### Task2: 迪杰斯特拉算法

使用堆优化实现迪杰斯特拉最短路径算法。

**输入格式：**
```
n m
r1 r2 weight
...
```

其中：
- `n` 为节点数
- `m` 为边数
- 后续 `m` 行描述每条边的两个端点和权重

**输出格式：**
- 从节点1到节点n的最短路径（节点编号从1开始）
- 如果不存在路径，输出 `-1`

**算法特点：**
- 使用优先队列（小根堆）优化
- 时间复杂度：O(m log n)
- 已通过 Codeforces 20C 测试验证



## 代码说明

### Task1 核心类
- `target_net` 结构体：存储目标网络的跳数和下一跳
- `R_map` 类：路由器对象，包含路由表管理和更新方法

### Task2 核心函数
- `dijkstra()`：实现堆优化的迪杰斯特拉算法
- 输入输出优化：使用 `ios::sync_with_stdio(false)` 和 `cin.tie(nullptr)`
