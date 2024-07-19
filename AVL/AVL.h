#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <string>

struct nodo {
    int clave;
    struct nodo *izquierda, *derecha;
    int altura;
};

void imprimirArbol(struct nodo* raiz, std::string prefijo = "", bool esIzquierdo = true) {
    if (raiz == nullptr) {
        return;
    }
    
    std::cout << prefijo;
    std::cout << (esIzquierdo ? );
    std::cout << raiz->clave << std::endl;
    
    imprimirArbol(raiz->derecha, prefijo + (esIzquierdo ? "¦   " : "    "), false);
    imprimirArbol(raiz->izquierda, prefijo + (esIzquierdo ? "¦   " : "    "), true);
}

int altura(struct nodo *N) {
    if (N == nullptr)
        return 0;
    return N->altura;
}

struct nodo* nuevoNodo(int clave) {
    struct nodo* nodo = new struct nodo;
    nodo->clave = clave;
    nodo->izquierda = nodo->derecha = nullptr;
    nodo->altura = 1; // nuevo nodo se añade al final del árbol
    return nodo;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct nodo* rotacionDerecha(struct nodo *y) {
    struct nodo *x = y->izquierda;
    struct nodo *T2 = x->derecha;
    // Realizar rotación
    x->derecha = y;
    y->izquierda = T2;
    // Actualizar alturas
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    // Devolver nueva raíz
    return x;
}

struct nodo* rotacionIzquierda(struct nodo *x) {
    struct nodo *y = x->derecha;
    struct nodo *T2 = y->izquierda;
    // Realizar rotación
    y->izquierda = x;
    x->derecha = T2;
    // Actualizar alturas
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    // Devolver nueva raíz
    return y;
}

// Obtener el factor de balanceo de un nodo N
int obtenerBalance(struct nodo *N) {
    if (N == nullptr)
        return 0;
    return altura(N->izquierda) - altura(N->derecha);
}

struct nodo* insertar(struct nodo* nodo, int clave) {
    // 1. Realizar la inserción normal 
    if (nodo == nullptr)
        return nuevoNodo(clave);
    if (clave < nodo->clave)
        nodo->izquierda = insertar(nodo->izquierda, clave);
    else if (clave > nodo->clave)
        nodo->derecha = insertar(nodo->derecha, clave);
    else // Las claves iguales no se permiten
        return nodo;
    // 2. Actualizar la altura del nodo ancestro
    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
    // 3. Obtener el factor de balanceo de este nodo ancestro para verificar si se desbalanceó
    int balance = obtenerBalance(nodo);
    // Si el nodo se desbalanceó, entonces hay 4 casos
    // Caso izquierda-izquierda
    if (balance > 1 && clave < nodo->izquierda->clave)
        return rotacionDerecha(nodo);
    // Caso derecha-derecha
    if (balance < -1 && clave > nodo->derecha->clave)
        return rotacionIzquierda(nodo);
    // Caso izquierda-derecha
    if (balance > 1 && clave > nodo->izquierda->clave) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    // Caso derecha-izquierda
    if (balance < -1 && clave < nodo->derecha->clave) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }
    // Devolver el puntero del nodo (sin cambios)
    return nodo;
}

struct nodo* buscar(struct nodo* raiz, int clave) {
    // Casos base: raiz es null o la clave está presente en la raiz
    if (raiz == nullptr || raiz->clave == clave)
        return raiz;
    // La clave es mayor que la clave de la raiz
    if (raiz->clave < clave)
        return buscar(raiz->derecha, clave);
    // La clave es menor que la clave de la raiz
    return buscar(raiz->izquierda, clave);
}

struct nodo* nodoConValorMinimo(struct nodo* nodo) {
    struct nodo* actual = nodo;
    while (actual->izquierda != nullptr)
        actual = actual->izquierda;
    return actual;
}

struct nodo* eliminar(struct nodo* raiz, int clave) {
    // PASO 1: REALIZAR LA ELIMINACIÓN ESTÁNDAR DE UN ABB
    if (raiz == nullptr)
        return raiz;
    // Si la clave a eliminar es menor que la clave de la raíz,
    // entonces está en el subárbol izquierdo
    if (clave < raiz->clave)
        raiz->izquierda = eliminar(raiz->izquierda, clave);
    // Si la clave a eliminar es mayor que la clave de la raíz,
    // entonces está en el subárbol derecho
    else if (clave > raiz->clave)
        raiz->derecha = eliminar(raiz->derecha, clave);
    // si la clave es la misma que la clave de la raíz, entonces
    // este es el nodo a ser eliminado
    else {
        // nodo con solo un hijo o sin hijos
        if ((raiz->izquierda == nullptr) || (raiz->derecha == nullptr)) {
            struct nodo *temp = raiz->izquierda ? raiz->izquierda : raiz->derecha;
            // Sin hijos
            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            }
            else // Un hijo
                *raiz = *temp; // Copiar el contenido del hijo no vacío
            delete temp;
        }
        else {
            // nodo con dos hijos: Obtener el sucesor inorden (el menor en el subárbol derecho)
            struct nodo* temp = nodoConValorMinimo(raiz->derecha);
            // Copiar la clave del sucesor inorden a este nodo
            raiz->clave = temp->clave;
            // Eliminar el sucesor inorden
            raiz->derecha = eliminar(raiz->derecha, temp->clave);
        }
    }
    // Si el árbol tenía solo un nodo, entonces retornar
    if (raiz == nullptr)
        return raiz;
    // PASO 2: ACTUALIZAR LA ALTURA DEL NODO ACTUAL
    raiz->altura = 1 + max(altura(raiz->izquierda), altura(raiz->derecha));
    // PASO 3: OBTENER EL FACTOR DE BALANCE DE ESTE NODO (para comprobar si este nodo se desequilibró)
    int balance = obtenerBalance(raiz);
    // Si este nodo se desequilibra, entonces hay 4 casos
    // Caso Izquierda Izquierda
    if (balance > 1 && obtenerBalance(raiz->izquierda) >= 0)
        return rotacionDerecha(raiz);
    // Caso Izquierda Derecha
    if (balance > 1 && obtenerBalance(raiz->izquierda) < 0) {
        raiz->izquierda = rotacionIzquierda(raiz->izquierda);
        return rotacionDerecha(raiz);
    }
    // Caso Derecha Derecha
    if (balance < -1 && obtenerBalance(raiz->derecha) <= 0)
        return rotacionIzquierda(raiz);
    // Caso Derecha Izquierda
    if (balance < -1 && obtenerBalance(raiz->derecha) > 0) {
        raiz->derecha = rotacionDerecha(raiz->derecha);
        return rotacionIzquierda(raiz);
    }
    return raiz;
}

#endif
