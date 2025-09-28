#include "InventoryBST.hpp"
#include <iostream>

Produce::Produce(std::string n, int q, int qual): name(std::move(n)), quantity(q), quality(qual) {}
BSTNode::BSTNode(const Produce &prod): p(prod), left(nullptr), right(nullptr) {}

InventoryBST::InventoryBST(): root(nullptr) {}
InventoryBST::~InventoryBST() { free_all(root); }

BSTNode* InventoryBST::insert_node(BSTNode* node, const Produce &p) {
    if (!node) return new BSTNode(p);
    // sort by quality desc, then name ascending
    if (p.quality > node->p.quality || (p.quality == node->p.quality && p.name < node->p.name))
        node->left = insert_node(node->left, p);
    else
        node->right = insert_node(node->right, p);
    return node;
}

void InventoryBST::insert(const Produce &p) { root = insert_node(root, p); }

void InventoryBST::inorder(BSTNode* node, std::vector<Produce> &out) const {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->p);
    inorder(node->right, out);
}

std::vector<Produce> InventoryBST::sorted_list() const {
    std::vector<Produce> v;
    inorder(root, v);
    return v;
}

void InventoryBST::show() const {
    auto v = sorted_list();
    if (v.empty()) { std::cout << "Inventory empty.\n"; return; }
    std::cout << "Inventory (best quality first):\n";
    for (auto &it : v) std::cout << "- " << it.name << " | " << it.quantity << "kg | quality " << it.quality << "\n";
}

void InventoryBST::free_all(BSTNode* node) {
    if (!node) return;
    free_all(node->left);
    free_all(node->right);
    delete node;
}
