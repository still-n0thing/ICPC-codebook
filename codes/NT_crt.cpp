ll mod_inv(ll c, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1) return 0;

    while (c > 1){
        ll q = c / m;
        ll t = m;
        m = c % m;
        c = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

ll CRT(vector<pair<ll,ll>> congru) {
    ll M = 1;
    for (auto var : congru) {
        M *= var.second;
    }
    ll solution = 0;
    for (auto var : congru) {
        ll a_i = var.first;
        ll M_i = M / var.second;
        ll N_i = mod_inv(M_i, var.second);
        solution = (solution + a_i * (M_i % M) * N_i) % M;
    }
    return solution;
}