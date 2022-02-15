#include <iostream>
using namespace std;
#include "list.h"

int main()
{
    cout << "#########################################\n";
    cout << "###  DOUBLE-LINKED LIST METHODS TEST  ###\n";
    cout << "#########################################\n\n";
    List NewList;
    for (unsigned i = 1; i < 5; i++)
    {
        NewList.push_back(i * i);
        NewList.push_front(i * i);
    }
    cout << "Pushing i*i elements in two sides 4 times:\n" << NewList << "\n\n";
    NewList.insert(0, 4);
    cout << "Inserting a zero in the middle:\n" << NewList << "\n\n";
    for (unsigned i = 0; i < NewList.get_size(); i+=2)
    {
        NewList.remove(i);
    }
    cout << "Removing every second element from 0 to list size (relatively):\n" << NewList << "\nFourth element now is " << NewList.at(3) << "\n\n";

    List otherList;
    for (unsigned i = 0; i < 4; i++)
    {
        otherList.push_back();
    }
    cout << "Creating new list of four zeros:\n" << otherList << "\n\n";
    for (unsigned i = 0; i < 4; i++)
    {
        otherList.set(i + 1, i);
    }
    cout << "Setting every element to a natural number sequentially:\n" << otherList << "\n\n";
    cout << "Pushing these two lists:\n" << otherList << " + " << NewList << " = ";
    NewList.push_front(otherList);
    cout << NewList << "\n\n";

    NewList.clear();
    cout << "Clearing the resulting list...\n\n";
    try
    {
        cout << "Trying to pop an element out of the back...\n";
        NewList.pop_back();
    }
    catch (logic_error exception)
    {
        cout << "\n[!] Exception caught: " << exception.what() << "\n\n";
    }
    cout << "Test: " << NewList << " (checkmark)\n\n";
    cout << "Checking if the pushed list is still accessible:\n" << otherList << " (checkmark)\n";
}
