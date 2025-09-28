#include "Graph.hpp"
#include <iostream>

Graph::Graph(int nodes): n(nodes), adj(nodes), names(nodes) {}

void Graph::setName(int v, const std::string &name) {
    if (v>=0 && v<n) names[v] = name;
}
std::string Graph::name(int v) const {
    if (v>=0 && v<n) return names[v];
    return "";
}
void Graph::addEdge(int u, int v) {
    if (u<0 || v<0 || u>=n || v>=n) return;
    adj[u].push_back(v);
    adj[v].push_back(u);
}
std::vector<int> Graph::neighbors(int v) const {
    if (v>=0 && v<n) return adj[v];
    return {};
}
int Graph::size() const { return n; }

void Graph::list_rooms() const {
    for (int i=0;i<n;++i) std::cout << i << ": " << names[i] << "\n";
}
void Graph::show_room(int v) const {
    if (v<0||v>=n) { std::cout<<"Unknown room\n"; return; }
    std::cout << "Market: " << names[v] << "\nNearby markets:\n";
    for (int to: adj[v]) std::cout << "- ["<<to<<"] " << names[to] << "\n";
}
