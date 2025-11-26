#pragma once
#include "Order.h"
#include <array>
#include <vector>
#include <cstdint>
#include <unordered_map>

class OrderBook {
private:
    static constexpr uint32_t PRICE_LEVELS = 131072;  // 2^17 → covers $0 to $1.3M at 0.01 ticks
    static constexpr uint64_t NULL_IDX = 0;

    struct PriceLevel {
        uint64_t head_idx{NULL_IDX};  // first order at this price
        uint64_t tail_idx{NULL_IDX};  // last order
        uint64_t total_qty{0};
        uint32_t order_count{0};
    };

    // Bids (higher index = higher price), Asks (lower index = lower price)
    std::array<PriceLevel, PRICE_LEVELS> bids{};
    std::array<PriceLevel, PRICE_LEVELS> asks{};

    // Fast lookup: order_id → position in slab (we'll add slab later)
    // For Day 1, we use simple map (slow but correct)
    std::unordered_map<uint64_t, uint64_t> order_to_idx;

    // All orders live here (later: replace with slab)
    std::vector<Order> orders;

public:
    void add_order(uint64_t order_id, uint64_t client_id, Side side,
                   uint32_t price, uint32_t qty);

    void cancel_order(uint64_t order_id);

    void print_book() const;  // for debugging Day 1–3
};