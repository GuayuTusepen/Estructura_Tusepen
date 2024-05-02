//Jeison mosquers y Daniela jaramillo



#include <iostream>
#include <cstring>
#include <limits>

    using namespace std;


struct Estudiante //modificada de muchas estructurasa una sola 
{
    char Nombre_Apellido [40];
    int codigo_estud;
    char fecha_Nac [11];
    Estudiante *izquierda;
    Estudiante *derecha;
};

void insertar_Arbol(Estudiante *&arbol, Estudiante *N_Estudiante, bool (*comparar)(int, int));
bool Comparar_Por_Codigo(int codigo1, int codigo2);
bool Comparar_Por_Fecha(const char *fecha1, const char *fecha2);
void registrar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&arbol_Fecha, Estudiante *N_Estudiante);
void mostrar_Menu();
void limpiar_Buffer();
void eliminar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&arbol_Fecha, const char *codigoAEliminar);
void eliminar_Nodo(Estudiante **arbol, const char *codigoAEliminar);
void imprimir_PreOrden(Estudiante *arbol);
void imprimir_InOrden(Estudiante *arbol);
void imprimir_PostOrden(Estudiante *arbol);
Estudiante *buscar_Estudiante(Estudiante *arbol, const char *codigo_Buscar);
void buscar_Estudiante_Y_Mostrar(Estudiante *Arbol_Cod, const char *codigo_Buscar);

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
            cout << "\nNombre completo del estudiante: ";

            cin.getline(N_Estudiante->Nombre_Apellido, 40);
            cout << "\nIngrese el código del estudiante: ";

            cin >> N_Estudiante->codigo_estud;
            cout << "Ingrese la fecha de nacimiento del estudiante (DD/MM/AAAA): ";
            cin.ignore(); // Limpiar el buffer antes de leer la fecha de nacimiento
            cin.getline(N_Estudiante->fecha_Nac, 11);
            N_Estudiante->izquierda = nullptr;
            N_Estudiante->derecha = nullptr;
            registrar_Estudiante(Arbol_Cod, arbol_Fecha, N_Estudiante);
            cout << "Estudiante registrado exitosamente." << endl;
            break;
        }
        case 2:
        {
            cout << "\nIngrese el código del estudiante a eliminar: ";
            char codigoEliminar[40];
            cin.ignore();
            cin.getline(codigoEliminar, 40);
            eliminar_Estudiante(Arbol_Cod, arbol_Fecha, codigoEliminar);
            break;
        }
        case 3:
        {
            cout << "\nIngrese el código del estudiante a buscar: ";
            char codigoBuscar[40];
            cin.ignore();
            cin.getline(codigoBuscar, 40);
            buscar_Estudiante_Y_Mostrar(Arbol_Cod, codigoBuscar);
            break;
        }
        case 4:
        {
            cout << "\nMostrando el árbol en Preorden:" << endl;
            cout << "Árbol ordenado por código:" << endl;
            imprimir_PreOrden(Arbol_Cod);
            cout << "Árbol ordenado por fecha de nacimiento:" << endl;
            imprimir_PreOrden(arbol_Fecha);
            cout << "\n";
            break;
        }
        case 5:
        {
            cout << "\nMostrando el árbol en Inorden:" << endl;
            cout << "Árbol ordenado por código:" << endl;
            imprimir_InOrden(Arbol_Cod);
            cout << "Árbol ordenado por fecha de nacimiento:" << endl;
            imprimir_InOrden(arbol_Fecha);
            cout << "\n";
            break;
        }
        case 6:
        {
            cout << "\nMostrando el árbol en Postorden:" << endl;
            cout << "Árbol ordenado por código:" << endl;
            imprimir_PostOrden(Arbol_Cod);
            cout << "Árbol ordenado por fecha de nacimiento:" << endl;
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
            cout << "\nOpción no válida. Intente de nuevo." << endl;
            break;
        }
    } while (opcion != 7);

    return 0;
}

void insertar_Arbol(Estudiante *&arbol, Estudiante *N_Estudiante, bool (*comparar)(int, int))
{
    if (arbol == nullptr)
    {
        arbol = N_Estudiante;
    }
    else if (comparar(N_Estudiante->codigo_estud, arbol->codigo_estud))
    {
        insertar_Arbol(arbol->izquierda, N_Estudiante, comparar);
    }
    else
    {
        insertar_Arbol(arbol->derecha, N_Estudiante, comparar);
    }
}

bool Comparar_Por_Codigo(int codigo1, int codigo2)
{
    return codigo1 < codigo2;
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
    cout << "6. Mostrar preorden" << endl;
    cout << "7. Mostrar inorden" << endl;
    cout << "8. Mostrar postorden" << endl;
    cout << "9. Salir" << endl;
    cout << "Ingrese su opción: ";
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

    if ((*arbol)->codigo_estud == atoi(codigoAEliminar))
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
            eliminar_Nodo(&((*arbol)->derecha), codigoAEliminar);
        }
    }
    else if ((*arbol)->codigo_estud > atoi(codigoAEliminar))
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

Estudiante *buscar_Estudiante(Estudiante *arbol, const char *codigo_Buscar)
{
    if (arbol == nullptr || arbol->codigo_estud == atoi(codigo_Buscar))
    {
        return arbol;
    }

    if (arbol->codigo_estud > atoi(codigo_Buscar))
    {
        return buscar_Estudiante(arbol->izquierda, codigo_Buscar);
    }
    else
    {
        return buscar_Estudiante(arbol->derecha, codigo_Buscar);
    }
}

void buscar_Estudiante_Y_Mostrar(Estudiante *Arbol_Cod, const char *codigo_Buscar)
{
    Estudiante *estudianteEncontrado = buscar_Estudiante(Arbol_Cod, codigo_Buscar);
    if (estudianteEncontrado != nullptr)
    {
        cout << "Estudiante encontrado:" << endl;
        cout << "Nombre: " << estudianteEncontrado->Nombre_Apellido << endl;
        cout << "Codigo: " << estudianteEncontrado->codigo_estud << endl;
        cout << "Fecha de nacimiento: " << estudianteEncontrado->fecha_Nac << endl;
    }
    else
    {
        cout << "Estudiante con código " << codigo_Buscar << " no encontrado." << endl;
    }
}