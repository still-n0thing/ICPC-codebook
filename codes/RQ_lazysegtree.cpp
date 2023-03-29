template<typename I, typename T>
class LazySegTree {
public:
    int n;
    vector<I> info;
    vector<T> tag;

    LazySegTree(int _n) {
        n = _n;
        info = vector<I>(4 * n + 1);
        tag = vector<T>(4 * n + 1);
    }

    LazySegTree(const vector<I> &init) : LazySegTree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int l, int r) -> void {
            if(r == l) {
                info[p] = init[l];
                return;
            }
            int m = l + (r - l) / 2;
            build(2 * p + 1, l, m);
            build(2 * p + 2, m + 1, r);
            pull(p);
        };
        build(0, 0, n - 1);
    }

    void pull(int p) {
        info[p] = info[2 * p + 1] + info[2 * p + 2];
    }

    void apply(int p, const T &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p) {
        apply(2 * p + 1, tag[p]);
        apply(2 * p + 2, tag[p]);
        tag[p] = T();
    }

    void modify(int p, int l, int r, int x, const I &v) {
        if(r == l) {
            info[p] = v;
            return;
        }

        int m = l + (r - l) / 2;
        push(p);
        if(x <= m) {
            modify(2 * p + 1, l, m, x, v);
        } else {
            modify(2 * p + 2, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const I &v) {
        modify(0, 0, n - 1, p, v);
    }

    I rangeQuery(int p, int l, int r, int x, int y) {
        if(y < l or r < x) {
            return I();
        }

        if(x <= l and r <= y) {
            return info[p];
        }

        int m = l + (r - l) / 2;
        push(p);
        return rangeQuery(2 * p + 1, l, m, x, y) + rangeQuery(2 * p + 2, m + 1, r, x, y);
    }

    I rangeQuery(int l, int r) {
        return rangeQuery(0, 0, n - 1, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const T &v) {
        if(y < l or r < x) {
            return;
        }

        if(x <= l and r <= y) {
            apply(p, v);
            return;
        }

        int m = l + (r - l) / 2;
        push(p);
        rangeApply(2 * p + 1, l, m, x, y, v);
        rangeApply(2 * p + 2, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const T &v) {
        return rangeApply(0, 0, n - 1, l, r, v);
    }
};

class Tag {
public:
    long long x = 0;
    
    Tag() {}
    
    Tag(long long _x) {
        x = _x;
    }
    
    void apply(const Tag &t) {
        x += t.x;
    }
};

class Sum {
public:
    long long x = 0;
    int index = -1;
    
    Sum() {}
    
    Sum(long long _x) {
        x = _x;
    }
    
    Sum(long long _x, int _index) {
        x = _x;
        index = _index;
    }
    
    void apply(const Tag &t) {
        x += t.x;
    }
};

Sum operator+(const Sum &lf, const Sum &rt) {
    return Sum(lf.x + rt.x);
}

class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        const int n = (int)s.size();
        LazySegTree<Sum, Tag> st(n);
        for(const auto& v: shifts) {
            st.rangeApply(v[0], v[1], Tag(v[2]? +1: -1));
        }
        for(int i = 0; i < n; i++) {
            int val = st.rangeQuery(i, i).x;
            s[i] = (((s[i] - 'a' + val) % 26 + 26) % 26) +'a';
        }
        return s;
    }
};