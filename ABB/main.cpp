#include <iostream>
#include "ABB.h"

using namespace std;
void mostrarMenu();

int main()
{
    int opcion;
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


    do{
        mostrarMenu();
        cin>>opcion;

        switch(opcion){
            case 1:

            break;
            case 2:

            break;

            case 3:
            break;

            case 4:
            break;

            case 5:
            case 6:
                cout<<"Saliendo del programa..."<< endl;
                break;
            default:
                cout<<"Opcion invalida. Intente nuevamente."<< endl;
                break;
        }
    }while(opcion != 6);
    return 0;
}


void mostrarMenu() {
    cout<< "/////ARBOLES MULTICAMINO/////"<< endl;
    cout<< "1.Creacion / Insercion"<<endl;
    cout<< "2.Recorridos sistematicos"<<endl;
    cout<< "3.Busqueda"<<endl;
    cout<< "4.Eliminacion"<<endl;
    cout<< "5.Arbol grafico"<<endl;
    cout<< "6.Salir"<<endl;
    cout<< "Seleccione una opcion: ";
}

