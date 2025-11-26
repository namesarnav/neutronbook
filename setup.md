NeutronBook/
├── CMakeLists.txt                  # Top-level CMake (C++23, -O3, march=native)
├── README.md                       # Legendary README with latency gif + histogram
├── LICENSE                         # MIT or Apache 2.0
├── .github/
│   └── workflows/
│       └── ci.yml                  # GitHub Actions: build + tests + benchmarks
│
├── benchmark/                      # Google Benchmark + nanobench
│   ├── matching_engine_bench.cpp
│   └── CMakeLists.txt
│
├── docs/
│   ├── architecture.md             # All diagrams (Mermaid) + sequence flows
│   ├── latency.md                  # How we measure <80 ns
│   └── replay.md                   # How to replay real Nasdaq ITCH data
│
├── include/
│   └── neutronbook/
│       ├── core/                   # Public hot path (inlined)
│       │   ├── Order.h
│       │   ├── PriceLevel.h
│       │   ├── OrderBook.h
│       │   ├── Sequencer.h
│       │   └── Worker.h
│       │
│       ├── memory/                 # Slab, pools, huge pages
│       │   ├── OrderSlab.h
│       │   └── Allocator.h
│       │
│       ├── messaging/              # Commands, ExecutionReport, SBE-like
│       │   ├── Command.h
│       │   └── ExecutionReport.h
│       │
│       ├── queue/                  # Lock-free queues
│       │   ├── SPSCQueue.h
│       │   └── MPMCQueue.h
│       │
│       └── utils/
│           ├── Align.h
│           ├── Constants.h
│           └── Timer.h             # Cycle-accurate timing
│
├── src/
│   ├── core/
│   │   ├── OrderBook.cpp
│   │   ├── Sequencer.cpp
│   │   └── Worker.cpp
│   │
│   ├── memory/
│   │   └── OrderSlab.cpp
│   │
│   ├── gateway/
│   │   ├── Gateway.cpp
│   │   └── Gateway.h
│   │
│   ├── publisher/
│   │   ├── Publisher.cpp
│   │   └── Publisher.h
│   │
│   └── main.cpp                    # Demo + backtester entry point
│
├── tests/
│   ├── unit/
│   │   ├── test_orderbook_correctness.cpp
│   │   ├── test_lockfree_queue.cpp
│   │   └── test_slab.cpp
│   │
│   ├── property/                   # Property-based testing (catch2)
│   │   └── prop_matching_engine.cpp
│   │
│   └── replay/                     # Real Nasdaq ITCH replay tests
│       ├── nasdaq_itch_replay.cpp
│       └── data/                   # Sample ITCH files (public)
│
├── tools/
│   ├── generate_itch.cpp           # Generate synthetic ITCH-like load
│   ├── latency_histogram.py        # Plot Perfetto traces
│   └── pin_threads.sh              # Core pinning script
│
└── third_party/
    ├── google_benchmark/
    ├── spdlog/                     # Fast logging (optional)
    ├── flat_hash_map/              # Abseil or ska::flat_hash_map
    └── catch2/                     # Testing framework