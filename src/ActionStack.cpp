#include "ActionStack.hpp"
#include <iostream>

void ActionStack::push(const std::string &s) { st.push_back(s); }
bool ActionStack::empty() const { return st.empty(); }
std::string ActionStack::pop() {
    if (st.empty()) return {};
    std::string s = st.back(); st.pop_back(); return s;
}
void ActionStack::show() const {
    if (st.empty()) { std::cout << "No actions.\n"; return; }
    std::cout << "Recent actions (undo stack):\n";
    for (int i = (int)st.size()-1; i>=0; --i) std::cout << "- " << st[i] << "\n";
}
