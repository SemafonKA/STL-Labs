#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define sz(x) (int)x.size()

using pii = std::pair<int, int>;

using namespace std;

int main()
{
   ifstream in("input.txt");

   int n, m;
   in >> n >> m;

   vector < vector < pii > > g(n + 1);                            // ��������� ���� (0 ������� �� ������������) (pii ������������ ���� ���������� - ��������)

   for (int i = 1; i <= m; ++i)
   {
      int u, v, w;
      in >> u >> v >> w;
      g[u].pb(mp(v, w));
      g[v].pb(mp(u, w));
   }
   in.close();

   priority_queue < pii, vector < pii >, greater < pii > > q;     // ������� ���-�������
   vector < int > key(n + 1, INT_MAX);                            // ������ ��� ������������ �����, ���������� �� ��������� �������
   vector < int > p(n + 1, -1);                                   // ������ �������, ���� ��������� ����������� ����� �� ��������� �������
   vector < bool > was(n + 1, false);                             // ��� �������, ������ �� �� �������


   int start = 1;                                                 // ��������� ������� ������
   int min_w = 0;                                                 // ��� ������������ �����

   q.push(mp(0, start));

   while (!q.empty())
   {
      int len = q.top().F;                                        // ����� �����
      int v = q.top().S;                                          // �������, ���� ����� �������

      q.pop();

      if (was[v])                                                 // ���� ��� ���� � ���� �������, �� ���������� �����
         continue;

      was[v] = true;                                              // �������� ������� ��� ����������, ������� ��� �����, ������� �� �� ��
      min_w += len;

      for (auto& cur : g[v])                                      // ������� ��� ���� ���� �������
      {
         int to = cur.F;                                          // �������, ���� ������� ����� ����
         int w = cur.S;                                           // ��� �������� �����
         if (!was[to] && key[to] > w)                             // ���� �� ��� �� ���� � ������� � ��� ������������ ����� ���� ������� ������, ��� ��� �������� �����, ��
         {
            key[to] = w;                                          // ���������� ��� ���� ������� ��� ������������ �����   
            q.push(mp(w, to));                                    // ����� ������� � ����� �� �� � �������
            p[to] = v;                                            // ��������, ��� �� ���� ������� ����� ������� � ������� [v]
         }
      }
   }

   ofstream out("output.txt");

   out << min_w << endl;

   for (int i = 2; i <= n; ++i)
      out << p[i] << " - " << i << endl;

   out.close();

   return 0;
}