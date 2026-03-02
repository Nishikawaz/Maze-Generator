#include <iostream>   // Librería estándar de C++ para entrada y salida (permite usar cout y cin).
#include <vector>     // Librería que nos da acceso a "vector", una estructura dinámica similar a un arreglo.
#include <cstdlib>    // Librería que incluye funciones como atoi (convierte texto a número entero).

using namespace std;  // Permite usar nombres como cout directamente, sin escribir std::cout.

// ---------------------------------------------------------
// Función: printMaze
// Objetivo: imprimir el laberinto en la consola.
// Recibe: la matriz del laberinto, número de filas y columnas.
// ---------------------------------------------------------
void printMaze(const vector<vector<char>>& maze, int filas, int columnas) {
    // Recorremos cada fila de la matriz
    for (int i = 0; i < filas; i++) {
        // Recorremos cada columna dentro de la fila
        for (int j = 0; j < columnas; j++) {
            cout << maze[i][j];  // Imprimimos el carácter que está en esa posición
        }
        cout << "\n";  // Al terminar la fila, hacemos un salto de línea
    }
}

// ---------------------------------------------------------
// Función principal: main
// Es el punto de entrada del programa, donde todo comienza.
// ---------------------------------------------------------
int main(int argc, char* argv[]) {
    // argc = número de argumentos que recibe el programa al ejecutarse
    // argv = arreglo de cadenas (texto) con los argumentos
    // Ejemplo: si ejecutas "./laberinto 15 20"
    // argc = 3
    // argv[0] = "./laberinto"   (nombre del programa)
    // argv[1] = "15"            (primer argumento: filas)
    // argv[2] = "20"            (segundo argumento: columnas)

    // 1. Tamaño configurable
    // Si el usuario pasa argumentos, usamos esos valores.
    // Si no, usamos valores por defecto (10x10).
    int filas = (argc > 1) ? atoi(argv[1]) : 10;       // atoi convierte texto a número entero
    int columnas = (argc > 2) ? atoi(argv[2]) : 10;

    // 2. Crear matriz llena de muros
    // Creamos un "vector de vectores" de caracteres.
    // Es como una tabla de filas x columnas, inicializada con '#'.
    vector<vector<char>> maze(filas, vector<char>(columnas, '#'));

    // 3. Marcar entrada y salida
    maze[0][0] = 'E';                       // Entrada en la esquina superior izquierda
    maze[filas-1][columnas-1] = 'S';        // Salida en la esquina inferior derecha

    // 4. Visualización inicial
    cout << "Laberinto inicial:\n";         // Mensaje en consola
    printMaze(maze, filas, columnas);       // Llamamos a la función que imprime el laberinto

    return 0;  // Fin del programa, devuelve 0 indicando que todo salió bien
}
