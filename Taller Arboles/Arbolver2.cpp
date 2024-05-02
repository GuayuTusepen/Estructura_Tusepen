//Jeison mosquers y Daniela jaramillo


#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

struct Estudiante
{
    char Nombre_Comp[40];
    char Codigo[40];
    char Fecha_Nacimiento[40];
    Estudiante *Izquierda;
    Estudiante *Derecha;
};

// metodos 
void Insertar_Arbol(Estudiante *&Arbol, Estudiante *Nuevo_Estudiante, bool (*Comparar)(const char *, const char *));
bool Comparar_Por_Codigo(const char *Codigo1, const char *Codigo2);
bool Comparar_Por_Fecha(const char *Fecha1, const char *Fecha2);
void Registrar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&Arbol_Fecha, Estudiante *Nuevo_Estudiante);
void Mostrar_Menu();
void Limpiar_Buffer();
void Eliminar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&Arbol_Fecha, const char *Codigo_Eliminar);
void Eliminar_Nodo(Estudiante **Arbol, const char *Codigo_Eliminar);
void Imprimir_PreOrden(Estudiante *Arbol);
void Imprimir_InOrden(Estudiante *Arbol);
void Imprimir_PostOrden(Estudiante *Arbol);
Estudiante *Buscar_Estudiante(Estudiante *Arbol, const char *Codigo_Buscar);
void Buscar_Estudiante_Y_Mostrar(Estudiante *Arbol_Cod, const char *Codigo_Buscar);

