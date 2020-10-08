#pragma once
#include "result.hpp"
#include "simple-buffer.hpp"
#include <cstdio>
#include <string_view>

namespace pf {
  struct File {
    File(size_t size, FILE* fd)
        : size_{size}
        , fd_{fd} {}

    File(const File&) = delete;
    File& operator=(const File&) = delete;

    File(File&&)  = default;
    File& operator=(File&&) = default;

    ~File() noexcept;

    static Result<File>  open_read(std::string_view path);
    Result<SimpleBuffer> read();

  private:
    size_t size_;
    FILE*  fd_;
  };
} // namespace pf