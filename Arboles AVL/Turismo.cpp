#include <iostream>
#include <cstdlib>
#include <cstring>


using namespace std;

const int Max = 50;//longitud maxima de char

//estructura pasajero 
struct Pasajero {
    char nombre[Max];
    Pasajero* siguiente;
};

struct Cola
{
    Pasajero* frente;
    Pasajero* final;
    int numPasajeros;
};



//viaje = nodo
 struct Viaje {
	
   char ID [Max]; 
    int Precio;
    char Destino [Max];
    char Matricula [3];
    char Embarcacion [Max];
    int  dia, mes, anio;
    int capacidad;
    Cola pasajeros;


    Viaje *izq;
    Viaje *dere;
    int altura;
};

Viaje *raiz = NULL;

// inserto mi nuevo nodo 
Viaje* crearNodo() {
    Viaje* nuevoViaje = (Viaje*)malloc(sizeof(Viaje));
    cout << "Matricula del Barco: ";
    cin >> nuevoViaje->Matricula;

    cout << "Nombre del Barco: ";
    cin.ignore();
    cin.getline(nuevoViaje->Embarcacion, Max);

    cout << "Fecha del viaje (Dia, mes , anio): ";
    cin >> nuevoViaje->dia >> nuevoViaje->mes >> nuevoViaje->anio;

    cout << "Precio del viaje: ";
    cin >> nuevoViaje->Precio;

    cout << "Destino del viaje: ";
    cin.ignore();
    cin.getline(nuevoViaje->Destino, Max);

    cout << "Capacidad del Barco: ";
    cin >> nuevoViaje->capacidad;

    nuevoViaje->pasajeros.frente = NULL;
    nuevoViaje->pasajeros.final = NULL;
    nuevoViaje->pasajeros.numPasajeros = 0;

    nuevoViaje->izq = NULL;
    nuevoViaje->dere = NULL;
    nuevoViaje->altura = 1;

    //genero el id concatenando

 strncpy(nuevoViaje->ID, nuevoViaje->Matricula, 2); 
    snprintf(nuevoViaje->ID + 2, sizeof(nuevoViaje->ID) - 2, "%04d%02d%02d", nuevoViaje->anio, nuevoViaje->mes, nuevoViaje->dia); // Año, mes y día
       //salida del ID
       cout << "Tome su pinche identifcador concatenado" << nuevoViaje->ID << endl;
       
        return nuevoViaje;
}




