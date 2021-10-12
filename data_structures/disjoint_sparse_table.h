const int maxn = 1e6;
int fLog2[maxn], cLog2[maxn];
void initLog2(){
  for (int i = 2; i < maxn; i ++){
    fLog2[i] = 1 + fLog2[i >> 1];
    cLog2[i] = 1 + cLog2[(i + 1) >> 1];
  }
}
template<class T> struct disjoint_sp_tb{
  vector<vector<T> > DST; int x, n; T (*m_)(T a, T b);
  disjoint_sp_tb(vector<T>&a,T(*m_)(T a,T b)):m_(m_){
    if (fLog2[2] == 0) initLog2();
    n=a.size(); x=cLog2[n];
    DST.resize(x + 1, vector<T>(n));
    for (int h = 1; h <= x; h ++){
      int s = (1 << h);
      for (int half = 0; half < n - (s >> 1); half += s){
        int R = half + s;
        int M = half + (s >> 1);
        DST[h][M] = a[M];
        for (int i = M - 1; i >= half; i --)
          DST[h][i] = m_(a[i], DST[h][i + 1]);
        if (M + 1 < n) DST[h][M + 1] = a[M + 1];
        for (int i = M + 2; i < n and i < R; i ++)
          DST[h][i] = m_(DST[h][i - 1], a[i]);
      }
    }
    for (int half = 0; half < n; half ++)
      DST[0][half] = a[half];
  }
  T query(int l, int r){
    int h = fLog2[l ^ r] + 1;
    if (l == r) return DST[0][l];
    if (r & ((1 << (h - 1)) - 1)) return m_(DST[h][l], DST[h][r]);
    return DST[h][l];
  }
};