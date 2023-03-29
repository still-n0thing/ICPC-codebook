ll mod_inv(ll c, ll m){
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1) return 0;
    while (c > 1){
        ll q = c / m, t = m;
        m = c % m;
        c = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}