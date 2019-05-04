// LOJ 6004 / Luogu 3254
#include <bits/stdc++.h>

using namespace std;

#define TemplateVersion "3.4.1"
// Useful Marcos
//====================START=====================
// Compile use C++11 and above
#ifdef LOCAL
#define debug(args...)                       \
  {                                          \
    string _s = #args;                       \
    replace(_s.begin(), _s.end(), ',', ' '); \
    stringstream _ss(_s);                    \
    istream_iterator<string> _it(_ss);       \
    err(_it, args);                          \
  }
void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " = " << a << endl;
  err(++it, args...);
}
#define MSG cout << "Finished" << endl
#else
#define debug(args...)
#define MSG
#endif
#if __cplusplus >= 201703L
template <typename... Args>
void readln(Args &... args) {
  ((cin >> args), ...);
}
template <typename... Args>
void writeln(Args... args) {
  ((cout << args << " "), ...);
  cout << endl;
}
#elif __cplusplus >= 201103L
void readln() {}
template <typename T, typename... Args>
void readln(T &a, Args &... args) {
  cin >> a;
  readln(args...);
}
void writeln() { cout << endl; }
template <typename T, typename... Args>
void writeln(T a, Args... args) {
  cout << a << " ";
  writeln(args...);
}
#endif
#if __cplusplus >= 201103L
#define FOR(_i, _begin, _end) for (auto _i = _begin; _i < _end; _i++)
#define FORR(_i, _begin, _end) for (auto _i = _begin; _i > _end; _i--)
#else
#define FOR(_i, _begin, _end) for (int _i = (int)_begin; _i < (int)_end; _i++)
#define FORR(_i, _begin, _end) for (int _i = (int)_begin; _i > (int)_end; _i--)
#define nullptr NULL
#endif
#if __cplusplus >= 201103L
#define VIS(_kind, _name, _size) \
  vector<_kind> _name(_size);    \
  for (auto &i : _name) cin >> i;
#else
#define VIS(_kind, _name, _size) \
  vector<_kind> _name;           \
  _name.resize(_size);           \
  for (int i = 0; i < _size; i++) cin >> _name[i];
#endif
// alias
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define tcase() \
  int T;        \
  cin >> T;     \
  FOR(kase, 1, T + 1)
// Swap max/min
template <typename T>
bool smax(T &a, const T &b) {
  if (a > b) return false;
  a = b;
  return true;
}
template <typename T>
bool smin(T &a, const T &b) {
  if (a < b) return false;
  a = b;
  return true;
}
// ceil divide
template <typename T>
T cd(T a, T b) {
  return (a + b - 1) / b;
}
// min exchange
template <typename T>
bool se(T &a, T &b) {
  if (a < b) return false;
  swap(a, b);
  return true;
}
// A better MAX choice
const int INF = 0x3f3f3f3f;
const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef set<int> si;
typedef vector<string> cb;
//====================END=====================

// Constants here
const int MAXN = 1e4 + 10;
const int MAXM = 5e4 + 10;

const int BOUND = 150;

struct Dinic {
  int s, t, n, m;
  int cnt;

  struct Edge {
    int to, next, rev;
    ll cap;
  } E[MAXM << 1];

  int last[MAXN];
  int dep[MAXN];
  int arc[MAXN];

  Dinic() {
    cnt = 0;
    memset(E, 0, sizeof E);
    memset(last, 0, sizeof last);
    memset(dep, 0, sizeof dep);
  }

  void add_edge(int u, int v, ll cap, ll rcap = 0) {
    E[++cnt].next = last[u];
    E[cnt].to = v;
    E[cnt].cap = cap;
    E[cnt].rev = cnt + 1;
    last[u] = cnt;

    // reverse edge
    E[++cnt].next = last[v];
    E[cnt].to = u;
    E[cnt].cap = rcap;
    E[cnt].rev = cnt - 1;
    last[v] = cnt;
  }

  bool bfs() {
    queue<int> q;

    memset(dep, 0, sizeof dep);
    dep[s] = 1;
    q.push(s);

    while (q.size()) {
      int x = q.front();
      q.pop();
      for (int i = last[x]; i; i = E[i].next) {
        if (E[i].cap && !dep[E[i].to]) {
          dep[E[i].to] = dep[x] + 1;
          q.push(E[i].to);
        }
      }
    }
    if (!dep[t]) return false;
    return true;
  }

  ll dfs(int cur, ll flow) {
    if (cur == t) return flow;
    for (int &i = arc[cur]; i; i = E[i].next) {
      if (dep[E[i].to] == dep[cur] + 1 && E[i].cap) {
        ll ret = dfs(E[i].to, min(flow, E[i].cap));
        if (ret) {
          E[i].cap -= ret;
          E[E[i].rev].cap += ret;
          return ret;
        }
      }
    }
    return 0;
  }

  ll operator()() {
    ll ans = 0;
    while (bfs()) {
      for (int i = 1; i <= n; i++) arc[i] = last[i];
      while (ll ret = dfs(s, INFLL)) ans += ret;
    }
    return ans;
  }

  void findAnswer(int n) {
    for (int i = 1; i <= n; i++) {
      for (int p = last[i]; p; p = E[p].next)
        if (!E[p].cap) cout << E[p].to - BOUND << ' ';
      cout << '\n';
    }
  }

} dinic;

// Pre-Build Function
inline void build() {}

// Actual Solver
inline void solve() {
  int n, m;
  cin >> n >> m;

  ll cap;

  dinic.s = 421, dinic.t = 422;
  dinic.n = 422;
  ll sum = 0;

  for (int i = 1; i <= n; i++) {
    cin >> cap;
    sum += cap;
    dinic.add_edge(dinic.s, i, cap);
  }

  for (int i = 1; i <= m; i++) {
    cin >> cap;
    dinic.add_edge(i + BOUND, dinic.t, cap);
  }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) dinic.add_edge(i, j + BOUND, 1LL);

  bool flag = sum == dinic();
  if (flag) {
    cout << "1\n";
    dinic.findAnswer(n);
  } else
    cout << "0\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

#ifdef LOCAL
  clock_t _begin = clock();
#endif

  build();
  solve();

#ifdef LOCAL
  cerr << "Time elapsed: " << (double)(clock() - _begin) * 1000 / CLOCKS_PER_SEC
       << "ms." << endl;
#endif

  return 0;
}