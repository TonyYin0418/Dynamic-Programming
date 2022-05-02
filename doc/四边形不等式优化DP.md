Donald E. Knuth. Optimum binary search trees. Acta Informatica, 1:14–25, 1971.

F. Frances Yao. Efficient dynamic programming using quadrangle inequalities. In Proceedings of the 12th Annual ACM Symposium on Theory of Computing, pages 429–435, 1980.

# 四边形不等式优化 DP

## 四边形不等式

若对于任意整数 $l_1,l_2,r_2,r_1$ 满足 $l_1\le l_2\le r_2\le r_1$，若二元函数 $w(x,y)$ 满足
$$
w(l_1,r_1)+w(l_2,r_2)\ge w(l_1,r_2)+w(l_2,r_1)\tag{1}
$$
则称 $w$ 满足四边形不等式。四边形不等式有一个常见的等价形式：
$$
w(l,r+1)+w(l+1,r)\ge w(l,r)+w(l+1,r+1)\tag{2}
$$
其中 $l\lt r$。由（1）得到（2）较为显然，由（2）推出（1）可以通过数学归纳法证得。

假设对于 $l+x\lt r$ 有
$$
w(l,r+1)+w(l+x,r)\ge w(l,r)+w(l+x,r+1)\\
$$
在 $x=1$ 时此式为（1）。

对于 $l+x+1\lt r$，根据（2）有
$$
w(l+x,r+1)+w(l+x+1,r)\ge w(l+x,r)+w(l+x+1,r+1)\\
$$
两式相加可得
$$
w(l,r+1)+w(l+x+1,r)\ge w(l,r)+w(l+x+1,r+1)
$$
同理可得 $w(l,r+y)+w(l+x,r)\ge w(l,r)+w(l+x,r+y)$，即证。

## 四边形不等式优化 DP

四边形不等式优化 DP 最早在 1971 年由 Donald E. Knuth. 提出，而后又在 1980 年由 F. Frances Yao 进行了深入研究和系统化整理。

### 一维 DP

在优化一维 DP 时，DP 的形式往往为 $f[i]=\min_{0\le j\lt i}\{f[j]+w(j,i)\}$。不妨设令 $f[i]$ 取得最小值的 $j$ 为 $d[i]$，那么若 $w$ 满足四边形不等式，则 $d$ 单调不减，称 $f$ 具有决策单调性。利用此性质可以使时间复杂度为 $O(n^2)$ 的计算简化为 $O(n\log n)$。本文将不对这类优化进行细致探讨。

### 二维 DP

在优化二维 DP 时，DP 的形式则多为 $f[i][j]=\min_{i\le k\lt j}\{f[i][k]+f[k+1][j]+w(i,j)\}(i\lt j)$，$f[i][i]=0$。

不妨设令 $f[i][j]$ 取得最小值的 $k$ 为 $d[i][j]$，那么

* 若
  1. $w$ 满足四边形不等式，
  2. 对于任意 $l_1\le l_2\le r_2\le r_1$，有 $w(l_1,r_1)\ge w(l_2,r_2)$；
* 则
  1. $dp$ 也满足四边形不等式，
  2. $d[i][j]\le d[i+1][j]$、$d[i][j]\le d[i][j+1]$。

对于满足 $d[i][j]\le \min\{d[i+1][j],d[i][j+1]\}$ 的，我们称 $dp$ 具有二维决策单调性。在对 $f[i][j]$ 进行计算时，仅考察位于 $[d[i][j-1],d[i+1][j]]$ 中的 $k$ 可以使时间复杂度为 $O(n^3)$ 的计算优化为 $O(n^2)$。

#### $dp$ 满足四边形不等式的证明

关于 $dp$ 满足四边形不等式的证明，考虑使用数学归纳法。

