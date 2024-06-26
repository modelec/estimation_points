#include <atomic>
#include <iostream>
#include "tcp/MyClient.h"

std::atomic<bool> stopRequested(false);

void userInputThread() {
    // Wait for the user to press Enter
    std::cout << "Press Enter to stop the program..." << std::endl;
    std::cin.ignore();
    stopRequested = true;
}

int main() {
    MyClient client("127.0.0.1", 8080);

    client.start();

    client.sendMessage("point;start;ready;1");

    std::thread inputThread(userInputThread);

    while (true) {
        if(stopRequested) {
            break;
        }
        usleep(1'000'000);
    }

    return 0;
}
