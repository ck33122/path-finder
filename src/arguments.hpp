#pragma once
#include "result.hpp"
#include <string_view>

namespace pf {
  struct Arguments {
    static Result<Arguments> parse(int argc, char** argv);
    static void              print_usage();

    std::string_view input_field_filepath;
    std::string_view output_filepath;
    unsigned int     loot_box_count;
  };
} // namespace pf