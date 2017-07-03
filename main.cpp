#include "Graph.cpp"
#include <string>

using std::string;

int main()
{
    int n;
    std::cin >> n;
    string City[10]=
    {
        "Moscow",
        "London",
        "Washington",
        "NY",
        "Paris",
        "Stavropol",
        "Saint-Petersburg",
        "Madrid",
        "Berlin",
        "Warsaw"
    };

    Graph<string> g(n);

    for (int i = 0; i < 10; i++)
        g.addNode(City[i]);

    g.addEdge(City[0], City[2]);

    g.addEdge(City[2], City[4]);
 
    g.addEdge(City[8], City[9]);
 
    g.addEdge(City[2], City[8]);
 
    g.addEdge(City[8], City[2]);
 
    g.addEdge(City[4], City[2]);

    g.addEdge(City[2], City[0]);

    g.dfs(City[0], City[8]);

    g.bfs(City[0], City[8]);
 
    return 0;
}
