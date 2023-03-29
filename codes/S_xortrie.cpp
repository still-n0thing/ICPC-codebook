class Trie {
private:
    static const int N = 2;
    
    class Node {
    public:
        int next[N];
        bool leaf;
        
        Node() {
            memset(next, -1, sizeof next);
            leaf = false;
        }
    };
public:
    vector<Node> root;
    
    Trie() {
        root = vector<Node>(1);
    }
    
    void insert(int num) {
        int v = 0;
        for(int i = 30; i >= 0; i--) {
            int c = ((1 << i) & num) > 0; 
            if(root[v].next[c] == -1) {
                root[v].next[c] = (int)root.size();
                root.emplace_back();
            }
            v = root[v].next[c];
        }
        root[v].leaf = true;
    }
    
    int query(int num) {
        int v = 0, res = 0;
        for(int i = 30; i >= 0; i--) {
            int sb = ((1 << i) & num), c = 1;
            if(sb > 0) c = 0;
            if(root[v].next[c] != -1) res += (1 << i);
            else c ^= 1;
            v = root[v].next[c];
        }
        return res;
    }
    
};

class Solution {
public:
    int findMaximumXOR(vector<int>& a) { // pair
        const int n = (int)a.size();
        Trie t;
        for(int i = 0; i < n; i++) t.insert(a[i]);
        int ans = INT_MIN;
        for(int i = 0; i < n; i++) ans = max(ans, t.query(a[i]));
        return ans;
    }
};