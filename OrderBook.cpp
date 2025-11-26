#include "OrderBook.h"
#include <iostream>
#include <iomanip>

void OrderBook::add_order(uint64_t order_id, uint64_t client_id, Side side,
                          uint32_t price, uint32_t qty)
{
    Order order{};
    order.order_id = order_id;
    order.client_id = client_id;
    order.side = side;
    order.price = price;
    order.quantity = qty;
    order.remaining_qty = qty;

    uint64_t idx = orders.size();
    orders.push_back(order);
    order_to_idx[order_id] = idx;

    auto& levels = (side == Side::Bid) ? bids : asks;
    uint32_t level_idx = price;  // simple mapping for now

    PriceLevel& level = levels[level_idx];
    // Simple append (Day 1 — not lock-free yet)
    if (level.tail_idx != NULL_IDX) {
        orders[level.tail_idx].next_idx = idx;
        order.prev_idx = level.tail_idx;
    } else {
        level.head_idx = idx;
    }
    level.tail_idx = idx;
    level.total_qty += qty;
    level.order_count++;

    std::cout << "Added: " << (side == Side::Bid ? "BID" : "ASK")
              << " " << qty << " @ " << (price / 100) << "." << std::setfill('0') << std::setw(2) << (price % 100) << "\n";
}

void OrderBook::print_book() const {
    std::cout << "\n--- Order Book ---\n";
    std::cout << "BIDS                  ASKS\n";
    // Simplified print — we'll make it pretty later
    for (int i = PRICE_LEVELS-1; i >= 0; --i) {
        if (bids[i].total_qty > 0 || asks[i].total_qty > 0) {
            std::cout << std::setw(8) << bids[i].total_qty << " @ " 
                      << (i/100) << "." << std::setw(2) << std::setfill('0') << (i%100)
                      << " | "
                      << std::setw(8) << asks[i].total_qty << "\n";
        }
    }
}