#ifndef MYPQHEAP_HPP
#define MYPQHEAP_HPP

#include "../../zlasdtest/container/container.hpp"
#include "../../zlasdtest/container/dictionary.hpp"
#include "../../zlasdtest/container/linear.hpp"
#include "../../zlasdtest/container/mappable.hpp"
#include "../../zlasdtest/container/testable.hpp"
#include "../../zlasdtest/container/traversable.hpp"

#include "../../zlasdtest/pq/pq.hpp"

#include "../../pq/heap/pqheap.hpp"

using namespace std;

namespace daje
{
  template <typename Data>
  void CopyAndMovePQHeapTest(uint& testnum, uint& testerr, lasd::PQHeap<Data> pq)
  {
    uint loctestnum = 0, loctesterr = 0;

    lasd::PQHeap<Data> coppq(pq);
    EqualLinear(loctestnum, loctesterr, pq, coppq, true);

    lasd::PQHeap<Data> movepq(move(coppq));
    EqualLinear(loctestnum, loctesterr, pq, movepq, true);

    Empty(loctestnum, loctesterr, coppq, true);
    EqualLinear(loctestnum, loctesterr, pq, coppq, false);
    
    lasd::PQHeap<Data> pq2;
    pq2 = pq;
    EqualLinear(loctestnum, loctesterr, pq, pq2, true);

    pq2.Clear();

    pq2 = move(movepq);
    EqualLinear(loctestnum, loctesterr, pq, pq2, true);

    Empty(loctestnum, loctesterr, movepq, true);
    EqualLinear(loctestnum, loctesterr, pq, movepq, false);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  void ContainerConstructorPQHeapIntTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    lasd::List<int> lst;

    lst.InsertAtFront(-4);
    lst.InsertAtFront(7);
    lst.InsertAtFront(104);
    lst.InsertAtFront(-88);

    lasd::PQHeap<int> heap1(lst);
    IsHeap(loctestnum, loctesterr, heap1, true);
    for (uint i = 0; i < lst.Size(); ++i)
    {
      Exists(loctestnum, loctesterr, heap1, true, lst[i]);
    }

    lasd::List<int> throwawaylst(lst);

    lasd::PQHeap<int> heap2(move(throwawaylst));
    EqualLinear(loctestnum, loctesterr, heap1, heap2, true);

    NonEqualLinear(loctestnum, loctesterr, throwawaylst, lst, true);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  void ContainerConstructorPQHeapStringTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    lasd::List<string> lst;

    lst.InsertAtFront(string("S"));
    lst.InsertAtFront(string("H"));
    lst.InsertAtFront(string("R"));
    lst.InsertAtFront(string("P"));

    lasd::PQHeap<string> heap1(lst);
    for (uint i = 0; i < lst.Size(); ++i)
    {
      Exists(loctestnum, loctesterr, heap1, true, lst[i]);
    }

    lasd::List<string> throwawaylst(lst);

    lasd::PQHeap<string> heap2(move(throwawaylst));
    EqualLinear(loctestnum, loctesterr, heap1, heap2, true);

    NonEqualLinear(loctestnum, loctesterr, throwawaylst, lst, true);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  template <typename Data>
  void InsertM(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, Data&& val) 
  {
    testnum++;
    bool tst = true;
    try {
      cout << " " << testnum << " Insert on the priority queue of the value \"" << val << "\": ";
      pq.Insert(move(val));
      cout << "Correct!" << endl;
    }
    catch (exception & exc) {
      cout << "\"" << exc.what() << "\": " << "Error!" << endl;
      tst = false;
    }
    testerr += (1 - (uint) tst);
  }

  template <typename Data>
  void ChangeM(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, bool chk, ulong idx, Data&& val) 
  {
    testnum++;
    bool tst = true;
    try {
      cout << " " << testnum << " Change the value \"" << pq[idx] << "\" at index << \"" << idx << "\" to the value \"" << val << "\" in the priority queue: ";
      pq.Change(idx, move(val));
      cout << (chk ? "Correct" : "Error") << "!" << endl;
      tst = chk;
    }
    catch (exception & exc) {
      cout << exc.what() << "\": " << (!chk ? "Correct" : "Error") << "!" << endl;
      tst = !chk;
    }
    testerr += (1 - (uint) tst);
  }

  template <typename Data>
  void PQHeapTest(uint& testnum, uint& testerr, lasd::SortableVector<Data> vec)
  {
    uint loctestnum = 0, loctesterr = 0;
    
    lasd::PQHeap<Data> pq;
    Size(loctestnum, loctesterr, pq, true, 0);

    Tip(loctestnum, loctesterr, pq, false, vec[0]);
    RemoveTip(loctestnum, loctesterr, pq, false);
    TipNRemove(loctestnum, loctesterr, pq, false, vec[0]);
    
    lasd::SortableVector<Data> copvec(vec);

    ulong size = vec.Size();

    for (ulong i = 0; i < size; ++i)
    {
      if (i % 2 == 0)
        Insert(loctestnum, loctesterr, pq, vec[i]);
      else
        InsertM(loctestnum, loctesterr, pq, move(vec[i]));
  
      IsHeap(loctestnum, loctesterr, pq, true);
    }

    vec = copvec;

    vec.Sort();

    for (ulong i = 1; i <= size; ++i)
    {
      Tip(loctestnum, loctesterr, pq, true, vec[size - i]);
      if (i % 2 == 0)
        RemoveTip(loctestnum, loctesterr, pq, true);
      else
        TipNRemove(loctestnum, loctesterr, pq, true, vec[size - i]);

      IsHeap(loctestnum, loctesterr, pq, true);
    }

    Tip(loctestnum, loctesterr, pq, false, vec[0]);
    RemoveTip(loctestnum, loctesterr, pq, false);
    TipNRemove(loctestnum, loctesterr, pq, false, vec[0]);

    for (ulong i = 0; i < vec.Size(); ++i)
    {
      Insert(loctestnum, loctesterr, pq, vec[i]);
      IsHeap(loctestnum, loctesterr, pq, true);
    }

    for (ulong i = 0; i + 1 < pq.Size(); i++)
    {
      Change(loctestnum, loctesterr, pq, true, i, vec[0]); // changing values in the pq so that the change move can actually change the values in the vec
    }

    for (ulong i = 0; i + 1 < vec.Size(); i++)
    {
      if (i % 2 == 0)
        Change(loctestnum, loctesterr, pq, true, i, vec[i]);
      else
        ChangeM(loctestnum, loctesterr, pq, true, i, move(vec[i]));
      
      IsHeap(loctestnum, loctesterr, pq, true);
    }

    copvec.Sort();

    EqualLinear(loctestnum, loctesterr, vec, copvec, false);

    Change(loctestnum, loctesterr, pq, 500, false, vec[0]);

    testnum += loctestnum;
    testerr += loctesterr;
  }

  void myPQHeapIntTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of myPQHeap<int> Test:" << endl;
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

      lasd::PQHeap<int> pq(vec);

      cout << endl << "PQHeap<int>: testing generic functions and edge cases" << endl;
      PQHeapTest(loctestnum, loctesterr, pq);

      cout << endl << "PQHeap<int>: testing Copy and Move assignments and constructors" << endl;
      CopyAndMovePQHeapTest(loctestnum, loctesterr, pq);

      cout << endl << "PQHeap<int>: testing constructors from containers" << endl;
      ContainerConstructorPQHeapIntTest(loctestnum, loctesterr);

      cout << endl << "PQHeap<int>: testing traverse and fold functions" << endl;
      TraverseAndFriendsIntTest(loctestnum, loctesterr, pq);

      cout << endl << "PQHeap<int>: testing sort function" << endl;
      SortTest(loctestnum, loctesterr, pq);
    }
    catch (...)
    {
      loctestnum++; loctesterr++;
      cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of myPQHeap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
  }

  void myPQHeapStringTest(uint& testnum, uint& testerr)
  {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of myPQHeap<string> Test:" << endl;
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

      lasd::PQHeap<string> pq(vec);

      cout << endl << "PQHeap<string>: testing generic functions and edge cases" << endl;
      PQHeapTest(loctestnum, loctesterr, vec);

      cout << endl << "PQHeap<string>: testing Copy and Move assignments and constructors" << endl;
      CopyAndMovePQHeapTest(loctestnum, loctesterr, pq);

      cout << endl << "PQHeap<string>: testing traverse and fold functions" << endl;
      TraverseAndFriendsStringTest(loctestnum, loctesterr, pq);

      cout << endl << "PQHeap<string>: testing sort function" << endl;
      SortTest(loctestnum, loctesterr, pq);
    }
    catch (...)
    {
      loctestnum++; loctesterr++;
      cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of myPQHeap<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
  }
}

#endif