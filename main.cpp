#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;


const int CANT_CATEGORIAS = 20;


struct Componente {
    int id;                 
    char tipo[50];          
    int cod_categoria;      
    char modelo[50];        
    char marca[50];         
    int consumoWatts;       
};

struct NodoComponente {
    Componente info;        
    NodoComponente* sgte;   
};



void inicializarVector(NodoComponente* vectorCategorias[]);
void generarArchivoPrueba();
void liberarMemoria(NodoComponente* vectorCategorias[]);
int desplegarMenu();

void cargarYProcesarDatos(NodoComponente* vectorCategorias[]);
void insertarOrdenado(NodoComponente*& lista, Componente comp);

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
                cout << "\n>>> Carga y Procesamiento de Datos <<<\n";
                cargarYProcesarDatos(vectorCategorias);
                break;
            case 2:
                cout << "\n>>> Reporte de Resultados Estadisticos <<<\n";
                mostrarResultados(vectorCategorias);
                break;
            case 3:
                cout << "\nSaliendo del sistema... Liberando recursos...\n";
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
    cout << "[SISTEMA] Archivo 'COMPONENTES.DAT' preparado con exito.\n";
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
    cout << "[SISTEMA] Memoria liberada correctamente.\n";
}

void cargarYProcesarDatos(NodoComponente* vectorCategorias[]) {
   
}

void insertarOrdenado(NodoComponente*& lista, Componente comp) {

}

void mostrarResultados(NodoComponente* vectorCategorias[]) {

}
