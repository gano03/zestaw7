// stack.h 

#ifndef STACK_H
#define STACK_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert> 
#include <algorithm>   // assert()

template <typename T>
class MyStack {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    MyStack(int s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~MyStack() { delete [] tab; }
    MyStack(const MyStack& other)
    {
        tab = new T[other.msize];
        last = other.last;
        msize = other.msize;
        for (int i = 0; i < last; i++)
        {
            tab[i] = other.tab[i];
        }
    } // copy constructor
    // usage:   ArrayList<int> list2(list1);
    MyStack(MyStack&& other)
    {
        tab = new T[other.msize];
        msize = other.msize;
        last = other.last;
        other.last = 0;
        other.msize = 0;
        for (int i = 0; i < last; i++)
        {
            tab[i] = other.tab[i];
            other.tab[i] = 0;
        }
        delete [] other.tab;
    } // move constructor NIEOBOWIAZKOWE
    //
    MyStack& operator=(const MyStack& other)
    {
        if (this != &other)
        {
            tab = new T [other.msize];
            last = other.last;
            msize = other.msize;
            for (int i = 0; i < last; i++)
            {
                tab[i] = other.tab[i];
            }
            delete [] other.tab;
            return *this;
        }
        else
        {
            std::cout << "Nie skopiowano listy\n";
            return (MyStack&)other;
        }
    } // copy assignment operator, return *this
    // usage:   list2 = list1; NIEOBOWIAZKOWE
    MyStack& operator=(MyStack&& other)
    {   
        if (this != &other)
        {
            tab = new T [other.msize];
            last = other.last;
            msize = other.msize;
            other.last = 0;
            other.msize = 0;
            for (int i = 0; i < last; i++)
            {
                tab[i] = other.tab[i];
                other.tab[i] = 0;
            }
            delete [] other.tab;
        }
        return *this;
    } // move assignment operator, return *this
    // usage:   list2 = std::move(list1);
    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    int size() const { return last; } // liczba elementow na liscie
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow
    void push(const T& item)
    {
        if (last == msize)
        {
            std::cout << "Kolejka jest pelna\n";
        }
        else
        {
            tab[last] = item;
            last++;
        }
    } 
    T& top()
    {
        if (last == 0)
        {
            std::cout << "Error, lista jest pusta\n";
            return tab[-1];
        }
        else
        {
            return tab[last-1];
        }
    } // zwraca koniec, nie usuwa, error dla pustej listy
    void pop()
    {
        if (last == 0)
        {
            std::cout << "Error, lista jest pusta\n";
        }
        else
        {
            tab[last-1] = 0;
        }
        last--;
    } // usuwa koniec, error dla pustej listy
    void clear()
    {
        for (int i = 0; i < last; i++)
        {
            tab[i] = 0;
        }
    } // czyszczenie listy z elementow
    void display()
    {
        for (int i = 0; i < last; i++)
        {
            std::cout << tab[i] << " ";
            if (i == last-1)
            {
                std::cout << "\n";
            }
        }
    }
    void reverse()
    {
        T pom[last];
        for (int i = 0; i < last; i++)
        {
            pom[i] = tab[i];
        }
        for (int i = 0; i < last; i++)
        {
            tab[i] = pom[last-1-i];
        }
    } // odwracanie kolejnosci
    void sort()
    {
        for (int i = 0; i < last; i++)
        {
            for (int j = 0; j < last; j++)
            {
                if (tab[j-1] > tab[j])
                {
                    std::swap (tab[j-1], tab[j]);
                }
            }
        }
    } // sortowanie listy
    T& operator[](int pos)
    {
        if (last == msize)
        {
            std::cout << "Kolejka jest pelna\n";
            return tab[-1];
        }
        if (pos > last)
        {
            std::cout << "Niedozwolona pozycja\n";
            return tab[-1];
        }
        else
        {
            if(pos == last){
                last++;
                return tab[pos];
            }
            else    
                return tab[pos];
        }
    } // podstawienie L[pos]=item
    const T& operator[](int pos) const
    {
        return tab[pos];
    } // odczyt L[pos]
    void erase(int pos)
    {
        for (int i = pos; i < last-1; i++ )
        {
            tab[i] = tab[i+1];
        }
        last--;
    } // usuniecie elementu na pozycji pos
    int index(const T& item)
    {
        for (int i = 0; i < last; i++)
        {
            if (tab[i] == item)
            {
                return i;
            }
        }
        return -1;
    } // jaki index na liscie (-1 gdy nie ma)
    void insert(int pos, const T& item)
    {
        if (pos > last+1)
        {
            std::cout << "Error, niedozwolona pozycja\n";
            return;
        }
        for (int i = last; i >=pos-1 ; i--)
        {
            tab[i] = tab[i-1];
        }
        tab[(pos-1)] = item;
        last++;
    } // inserts item before pos
    void insert(int pos, T&& item)
    {
        if (pos > last+1)
        {
            std::cout << "Error, niedozwolona pozycja\n";
            return;
        }
        if (pos == size())
        {
            tab[last] = item;
            last++;
            return;
        }
        for (int i = last; i >=pos-1 ; i--)
        {
            if (i == 0)
                {
                    tab[0] = item;
                    last++;
                    return;
                }
            tab[i] = tab[i-1];
        }
        tab[(pos-1)] = item;
        last++;
   
    } // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
    friend std::ostream& operator<<(std::ostream& os, const MyStack& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
    int retlast(void)
    {
        return last;
    }
};

#endif

// EOF