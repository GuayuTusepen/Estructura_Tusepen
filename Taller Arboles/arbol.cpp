//Jeison mosquers y Daniela jaramillo




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
    } else 
<<<<<<< HEAD
       
=======
       
>>>>>>> 30d237396a96efa06c8b63b9be7f8ec358eda0c8
