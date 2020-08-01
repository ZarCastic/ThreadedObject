#include "util.h"
#include <thread>

namespace test_util {

bool waitFor(std::function<bool()> condition,
             std::chrono::milliseconds timeout) {
  using namespace std::chrono_literals;
  while (timeout > 0ms) {
    if (condition()) {
      return true;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    timeout -= 100ms;
  }

  return condition();
}

}  // namespace test_util