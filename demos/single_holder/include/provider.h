//
// Created by Tobias Fuchs on 08.08.20.
//

#pragma once

#include <chrono>
#include "consumer.h"
class Provider {
 public:
  explicit Provider(int min = 0, int max =100);

  void setConsumer(Consumer& consumer);
  void resetConsumer();
  void provide(const std::chrono::milliseconds& sleep_time);

 private:
  Consumer* _consumer = nullptr;
  const int _min = 0;
  const int _max = 100;
};