//altura de un nodo 
    int obtenerAltura(Viaje *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}
    int obtenerBalance(Viaje *nodo) { 
    if (nodo == NULL) {
        return 0;
    }
    return obtenerAltura(nodo->izq) - obtenerAltura(nodo->dere);
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

//insertar nuevo viaje en arbol alv

Viaje* insertar(Viaje *nodo, Viaje *nuevoViaje){
    if (nodo == NULL) {
        return nuevoViaje;  
    }

    if (strcmp(nuevoViaje->ID, nodo->ID) < 0) {
        nodo->izq = insertar(nodo->izq, nuevoViaje);
    } else if (strcmp(nuevoViaje->ID, nodo->ID) > 0) {
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


 //Fubcion donde registro el pasajero
    bool registrarPasajero(Viaje* viaje, const char* nombre) {
    if (viaje->pasajeros.numPasajeros >= viaje->capacidad) {
        cout << "No hay cupo." << endl;
        return false;
    }

    Pasajero* nuevoPasajero = (Pasajero*)malloc(sizeof(Pasajero));
    strcpy(nuevoPasajero->nombre, nombre);
    nuevoPasajero->siguiente = NULL;

    if (viaje->pasajeros.final == NULL) {
        viaje->pasajeros.frente = nuevoPasajero;
        viaje->pasajeros.final = nuevoPasajero;
    } else {
        viaje->pasajeros.final->siguiente = nuevoPasajero;
        viaje->pasajeros.final = nuevoPasajero;
    }

    viaje->pasajeros.numPasajeros++;
    return true;
}

//enlistar los pasajeros
void listarPasajeros(Viaje* viaje) {
    if (viaje->pasajeros.frente == NULL) {
        cout << "Nadie se registro en el viaje" << endl;
        return;
    }

    Pasajero* actual = viaje->pasajeros.frente;
    while (actual != NULL) {
        cout << actual->nombre << " ";
        actual = actual->siguiente;
    }
    cout << endl;
}

// busco el viaje por si ID
Viaje* buscarViaje(Viaje* nodo, const char* id) {
    if (nodo == NULL || strcmp(nodo->ID, id) == 0) {
        return nodo;
    }

    if (strcmp(id, nodo->ID) < 0) {
        return buscarViaje(nodo->izq, id);
    }

     return buscarViaje(nodo->dere, id);
}








int main() {
    int opc = 0;
    while (opc != 7) {
        cout << "Menu de opciones" << endl;
        cout << "1. Registrar un viaje" << endl;
        cout << "2. Buscar un viaje por ID" << endl;
        cout << "3. EnListar todos los viajes" << endl;
        cout << "4. Eliminar un viaje por identificador" << endl;
        cout << "5. Registrar un pasajero en un viaje" << endl;
        cout << "6. EnListar todos los pasajeros de un viaje" << endl;
        cout << "7. Salir" << endl;
        cin >> opc;
        
        switch (opc) {
            case 1: {
                Viaje* nuevoViaje = crearNodo();
                raiz = insertar(raiz, nuevoViaje);
                break;
            }

       case 2: {
                char id[11];
                cout << "Ingrese el Id del viaje: ";
                cin >> id;
                Viaje* viaje = buscarViaje(raiz, id);
                if (viaje != NULL) {
                    cout << "Viaje encontrado: " << viaje->ID << endl;
                    cout << "Matrícula: " << viaje->Matricula << endl;
                    cout << "Nombre del Barco: " << viaje->Embarcacion << endl;
                    cout << "Fecha: " << viaje->dia << "/" << viaje->mes << "/" << viaje->anio << endl; // Modificación: Mostrar la fecha desglosada
                    cout << "Precio: " << viaje->Precio << endl;
                    cout << "Destino: " << viaje->Destino << endl;
                    cout << "Capacidad: " << viaje->capacidad << endl;
                    cout << "Pasajeros: " << viaje->pasajeros.numPasajeros << endl;
                } else {
                    cout << "Viaje no encontrado" << endl;
                }
                break;
            }

            case 3: {
                cout << "Lista de viajes (preorden): " << endl;
                preOrden(raiz);
                cout << endl;
                break;
            }

            case 4: {
                // Implementar eliminación de un viaje por identificador
                break;
            }



case 5: {
                char id[11];
                cout << "Ingrese el Id del viaje: ";
                cin >> id;
                Viaje* viaje = buscarViaje(raiz, id);
                if (viaje != NULL) {
                    char nombrePasajero[Max];
                    cout << "Ingrese el nombre del pasajero: ";
                    cin.ignore();
                    cin.getline(nombrePasajero, Max);
                    if (registrarPasajero(viaje, nombrePasajero)) {
                        cout << "Pasajero registrado exitosamente" << endl;
                    } else {
                        cout << "No se pudo registrar el pasajero" << endl;
                    }
                } else {
                    cout << "Viaje no encontrado" << endl;
                }
                break;
            }

            case 6: {
                char id[11];
                cout << "Ingrese el Id del viaje: ";
                cin >> id;
                Viaje* viaje = buscarViaje(raiz, id);
                if (viaje != NULL) {
                    cout << "Lista de pasajeros:" << endl;
                    listarPasajeros(viaje);
                } else {
                    cout << "Viaje no encontrado" << endl;
                }
                break;
            }

            case 7: {
                cout << "Saliendo del programa..." << endl;
                break;
            }

            default: {
                cout << "Opción no válida" << endl;
                break;
            }
        }
    }

    liberarArbol(raiz);
    return 0;
}