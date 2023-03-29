const int MOD = 998244353; // prime modulo for NTT
const int PRIMITIVE_ROOT = 3; // primitive root of MOD

int power(int a, int b, int mod) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = (1LL * res * a) % mod;
        a = (1LL * a * a) % mod;
        b >>= 1;
    }
    return res % mod;
}

int inverse(int a, int mod) {
    return power(a, mod - 2, mod);
}

void ntt(vector<int>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? inverse(power(PRIMITIVE_ROOT, (MOD - 1) / len, MOD), MOD) :
                             power(PRIMITIVE_ROOT, (MOD - 1) / len, MOD);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j], v = (1LL * a[i + j + len / 2] * w) % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = (1LL * w * wlen) % MOD;
            }
        }
    }
    if (invert) {
        int n_inv = inverse(n, MOD);
        for (int i = 0; i < n; i++) {
            a[i] = (1LL * a[i] * n_inv) % MOD;
        }
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int n = 1, sz_a = a.size(), sz_b = b.size();
    while (n < sz_a + sz_b) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++) {
        a[i] = (1LL * a[i] * b[i]) % MOD;
    }
    ntt(a, true);
    // added later (to fix the size)
    while((int)a.size() > sz_a + sz_b - 1) a.pop_back();
    return a;
}
