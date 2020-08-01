//
// Created by Tobias Fuchs on 01.08.20.
//

#pragma once

#include <gtest/gtest.h>
#include <thread_holder.h>

class ThreadedObject : public ::testing::Test, public ThreadLib::ThreadHolder {
 public:
  explicit ThreadedObject(const std::string& name);
  explicit ThreadedObject(ThreadHolder& share);

  void asyncVoidWithoutParams();
  void asyncVoidWithParams();

 private:
};
