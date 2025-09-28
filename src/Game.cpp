#include "Game.hpp"
#include "Leaderboard.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

Game::Game(): map(6), currentMarket(0) {
    map.setName(0,"Harare Central Market");
    map.setName(1,"Mbare Market");
    map.setName(2,"Chitungwiza Market");
    map.setName(3,"Mutare Market");
    map.setName(4,"Gweru Market");
    map.setName(5,"Bulawayo Market");
    map.addEdge(0,1); map.addEdge(0,2); map.addEdge(1,3); map.addEdge(2,4); map.addEdge(3,5);

    // sample inventory
    inventory.insert(Produce("Maize", 100, 7));
    inventory.insert(Produce("Groundnuts", 50, 8));
    inventory.insert(Produce("Tomatoes", 30, 6));

    // sample leaderboard
    leaderboard.push_back({"BuyerA", 200});
    leaderboard.push_back({"BuyerB", 150});
}

void Game::help() const {
    std::cout << "Commands:\n";
    std::cout << " map                      - list markets\n";
    std::cout << " look                     - show current market and neighbors\n";
    std::cout << " go <id>                  - move to market id\n";
    std::cout << " add <name> <kg> <qual>   - add produce to inventory\n";
    std::cout << " inventory                - show inventory (BST)\n";
    std::cout << " placeorder <buyer> <prod> <kg> <price>  - place buyer order\n";
    std::cout << " orders                   - show pending orders (queue)\n";
    std::cout << " fulfill                  - fulfill next order if possible\n";
    std::cout << " txlog                    - show transaction log (linked list)\n";
    std::cout << " undo                     - undo last user action (stack) (demo only)\n";
    std::cout << " leaderboard              - show top buyers (quicksort)\n";
    std::cout << " help                     - show this help\n";
    std::cout << " exit                     - quit\n";
}

void Game::run() {
    std::cout << "Welcome to ZimMarketMate (console)\nType 'help' for commands\n";
    std::string line;
    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string cmd; ss >> cmd;
        if (cmd == "map") cmd_map();
        else if (cmd == "look") cmd_look();
        else if (cmd == "go") { int id; if (ss >> id) cmd_go(id); else std::cout<<"Usage: go <id>\n"; }
        else if (cmd == "add") { std::string n; int kg, qual; if (ss>>n>>kg>>qual) cmd_addproduce(n,kg,qual); else std::cout<<"Usage: add <name> <kg> <quality>\n"; }
        else if (cmd == "inventory") cmd_inventory();
        else if (cmd == "placeorder") { std::string buyer, prod; int kg, price; if (ss>>buyer>>prod>>kg>>price) cmd_placeorder(buyer,prod,kg,price); else std::cout<<"Usage: placeorder <buyer> <prod> <kg> <price>\n"; }
        else if (cmd == "orders") cmd_orders();
        else if (cmd == "fulfill") cmd_fulfill();
        else if (cmd == "txlog") cmd_txlog();
        else if (cmd == "undo") cmd_undo();
        else if (cmd == "leaderboard") cmd_leaderboard();
        else if (cmd == "help") help();
        else if (cmd == "exit") break;
        else std::cout << "Unknown command. Type 'help'\n";
    }
}

void Game::cmd_map() const { map.list_rooms(); }
void Game::cmd_look() const { map.show_room(currentMarket); }
void Game::cmd_go(int id) {
    auto neigh = map.neighbors(currentMarket);
    bool ok = false;
    for (int v : neigh) if (v==id) ok=true;
    if (!ok) { std::cout<<"You can't go directly there.\n"; return; }
    actions.push("go from " + map.name(currentMarket) + " to " + map.name(id));
    currentMarket = id;
    std::cout << "Moved to " << map.name(currentMarket) << "\n";
}
void Game::cmd_addproduce(const std::string &name, int quantity, int quality) {
    inventory.insert(Produce(name, quantity, quality));
    actions.push("add " + name + " " + std::to_string(quantity));
    std::cout << "Added produce: " << name << " " << quantity << "kg quality " << quality << "\n";
}
void Game::cmd_inventory() const { inventory.show(); }

void Game::cmd_placeorder(const std::string &buyer, const std::string &prod, int qty, int price) {
    orders.push(Order(buyer, prod, qty, price));
    actions.push("placeorder " + buyer + " " + prod);
    std::cout << "Order placed by " << buyer << " for " << qty << "kg of " << prod << " @ " << price << "/kg\n";
}

void Game::cmd_orders() const { orders.show(); }

void Game::cmd_fulfill() {
    if (orders.empty()) { std::cout << "No orders to fulfill.\n"; return; }
    Order o = orders.pop();
    // naive fulfillment: check inventory for produce matching name and enough quantity (reduce first matching)
    auto invlist = inventory.sorted_list();
    bool filled = false;
    // naive linear search through BST in-order list (demonstrate array traversal and optional binary search)
    for (auto &pr : invlist) {
        if (pr.name == o.produceName && pr.quantity >= o.quantity) {
            // reduce quantity
            // Note: our BST doesn't support modify; for simplicity, we record sale and keep inventory unchanged (documented).
            filled = true;
            std::string rec = "Sold " + std::to_string(o.quantity) + "kg " + o.produceName + " to " + o.buyerName + " @ " + std::to_string(o.price) + "/kg";
            txlog.add(rec);
            actions.push("fulfill " + o.buyerName + " " + o.produceName);
            // update leaderboard (sum paid)
            int paid = o.quantity * o.price;
            bool found=false;
            for (auto &b : leaderboard) if (b.first == o.buyerName) { b.second += paid; found=true; break; }
            if (!found) leaderboard.push_back({o.buyerName, paid});
            std::cout << "Order fulfilled: " << rec << "\n";
            break;
        }
    }
    if (!filled) {
        std::cout << "Could not fulfill order: insufficient matching produce in inventory. Order discarded.\n";
        txlog.add("Failed to fulfill order for " + o.buyerName + " (" + o.produceName + ")");
    }
}

void Game::cmd_txlog() const { txlog.show(); }

void Game::cmd_undo() {
    if (actions.empty()) { std::cout << "Nothing to undo.\n"; return; }
    std::string a = actions.pop();
    std::cout << "Undoing: " << a << " (note: for demo we log undo but do not reverse complex state changes)\n";
}

void Game::cmd_leaderboard() const {
    auto arr = leaderboard;
    if (!arr.empty()) {
        quicksort_leader(arr, 0, (int)arr.size()-1);
        std::cout << "Top buyers (by amount spent):\n";
        for (size_t i=0;i<arr.size();++i) std::cout << i+1 << ". " << arr[i].first << " - " << arr[i].second << "\n";
    } else std::cout << "Leaderboard empty.\n";
}
