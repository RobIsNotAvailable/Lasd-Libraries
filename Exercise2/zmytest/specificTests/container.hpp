#ifndef MYCONTAINERTEST_HPP
#define MYCONTAINERTEST_HPP


#include "../../zlasdtest/container/mappable.hpp"
#include "../../zlasdtest/container/traversable.hpp"

#include "../../container/linear.hpp"

#include "../../vector/vector.hpp"

using namespace std;

namespace daje
{ 
    void TraverseAndFriendsIntTest(uint& testnum, uint& testerr, lasd::Heap<int>& con)
    {
        uint loctestnum = 0, loctesterr = 0;

        TraversePreOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, con, true, &TraversePrint<int>); // traverse functions

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

        FoldPreOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 310);
        FoldPostOrder(loctestnum, loctesterr, con, true, &FoldAdd<int>, 0, 310); // fold functions

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

    template <typename Data>
    void IsSorted(uint& testnum, uint& testerr, lasd::SortableLinearContainer<Data>& con, bool chk)
    {
        bool tst;
        testnum++;
        try {
            lasd::SortableVector<Data> vec(con);
            vec.Sort();
            cout << " " << testnum << " (" << testerr << ") The container is " << ((tst = (vec.lasd::LinearContainer<Data>::operator == (con))) ? "" : "not ") << "sorted: ";
            cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << endl;
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

}

#endif