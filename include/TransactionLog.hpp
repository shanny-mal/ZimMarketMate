#ifndef TRANSACTIONLOG_HPP
#define TRANSACTIONLOG_HPP

#include <string>

struct TxNode {
    std::string record;
    TxNode* next;
    explicit TxNode(const std::string &r);
};

class TransactionLog {
private:
    TxNode* head;
public:
    TransactionLog();
    ~TransactionLog();
    void add(const std::string &record); // add to head (most recent)
    void show() const;
};

#endif 
