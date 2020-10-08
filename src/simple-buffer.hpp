#pragma once
#include <memory>
#include <string_view>

namespace pf {
  struct SimpleBuffer {
    SimpleBuffer(const SimpleBuffer&) = delete;
    SimpleBuffer& operator=(const SimpleBuffer&) = delete;

    SimpleBuffer() noexcept = default;

    explicit SimpleBuffer(size_t size) noexcept
        : ptr_(malloc(size))
        , size_(size) {}

    SimpleBuffer(SimpleBuffer&& buf) noexcept
        : SimpleBuffer() {
      std::swap(ptr_, buf.ptr_);
      std::swap(size_, buf.size_);
    }

    SimpleBuffer& operator=(SimpleBuffer&& buf) noexcept {
      if (this != &buf) {
        std::swap(ptr_, buf.ptr_);
        std::swap(size_, buf.size_);
      }
      return *this;
    }

    ~SimpleBuffer() noexcept {
      if (ptr_) {
        free(ptr_);
      }
    }

    template <typename TPtr = uint8_t*>
    [[nodiscard]] TPtr ptr() { return reinterpret_cast<TPtr>(ptr_); }

    template <typename TPtr = const uint8_t*>
    [[nodiscard]] TPtr ptr() const { return reinterpret_cast<TPtr>(ptr_); }

    [[nodiscard]] size_t           size() const { return size_; }
    [[nodiscard]] std::string_view string_view() const { return std::string_view{ptr<const char*>(), size()}; }

  private:
    void*  ptr_  = nullptr;
    size_t size_ = 0;
  };
} // namespace pf