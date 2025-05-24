#ifndef MYVECTORTEST_HPP
#define MYVECTORTEST_HPP

#include "./container.hpp"
#include "../../zlasdtest/vector/vector.hpp"
#include "../../vector/vector.hpp"

using namespace std;

namespace daje
{
  template <typename Data>
  void CopyAndMoveVectorTest(uint& testnum, uint& testerr, lasd::Vector<Data> vec)
  {
    uint loctestnum = 0, loctesterr = 0;

    lasd::SortableVector<Data> copvec(vec);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);

    lasd::SortableVector<Data> movevec(move(copvec));
    EqualVector(loctestnum, loctesterr, vec, movevec, true);

    Empty(loctestnum, loctesterr, copvec, true);
    EqualVector(loctestnum, loctesterr, vec, copvec, false);
    
    lasd::SortableVector<Data> vec2;
    vec2 = vec;
    EqualVector(loctestnum, loctesterr, vec, vec2, true);

    vec2.Clear();

    vec2 = move(movevec);
    EqualVector(loctestnum, loctesterr, vec, vec2, true);
    
    Empty(loctestnum, loctesterr, movevec, true);
    EqualVector(loctestnum, loctesterr, vec, movevec, false);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  void ContainerConstructorVectorIntTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    lasd::List<int> lst;

    lasd::Vector<int> emptyvec(lst);
    EmptyContainerTest(loctestnum, loctesterr, emptyvec);

    lst.InsertAtFront(-4);
    lst.InsertAtFront(7);
    lst.InsertAtFront(104);
    lst.InsertAtFront(-88);

    lasd::Vector<int> vec1(lst);
    EqualLinear(loctestnum, loctesterr, vec1, lst, true);

    lasd::Vector<int> vec2(move(lst));
    EqualLinear(loctestnum, loctesterr, vec1, vec2, true);

    NonEqualLinear(loctestnum, loctesterr, vec1, lst, true);


    testnum += loctestnum;
    testerr += loctesterr;
  }

  void ContainerConstructorVectorStringTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    lasd::List<string> lst;

    lst.InsertAtFront(string("S"));
    lst.InsertAtFront(string("H"));
    lst.InsertAtFront(string("R"));
    lst.InsertAtFront(string("P"));

    lasd::Vector<string> vec1(lst);
    EqualLinear(loctestnum, loctesterr, vec1, lst, true);

    lasd::Vector<string> vec2(move(lst));
    EqualLinear(loctestnum, loctesterr, vec1, vec2, true);

    NonEqualLinear(loctestnum, loctesterr, vec1, lst, true);


    testnum += loctestnum;
    testerr += loctesterr;
  }

  void myVectorIntTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of myVector<int> Test:" << endl;
    try 
    {
      {
        cout << endl << "Vector<int>: testing different kind of empty vectors" << endl;

        lasd::SortableVector<int> vec;
        EmptyContainerTest(loctestnum, loctesterr, vec);

        vec = lasd::SortableVector<int>(0);
        EmptyContainerTest(loctestnum, loctesterr, vec);

        vec = lasd::SortableVector<int>(7);
        vec.Resize(0);
        EmptyContainerTest(loctestnum, loctesterr, vec);

        vec = lasd::SortableVector<int>(7);
        vec.Clear();
        EmptyContainerTest(loctestnum, loctesterr, vec);

        vec.Sort();
      }
      {
        lasd::SortableVector<int> vec(5);

        SetAt(loctestnum, loctesterr, vec, true, 0, 4);
        SetAt(loctestnum, loctesterr, vec, true, 1, 3);
        SetAt(loctestnum, loctesterr, vec, true, 2, 0);
        SetAt(loctestnum, loctesterr, vec, true, 3, 4);
        SetAt(loctestnum, loctesterr, vec, true, 4, -6);

        cout << endl << "Vector<int>: testing generic functions and edge cases" << endl;
        ContainerIntTest(loctestnum, loctesterr, vec);

        cout << endl << "Vector<int>: testing Copy and Move assignments and constructors" << endl;
        CopyAndMoveVectorTest(loctestnum, loctesterr, vec);

        cout << endl << "Vector<int>: testing constructors from containers" << endl;
        ContainerConstructorVectorIntTest(loctestnum, loctesterr);

        cout << endl << "Vector<int>: testing traverse, fold and map functions" << endl;
        TraverseAndFriendsIntTest(loctestnum, loctesterr, vec);

        cout << endl << "Vector<int>: testing sort function" << endl;
        SortIntTest(loctestnum, loctesterr, vec);
      }
    }
    catch (...)
    {
      loctestnum++; loctesterr++;
      cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of myVector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
  }

  void myVectorStringTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of myVector<string> Test:" << endl;
    try 
    {
      {
        lasd::SortableVector<string> vec(5);

        SetAt(loctestnum, loctesterr, vec, true, 0, string("C"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("B"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("E"));

        cout << endl << "Vector<string>: testing generic functions" << endl;
        ContainerStringTest(loctestnum, loctesterr, vec);

        cout << endl << "Vector<string>: testing Copy and Move assignments and constructors" << endl;
        CopyAndMoveVectorTest(loctestnum, loctesterr, vec);

        cout << endl << "Vector<string>: testing constructors from containers" << endl;
        ContainerConstructorVectorStringTest(loctestnum, loctesterr);

        cout << endl << "Vector<string>: testing traverse and fold functions" << endl;
        TraverseAndFriendsStringTest(loctestnum, loctesterr, vec);

        cout << endl << "Vector<string>: testing sort function" << endl;
        SortStringTest(loctestnum, loctesterr, vec);
      }
    }
    catch (...)
    {
      loctestnum++; loctesterr++;
      cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of myVector<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
  }
}

#endif