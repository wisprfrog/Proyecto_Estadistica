#include <iostream> 
#include <algorithm>
#include <cmath>
#include <map>

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
        double calculo_media_no_agrupados(int &N, double lista_numeros[]); //Brandom
        double calculo_mediana_no_agrupados(int &N, double lista_numeros[]); //Brandom
        double calculo_moda_no_agrupados(int &N, double lista_numeros[]); //Mau

    //Calculos de datos agrupados
        double calculo_regla_sturges(int &N); //Willy
        double calculo_amplitud_intervalo(double &dato_menor, double &dato_mayor, double &K); //Brandom
        void calculo_de_intervalos(fila_tabla fila[], double &K, double &A, double &dato_menor); //Willy
        void calculo_de_marcas_de_clase(fila_tabla filas_de_tabla[], double &K); //Mau
        void calculo_de_frec_abs(fila_tabla filas_de_tabla[], double &K, double lista_numeros[], int &N); //Brandom
        void calculo_de_frec_abs_acum(fila_tabla filas_de_tabla[], double &K); //Willy
        double calculo_media_agrupados(fila_tabla filas_de_tabla[], double &K, int &N); //Brandom

        int buscar_intervalo_mediana(fila_tabla filas_de_tabla[], double &K, int &N); //Brandom
        double calculo_mediana_agrupados(int &interv_mediana, fila_tabla filas_de_tabla[], double &K, int &N); //Brandom

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
    int interv_mediana, pos_interv_moda;
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

                interv_mediana = buscar_intervalo_mediana(filas_de_tabla, K, N);
                mediana_agrupados = calculo_mediana_agrupados(interv_mediana, filas_de_tabla, K, N);

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
double calculo_media_no_agrupados(int &N, double lista_numeros[]){//Brandom
    double media = 0;

    for(int i = 0; i<N; i++) media += lista_numeros[i];

    media /= N;

    return media;
}

double calculo_mediana_no_agrupados(int &N, double lista_numeros[]){//Brandom
    int mitad = N/2;
    
    double mediana = lista_numeros[mitad];

    return mediana;
} 

double calculo_moda_no_agrupados(int &N, double lista_numeros[]){//Mau
    //Se utilizó el algoritmo counting sort para el cálculo de la moda
    
    // map<tipo de indice, tipo de valor a almacenar>
    map<double, int> conteo; //Valor de la lista, su conteo (int)

    //nombre_mapa[valor_a_incrementar]++;
    double numero;
    for(int i=0; i < N; i++){
        numero = lista_numeros[i];
        conteo[numero]++;
    }

    //8 9 10 8 9 1 2
    //2 2 1      1 1

    double valor_mayor = -1;
    int repeticiones = INT_MIN; 

    //{indice, valor}
    //{first, second}
    for(auto valor : conteo){
        if(valor.second > repeticiones){
            valor_mayor = valor.first;
            repeticiones = valor.second;
        }
    }  

    return valor_mayor;
} 

//Calculos de datos agrupados
double calculo_regla_sturges(int &N){ //Willy
    double ret = 1 + 3.322*log10(N);

    return ret;
}

double calculo_amplitud_intervalo(double &dato_menor, double &dato_mayor, double &K){//Brandom
    double A = (dato_mayor - dato_menor) / K;

    return A;
}

void calculo_de_intervalos(fila_tabla fila[], double &K, double &A, double &dato_menor){//Willy
    fila[0].limite_inferior = dato_menor - 1.0;     ///Se modifica el arreglo de la estructura directamente
    fila[0].limite_superior = fila[0].limite_inferior + A;

    //Esta 1-indexado porque ya se hicieron los calculos para la primera fila 0
    for(int i = 1; i < K; i++){     
        fila[i].limite_inferior = fila[i-1].limite_superior + 1.0; ///Limite de la fila anterior + 1
        fila[i].limite_superior = fila[i].limite_inferior + A;
    }
} 

void calculo_de_marcas_de_clase(fila_tabla filas_de_tabla[], double &K){ //Mau
    for(int i = 0; i < K; i++){
        filas_de_tabla[i].marca_clase = (filas_de_tabla[i].limite_superior+filas_de_tabla[i].limite_inferior)/2;
    }
}
 
