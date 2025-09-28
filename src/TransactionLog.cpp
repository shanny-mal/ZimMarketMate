#include "TransactionLog.hpp"
#include <iostream>

TxNode::TxNode(const std::string &r): record(r), next(nullptr) {}
TransactionLog::TransactionLog(): head(nullptr) {}
TransactionLog::~TransactionLog() {
    while (head) { TxNode* t = head; head = head->next; delete t; }
}
void TransactionLog::add(const std::string &record) {
    TxNode* n = new TxNode(record);
    n->next = head; head = n;
}
void TransactionLog::show() const {
    if (!head) { std::cout << "No transactions yet.\n"; return; }
    std::cout << "Transaction log (most recent first):\n";
    TxNode* cur = head; int i=1;
    while (cur) {
        std::cout << i++ << ". " << cur->record << "\n";
        cur = cur->next;
    }
}
