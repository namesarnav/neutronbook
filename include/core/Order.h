#pragma once
#include <cstdint>

enum class Side : uint8_t { Bid, Ask };

struct Order {
    uint64_t order_id;
    uint64_t client_id;
    uint32_t symbol_id;
    uint32_t price;          // e.g. 500050 = $5000.50
    uint32_t quantity;
    uint32_t remaining_qty;
    Side     side;
    uint64_t prev_idx{0};     // index linking (0 = null)
    uint64_t next_idx{0};     // index linking (0 = null)

    // Default constructor for slab
    Order() = default;
};