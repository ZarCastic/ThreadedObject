//
// Created by Tobias Fuchs on 08.08.20.
//
#include <consumer.h>
#include <provider.h>

int main() {
  using namespace std::chrono_literals;

  Provider provider;
  Consumer consumer(30ms);

  provider.setConsumer(consumer);

  for (auto i = 0; i < 100; ++i) {
    provider.provide(20ms);
  }

  return 0;
}