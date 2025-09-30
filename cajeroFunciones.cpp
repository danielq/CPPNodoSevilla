#include <iostream>
#include <string>
using namespace std;

// Declaración de funciones
void mostrarMenu();
void consultarSaldo(double saldo);
void retirarDinero(double &saldo);
void ingresarDinero(double &saldo);
void cambiarPIN(int &pin);

int main() {
    // Datos del cajero
    double saldo = 1000.0; // Saldo inicial
    int pin = 1234; // PIN inicial
    int intentos = 3; // Intentos para ingresar el PIN

    int pinIngresado;

    // Verificar PIN
    cout << "Por favor, ingresa tu PIN: ";
    while (intentos > 0) {
        cin >> pinIngresado;
        if (pinIngresado == pin) {
            cout << "PIN correcto.\n";
            break;
        } else {
            intentos--;
            cout << "PIN incorrecto. Te quedan " << intentos << " intentos.\n";
            if (intentos == 0) {
                cout << "Has agotado los intentos.\n";
                return 0;
            }
            cout << "Vuelve a intentarlo: ";
        }
    }

    // Menú principal del cajero
    int opcion;
    do {
        mostrarMenu();
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                consultarSaldo(saldo);
                break;
            case 2:
                retirarDinero(saldo);
                break;
            case 3:
                ingresarDinero(saldo);
                break;
            case 4:
                cambiarPIN(pin);
                break;
            case 5:
                cout << "Gracias por utilizar nuestro cajero. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opción no válida. Intenta de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n----- Menú del Cajero Automático -----\n";
    cout << "1. Consultar saldo\n";
    cout << "2. Retirar dinero\n";
    cout << "3. Ingresar dinero\n";
    cout << "4. Cambiar PIN\n";
    cout << "5. Salir\n";
}

// Función para consultar el saldo
void consultarSaldo(double saldo) {
    cout << "Tu saldo actual es: $" << saldo << endl;
}

// Función para retirar dinero
void retirarDinero(double &saldo) {
    double cantidad;
    cout << "¿Cuánto dinero deseas retirar? $";
    cin >> cantidad;

    if (cantidad <= saldo) {
        saldo -= cantidad;
        cout << "Has retirado $" << cantidad << ". Tu saldo es ahora: $" << saldo << endl;
    } else {
        cout << "No tienes suficiente saldo para realizar esta operación.\n";
    }
}

// Función para ingresar dinero
void ingresarDinero(double &saldo) {
    double cantidad;
    cout << "¿Cuánto dinero deseas ingresar? $";
    cin >> cantidad;

    if (cantidad > 0) {
        saldo += cantidad;
        cout << "Has ingresado $" << cantidad << ". Tu saldo es ahora: $" << saldo << endl;
    } else {
        cout << "La cantidad ingresada debe ser mayor que cero.\n";
    }
}

// Función para cambiar el PIN
void cambiarPIN(int &pin) {
    int nuevoPIN;
    cout << "Ingresa tu nuevo PIN: ";
    cin >> nuevoPIN;
    pin = nuevoPIN;
    cout << "Tu PIN ha sido cambiado correctamente.\n";
}
