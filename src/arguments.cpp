#include "arguments.hpp"
#include "log.hpp"

using namespace pf;

Result<Arguments> Arguments::parse(int argc, char** argv) {
  if (argc != 4) {
    return Error::ParseArguments;
  }
  Arguments args;
  args.input_field_filepath = argv[1];
  args.output_filepath      = argv[2];
  if (sscanf(argv[3], "%u", &args.loot_box_count) != 1) {
    return Error::ParseArguments;
  }
  return args;
}

void Arguments::print_usage() {
  fprintf(stdout, "\n"
                  "Path-finder находчик лутбоксов. Аргументы программы:\n"
                  "\t[1] путь до входного файла с описанием игрового поля,\n"
                  "\t[2] путь до выходного файла,\n"
                  "\t[3] количество лутбоксов.\n"
                  "Пример:\n"
                  "\t./path-finder input.txt output.txt 10\n");
}
