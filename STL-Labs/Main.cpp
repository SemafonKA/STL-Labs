#include <iostream>
#include <vector>

using namespace std;

class WeighedEdge
{
public:
   size_t firstNode;
   size_t secondNode;
   size_t weight;

   WeighedEdge(size_t _firstNode, size_t _secondNode, size_t _weight)
   {
      firstNode = _firstNode;
      secondNode = _secondNode;
      weight = _weight;
   }

   bool operator == (const WeighedEdge& _right) const
   {
      return (firstNode == _right.firstNode && 
         secondNode == _right.secondNode && 
         weight == _right.weight);
   }

   bool operator < (const WeighedEdge& _right) const
   {
      return weight < _right.weight;
   }
   bool operator > (const WeighedEdge& _right) const
   {
      return weight > _right.weight;
   }

   bool contains(size_t _node)
   {
      return (firstNode == _node || secondNode == _node);
   }
};

class WeighedGraph
{
public:
   vector<WeighedEdge> edges;

   void addEdge(const WeighedEdge _edge)
   {
      edges.push_back(_edge);
   }

   bool removeEdge(const WeighedEdge _edge)
   {
      std::swap(edges[edges.size() - 1], *find(edges.begin(), edges.end(), _edge));
      edges.pop_back();
   }
};