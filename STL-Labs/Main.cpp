#include <iostream>
#include <vector>
#include <queue>

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define sz(x) (int)x.size()

using pii = std::pair<int, int>;

using namespace std;

int main()
{
   int n, m;

   cin >> n >> m;

   vector < vector < pii > > g(n + 1);

   for (int i = 1; i <= m; ++i)
   {
      int u, v, w;
      cin >> u >> v >> w;
      g[u].pb(mp(v, w));
      g[v].pb(mp(u, w));
   }

   priority_queue <pii, vector < pii >, greater < pii> > q;

   vector < int > key(n + 1, INT_MAX);
   vector < int > p(n + 1, -1);
   vector < bool > was(n + 1, false);


   int start = 1;

   q.push(mp(0, start));

   int min_w = 0;

   while (!q.empty())
   {
      int len = q.top().F;
      int v = q.top().S;

      q.pop();

      if (was[v])
         continue;

      was[v] = true;
      min_w += len;

      for (auto cur : g[v])
      {
         int to = cur.F, w = cur.S;
         if (!was[to] && key[to] > w)
         {
            key[to] = w;
            q.push(mp(key[to], to));
            p[to] = v;
         }
      }
   }

   cout << min_w << endl;

   for (int i = 2; i <= n; ++i)
      cout << p[i] << " - " << i << endl;

   return 0;
}