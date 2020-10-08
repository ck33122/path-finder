#include "field.hpp"
#include "string-utils.hpp"
#include "log.hpp"
#include <array>

using namespace pf;

static constexpr auto input_cell_char_types = std::array{
    (char) CellType::Free,
    (char) CellType::Wall,
};

Result<Field> Field::parse(std::string_view field) {
  auto width  = field.find('\n'),
       height = std::string_view::size_type{};
  if (width == std::string_view::npos) {
    width  = field.size();
    height = 1;
  } else {
    height = (field.size() + 1) / (width + 1);
    if ((width + 1) * height != field.size() + 1) {
      return Error::ParsingField;
    }
  }
  if (width > UINT32_MAX || height > UINT32_MAX) {
    return Error::ParsingField;
  }

  auto values      = std::make_unique<char[]>(width * height);
  auto values_ptr  = values.get();
  auto current_row = uint32_t{0};
  auto ok          = str::split(field, '\n', [&](std::string_view row) {
    if (row.size() != width) {
      log::error("Длина строки поля не равна %u. Поле должно быть строго прямоугольной формы\n", width);
      return false;
    }
    auto input_char_broken_func = [](const char c) {
      return std::find(input_cell_char_types.cbegin(), input_cell_char_types.cend(), c) == input_cell_char_types.cend();
    };
    if (auto it = std::find_if(row.cbegin(), row.cend(), input_char_broken_func); it != row.cend()) {
      log::error("Один из символов поля был неопознан: %c\n", *it);
    }

    memcpy(values_ptr + current_row * width, row.data(), row.size());
    current_row++;

    if (current_row == height) {
      log::error("Количество строк в описании поля больше чем ожидалось. Поле должно быть строго прямоугольной формы.\n");
      return false;
    }
    return true;
  });
  if (!ok) {
    return Error::ParsingField;
  }
  return Field{(uint32_t) width, (uint32_t) height, std::move(values)};
}
