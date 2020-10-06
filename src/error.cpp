#include "error.hpp"

const char* pf::to_string(Error e) {
  switch (e) {
#define EXPAND_CASE_RETURN(name, desc) \
  case Error::name: return desc;
    ERRORS_X(EXPAND_CASE_RETURN)
#undef EXPAND_CASE_RETURN
    default: return "";
  }
}