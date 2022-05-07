#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e3 + 5, maxp = 305;
int n, p, dp[maxn][maxp], d[maxn][maxp], x[maxn], s[maxn];
inline int w(int l, int r)
{
    int mid = l + r >> 1;
    int res = s[r] - s[mid] - x[mid] * (r - mid);
    res += x[mid] * (mid - l) - (s[mid - 1] - s[l - 1]);
    return res;
}
int main()
{
    cin >> n >> p;
    for(int i = 1; i <= n; i++) cin >> x[i];
    sort(x + 1, x + 1 + n);
    for(int i = 1; i <= n; i++) s[i] = s[i - 1] + x[i];
    for(int i = 1; i <= p; i++) d[n + 1][i] = n;
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for(int j = 1; j <= p; j++)
        for(int i = n; i >= 1; i--)
            for(int k = d[i][j - 1]; k <= d[i + 1][j]; k++)
            {
                int nx = dp[k][j - 1] + w(k + 1, i);
                if(nx < dp[i][j])
                    dp[i][j] = nx, d[i][j] = k;
            }
    cout << dp[n][p] << '\n';
    return 0;
}