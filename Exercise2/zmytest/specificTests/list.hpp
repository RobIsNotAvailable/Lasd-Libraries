#ifndef MYLISTTEST_HPP
#define MYLISTTEST_HPP

#include "./container.hpp"
#include "../../zlasdtest/list/list.hpp"
#include "../../list/list.hpp"

using namespace std;

namespace daje
{
    void ListEdgeCases(uint& testnum, uint& testerr, lasd::List<int> lst) // ensures that the different functions work with few elements  
    {                                                                     // and keep the list serviceable after removing the last element in different ways
        uint loctestnum = 0, loctesterr = 0;

        EmptyContainerTest(loctestnum, loctesterr, lst);

        InsertAtFront(loctestnum, loctesterr, lst, true, 4);
        InsertAtFront(loctestnum, loctesterr, lst, true, 3);
        InsertAtBack(loctestnum, loctesterr, lst, true, 7);

        RemoveFromFront(loctestnum, loctesterr, lst, true);
        RemoveFromFront(loctestnum, loctesterr, lst, true);
        RemoveFromFront(loctestnum, loctesterr, lst, true);
        EmptyContainerTest(loctestnum, loctesterr, lst);
        InsertAtFront(loctestnum, loctesterr, lst, true, 4); // clearing with removefromfront
        InsertAtFront(loctestnum, loctesterr, lst, true, 3);
        InsertAtBack(loctestnum, loctesterr, lst, true, 7);

        RemoveFromBack(loctestnum, loctesterr, lst, true);
        RemoveFromBack(loctestnum, loctesterr, lst, true);
        RemoveFromBack(loctestnum, loctesterr, lst, true);
        EmptyContainerTest(loctestnum, loctesterr, lst);
        InsertAtFront(loctestnum, loctesterr, lst, true, 4); // clearing with removefromback
        InsertAtFront(loctestnum, loctesterr, lst, true, 3);
        InsertAtBack(loctestnum, loctesterr, lst, true, 7);

        BackNRemove(loctestnum, loctesterr, lst, true, 7);
        BackNRemove(loctestnum, loctesterr, lst, true, 4);
        BackNRemove(loctestnum, loctesterr, lst, true, 3);
        EmptyContainerTest(loctestnum, loctesterr, lst);
        InsertAtFront(loctestnum, loctesterr, lst, true, 4); // clearing with backnremove
        InsertAtFront(loctestnum, loctesterr, lst, true, 3);
        InsertAtBack(loctestnum, loctesterr, lst, true, 7);

        FrontNRemove(loctestnum, loctesterr, lst, true, 3);
        FrontNRemove(loctestnum, loctesterr, lst, true, 4);
        FrontNRemove(loctestnum, loctesterr, lst, true, 7);
        EmptyContainerTest(loctestnum, loctesterr, lst);
        InsertAtFront(loctestnum, loctesterr, lst, true, 4);// clearing with frontnremove
        InsertAtFront(loctestnum, loctesterr, lst, true, 3);
        InsertAtBack(loctestnum, loctesterr, lst, true, 7);

        lst.Clear();
        EmptyContainerTest(loctestnum, loctesterr, lst);
        InsertAtFront(loctestnum, loctesterr, lst, true, 4);// clearing with clear
        InsertAtFront(loctestnum, loctesterr, lst, true, 3);
        InsertAtBack(loctestnum, loctesterr, lst, true, 7);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    template <typename Data>
    void CopyAndMoveListTest(uint& testnum, uint& testerr, lasd::List<Data> lst)
    {
        uint loctestnum = 0, loctesterr = 0;

        lasd::List<Data> coplst(lst);
        EqualList(loctestnum, loctesterr, lst, coplst, true);

        lasd::List<Data> movelst(move(coplst));
        EqualList(loctestnum, loctesterr, lst, movelst, true);

        Empty(loctestnum, loctesterr, coplst, true);
        EqualList(loctestnum, loctesterr, lst, coplst, false);

        lasd::List<Data> lst2;
        lst2 = lst;
        EqualList(loctestnum, loctesterr, lst, lst2, true);

        lst2.Clear();

        lst2 = move(movelst);
        EqualList(loctestnum, loctesterr, lst, lst2, true);

        Empty(loctestnum, loctesterr, movelst, true);
        EqualList(loctestnum, loctesterr, lst, movelst, false);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void ContainerConstructorListIntTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;

        lasd::Vector<int> vec;

        lasd::List<int> emptylst(vec);
        EmptyContainerTest(loctestnum, loctesterr, emptylst);

        vec = lasd::Vector<int>(5);

        vec[0] = 5;
        vec[1] = 0;
        vec[2] = -6;
        vec[3] = 6;
        vec[4] = 5;

        lasd::List<int> lst1(vec);
        EqualLinear(loctestnum, loctesterr, lst1, vec, true);

        lasd::List<int> lst2(move(vec));
        EqualLinear(loctestnum, loctesterr, lst1, lst2, true);

        NonEqualLinear(loctestnum, loctesterr, lst1, vec, true);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void ContainerConstructorListStringTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;

        lasd::Vector<string> vec;

        vec = lasd::Vector<string>(5);

        vec[0] = string("!");
        vec[1] = string("@");
        vec[2] = string("^");
        vec[3] = string("*");
        vec[4] = string("#");

        lasd::List<string> lst1(vec);
        EqualLinear(loctestnum, loctesterr, lst1, vec, true);

        lasd::List<string> lst2(move(vec));
        EqualLinear(loctestnum, loctesterr, lst1, lst2, true);

        NonEqualLinear(loctestnum, loctesterr, lst1, vec, true);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void myListIntTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        cout << endl << "Begin of myList<int> Test:" << endl; 
        try 
        {
            lasd::List<int> lst;
            cout << endl << "List<int>: testing different kind of empty lists" << endl;
            ListEdgeCases(loctestnum, loctesterr, lst);

            lst = lasd::List<int>();
            InsertAtBack(loctestnum, loctesterr, lst, true, 4);
            InsertAtBack(loctestnum, loctesterr, lst, true, 3);
            InsertAtBack(loctestnum, loctesterr, lst, true, 0);
            InsertAtBack(loctestnum, loctesterr, lst, true, 4);
            InsertAtBack(loctestnum, loctesterr, lst, true, -6);

            cout << endl << "List<int>: testing generic functions" << endl;
            ContainerIntTest(loctestnum, loctesterr, lst);

            cout << endl << "List<int>: testing Copy and Move assignments and constructors" << endl;
            CopyAndMoveListTest(loctestnum, loctesterr, lst);

            cout << endl << "List<int>: testing constructors from containers" << endl;
            ContainerConstructorListIntTest(loctestnum, loctesterr);

            cout << endl << "List<int>: testing traverse, fold and map functions" << endl;
            TraverseAndFriendsIntTest(loctestnum, loctesterr, lst);
        }
        catch (...)
        {
            loctestnum++; loctesterr++;
            cout << endl << "Unmanaged error! " << endl;
        }
        cout << "End of myList<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }
    
    void myListStringTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        cout << endl << "Begin of myList<string> Test:" << endl; 
        try 
        {
            lasd::List<string> lst;
            
            InsertAtBack(loctestnum, loctesterr, lst, true, string("C"));
            InsertAtBack(loctestnum, loctesterr, lst, true, string("D"));
            InsertAtBack(loctestnum, loctesterr, lst, true, string("A"));
            InsertAtBack(loctestnum, loctesterr, lst, true, string("B"));
            InsertAtBack(loctestnum, loctesterr, lst, true, string("E"));

            cout << endl << "List<string>: testing generic functions" << endl;
            ContainerStringTest(loctestnum, loctesterr, lst);

            cout << endl << "List<string>: testing Copy and Move assignments and constructors" << endl;
            CopyAndMoveListTest(loctestnum, loctesterr, lst);

            cout << endl << "List<string>: testing constructors from containers" << endl;
            ContainerConstructorListStringTest(loctestnum, loctesterr);

            cout << endl << "List<string>: testing traverse and fold functions" << endl;
            TraverseAndFriendsStringTest(loctestnum, loctesterr, lst);
        }
        catch (...)
        {
            loctestnum++; loctesterr++;
            cout << endl << "Unmanaged error! " << endl;
        }
        cout << "End of myList<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }
}

#endif