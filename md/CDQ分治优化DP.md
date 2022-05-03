# CDQ 分治优化 DP

## CDQ 分治

### 定义

CDQ 分治最早为陈丹琦在《从\<cash\>谈一类分治算法的应用》（2008国家集训队作业）中整理的，因此以 CDQ 命名。陈丹琦本人整理的 CDQ 分治应用方法主要为先将在线维护的问题转换为离线问题，并添加一个操作时间的维度，再对高维的偏序问题进行分治处理。后来引申的 CDQ 分治应用范围则包括了可离线的高维偏序问题以及转移包括高维偏序条件的动态规划问题。下文将探讨 CDQ 分治对转移包括高维偏序条件的动态规划问题的优化。

## 应用实例

### 长者

#### 题目描述

给定一个长度为 $n$ 的排列 $a$，其中有若干位置上的数字已经确定了，剩下位置上的数字不确定。

你需要钦定未被确定的位置上的数字，使得得到的排列的最长上升子序列（LIS，Longest Increasing Subsequence）长度尽量长。试求出这个最长长度。

$n\leq 10^5$

#### 解题思路

注意到 “是一个排列” 这个限制，事实上仅仅限制了那些未被确定的位置上的数字不能与已经确定的位置相同，而我们在计算最优答案时并不需要特别处理未被确定的数字之间是否相同，因为 LIS 中不能出现两个相同的数字，因此剩下位置上出现相同数字一定不优。

设 $f(i,j)$ 表示对于 $a$ 数组长度为 $i$ 的前缀，在所有钦定方案中，以 $j$ 结尾的最长的 LIS 长度。有转移：

* 若位置 $i$ 被确定了，则 $f(i,x)=\begin{cases}\max_{j\lt p_i}(f(i-1,j))+1&x=p_i\\0&x\not=p_i\end{cases}$；

* 否则 $f(i,j)=\max\{\max_{k\lt j}(f(i-1,k))+1,f(i-1,j)\}$，这里的 $j$ 必须不在已经确定的数字中出现过。

这样直接转移是 $O(n^2)$ 的。

但是二维 dp 是不方便使用 CDQ 分治优化的，仍然考虑转成一维 dp 的形式。

设 $f(i)$ 表示以位置 $i$ 结尾的最长 LIS，此处位置 $i$ 的数字必须被确定了。

则枚举 LIS 中上一个有确定数字的位置，可以得到：

$$
f(i)=\max_{p_j\lt p_i}(f(j)+\min\{cnt[i]-cnt[j],rem[p_i]-rem[p_j]\})+1
$$
其中，$cnt[i]$ 表示 $a$ 长度为 $i$ 的前缀中没被确定的位置个数，$rem[p_i]$ 表示 $< p_i$ 且未出现在被确定的位置的数字个数。

注意到这里同时有 $p_j<p_i$ 和 $j<i$ 两个限制，且中间的 $\min$ 可以分类讨论为两种情况：

1. $cnt[i]-cnt[j]>=rem[p_i]-rem[p_j] \iff cnt[i]-rem[p_i]>=cnt[j]-rem[p_j]$
2. $cnt[i]-cnt[j]<rem[p_i]-rem[p_j] \iff cnt[i]-rem[p_i]<cnt[j]-rem[p_j]$

这也就相当于第三个限制，加上前两个就是三维偏序。因此我们先按下标分治，然后左右两边分别按 $cnt[i]-rem[p_i]$ 排序，以第一种情况为例，双指针扫的时候用树状数组维护 $f(j)-rem[p_j]$ 即可。

整体时间复杂度 $O(n \log^2 n)$，空间复杂度 $O(n)$。

#### 代码实现

```cpp
//a[i].x=id,a[i].y=cnt[i]-rem[p[i]],a[i].tp=(p[i]>0);
void cdq(int l,int r){
    if(l>=r)return ;
    int mid=(l+r)>>1;
    cdq(l,mid);
    sort(a+l,a+mid+1,cmpy);
    sort(a+mid+1,a+r+1,cmpy);
    int i=l,j=mid+1;
    for(;j<=r;j++){
        if(!a[j].tp)continue;
        while(i<=mid&&a[i].y<=a[j].y)
        	{if(a[i].tp)upd(a[i].p,a[i].f-rem[a[i].p]);i++;}
        a[j].f=max(a[j].f,qry(a[j].p)+rem[a[j].p]+1);
    }for(j=l;j<i;j++)if(a[j].tp)clr(a[j].p);
    i=mid;j=r;
    for(;j>mid;j--){
        while(i>=l&&a[i].y>a[j].y)
        	{if(a[i].tp)upd(a[i].p,a[i].f-cnt[a[i].p]);i++;}
        a[j].f=max(a[j].f,qry(a[j].p)+cnt[a[j].p]+1);
    }for(j=mid;j>i;j--)if(a[j].tp)clr(a[j].p);
    sort(a+l,a+r+1,cmpx);
    cdq(mid+1,r);
}
```

