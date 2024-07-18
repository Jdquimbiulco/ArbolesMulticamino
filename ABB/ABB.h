#ifndef ABB_H
#define ABB_H

#include <iostream>

struct nodo {
    int clave;
    struct nodo *izquierda, *derecha;
    int altura;
};

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
    // 1. Realizar la inserción normal en el BST
    if (nodo == nullptr)
        return nuevoNodo(clave);

    if (clave < nodo->clave)
        nodo->izquierda = insertar(nodo->izquierda, clave);
    else if (clave > nodo->clave)
        nodo->derecha = insertar(nodo->derecha, clave);
    else // Las claves iguales no se permiten en el BST
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

#endif
