
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "LASD Libraries 2025" << std::endl;
  int choice = 0;
  while (true)
  {
    std::cout << "Press 1 to run lasdtest, 2 to run mytest, anything else to exit." << std::endl;
    std::cin >> choice;
    if (choice == 1)
      lasdtest();
    else if (choice == 2)
      mytest();
    else
      return 0;
  }
  return 0;
}
