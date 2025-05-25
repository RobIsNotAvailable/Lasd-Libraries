#ifndef MYSET_HPP
#define MYSET_HPP

#include "../../zlasdtest/container/dictionary.hpp"
#include "../../zlasdtest/set/set.hpp"

#include "../../set/lst/setlst.hpp"
#include "../../set/vec/setvec.hpp"

#include "./container.hpp"

using namespace std;

namespace daje
{
    void SetEdgeCases(uint& testnum, uint& testerr, lasd::Set<int>& set) // ensures that the different functions work with few elements  
    {                                                                     // and keep the set serviceable after removing the last element in different ways
        uint loctestnum = 0, loctesterr = 0;

        EmptyContainerTest(loctestnum, loctesterr, set); //originally empty

        InsertC(loctestnum, loctesterr, set, 1);
        RemoveMin(loctestnum, loctesterr, set, true);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with remove min

        InsertC(loctestnum, loctesterr, set, 2);
        RemoveMax(loctestnum, loctesterr, set, true);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with remove max

        InsertC(loctestnum, loctesterr, set, 3);
        MinNRemove(loctestnum, loctesterr, set, true, 3);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with min n remove

        InsertC(loctestnum, loctesterr, set, 4);
        MaxNRemove(loctestnum, loctesterr, set, true, 4);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with max n remove

        InsertC(loctestnum, loctesterr, set, 5);
        RemovePredecessor(loctestnum, loctesterr, set, true, 9);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with remove pred

        InsertC(loctestnum, loctesterr, set, 6);
        RemoveSuccessor(loctestnum, loctesterr, set, true, 5);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with remove succ

        InsertC(loctestnum, loctesterr, set, 7);
        PredecessorNRemove(loctestnum, loctesterr, set, true, 9, 7);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with pred n remove

        InsertC(loctestnum, loctesterr, set, 8);
        SuccessorNRemove(loctestnum, loctesterr, set, true, 5, 8);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with succ n remove

        InsertC(loctestnum, loctesterr, set, 34);
        Remove(loctestnum, loctesterr, set, true, 34);
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with remove

        InsertC(loctestnum, loctesterr, set, 7);
        InsertC(loctestnum, loctesterr, set, 8);
        set.Clear();
        EmptyContainerTest(loctestnum, loctesterr, set); // emptied with clear
        
        testnum += loctestnum;
        testerr += loctesterr;
    }
    
    void ContainerConstructorSetVecIntTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        lasd::List<int> lst;

        lasd::SetVec<int> emptyset(lst);
        EmptyContainerTest(loctestnum, loctesterr, emptyset);

        lst.InsertAtBack(6);
        lst.InsertAtBack(8);
        lst.InsertAtBack(-9);
        lst.InsertAtBack(3);
        lst.InsertAtBack(8);

        lasd::List<int> checklst;

        checklst.InsertAtBack(-9);
        checklst.InsertAtBack(3);
        checklst.InsertAtBack(6);
        checklst.InsertAtBack(8);

        lasd::SetVec<int> set1(lst);
        EqualLinear(loctestnum, loctesterr, set1, checklst, true);

        lasd::SetVec<int> set2(move(lst));
        EqualLinear(loctestnum, loctesterr, set2, checklst, true);

        NonEqualLinear(loctestnum, loctesterr, set1, lst, true);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void ContainerConstructorSetListStringTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        lasd::List<string> lst;

        lst.InsertAtBack(string("F"));
        lst.InsertAtBack(string("B"));
        lst.InsertAtBack(string("P"));
        lst.InsertAtBack(string("L"));
        lst.InsertAtBack(string("B"));

        lasd::List<string> checklst;

        checklst.InsertAtBack(string("B"));
        checklst.InsertAtBack(string("F"));
        checklst.InsertAtBack(string("L"));
        checklst.InsertAtBack(string("P"));

        lasd::SetLst<string> set1(lst);
        EqualLinear(loctestnum, loctesterr, set1, checklst, true);

        lasd::SetLst<string> set2(move(lst));
        EqualLinear(loctestnum, loctesterr, set2, checklst, true);

        NonEqualLinear(loctestnum, loctesterr, set1, lst, true);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void ContainerConstructorSetListIntTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        lasd::List<int> lst;

        lasd::SetLst<int> emptyset(lst);
        EmptyContainerTest(loctestnum, loctesterr, emptyset);

        lst.InsertAtBack(6);
        lst.InsertAtBack(8);
        lst.InsertAtBack(-9);
        lst.InsertAtBack(3);
        lst.InsertAtBack(8);