int main()
{
    Estudiante *Arbol_Cod = nullptr;
    Estudiante *Arbol_Fecha = nullptr;

    int Opcion;
    do
    {
        Mostrar_Menu();
        cin >> Opcion;
        Limpiar_Buffer();

        switch (Opcion)
        {
        case 1:
        {
            Estudiante *Nuevo_Estudiante = new Estudiante;
            cout << "\nIngrese el nombre completo del estudiante: ";
            cin.getline(Nuevo_Estudiante->Nombre_Comp, 40);
            cout << "Ingrese el código del estudiante: ";
            cin.getline(Nuevo_Estudiante->Codigo, 40);
            cout << "Ingrese la fecha de nacimiento del estudiante (DD/MM/AAAA): ";
            cin.getline(Nuevo_Estudiante->Fecha_Nacimiento, 40);
            Nuevo_Estudiante->Izquierda = nullptr;
            Nuevo_Estudiante->Derecha = nullptr;
            Registrar_Estudiante(Arbol_Cod, Arbol_Fecha, Nuevo_Estudiante);
            cout << "Estudiante registrado exitosamente." << endl;
            break;
        }
        case 2:
        {
            cout << "\nIngrese el codigo del estudiante a eliminar: ";
            char Codigo_Eliminar[40];
            cin.ignore();
            cin.getline(Codigo_Eliminar, 40);
            Eliminar_Estudiante(Arbol_Cod, Arbol_Fecha, Codigo_Eliminar);
            break;
        }
        case 3:
        {
            cout << "\nIngrese el codigo del estudiante a buscar: ";
            char Codigo_Buscar[40];
            cin.ignore();
            cin.getline(Codigo_Buscar, 40);
            Buscar_Estudiante_Y_Mostrar(Arbol_Cod, Codigo_Buscar);
            break;
        }
        case 4:
        {
            cout << "\nMostrando el arbol en Preorden:" << endl;
            cout << "Arbol ordenado por codigo:" << endl;
            Imprimir_PreOrden(Arbol_Cod);
            cout << "Arbol ordenado por fecha de nacimiento:" << endl;
            Imprimir_PreOrden(Arbol_Fecha);
            cout << "\n";
            break;
        }
        case 5:
        {
            cout << "\nMostrando el arbol en Inorden:" << endl;
            cout << "Arbol ordenado por codigo:" << endl;
            Imprimir_InOrden(Arbol_Cod);
            cout << "Arbol ordenado por fecha de nacimiento:" << endl;
            Imprimir_InOrden(Arbol_Fecha);
            cout << "\n";
            break;
        }
        case 6:
        {
            cout << "\nMostrando el arbol en Postorden:" << endl;
            cout << "Arbol ordenado por codigo:" << endl;
            Imprimir_PostOrden(Arbol_Cod);
            cout << "Arbol ordenado por fecha de nacimiento:" << endl;
            Imprimir_PostOrden(Arbol_Fecha);
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
    } while (Opcion != 7);

    return 0;
}

void Insertar_Arbol(Estudiante *&Arbol, Estudiante *Nuevo_Estudiante, bool (*Comparar)(const char *, const char *))
{
    if (Arbol == nullptr)
    {
        Arbol = Nuevo_Estudiante;
    }
    else if (Comparar(Nuevo_Estudiante->Codigo, Arbol->Codigo))
    {
        Insertar_Arbol(Arbol->Izquierda, Nuevo_Estudiante, Comparar);
    }
    else
    {
        Insertar_Arbol(Arbol->Derecha, Nuevo_Estudiante, Comparar);
    }
}

bool Comparar_Por_Codigo(const char *Codigo1, const char *Codigo2)
{
    return strcmp(Codigo1, Codigo2) < 0;
}

bool Comparar_Por_Fecha(const char *Fecha1, const char *Fecha2)
{
    return strcmp(Fecha1, Fecha2) < 0;
}

void Registrar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&Arbol_Fecha, Estudiante *Nuevo_Estudiante)
{
    Insertar_Arbol(Arbol_Cod, Nuevo_Estudiante, Comparar_Por_Codigo);
    Estudiante *Copia_Estudiante = new Estudiante(*Nuevo_Estudiante);
    Insertar_Arbol(Arbol_Fecha, Copia_Estudiante, Comparar_Por_Fecha);
}

void Limpiar_Buffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Eliminar_Estudiante(Estudiante *&Arbol_Cod, Estudiante *&Arbol_Fecha, const char *Codigo_Eliminar)
{
    Eliminar_Nodo(&Arbol_Cod, Codigo_Eliminar);
    Eliminar_Nodo(&Arbol_Fecha, Codigo_Eliminar);
    cout << "Estudiante eliminado exitosamente." << endl;
}

void Eliminar_Nodo(Estudiante **Arbol, const char *Codigo_Eliminar)
{
    if (*Arbol == nullptr)
    {
        return;
    }

    if (strcmp((*Arbol)->Codigo, Codigo_Eliminar) == 0)
    {
        Estudiante *Nodo_A_Eliminar = *Arbol;
        if ((*Arbol)->Izquierda == nullptr && (*Arbol)->Derecha == nullptr)
        {
            delete Nodo_A_Eliminar;
            *Arbol = nullptr;
        }
        else if ((*Arbol)->Derecha == nullptr)
        {
            *Arbol = (*Arbol)->Izquierda;
            delete Nodo_A_Eliminar;
        }
        else if ((*Arbol)->Izquierda == nullptr)
        {
            *Arbol = (*Arbol)->Derecha;
            delete Nodo_A_Eliminar;
        }
        else
        {
            Estudiante *Sucesor = (*Arbol)->Derecha;
            while (Sucesor->Izquierda != nullptr)
            {
                Sucesor = Sucesor->Izquierda;
            }
            strcpy((*Arbol)->Codigo, Sucesor->Codigo);
            Eliminar_Nodo(&((*Arbol)->Derecha), Sucesor->Codigo);
        }
    }
    else if (strcmp((*Arbol)->Codigo, Codigo_Eliminar) > 0)
    {
        Eliminar_Nodo(&((*Arbol)->Izquierda), Codigo_Eliminar);
    }
    else
    {
        Eliminar_Nodo(&((*Arbol)->Derecha), Codigo_Eliminar);
    }
}

void Imprimir_PreOrden(Estudiante *Arbol)
{
    if (Arbol != nullptr)
    {
        cout << "Nombre: " << Arbol->Nombre_Comp << endl;
        cout << "Codigo: " << Arbol->Codigo << endl;
        cout << "Fecha de nacimiento: " << Arbol->Fecha_Nacimiento << endl << endl;
        Imprimir_PreOrden(Arbol->Izquierda);
        Imprimir_PreOrden(Arbol->Derecha);
    }
}

void Imprimir_InOrden(Estudiante *Arbol)
{
    if (Arbol != nullptr)
    {
        Imprimir_InOrden(Arbol->Izquierda);
        cout << "Nombre: " << Arbol->Nombre_Comp << endl;
        cout << "Codigo: " << Arbol->Codigo << endl;
        cout << "Fecha de nacimiento: " << Arbol->Fecha_Nacimiento << endl << endl;
        Imprimir_InOrden(Arbol->Derecha);
    }
}

void Imprimir_PostOrden(Estudiante *Arbol)
{
    if (Arbol != nullptr)
    {
        Imprimir_PostOrden(Arbol->Izquierda);
        Imprimir_PostOrden(Arbol->Derecha);
        cout << "Nombre: " << Arbol->Nombre_Comp << endl;
        cout << "Codigo: " << Arbol->Codigo << endl;
        cout << "Fecha de nacimiento: " << Arbol->Fecha_Nacimiento << endl << endl;
    }
}

Estudiante *Buscar_Estudiante(Estudiante *Arbol, const char *Codigo_Buscar)
{
    if (Arbol == nullptr || strcmp(Arbol->Codigo, Codigo_Buscar) == 0)
    {
        return Arbol;
    }

    if (strcmp(Arbol->Codigo, Codigo_Buscar) > 0)
    {
        return Buscar_Estudiante(Arbol->Izquierda, Codigo_Buscar);
    }
    else
    {
        return Buscar_Estudiante(Arbol->Derecha, Codigo_Buscar);
    }
}

void Buscar_Estudiante_Y_Mostrar(Estudiante *Arbol_Cod, const char *Codigo_Buscar)
{
    Estudiante *Estudiante_Encontrado = Buscar_Estudiante(Arbol_Cod, Codigo_Buscar);
    if (Estudiante_Encontrado != nullptr)
    {
        cout << "Estudiante encontrado:" << endl;
        cout << "Nombre: " << Estudiante_Encontrado->Nombre_Comp << endl;
        cout << "Codigo: " << Estudiante_Encontrado->Codigo << endl;
        cout << "Fecha de nacimiento: " << Estudiante_Encontrado->Fecha_Nacimiento << endl;
    }
    else
    {
        cout << "Estudiante con codigo " << Codigo_Buscar << " no encontrado." << endl;
    }
}

void Mostrar_Menu()
{
    cout << "\nMenu" << endl;
    cout << "1. Registrar estudiante" << endl;
    cout << "2. Eliminar estudiante" << endl;
    cout << "3. Buscar estudiante" << endl;
    cout << "4. Mostrar en Preorden" << endl;
    cout << "5. Mostrar en Inorden" << endl;
    cout << "6. Mostrar en Postorden" << endl;
    cout << "7. Salir" << endl;
    cout << "Ingrese su opcion: ";
}
