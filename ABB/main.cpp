#include <iostream>
#include "AVL.h"

using namespace std;
void mostrarMenu();

int main()
{
    int opcion;
    struct nodo* root = nullptr;
    root = insertar(root, 50);
    insertar(root, 30);
    insertar(root, 20);
    insertar(root, 40);
    insertar(root, 70);
    insertar(root, 60);
    insertar(root, 80);


    int key = 6;

    if (buscar(root, key) == nullptr)
        cout << key << " No Encontrado" << endl;
    else
        cout << key << " Encontrado" << endl;

    key = 60;

    if (buscar(root, key) == nullptr)
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

