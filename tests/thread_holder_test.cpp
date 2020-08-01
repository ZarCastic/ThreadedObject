#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "thread_holder.h"
#include <gtest/gtest.h>
#include "test_util/util.h"

TEST(ThreadHolder, Constructability) { ThreadLib::ThreadHolder thread_holder; }

TEST(ThreadHolder, Copyability) {
  ThreadLib::ThreadHolder thread_holder_1;
  ThreadLib::ThreadHolder thread_holder_2(thread_holder_1);
}

TEST(ThreadHolder, AsyncCallWithoutReturnValue) {
  ThreadLib::ThreadHolder thread_holder;

  std::atomic_bool callback_done = false;
  auto task = [&callback_done]() { callback_done = true; };

  thread_holder.asyncCall(task);

  EXPECT_TRUE(
      test_util::waitFor([&callback_done]() -> bool { return callback_done; },
                         std::chrono::milliseconds(1)));
}

TEST(ThreadHolder, SyncCallWithReturnValue) {
  ThreadLib::ThreadHolder thread_holder;

  auto task = []() -> bool { return true; };

  EXPECT_TRUE(thread_holder.syncCall<bool>(task));
}

TEST(ThreadHolder, DifferentLifetimes) {
  ThreadLib::ThreadHolder main_holder;
  ThreadLib::ThreadHolder shared_holder(main_holder);

  auto task = []() -> bool { return true; };
  EXPECT_TRUE(main_holder.syncCall<bool>(task));
  EXPECT_TRUE(shared_holder.syncCall<bool>(task));
}

TEST(ThreadHolder, MultipleHolders) {
  ThreadLib::ThreadHolder *main_holder = new ThreadLib::ThreadHolder();
  ThreadLib::ThreadHolder shared_holder(*main_holder);

  auto task = []() -> bool { return true; };
  EXPECT_TRUE(main_holder->syncCall<bool>(task));
  EXPECT_TRUE(shared_holder.syncCall<bool>(task));

  delete main_holder;
  EXPECT_TRUE(shared_holder.syncCall<bool>(task));
  EXPECT_TRUE(shared_holder.syncCall<bool>(task));

  main_holder = new ThreadLib::ThreadHolder(shared_holder);
  EXPECT_TRUE(main_holder->syncCall<bool>(task));
  EXPECT_TRUE(shared_holder.syncCall<bool>(task));

  delete main_holder;
}

#pragma clang diagnostic pop