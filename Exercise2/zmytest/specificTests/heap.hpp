#ifndef MYHEAPTEST_HPP
#define MYHEAPTEST_HPP

#include "../../zlasdtest/heap/heap.hpp"
#include "../../zlasdtest/container/linear.hpp"

#include "../../heap/vec/heapvec.hpp"

#include "./container.hpp"

using namespace std;

namespace daje
{
  template <typename Data>
  void CopyAndMoveHeapVecTest(uint& testnum, uint& testerr, lasd::HeapVec<Data> heap)
  {
    uint loctestnum = 0, loctesterr = 0;

    lasd::HeapVec<Data> copheap(heap);
    EqualLinear(loctestnum, loctesterr, heap, copheap, true);

    lasd::HeapVec<Data> moveheap(move(copheap));
    EqualLinear(loctestnum, loctesterr, heap, moveheap, true);

    Empty(loctestnum, loctesterr, copheap, true);
    EqualLinear(loctestnum, loctesterr, heap, copheap, false);
    
    lasd::HeapVec<Data> heap2;
    heap2 = heap;
    EqualLinear(loctestnum, loctesterr, heap, heap2, true);

    heap2.Clear();

    heap2 = move(moveheap);
    EqualLinear(loctestnum, loctesterr, heap, heap2, true);
    
    Empty(loctestnum, loctesterr, moveheap, true);
    EqualLinear(loctestnum, loctesterr, heap, moveheap, false);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  void ContainerConstructorHeapVecIntTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    lasd::List<int> lst;

    lst.InsertAtFront(-4);
    lst.InsertAtFront(7);
    lst.InsertAtFront(104);
    lst.InsertAtFront(-88);

    lasd::HeapVec<int> heap1(lst);
    IsHeap(loctestnum, loctesterr, heap1, true);
    for (uint i = 0; i < lst.Size(); ++i)
    {
      Exists(loctestnum, loctesterr, heap1, true, lst[i]);
    }

    lasd::List<int> throwawaylst(lst);

    lasd::HeapVec<int> heap2(move(throwawaylst));
    EqualLinear(loctestnum, loctesterr, heap1, heap2, true);

    NonEqualLinear(loctestnum, loctesterr, throwawaylst, lst, true);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  void ContainerConstructorHeapVecStringTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    lasd::List<string> lst;

    lst.InsertAtFront(string("S"));
    lst.InsertAtFront(string("H"));
    lst.InsertAtFront(string("R"));
    lst.InsertAtFront(string("P"));

    lasd::HeapVec<string> heap1(lst);
    for (uint i = 0; i < lst.Size(); ++i)
    {
      Exists(loctestnum, loctesterr, heap1, true, lst[i]);
    }

    lasd::List<string> throwawaylst(lst);

    lasd::HeapVec<string> heap2(move(throwawaylst));
    EqualLinear(loctestnum, loctesterr, heap1, heap2, true);

    NonEqualLinear(loctestnum, loctesterr, throwawaylst, lst, true);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  template <typename Data>
  void HeapVecTest(uint& testnum, uint& testerr, lasd::HeapVec<Data> heap)
  {
    uint loctestnum = 0, loctesterr = 0;
    
    lasd::HeapVec<Data> emptyheap;
    IsHeap(loctestnum, loctesterr, emptyheap, true);
    emptyheap.Heapify();
    emptyheap.Sort();
    TraversePreOrder(loctestnum, loctesterr, emptyheap, true, &TraversePrint<Data>);

    lasd::Vector<Data> vec(1);
    SetAt(loctestnum, loctesterr, vec, true, 0, heap[0]);

    lasd::HeapVec<Data> smallheap(vec);
    IsHeap(loctestnum, loctesterr, smallheap, true);
    smallheap.Heapify();
    smallheap.Sort();
    TraversePreOrder(loctestnum, loctesterr, smallheap, true, &TraversePrint<Data>);

    heap.Heapify();
    IsHeap(loctestnum, loctesterr, heap, true);
    heap.Sort();
    IsSorted(loctestnum, loctesterr, heap, true);
    IsHeap(loctestnum, loctesterr, heap, false);
    heap.Heapify();
    TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<Data>);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  void myHeapVecIntTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of myHeapVec<int> Test:" << endl;
    try 
    {
      lasd::SortableVector<int> vec(9);

      SetAt(loctestnum, loctesterr, vec, true, 0, 89);
      SetAt(loctestnum, loctesterr, vec, true, 1, 43);
      SetAt(loctestnum, loctesterr, vec, true, 2, -84);
      SetAt(loctestnum, loctesterr, vec, true, 3, 105);
      SetAt(loctestnum, loctesterr, vec, true, 4, 0);
      SetAt(loctestnum, loctesterr, vec, true, 5, -31);
      SetAt(loctestnum, loctesterr, vec, true, 6, 43);
      SetAt(loctestnum, loctesterr, vec, true, 7, 22);
      SetAt(loctestnum, loctesterr, vec, true, 8, 105);

      lasd::HeapVec<int> heap(vec);

      cout << endl << "HeapVec<int>: testing generic functions and edge cases" << endl;
      HeapVecTest(loctestnum, loctesterr, heap);

      cout << endl << "HeapVec<int>: testing Copy and Move assignments and constructors" << endl;
      CopyAndMoveHeapVecTest(loctestnum, loctesterr, heap);

      cout << endl << "HeapVec<int>: testing constructors from containers" << endl;
      ContainerConstructorHeapVecIntTest(loctestnum, loctesterr);

      cout << endl << "HeapVec<int>: testing traverse and fold functions" << endl;
      TraverseAndFriendsIntTest(loctestnum, loctesterr, heap);

      cout << endl << "HeapVec<int>: testing sort function" << endl;
      SortTest(loctestnum, loctesterr, heap);
    }
    catch (...)
    {
      loctestnum++; loctesterr++;
      cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of myHeapVec<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
  }

  void myHeapVecStringTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of myHeapVec<string> Test:" << endl;
    try 
    {
      lasd::SortableVector<string> vec(9);

      SetAt(loctestnum, loctesterr, vec, true, 0, string("@#!"));
      SetAt(loctestnum, loctesterr, vec, true, 1, string("stringa"));
      SetAt(loctestnum, loctesterr, vec, true, 2, string("A"));
      SetAt(loctestnum, loctesterr, vec, true, 3, string("G"));
      SetAt(loctestnum, loctesterr, vec, true, 4, string("no "));
      SetAt(loctestnum, loctesterr, vec, true, 5, string("doppione"));
      SetAt(loctestnum, loctesterr, vec, true, 6, string("<3"));
      SetAt(loctestnum, loctesterr, vec, true, 7, string("*][|]"));
      SetAt(loctestnum, loctesterr, vec, true, 8, string("doppione"));

      lasd::HeapVec<string> heap(vec);

      cout << endl << "HeapVec<string>: testing generic functions and edge cases" << endl;
      HeapVecTest(loctestnum, loctesterr, heap);

      cout << endl << "HeapVec<string>: testing Copy and Move assignments and constructors" << endl;
      CopyAndMoveHeapVecTest(loctestnum, loctesterr, heap);

      cout << endl << "HeapVec<string>: testing traverse and fold functions" << endl;
      TraverseAndFriendsStringTest(loctestnum, loctesterr, heap);

      cout << endl << "HeapVec<string>: testing sort function" << endl;
      SortTest(loctestnum, loctesterr, heap);
    }
    catch (...)
    {
      loctestnum++; loctesterr++;
      cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of myHeapVec<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
  }
}

#endif