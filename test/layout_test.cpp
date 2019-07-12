#define FMT_HEADER_ONLY = true

#include "qasm/qasm.hpp"
#include "qasm/visitors/source_printer.hpp"

#include "mapping/device.hpp"
#include "mapping/layout/basic.hpp"

using namespace synthewareQ;

int main(int argc, char** argv) {

  if (argc < 2) {
    std::cerr << "Input file not specified.\n";
  }

  auto program = qasm::read_from_file(argv[1]);
  if (program) {
    std::cout << "\nOriginal source:\n";
    qasm::source_printer src(std::cout);
    src.visit(*program);

    auto physical_layout = mapping::compute_layout(program.get(), mapping::rigetti_8q);
    mapping::apply_layout(program.get(), physical_layout);
    std::cout << "\nPhysical layout:\n";
    src.visit(*program);
  } else {
    std::cout << "Parsing of file \"" << argv[1] << "\" failed\n";
  }

  return 1;
}