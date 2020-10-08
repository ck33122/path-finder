#include "file.hpp"
#include "string-utils.hpp"
#include "log.hpp"
#include <filesystem>

using namespace pf;

Result<File> File::open_read(std::string_view path) {
  auto cpath = CStr256::from(path);
  if (cpath.has_error()) {
    if (cpath.error() == Error::StringTooLong) {
      log::error("Слишком длинный путь к файлу '%s'\n", (const char*) cpath.value());
      return Error::PathTooLong;
    }
    return cpath.error();
  }

  auto fd = fopen(cpath.value(), "rb");
  if (fd == nullptr) {
    log::error("Файл '%s' не найден\n", (const char*) cpath.value());
    return Error::FileNotFound;
  }

  std::error_code size_err;
  auto            size = std::filesystem::file_size(path, size_err);
  if (size_err) {
    log::error("Не могу определить размер файла '%s'\n", (const char*) cpath.value());
    return Error::FileGetSize;
  }

  return File{size, fd};
}

File::~File() noexcept {
  fclose(fd_);
}

Result<SimpleBuffer> File::read() {
  auto   buffer    = SimpleBuffer(size_);
  size_t readed    = 0;
  int    was_error = 0;
  while (readed != size_ && !std::feof(fd_) && !(was_error = std::ferror(fd_))) {
    auto read_at    = buffer.ptr<>() + readed;
    auto read_count = size_ - readed;
    readed += std::fread(read_at, sizeof(uint8_t), read_count, fd_);
  }
  if (was_error) {
    log::error("Чтение из файла неудалось: %s\n", std::strerror(was_error));
    return Error::FileRead;
  }
  if (readed == size_) {
    return buffer;
  }
  log::error("Неожиданное окончание файла\n");
  return Error::FileRead;
}
