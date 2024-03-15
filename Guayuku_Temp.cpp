#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Estructura para almacenar la temperatura en diferentes momentos del día
struct TemperaturaDia {
    float manana;
    float tarde;
    float noche;
};

// Estructura para almacenar los registros de temperatura de un día específico
struct RegistroDia {
    string fecha;
    TemperaturaDia temperatura;
    RegistroDia* siguiente;
};

// Clase para gestionar los registros de temperatura
class Guayuku_Temp {
private:
    RegistroDia* primero;
    RegistroDia* ultimo;

public:
    Guayuku_Temp() : primero(nullptr), ultimo(nullptr) {}

    // Función para agregar un registro de temperatura para un día específico
    void agregarRegistro(string fecha, float manana, float tarde, float noche) {
        RegistroDia* nuevoRegistro = new RegistroDia;
        nuevoRegistro->fecha = fecha;
        nuevoRegistro->temperatura.manana = manana;
        nuevoRegistro->temperatura.tarde = tarde;
        nuevoRegistro->temperatura.noche = noche;
        nuevoRegistro->siguiente = nullptr;

        if (!primero) {
            primero = nuevoRegistro;
            ultimo = nuevoRegistro;
        } else {
            ultimo->siguiente = nuevoRegistro;
            ultimo = nuevoRegistro;
        }
    }

    // Función para mostrar los registros de temperatura
    void mostrarRegistros() {
        RegistroDia* actual = primero;
        while (actual) {
            cout << "Fecha: " << actual->fecha << endl;
            cout << "Temperatura mañana: " << actual->temperatura.manana << " °C" << endl;
            cout << "Temperatura tarde: " << actual->temperatura.tarde << " °C" << endl;
            cout << "Temperatura noche: " << actual->temperatura.noche << " °C" << endl;
            cout << endl;
            actual = actual->siguiente;
        }
    }

    // Función para calcular el promedio de temperatura del día
    float promedioTemperaturaDia(string fecha) {
        RegistroDia* actual = primero;
        while (actual) {
            if (actual->fecha == fecha) {
                return (actual->temperatura.manana + actual->temperatura.tarde + actual->temperatura.noche) / 3.0;
            }
            actual = actual->siguiente;
        }
        return -1; // Fecha no encontrada
    }

    // Función para calcular el promedio de temperatura de todos los registros
    float promedioTemperaturaTotal() {
        RegistroDia* actual = primero;
        int count = 0;
        float total = 0;
        while (actual) {
            total += (actual->temperatura.manana + actual->temperatura.tarde + actual->temperatura.noche) / 3.0;
            count++;
            actual = actual->siguiente;
        }
        if (count == 0) return 0;
        return total / count;
    }

    // Destructor para liberar la memoria asignada dinámicamente
    ~Guayuku_Temp() {
        RegistroDia* actual = primero;
        while (actual) {
            RegistroDia* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
};

int main() {
    Guayuku_Temp registros;

    // Agregar registros de temperatura
    registros.agregarRegistro("2024-03-15", 20, 25, 18);
    registros.agregarRegistro("2024-03-16", 22, 28, 20);
    registros.agregarRegistro("2024-03-17", 19, 24, 17);

    int opcion;
    do {
        // Menú
        cout << "----- Menú -----" << endl;
        cout << "1. Mostrar registros" << endl;
        cout << "2. Calcular promedio de temperatura del día" << endl;
        cout << "3. Calcular promedio de temperatura total" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registros.mostrarRegistros();
                break;
            case 2: {
                string fecha;
                cout << "Ingrese la fecha (YYYY-MM-DD): ";
                cin >> fecha;
                float promedio = registros.promedioTemperaturaDia(fecha);
                if (promedio != -1) {
                    cout << "El promedio de temperatura del día " << fecha << " es: " << promedio << " °C" << endl;
                } else {
                    cout << "No se encontraron registros para la fecha especificada." << endl;
                }
                break;
            }
            case 3:
                cout << "El promedio de temperatura total es: " << registros.promedioTemperaturaTotal() << " °C" << endl;
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
                break;
        }

    } while (opcion != 4);

    return 0;
}