        lasd::List<int> checklst;

        checklst.InsertAtBack(-9);
        checklst.InsertAtBack(3);
        checklst.InsertAtBack(6);
        checklst.InsertAtBack(8);

        lasd::SetLst<int> set1(lst);
        EqualLinear(loctestnum, loctesterr, set1, checklst, true);

        lasd::SetLst<int> set2(move(lst));
        EqualLinear(loctestnum, loctesterr, set2, checklst, true);

        NonEqualLinear(loctestnum, loctesterr, set1, lst, true);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void ContainerConstructorSetVecStringTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;
        lasd::List<string> lst;

        lst.InsertAtBack(string("F"));
        lst.InsertAtBack(string("B"));
        lst.InsertAtBack(string("P"));
        lst.InsertAtBack(string("L"));
        lst.InsertAtBack(string("B"));

        lasd::List<string> checklst;

        checklst.InsertAtBack(string("B"));
        checklst.InsertAtBack(string("F"));
        checklst.InsertAtBack(string("L"));
        checklst.InsertAtBack(string("P"));

        lasd::SetVec<string> set1(lst);
        EqualLinear(loctestnum, loctesterr, set1, checklst, true);

        lasd::SetVec<string> set2(move(lst));
        EqualLinear(loctestnum, loctesterr, set2, checklst, true);

