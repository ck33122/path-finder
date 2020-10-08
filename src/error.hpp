#pragma once

#define ERRORS_X(X)                                                                                          \
  X(None, "")                                                                                                \
  X(ParseArguments, "Ошибка парсинга входных аргументов")                                                    \
  X(LootboxIsolated, "Невозможно найти путь до одного или нескольких лутбоксов: он изолирован от персонажа") \
  X(ParsingField, "Ошибка парсинга поля. Возможно неверный формат описания")                                 \
  X(PathTooLong, "Слишком длинный путь к файлу")                                                             \
  X(StringTooLong, "Слишком длинная строка")                                                                 \
  X(FileNotFound, "Файл не найден")                                                                          \
  X(FileGetSize, "Не могу определить размер файла")                                                          \
  X(FileRead, "Ошибка чтения файла")

namespace pf {
  enum class [[nodiscard]] Error{
#define EXPAND_DECLARE_ENUM(name, _) name,
      ERRORS_X(EXPAND_DECLARE_ENUM)
#undef EXPAND_DECLARE_ENUM
  };

  const char* to_string(Error e);
} // namespace pf
