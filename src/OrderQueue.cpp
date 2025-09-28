#include "OrderQueue.hpp"
#include <iostream>
#include <queue>

Order::Order(std::string b, std::string prod, int qnt, int p): buyerName(std::move(b)), produceName(std::move(prod)), quantity(qnt), price(p) {}
void OrderQueue::push(const Order &o) { q.push(o); }
bool OrderQueue::empty() const { return q.empty(); }
Order OrderQueue::pop() { Order o = q.front(); q.pop(); return o; }
std::vector<Order> OrderQueue::to_vector() const {
    std::vector<Order> out;
    std::queue<Order> tmp = q;
    while(!tmp.empty()){ out.push_back(tmp.front()); tmp.pop(); }
    return out;
}
void OrderQueue::show() const {
    auto v = to_vector();
    if (v.empty()) { std::cout << "No buyer orders pending.\n"; return; }
    std::cout << "Pending orders (FIFO):\n";
    for (size_t i=0;i<v.size();++i) {
        std::cout << i+1 << ". " << v[i].buyerName << " wants " << v[i].quantity << "kg of " << v[i].produceName << " @ " << v[i].price << "/kg\n";
    }
}
