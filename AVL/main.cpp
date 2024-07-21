#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <sstream>
#include "AVL.h"

using namespace std;

const char TECLA_SALIDA = 'q';

void mostrarMenu();
int obtenerEntradaEntero();
bool teclaPresionada(char tecla);

int main()
{
    SetConsoleOutputCP(CP_UTF8); 

    int opcion;
    struct nodo* raiz = nullptr; 
    int valor = 0;

    do {
        mostrarMenu();
        cin >> opcion;

        // Manejo de errores para entrada de datos inválidos
        if(cin.fail()) {
            cin.clear(); // Limpia el estado de error
            cin.ignore(10000, '\n'); // Ignora el input restante
            cout << "Entrada inválida. Intente nuevamente." << endl;
            continue;
        }

        switch(opcion) {
            case 1:
                {
                    while (true) {
                        cout << "Ingrese el valor a insertar (o presione 'q' para salir): ";
                        valor = obtenerEntradaEntero(); 

                        if (valor == -1) {
                            cout << "\nSaliendo del modo de inserción..." << endl;
                            break; 
                        } else {
                            raiz = insertar(raiz, valor);
                            cout << "\nValor insertado correctamente." << endl;
                            imprimirArbol(raiz); 
                        }
                    }
                }
                break;
            case 2:
     
                if (raiz == nullptr) {
                    cout << "El árbol está vacío." << endl;
                } else {
                    int tipoRecorrido;
                    cout << "Seleccione el tipo de recorrido:\n1. PreOrden\n2. InOrden\n3. PostOrden\n";
                    cin >> tipoRecorrido;
                    cout << "Recorrido seleccionado:" << endl;
                    switch (tipoRecorrido) {
                        case 1:
                            preOrden(raiz); 
                            break;
                        case 2:
                            inOrden(raiz); 
                            break;
                        case 3:
                            postOrden(raiz); 
                            break;
                        default:
                            cout << "Tipo de recorrido inválido." << endl;
                            break;
                    }
                    cout << endl;
                }
                break;
            
            case 3:
			    if (raiz == nullptr) {
			        cout << "El árbol está vacío." << endl;
			    } else {
			        int tipoBusqueda;
			        cout << "Seleccione el tipo de búsqueda:\n";
			        cout << "1. Profundidad (DFS)\n";
			        cout << "2. Anchura (BFS)\n";
			        tipoBusqueda = obtenerEntradaEntero();
			
			        int clave;
			        cout << "Ingrese el valor a buscar: ";
			        cin >> clave;
			
			        ResultadoBusqueda resultado;
			        string tipoRecorrido;
			
			        switch (tipoBusqueda) {
			            case 1:
			                resultado = dfs(raiz, clave);
			                tipoRecorrido = "DFS";
			                break;
			            case 2:
			                resultado = bfs(raiz, clave);
			                tipoRecorrido = "BFS";
			                break;
			            default:
			                cout << "Tipo de búsqueda inválido. Por favor seleccione 1 o 2." << endl;
			                break;
			        }
			
			        if (tipoBusqueda == 1 || tipoBusqueda == 2) {
			            if (resultado.encontrado) {
			                cout << "El valor " << clave << " fue encontrado en el árbol usando " << tipoRecorrido << ".\n";
			                cout << "Nivel: " << resultado.nivel << "\n";
			                cout << "Posición: " << resultado.posicion << "\n";
			            } else {
			                cout << "El valor " << clave << " no fue encontrado en el árbol usando " << tipoRecorrido << ".\n";
			            }
			        }
			    }
			    break;

            case 4:
            	
                cout << "Ingrese el valor a eliminar: ";
                cin >> valor;
                raiz = eliminar(raiz, valor); // Elimina el valor del árbol
                cout << "Valor eliminado" << endl;
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
    cout << "\n/////ARBOLES AVL/////" << endl;
    cout << "----------------------" << endl;
    cout << "1. Inserción" << endl;
    cout << "2. Recorridos sistemáticos" << endl;
    cout << "3. Búsqueda" << endl;
    cout << "4. Eliminación" << endl;
    cout << "5. Árbol gráfico" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opción: " << endl;
}

int obtenerEntradaEntero() {
    string entrada;
    char ch;

    while (true) {
        if (_kbhit()) {
            ch = _getch(); // Captura el carácter presionado

            if (ch == TECLA_SALIDA) {
                return -1; // Retorna -1 para indicar que se presionó la tecla de salida
            }

            if (isdigit(ch) || ch == '-' || ch == '+') {
                entrada += ch; // Agrega el carácter a la cadena de entrada
                cout << ch; // Muestra el carácter en la consola
            } else if (ch == '\r') { // Enter
                if (!entrada.empty()) {
                    int valor;
                    istringstream(entrada) >> valor; // Convierte la cadena a entero
                    entrada.clear(); // Limpia la cadena de entrada
                    return valor;
                }
            } else if (ch == '\b') { // Backspace
                if (!entrada.empty()) {
                    entrada.pop_back(); // Elimina el último carácter de la cadena
                    cout << "\b \b"; // Borra el carácter en la consola
                }
            } else {
                cout << "\nEntrada inválida. Intente nuevamente." << endl;
                entrada.clear(); 
            }
        }
    }
} 


