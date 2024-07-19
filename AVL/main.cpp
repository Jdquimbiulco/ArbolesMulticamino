#include <iostream>
#include <windows.h>
#include "AVL.h"

using namespace std;

void mostrarMenu();


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	
    int opcion;
    struct nodo* raiz = nullptr;
    int valor;
   
    do {
        mostrarMenu();
        cin >> opcion;
        switch(opcion) {
            case 1:
                cout << "Ingrese el valor a insertar: ";
                cin >> valor;
                raiz = insertar(raiz, valor);
                cout << "Valor insertado correctamente." << endl;
                break;
            case 2:
                if (raiz == nullptr) {
                    cout << "El árbol está vacío." << endl;
                } else {
                    cout << "Árbol AVL:" << endl;
                    imprimirArbol(raiz);
                }
                break;
            case 3:
                cout << "Ingrese el valor a buscar: ";
                cin >> valor;
                if (buscar(raiz, valor) != nullptr) {
                    cout << "El valor " << valor << " se encuentra en el árbol." << endl;
                } else {
                    cout << "El valor " << valor << " no se encuentra en el árbol." << endl;
                }
                break;
            case 4:
                cout << "Ingrese el valor a eliminar: ";
                cin >> valor;
                raiz = eliminar(raiz, valor);
                cout << "Valor eliminado (si existía)." << endl;
                break;
            case 5:
                if (raiz == nullptr) {
                    cout << "El árbol está vacío." << endl;
                } else {
                    cout << "Árbol AVL (representación gráfica):" << endl;
                    imprimirArbol(raiz);
                }
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
        }
        cout << endl;
    } while(opcion != 6);
    
    return 0;
}

void mostrarMenu() {
    cout << "\n/////ARBOLES MULTICAMINO/////" << endl;
    cout << "1. Creacion / Insercion" << endl;
    cout << "2. Recorridos sistematicos" << endl;
    cout << "3. Busqueda" << endl;
    cout << "4. Eliminacion" << endl;
    cout << "5. Arbol grafico" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opcion: " <<endl;
}

