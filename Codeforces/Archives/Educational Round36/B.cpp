#include <bits/stdc++.h>

#define FOR(_i, _s, _e) for (int _i = _s; _i < _e; _i++)
#define FORE(_c) for (auto i : _c)
#define FORER(_c) for (auto& i : _c)
#define VIS(_kind, _name, _size) \
  vector<_kind> _name(_size);    \
  for (auto& i : v) cin >> i;

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef set<int> si;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, pos, l, r, res = 0;
  cin >> n >> pos >> l >> r;
  if (r < n) res++;
  if (l > 1) res++;
  return 0;
}