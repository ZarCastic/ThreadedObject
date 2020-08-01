#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <thread_object.h>
#include "test_util/util.h"

TEST(ThreadObject, Constructability) {
  ThreadLib::ThreadObject thread;
  thread.startThread();

  EXPECT_NE(std::this_thread::get_id(), thread.getId());
  thread.stopThread();
  thread.join();
}

TEST(ThreadObject, StartStop) {
  ThreadLib::ThreadObject thread;
  thread.startThread();

  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  EXPECT_TRUE(thread.joinable());
  thread.stopThread();
  thread.join();

  EXPECT_FALSE(thread.joinable());
}

TEST(ThreadObject, AsyncCallback) {
  ThreadLib::ThreadObject thread;

  std::atomic_bool callback_done = false;
  thread.startThread();
  thread.addCallback([&callback_done]() { callback_done = true; });

  EXPECT_TRUE(
      test_util::waitFor([&callback_done]() -> bool { return callback_done; },
                         std::chrono::milliseconds(1)));
  thread.stopThread();
  thread.join();
}

#pragma clang diagnostic pop