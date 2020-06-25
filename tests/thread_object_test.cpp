#include "thread_object.h"
#include <gtest/gtest.h>
#include <iostream>
#include "test_util/util.h"

TEST(ThreadObject, Constructability) {
  ThreadLib::ThreadObject thread;
  thread.startThread();

  EXPECT_NE(std::this_thread::get_id(), thread.getId());

  thread.stopThread();
  thread.join();
}

TEST(ThreadObject, Copyability) {
  ThreadLib::ThreadObject thread_1;
  thread_1.startThread();
  ThreadLib::ThreadObject thread_2(thread_1);
  EXPECT_TRUE(thread_2.isRunning());

  EXPECT_NE(std::this_thread::get_id(), thread_1.getId());
  EXPECT_EQ(thread_1.getId(), thread_2.getId());

  ThreadLib::ThreadObject thread_3;
  thread_3.startThread();
  EXPECT_NE(std::this_thread::get_id(), thread_3.getId());
  EXPECT_NE(thread_1.getId(), thread_3.getId());
  EXPECT_NE(thread_2.getId(), thread_3.getId());

  thread_2 = thread_3;
  EXPECT_NE(thread_2.getId(), thread_1.getId());
  EXPECT_EQ(thread_2.getId(), thread_3.getId());

  thread_1.stopThread();
  thread_2.stopThread();
  thread_3.stopThread();

  thread_1.join();
  thread_2.join();
  thread_3.join();

  std::cout << "ciao" << std::endl;
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
                         std::chrono::milliseconds(100)));
  thread.stopThread();
  thread.join();
}