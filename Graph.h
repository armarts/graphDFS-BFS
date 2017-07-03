#ifndef __GRAPH__H__
#define __GRAPH__H__

#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <iostream>
#include <cstdio>

using std::vector;
using std::map;
using std::set;
using std::stack;
using std::queue;
using std::pair;
using std::cout;

#define INF 9999999

enum ERROR
{
    OK,
    NOT_FOUND_NODE,
    FULL_GRAPH,
    EDGE_IS_EXISTED,
    NODE_IS_EXISTED,
    ALLOCATE_ERROR
};

template <typename T>
class Graph
{
public:

    typedef T value_type;
    
    Graph();
    Graph(size_t size);
    ~Graph();

    void dump();

    bool isValid(const value_type& node) const;

    int addNode(const value_type& node);
    int addEdge(const value_type& from, const value_type& to); 
    bool isConected(const value_type& from, const value_type& to);

    value_type findNode(int id) const;

    // depth first search
    int dfs(const value_type& form, const value_type& to) const;
    
    // breadth first search
    int bfs(const value_type& from, const value_type& to) const;

private:
    
    map <value_type, int> m_map;

    int m_graphCapacity;
    int m_graphSize;
    vector< set<int> > m_graph; // Graph List

};


#endif
