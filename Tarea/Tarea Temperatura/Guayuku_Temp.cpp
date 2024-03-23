#include <iostream>
#include <string>
using namespace std;

struct RegistroTemperatura {
    string fecha;
    float temperaturaManana;
    float temperaturaTarde;
    float temperaturaNoche;
};

void registrarTemperatura(RegistroTemperatura *registros, int n) {
    for (int i = 0; i < n; ++i) {
        cout << "Ingrese la fecha (dd/mm/yyyy) para el dia " << i+1 << ": ";
        cin >> registros[i].fecha;
        cout << "Ingrese la temperatura de la manana: ";
        cin >> registros[i].temperaturaManana;
        cout << "Ingrese la temperatura de la tarde: ";
        cin >> registros[i].temperaturaTarde;
        cout << "Ingrese la temperatura de la noche: ";
        cin >> registros[i].temperaturaNoche;
    }
}

void mostrarRegistros(RegistroTemperatura *registros, int n) {
    cout << "Fecha\t\tManana\tTarde\tNoche" << endl;
    for (int i = 0; i < n; ++i) {
        cout << registros[i].fecha << "\t";
        cout << registros[i].temperaturaManana << "\t";
        cout << registros[i].temperaturaTarde << "\t";
        cout << registros[i].temperaturaNoche << endl;
    }
}

float calcularPromedioDia(const RegistroTemperatura &registro) {
    return (registro.temperaturaManana + registro.temperaturaTarde + registro.temperaturaNoche) / 3.0;
}

float calcularPromedioTotal(const RegistroTemperatura *registros, int n) {
    float suma = 0;
    for (int i = 0; i < n; ++i) {
        suma += calcularPromedioDia(registros[i]);
    }
    return suma / n;
}

int main() {
    int n;
    cout << "Ingrese el numero de dias a registrar: ";
    cin >> n;

    RegistroTemperatura *registros = new RegistroTemperatura[n];

    registrarTemperatura(registros, n);

    int opcion;
    do {
        cout << "\n--- Guayuku Temp ---" << endl;
        cout << "1. Mostrar registros" << endl;
        cout << "2. Calcular promedio de temperatura del dia" << endl;
        cout << "3. Calcular promedio de temperatura total" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese su opcin: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarRegistros(registros, n);
                break;
            case 2:
                cout << "Promedio de temperatura del dia: " << calcularPromedioDia(registros[0]) << endl; // Suponiendo que queremos calcular el promedio para el primer dia como ejemplo
                break;
            case 3:
                cout << "Promedio de temperatura de todos los registros: " << calcularPromedioTotal(registros, n) << endl;
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, ingrese un numero valido." << endl;
        }
    } while (opcion != 4);

    delete[] registros; // Liberar la memoria asignada dinamicamente

    return 0;
}