void calculo_de_frec_abs(fila_tabla filas_de_tabla[], double &K, double lista_numeros[], int &N){//Brandom
    int guardar_en_intervalo = 0;

    double lim_inf_actual = filas_de_tabla[guardar_en_intervalo].limite_inferior;
    double lim_sup_actual = filas_de_tabla[guardar_en_intervalo].limite_superior;

    double num_auxiliar;
    for(int i=0; i < K;i ++){
        num_auxiliar = lista_numeros[i];
        
        if(num_auxiliar < lim_inf_actual || num_auxiliar > lim_sup_actual){
            guardar_en_intervalo++;
            lim_inf_actual = filas_de_tabla[guardar_en_intervalo].limite_inferior;
            lim_sup_actual = filas_de_tabla[guardar_en_intervalo].limite_superior;
        }

        filas_de_tabla[guardar_en_intervalo].frec_absoluta++;
    }
}

void calculo_de_frec_abs_acum(fila_tabla filas_de_tabla[], double &K){//Willy
    filas_de_tabla[0].frec_absoluta_acum = filas_de_tabla[0].frec_absoluta;

    for(int i = 1; i < K; i++){
        filas_de_tabla[i].frec_absoluta_acum = filas_de_tabla[i].frec_absoluta + filas_de_tabla[i-1].frec_absoluta_acum;
        //sumatoria de frecuencias anteriores + frec actual
    }
} 

double calculo_media_agrupados(fila_tabla filas_de_tabla[], double &K, int &N){//Brandom
    double media = 0;
    for(int i=0; i < K; i++) media += filas_de_tabla[i].marca_clase * filas_de_tabla[i].frec_absoluta;

    media /= N;

    return media;
}    

int buscar_intervalo_mediana(fila_tabla filas_de_tabla[], double &K, int &N){//Brandom
    double posible_mediana = N/2;
    int lim_superior = 1;

    int intervalo_mediana = 0;
    while(filas_de_tabla[intervalo_mediana].frec_absoluta_acum < posible_mediana) intervalo_mediana++;

    return intervalo_mediana;
}

double calculo_mediana_agrupados(int &interv_mediana, fila_tabla filas_de_tabla[], double &K, int &N){//Brandom
    double mediana;
    double frec_abs_acum_anterior = filas_de_tabla[interv_mediana - 1].frec_absoluta_acum;
    double frec_abs_mediana = filas_de_tabla[interv_mediana].frec_absoluta;
    double limite_superior = filas_de_tabla[interv_mediana].limite_superior;
    double limite_inferior = filas_de_tabla[interv_mediana].limite_inferior;
    
    mediana = ((N/2) - frec_abs_acum_anterior) / frec_abs_mediana;
    mediana *= (limite_superior - limite_inferior);

    mediana += limite_inferior;

    return mediana;
}

int buscar_intervalo_moda(fila_tabla filas_de_tabla[], double &K){ //Mau
    int posicion, frec_max = INT_MIN;
    for(int i = 0; i < K; i++){
        if(filas_de_tabla[i].frec_absoluta > frec_max){
            frec_max = filas_de_tabla[i].frec_absoluta;
            posicion = i;
        }
    }
    return posicion;
}

double calculo_moda_agrupados(int &pos_interv_moda, fila_tabla fila_de_tabla[], double &K){//Willy
    double delta_1, delta_2, moda;

    delta_1 = fila_de_tabla[pos_interv_moda].frec_absoluta - fila_de_tabla[pos_interv_moda - 1].frec_absoluta; //nj - nj-1
    delta_2 = fila_de_tabla[pos_interv_moda].frec_absoluta - fila_de_tabla[pos_interv_moda + 1].frec_absoluta; //nj - nj+1

    moda = fila_de_tabla[pos_interv_moda].limite_inferior;  //Se divide la formula en 2 partes, solo por comodidad
    moda += ((delta_1 / (delta_1 + delta_2)) * (fila_de_tabla[pos_interv_moda].limite_superior - fila_de_tabla[pos_interv_moda].limite_inferior));

    return moda;
}
