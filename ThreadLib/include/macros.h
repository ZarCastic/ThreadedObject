//
// Created by Tobias Fuchs on 08.08.20.
//

#pragma once

#include <utility>

#define async(function_name)                                                \
  template <class... Args>                                                  \
  void async_##function_name(Args&... args) {                               \
    asyncCall(                                                              \
        [args..., this]() { function_name(std::forward<Args>(args)...); }); \
  }