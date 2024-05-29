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

Viaje* crearNodo() {
    Viaje *nuevoViaje = (Viaje *)malloc(sizeof(Viaje));
    cout << "Matricula del Barco:";
    cin >> nuevoViaje->Matricula;

    cout << "Nombre del Barco: ";
    cin.ignore();
    cin.getline (nuevoViaje->nombreEmbarcacion,Max);
    c
    



    
}









// meytot

void Registar_Viaje(Viaje *&arbol, Viaje *Nuevo_Viaje){}
void Buscar_Viaje(Viaje *&arbol, char ID){};
void Listar_Viaje;
void Eliminar_Viaje;
void Registar_pasajero;
void Listar_pasajero;

int main()
{




}