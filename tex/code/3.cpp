#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
int a, b, num[MAXN];
int dp[MAXN][MAXN];
int dfs(int pos, int lst, bool lim, bool zero)
{
	if (pos == 0)
		return 1;
	if (!lim && !zero && dp[pos][lst] != -1)
		return dp[pos][lst];
	int ret = 0;
	int mx = lim ? num[pos] : 9;
	for (int i = 0; i <= mx; i++)
		if (abs(i - lst) >= 2)
			ret += dfs(pos - 1, (zero & (i == 0)) ? -2 : i,
					   lim & (i == num[pos]), zero & (i == 0));
	if (!lim && !zero)
		dp[pos][lst] = ret;
	return ret;
}
int solve(int x)
{
	int p = 0;
	while (x)
		num[++p] = x % 10, x /= 10;
	memset(dp, -1, sizeof(dp));
	return dfs(p, -2, 1, 1);
}
int main()
{
	cin >> a >> b;
	cout << solve(b) - solve(a - 1) << endl;
	return 0;
}