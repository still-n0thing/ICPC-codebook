deque<line> dq;
vector<int> ints(n);
iota(ints.begin(), ints.end(), 0);
auto cmp = [&dq](int idx, int x) { return dq[idx].intersectX(dq[idx + 1]) < x; };
dq.push_front({0, 0});
long long ans = 0;
for (int i = 1; i <= n; i++) {
    int idx = *lower_bound(ints.begin(), ints.begin() + dq.size() - 1, a[i].q, cmp);
    long long f = dq[idx].eval(rects[i].q) + rects[i].p * 1LL * rects[i].q - rects[i].a;
    ans = max(ans, f);
    line cur = {-rects[i].p, f};
    while (dq.size() >= 2 && cur.intersectX(dq[0]) >= dq[0].intersectX(dq[1]))
        dq.pop_front();
    dq.push_front(cur);
}
