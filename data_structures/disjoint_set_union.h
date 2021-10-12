struct union_find{
	int n; vector<int>S;
	vector<int>parent;
	union_find(int n):n(n){
		S.assign(n, 1);
		parent.assign(n, 0);
		for (int i = 1; i < n; i ++)
			parent[i] = i;
	}
	int find_set(int a){
		if (parent[a] == a)
			return a;
		return parent[a]=find_set(parent[a]);
	}
	void union_set(int a, int b) {
		a = find_set(a); b = find_set(b);
		if (a == b) return;
		if (S[a] > S[b]) swap(a, b);
		parent[a] = b;
		S[b] += S[a];
	}
	bool same_set(int a, int b){
		return find_set(a)==find_set(b);
	}
	void add_set(){
		parent.pb(n++);
		S.pb(1);
	}
};