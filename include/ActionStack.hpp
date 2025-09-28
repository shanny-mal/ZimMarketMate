#ifndef ACTIONSTACK_HPP
#define ACTIONSTACK_HPP

#include <string>
#include <vector>

class ActionStack {
private:
    std::vector<std::string> st;
public:
    void push(const std::string &s);
    bool empty() const;
    std::string pop();
    void show() const;
};

#endif 