当 $r-l=1$ 时，
$$
dp[l][r+1]+dp[l+1][r]=dp[l][l+2]\ge w(l,l+2)\\
dp[l][r]+dp[l+1][r+1]=dp[l][l+1]+dp[l+1][l+2]=w(l,l+1)+w(l+1,l+2)\\
dp[l][r+1]+dp[l+1][r]\ge dp[l][r]+dp[l+1][r+1]
$$
设在 $r-l\lt k$ 时，$dp$ 满足四边形不等式。为方便起见，设 $x=d[l][r+1],y=d[l+1][r]$，那么
$$
dp[l][r+1]+dp[l+1][r]=(dp[l][x]+dp[x+1][r+1]+w(l,r+1))+(dp[l+1][y]+dp[y+1][r]+w(l+1,r))\\
dp[l][r]+dp[l+1][r+1]\le(dp[l][x]+dp[x+1][r]+w(l,r))+(dp[l+1][y]+dp[y+1][r+1]+w(l+1,r+1))\\
$$
欲证 $dp[l][r+1]+dp[l+1][r]\ge dp[l][r]+dp[l+1][r+1]$，只需证
$$
dp[x+1][r+1]+dp[y+1][r]+w(l,r+1)+w(l+1,r)\ge dp[x+1][r]+dp[y+1][r+1]+w(l,r)+w(l+1,r+1)
$$
只需证
$$
dp[x+1][r+1]+dp[y+1][r]\ge dp[x+1][r]+dp[y+1][r+1]\\
w(l,r+1)+w(l+1,r)\ge w(l,r)+w(l+1,r+1)
$$
两式分别可以由归纳假设以及 $w$ 满足四边形不等式得到，即证 $dp$ 满足四边形不等式。

#### 二维决策单调性的证明

关于二维决策单调性的证明，设 $x=d[i][j]$，$i\le k\lt x$。根据 $dp$ 满足四边形不等式和 $d[i][j]$ 的最优性，有
$$
dp[i][x]+dp[i+1][k]\ge dp[i][k]+dp[i+1][x]\\
dp[i][k]+dp[k+1][j]\ge dp[i][x]+dp[x+1][j]
$$
可以得到
$$
dp[i+1][k]+dp[k+1][j]\ge dp[i+1][x]+dp[x+1][j]
$$
因此对于 $dp[i+1][j]$ 的转移，$k\in [i,d[i][j])$ 一定不优于 $d[i][j]$，有 $d[i+1][j]\ge d[i][j]$。

类似的，设 $x\lt k\le j$，有
$$
dp[x+1][j]+dp[k+1][j-1]\ge dp[x+1][j-1]+dp[k+1][j]\\
dp[i][k]+dp[k+1][j]\ge dp[i][x]+dp[x+1][j]
$$
可以得到
$$
dp[i][k]+dp[k+1][j-1]\ge dp[i][x]+dp[x+1][j-1]
$$
即 $d[i][j-1]\le d[i][j]$。

#### 时间复杂度的证明

关于时间复杂度是 $O(n^2)$ 的证明，考虑
$$
\sum_{i=1}^{n-1}\sum_{j=i+1}^n(d[i+1][j]-d[i][j-1])\\
=\sum_{i=2}^n\sum_{j=i+1}^nd[i][j]-\sum_{i=1}^{n-1}\sum_{j=i}^{n-1}d[i][j]\\
=\sum_{i=1}^{n-1}d[i][n]-\sum_{j=2}^nd[1][j]-\sum_{i=1}^nd[i][i]
$$
并且 $d[i][j]\in[1,n]$，因此 $O(\sum_{i=1}^{n-1}\sum_{j=i+1}^n(d[i+1][j]-d[i][j-1]))=O(n^2)$。

### 应用实例

#### 石子合并

##### 题目描述

有 $n$ 堆直线排列的石子，第 $i$ 堆石子有 $a[i]$ 个。规定每次只能合并任意相邻的两堆石子，并产生两堆石子数量之和的疲劳值。现在要将石子有序的合并成一堆，试求最小总疲劳值。

$1\le n\le 5000$

##### 解题思路

设 $dp[i][j]$ 为将下标在 $[i,j]$ 内的石子合并为一堆所需的最小疲劳值，$w(i,j)=\sum_{k=i}^ja[k]$，那么有
$$
dp[i][j]=
\begin{cases}
\min_{i\le k\lt j}\{dp[i][k]+dp[k+1][j]+w(i,j)\}&i\lt j\\[2ex]
0&i=j
\end{cases}
$$
直接转移时间复杂度为 $O(n^3)$，不能接受。发现 $w$ 满足
$$
w(l,r+1)+w(l+1,r)=w(l,r)+w(l+1,r+1)
$$
即复合四边形不等式条件，因此可以对上述 DP 进行优化，达到 $O(n^2)$ 的时间复杂度。

##### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=5005;
int n,a[maxn],s[maxn],dp[maxn][maxn],d[maxn][maxn];
#define w(i,j) (s[j]-s[i-1])
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;i++)dp[i][i]=0,d[i][i]=i;
    for(int l=2;l<=n;l++){
        for(int i=1,j;i+l-1<=n;i++){
            j=i+l-1;
            for(int k=d[i][j-1];k<=min(j-1,d[i+1][j]);k++){
                int nx=dp[i][k]+dp[k+1][j]+w(i,j);
                if(nx<dp[i][j]){
                    dp[i][j]=nx;
                    d[i][j]=k;
                }
            }
        }
    }
    cout<<dp[1][n]<<endl;
    return 0;
}
```

#### P4767 [IOI2000]邮局

##### 题目描述

给定 $n$ 个村庄在一条直线上的坐标。现在要选一些村庄建立 $k$ 个邮局，使得每个村庄与其最近的邮局之间的距离总和最小。试求这个最小距离和。

$1\le k\le 300$，$k\le n\le 3000$，$1\le$ 村庄位置 $\le 10000$。

##### 解题思路

首先将村庄按其在坐标轴上的位置排序，设第 $i$ 个村庄的坐标为 $x_i$。

设 $dp[i][j]$ 表示前 $i$ 个村庄建立 $j$ 个邮局的最小距离和，$w(l,r)$ 表示在第 $p$ 个村庄建立一个邮局所得到的 $\sum_{i=l}^r|x_i-x_p|$ 的最小值。不难看出 $p=\lfloor \frac{l+r}{2}\rfloor$，因此
$$
w(l,r)=(\sum_{i=p+1}^rx_i-x_p(r-p))+(x_p(p-l)-\sum_{i=l}^{p-1}x_i)\\
w(l,r)=w(l,r-1)+x_r-x_p\\
w(l,r)=w(l+1,r)+x_p-x_l\\
$$
可以在 $dp$ 转移前 $O(n^2)$ 递推，也可以使用前缀和每次转移时 $O(1)$ 计算。

同时 DP 递推式有
$$
dp[i][j]=
\begin{cases}
\min_{1\le k\le i}\{dp[k-1][j-1]+w(k,i)\}&i\not=0,j\not=0\\[2ex]
1&i=0,j=0\\[2ex]
0&else
\end{cases}
$$
直接递推是 $O(n^2k)$ 的，不能接受。发现
$$
\begin{aligned}
w(l,r)+w(l+1,r-1)&=2w(l+1,r-1)+x_r-x_l\\
w(l+1,r)+w(l,r-1)&=2w(l+1,r-1)+x_r-x_l-(x_{\lfloor \frac{l+r+1}{2}\rfloor}-x_{\lfloor \frac{l+r-1}{2}\rfloor})
\end{aligned}
$$
因为 $x$ 递增，有 $(x_{\lfloor \frac{l+r+1}{2}\rfloor}-x_{\lfloor \frac{l+r-1}{2}\rfloor})\ge0$，所以 $w(l,r)+w(l+1,r-1)\ge w(l+1,r)+w(l,r-1)$，$w$ 满足四边形不等式，$dp$ 满足四边形不等式。因此对转移时计算的区间进行优化就能达到 $O(nk)$ 的时间复杂度。

##### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=3e3+5,maxp=305;
int n,p,dp[maxn][maxp],d[maxn][maxp],x[maxn],s[maxn];
inline int w(int l,int r){
    int mid=l+r>>1;
    int res=s[r]-s[mid]-x[mid]*(r-mid);
    res+=x[mid]*(mid-l)-(s[mid-1]-s[l-1]);
    return res;
}
int main(){
    cin>>n>>p;
    for(int i=1;i<=n;i++)cin>>x[i];
    sort(x+1,x+1+n);
    for(int i=1;i<=n;i++)s[i]=s[i-1]+x[i];
    for(int i=1;i<=p;i++)d[n+1][i]=n;
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int j=1;j<=p;j++)
        for(int i=n;i>=1;i--)
        for(int k=d[i][j-1];k<=d[i+1][j];k++){
            int nx=dp[k][j-1]+w(k+1,i);
            if(nx<dp[i][j])
                dp[i][j]=nx,d[i][j]=k;
        }
    cout<<dp[n][p]<<'\n';
    return 0;
}
```