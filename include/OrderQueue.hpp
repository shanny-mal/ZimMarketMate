#ifndef ORDERQUEUE_HPP
#define ORDERQUEUE_HPP

#include <string>
#include <queue>
#include <vector>

struct Order {
    std::string buyerName;
    std::string produceName;
    int quantity; // kg requested
    int price;    // price per kg
    Order(std::string b="", std::string prod="", int q=0, int p=0);
};

class OrderQueue {
private:
    std::queue<Order> q;
public:
    void push(const Order &o);
    bool empty() const;
    Order pop();
    std::vector<Order> to_vector() const; // non-destructive
    void show() const;
};

#endif 
