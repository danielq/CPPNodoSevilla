/*
 * Ejercicio 7: Funciones en C++
 * 
 * Objetivos:
 * - Aprender a declarar y definir funciones
 * - Entender parámetros y valores de retorno
 * - Practicar sobrecarga de funciones
 * - Aprender sobre scope y variables locales
 */

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ===== DECLARACIONES DE FUNCIONES =====

// Función simple sin parámetros
void saludar();

// Función con parámetros
void mostrarInformacion(string nombre, int edad);

// Función con valor de retorno
int sumar(int a, int b);

// Función con múltiples valores de retorno (usando referencias)
void calcularEstadisticas(int numeros[], int tamano, double& promedio, int& maximo, int& minimo);

// Función con parámetros por defecto
void imprimirMensaje(string mensaje = "Hola", int veces = 1);

// Función recursiva
int factorial(int n);

// Función inline
inline int cuadrado(int x) { return x * x; }

// Función con parámetros constantes
double calcularArea(const double& radio);

// ===== IMPLEMENTACIÓN DE FUNCIONES =====

void saludar() {
    cout << "   ¡Hola desde la función saludar()!\n";
}

void mostrarInformacion(string nombre, int edad) {
    cout << "   Nombre: " << nombre << "\n";
    cout << "   Edad: " << edad << " años\n";
    cout << "   Años para jubilación: " << (65 - edad) << "\n";
}

int sumar(int a, int b) {
    return a + b;
}

void calcularEstadisticas(int numeros[], int tamano, double& promedio, int& maximo, int& minimo) {
    if (tamano <= 0) return;
    
    // Inicializar valores
    maximo = minimo = numeros[0];
    int suma = numeros[0];
    
    // Calcular suma, máximo y mínimo
    for (int i = 1; i < tamano; i++) {
        suma += numeros[i];
        if (numeros[i] > maximo) maximo = numeros[i];
        if (numeros[i] < minimo) minimo = numeros[i];
    }
    
    promedio = (double)suma / tamano;
}

void imprimirMensaje(string mensaje, int veces) {
    for (int i = 0; i < veces; i++) {
        cout << "   " << mensaje << "\n";
    }
}

int factorial(int n) {
    // Caso base
    if (n <= 1) return 1;
    
    // Caso recursivo
    return n * factorial(n - 1);
}

double calcularArea(const double& radio) {
    return M_PI * radio * radio;
}

// ===== SOBRECARGA DE FUNCIONES =====

// Diferentes versiones de la función sumar
int sumar(int a, int b, int c) {
    return a + b + c;
}

double sumar(double a, double b) {
    return a + b;
}

string sumar(string a, string b) {
    return a + " " + b;
}

// ===== FUNCIONES TEMPLATE =====

