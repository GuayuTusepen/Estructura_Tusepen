#include <iostream>
#include <cstdlib>
#include <cstring>


using namespace std;

const int Max = 50;


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
    cout << "Ingrese la Matricula del Barco (max 3 caracteres) : "; //error de concatenar al ingresar mas de 3 caracteres poque puse ese limite
    cin >> nuevoViaje->Matricula;

    cout << "Ingrese el Nombre del Barco: ";
    cin.ignore();
    cin.getline(nuevoViaje->Embarcacion, Max);

    cout << "Ingrese la Fecha del viaje (Dia, mes , anio) (solo los numeros ): ";
    cin >> nuevoViaje->dia >> nuevoViaje->mes >> nuevoViaje->anio;

    cout << "Ingrese el Precio del viaje: ";
    cin >> nuevoViaje->Precio;

    cout << "Ingrese el Destino del viaje: ";
    cin.ignore();
    cin.getline(nuevoViaje->Destino, Max);

    cout << "Ingrese la Capacidad del Barco: ";
    cin >> nuevoViaje->capacidad;

    nuevoViaje->pasajeros.frente = NULL;
    nuevoViaje->pasajeros.final = NULL;
    nuevoViaje->pasajeros.numPasajeros = 0;

    nuevoViaje->izq = NULL;
    nuevoViaje->dere = NULL;
    nuevoViaje->altura = 1;

    //genero el id concatenando
// para asesoria al mostrar los datos en la matricula me muestra la matricula mas el nombre de la embarcacion
 strncpy(nuevoViaje->ID, nuevoViaje->Matricula, 2); 
   
    nuevoViaje->ID [2] = '\0';

    snprintf(nuevoViaje->ID + 2, sizeof(nuevoViaje->ID) - 2, "%04d%02d%02d", nuevoViaje->anio, nuevoViaje->mes, nuevoViaje->dia);
       //salida del ID
       cout << "Tome su pinche identifcador concatenado:      " << nuevoViaje->ID << endl;
       
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



//recore in orden 
void inorden(Viaje* nodo) {
    if (nodo != NULL) {
        inorden(nodo->izq);
            cout << "ID del viaje: " << nodo->ID << endl;
            inorden(nodo->dere);
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
        cout << "No hay cupo. no insista." << endl;
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
        cout << "No hay nadie en este viaje." << endl;
        return;
    }

    cout << "Pasajeros registrados en este viaje:" << endl;
    Pasajero* actual = viaje->pasajeros.frente;
    while (actual != NULL) {
        cout << actual->nombre << endl;
        actual = actual->siguiente;
    }
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
// eliminacion del ciaje

Viaje* eliminarViaje(Viaje* nodo, const char* id) {
    if (nodo == NULL) {
        return nodo;
    }

    if (strcmp(id, nodo->ID) < 0) {
        nodo->izq = eliminarViaje(nodo->izq, id);
    } else if (strcmp(id, nodo->ID) > 0) {
        nodo->dere = eliminarViaje(nodo->dere, id);
    } else {
        if (nodo->izq == NULL) {
            Viaje* temp = nodo->dere;
            free(nodo);
            return temp;
        } else if (nodo->dere == NULL) {
            Viaje* temp = nodo->izq;
            free(nodo);
            return temp;
        }

        Viaje* temp = nodo->dere;
        while (temp->izq != NULL) {
            temp = temp->izq;
        }
        strcpy(nodo->ID, temp->ID);
        nodo->dere = eliminarViaje(nodo->dere, temp->ID);
    }
    return nodo;
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
        cout << "6. EnListar los pasajeros de un viaje" << endl;
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
                    cout << " Viaje encontrado: " << viaje->ID << endl;
                    cout << " La Maticula es: " << viaje->Matricula << endl;
                    cout << " El Nombre del Barco es: " << viaje->Embarcacion << endl;
                    cout << " la Fecha del viaje es: " << viaje->dia << "/" << viaje->mes << "/" << viaje->anio << endl; // Modificación: Mostrar la fecha desglosada
                    cout << " este es el Precio: " << viaje->Precio << endl;
                    cout << " El Destino es hacia: " << viaje->Destino << endl;
                    cout << " La Capacidad del viaje es de: " << viaje->capacidad<< endl;
                    cout << " Pasajeros enlistados: " << viaje->pasajeros.numPasajeros << endl;
                } else {
                    cout << "No se enconto viaje. sorry" << endl;
                }
                break;
            }

            case 3: {
                cout << "Lista de viajes (inorden): " << endl;
                inorden(raiz);
                cout << endl;
                break;
            }

            case 4: {
    char idEliminar[11];
    cout << "Ingrese el ID del viaje a eliminar: ";
    cin >> idEliminar;
    raiz = eliminarViaje(raiz, idEliminar);
    break;
}




case 5: {
    char id[11];
    cout << "Ingrese el Id del viaje: ";
    cin >> id;
    Viaje* viaje = buscarViaje(raiz, id);
    if (viaje != NULL) {
        char nombrePasajero[Max];
        cout << "Ingrese el nombre del pasajero a registrar: ";
        cin.ignore();
        cin.getline(nombrePasajero, Max);

        bool registrado = registrarPasajero(viaje, nombrePasajero);
        if (registrado) {
            cout << "Pasajero registrado exitosamente en el viaje." << endl;
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
                cout << "opcion invalida . Mire bien " << endl;
                break;
            }
        }
    }

    liberarArbol(raiz);
    return 0;
}