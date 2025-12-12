#include "MarketDataEngine.hpp"
#include <gtest/gtest.h>

// Ejemplo MUY básico de test, para verificar que linkea y corre
TEST(MarketDataEngineTests, CanInstantiate) {
    // En el futuro le vas a pasar lo que haga falta (mock de messaging, etc.)
    MarketDataEngine* engine = nullptr; // placeholder hasta que tengas ctor real
    SUCCEED();
}
