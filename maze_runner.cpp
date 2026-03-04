/*
Estructura del código

LIBRERÍAS

using namespace std;

ANTES DEL MAIN
-Funciones para llamar en el main:
-Generador del tablero #
-Función de impresión del tablero compacto
-Lógica de corte de # del DFS
-Backtracking recursivo del DFS


MAIN
-Input
-Output
-Orquestador
-Timer de generación
-Timer de resolución
-Return 0;
*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> crear_tablero(int filas, int columnas){
    vector<vector<int>> tablero(filas, vector<int>(columnas, 0));
    return tablero;
}

void colocar_inicio_y_fin(vector<vector<int>>&tablero, int filas, int columnas){
    tablero[0][0] = 1;
    tablero[filas-1][columnas-1] = 2;
}

void imprimir_tablero(vector<vector<int>>&tablero, int filas, int columnas){
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            if(tablero[i][j] == 2)cout<< "S";
            else if(tablero[i][j] == 1)cout<< "E";
            else cout<< "#";
       
        }
        cout<<"\n";
    }
}

int main(){

    int filas = 10;
    int columnas = 10; 

    vector<vector<int>> tablero = crear_tablero(filas, columnas); 

    colocar_inicio_y_fin(tablero, filas, columnas);

    cout << "Valor en tablero[9][9]: " << tablero[9][9] << endl;

    imprimir_tablero(tablero, filas, columnas); 

    return 0;
}
