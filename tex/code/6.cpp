#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 5e4 + 10;
int n, L;
int c[MAXN], s[MAXN], f[MAXN];
double slope(int i, int j)
{
	return ((f[j] + (s[j] + L) * (s[j] + L)) - (f[i] + (s[i] + L) * (s[i] + L))) / (double)(s[j] - s[i]);
}
int head, tail, q[MAXN];
signed main()
{
	scanf("%lld%lld", &n, &L);
	L += 1;
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &c[i]);
		s[i] = s[i - 1] + c[i] + 1;
	}
	head = tail = 1;
	for (int i = 1; i <= n; i++)
	{
		while (head < tail && slope(q[head], q[head + 1]) <= 2 * s[i])
		{
			head++;
		}
		f[i] = f[q[head]] + (s[i] - s[q[head]] - L) * (s[i] - s[q[head]] - L);
		while (head < tail && slope(q[tail - 1], q[tail]) >= slope(q[tail], i))
		{
			tail--;
		}
		q[++tail] = i;
	}
	printf("%lld", f[n]);
	return 0;
}