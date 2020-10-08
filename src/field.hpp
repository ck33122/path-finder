#pragma once
#include "result.hpp"
#include <memory>
#include <string_view>

namespace pf {
  enum class CellType : char {
    Free = '+',
    Wall = ' ',
  };

  struct Field {
    Field(uint32_t width, uint32_t height, std::unique_ptr<char[]>&& values)
        : width{width}
        , height{height}
        , values(std::move(values)) {}

    Field(Field&&) = default;
    Field& operator=(Field&&) = default;

    Field(const Field&) = delete;
    Field& operator=(const Field&) = delete;

    static Result<Field> parse(std::string_view field);

  private:
    uint32_t                width;
    uint32_t                height;
    std::unique_ptr<char[]> values;
  };
} // namespace pf
