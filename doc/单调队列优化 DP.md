> P3400 仓鼠窝：每行跑单调栈，好像并不是优化 DP 决策，而是优化 DP 计算了？（等同线段树之类的其他 DS）
>
> * 为什么单调栈不优化 DP 决策：单调栈后进先出，假设
>   * 决策时取栈底：那么可以直接在每个元素进来后直接和当前栈底作比较，否则肯定用不上。意味着栈大小不超过 1，也就没有特别定义“后进先出”的意义了。
>   * 决策时取栈顶：单调栈一般情况下当前元素都一定会入栈，然后就直接没意义了。（单调一般是若干二元组 $(w,id)$ 满足偏序关系，加的时候至少要在一维上偏序加入，优化 DP 时一般是 $id$ 单增，这样的话最大的 $id$ 一定会在栈中，也就是**当前元素一定会入栈**）

# 单调队列优化 DP

## 单调队列 - 定义

队列是一种先进先出的数据结构，其队尾可加入元素，队首可取出或弹出元素。单调队列则是在队列的基础上，让队尾可以弹出元素以使队列中从队首到队尾相邻元素均满足定义的偏序关系。在信息学竞赛中，这样的元素多为二元组或三元组，其中一维为数组下标。

如经典问题“滑动窗口”中，题目给定一长度为 $n$ 的数组 $a$，定义 $s_i=\min_{j\in(\max(1,i-k),i]} a_j$，要求出对于任意 $i\in[1,n],s_i$ 的值。

较为常用的解决区间最值问题的数据结构，如线段树、树状数组、ST 表等，均需要 $O(n\log n)$ 的时间复杂度。

而使用单调队列，则可做到 $O(n)$ 的时间复杂度和空间复杂度。具体而言，维护二元组 $(a_i,i)$ 使队列中元素满足严格偏序关系 $\lt=\{((x_1,y_1),(x_2,y_2))\mid x_1\lt x_2\and y_1\lt y_2\}$，下标 $i$ 从小到大遍历 $[1,n]$ 时，加入元素 $(a_i,i)$。若加入元素前队列非空且队尾元素不满足偏序关系，则一直弹出队尾元素直到队列为空或队尾元素满足偏序关系为止。加入元素 $(a_i,i)$ 后，在队首元素第二维 $id$ 不满足 $id\gt i-k$ 时弹出队首元素直至满足条件。因为第二维加入时单调递增，第一维在队列中也单调递增，所以队列中最小值在队首。而在弹出队首操作中满足了队列中所有元素均在 $(i-k,i]$ 中，且先前在队列中且第二维属于 $(i-k,i]$ 的不会因为队首弹出操作在此之前弹出，因此队首元素 $(a_{h},h)$ 的第一维即为 $s_i$。

## 优化 DP

使用单调队列优化 DP 时，往往是题目中有一些条件使得在没有该条件时的最优决策不合法了，因此使用单调队列排除不可能在接下来成为最优决策点的元素，保留其余元素。

### P3572 [POI2014\]PTA-Little Bird

#### 题目描述

给定 $n$ 颗树，第 $i$ 颗树的高度为 $h_i$，有一只鸟要从第 $1$ 颗树飞到第 $n$ 颗树，它的初始劳累值为 $0$。

如果这只鸟当前在第 $i$ 颗树，那么它接下来可以飞到 $i+1,i+2,\dots,i+k$ 颗树。

如果它从一颗高度为 $h_i$ 的树飞到高度为 $h_j$ 的树，且 $h_i\le h_j$，那么它的劳累值会 $+1$，反之若 $h_i\gt h_j$ 那么劳累值不变。

有 $Q$ 次询问，每次询问指定 $k$，求这只鸟从第 $1$ 颗树飞到第 $n$ 颗树的劳累值最少是多少。

$2\le n\le 10^6$，$1\le Q\le 25$

#### 解题思路

设 $dp[i]$ 表示从第 $1$ 颗树飞到第 $i$ 颗树所需的最小劳累值，那么转移有
$$
dp[i]=\min_{j\in[\max(1,i-k),i]}(dp[j]+[h[j]\le h[i]])
$$
其中 $[p]$ 表示若命题 $p$ 为真则值为 $1$，否则为 $0$。这样直接转移是 $O(Qn^2)$ 的，考虑优化。

设 $m_i=\min_{j\in[\max(1,i-k),i]}dp[j]$，不难看出有
$$
\min_{j\in[\max(1,i-k),i]\and dp[j]=m_i}(dp[j]+[h[j]\le h[i]])\le\min_{j\in[\max(1,i-k),i]\and dp[j]\gt m_i}(dp[j]+[h[j]\le h[i]])
$$
因为
$$
\text{左式}\le\min_{j\in[\max(1,i-k),i]\and dp[j]=m_i}(dp[j]+1)\le m_i+1
$$

$$
\text{右式}\ge\min_{j\in[\max(1,i-k),i]\and dp[j]\gt m_i}(dp[j])\ge m_i+1
$$

即证。

