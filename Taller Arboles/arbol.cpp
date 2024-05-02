//Jeison mosquers y Daniela jaramillo



#include <iostream>
#include <cstring>
#include <limits>

    using namespace std;


struct Estudiante //modificada de muchas estructurasa una sola 
{
    char Nombre_Apelido;
    int codigo_estud;
    char fecha_Nac;
    Estudiante *izquierda;
    Estudiante *derecha;
};

void insertar_Arbol(Estudiante *&arbol, Estudiante *N_Estudiante, bool (*comparar)(const char *, const char *));
bool Comparar_Por_Codigo(const char *codigo1, const char *codigo2);
bool Comparar_Por_Fecha(const char *fecha1, const char *fecha2);
void registrar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&arbol_Fecha, Estudiante *N_Estudiante);
void mostrar_Menu();
void limpiar_Buffer();
void eliminar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&arbol_Fecha, const char *codigoAEliminar);
void eliminar_Nodo(Estudiante **arbol, const char *codigoAEliminar);
void imprimir_PreOrden(Estudiante *arbol);
void imprimir_InOrden(Estudiante *arbol);
void imprimir_PostOrden(Estudiante *arbol);

Estudiante *buscar_Estudiante(Estudiante *arbol, const char *codigoABuscar);
void buscar_Estudiante_Y_Mostrar(Estudiante *Arbol_Cod, const char *codigoABuscar);


int main()
{
    Estudiante *Arbol_Cod = nullptr;
    Estudiante *arbol_Fecha = nullptr;

    int opcion;
    do
    {
        mostrar_Menu();
        cin >> opcion;
        limpiar_Buffer();

        switch (opcion)
        {
        case 1:
        {
            Estudiante *N_Estudiante = new Estudiante;
            cout << "\nNombre completico del estudiante : ";

            cin.getline(N_Estudiante->Nombre_Apellido, 40);
            cout << "Ingrese el código del estudiante: ";

            cin >> N_Estudiante->codigo_estud;
            cout << "Ingrese la fecha de nacimiento del estudiante (DD/MM/AAAA): ";
            
            cin >> N_Estudiante->fecha_Nac;
            N_Estudiante->izquierda = nullptr;
            N_Estudiante->derecha = nullptr;
            registrar_Estudiante(Arbol_Cod, arbol_Fecha, N_Estudiante);
            cout << "Correcto" << endl;
            break;
        }
        case 2:
        {
            cout << "\nIngrese el codigo del estudiante a eliminar: ";
            char codigoEliminar[40];
            cin.ignore();
            cin.getline(codigoEliminar, 40);
            eliminar_Estudiante(Arbol_Cod, arbol_Fecha, codigoEliminar);
            break;
        }
        case 3:
        {
            cout << "\nIngrese el codigo del estudiante a buscar: ";
            char codigoBuscar[40];
            cin.ignore();
            cin.getline(codigoBuscar, 40);
            buscar_Estudiante_Y_Mostrar(Arbol_Cod, codigoBuscar);
            break;
        }
        case 4:
        {
            cout << "\nMostrando el arbol en Preorden:" << endl;
            cout << "Arbol ordenado por codigo:" << endl;
            imprimir_PreOrden(Arbol_Cod);
            cout << "Arbol ordenado por fecha de nacimiento:" << endl;
            imprimir_PreOrden(arbol_Fecha);
            cout << "\n";
            break;
        }
        case 5:
        {
            cout << "\nMostrando el arbol en Inorden:" << endl;
            cout << "Arbol ordenado por codigo:" << endl;
            imprimir_InOrden(Arbol_Cod);
            cout << "Arbol ordenado por fecha de nacimiento:" << endl;
            imprimir_InOrden(arbol_Fecha);
            cout << "\n";
            break;
        }
        case 6:
        {
            cout << "\nMostrando el arbol en Postorden:" << endl;
            cout << "Arbol ordenado por codigo:" << endl;
            imprimir_PostOrden(Arbol_Cod);
            cout << "Arbol ordenado por fecha de nacimiento:" << endl;
            imprimir_PostOrden(arbol_Fecha);
            cout << "\n";
            break;
        }
        case 7:
        {
            cout << "\nSaliendo del programa..." << endl;
            break;
        }
        default:
            cout << "\nOpcion no valida. Intente de nuevo." << endl;
            break;
        }
    } while (opcion != 7);

    return 0;
}


void insertar_Arbol(Estudiante *&arbol, Estudiante *N_Estudiante, bool (*comparar)(const char *, const char *))
{
    if (arbol == nullptr)
    {
        arbol = N_Estudiante;
    }
    else if (comparar(to_string(N_Estudiante->codigo_estud).c_str(), to_string(arbol->codigo_estud).c_str()))
    {
        insertar_Arbol(arbol->izquierda, N_Estudiante, comparar);
    }
    else
    {
        insertar_Arbol(arbol->derecha, N_Estudiante, comparar);
    }
}

bool Comparar_Por_Codigo(const char *codigo1, const char *codigo2)
{
    return atoi(codigo1) < atoi(codigo2);
}

bool Comparar_Por_Fecha(const char *fecha1, const char *fecha2)
{
    return strcmp(fecha1, fecha2) < 0;
}

