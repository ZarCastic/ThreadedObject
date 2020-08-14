//
// Created by Tobias Fuchs on 08.08.20.
//
#include "provider.h"
#include <iostream>
#include <random>
#include <thread>

Provider::Provider(int min, int max) : _min(min), _max(max) {}

void Provider::setConsumer(Consumer& consumer) { _consumer = &consumer; }

void Provider::resetConsumer() { _consumer = nullptr; }
void Provider::provide(const std::chrono::milliseconds& sleep_time) {
  static std::random_device random_device;
  static std::mt19937 generator(random_device());
  static std::uniform_int_distribution<> distribution(_min, _max);

  if (_consumer) {
    const int number = distribution(generator);
    _consumer->async_collect(number);
    std::cout << "Provided " << number << " from thread "
              << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(sleep_time);
  }
}
