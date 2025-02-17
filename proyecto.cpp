#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct fila_tabla {
    double limite_inferior = -1;
    double limite_superior = -1;
    double marca_clase = -1;
    double frec_absoluta = -1;
    double frec_absoluta_acum = -1;
};

//Declaracion de funciones
    void entrada_de_datos(int &N, double *lista_numeros[]);
    char regresar_al_menu();
    double redondear_entero_cercano(double &numero);

    //Calculos de datos no agrupados
        double calculo_media_no_agrupados(int &N, double lista_numeros[]); //Mario
        double calculo_mediana_no_agrupados(int &N, double lista_numeros[]); //Brandom
        double calculo_moda_no_agrupados(int &N, double lista_numeros[]); //Mau

    //Calculos de datos agrupados
        double calculo_regla_sturges(int &N); //Willy
        double calculo_amplitud_intervalo(double &dato_menor, double &dato_mayor, double &K); //Mario
        void calculo_de_intervalos(fila_tabla fila[], double &K, double &A, double &dato_menor); //Willy
        void calculo_de_marcas_de_clase(fila_tabla filas_de_tabla[], double &K); //Mau
        void calculo_de_frec_abs(fila_tabla filas_de_tabla[], double &K, double lista_numeros[], int &N); //Brandom
        void calculo_de_frec_abs_acum(fila_tabla filas_de_tabla[], double &K); //Willy
        double calculo_media_agrupados(fila_tabla filas_de_tabla[], double &K, int &N); //Mario

        int buscar_intervalo_mediana(fila_tabla filas_de_tabla[], double &K, int &N); //Brandom
        double calculo_mediana_agrupados(int &pos_interv_sup_mediana, fila_tabla filas_de_tabla[], double &K); //Brandom

        int buscar_intervalo_moda(fila_tabla filas_de_tabla[], double &K); //Mau
        double calculo_moda_agrupados(int &pos_interv_moda, fila_tabla fila_de_tabla[], double &K); //Willy

int main() {
    int opc_menu_principal;
    char opc_regresar_menu;

    int N;
    double *lista_numeros = nullptr;

    //Declaracion de variables para datos no agrupados
    double media_no_agrupados, mediana_no_agrupados, moda_no_agrupados;

    //Declaracion de variables para datos agrupados
    double media_agrupados, mediana_agrupados, moda_agrupados;
    double K, A, dato_menor, dato_mayor;
    int pos_interv_sup_mediana, pos_interv_moda;
    fila_tabla *filas_de_tabla;

    do {
        cout<<"CALCULO DE MEDIA, MEDIANA Y MODA\n\n";
        cout<<"\t--- MENU ---\n";
        cout<<"\t1. Datos no agrupados\n";
        cout<<"\t2. Datos agrupados\n";
        cout<<"\t3. Salir\n";
        cin>>opc_menu_principal;

        switch(opc_menu_principal) {

            case 1:
                //Calculos para datos no agrupados
                cout<<"Digite el numero total de datos a ingresar: ";
                cin>>N;

                lista_numeros = new double[N];
                entrada_de_datos(N, lista_numeros);

                sort(lista_numeros, lista_numeros+N);

                media_no_agrupados = calculo_media_no_agrupados(N, lista_numeros);

                mediana_no_agrupados = calculo_mediana_no_agrupados(N, lista_numeros);

                moda_no_agrupados = calculo_moda_no_agrupados(N, lista_numeros);

                cout<<"\n\t--- IMPRESION DE RESULTADOS ---\n";
                cout<<"\tMedia: "<<media_no_agrupados<<'\n';
                cout<<"\tMediana: "<<mediana_no_agrupados<<'\n';
                cout<<"\tModa: "<<moda_no_agrupados<<"\n\n";

                opc_regresar_menu = regresar_al_menu();

                if (opc_regresar_menu == 'n' || opc_regresar_menu == 'N') {
                    cout<<"Saliendo...\n\n";
                    system("pause");

                    opc_menu_principal = 3;
                }

                break;

            case 2:
                //Calculos para datos agrupados
                cout<<"Digite el numero total de datos a ingresar: ";
                cin>>N;

                lista_numeros = new double[N];
                entrada_de_datos(N, lista_numeros);

                sort(lista_numeros, lista_numeros+N);

                dato_menor = lista_numeros[0];
                dato_mayor = lista_numeros[N-1];

                K = calculo_regla_sturges(N);
                K = redondear_entero_cercano(K);

                A = calculo_amplitud_intervalo(dato_menor, dato_mayor, K);
                A = redondear_entero_cercano(A);

                filas_de_tabla = new fila_tabla[K];

                calculo_de_intervalos(filas_de_tabla, K, A, dato_menor);

                calculo_de_marcas_de_clase(filas_de_tabla, K);

                calculo_de_frec_abs(filas_de_tabla, K, lista_numeros, N);
                calculo_de_frec_abs_acum(filas_de_tabla, K);

                media_agrupados = calculo_media_agrupados(filas_de_tabla, K, N);

                pos_interv_sup_mediana = buscar_intervalo_mediana(filas_de_tabla, K, N);
                mediana_agrupados = calculo_mediana_agrupados(pos_interv_sup_mediana, filas_de_tabla, K);

                pos_interv_moda = buscar_intervalo_moda(filas_de_tabla, K);
                moda_agrupados = calculo_moda_agrupados(pos_interv_moda, filas_de_tabla, K);

                cout<<"\n\t--- IMPRESION DE RESULTADOS ---\n";
                cout<<"\tMedia: "<<media_agrupados<<'\n';
                cout<<"\tMediana: "<<mediana_agrupados<<'\n';
                cout<<"\tModa: "<<moda_agrupados<<"\n\n";

                opc_regresar_menu = regresar_al_menu();

                if (opc_regresar_menu == 'n' || opc_regresar_menu == 'N') {
                    cout<<"Saliendo...\n\n";
                    system("pause");

                    opc_menu_principal = 3;
                }

                delete [] filas_de_tabla;
                break;

            case 3:
                cout<<"Saliendo...\n\n";
                system("pause");

                break;

            default:
                lista_numeros = nullptr;

                system("cls");
                cout<<"Ingreso una opcion invalida, digite otra...\n";
                system("pause");
        }

        if (lista_numeros != nullptr) {
            delete [] lista_numeros;
            lista_numeros = nullptr;
        }

        system("cls");
    }while (opc_menu_principal != 3);

    return 0;
}

//Definicion de funciones
void entrada_de_datos(int N, double lista_numeros[]) {
    for (int i=0; i<N; i++) {
        cout<<"Dato numero: "<<i+1<<": ";
        cin>>lista_numeros[i];
    }
}

char regresar_al_menu() {
    char res;

    do {
        cout<<"Desea volver al menu? (s/n): ";
        cin>>res;

        if (res != 's' && res != 'S' && res != 'n' && res != 'N') cout<<"\n\tDigito una opcion invalida, intente de nuevo...\n\n";
    }while(res != 's' && res != 'S' && res != 'n' && res != 'N');

    return res;
}

double redondear_entero_cercano(double &numero) {
    double numero_inferior, numero_superior, redondeado, mitad;

    numero_inferior = floor(numero);
    numero_superior = ceil(numero);

    if (numero_inferior == numero_superior) redondeado = numero; //Significa que es entero
    else {
        mitad = (numero_inferior + numero_superior) / 2;

        if (numero >= mitad) redondeado = numero_superior;
        else redondeado = numero_inferior;
    }

    return redondeado;
}

//Calculos de datos no agrupados
double calculo_media_agrupados(int &N, double lista_numeros[]) {

}

//Calculos de datos agrupados

