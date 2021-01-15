#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
#define MOD 998244353
#define ll long long int
ll mul(ll x, ll y) {ll res = x * y; return (res >= MOD ? res % MOD : res);}
ll power(ll x, ll y) {if (y < 0) return 1; ll res = 1; x %= MOD; while (y) {if (y & 1)res = mul(res, x); y >>= 1; x = mul(x, x);} return res;}
ll inv(ll x) {return power(x, MOD - 2);}

const int N = 1 << 20;
const int M = 100005;

ll a[N], b[N], c[N];
int ext, bit;

void fwht_or(ll *f, int opt)
{
    for (int l = 2, k = 1; l <= ext; l <<= 1, k <<= 1) {
        for (int i = 0; i < ext; i += l) {
            for (int j = 0; j < k; j++) {
                f[i + j + k] = (f[i + j + k] + f[i + j] * opt) % MOD;
            }
        }
    }
}

void fwht_and(ll *f, int opt) {
    for (int l = 2, k = 1; l <= ext; l <<= 1, k <<= 1) {
        for (int i = 0; i < ext; i += l) {
            for (int j = 0; j < k; j++) {
                f[i + j] = (f[i + j] + f[i + j + k] * opt) % MOD;
            }
        }
    }
}
int main ()
{
    int t, n, m, x;
    cin >> t;
    while (t--)
    {
        int mx = 0;
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        cin >> n >> m;
        for (ll i = 1; i <= n; i++) {
            cin >> x;
            ++a[x];
            mx = max(mx, x);
        }

        a[0] = c[0] = 1;
        for (ll i = 1; i <= m; i++) {
            cin >> x;
            ++b[x];
            mx = max(mx, x);
        }

        bit = 0;
        while ((1 << bit) <= mx)
            ++bit;

        bit = min(bit + 1, 20);
        ext = 1 << bit;
        b[ext - 1] = 1;

        fwht_or(a, 1);
        for (ll i = 0; i <= ext - 1; i++)
            a[i] = power(a[i], 1800);
        fwht_and(b, 1);
        for (ll i = 0; i <= ext - 1; i++)
            b[i] = power(b[i], 1800);

        for (ll i = 0; i <= 20; i++)
        {
            fwht_or(c, 1);
            for (ll j = 0; j <= ext - 1; j++)
                c[j] = c[j] * a[j] % MOD;
            fwht_or(c, MOD - 1);
            fwht_and(c, 1);
            for (ll j = 0; j <= ext - 1; j++)
                c[j] = c[j] * b[j] % MOD;
            fwht_and(c, MOD - 1);
        }
        int ans = 0;
        for (ll i = 0; i <= ext - 1; i++) {
            if (c[i])++ans;
        }
        cout << ans << "\n";
    }

    return 0;
}