void registrar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&arbol_Fecha, Estudiante *N_Estudiante)
{
    insertar_Arbol(Arbol_Cod, N_Estudiante, Comparar_Por_Codigo);
    Estudiante *N_Estudiante_Fecha = new Estudiante(*N_Estudiante);
    insertar_Arbol(arbol_Fecha, N_Estudiante_Fecha, Comparar_Por_Fecha);
}

void mostrar_Menu()
{
    cout << "\nMenu" << endl;
    cout << "1. Registrar estudiante" << endl;
    cout << "2. Eliminar estudiante" << endl;
    cout << "3. Ordenar por código" << endl;
    cout << "4. Ordenar por fecha de nacimiento" << endl;
    cout << "5. Buscar estudiante" << endl;
    cout << "6. Mostrar pre orden" << endl;
    cout << "7. Mostrar in orden" << endl;
    cout << "8. Mostrar post orden" << endl;
    cout << "9. Salir" << endl;
    cout << "Ingrese su opcion: ";
}

void limpiar_Buffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void eliminar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&arbol_Fecha, const char *codigoAEliminar)
{
    eliminar_Nodo(&Arbol_Cod, codigoAEliminar);
    eliminar_Nodo(&arbol_Fecha, codigoAEliminar);
    cout << "Estudiante eliminado exitosamente." << endl;
}

void eliminar_Nodo(Estudiante **arbol, const char *codigoAEliminar)
{
    if (*arbol == nullptr)
    {
        return;
    }

    if (atoi((*arbol)->codigo_estud) == atoi(codigoAEliminar))
    {
        Estudiante *nodoAEliminar = *arbol;
        if ((*arbol)->izquierda == nullptr && (*arbol)->derecha == nullptr)
        {
            delete nodoAEliminar;
            *arbol = nullptr;
        }
        else if ((*arbol)->derecha == nullptr)
        {
            *arbol = (*arbol)->izquierda;
            delete nodoAEliminar;
        }
        else if ((*arbol)->izquierda == nullptr)
        {
            *arbol = (*arbol)->derecha;
            delete nodoAEliminar;
        }
        else
        {
            Estudiante *sucesor = (*arbol)->derecha;
            while (sucesor->izquierda != nullptr)
            {
                sucesor = sucesor->izquierda;
            }
            (*arbol)->codigo_estud = sucesor->codigo_estud;
            eliminar_Nodo(&((*arbol)->derecha), sucesor->codigo_estud);
        }
    }
    else if (atoi((*arbol)->codigo_estud) > atoi(codigoAEliminar))
    {
        eliminar_Nodo(&((*arbol)->izquierda), codigoAEliminar);
    }
    else
    {
        eliminar_Nodo(&((*arbol)->derecha), codigoAEliminar);
    }
}

void imprimir_PreOrden(Estudiante *arbol)
{
    if (arbol != nullptr)
    {
        cout << "Nombre: " << arbol->Nombre_Apellido << endl;
        cout << "Codigo: " << arbol->codigo_estud << endl;
        cout << "Fecha de nacimiento: " << arbol->fecha_Nac << endl
             << endl;
        imprimir_PreOrden(arbol->izquierda);
        imprimir_PreOrden(arbol->derecha);
    }
}

void imprimir_InOrden(Estudiante *arbol)
{
    if (arbol != nullptr)
    {
        imprimir_InOrden(arbol->izquierda);
        cout << "Nombre: " << arbol->Nombre_Apellido << endl;
        cout << "Codigo: " << arbol->codigo_estud << endl;
        cout << "Fecha de nacimiento: " << arbol->fecha_Nac << endl
             << endl;
        imprimir_InOrden(arbol->derecha);
    }
}

void imprimir_PostOrden(Estudiante *arbol)
{
    if (arbol != nullptr)
    {
        imprimir_PostOrden(arbol->izquierda);
        imprimir_PostOrden(arbol->derecha);
        cout << "Nombre: " << arbol->Nombre_Apellido << endl;
        cout << "Codigo: " << arbol->codigo_estud << endl;
        cout << "Fecha de nacimiento: " << arbol->fecha_Nac << endl
             << endl;
    }
}

Estudiante *buscar_Estudiante(Estudiante *arbol, const char *codigoABuscar)
{
    if (arbol == nullptr || atoi(arbol->codigo_estud) == atoi(codigoABuscar))
    {
        return arbol;
    }

    if (atoi(arbol->codigo_estud) > atoi(codigoABuscar))
    {
        return buscar_Estudiante(arbol->izquierda, codigoABuscar);
    }
    else
    {
        return buscar_Estudiante(arbol->derecha, codigoABuscar);
    }
}

void buscar_Estudiante_Y_Mostrar(Estudiante *Arbol_Cod, const char *codigoABuscar)
{
    Estudiante *estudianteEncontrado = buscar_Estudiante(Arbol_Cod, codigoABuscar);
    if (estudianteEncontrado != nullptr)
    {
        cout << "Estudiante encontrado:" << endl;
        cout << "Nombre: " << estudianteEncontrado->Nombre_Apellido << endl;
        cout << "Codigo: " << estudianteEncontrado->codigo_estud << endl;
        cout << "Fecha de nacimiento: " << estudianteEncontrado->fecha_Nac << endl;
    }
    else
    {
        cout << "Estudiante con codigo " << codigoABuscar << " no encontrado." << endl;
    }
}