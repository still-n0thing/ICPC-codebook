vector<ll> phi_1_to_n(ll n) {
    vector<ll> phi(n + 1);
    for (ll i = 0; i <= n; i++)
        phi[i] = i;
    
    for (ll i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (ll j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}