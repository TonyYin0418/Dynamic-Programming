#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e3 + 5;
int n;
struct node
{
    int x, w;
} a[maxn];
bool cmp(node a, node b) { return a.x < b.x; }
struct Que
{
    node v[maxn];
    int tail, head;
    inline void push(node x)
    {
        while(tail && v[tail].x == x.x && v[tail].w <= x.w) tail--;
        if(x.w > v[tail].w || !tail) v[++tail] = x;
    }
    inline void pop(int x)
    {
        while(head < tail && x >= v[head + 1].x) head++;
    }
    inline void clear()
    {
        tail = head = 0;
    }
} s[maxn];
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i].x >> a[i].w;
    sort(a + 1, a + 1 + n, cmp);
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        s[i].push((node){-1, a[i].w});
        for(int j = i - 1; j >= 1; j--)
        {
            s[j].pop(a[i].x - a[j].x);
            s[i].push((node){a[i].x - a[j].x, s[j].v[s[j].head].w + a[i].w});
        }
        ans = max(ans, s[i].v[s[i].tail].w);
    }
    for(int i = 1; i <= n; i++) s[i].clear();
    for(int i = n; i >= 1; i--)
    {
        s[i].push((node){-1, a[i].w});
        for(int j = i + 1; j <= n; j++)
        {
            s[j].pop(a[j].x - a[i].x);
            s[i].push((node){a[j].x - a[i].x, s[j].v[s[j].head].w + a[i].w});
        }
        ans = max(ans, s[i].v[s[i].tail].w);
    }
    cout << ans << '\n';
    return 0;
}