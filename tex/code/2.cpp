#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 505, maxs = (1 << 8), prn = 8, pr[prn] = {2, 3, 5, 7, 11, 13, 17, 19};
int n, mod;
struct num
{
    int v, key, S;
} a[maxn];
bool cmp(num a, num b) { return a.key == b.key ? a.v < b.v : a.key < b.key; }
int f[maxs][maxs], dp1[maxs][maxs], dp2[maxs][maxs], _dp1[maxs][maxs], _dp2[maxs][maxs];
inline void upd(int &x, int y)
{
    x = x + y;
    if(x >= mod) x -= mod;
}
int main()
{
    cin >> n >> mod;
    for(int i = 1; i < n; i++)
    {
        a[i].v = a[i].key = i + 1;
        for(int j = 0; j < prn; j++)
        {
            if(!(a[i].key % pr[j])) a[i].S |= (1 << j);
            while(!(a[i].key % pr[j])) a[i].key /= pr[j];
        }
    }
    sort(a + 1, a + n, cmp);
    f[0][0] = 1;
    int st = 1;
    while(a[st].key == 1)
    {
        memset(_dp1, 0, sizeof(_dp1));
        for(int s1 = 0; s1 < (1 << prn); s1++)
            for(int s2 = 0; s2 < (1 << prn); s2++)
            {
                upd(_dp1[s1 | a[st].S][s2], f[s1][s2]);
                upd(_dp1[s1][s2 | a[st].S], f[s1][s2]);
            }
        for(int s1 = 0; s1 < (1 << prn); s1++)
            for(int s2 = 0; s2 < (1 << prn); s2++)
                upd(f[s1][s2], _dp1[s1][s2]);
        st++;
    }
    for(int i = st; i < n; i++)
    {
        if(a[i].key != a[i - 1].key)
            for(int s1 = 0; s1 < (1 << prn); s1++)
                for(int s2 = 0; s2 < (1 << prn); s2++)
                    dp1[s1][s2] = dp2[s1][s2] = f[s1][s2];
        memset(_dp1, 0, sizeof(_dp1));
        memset(_dp2, 0, sizeof(_dp2));
        for(int s1 = 0; s1 < (1 << prn); s1++)
            for(int s2 = 0; s2 < (1 << prn); s2++)
            {
                upd(_dp1[s1 | a[i].S][s2], dp1[s1][s2]);
                upd(_dp2[s1][s2 | a[i].S], dp2[s1][s2]);
            }
        for(int s1 = 0; s1 < (1 << prn); s1++)
            for(int s2 = 0; s2 < (1 << prn); s2++)
                upd(dp1[s1][s2], _dp1[s1][s2]),
                    upd(dp2[s1][s2], _dp2[s1][s2]);
        if(a[i].key != a[i + 1].key)
            for(int s1 = 0; s1 < (1 << prn); s1++)
                for(int s2 = 0; s2 < (1 << prn); s2++)
                    f[s1][s2] = ((dp1[s1][s2] + dp2[s1][s2]) % mod - f[s1][s2] + mod) % mod;
    }
    int ans = 0;
    for(int s1 = 0; s1 < (1 << prn); s1++)
        for(int s2 = 0; s2 < (1 << prn); s2++)
            if((s1 & s2) == 0) upd(ans, f[s1][s2]);
    cout << ans << '\n';
    return 0;
}