### P4655 Building Bridges

#### 题目描述

给定 $n$​​ 个柱子，每个柱子用 $(h_i,w_i)$​​ 描述。拆除第 $i$​ 根柱子的代价为 $w_i$​。在 $i,j$​ 之间架桥的代价为 $(h_i-h_j)^2$​​​，同时还需要拆除 $[i+1,j-1]$​ 之间的所有柱子。求通过桥梁把 $1$​ 和 $n$​​​ 连通的最小代价。

$2\leq n\leq 10^5$，$0\leq h_i,|w_i|\leq 10^6$​

#### 解题思路

不妨设 $dp[i]$ 为通过桥梁将 $1$ 和 $i$ 联通的最小代价，$s_i=\sum_{i\in[1,i]}w_i$，不难得到
$$
dp[i]=\min_{j\lt i}(dp[j]+s_{i-1}-s_j+(h_i-h_j)^2)
$$
将 $\min$ 去掉可以得到
$$
(dp[j]-s_j+h_j^2)=h_i\times(2h_j)-(s_{i-1}+h_i^2)+dp[i]
$$

发现能斜率优化，然而直接进行斜率优化需要满足斜率 $2h_j$ 单调，因此考虑 CDQ 分治。具体来讲，以第一维为下标，计算 $cdq(l,r)$ 时，令 $mid=\lfloor\frac{l+r}{2}\rfloor$，对 $[l,mid]$ 中的下标 $i$ 直接计算出由 $(dp[i]-s_i+h_i^2,h_i)$ 构成的下凸包 ，$[mid+1,r]$ 中的元素按照 $h$ 排序然后做斜率优化 DP 计算贡献即可。

#### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
const double eps=1e-6;
inline int read(){
    int x=0,f=1,ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
    return x*f;
}
int n;
ll f[maxn],s[maxn];
struct node{int h,id;ll s;}a[maxn];
bool cmph(node a,node b){return a.h<b.h;}
bool cmpid(node a,node b){return a.id<b.id;}
int q[maxn],hd=1,tl;
double slope(int u,int v){
    ll uy=f[a[u].id]-a[u].s+(1ll)*a[u].h*a[u].h;
    ll vy=f[a[v].id]-a[v].s+(1ll)*a[v].h*a[v].h;
    if(a[u].h==a[v].h){return vy>uy?1e18:-1e18;}
    return (uy-vy)*1.0/(a[u].h-a[v].h);
}
void cdq(int l,int r){
    if(l>=r)return ;
    int mid=l+r>>1;
    cdq(l,mid);
    sort(a+l,a+mid+1,cmph);
    sort(a+mid+1,a+r+1,cmph);
    //斜率优化
    for(int i=l;i<=mid;i++){
        while(tl>1&&slope(q[tl],i)<slope(q[tl-1],q[tl]))tl--;
        q[++tl]=i;
    }
    for(int j=mid+1;j<=r;j++){
        while(hd<tl&&slope(q[hd],q[hd+1])<=2.0*a[j].h+eps)hd++;
        if(hd<=tl)f[a[j].id]=min(f[a[j].id],s[a[j].id-1]+(1ll)*a[j].h*a[j].h+f[a[q[hd]].id]-a[q[hd]].s+(1ll)*a[q[hd]].h*a[q[hd]].h-2ll*a[j].h*a[q[hd]].h);
    }hd=1,tl=0;
    sort(a+mid+1,a+r+1,cmpid);
    cdq(mid+1,r);
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)a[i].h=read(),a[i].id=i;
    for(int i=1;i<=n;i++)a[i].s=a[i-1].s+read(),s[i]=a[i].s;
    memset(f,0x3f,sizeof(f));f[1]=0;
    cdq(1,n);
    cout<<f[n]<<'\n';
    return 0;
}
```

