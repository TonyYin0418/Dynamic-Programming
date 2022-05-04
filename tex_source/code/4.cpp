#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
int n, Q, k, h[maxn], dp[maxn];
int q[maxn], hd, tl;
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> h[i];
	cin >> Q;
	while (Q--)
	{
		cin >> k;
		q[hd = tl = 1] = 1;
		for (int i = 2; i <= n; i++)
		{
			while (hd <= tl && i - q[hd] > k)
				hd++;
			dp[i] = dp[q[hd]] + (h[q[hd]] <= h[i]);
			while (hd <= tl && (dp[q[tl]] > dp[i] || (dp[q[tl]] == dp[i] && h[q[tl]] <= h[i])))
				tl--;
			q[++tl] = i;
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}