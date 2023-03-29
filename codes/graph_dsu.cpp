class UnionFind {
    private:
        vector<ll> p, rank, setSize;
        ll numSets;
    public:
        UnionFind(ll N){
            p.assign(N, 0);
            for(ll i = 0; i < N; i++){
                p[i] = i;
            }
            rank.assign(N, 0);
            setSize.assign(N, 1);
            numSets = N;
        }

        ll findSet(ll i){
            if(p[i] == i) return i;
            else return p[i] = findSet(p[i]);
        }

        bool isSameSet(ll i, ll j){
            return findSet(i) == findSet(j); 
        }

        ll sizeOfSet(ll i){
            return setSize[findSet(i)];
        }

        ll numDisjointSets(){
            return numSets; 
        }

        void unionSet(ll i, ll j){
            if(isSameSet(i,j)) return;

            ll x = findSet(i);
            ll y = findSet(j);
            if(rank[x] > rank[y]) swap(x,y);
            p[x] = y; 

            if (rank[x] == rank[y]) rank[y]++;
            setSize[y] += setSize[x];
            numSets--;
        }
};