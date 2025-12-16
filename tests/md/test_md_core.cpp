#include "../../b3-md-connector/src/TopNBookSnapshot.hpp"
#include "../../b3-md-connector/src/SnapshotQueueSpsc.hpp"
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>

using b3::md::TopNBookSnapshot10;
using b3::md::SnapshotQueueSpsc;

// ============================================================================
// TopNBookSnapshot Tests
// ============================================================================

TEST(TopNBookSnapshotTests, IsTriviallyCopyable) {
    EXPECT_TRUE(std::is_trivially_copyable_v<TopNBookSnapshot10>);
}

TEST(TopNBookSnapshotTests, IsTriviallyDestructible) {
    EXPECT_TRUE(std::is_trivially_destructible_v<TopNBookSnapshot10>);
}

TEST(TopNBookSnapshotTests, DefaultConstruction) {
    TopNBookSnapshot10 s{};

    EXPECT_EQ(s.instrumentId, 0);
    EXPECT_EQ(s.exchangeTsNs, 0);
    EXPECT_EQ(s.bidCount, 0);
    EXPECT_EQ(s.askCount, 0);

    // Verify all levels are zeroed
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(s.bids[i].price, 0);
        EXPECT_EQ(s.bids[i].qty, 0);
        EXPECT_EQ(s.asks[i].price, 0);
        EXPECT_EQ(s.asks[i].qty, 0);
    }
}

TEST(TopNBookSnapshotTests, DataAssignment) {
    TopNBookSnapshot10 snapshot;

    snapshot.instrumentId = 12345;
    snapshot.exchangeTsNs = 1234567890123456789ULL;
    snapshot.bidCount = 3;
    snapshot.askCount = 2;

    // Set bid levels
    snapshot.bids[0] = {100000, 1000};
    snapshot.bids[1] = {99500, 1500};
    snapshot.bids[2] = {99000, 2000};

    // Set ask levels
    snapshot.asks[0] = {100500, 800};
    snapshot.asks[1] = {101000, 1200};

    EXPECT_EQ(snapshot.instrumentId, 12345);
    EXPECT_EQ(snapshot.exchangeTsNs, 1234567890123456789ULL);
    EXPECT_EQ(snapshot.bidCount, 3);
    EXPECT_EQ(snapshot.askCount, 2);

    EXPECT_EQ(snapshot.bids[0].price, 100000);
    EXPECT_EQ(snapshot.bids[0].qty, 1000);
    EXPECT_EQ(snapshot.bids[1].price, 99500);
    EXPECT_EQ(snapshot.bids[1].qty, 1500);
    EXPECT_EQ(snapshot.bids[2].price, 99000);
    EXPECT_EQ(snapshot.bids[2].qty, 2000);

    EXPECT_EQ(snapshot.asks[0].price, 100500);
    EXPECT_EQ(snapshot.asks[0].qty, 800);
    EXPECT_EQ(snapshot.asks[1].price, 101000);
    EXPECT_EQ(snapshot.asks[1].qty, 1200);
}

// ============================================================================
// SnapshotQueueSpsc Tests - Single Thread
// ============================================================================

TEST(SnapshotQueueSpscTests, EmptyQueueBehavior) {
    SnapshotQueueSpsc<TopNBookSnapshot10, 1024> q;
    TopNBookSnapshot10 out{};

    EXPECT_EQ(q.size_approx(), 0);
    EXPECT_FALSE(q.try_pop(out));
}

TEST(SnapshotQueueSpscTests, FifoSingleThread) {
    SnapshotQueueSpsc<TopNBookSnapshot10, 1024> q;
    TopNBookSnapshot10 a{}, b{}, out{};
    a.instrumentId = 10;
    b.instrumentId = 11;

    EXPECT_TRUE(q.try_push(a));
    EXPECT_TRUE(q.try_push(b));
    EXPECT_GE(q.size_approx(), 2);

    EXPECT_TRUE(q.try_pop(out));
    EXPECT_EQ(out.instrumentId, 10);

    EXPECT_TRUE(q.try_pop(out));
    EXPECT_EQ(out.instrumentId, 11);

    EXPECT_FALSE(q.try_pop(out));
    EXPECT_EQ(q.size_approx(), 0);
}

