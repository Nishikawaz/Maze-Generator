// Librerías
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;

// Constantes para las celdas
const int MURO = 0;
const int CAMINO = 1;
const int ENTRADA = 2;
const int SALIDA = 3;
const int RECORRIDO = 4;

// Constante de valor referencial/centinela
const pair<int, int> SIN_PADRE = {-1,-1};

// Generación del tablero lleno de muros (Matriz compacta)
vector<vector<int>> crear_tablero(int filas, int columnas){
    return vector<vector<int>>(filas, vector<int>(columnas, MURO));
}

// Impresión de cada posición del tablero (Citado nombre --> valor)
void imprimir_tablero(const vector<vector<int>>& tablero){
    for(int i=0; i<tablero.size(); i++){
        for(int j=0; j<tablero[i].size(); j++){
            if (tablero[i][j] == MURO)cout<< "#";
            else if(tablero[i][j] == CAMINO)cout<< ".";
            else if(tablero[i][j] == ENTRADA)cout<< "E";
            else if (tablero[i][j] == SALIDA)cout<< "S";
            else if (tablero[i][j] == RECORRIDO)cout<< "*";
       
        }
        cout<<"\n";
    }
}

// DFS recursivo para ir "rompiendo" # e ir carvando los futuros caminos.
void generador_dfs(vector<vector<int>>&tablero, int x, int y){

    // Posibles direcciones
    vector<pair<int,int>> direcciones = {{-2,0},{2,0},{0,-2},{0,2}};

    // Randomizar las direcciones
    random_device rd;
    mt19937 g(rd());
    shuffle(direcciones.begin(), direcciones.end(), g);

    // Exploración de los movimientos
    for(pair<int,int> movimientos : direcciones){
        int dx = movimientos.first;
        int dy = movimientos.second;
        // Para la nueva pos
        int nueva_x = x + dx;
        int nueva_y = y + dy;

        // Verificación de las dimensiones del tablero
        if((nueva_x > 0 && nueva_x < tablero.size()-1) && (nueva_y > 0 && nueva_y < tablero[0].size()-1)){

            if(tablero[nueva_x][nueva_y] == MURO){          //Verifica si la nueva pos es un muro.
                tablero[x+(dx/2)][y+(dy/2)] = CAMINO;       //A la celda intermedia la vuelve del valor de camino.
                tablero[nueva_x][nueva_y] = CAMINO;         //A la celda destino la vuelve del valor del camino.
                generador_dfs(tablero, nueva_x, nueva_y);   //Backtracking de post-procesamiento (recursivo).
            }
        }

    }

}

// Resolver laberinto con BFS
bool resolucion_bfs(vector<vector<int>>&tablero, int entrada_x, int entrada_y, int salida_x, int salida_y){
    int filas = tablero.size();
    int columnas = tablero[0].size();

    // Movimientos posibles
    vector<pair<int, int>> direcciones;
    direcciones.push_back(make_pair(-1,0)); //arriba
    direcciones.push_back(make_pair(1,0));  //abajo
    direcciones.push_back(make_pair(0,-1)); //izquierda
    direcciones.push_back(make_pair(0,1));  //derecha

    // Matriz para marcar visitados
    vector<vector<bool>> visitado(filas, vector<bool>(columnas, false));

    // Matriz para guardar el padre de cada celda (Reconstrucción del camino)
    vector<vector<pair<int, int>>> padre(filas, vector<pair<int, int>>(columnas, SIN_PADRE));

    // Cola para BFS 
    queue<pair<int,int>> cola;
    cola.push(make_pair(entrada_x, entrada_y)); //Se encola la entrada.
    visitado[entrada_x][entrada_y] = true;      //Se marca la entrada como visitada.

    // Aplicación del FIFO
    while(!cola.empty()){ 
        pair<int, int> celda = cola.front(); //Se toma la primera celda de la cola.
        cola.pop();                          //Se saca de la cola.
        int celda_x = celda.first;
        int celda_y = celda.second;

        // Si llegamos a la salida 
        if(celda_x == salida_x && celda_y == salida_y){
            while(!(celda_x == entrada_x && celda_y == entrada_y)){
                tablero[celda_x][celda_y] = RECORRIDO;
                pair<int, int> padreCelda = padre[celda_x][celda_y];
                celda_x = padreCelda.first;
                celda_y = padreCelda.second;
            }
            return true; // Camino encontrado
        }
        
        // Explorar celdas vecinas (adyacentes)
        for(size_t i=0; i<direcciones.size(); i++){
            int direccion_x = direcciones[i].first;  //Filas
            int direccion_y = direcciones[i].second; //Columnas
            int nueva_pos_x = celda_x + direccion_x;
            int nueva_pos_y = celda_y + direccion_y;

            // Verificación de límites y condiciones
            if((nueva_pos_x >= 0 && nueva_pos_x <filas) && (nueva_pos_y >= 0 && nueva_pos_y < columnas)){
                // Indicación si NO fue visitado y sea transitable
                if(!visitado[nueva_pos_x][nueva_pos_y] && ((tablero[nueva_pos_x][nueva_pos_y] == CAMINO) || tablero[nueva_pos_x][nueva_pos_y] == SALIDA)){ 
                    visitado[nueva_pos_x][nueva_pos_y] = true;                                      
                    padre[nueva_pos_x][nueva_pos_y] = make_pair(celda_x, celda_y);
                    cola.push(make_pair(nueva_pos_x, nueva_pos_y));
                }
            }
        }

    }
    return false; // No hay caminos
}

int main(){
    int filas, columnas;

    // Pedir dimensiones al usuario
    cout << "Ingrese el numero de filas (minimo 5): ";
    cin >> filas;
    cout << "Ingrese el numero de columnas (minimo 5): ";
    cin >> columnas;

    // Validación: no permitir valores menores a 5
    if(filas < 5 || columnas < 5){
        cout << "Error: las dimensiones deben ser al menos 5x5.\n";
        return 1;
    }

    // Ajustar a impares si el usuario da pares
    if(filas % 2 == 0) {
        filas++;
    }
    if(columnas % 2 == 0) {
        columnas++;
    }

    // Crear tablero
    auto tablero = crear_tablero(filas, columnas);

    // Medir tiempo de generación (DFS)
    auto inicio_generacion = chrono::high_resolution_clock::now();
    tablero[1][1] = CAMINO;
    generador_dfs(tablero, 1, 1);
    auto fin_generacion = chrono::high_resolution_clock::now();
    auto duracion_generacion = chrono::duration_cast<chrono::microseconds>(fin_generacion - inicio_generacion).count();

    // Definir entrada y salida
    tablero[1][1] = ENTRADA;
    tablero[filas-2][columnas-2] = SALIDA;

    cout << "\nLaberinto generado:\n";
    imprimir_tablero(tablero);
    cout << "Tiempo de generacion: " << duracion_generacion << " microsegundos\n";

    // Medir tiempo de resolución (BFS)
    auto inicio_resolucion = chrono::high_resolution_clock::now();
    bool encontrado = resolucion_bfs(tablero, 1, 1, filas-2, columnas-2);
    auto fin_resolucion = chrono::high_resolution_clock::now();
    auto duracion_resolucion = chrono::duration_cast<chrono::microseconds>(fin_resolucion - inicio_resolucion).count();

    if(encontrado){
    cout << "\nCamino encontrado:\n";
    imprimir_tablero(tablero);
    } else {
    cout << "\nNo hay camino.\n";
    }
    cout << "Tiempo de resolucion: " << duracion_resolucion << " microsegundos\n";

    return 0;
}
