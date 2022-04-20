# 解决的问题

给定区间 $[L,R]$，求区间内满足一定条件的数的个数。

问题有如下特征：

- 给定的条件一般与数的组成有关，比如数位之间的关系。

- 此类问题的数据规模一般较大。$1\leq L<R\leq 10^{100000}$ 在某些情况下也是可以接受的，因为是按位DP。
- 最终目的为计数。

为了方便，数位DP一般使用**记忆化搜索**实现。

# 算法原理

通常情况下，首先将求 $\operatorname{ans}_{[L,R]}$ 的问题转化为 $\operatorname{ans}_{[1,R]}-\operatorname{ans}_{[1,l-1]}$.

数位DP的核心思想，是注意到：在从 $1$ 向上数数的过程中，过程中有很多重复的部分，比如 $7000\sim7999$，$9000\sim9999$，它们的后三位都是 $\_000\sim \_ 999$，对这些部分加以记录，相同的部分只计算一次。

可以进一步通过例题理解。

# P2657 [SCOI2009] windy 数

## 题目描述

$\rm{windy}$ 数：**不含前导零且相邻两个数字之差至少为 $2$ 的正整数**。

给定 $a,b$，求 $[a,b]$ 中有多少个 $\rm{windy}$ 数。

$1\leq a\leq b\leq 2\times 10^9$.

## 解题思路

定义状态：$\rm{(pos,lst,lim,zero)}$，分别表示：

- $\rm{pos}$：当前正在尝试确定第几位，个位是第 $1$ 位，十位是第 $2$ 位，以此类推。
- $\rm{lst}$：本题中，需要记录上一位选的是什么数，以约束当前位置的选取。
- $\rm{lim}$：当前选出的前缀是否与上界相同。比如对于上界 $273967$，当前枚举出的前缀为 $2739\_\ \_$，则 $\operatorname{pos}=2$ 时只能选取 $[0,6]$ 的数。
- $\rm{zero}$：当前选出的前缀是否都为 $0$. 对于上界 $273967$，$\underline{00}9000$ 也是可以取到的，这时有 $2$ 个前导零。这与 $\operatorname{lim}$ 的作用类似，都用于标记特殊情况。

## 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;
const int MAXN = 20;
int a, b, num[MAXN];
int dp[MAXN][MAXN];
int dfs(int pos, int lst, bool lim, bool zero) {
	if(pos == 0) return 1;
	if(!lim && !zero && dp[pos][lst] != -1) return dp[pos][lst];
	int ret = 0;
	int mx = lim ? num[pos] : 9;
	for(int i = 0; i <= mx; i++) if(abs(i - lst) >= 2)
		ret += dfs(pos - 1, (zero & (i == 0)) ? -2 : i, lim & (i == num[pos]), zero & (i == 0));
	if(!lim && !zero) dp[pos][lst] = ret;
	return ret;
}
int solve(int x) {
	int p = 0;
	while(x) {
		num[++p] = x % 10;
		x /= 10;
	}
	memset(dp, -1, sizeof(dp));
	return dfs(p, -2, 1, 1);
}
int main() {
	cin >> a >> b;
	cout << solve(b) - solve(a - 1) << endl;
	return 0;
}
```
