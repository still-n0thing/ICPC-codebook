class Node {
public:
    static const int N = (1 << 8); // 256
    bool is_leaf;
    int next[N];
    int count;

    Node() {
        is_leaf = false;
        count = 0;
        memset(next, -1, sizeof next);
    }
};

class Trie {
public:
    vector<Node> root;

    Trie() {
        root.emplace_back(); // insert a object
    }
    
    void insert(string word) {
        int i = 0;
        for (char c: word) {
            if (root[i].next[c] == -1) {
                root[i].next[c] = root.size();
                root.emplace_back();
            }
            i = root[i].next[c];
        }
        root[i].is_leaf = true;
    }
    
    bool search(string word) {
        int i = 0;
        for (char c: word) {
            if (root[i].next[c] == -1) {
                return false;
            }
            i = root[i].next[c];
        }
        return root[i].is_leaf;
    }
    
    bool startsWith(string prefix) {
        int i = 0;
        for (char c: prefix) {
            if (root[i].next[c] == -1) {
                return false;
            }
            i = root[i].next[c];
        }
        return true;
    }
};
