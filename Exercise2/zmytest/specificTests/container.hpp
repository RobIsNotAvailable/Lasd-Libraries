#ifndef MYCONTAINERTEST_HPP
#define MYCONTAINERTEST_HPP


#include "../../zlasdtest/container/container.hpp"
#include "../../zlasdtest/container/dictionary.hpp"
#include "../../zlasdtest/container/linear.hpp"
#include "../../zlasdtest/container/mappable.hpp"
#include "../../zlasdtest/container/testable.hpp"
#include "../../zlasdtest/container/traversable.hpp"

#include "../../container/container.hpp"
#include "../../container/dictionary.hpp"
#include "../../container/linear.hpp"
#include "../../container/mappable.hpp"
#include "../../container/testable.hpp"
#include "../../container/traversable.hpp"

#include "../../vector/vector.hpp"

using namespace std;

namespace daje
{ 
    void EmptyContainerTest(uint& testnum, uint& testerr, lasd::LinearContainer<int>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        Empty(loctestnum, loctesterr, con, true);

        GetFront(loctestnum, loctesterr, con, false, 0);
        GetBack(loctestnum, loctesterr, con, false, 0);
        GetAt(loctestnum, loctesterr, con, false, 2, 0);

        Exists(loctestnum, loctesterr, con, false, 0);

        TraversePreOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 0);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void TraverseAndFriendsIntTest(uint& testnum, uint& testerr, lasd::MutableLinearContainer<int>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        TraversePreOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>); // traverse functions

        FoldPreOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 5);
        FoldPostOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 5); // fold functions

        lasd::Vector<int> copvec(con);

        MapPreOrder(loctestnum, loctesterr, con, true, &MapIncrement<int>);
        for (ulong i = 0; i < con.Size(); i++)
        {
            GetAt(loctestnum, loctesterr, con, true, i, copvec[i] + 1);
        }

        MapPostOrder(loctestnum, loctesterr, con, true, &MapIncrement<int>); // map functions
        for (ulong i = 0; i < con.Size(); i++)
        {
            GetAt(loctestnum, loctesterr, con, true, i, copvec[i] + 2);
        }

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void TraverseAndFriendsIntTest(uint& testnum, uint& testerr, lasd::LinearContainer<int>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        TraversePreOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>); // traverse functions

        FoldPreOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 5);
        FoldPostOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 5); // fold functions

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void TraverseAndFriendsIntTest(uint& testnum, uint& testerr, lasd::Heap<int>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        TraversePreOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>); // traverse functions

        FoldPreOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 292);
        FoldPostOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 292); // fold functions

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void TraverseAndFriendsStringTest(uint& testnum, uint& testerr, lasd::Heap<string>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        TraversePreOrder(loctestnum, loctesterr, con, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, con, true, &TraversePrint<string>); // traverse functions

        FoldPreOrder(loctestnum, loctesterr, con, true, &FoldStringConcatenate, string("inizio "), string("inizio stringano doppionedoppione@#!A<3*][|]G"));
        FoldPostOrder(loctestnum, loctesterr, con, true, &FoldStringConcatenate, string("inizio "), string("inizio G*][|]<3A@#!doppionedoppioneno stringa")); // fold functions

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void ContainerIntTest(uint& testnum, uint& testerr, lasd::MutableLinearContainer<int>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        SetAt(loctestnum, loctesterr, con, false, -1, 5);
        SetAt(loctestnum, loctesterr, con, false, 5, 4); //setting out of bounds

        Size(loctestnum, loctesterr, con, true, 5); //size after false insertions

        GetAt(loctestnum, loctesterr, con, true, 0, 4);
        GetAt(loctestnum, loctesterr, con, true, 1, 3);
        GetAt(loctestnum, loctesterr, con, true, 2, 0);
        GetAt(loctestnum, loctesterr, con, true, 3, 4);
        GetAt(loctestnum, loctesterr, con, true, 4, -6); // checking if the values are correct

        GetAt(loctestnum, loctesterr, con, false, -1, 5);
        GetAt(loctestnum, loctesterr, con, false, 5, 4); // getting out of bounds

        Exists(loctestnum, loctesterr, con, true, -6);//searching for existing value
        Exists(loctestnum, loctesterr, con, false, -4);//searching for non existing value

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void SortIntTest(uint& testnum, uint& testerr, lasd::SortableLinearContainer<int>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        con.Sort(); //sorting

        GetAt(loctestnum, loctesterr, con, true, 0, -4);
        GetAt(loctestnum, loctesterr, con, true, 1, 2);
        GetAt(loctestnum, loctesterr, con, true, 2, 5);
        GetAt(loctestnum, loctesterr, con, true, 3, 6);
        GetAt(loctestnum, loctesterr, con, true, 4, 6); //original values +2 (two map increment in previous test)

        Size(loctestnum, loctesterr, con, true, 5); //size after sorting

        testnum += loctestnum;
        testerr += loctesterr;
    }

    template <typename Data>
    void IsSorted(uint& testnum, uint& testerr, lasd::SortableLinearContainer<Data>& con, bool chk)
    {
        bool tst;
        testnum++;
        try {
            lasd::SortableVector<Data> vec(con);
            vec.Sort();
            cout << " " << testnum << " (" << testerr << ") The container is " << ((tst = (vec.lasd::LinearContainer<Data>::operator == (con))) ? "" : "not ") << "sorted: ";
            cout << (tst = ((vec.lasd::LinearContainer<Data>::operator == (con))) ? "Correct" : "Error") << "!" << endl;
        }
        catch (exception & exc) {
            cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << endl;
        }
        testerr += (1 - (uint) tst);
    }

    
    template <typename Data>
    void SortTest(uint& testnum, uint& testerr, lasd::SortableLinearContainer<Data>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        IsSorted(loctestnum, loctesterr, con, false);

        con.Sort();

        IsSorted(loctestnum, loctesterr, con, true);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void TraverseAndFriendsStringTest(uint& testnum, uint& testerr, lasd::MutableLinearContainer<string>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        TraversePreOrder(loctestnum, loctesterr, con, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, con, true, &TraversePrint<string>); // traverse functions

        FoldPreOrder(loctestnum, loctesterr, con, true, &FoldStringConcatenate, string("inizio "), string("inizio CDABE"));
        FoldPostOrder(loctestnum, loctesterr, con, true, &FoldStringConcatenate, string("inizio "), string("inizio EBADC")); // fold functions

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void TraverseAndFriendsStringTest(uint& testnum, uint& testerr, lasd::LinearContainer<string>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        TraversePreOrder(loctestnum, loctesterr, con, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, con, true, &TraversePrint<string>); // traverse functions

        FoldPreOrder(loctestnum, loctesterr, con, true, &FoldStringConcatenate, string("inizio "), string("inizio ABDJTY"));
        FoldPostOrder(loctestnum, loctesterr, con, true, &FoldStringConcatenate, string("inizio "), string("inizio YTJDBA")); // fold functions

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void ContainerStringTest(uint& testnum, uint& testerr, lasd::MutableLinearContainer<string>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        SetAt(loctestnum, loctesterr, con, false, -1, string("tanto non funziona"));
        SetAt(loctestnum, loctesterr, con, false, 5, string("tanto non funziona")); //setting out of bounds

        Size(loctestnum, loctesterr, con, true, 5); //size after false insertions

        GetAt(loctestnum, loctesterr, con, true, 0,string("C"));
        GetAt(loctestnum, loctesterr, con, true, 1,string("D"));
        GetAt(loctestnum, loctesterr, con, true, 2,string("A"));
        GetAt(loctestnum, loctesterr, con, true, 3,string("B"));
        GetAt(loctestnum, loctesterr, con, true, 4, string("E")); // checking if the values are correct

        GetAt(loctestnum, loctesterr, con, false, -1, string("tanto non funziona"));
        GetAt(loctestnum, loctesterr, con, false, 5, string("tanto non funziona")); // getting out of bounds

        Exists(loctestnum, loctesterr, con, true, string("C"));//searching for existing value
        Exists(loctestnum, loctesterr, con, false, string("nope"));//searching for non existing value

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void SortStringTest(uint& testnum, uint& testerr, lasd::SortableLinearContainer<string>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        con.Sort(); //sorting

        GetAt(loctestnum, loctesterr, con, true, 0, string("A"));
        GetAt(loctestnum, loctesterr, con, true, 1, string("B"));
        GetAt(loctestnum, loctesterr, con, true, 2, string("C"));
        GetAt(loctestnum, loctesterr, con, true, 3, string("D"));
        GetAt(loctestnum, loctesterr, con, true, 4, string("E")); //original values

        Size(loctestnum, loctesterr, con, true, 5); //size after sorting

        testnum += loctestnum;
        testerr += loctesterr;
    }
}

#endif