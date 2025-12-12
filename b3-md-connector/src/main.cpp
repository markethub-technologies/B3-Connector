#include "MessagingServer.hpp"
#include "MarketDataEngine.hpp"

int main() {
    MessagingServer messaging;
    MarketDataEngine engine(&messaging);
    return 0;
}