template<typename T>
T obtenerMaximo(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
void intercambiar(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// ===== FUNCIÓN PRINCIPAL =====

int main() {
    cout << "=== EJERCICIO 7: FUNCIONES EN C++ ===\n\n";
    
    // ===== PARTE 1: FUNCIONES SIMPLES =====
    cout << "1. FUNCIONES SIMPLES:\n";
    
    saludar();
    mostrarInformacion("Ana García", 28);
    cout << "\n";
    
    // ===== PARTE 2: FUNCIONES CON VALOR DE RETORNO =====
    cout << "2. FUNCIONES CON VALOR DE RETORNO:\n";
    
    int resultado = sumar(15, 25);
    cout << "   Suma de 15 + 25 = " << resultado << "\n";
    
    double area = calcularArea(5.0);
    cout << "   Área del círculo con radio 5 = " << area << "\n";
    
    int numeroCuadrado = cuadrado(8);
    cout << "   Cuadrado de 8 = " << numeroCuadrado << "\n\n";
    
    // ===== PARTE 3: SOBRECARGA DE FUNCIONES =====
    cout << "3. SOBRECARGA DE FUNCIONES:\n";
    
    cout << "   Suma de enteros (2, 3): " << sumar(2, 3) << "\n";
    cout << "   Suma de enteros (2, 3, 4): " << sumar(2, 3, 4) << "\n";
    cout << "   Suma de doubles (2.5, 3.7): " << sumar(2.5, 3.7) << "\n";
    cout << "   Suma de strings: " << sumar("Hola", "Mundo") << "\n\n";
    
    // ===== PARTE 4: FUNCIONES TEMPLATE =====
    cout << "4. FUNCIONES TEMPLATE:\n";
    
    cout << "   Máximo entre 10 y 20: " << obtenerMaximo(10, 20) << "\n";
    cout << "   Máximo entre 3.14 y 2.71: " << obtenerMaximo(3.14, 2.71) << "\n";
    cout << "   Máximo entre 'A' y 'Z': " << obtenerMaximo('A', 'Z') << "\n";
    
    int x = 10, y = 20;
    cout << "   Antes del intercambio: x = " << x << ", y = " << y << "\n";
    intercambiar(x, y);
    cout << "   Después del intercambio: x = " << x << ", y = " << y << "\n\n";
    
    // ===== PARTE 5: FUNCIONES CON REFERENCIAS =====
    cout << "5. FUNCIONES CON REFERENCIAS:\n";
    
    int numeros[] = {15, 8, 23, 7, 19, 12};
    int tamano = sizeof(numeros) / sizeof(numeros[0]);
    
    cout << "   Array: ";
    for (int i = 0; i < tamano; i++) {
        cout << numeros[i] << " ";
    }
    cout << "\n";
    
    double promedio;
    int maximo, minimo;
    
    calcularEstadisticas(numeros, tamano, promedio, maximo, minimo);
    
    cout << "   Promedio: " << promedio << "\n";
    cout << "   Máximo: " << maximo << "\n";
    cout << "   Mínimo: " << minimo << "\n\n";
    
    // ===== PARTE 6: FUNCIONES RECURSIVAS =====
    cout << "6. FUNCIONES RECURSIVAS:\n";
    
    int n = 5;
    cout << "   Factorial de " << n << " = " << factorial(n) << "\n";
    
    // Mostrar el proceso del factorial
    cout << "   Proceso: ";
    for (int i = n; i >= 1; i--) {
        cout << i;
        if (i > 1) cout << " × ";
    }
    cout << " = " << factorial(n) << "\n\n";
    
    // ===== PARTE 7: FUNCIONES CON PARÁMETROS POR DEFECTO =====
    cout << "7. FUNCIONES CON PARÁMETROS POR DEFECTO:\n";
    
    imprimirMensaje();  // Usa valores por defecto
    cout << "\n";
    
    imprimirMensaje("¡Hola C++!", 3);  // Especifica ambos parámetros
    cout << "\n";
    
    imprimirMensaje("Programación");  // Solo especifica el mensaje
    cout << "\n";
    
    // ===== PARTE 8: SCOPE Y VARIABLES LOCALES =====
    cout << "8. SCOPE Y VARIABLES LOCALES:\n";
    
    {
        int variableLocal = 100;
        cout << "   Variable local en bloque: " << variableLocal << "\n";
    }
    
    // cout << variableLocal;  // Esto causaría un error de compilación
    
    // Variable global del main
    int variableMain = 200;
    cout << "   Variable del main: " << variableMain << "\n\n";
    
    // ===== PARTE 9: EJERCICIO INTERACTIVO =====
    cout << "9. EJERCICIO INTERACTIVO - CALCULADORA AVANZADA:\n";
    
    int opcion;
    do {
        cout << "   Menú de operaciones:\n";
        cout << "   1 - Calcular factorial\n";
        cout << "   2 - Calcular área de círculo\n";
        cout << "   3 - Calcular potencia\n";
        cout << "   4 - Salir\n";
        cout << "   Selecciona una opción (1-4): ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                int numero;
                cout << "   Ingresa un número para calcular factorial: ";
                cin >> numero;
                if (numero >= 0 && numero <= 12) {  // Evitar overflow
                    cout << "   Factorial de " << numero << " = " << factorial(numero) << "\n\n";
                } else {
                    cout << "   Por favor ingresa un número entre 0 y 12\n\n";
                }
                break;
            }
            case 2: {
                double radio;
                cout << "   Ingresa el radio del círculo: ";
                cin >> radio;
                if (radio > 0) {
                    cout << "   Área del círculo = " << calcularArea(radio) << "\n\n";
                } else {
                    cout << "   El radio debe ser positivo\n\n";
                }
                break;
            }
            case 3: {
                double base;
                int exponente;
                cout << "   Ingresa la base: ";
                cin >> base;
                cout << "   Ingresa el exponente: ";
                cin >> exponente;
                cout << "   " << base << "^" << exponente << " = " << pow(base, exponente) << "\n\n";
                break;
            }
            case 4:
                cout << "   ¡Hasta luego!\n\n";
                break;
            default:
                cout << "   Opción no válida\n\n";
        }
    } while (opcion != 4);
    
    // ===== PARTE 10: EJERCICIOS PARA PRACTICAR =====
    cout << "=== EJERCICIOS PARA PRACTICAR ===\n";
    cout << "1. Crea una función que calcule el MCD de dos números\n";
    cout << "2. Implementa una función que genere números de Fibonacci\n";
    cout << "3. Desarrolla una función que valide si un número es primo\n";
    cout << "4. Crea una función que ordene un array usando diferentes algoritmos\n";
    cout << "5. Implementa una función que convierta entre diferentes bases numéricas\n";
    cout << "6. Desarrolla una función que encuentre el palíndromo más largo en un string\n";
    cout << "7. Crea una función que calcule el determinante de una matriz 2x2\n\n";
    
    cout << "¡Programa ejecutado exitosamente!\n";
    
    return 0;
}
