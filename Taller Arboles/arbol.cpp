//Jeison mosquers y Daniela jaramillo



#include <iostream>
#include <cstring>
#include <limits>

    using namespace std;


struct Estudiante //modificada de muchas estructurasa una sola 
{
    char nombreComp[40];
    char codigo[40];
    char fechaDeNacimiento[40];
    Estudiante *izquierda;
    Estudiante *derecha;
};
