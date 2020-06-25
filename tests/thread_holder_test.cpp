#include "thread_holder.h"
#include <gtest/gtest.h>

TEST(ThreadHolder, Constructability) { ThreadLib::ThreadHolder thread_holder; }

TEST(ThreadHolder, Copyability) {
  ThreadLib::ThreadHolder thread_holder_1;
  ThreadLib::ThreadHolder thread_holder_2(thread_holder_1);
}
