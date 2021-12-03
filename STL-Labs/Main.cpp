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

   vector < vector < pii > > g(n + 1);                            // начальный граф (0 элемент не используется) (pii используется вида конецРебра - весРебра)

   for (int i = 1; i <= m; ++i)
   {
      int u, v, w;
      cin >> u >> v >> w;
      g[u].pb(mp(v, w));
      g[v].pb(mp(u, w));
   }

   priority_queue < pii, vector < pii >, greater < pii > > q;     // Очередь вес-вершина
   vector < int > key(n + 1, INT_MAX);                            // Храним вес минимального ребра, исходящего из выбранной вершины
   vector < int > p(n + 1, -1);                                   // Храним вершину, куда указывает минимальное ребро из выбранной вершины
   vector < bool > was(n + 1, false);                             // Для отметок, прошли ли мы вершину


   int start = 1;                                                 // Начальная вершина обхода
   int min_w = 0;                                                 // Вес минимального графа

   q.push(mp(0, start));

   while (!q.empty())
   {
      int len = q.top().F;                                        // Длина ребра
      int v = q.top().S;                                          // Вершина, куда ребро привело

      q.pop();

      if (was[v])                                                 // Если уже были в этой вершине, то пропускаем ребро
         continue;

      was[v] = true;                                              // Помечаем вершину как пройденную, считаем вес ребра, который вёл до неё
      min_w += len;

      for (auto& cur : g[v])                                      // Находим все рёбра этой вершины
      {
         int to = cur.F;                                          // Вершина, куда текущее ребро ведёт
         int w = cur.S;                                           // Вес текущего ребра
         if (!was[to] && key[to] > w)                             // Если мы ещё не были в вершине и вес минимального ребра этой вершины больше, чем вес текущего ребра, то
         {
            key[to] = w;                                          // Запоминаем для этой вершины вес минимального ребра   
            q.push(mp(w, to));                                    // Пушим вершину с весом до неё в очередь
            p[to] = v;                                            // Отмечаем, что из этой вершины можно попасть в вершину [v]
         }
      }
   }

   cout << min_w << endl;

   for (int i = 2; i <= n; ++i)
      cout << p[i] << " - " << i << endl;

   return 0;
}