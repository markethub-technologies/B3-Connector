#include <gtest/gtest.h>

#include "../../b3-md-connector/src/telemetry/SpdlogLogPublisher.hpp"
#include "../../b3-md-connector/src/telemetry/LogEvent.hpp"

#include <chrono>
#include <thread>

using namespace b3::md::telemetry;

TEST(SpdlogLogPublisherTests, StartStopClean) {
    SpdlogLogPublisher<64> pub;
    pub.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    pub.stop();
    SUCCEED();
}

TEST(SpdlogLogPublisherTests, DropsWhenQueueIsFull) {
    // Capacidad chica a propósito para forzar saturación
    SpdlogLogPublisher<8> pub;
    pub.start();

    LogEvent e{};
    e.level = LogLevel::Info;
    e.component = Component::Worker;
    e.code = Code::HealthTick;

    // Encolamos mucho sin dormir: inevitablemente se llena y dropea
    constexpr int N = 5000;
    for (int i = 0; i < N; ++i) {
        e.arg0 = static_cast<uint64_t>(i);
        (void)pub.try_publish(e);
    }

    // Dejá que el thread consuma un poco
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    pub.stop();

    // Con capacidad 8 y N=5000, casi seguro dropeó algo
    EXPECT_GT(pub.dropped(), 0u);
}

TEST(SpdlogLogPublisherTests, DoesNotDropUnderLightLoad) {
    SpdlogLogPublisher<1024> pub;
    pub.start();

    LogEvent e{};
    e.level = LogLevel::Info;
    e.component = Component::Core;
    e.code = Code::Startup;

    // Carga liviana + pequeñas pausas -> no debería dropear
    constexpr int N = 200;
    for (int i = 0; i < N; ++i) {
        e.arg0 = static_cast<uint64_t>(i);
        ASSERT_TRUE(pub.try_publish(e));
        std::this_thread::sleep_for(std::chrono::microseconds(200));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    pub.stop();

    EXPECT_EQ(pub.dropped(), 0u);
}