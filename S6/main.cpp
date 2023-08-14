#include "SortingsManagement.h"

int main(int argc, const char *argv[])
{
  if (argc != 4) {
    std::cerr << "Error: invalid amount of arguments.";
    return 1;
  }

  std::string sorting_order(argv[1]);
  std::string value_type(argv[2]);
  std::size_t container_size;
  try {
    container_size = std::stoul(argv[3]);
  } catch (...) {
    std::cerr << "Error: invalid amount of numbers.";
    return 1;
  }

  try {
    if (value_type == "ints") {
      if (sorting_order == "ascending") {
        siobko::SortingsManagement< int, std::less<> > sortingsManagement(container_size);
        sortingsManagement.testSortings(std::cout);
      } else {
        siobko::SortingsManagement< int, std::greater<> > sortingsManagement(container_size);
        sortingsManagement.testSortings(std::cout);
      }
    } else if (value_type == "floats") {
      if (sorting_order == "ascending") {
        siobko::SortingsManagement< double, std::less<> > sortingsManagement(container_size);
        sortingsManagement.testSortings(std::cout);
      } else {
        siobko::SortingsManagement< double, std::greater<> > sortingsManagement(container_size);
        sortingsManagement.testSortings(std::cout);
      }
    } else {
      std::cerr << "Error: invalid sorting strategy order.";
      return 1;
    }
  }
  catch (const std::exception & e){
    std::cerr<<e.what()<<'\n';
    return 1;
  }
}
