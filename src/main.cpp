#include "arguments.hpp"
#include "log.hpp"

using namespace pf;

#define RET_MAIN(code) \
  {                    \
    fflush(stderr);    \
    fflush(stdout);    \
    return code;       \
  }

int main(int argc, char** argv) {
  auto args = Arguments::parse(argc, argv);
  if (args.has_error()) {
    log::error(args.error());
    Arguments::print_usage();
    RET_MAIN(EXIT_FAILURE);
  }

  RET_MAIN(EXIT_SUCCESS);
}
