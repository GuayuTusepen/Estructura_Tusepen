#include <iostream>
using namespace std;

struct Estudiante {
    int codigo;
    string nombres;
    string apellidos;
    struct FechaNacimiento {
        int year;
        int month;
        int day;
    } fecha;
};

struct Nodo {
    Estudiante estudiante;
    Nodo *izq;
    Nodo *der;
};

Nodo *raiz = NULL;

void Insert_cod_estd(Estudiante estudiante) {
    Nodo *nuevo = new Nodo;
    nuevo->estudiante = estudiante;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    if (raiz == NULL) {
        raiz = nuevo;
    } else {
        Nodo *temp = raiz;
        while (temp != NULL) {
            if (estudiante.codigo < temp->estudiante.codigo) {
                if (temp->izq == NULL) {
                    temp->izq = nuevo;
                    return;
                }
                temp = temp->izq;
            } else {
                if (temp->der == NULL) {
                    temp->der = nuevo;
                    return;
                }
                temp = temp->der;
            }
        }
    }
}
