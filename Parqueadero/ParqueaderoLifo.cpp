//Daniela jaramillo y jeison mosquera


#include <iostream>
#include <malloc.h>

using namespace std;

struct Vehiculo {
    string tipo; // "auto" o "moto"
    int movimientos; // Número de movimientos
    Vehiculo* siguiente; // Puntero al siguiente vehículo en la pila
};

Vehiculo* tope = NULL; // Puntero al tope de la pila

// Función para calcular el costo total de un vehículo
int calcularCosto(const Vehiculo& vehiculo) {
    int costoParqueada, costoMovimientos;
    if (vehiculo.tipo == "auto") {
        costoParqueada = 5000;
        costoMovimientos = 1000 * vehiculo.movimientos;
    } else if (vehiculo.tipo == "moto") {
        costoParqueada = 2500;
        costoMovimientos = 500 * vehiculo.movimientos;
    } else {
        cout << "Tipo de vehículo no válido." << endl;
        return 0;
    }
    return costoParqueada + costoMovimientos;
}

// Función para agregar un vehículo al parqueadero
void agregarVehiculo(const string& tipo, int movimientos) {
    Vehiculo* nuevoVehiculo = (Vehiculo*)malloc(sizeof(Vehiculo));
    nuevoVehiculo->tipo = tipo;
    nuevoVehiculo->movimientos = movimientos;
    nuevoVehiculo->siguiente = tope;
    tope = nuevoVehiculo;
}

// Función para calcular el costo total y liberar la memoria de los vehículos
void calcularCostoTotal() {
    int totalAutos = 0;
    int totalMotos = 0;
    while (tope != NULL) {
        Vehiculo* vehiculo = tope;
        tope = tope->siguiente;
        int costo = calcularCosto(*vehiculo);
        if (vehiculo->tipo == "auto") {
            totalAutos += costo;
        } else if (vehiculo->tipo == "moto") {
            totalMotos += costo;
        }
        free(vehiculo);
    }
    cout << "Costo total por concepto:" << endl;
    cout << "Autos: " << totalAutos << " pesos" << endl;
    cout << "Motos: " << totalMotos << " pesos" << endl;
}

int main() {
    // Ejemplo: Agregar dos autos y una moto al parqueadero
    agregarVehiculo("auto", 3); // Auto con 3 movimientos
    agregarVehiculo("auto", 2); // Auto con 2 movimientos
    agregarVehiculo("moto", 1); // Moto con 1 movimiento

    // Calcular el costo total y liberar la memoria
    calcularCostoTotal();

    return 0;
}
