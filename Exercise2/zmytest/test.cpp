#include <iostream>

/* ************************************************************************** */

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"
#include "../zlasdtest/vector/vector.hpp"

#include "../container/container.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"
#include "../container/mappable.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../list/list.hpp"
#include "../heap/vec/heapvec.hpp"
#include "../set/set.hpp"
#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"
#include "../vector/vector.hpp"

#include "./specificTests/list.hpp"
#include "./specificTests/vector.hpp"
#include "./specificTests/set.hpp"
#include "./specificTests/heap.hpp"
#include "./test.hpp"

using namespace std;

/* ************************************************************************** */

void mytest()
{
  uint loctestnum, loctesterr;
  uint stestnum = 0, stesterr = 0;

  // loctestnum = 0; loctesterr = 0;
  // daje::myVectorIntTest(loctestnum, loctesterr);
  // stestnum += loctestnum; stesterr += loctesterr;

  // loctestnum = 0; loctesterr = 0;
  // daje::myVectorStringTest(loctestnum, loctesterr);
  // stestnum += loctestnum; stesterr += loctesterr;

  // loctestnum = 0; loctesterr = 0;
  // daje::myListIntTest(loctestnum, loctesterr);
  // stestnum += loctestnum; stesterr += loctesterr;

  // loctestnum = 0; loctesterr = 0;
  // daje::myListStringTest(loctestnum, loctesterr);
  // stestnum += loctestnum; stesterr += loctesterr;

  // loctestnum = 0; loctesterr = 0;
  // daje::mySetIntTest(loctestnum, loctesterr);
  // stestnum += loctestnum; stesterr += loctesterr;

  // loctestnum = 0; loctesterr = 0;
  // daje::mySetStringTest(loctestnum, loctesterr);
  // stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  daje::myHeapVecIntTest(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  daje::myHeapVecStringTest(loctestnum, loctesterr);
  stestnum += loctestnum; stesterr += loctesterr;

  cout << endl << "Exercise 2 (Student's Test) (Errors/Tests: " << stesterr << "/" << stestnum << ")" << endl;
}
