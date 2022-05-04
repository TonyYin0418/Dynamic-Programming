#include <bits/stdc++.h>
using namespace std;
long long n, k, f[15][105][(1 << 9)];
#define pc __builtin_popcount
int main()
{
	cin >> n >> k;
	f[0][0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int S1 = 0; S1 < (1 << n); S1++)
		{
			if ((S1 & (S1 << 1)) == 0)
			{
				for (int S2 = 0; S2 < (1 << n); S2++)
				{
					if (((S2 & (S2 << 1)) == 0) && (((S1 & S2) || (S1 & (S2 << 1)) || (S1 & (S2 >> 1))) == 0))
					{
						for (int j = 0; j <= k; j++)
						{
							f[i][j + pc(S2)][S2] += f[i - 1][j][S1];
						}
					}
				}
			}
		}
	}
	long long ans = 0;
	for (int S = 0; S < (1 << n); S++)
		ans += f[n][k][S];
	cout << ans << endl;
	return 0;
}