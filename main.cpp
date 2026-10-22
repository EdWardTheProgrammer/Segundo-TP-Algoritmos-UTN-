#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define CANT_CATEGORIAS 20

struct Componente {
    int  id;
    char tipo[51];
    int  codCategoria;
    char modelo[51];
    char fabricante[51];
    int  consumoWatts;
};

struct NodoComponente {
    Componente      info;
    NodoComponente* sgte;
};

bool insertarOrdenado(NodoComponente*& lista, const Componente& dato)
{
    NodoComponente* ant = NULL;
    NodoComponente* act = lista;

    while (act != NULL && act->info.id < dato.id) {
        ant = act;
        act = act->sgte;
    }

    if (act != NULL && act->info.id == dato.id)
        return false;

    NodoComponente* nuevo = new NodoComponente;
    nuevo->info = dato;
    nuevo->sgte = act;

    if (ant == NULL)
        lista = nuevo;
    else
        ant->sgte = nuevo;

    return true;
}

int cargarDatos(NodoComponente* vectorCategorias[], const char* nombreArchivo)
{
    FILE* f = fopen(nombreArchivo, "rb");
    if (f == NULL) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return -1;
    }

    Componente c;
    int insertados = 0, descartados = 0;

    while (fread(&c, sizeof(Componente), 1, f) == 1) {
        if (c.codCategoria < 0 || c.codCategoria >= CANT_CATEGORIAS) {
            descartados++;
            continue;
        }
        if (insertarOrdenado(vectorCategorias[c.codCategoria], c))
            insertados++;
        else
            descartados++;
    }

    fclose(f);
    cout << "Insertados: " << insertados
         << " | Descartados: " << descartados << endl;
    return insertados;
}
