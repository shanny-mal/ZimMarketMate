#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

class Graph {
private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<std::string> names;
public:
    explicit Graph(int nodes = 0);
    void setName(int v, const std::string &name);
    std::string name(int v) const;
    void addEdge(int u, int v);
    std::vector<int> neighbors(int v) const;
    int size() const;
    void list_rooms() const;
    void show_room(int v) const;
};

#endif 
