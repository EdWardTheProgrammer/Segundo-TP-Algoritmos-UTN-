#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int CANT_CATEGORIAS = 20;

struct Componente {
    int id;                 
    char tipo[51];          
    int cod_categoria;      
    char modelo[51];        
    char marca[51];         
    int consumoWatts;       
};

struct NodoComponente {
    Componente info;        
    NodoComponente* sgte;   
};

// Prototipos
void inicializarVector(NodoComponente* vectorCategorias[]);
void generarArchivoPrueba();
void liberarMemoria(NodoComponente* vectorCategorias[]);
int desplegarMenu();

void cargarYProcesarDatos(NodoComponente* vectorCategorias[]);
bool insertarOrdenado(NodoComponente*& lista, const Componente& dato);
void mostrarResultados(NodoComponente* vectorCategorias[]);

int main() {
    NodoComponente* vectorCategorias[CANT_CATEGORIAS];

    inicializarVector(vectorCategorias);
    generarArchivoPrueba();

    int opcion;
    do {
        opcion = desplegarMenu(); 

        switch (opcion) {
            case 1:
                cout << "\nCarga y Procesamiento de Datos\n";
                cargarYProcesarDatos(vectorCategorias);
                break;
            case 2:
                cout << "\nReporte de Resultados Estadisticos\n";
                mostrarResultados(vectorCategorias);
                break;
            case 3:
                cout << "\nSaliendo del sistema y liberando recursos.\n";
                liberarMemoria(vectorCategorias);
                break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo.\n";
        }
        cout << endl;
    } while (opcion != 3);

    return 0;
}

void inicializarVector(NodoComponente* vectorCategorias[]) {
    for (int i = 0; i < CANT_CATEGORIAS; i++) {
        vectorCategorias[i] = NULL;
    }
}

void generarArchivoPrueba() {
    FILE* arch = fopen("COMPONENTES.DAT", "wb"); 
    if (arch == NULL) {
        cout << "Error al intentar crear el archivo de prueba.\n";
        return;
    }

    Componente listaPrueba[] = {
        {105, "GPU", 1, "RTX 3080", "Nvidia", 320},
        {101, "CPU", 0, "Core i7", "Intel", 125},
        {108, "Fuente", 4, "RM850x", "Corsair", 850},
        {102, "CPU", 0, "Ryzen 5", "AMD", 65},
        {104, "GPU", 1, "RX 6700XT", "AMD", 230},
        {103, "RAM", 3, "Vengeance 16GB", "Corsair", 15}
    };

    int cantidad = sizeof(listaPrueba) / sizeof(Componente);

    fwrite(listaPrueba, sizeof(Componente), cantidad, arch);

    fclose(arch);
    cout << "SISTEMA: el archivo 'COMPONENTES.DAT' esta preparado con exito.\n";
}

int desplegarMenu() {
    int op;
    cout << "===============================================\n";
    cout << "  AUDITORIA DE INFRAESTRUCTURAS TECNOLOGICAS   \n";
    cout << "===============================================\n";
    cout << "1. Cargar y procesar datos de componentes\n";
    cout << "2. Mostrar resultados\n"; 
    cout << "3. Salir\n"; 
    cout << "Seleccione una opcion: ";
    cin >> op;
    return op;
}

void liberarMemoria(NodoComponente* vectorCategorias[]) {
    for (int i = 0; i < CANT_CATEGORIAS; i++) {
        NodoComponente* actual = vectorCategorias[i];
        while (actual != NULL) {
            NodoComponente* aux = actual;
            actual = actual->sgte;
            delete aux; 
        }
        vectorCategorias[i] = NULL; 
    }
    cout << "SISTEMA: Memoria liberada correctamente.\n";
}

bool insertarOrdenado(NodoComponente*& lista, const Componente& dato) {
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

void cargarYProcesarDatos(NodoComponente* vectorCategorias[]) {
    FILE* f = fopen("COMPONENTES.DAT", "rb");
    if (f == NULL) {
        cout << "No se pudo abrir el archivo: COMPONENTES.DAT\n";
        return;
    }

    Componente c;
    int insertados = 0, descartados = 0;

    while (fread(&c, sizeof(Componente), 1, f) == 1) {
        if (c.cod_categoria < 0 || c.cod_categoria >= CANT_CATEGORIAS) {
            descartados++;
            continue;
        }
        if (insertarOrdenado(vectorCategorias[c.cod_categoria], c))
            insertados++;
        else
            descartados++;
    }

    fclose(f);
    cout << "Insertados: " << insertados
         << " | Descartados: " << descartados << endl;
}

void mostrarResultados(NodoComponente* vectorCategorias[]) {
    // Pendiente de implementacion
}
