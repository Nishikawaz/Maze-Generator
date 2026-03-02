#include <iostream> // Librería estándar de C++ para entrada y salida (permite usar cout y cin).
#include <vector> // Librería que permite acceder a "vector", una estructura dinámica similar a un arreglo.
#include <cstdlib> // Librería que incluye funciones como atoi (convierte texto a número entero).

using namespace std; // Permite usar funciones cout directamene, sin escribir std::cout

void printMaze(const vector<vector<char>>&maze, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j= 0; j < columnas; j++) {
            cout << maze[i][j];
        }
        cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    int filas = (argc > 1) ? atoi(argv[1]): 10;
    int columnas = (argc > 2) ? atoi(argv[2]): 10;

    vector<vector<char>> maze(filas, vector<char>(columnas, '#'));

    maze[0][0] = 'E';
    maze[filas-1][columnas-1] = 'S';

    cout << "Laberinto inicial: \n";
    printMaze(maze, filas, columnas);

    return 0;
}