TEST(SnapshotQueueSpscTests, PushMultipleElements) {
    SnapshotQueueSpsc<int, 16> queue;

    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(queue.try_push(i));
    }

    EXPECT_EQ(queue.size_approx(), 10);

    for (int i = 0; i < 10; ++i) {
        int value;
        EXPECT_TRUE(queue.try_pop(value));
        EXPECT_EQ(value, i);
    }

    EXPECT_EQ(queue.size_approx(), 0);
}

TEST(SnapshotQueueSpscTests, QueueFullBehavior) {
    SnapshotQueueSpsc<int, 4> queue;

    // Fill the queue to capacity
    EXPECT_TRUE(queue.try_push(1));
    EXPECT_TRUE(queue.try_push(2));
    EXPECT_TRUE(queue.try_push(3));
    EXPECT_TRUE(queue.try_push(4));

    EXPECT_EQ(queue.size_approx(), 4);

    // Next push should fail (queue is full)
    EXPECT_FALSE(queue.try_push(5));

    // Pop one element
    int value;
    EXPECT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, 1);

    // Now we should be able to push again
    EXPECT_TRUE(queue.try_push(5));
}

TEST(SnapshotQueueSpscTests, WrapAroundBehavior) {
    SnapshotQueueSpsc<int, 4> queue;

    // Fill and empty multiple times to test wrap-around
    for (int cycle = 0; cycle < 3; ++cycle) {
        // Fill
        for (int i = 0; i < 4; ++i) {
            EXPECT_TRUE(queue.try_push(cycle * 10 + i));
        }

        // Empty
        for (int i = 0; i < 4; ++i) {
            int value;
            EXPECT_TRUE(queue.try_pop(value));
            EXPECT_EQ(value, cycle * 10 + i);
        }

        EXPECT_EQ(queue.size_approx(), 0);
    }
}

// ============================================================================
// SnapshotQueueSpsc Tests - Multi-threaded SPSC
// ============================================================================

TEST(SnapshotQueueSpscTests, SpscThreadedNoCorruption) {
    constexpr int N = 200000;
    SnapshotQueueSpsc<TopNBookSnapshot10, 4096> q;

    std::atomic<bool> done{false};
    std::atomic<int> produced{0};
    std::atomic<int> consumed{0};

    // Producer thread
    std::thread prod([&]{
        for (int i = 0; i < N; ) {
            TopNBookSnapshot10 s{};
            s.instrumentId = 77;
            s.exchangeTsNs = static_cast<uint64_t>(i);
            if (q.try_push(s)) {
                ++i;
                ++produced;
            }
        }
        done.store(true, std::memory_order_release);
    });

    // Consumer thread
    std::thread cons([&]{
        uint64_t last = 0;
        bool hasLast = false;

        TopNBookSnapshot10 s{};
        while (!done.load(std::memory_order_acquire) || q.size_approx() > 0) {
            if (q.try_pop(s)) {
                if (hasLast) {
                    // FIFO: in a single producer, exchangeTsNs must be increasing
                    EXPECT_EQ(s.exchangeTsNs, last + 1);
                } else {
                    hasLast = true;
                }
                last = s.exchangeTsNs;
                ++consumed;
            }
        }
        EXPECT_EQ(consumed.load(), produced.load());
    });

    prod.join();
    cons.join();
}

TEST(SnapshotQueueSpscTests, SpscThreadedStress) {
    constexpr int N = 100000;
    SnapshotQueueSpsc<int, 256> q;

    std::atomic<bool> producerDone{false};
    std::vector<int> consumedValues;
    consumedValues.reserve(N);

    // Producer thread
    std::thread producer([&]() {
        for (int i = 0; i < N; ++i) {
            while (!q.try_push(i)) {
                std::this_thread::yield();
            }
        }
        producerDone.store(true, std::memory_order_release);
    });

    // Consumer thread
    std::thread consumer([&]() {
        int value;
        while (!producerDone.load(std::memory_order_acquire) || q.size_approx() > 0) {
            if (q.try_pop(value)) {
                consumedValues.push_back(value);
            } else {
                std::this_thread::yield();
            }
        }
    });

    producer.join();
    consumer.join();

    // Verify all values were consumed in order
    EXPECT_EQ(consumedValues.size(), N);
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(consumedValues[i], i);
    }

    EXPECT_EQ(q.size_approx(), 0);
}
