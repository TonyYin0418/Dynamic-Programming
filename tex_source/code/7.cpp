#include <bits/stdc++.h>
using namespace std;
const int maxn = 5005;
int n, a[maxn], s[maxn], dp[maxn][maxn], d[maxn][maxn];
#define w(i, j) (s[j] - s[i - 1])
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		s[i] = s[i - 1] + a[i];
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 1; i <= n; i++)
		dp[i][i] = 0, d[i][i] = i;
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1, j; i + l - 1 <= n; i++)
		{
			j = i + l - 1;
			for (int k = d[i][j - 1]; k <= min(j - 1, d[i + 1][j]); k++)
			{
				int nx = dp[i][k] + dp[k + 1][j] + w(i, j);
				if (nx < dp[i][j])
				{
					dp[i][j] = nx;
					d[i][j] = k;
				}
			}
		}
	}
	cout << dp[1][n] << endl;
	return 0;
}