template<class T> struct IterativeSegmentTree{
    int n; vector<T> ST; T (*merge)(T, T);
    IterativeSegmentTree(vector<T> &a, T (*merge)(T, T)) : merge(merge){
        n = a.size(); ST.resize(n << 1);
        for (int i = n; i < (n << 1); i ++)
            ST[i] = a[i - n];
        for (int i = n - 1; i > 0; i --)
            ST[i] = merge(ST[i << 1], ST[i << 1 | 1]);
    }
    void update(int pos, T val){
        ST[pos += n] = val;
        for (pos >>= 1; pos > 0; pos >>= 1)
            ST[pos] = merge(ST[pos << 1], ST[pos << 1 | 1]);
    }
    T query(int l, int r){
        T ansL, ansR; bool hasL = 0, hasR = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) 
                ansL = (hasL ? merge(ansL, ST[l ++]) : ST[l ++]), hasL = 1;
            if (r & 1) 
                ansR = (hasR ? merge(ST[ --r], ansR) : ST[ --r]), hasR = 1;
        }
        if (!hasL) return ansR;
        if (!hasR) return ansL;
        return merge(ansL, ansR);
    }
};