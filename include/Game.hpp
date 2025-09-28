#ifndef GAME_HPP
#define GAME_HPP

#include "Graph.hpp"
#include "InventoryBST.hpp"
#include "OrderQueue.hpp"
#include "TransactionLog.hpp"
#include "ActionStack.hpp"
#include <vector>
#include <utility>
#include <string>

class Game {
private:
    Graph map;
    int currentMarket;
    InventoryBST inventory;
    OrderQueue orders;
    TransactionLog txlog;
    ActionStack actions;
    std::vector<std::pair<std::string,int>> leaderboard; // buyer name, total paid
public:
    Game();
    void help() const;
    void run(); // main loop
    // helper functions accessible from commands:
    void cmd_map() const;
    void cmd_look() const;
    void cmd_go(int id);
    void cmd_addproduce(const std::string &name, int quantity, int quality);
    void cmd_inventory() const;
    void cmd_placeorder(const std::string &buyer, const std::string &prod, int qty, int price);
    void cmd_orders() const;
    void cmd_fulfill(); // try to fulfill next order
    void cmd_txlog() const;
    void cmd_undo();
    void cmd_leaderboard() const;
};

#endif 
