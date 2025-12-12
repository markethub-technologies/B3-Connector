#include "OrderMessagingServer.hpp"
#include "OrderEngine.hpp"

int main() {
    OrderMessagingServer messaging;
    OrderEngine engine(&messaging);
    return 0;
}