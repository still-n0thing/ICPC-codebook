template<typename Info>
class SegTree {
public:
    int n;
    vector<Info> info;

    SegTree(int _n) {
        n = _n;
        info = vector<Info>(4 * n + 1);
    }

    SegTree(const vector<Info> &init) : SegTree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int l, int r) -> void {
            if(l == r) {
                info[p] = init[l];
                return;
            } 
            int m = l + (r - l) / 2;
            build(2 * p + 1, l, m);
            build(2 * p + 2, m + 1, r);
        };
        build(0, 0, n - 1);
    }

    void pull(int p) {
        info[p] = info[2 * p + 1] + info[2 * p + 2];
    }

    void modify(int p, int l, int r, int x, const Info& v) {
        if(r == l) {
            info[p] = v;
            return;
        }

        int m = l + (r - l) / 2;
        if(x <= m) {
            modify(2 * p + 1, l, m, x, v);
        } else {
            modify(2 * p + 2, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info& v) {
        modify(0, 0, n - 1, p, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y) {
        if(y < l or r < x) {
            return Info();
        }

        if(x <= l and r <= y) {
            return info[p];
        }

        int m = l + (r - l) / 2;
        return rangeQuery(2 * p + 1, l, m, x, y) + rangeQuery(2 * p + 2, m + 1, r, x, y);
    }

    Info rangeQuery(int l, int r) {
        return rangeQuery(0, 0, n - 1, l, r);
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
    
};

Sum operator+(const Sum &lf, const Sum &rt) {
    return Sum(lf.x + rt.x);
}

class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        const int n = (int)nums1.size();
        SegTree<Sum> st(1e5 + 2);
        
        int shift = 1e4;
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            int lf = nums1[i] - nums2[i] + 2 * shift;
            ans += st.rangeQuery(0, lf + diff).x;
            int val = st.rangeQuery(lf, lf).x;
            st.modify(lf, Sum(val + 1));
        }
        return ans;
    }
};
