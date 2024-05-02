//Jeison mosquers y Daniela jaramillo


#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

struct Estudiante
{
    char Nombre_Apellido[40];
    char codigo_estud[40];
    char fecha_Nac[11];
    Estudiante *izquierda;
    Estudiante *derecha;
};

// Prototipos de función
void insertar_Arbol(Estudiante *&arbol, Estudiante *N_Estudiante, bool (*comparar)(const char *, const char *));
bool Comparar_Por_Codigo(const char *codigo1, const char *codigo2);
bool Comparar_Por_Fecha(const char *fecha1, const char *fecha2);
void registrar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&arbol_Fecha, Estudiante *N_Estudiante);
void mostrar_Menu();
void limpiar_Buffer();
void eliminar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&arbol_Fecha, const char *codigo_Eliminar);
void eliminar_Nodo(Estudiante **arbol, const char *codigo_Eliminar);
void imprimir_PreOrden(Estudiante *arbol);
void imprimir_InOrden(Estudiante *arbol);
void imprimir_PostOrden(Estudiante *arbol);
Estudiante *buscar_Estudiante(Estudiante *arbol, const char *codigo_Buscar);
void buscar_Estudiante_Y_Mostrar(Estudiante *Arbol_Cod, const char *codigo_Buscar);

int main()
{
    Estudiante *arbolPorCodigo = nullptr;
    Estudiante *arbolPorFecha = nullptr;

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
            Estudiante *nuevoEstudiante = new Estudiante;
            cout << "\nIngrese el nombre completo del estudiante: ";
            cin.getline(nuevoEstudiante->Nombre_Apellido, 40);
            cout << "Ingrese el código del estudiante: ";
            cin.getline(nuevoEstudiante->codigo_estud, 40);
            cout << "Ingrese la fecha de nacimiento del estudiante (DD/MM/AAAA): ";
            cin.getline(nuevoEstudiante->fecha_Nac, 11);
            nuevoEstudiante->izquierda = nullptr;
            nuevoEstudiante->derecha = nullptr;
            registrar_Estudiante(arbolPorCodigo, arbolPorFecha, nuevoEstudiante);
            cout << "Estudiante registrado exitosamente." << endl;
            break;
        }
        case 2:
        {
            cout << "\nIngrese el código del estudiante a eliminar: ";
            char codigoEliminar[40];
            cin.ignore();
            cin.getline(codigoEliminar, 40);
            eliminar_Estudiante(arbolPorCodigo, arbolPorFecha, codigoEliminar);
            break;
        }
        case 3:
        {
            cout << "\nIngrese el código del estudiante a buscar: ";
            char codigoBuscar[40];
            cin.ignore();
            cin.getline(codigoBuscar, 40);
            buscar_Estudiante_Y_Mostrar(arbolPorCodigo, codigoBuscar);
            break;
        }
        case 4:
        {
            cout << "\nMostrando el árbol en Preorden:" << endl;
            cout << "Árbol ordenado por código:" << endl;
            imprimir_PreOrden(arbolPorCodigo);
            cout << "Árbol ordenado por fecha de nacimiento:" << endl;
            imprimir_PreOrden(arbolPorFecha);
            cout << "\n";
            break;
        }
        case 5:
        {
            cout << "\nMostrando el árbol en Inorden:" << endl;
            cout << "Árbol ordenado por código:" << endl;
            imprimir_InOrden(arbolPorCodigo);
            cout << "Árbol ordenado por fecha de nacimiento:" << endl;
            imprimir_InOrden(arbolPorFecha);
            cout << "\n";
            break;
        }
        case 6:
        {
            cout << "\nMostrando el árbol en Postorden:" << endl;
            cout << "Árbol ordenado por código:" << endl;
            imprimir_PostOrden(arbolPorCodigo);
            cout << "Árbol ordenado por fecha de nacimiento:" << endl;
            imprimir_PostOrden(arbolPorFecha);
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

void insertar_Arbol(Estudiante *&arbol, Estudiante *nuevoEstudiante, bool (*comparar)(const char *, const char *))
{
    if (arbol == nullptr)
    {
        arbol = nuevoEstudiante;
    }
    else if (comparar(nuevoEstudiante->codigo_estud, arbol->codigo_estud))
    {
        insertar_Arbol(arbol->izquierda, nuevoEstudiante, comparar);
    }
    else
    {
        insertar_Arbol(arbol->derecha, nuevoEstudiante, comparar);
    }
}

bool Comparar_Por_Codigo(const char *codigo1, const char *codigo2)
{
    return strcmp(codigo1, codigo2) < 0;
}

bool Comparar_Por_Fecha(const char *fecha1, const char *fecha2)
{
    return strcmp(fecha1, fecha2) < 0;
}

void registrar_Estudiante(Estudiante *&arbolPorCodigo, Estudiante *&arbolPorFecha, Estudiante *nuevoEstudiante)
{
    insertar_Arbol(arbolPorCodigo, nuevoEstudiante, Comparar_Por_Codigo);
    Estudiante *copiaEstudiante = new Estudiante(*nuevoEstudiante);
    insertar_Arbol(arbolPorFecha, copiaEstudiante, Comparar_Por_Fecha);
}

void limpiar_Buffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void eliminar_Estudiante(Estudiante *&arbolPorCodigo, Estudiante *&arbolPorFecha, const char *codigoAEliminar)
{
    eliminar_Nodo(&arbolPorCodigo, codigoAEliminar);
    eliminar_Nodo(&arbolPorFecha, codigoAEliminar);
    cout << "Estudiante eliminado exitosamente." << endl;
}

void eliminar_Nodo(Estudiante **arbol, const char *codigoAEliminar)
{
    if (*arbol == nullptr)
    {
        return;
    }

    if (strcmp((*arbol)->codigo_estud, codigoAEliminar) == 0)
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
            strcpy((*arbol)->codigo_estud, sucesor->codigo_estud);
            eliminar_Nodo(&((*arbol)->derecha), sucesor->codigo_estud);
        }
    }
    else if (strcmp((*arbol)->codigo_estud, codigoAEliminar) > 0)
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
        cout << "Fecha de nacimiento: " << arbol->fecha_Nac << endl << endl;
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
        cout << "Fecha de nacimiento: " << arbol->fecha_Nac << endl << endl;
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
        cout << "Fecha de nacimiento: " << arbol->fecha_Nac << endl << endl;
    }
}

Estudiante *buscar_Estudiante(Estudiante *arbol, const char *codigoABuscar)
{
    if (arbol == nullptr || strcmp(arbol->codigo_estud, codigoABuscar) == 0)
    {
        return arbol;
    }

    if (strcmp(arbol->codigo_estud, codigoABuscar) > 0)
    {
        return buscar_Estudiante(arbol->izquierda, codigoABuscar);
    }
    else
    {
        return buscar_Estudiante(arbol->derecha, codigoABuscar);
    }
}

void buscar_Estudiante_Y_Mostrar(Estudiante *arbolPorCodigo, const char *codigoABuscar)
{
    Estudiante *estudianteEncontrado = buscar_Estudiante(arbolPorCodigo, codigoABuscar);
    if (estudianteEncontrado != nullptr)
    {
        cout << "Estudiante encontrado:" << endl;
        cout << "Nombre: " << estudianteEncontrado->Nombre_Apellido << endl;
        cout << "Codigo: " << estudianteEncontrado->codigo_estud << endl;
        cout << "Fecha de nacimiento: " << estudianteEncontrado->fecha_Nac << endl;
    }
    else
    {
        cout << "Estudiante con código " << codigoABuscar << " no encontrado." << endl;
    }
}
