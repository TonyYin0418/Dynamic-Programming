#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const double eps = 1e-6;
inline int read()
{
	int x = 0, f = 1, ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 3) + (x << 1) + ch - 48;
		ch = getchar();
	}
	return x * f;
}
int n;
ll f[maxn], s[maxn];
struct node
{
	int h, id;
	ll s;
} a[maxn];
bool cmph(node a, node b) { return a.h < b.h; }
bool cmpid(node a, node b) { return a.id < b.id; }
int q[maxn], hd = 1, tl;
double slope(int u, int v)
{
	ll uy = f[a[u].id] - a[u].s + (1ll) * a[u].h * a[u].h;
	ll vy = f[a[v].id] - a[v].s + (1ll) * a[v].h * a[v].h;
	if (a[u].h == a[v].h)
	{
		return vy > uy ? 1e18 : -1e18;
	}
	return (uy - vy) * 1.0 / (a[u].h - a[v].h);
}
void cdq(int l, int r)
{
	if (l >= r)
		return;
	int mid = l + r >> 1;
	cdq(l, mid);
	sort(a + l, a + mid + 1, cmph);
	sort(a + mid + 1, a + r + 1, cmph);
	//斜率优化
	for (int i = l; i <= mid; i++)
	{
		while (tl > 1 && slope(q[tl], i) < slope(q[tl - 1], q[tl]))
			tl--;
		q[++tl] = i;
	}
	for (int j = mid + 1; j <= r; j++)
	{
		while (hd < tl && slope(q[hd], q[hd + 1]) <= 2.0 * a[j].h + eps)
			hd++;
		if (hd <= tl)
			f[a[j].id] = min(f[a[j].id], s[a[j].id - 1] + (1ll) * a[j].h * a[j].h + f[a[q[hd]].id] - a[q[hd]].s + (1ll) * a[q[hd]].h * a[q[hd]].h - 2ll * a[j].h * a[q[hd]].h);
	}
	hd = 1, tl = 0;
	sort(a + mid + 1, a + r + 1, cmpid);
	cdq(mid + 1, r);
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		a[i].h = read(), a[i].id = i;
	for (int i = 1; i <= n; i++)
		a[i].s = a[i - 1].s + read(), s[i] = a[i].s;
	memset(f, 0x3f, sizeof(f));
	f[1] = 0;
	cdq(1, n);
	cout << f[n] << '\n';
	return 0;
}