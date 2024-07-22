//Juan Quimbiulco & Gabriel Murillo
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
void mostrarGrafico(nodo* raiz);
//Funcion para mostrar el arbol
void DrawAVL(HDC hdc, nodo* nodo, int x, int y, int offset);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int opcion;
    struct nodo* raiz = nullptr;
    int valor = 0;

    do {
        mostrarMenu();
        cin >> opcion;

        // validacion
        if(cin.fail()) {
            cin.clear(); // Limpia el estado de error
            cin.ignore(10000, '\n'); // Ignora el input restante
            cout << "Entrada invalida. Intente nuevamente." << endl;
            continue;
        }

        switch(opcion) {
            case 1:
                {
                    while (true) {
                        cout << "Ingrese el valor a insertar (o presione 'q' para salir): ";
                        valor = obtenerEntradaEntero();

                        if (valor == -1) {
                            cout << "\nSaliendo del modo de insercion..." << endl;
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
                    cout << "El arbol esta vacio." << endl;
                } else {
                    int tipoRecorrido;
                    cout << "\nSeleccione el tipo de recorrido:\n1. PreOrden\n2. InOrden\n3. PostOrden\n";
                    cout <<"\nRecorrido ----> ";
                    cin >> tipoRecorrido;
                    cout << "Recorrido seleccionado:" << endl;
                    cout << endl;
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
                            cout << "Tipo de recorrido invalido." << endl;
                            break;
                    }
                    cout << endl;
                }
                break;

            case 3:
			    if (raiz == nullptr) {
			        cout << "El arbol está vacio." << endl;
			    } else {
			        int tipoBusqueda;
			        cout << "\nSeleccione el tipo de busqueda:\n";
			        cout << "1. Profundidad (DFS)\n";
			        cout << "2. Anchura (BFS)\n";
			        cout <<"Busqueda---->" ;
			        tipoBusqueda = obtenerEntradaEntero();

			        int clave;
			        cout << "\nIngrese el valor a buscar: ";
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
			                cout << "Tipo de busqueda invalido. Por favor seleccione 1 o 2." << endl;
			                break;
			        }

			        if (tipoBusqueda == 1 || tipoBusqueda == 2) {
			            if (resultado.encontrado) {
			                cout << "El valor " << clave << " fue encontrado en el arbol usando " << tipoRecorrido << ".\n";
			                cout << "Nivel: " << resultado.nivel << "\n";
			                cout << "Posicion: " << resultado.posicion << "\n";
			            } else {
			                cout << "El valor " << clave << " no fue encontrado en el arbol usando " << tipoRecorrido << ".\n";
			            }
			        }
			    }
			    break;

            case 4:
                imprimirArbol(raiz);
                cout << "\nIngrese el valor a eliminar: ";
                cin >> valor;
                raiz = eliminar(raiz, valor); // Elimina el valor del árbol
                cout << "Valor eliminado" << endl;
                imprimirArbol(raiz);
                break;

            case 5:

                if (raiz == nullptr) {
                    cout << "\nEl arbol esta vacio." << endl;
                } else {
                    cout << "Mostrando representacion grafica del arbol AVL..." << endl;
                    mostrarGrafico(raiz);
                }
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }
        cout << endl;
    } while(opcion != 6);

    return 0;
}

void mostrarMenu() {
    cout << "\n/////ARBOLES MULTICAMINO/////" << endl;
    cout << "-------------------------------" << endl;
    cout << "1. Insercion" << endl;
    cout << "2. Recorridos sistematicos" << endl;
    cout << "3. Busqueda" << endl;
    cout << "4. Eliminacion" << endl;
    cout << "5. Arbol grafico" << endl;
    cout << "6. Salir" << endl;
    cout << "-------------------------------" << endl;
    cout << "//////////////////////////////" << endl;
    cout << "\nSeleccione una opcion: " ;
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

void DrawAVL(HDC hdc, nodo* nodo, int x, int y, int offset) {
    if (nodo == nullptr) return;

    // Dibuja el nodo
    Ellipse(hdc, x - 15, y - 15, x + 15, y + 15);
    char clave[10];
    sprintf(clave, "%d", nodo->clave);
    TextOut(hdc, x - 10, y - 10, clave, strlen(clave));

    // Conexión con el hijo izquierdo
    if (nodo->izquierda != nullptr) {
        MoveToEx(hdc, x, y, nullptr);
        LineTo(hdc, x - offset, y + 50);
        DrawAVL(hdc, nodo->izquierda, x - offset, y + 50, offset / 2);
    }

    // Conexión con el hijo derecho
    if (nodo->derecha != nullptr) {
        MoveToEx(hdc, x, y, nullptr);
        LineTo(hdc, x + offset, y + 50);
        DrawAVL(hdc, nodo->derecha, x + offset, y + 50, offset / 2);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static nodo* raiz = nullptr;

    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Aquí dibujamos el árbol AVL
        RECT rect;
        GetClientRect(hwnd, &rect);
        DrawAVL(hdc, (nodo*)GetWindowLongPtr(hwnd, GWLP_USERDATA), rect.right / 2, 20, rect.right / 4);

        EndPaint(hwnd, &ps);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void mostrarGrafico(nodo* raiz) {
    const char CLASS_NAME[] = "AVLTreeWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Árbol AVL",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        GetModuleHandle(NULL),
        nullptr
    );

    if (hwnd == nullptr) {
        return;
    }

    // Asignar la raíz del árbol AVL a una variable estática
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)raiz);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}