        NonEqualLinear(loctestnum, loctesterr, set1, lst, true);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void SetContentIntTest(uint& testnum, uint& testerr, lasd::Set<int>& set)
    {
        uint loctestnum = 0, loctesterr = 0;

        Size(loctestnum, loctesterr, set, true, 6);

        GetAt(loctestnum, loctesterr, set, true, 0, -6);
        GetAt(loctestnum, loctesterr, set, true, 1, -3);
        GetAt(loctestnum, loctesterr, set, true, 2, 0);
        GetAt(loctestnum, loctesterr, set, true, 3, 3);
        GetAt(loctestnum, loctesterr, set, true, 4, 4);
        GetAt(loctestnum, loctesterr, set, true, 5, 7);// checking if the values are correct

        GetAt(loctestnum, loctesterr, set, false, -1, 5);
        GetAt(loctestnum, loctesterr, set, false, 9, 4); // getting out of bounds

        Exists(loctestnum, loctesterr, set, true, -6);//searching for existing value
        Exists(loctestnum, loctesterr, set, false, -4);//searching for non existing value

        Remove(loctestnum, loctesterr, set, true, -6);
        Remove(loctestnum, loctesterr, set, true, 7);
        Remove(loctestnum, loctesterr, set, false, 100);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void SetContentStringTest(uint& testnum, uint& testerr, lasd::Set<string>& set)
    {
        uint loctestnum = 0, loctesterr = 0;

        Size(loctestnum, loctesterr, set, true, 6);

        GetAt(loctestnum, loctesterr, set, true, 0, string("A"));
        GetAt(loctestnum, loctesterr, set, true, 1, string("B"));
        GetAt(loctestnum, loctesterr, set, true, 2, string("D"));
        GetAt(loctestnum, loctesterr, set, true, 3, string("J"));
        GetAt(loctestnum, loctesterr, set, true, 4, string("T"));
        GetAt(loctestnum, loctesterr, set, true, 5, string("Y"));// checking if the values are correct

        GetAt(loctestnum, loctesterr, set, false, -1, string("tanto è fuori"));
        GetAt(loctestnum, loctesterr, set, false, 9, string("tanto è fuori")); // getting out of bounds

        Exists(loctestnum, loctesterr, set, true, string("D"));//searching for existing value
        Exists(loctestnum, loctesterr, set, false, string("tanto non c'è"));//searching for non existing value

        testnum += loctestnum;
        testerr += loctesterr;
    }

    template <typename Data>
    void CopyAndMoveSetVecTest(uint& testnum, uint& testerr, lasd::SetVec<Data> set)
    {
        uint loctestnum = 0, loctesterr = 0;

        lasd::SetVec<Data> copset(set);
        EqualSetVec(loctestnum, loctesterr, set, copset, true);

        lasd::SetVec<Data> moveset(move(copset));
        EqualSetVec(loctestnum, loctesterr, set, moveset, true);

        Empty(loctestnum, loctesterr, copset, true);
        EqualSetVec(loctestnum, loctesterr, set, copset, false);
        
        lasd::SetVec<Data> set2;
        set2 = set;
        EqualSetVec(loctestnum, loctesterr, set, set2, true);

        set2.Clear();

        set2 = move(moveset);
        EqualSetVec(loctestnum, loctesterr, set, set2, true);
        
        Empty(loctestnum, loctesterr, moveset, true);
        EqualSetVec(loctestnum, loctesterr, set, moveset, false);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    template <typename Data>
    void CopyAndMoveSetListTest(uint& testnum, uint& testerr, lasd::SetLst<Data> set)
    {
        uint loctestnum = 0, loctesterr = 0;

        lasd::SetLst<Data> copset(set);
        EqualSetLst(loctestnum, loctesterr, set, copset, true);

        lasd::SetLst<Data> moveset(move(copset));
        EqualSetLst(loctestnum, loctesterr, set, moveset, true);

        Empty(loctestnum, loctesterr, copset, true);
        EqualSetLst(loctestnum, loctesterr, set, copset, false);
        
        lasd::SetLst<Data> set2;
        set2 = set;
        EqualSetLst(loctestnum, loctesterr, set, set2, true);

        set2.Clear();

        set2 = move(moveset);
        EqualSetLst(loctestnum, loctesterr, set, set2, true);
        
        Empty(loctestnum, loctesterr, moveset, true);
        EqualSetLst(loctestnum, loctesterr, set, moveset, false);

        testnum += loctestnum;
        testerr += loctesterr;
    }
    
    void Reset(lasd::Set<int>& set)
    {
        set.Clear();
        set.Insert(4);
        set.Insert(3);
        set.Insert(0);
        set.Insert(4);
        set.Insert(-6);
        set.Insert(7);
        set.Insert(-3);
    }

    void SetPredecessorSuccessorTest(uint& testnum, uint& testerr, lasd::Set<int>& set)
    {
        uint loctestnum = 0, loctesterr = 0; 

        Reset(set);
        
        Predecessor(loctestnum, loctesterr, set, false, -8, 1);        //predecessor di testa in tre varianti
        RemovePredecessor(loctestnum, loctesterr, set, false, -8);
        PredecessorNRemove(loctestnum, loctesterr, set, false, -8, 1);

        Successor(loctestnum, loctesterr, set, false, 50, 1);        //successor di coda in tre varianti
        RemoveSuccessor(loctestnum, loctesterr, set, false, 50);
        SuccessorNRemove(loctestnum, loctesterr, set, false, 50, 1);
        
        Predecessor(loctestnum, loctesterr, set, true, 0, -3);        //predecessor di un presente di tre varianti
        RemovePredecessor(loctestnum, loctesterr, set, true, 0);
        PredecessorNRemove(loctestnum, loctesterr, set, true, 0, -6);

        Successor(loctestnum, loctesterr, set, true, 0, 3);        //successor di un presente di tre varianti
        RemoveSuccessor(loctestnum, loctesterr, set, true, 0);
        SuccessorNRemove(loctestnum, loctesterr, set, true, 0, 4);
        
        Reset(set);       

        Predecessor(loctestnum, loctesterr, set, true, -1, -3);        //predecessor di un assente di tre varianti
        RemovePredecessor(loctestnum, loctesterr, set, true, -1);
        PredecessorNRemove(loctestnum, loctesterr, set, true, -1, -6);

        Successor(loctestnum, loctesterr, set, true, 1, 3);        //successor di un assente di tre varianti
        RemoveSuccessor(loctestnum, loctesterr, set, true, 1);
        SuccessorNRemove(loctestnum, loctesterr, set, true, 1, 4);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void SetPopulate(uint& testnum, uint& testerr, lasd::Set<int>& set)
    {
        uint loctestnum = 0, loctesterr = 0; 

        set.Clear();
        InsertC(loctestnum, loctesterr, set, true, 4);
        InsertC(loctestnum, loctesterr, set, true, 3);
        InsertC(loctestnum, loctesterr, set, true, 0);
        InsertC(loctestnum, loctesterr, set, false, 4);
        InsertC(loctestnum, loctesterr, set, true, -6);
        InsertC(loctestnum, loctesterr, set, true, 7);
        InsertC(loctestnum, loctesterr, set, true, -3);

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void SetPopulate(uint& testnum, uint& testerr, lasd::Set<string>& set)
    {
        uint loctestnum = 0, loctesterr = 0; 

        set.Clear();
        InsertC(loctestnum, loctesterr, set, true, string("T"));
        InsertC(loctestnum, loctesterr, set, true, string("J"));
        InsertC(loctestnum, loctesterr, set, true, string("D"));
        InsertC(loctestnum, loctesterr, set, false, string("T"));
        InsertC(loctestnum, loctesterr, set, true, string("A"));
        InsertC(loctestnum, loctesterr, set, true, string("Y"));
        InsertC(loctestnum, loctesterr, set, true, string("B"));

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void mySetIntTest(uint& testnum, uint& testerr, lasd::Set<int>& set)
    {
        uint loctestnum = 0, loctesterr = 0;
        try 
        {
            cout << endl << "Set<int>: testing different kind of empty sets" << endl;
            SetEdgeCases(loctestnum, loctesterr, set);

            cout << endl << "Set<int>: testing generic functions" << endl;
            SetPopulate(loctestnum, loctesterr, set);
            SetContentIntTest(loctestnum, loctesterr, set);

            cout << endl << "Set<int>: testing predecessor, successor and variants" << endl;
            SetPredecessorSuccessorTest(loctestnum, loctesterr, set);

            cout << endl << "Set<int>: testing traverse, fold and map functions" << endl;
            Reset(set);
            TraverseAndFriendsIntTest(loctestnum, loctesterr, set);
        }
        catch (...)
        {
            loctestnum++; loctesterr++;
            cout << endl << "Unmanaged error! " << endl;
        }

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void mySetIntTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;   

        cout << endl << "Begin of mySet<int> Test:" << endl; 

        lasd::SetLst<int> setlst;
        mySetIntTest(loctestnum, loctesterr, setlst);

        cout << endl << "SetList<int>: testing constructors from containers" << endl;
        ContainerConstructorSetListIntTest(loctestnum, loctesterr);

        cout << endl << "SetList<int>: testing Copy and Move assignments and constructors" << endl;
        SetPopulate(loctestnum, loctesterr, setlst);
        CopyAndMoveSetListTest(loctestnum, loctesterr, setlst);

        lasd::SetVec<int> setvec;
        mySetIntTest(loctestnum, loctesterr, setvec);

        cout << endl << "SetVec<int>: testing constructors from containers" << endl;
        ContainerConstructorSetVecIntTest(loctestnum, loctesterr);

        cout << endl << "SetVec<int>: testing Copy and Move assignments and constructors" << endl;
        SetPopulate(loctestnum, loctesterr, setvec);
        CopyAndMoveSetVecTest(loctestnum, loctesterr, setvec);

        cout << "End of mySet<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void mySetStringTest(uint& testnum, uint& testerr, lasd::Set<string>& set)
    {
        uint loctestnum = 0, loctesterr = 0;
        try 
        {
            cout << endl << "Set<int>: testing generic functions" << endl;
            SetPopulate(loctestnum, loctesterr, set);
            SetContentStringTest(loctestnum, loctesterr, set);

            cout << endl << "Set<int>: testing traverse, fold and map functions" << endl;
            TraverseAndFriendsStringTest(loctestnum, loctesterr, set);
        }
        catch (...)
        {
            loctestnum++; loctesterr++;
            cout << endl << "Unmanaged error! " << endl;
        }

        testnum += loctestnum;
        testerr += loctesterr;
    }

    void mySetStringTest(uint& testnum, uint& testerr)
    {
        uint loctestnum = 0, loctesterr = 0;   

        cout << endl << "Begin of mySet<string> Test:" << endl; 

        lasd::SetLst<string> setlst;
        mySetStringTest(loctestnum, loctesterr, setlst);

        cout << endl << "SetList<string>: testing constructors from containers" << endl;
        ContainerConstructorSetListStringTest(loctestnum, loctesterr);
        
        cout << endl << "SetList<string>: testing Copy and Move assignments and constructors" << endl;
        SetPopulate(loctestnum, loctesterr, setlst);
        CopyAndMoveSetListTest(loctestnum, loctesterr, setlst);

        lasd::SetVec<string> setvec;
        mySetStringTest(loctestnum, loctesterr, setvec);

        cout << endl << "SetVec<string>: testing constructors from containers" << endl;
        ContainerConstructorSetVecStringTest(loctestnum, loctesterr);

        cout << endl << "SetVec<string>: testing Copy and Move assignments and constructors" << endl;
        SetPopulate(loctestnum, loctesterr, setvec);
        CopyAndMoveSetVecTest(loctestnum, loctesterr, setvec);

        cout << "End of mySet<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

        testnum += loctestnum;
        testerr += loctesterr;
    }
}
#endif