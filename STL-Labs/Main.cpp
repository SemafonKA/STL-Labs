#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

#define per(name, beg, en) for (int name = beg; name <= en; ++name)
#define rep(name, beg, en) for (int name = beg; name >= en; --name)

#define pb push_back
#define mp make_pair
#define sz(x) (int)(x).size()

#define F first
#define S second
#define FF first.first
#define FS first.second
#define SF second.first
#define SS second.second

using namespace std;


using pii = pair<int, int>;

using GraphList = vector<vector<pii>>;      // Граф списком смежности
using GraphMatrix = vector<vector<int>>;     // Граф матрицей смежности

const int inf = INT_MAX;
const pii pinf = mp(inf, inf);

pii finder(vector < pii > vec, int v) {
   pii ans = pinf;
   for (auto x : vec)
      if (x.F == v)
      {
         ans = x;
         break;
      }
   return ans;
}

void floyd(GraphMatrix sD, int size)
{
   per(i, 1, size - 1)
      per(u, 1, size - 1)
         per(v, 1, size - 1)
         if (sD[u][i] < inf && sD[i][v] < inf)
            sD[u][v] = min(sD[u][v], sD[u][i] + sD[i][v]);

   per(u, 1, size - 1)
   {
      per(v, 1, size - 1)
         cout << ((sD[u][v] == inf || u == v) ? 0 : sD[u][v]) << ' ';
      cout << endl;
   }
}

void floydAlgMatrix(const GraphMatrix& graph)//, ostream& out, int numThreads = omp_get_max_threads())
{
   GraphMatrix sD = graph;
   int size = static_cast<int>(sz(graph));

   per(u, 1, size - 1)
      per(v, 1, size - 1)
      if (!sD[u][v])
         sD[u][v] = inf;

   floyd(sD, size);
}

void floydAlgList(const GraphList& graph)
{
   GraphMatrix sD;
   int size = static_cast<int>(sz(graph));
   sD.resize(size);
   per(i, 1, size - 1)
   {
      sD[i].pb(inf);
      per(j, 1, size - 1)
         sD[i].pb(finder(graph[i], j).S);
   }
   floyd(sD, size);
}

void solve()
{
   int n, m;
   cin >> n >> m;
   GraphMatrix g;       // граф матрицей смежности
   GraphList G;         // граф списком смежности
   G.resize(n + 1);
   g.resize(n + 1);
   per(i, 1, n)
      g[i].resize(n + 1, 0);
   per(i, 1, m)
   {
      int u, v, w;
      cin >> u >> v >> w;
      g[u][v] = g[v][u] = w;
      G[u].pb(mp(v, w));
      G[v].pb(mp(u, w));
   }
   floydAlgMatrix(g);
   cout << endl;
   floydAlgList(G);
}

int main()
{
   solve();
}