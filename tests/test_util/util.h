#pragma once

#include <chrono>
#include <functional>

namespace test_util {

bool waitFor(std::function<bool()> condition,
             std::chrono::milliseconds timeout);

}  // namespace test_util