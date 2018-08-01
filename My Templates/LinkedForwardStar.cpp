#include <bits/stdc++.h>

using namespace std;

const int SIZE = 1e5 + 10; // Number of edges

struct Edge
{
    int next, to, w;

    Edge() : next(0), to(0), w(0) {}
};

Edge E[SIZE];
int last[SIZE];
int cnt = 0;

void add_edge(int u, int v, int w = 1)
{
    E[++cnt].next = last[u];
    E[cnt].to = v;
    E[cnt].w = w;
    last[u] = cnt;
}