因此考虑在每次询问时用类似“滑动窗口”的方式，$O(n)$ 维护 $[\max(1,i-k),i]$ 中 $dp$ 最小值所对应下标。考虑到要取最小值，还要 $+[h[j]\le h[i]]$，对下标递增，$dp$ 值相同的元素，在队列中需要使其 $h$ 值递减。这样取到的队首元素就是合法转移点中，$dp$ 值最小且 $h$ 最大的元素。

整体时间复杂度为 $O(qn)$，空间复杂度为 $O(n)$。

#### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5;
int n,Q,k,h[maxn],dp[maxn];
int q[maxn],hd,tl;
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>h[i];
    cin>>Q;
    while(Q--){
        cin>>k;
        q[hd=tl=1]=1;
        for(int i=2;i<=n;i++){
            while(hd<=tl&&i-q[hd]>k)hd++;
            dp[i]=dp[q[hd]]+(h[q[hd]]<=h[i]);
            while(hd<=tl&&(dp[q[tl]]>dp[i]||(dp[q[tl]]==dp[i]&&h[q[tl]]<=h[i])))tl--;
            q[++tl]=i;
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
```

### P3089 [USACO13NOV] Pogo-Cow S

#### 题目描述

给定 $n$ 个目标点，每个目标点在数轴上有一个坐标 $x_i$ 和一个可获得分数 $p_i$。

定义一个长为 $|p|$ 的序列 $p$ 合法当且仅当 $x_{p_i}$ 关于 $i$ 单调递增或单调递减，且 $\forall i\in[1,|p|-2],|x_{p_i}-x_{p_{i+1}}|\le |x_{p_{i+1}}-x_{p_{i+2}}|$，该序列权值为 $\sum_{i\in[1,|p|]}w_{p_i}$。

试求出所有合法序列的权值的最大值。

$1\le n\le 10^3$

#### 解题思路

单调递减只需令所有 $x_i:=-x_i$ 就可以归约到单调递增的情况，因此下文将仅讨论序列中 $x_{p_i}$ 单调递增的情况。

首先将目标点按 $x$ 排序，记录 $dp[i][\Delta x]$ 表示满足最后一个值为 $i$ 且倒数第二个值与最后一个值对应目标点 $x$ 差值为 $\Delta x$ 的序列中序列权值的最大值，那么应当有
$$
dp[i][x_i-x_j]=\max_{j\in[1,i)\and x'\le x_i-x_j}(dp[j][x'])+p_i
$$
但就算是离散地考虑 $x'$ 一维，这样转移也是 $O(n^3)$ 的，考虑优化。

发现若对于同一 $i$，有 $a\le b$ 且 $dp[i][a]\ge dp[i][b]$，那么忽略 $b$ 不会对任何 $dp[i][x]$ 有影响。而对同一 $j$，在 $i$ 单调递增的情况下，限制产生贡献的 $dp[j][x]$ 的 $x$ 值单调不减。因此考虑对每一个 $i$ 建立一个单调队列，每个元素 $(\Delta x,dp[i][\Delta x])$ 两维均单调递增。在队列内元素个数大于 $1$，且从队首数第二个元素第一维满足限制时，弹出队首元素。这样能够找到可能对 $dp[i][x_i-x_j]$ 产生贡献的最大的满足限制 $x'\le x_i-x_j$ 的 $x'$，对应 $dp[i][x']$ 也是满足限制下的最大值。

这样一共需要 $O(n)$ 个单调队列，每个队列中元素至多 $O(n)$ 个，转移整体时间复杂度为 $O(n^2)$，空间复杂度为 $O(n^2)$。

#### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e3+5;
int n;
struct node{int x,w;}a[maxn];
bool cmp(node a,node b){return a.x<b.x;}
struct Que{
    node v[maxn];
    int tail,head;
    inline void push(node x){
        while(tail&&v[tail].x==x.x&&v[tail].w<=x.w)tail--;
        if(x.w>v[tail].w||!tail)v[++tail]=x;
    }
    inline void pop(int x){
        while(head<tail&&x>=v[head+1].x)head++;
    }
    inline void clear(){
        tail=head=0;
    }
}s[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].w;
    sort(a+1,a+1+n,cmp);
    int ans=0;
    for(int i=1;i<=n;i++){
        s[i].push((node){-1,a[i].w});
        for(int j=i-1;j>=1;j--){
            s[j].pop(a[i].x-a[j].x);
            s[i].push((node){a[i].x-a[j].x,s[j].v[s[j].head].w+a[i].w});
        }
        ans=max(ans,s[i].v[s[i].tail].w);
    }
    for(int i=1;i<=n;i++)s[i].clear();
    for(int i=n;i>=1;i--){
        s[i].push((node){-1,a[i].w});
        for(int j=i+1;j<=n;j++){
            s[j].pop(a[j].x-a[i].x);
            s[i].push((node){a[j].x-a[i].x,s[j].v[s[j].head].w+a[i].w});
        }
        ans=max(ans,s[i].v[s[i].tail].w);
    }
    cout<<ans<<'\n';
    return 0;
}
```
