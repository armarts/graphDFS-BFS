#include "Graph.h"


template <typename value_type>
Graph<value_type>::Graph():
                m_graphSize(0),
                m_graphCapacity(0),
                m_graph(),
                m_map()
{
}

template <typename value_type>
Graph<value_type>::Graph(size_t size):
                            m_graphSize(0),
                            m_graphCapacity(size),
                            m_graph(size),
                            m_map()
{
}

template <typename value_type>
Graph<value_type>::~Graph()
{
    m_map.clear();
    
    for (auto elem = m_graph.begin(); elem != m_graph.end(); elem++)
        elem -> clear();
    m_graph.clear();
}

template <typename value_type>
void Graph<value_type>::dump()
{
    for (auto& i: m_map)
    {
        std::cout << i.first << std::endl;
    }
}

template <typename value_type>
bool Graph<value_type>::isValid(const value_type& node) const
{
    auto iter = m_map.find(node);

    if (iter != m_map.end())
        return true;

    return false;
}

template <typename value_type>
int Graph<value_type>::addNode(const value_type& node)
{
    if (isValid(node))
        return NODE_IS_EXISTED;

    if (m_graphSize == m_graphCapacity)
        return FULL_GRAPH;

    m_map.insert(pair<value_type, int>(node, m_graphSize));
    m_graphSize++;

    return OK;
}

template <typename value_type>
int Graph<value_type>::addEdge(const value_type& from, const value_type& to)
{
    if (!isValid(from) || !isValid(to))
        return NOT_FOUND_NODE;

    int idFrom = m_map.find(from) -> second;
    int idTo   = m_map.find(to)   -> second;
    m_graph[idFrom].insert(idTo);

    return OK;
}

template <typename value_type>
bool Graph<value_type>::isConected(const value_type& from, const value_type& to)
{
    if (!isValid(from) || !isValid(to))
        return false;
    
    int idFrom = m_map.find(from) -> second;
    int idTo   = m_map.find(to)   -> second;
    
    auto iter = m_graph[idFrom].find(idTo);

    if (iter == m_graph[idFrom].end())
        return false;

   
    return true;
}

template <typename value_type>
value_type Graph<value_type>::findNode(int id) const
{
    for (auto& iter:m_map)
        if (iter.second == id)
            return iter.first;
}

template <typename value_type>
int Graph<value_type>::dfs(const value_type& from, const value_type& to) const
{
    if (!isValid(from) || !isValid(to))
        return NOT_FOUND_NODE;

    int idFrom = m_map.find(from) -> second;
    int idTo   = m_map.find(to)   -> second;
    
    bool *used = (bool*) calloc(m_graphSize, sizeof(bool));
    int  *path = (int*)  calloc(m_graphSize, sizeof(int));
    
    if (path == NULL || used == NULL)
    {
        free(used);
        free(path);
        return ALLOCATE_ERROR;
    }

    for (int i = 0; i < m_graphSize; i++)
        path[i] = INF;

    stack<int> st;
    st.push(idFrom);
    used[idFrom] = true;
    path[idFrom] = 0;

    while (!st.empty())
    {
        int v = st.top();
        st.pop();

        for (auto iter = m_graph[v].begin(); iter != m_graph[v].end(); iter++)
            if (!used[*iter])
            {
                st.push(*iter);
                used[*iter] = true;
                path[*iter] = v;
            }
    }

    if (!used[idTo])
        cout << "PATH IS NOT EXIST\n";
    else
    {
        int v = idTo;

        cout << "PATH\n";
        while (v != idFrom)
        {
            cout << findNode(v) << " <- ";
            v = path[v];
        }
        cout << findNode(idFrom)<<"\n";
    }

    free(used);
    free(path);
    return OK;
}

template <typename value_type>
int Graph<value_type>::bfs(const value_type& from, const value_type& to) const
{
    if (!isValid(from) || !isValid(to))
        return NOT_FOUND_NODE;

    int idFrom = m_map.find(from) -> second;
    int idTo   = m_map.find(to)   -> second;

    bool *used = (bool*) calloc(m_graphSize, sizeof(bool));
    int  *dist = (int*) calloc(m_graphSize, sizeof(int));

    if (dist == NULL || used == NULL)
    {
        free(dist);
        free(used);
        return ALLOCATE_ERROR;
    }

    for (int i = 0; i < m_graphSize; i++)
        dist[i] = INF;

    queue <int> q;

    q.push(idFrom);
    dist[idFrom] = 0;
    used[idFrom] = true;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (auto iter = m_graph[v].begin(); iter != m_graph[v].end(); iter++)
            if (!used[*iter])
            {
                q.push(*iter);
                used[*iter] = true;
                dist[*iter] = dist[v] + 1;
            }
    }
    
    if (!used[idTo])
        cout << "PATH IS NOT EXIST\n";
    else
    {
        std::cout << "Dist from :" << findNode(idFrom) << " To:\n";
        for (int i = 0; i < m_graphSize; i++)
            if (dist[i] != INF)
                std::cout << findNode(i) <<" - " << dist[i] << "\n";
    }
    free(used);
    free(dist);

    return OK;
}


