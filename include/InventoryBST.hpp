#ifndef INVENTORY_BST_HPP
#define INVENTORY_BST_HPP

#include <string>
#include <vector>

struct Produce {
    std::string name;
    int quantity;   // kilograms
    int quality;    // 1..10 (higher better)
    Produce(std::string n = "", int q = 0, int qual = 5);
};

struct BSTNode {
    Produce p;
    BSTNode *left, *right;
    explicit BSTNode(const Produce &prod);
};

class InventoryBST {
private:
    BSTNode* root;
    BSTNode* insert_node(BSTNode* node, const Produce &p);
    void inorder(BSTNode* node, std::vector<Produce> &out) const;
    void free_all(BSTNode* node);
public:
    InventoryBST();
    ~InventoryBST();
    void insert(const Produce &p);
    std::vector<Produce> sorted_list() const; // in-order
    void show() const;
};

#endif 
