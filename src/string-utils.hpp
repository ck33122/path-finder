#pragma once
#include <string_view>
#include <cctype>
#include <algorithm>
#include <functional>

namespace pf {
  template <size_t size_>
  struct CStr {
    static constexpr size_t size = size_;

    inline static Result<CStr<size>> from(std::string_view sv) {
      if (sv.size() >= size) {
        return Error::StringTooLong;
      }
      CStr<size> res;
      memcpy(res.value, sv.data(), sv.size());
      res[sv.size()] = 0;
      res.length     = sv.size();
      return res;
    }

    operator char*() { return value; }             // NOLINT(google-explicit-constructor)
    operator const char*() const { return value; } // NOLINT(google-explicit-constructor)

  private:
    char     value[size];
    uint32_t length;
  };

  using CStr256 = CStr<256>;

  namespace str {
    inline std::string_view trim(std::string_view str) {
      auto left  = std::find_if(str.begin(), str.end(), [](auto ch) { return !std::isspace(ch); });
      auto right = std::find_if(str.rbegin(), str.rend(), [](auto ch) { return !std::isspace(ch); });
      auto begin = left - str.begin(),
           end   = str.rend() - right;
      if (end >= begin) {
        return str.substr(begin, end - begin);
      }
      return "";
    }

    inline bool split(std::string_view str, char c, const std::function<bool(std::string_view)>& func) {
      std::string_view::size_type it, from = 0;
      do {
        it = str.find(c, from);
        if (it == std::string_view::npos) {
          it = str.size();
        }
        if (!func(str.substr(from, it - from))) {
          return false;
        }
        from = it + 1;
      } while (from < str.size());
      return true;
    }
  } // namespace str
} // namespace pf