#include <iostream>
#include <cstdlib>

using namespace std;

const int Max = 50://longitud maxima de char
//viaje = nodo
 struct Viaje {
	
   char ID [11]; 
    int Precio;
    char Destino [Max];
    char Matricula [3];
    char Embarcacion [Max];
    char fecha [9];
    int capacidad;
    int pasajeros;

    Viaje *izq;
    Viaje *dere;
    int altura;
}

Viaje *raiz =NULL
// inserto mi nuevo nodo 
Viaje* crearNodo() {
    Viaje *nuevoViaje = (Viaje *)malloc(sizeof(Viaje));
    cout << "Matricula del Barco:";
    cin >> nuevoViaje->Matricula;

    cout << "Nombre del Barco: ";
    cin.ignore();
    cin.getline (nuevoViaje->nombreEmbarcacion,Max);
    
    cout<< "Fecha del viaje XXYYYYMMDD: ";
    cin >> nuevoViaje->fecha;

    cout << "Precio del viaje: ";
    cin >> nuevoViaje->precio;

    cout << "Destino del viaje: ";
    cin.ignore();
    cin.getline(nuevoViaje->destino, Max);

    cout<< "Capacidad del Barco:";
    cin>> nuevoViaje-> capacidad;
    nuevoViaje-> pasajeros =0;
    nuevoViaje->izq =NULL;
    nuevoViaje->dere =NULL;
    nuevoViaje->altura =1;

    //genero el id concatenando

 strncpy(nuevoViaje->ID, nuevoViaje->matricula, 2);
    strncat(nuevoViaje->ID, nuevoViaje->fecha, 8);
    nuevoViaje->ID[10] = "\0"; 
    return nuevoViaje;
}

//insertar nuevo viaje en arbol alv

Viaje* insertar(Viaje *nodo, Viaje *nuevoViaje){
    if (nodo == NULL) {
        return nuevoViaje;  
    }

    if (strcmp(nuevoViaje->ID, nodo->ID) <0){
        nodo->izq = insertar(nodo->izq, nuevoViaje);
    }} else if (strcmp(nuevoViaje->ID, nodo->ID) > 0) {
        nodo->dere = insertar(nodo->dere, nuevoViaje);
    } else {
        return nodo;
    }

//actualizo la altura del nodo act
nodo->altura =1 +max(obtenerAltura(nodo->izq), obtenerAltura(nodo->dere));

//balance y rotacion
int balance = obtenerBalance(nodo);//rota derecha

    if (balance > 1 && strcmp(nuevoViaje->ID, nodo->izq->ID) < 0) {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && strcmp(nuevoViaje->ID, nodo->dere->ID) > 0) {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && strcmp(nuevoViaje->ID, nodo->izq->ID) > 0) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && strcmp(nuevoViaje->ID, nodo->dere->ID) < 0) {
        nodo->dere = rotarDerecha(nodo->dere);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

//altura de un nodo 
int obtenerAltura(Viaje *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}
//izq rotar
Viaje* rotarDerecha(Viaje *y) {
    Viaje *x = y->izq;
    Viaje *T2 = x->dere;

    x->dere = y;
    y->izq = T2;
  // Actualizar alturas
    y->altura = max(obtenerAltura(y->izq), obtenerAltura(y->dere)) + 1;
    x->altura = max(obtenerAltura(x->izq), obtenerAltura(x->dere)) + 1;

    return x;
}

//der rotar
Viaje* rotarIzquierda(Viaje *x) {
    Viaje *y = x->dere;
    Viaje *T2 = y->izq;

    y->izq = x;
    x->dere = T2;

    // Actualizar alturas
    x->altura = max(obtenerAltura(x->izq), obtenerAltura(x->dere)) + 1;
    y->altura = max(obtenerAltura(y->izq), obtenerAltura(y->dere)) + 1;

    return y;
}

//recore preorden m
 void preOrden (Viaje *nodo) {
    if (nodo != NULL){
        cout<< nodo->ID <<"";
        preOrden(nodo->izq);
        preOrden(nodo->dere);
    }
 }

 //liberar la memoria 
 void liberarArbol (Viaje *nodo){
    if (nodo!=NULL){
        liberarArbol(nodo->izq);
        liberarArbol(nodo->dere);
        free (nodo);
    }
 }




























    










int main()
{




}