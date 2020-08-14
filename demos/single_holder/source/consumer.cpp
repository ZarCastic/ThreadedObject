//
// Created by Tobias Fuchs on 08.08.20.
//

#include "consumer.h"
#include <iostream>

Consumer::Consumer(std::chrono::milliseconds timeout)
    : ThreadHolder("Consumer"), _timeout(timeout) {}

void Consumer::collect(int number) {
  std::cout << "Consumed " << number << " in thread " << getThreadId()
            << std::endl;
  std::this_thread::sleep_for(_timeout);
}
