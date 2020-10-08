#include "arguments.hpp"
#include "log.hpp"
#include "field.hpp"
#include "file.hpp"

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
    log::critical(args.error());
    Arguments::print_usage();
    RET_MAIN(EXIT_FAILURE);
  }

  auto field_file = File::open_read(args.value().input_field_filepath);
  if (field_file.has_error()) {
    log::critical(field_file.error());
    RET_MAIN(EXIT_FAILURE);
  }

  auto field_file_content = field_file.value().read();
  if (field_file_content.has_error()) {
    log::critical(field_file_content.error());
    RET_MAIN(EXIT_FAILURE);
  }

  auto field = Field::parse(field_file_content.value().string_view());
  if (field.has_error()) {
    log::critical(field.error());
    RET_MAIN(EXIT_FAILURE);
  }

  RET_MAIN(EXIT_SUCCESS);
}
