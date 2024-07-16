#include <iostream>
#include "ABB.h"

using namespace std;

int main()
{
    struct node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
 
 
    int key = 6;
 
    if (search(root, key) == nullptr)
        cout << key << " No Encontrado" << endl;
    else
        cout << key << " Encontrado" << endl;
 
    key = 60;
    
    if (search(root, key) == nullptr)
        cout << key << " No Encomtrado" << endl;
    else
        cout << key << " Econtrado" << endl;
    return 0;
}
