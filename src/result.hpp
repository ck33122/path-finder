#pragma once
#include "error.hpp"
#include <optional>

namespace pf {
  template <typename TValue>
  struct Result : public std::optional<TValue> {
    using Base = std::optional<TValue>;
    using Base::Base;

    constexpr Result(Error error) noexcept // NOLINT(google-explicit-constructor)
        : error_{error} {}

    [[nodiscard]] constexpr bool has_error() const noexcept { return error_ != Error::None; }
    constexpr Error              error() const noexcept { return error_; }

  private:
    Error error_ = Error::None;
  };
} // namespace pf