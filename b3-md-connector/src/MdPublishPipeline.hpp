#pragma once
#include "MdPublishWorker.hpp"
#include "TopNBookSnapshot.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace b3::md {

class MdPublishPipeline {
public:
    MdPublishPipeline(uint32_t shardCount,
                      MdSnapshotMapper& mapper,
                      IMdPublisher& publisher,
                      std::string_view topic)
        : shardCount_(shardCount) {

        workers_.reserve(shardCount_);
        for (uint32_t i = 0; i < shardCount_; ++i) {
            workers_.emplace_back(
                std::make_unique<MdPublishWorker>(mapper, publisher, topic)
            );
        }
    }

    ~MdPublishPipeline() {
        stop();
    }

    void start() {
        for (auto& worker : workers_) {
            worker->start();
        }
    }

    void stop() {
        for (auto& worker : workers_) {
            worker->stop();
        }
    }

    // Producer side (MarketDataEngine / callback)
    bool enqueue(const BookSnapshot& snapshot) noexcept {
        auto& worker = workers_[shardFor(snapshot.instrumentId)];
        return worker->try_enqueue(snapshot);
    }

    uint32_t shardCount() const noexcept {
        return shardCount_;
    }

private:
    uint32_t shardFor(uint32_t instrumentId) const noexcept {
    
    uint32_t h = instrumentId * 2654435761u; // Multiplicative hash (Knuth)
    return h % shardCount_; //Guarda, que shardCount no sea potencia de 2 que resta uniformidad a la distribución
}

private:
    uint32_t shardCount_;
    std::vector<std::unique_ptr<MdPublishWorker>> workers_;
};

} // namespace b3::md
