#include "thread_object.h"
#include <gtest/gtest.h>
#include "test_util/util.h"

TEST(ThreadObject, Contractibility) { ThreadLib::ThreadObject thread; }

TEST(ThreadObject, StartStop) {
  ThreadLib::ThreadObject thread;
  thread.startThread();

  std::this_thread::sleep_for(std::chrono::seconds(1));
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
                         std::chrono::seconds(1)));
}