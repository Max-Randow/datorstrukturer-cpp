// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <string>
#include "grid.h"
#include "lifeutil.h"

int main() {
  // TODO: Finish the program!
  Grid<char> grid(5, 5);

  std::cout << grid.numCols() << '\n';

  std::cout << "Have a nice Life! " << std::endl;
  return 0;
}
