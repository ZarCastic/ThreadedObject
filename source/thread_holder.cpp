#include "thread_holder.h"
#include "thread_object.h"

namespace ThreadLib {

ThreadHolder::ThreadHolder(const ThreadHolder& other)
    : __thread__(other.__thread__) {}

ThreadHolder& ThreadHolder::operator=(const ThreadHolder& other) {
  __thread__ = other.__thread__;
  return *this;
}

}  // namespace ThreadLib