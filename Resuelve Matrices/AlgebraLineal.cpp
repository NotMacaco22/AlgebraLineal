#include <iostream>

using namespace std;

void ImprimirMatriz(double** matriz, int filas, int columnas); //Funcion que imprime la matriz original
void EditarMatriz(double** matriz, int filas, int columnas); //Funcion que resuelve la matriz y la imprime junto a las posiciones pivote
void MostrarNumerosPivote(double** matriz, int filas, int columnas);

int main() {
    int filas, columnas;
    cout << "Ingrese el numero de filas: ";
    cin >> filas;
    
    while (filas <= 0) {
        cout << "El numero de filas debe ser mayor a cero. Ingrese nuevamente: ";
        cin >> filas;
    }

    cout << "Ingrese el numero de columnas: ";
    cin >> columnas;
    
    while (columnas <= 0) {
        cout << "El numero de columnas debe ser mayor a cero. Ingrese nuevamente: ";
        cin >> columnas;
    }

    //Se declara puntero el cual apuntara a un nuevo conjunto de punteros
    double** matriz = new double*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new double[columnas];
    } //Se crea una matriz dinamica usando punteros 

    //Nos permite ingresar numeros a la matriz
    cout << "Ingrese los numeros correspondientes a la matriz:" << endl; 
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cin >> matriz[i][j];
        }
    }

    system("cls");

    cout << "Matriz original:" << endl;
    ImprimirMatriz(matriz, filas, columnas);
    MostrarNumerosPivote(matriz, filas, columnas);
    cout << endl;

    EditarMatriz(matriz, filas, columnas);

    cout << "Matriz escalonada reducida y posiciones pivote:" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "\t";
        }
        if (i < min(filas, columnas)) { //El min demuestra el valor minimo entre dos valores (numero pivote)
            cout << "\tCoordenadas de Numero Pivote: Fila (" << i + 1 << ") Columna (" << i + 1 <<")";
        }
        cout << endl;
    }

    return 0;
}

void ImprimirMatriz(double** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; ++i) { //Imprime la matriz original - la matriz ingresada por el usuario
        for (int j = 0; j < columnas; ++j) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void MostrarNumerosPivote(double** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        bool foundPivot = false;
        for (int j = 0; j < columnas; ++j) {
            if (matriz[i][j] != 0) {
                cout << "Coordenadas de Numero Pivote: Fila (" << i + 1 << ") Columna (" << j + 1 << ")"<< endl;
                foundPivot = true;
                break; // Solo necesitas encontrar un pivote por fila
            }
        }
        if (!foundPivot) {
            cout << "No hay numero pivote en la fila " << i + 1 << endl;
        }
    }
}

void EditarMatriz(double** matriz, int filas, int columnas) { //De aqui en adelante se edita la matriz para llegar a la matiz escalonada reducida
    for (int col = 0; col < columnas && col < filas; col++) { // Encuentra la fila pivote (la que se va a editar) para la columna actual     
        int CambioFila = col;
        while (CambioFila < filas && matriz[CambioFila][col] == 0) {
            CambioFila++;
        }

        if (CambioFila < filas) { //Se verifica si se encontro la fila pivote
            if (CambioFila != col) { //Si la fila pivote no es la actual va a realizar un intercambio
                cout << "Intercambia f" << col + 1 << " con f" << CambioFila + 1 << endl;
                swap(matriz[col], matriz[CambioFila]);
            }

            //Obtenemos el valor en la columna actual
            double pivotValue = matriz[col][col];

            // Confirma que el divisor no es igual a 1 pq si no puede aparecer un mensaje de dividir entre 1
            // y asi evitamos confundir al usuario
            if (pivotValue != 1) {
                cout << "Divide f" << col + 1 << " entre " << pivotValue << endl;
                for (int k = col; k < columnas; k++) {
                    matriz[col][k] /= pivotValue;
                }
                cout << "Cambios realizados:" << endl;
                ImprimirMatriz(matriz, filas, columnas);
            }

            //la siguiente iteracion realiza la eliminacion de los numeros
            for (int row = 0; row < filas; row++) { //Itera a traves de todas las filas
                if (row != col) { //Este if nos permite que no se apliquen operaciones en la fila pivote
                    double variacion = matriz[row][col];
                    for (int k = col; k < columnas; ++k) { //Esta iteracion va a traves de las columnas del pivote (hacia la derecha)
                        matriz[row][k] -= variacion * matriz[col][k];
                    }
                    if (variacion != 0) { //Confirma si se realizo alguna operacion de eliminacion
                        //muestra el proceso de eliminacion en la terminal 
                        cout << "f" << row + 1 << " -> f" << row + 1 << " - " << variacion << " * f" << col + 1 << endl;
                        cout << "Cambios realizados:" << endl;
                        ImprimirMatriz(matriz, filas, columnas); //Imprime la matriz actualizada
                    }
                }
            }
        }
    }
}
