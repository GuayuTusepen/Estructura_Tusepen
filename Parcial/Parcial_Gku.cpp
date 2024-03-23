#include <iostream>

using namespace std;

// Definición de la estructura Cliente
struct Cliente
{
    int numeroCuenta;
    int tipoCuenta; // 1 para preferencial, 2 para tradicional
    Cliente *siguiente;

    Cliente(int numero, int tipo) : numeroCuenta(numero), tipoCuenta(tipo), siguiente(nullptr) {}
};

class FilaEspera
{ // la clase e fila espera
public:
    Cliente *inicio;

    FilaEspera() : inicio(nullptr) {}

    //  registrar un cliente en la fila de espera
    void registrarCliente(int numeroCuenta, int tipoCuenta)
    { // cree el cliente y reserve la memoria de ese berraco cliente

        Cliente *nuevoCliente = new Cliente(numeroCuenta, tipoCuenta);
        if (!inicio) // si la fila esta vacia apunte a null mijo
        {
            inicio = nuevoCliente;
        }
        else // sino recorra la fina y busque el ultimo cliente
        {
            Cliente *temp = inicio;
            while (temp->siguiente)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoCliente;
        }

        // Verificar la condición de transferencia después de registrar un nuevo cliente
        verificarTransferencia();
    }

    // verificar y realizar la transferencia entre filas si es necesario
    void verificarTransferencia()
    { // variables para contar los clientes en la fila
        int countTradicionales = 0;
        int countPreferenciales = 0;
        Cliente *temp = inicio; // apunta a la fila de espera
        while (temp)            // blucle para recorreer la fisla ds espera
        {
            if (temp->tipoCuenta == 1)// comprueba el tipode cuenata si es = a 1 se incrementa la preferencial
            {
                countPreferenciales++;
            }
            else // sino se incrementa la tradicionañ
            {
                countTradicionales++;
            }
            temp = temp->siguiente;
        }

        if (countTradicionales >= 5 && countPreferenciales <= 2) // verifica si hay mas dde ee 5 clientes en tradi... y si  hay 2 ne la tradicional 
        {
            // Buscar el tercer cliente en la fila tradicional y moverlo a la fila preferencial
            int contador = 0;// inicia contador apunta al primer liente 
            temp = inicio;
            Cliente *anterior = nullptr;// apunta al cliente anterior en fila
           
           
            while (temp)
            {
                contador++;
                if (contador == 3 && temp->tipoCuenta == 2) //si el contador llega a 3 y es tradiconal encontro al 3cer cliente
                {
                    // Mover el cliente a la fila preferencial
                    if (anterior)
                    {
                        anterior->siguiente = temp->siguiente;
                    }
                    else// si encuentra a l primer cliente en la fina actualiza a sig
                    {
                        inicio = temp->siguiente;
                    }
                    temp->tipoCuenta = 1; // Cambiar el tipo de cuenta a preferencial
                    temp->siguiente = nullptr;

                    // Insertar al cliente en la fila preferencial
                    insertarClientePreferencial(temp);
                    break;
                }// sale del bucfe
                anterior = temp;
                temp = temp->siguiente;
            }
        }
    }

    //  insertar un cliente en la fila preferencial
    void insertarClientePreferencial(Cliente *cliente)
    {
        if (!inicio)
        {// verifico si esta vacio
            inicio = cliente;
        }
        else// sino apunte al 1ero
        {
            Cliente *temp = inicio;
            while (temp->siguiente)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = cliente;
        }
    }

    //  mostrar los clientes en la fila de espera
    void mostrarFilas()
    {
        Cliente *temp = inicio;
        int contador = 1;
        cout << "Clientes en la fila tradicional:" << endl;
        while (temp && temp->tipoCuenta == 2)
        {
            cout << "Cliente " << contador << ": Cuenta #" << temp->numeroCuenta << endl;
            temp = temp->siguiente;
            contador++;
        }

        contador = 1;
        cout << "\nClientes en la fila preferencial:" << endl;
        while (temp && temp->tipoCuenta == 1)
        {
            cout << "Cliente " << contador << ": Cuenta #" << temp->numeroCuenta << endl;
            temp = temp->siguiente;
            contador++;
        }

        cout << endl;
    }

    //  eliminar un cliente de la fila de espera
    void eliminarCliente()
    {
        if (!inicio)
        {
            cout << "No hay clientes en la fila de espera." << endl;
            return;
        }

        Cliente *temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
        cout << "Cliente atendido y eliminado de la fila de espera." << endl;

        // Reasignar turnos
        reasignarTurnos();
    }

    //  reasignar los turnos de los clientes en la fila de espera
    void reasignarTurnos()
    {
        Cliente *temp = inicio;
        int contador = 1;
        while (temp)
        {
            temp = temp->siguiente;
            contador++;
        }

        // Si no hay clientes, no hay necesidad de reasignar turnos
        if (contador == 1)
        {
            return;
        }

        // Reasignar los turnos
        temp = inicio;
        for (int i = 1; i <= contador; i++)
        {
            temp->numeroCuenta = i;
            temp = temp->siguiente;
        }
    }
};

int main()
{
    FilaEspera filaEspera;

    // Menú
    int opcion;
    do
    {
        cout << "Menu:\n";
        cout << "1. Registrar cliente\n";
        cout << "2. Mostrar filas de espera\n";
        cout << "3. Atender cliente\n";
        cout << "4. Salir\n";
        cout << "Ingrese la opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int numeroCuenta, tipoCuenta;
            cout << "Ingrese el numero de cuenta del cliente: ";
            cin >> numeroCuenta;
            cout << "Ingrese el tipo de cuenta (1 para preferencial, 2 para tradicional): ";
            cin >> tipoCuenta;
            filaEspera.registrarCliente(numeroCuenta, tipoCuenta);
            break;
        }
        case 2:
            filaEspera.mostrarFilas();
            break;
        case 3:
            filaEspera.eliminarCliente();
            break;
        case 4:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opcion no valida. Por favor ingrese una opcion valida.\n";
        }
    } while (opcion != 4);

    return 0;
}
