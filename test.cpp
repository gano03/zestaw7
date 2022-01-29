#include "stack.h"
#include <iostream>
#include <cstdlib>

int main ()
{   
    MyStack<int> obj;
    MyStack<int> L;
    obj.top();
    
    std::cout << "Empty " << obj.empty() <<"\n";
    obj[0] = 1;
    obj[1] = 3;
    obj[2] = 7;
    obj.insert(1,10);
    obj.insert(3,11);
    std::cout << "Empty " << obj.empty() <<"\n";

    std::cout << obj.index(10) <<"\n";
    std::cout << obj.index(1) <<"\n";
    std::cout << obj.index(3) <<"\n";
    std::cout << obj.index(7) <<"\n";

    obj.push(12);
    obj.push(14);
    std::cout << obj.top() << "\n";

    L = obj;
    L.display();

    L.erase(2);
    std::cout << "last to " <<L.retlast() << "\n";
    L.display();

    std::cout << "last to " <<L.retlast() << "\n";
    L.reverse();
    L.display();
    L.reverse();
    L.display();

    std::cout << "Rozmiar listy to " <<L.size() <<"\n";

    L.pop();
    L.pop();
    L.display();

    L.sort();
    L.display();

    L.clear();
    L.display();
    obj.display();

    return 0;
}