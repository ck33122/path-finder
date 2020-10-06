#pragma once
#include <cstdio>
#include <cstdarg>
#include "error.hpp"

namespace pf::log {
  inline void info(const char* fmt, ...) {
    fprintf(stdout, "[info] ");
    va_list args;
    va_start(args, fmt);
    std::vfprintf(stdout, fmt, args);
    va_end(args);
  }
  inline void error(const char* fmt, ...) {
    fprintf(stderr, "[error] ");
    va_list args;
    va_start(args, fmt);
    std::vfprintf(stderr, fmt, args);
    va_end(args);
  }
  inline void error(Error e) {
    std::fprintf(stderr, "[error] %s\n", to_string(e));
  }
} // namespace pf::log
