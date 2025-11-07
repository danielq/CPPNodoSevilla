/*
 * EJERCICIO 2: SISTEMA BANCARIO
 * 
 * PROBLEMA: Crear un sistema para gestionar cuentas bancarias y transacciones
 * 
 * METODOLOGÍA OOP - DESCOMPOSICIÓN:
 * 1. IDENTIFICAR OBJETOS:
 *    - Cuenta: tiene número de cuenta, saldo, tipo (ahorros/corriente), titular
 *    - Transaccion: tiene ID, tipo (depósito/retiro), monto, fecha, cuenta asociada
 *    - Cliente: tiene nombre, DNI, lista de cuentas
 *    - Banco: gestiona clientes, cuentas y transacciones
 * 
 * 2. IDENTIFICAR RELACIONES:
 *    - Banco tiene muchos Clientes (composición)
 *    - Banco tiene muchas Cuentas (composición)
 *    - Cliente tiene varias Cuentas (composición)
 *    - Cuenta tiene muchas Transacciones (composición)
 *    - Transaccion pertenece a una Cuenta (asociación)
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// ===== ENUMS =====
enum TipoCuenta { AHORROS, CORRIENTE };
enum TipoTransaccion { DEPOSITO, RETIRO };

// ===== CLASE TRANSACCION =====
class Transaccion {
private:
    int id;
    TipoTransaccion tipo;
    double monto;
    string fecha;
    int cuentaId;

public:
    Transaccion(int i, TipoTransaccion t, double m, int cId) 
        : id(i), tipo(t), monto(m), cuentaId(cId) {
        // Obtener fecha actual
        time_t ahora = time(0);
        tm* tiempo = localtime(&ahora);
        stringstream ss;
        ss << put_time(tiempo, "%Y-%m-%d %H:%M:%S");
        fecha = ss.str();
    }

    int getId() const { return id; }
    TipoTransaccion getTipo() const { return tipo; }
    double getMonto() const { return monto; }
    string getFecha() const { return fecha; }
    int getCuentaId() const { return cuentaId; }

    void mostrarInfo() const {
        string tipoStr = (tipo == DEPOSITO) ? "DEPÓSITO" : "RETIRO";
        cout << "[" << fecha << "] " << tipoStr 
             << " - Monto: $" << fixed << setprecision(2) << monto 
             << " - Cuenta: " << cuentaId << endl;
    }
};

// ===== CLASE CUENTA =====
class Cuenta {
private:
    int numero;
    TipoCuenta tipo;
    double saldo;
    string titular;
    vector<shared_ptr<Transaccion>> transacciones;
    static int contadorCuentas;

public:
    Cuenta(TipoCuenta t, string tit) 
        : tipo(t), saldo(0.0), titular(tit) {
        numero = ++contadorCuentas;
    }

    int getNumero() const { return numero; }
    TipoCuenta getTipo() const { return tipo; }
    double getSaldo() const { return saldo; }
    string getTitular() const { return titular; }

    // Método para realizar depósito
    bool depositar(double monto) {
        if (monto <= 0) {
            cout << "Error: El monto debe ser mayor a 0" << endl;
            return false;
        }
        saldo += monto;
        transacciones.push_back(make_shared<Transaccion>(
            transacciones.size() + 1, DEPOSITO, monto, numero));
        cout << "Depósito realizado: $" << monto << endl;
        return true;
    }

    // Método para realizar retiro
    bool retirar(double monto) {
        if (monto <= 0) {
            cout << "Error: El monto debe ser mayor a 0" << endl;
            return false;
        }
        if (saldo < monto) {
            cout << "Error: Saldo insuficiente" << endl;
            return false;
        }
        saldo -= monto;
        transacciones.push_back(make_shared<Transaccion>(
            transacciones.size() + 1, RETIRO, monto, numero));
        cout << "Retiro realizado: $" << monto << endl;
        return true;
    }

    // Método para mostrar información
    void mostrarInfo() const {
        string tipoStr = (tipo == AHORROS) ? "AHORROS" : "CORRIENTE";
        cout << "Cuenta #" << numero << " - " << tipoStr << endl;
        cout << "Titular: " << titular << endl;
        cout << "Saldo: $" << fixed << setprecision(2) << saldo << endl;
    }

    // Método para mostrar historial
    void mostrarHistorial() const {
        cout << "\n=== HISTORIAL DE TRANSACCIONES - Cuenta #" << numero << " ===" << endl;
        if (transacciones.empty()) {
            cout << "No hay transacciones registradas" << endl;
        } else {
            for (const auto& trans : transacciones) {
                trans->mostrarInfo();
            }
        }
    }
};

// Inicializar contador estático
int Cuenta::contadorCuentas = 0;

// ===== CLASE CLIENTE =====
class Cliente {
private:
    string nombre;
    string dni;
    vector<shared_ptr<Cuenta>> cuentas;

public:
    Cliente(string n, string d) : nombre(n), dni(d) {}

    string getNombre() const { return nombre; }
    string getDni() const { return dni; }
    vector<shared_ptr<Cuenta>> getCuentas() const { return cuentas; }

    // Método para agregar cuenta
    void agregarCuenta(shared_ptr<Cuenta> cuenta) {
        cuentas.push_back(cuenta);
        cout << "Cuenta agregada al cliente " << nombre << endl;
    }

    // Método para mostrar información
    void mostrarInfo() const {
        cout << "Cliente: " << nombre << " (DNI: " << dni << ")" << endl;
        cout << "Cuentas: " << cuentas.size() << endl;
        for (const auto& cuenta : cuentas) {
            cuenta->mostrarInfo();
            cout << "---" << endl;
        }
    }
};

// ===== CLASE BANCO =====
class Banco {
private:
    string nombre;
    vector<shared_ptr<Cliente>> clientes;
    vector<shared_ptr<Cuenta>> cuentas;

    // Método auxiliar para buscar cuenta
    shared_ptr<Cuenta> buscarCuenta(int numero) {
        for (auto& cuenta : cuentas) {
            if (cuenta->getNumero() == numero) {
                return cuenta;
            }
        }
        return nullptr;
    }

    // Método auxiliar para buscar cliente
    shared_ptr<Cliente> buscarCliente(string dni) {
        for (auto& cliente : clientes) {
            if (cliente->getDni() == dni) {
                return cliente;
            }
        }
        return nullptr;
    }

public:
    Banco(string n) : nombre(n) {}

    // Método para registrar cliente
    void registrarCliente(string nombre, string dni) {
        if (buscarCliente(dni)) {
            cout << "Error: Cliente ya registrado" << endl;
            return;
        }
        clientes.push_back(make_shared<Cliente>(nombre, dni));
        cout << "Cliente registrado: " << nombre << endl;
    }

    // Método para crear cuenta
    int crearCuenta(string dni, TipoCuenta tipo) {
        auto cliente = buscarCliente(dni);
        if (!cliente) {
            cout << "Error: Cliente no encontrado" << endl;
            return -1;
        }

        auto cuenta = make_shared<Cuenta>(tipo, cliente->getNombre());
        cuentas.push_back(cuenta);
        cliente->agregarCuenta(cuenta);
        return cuenta->getNumero();
    }

    // Método para realizar depósito
    bool depositar(int numeroCuenta, double monto) {
        auto cuenta = buscarCuenta(numeroCuenta);
        if (!cuenta) {
            cout << "Error: Cuenta no encontrada" << endl;
            return false;
        }
        return cuenta->depositar(monto);
    }

    // Método para realizar retiro
    bool retirar(int numeroCuenta, double monto) {
        auto cuenta = buscarCuenta(numeroCuenta);
        if (!cuenta) {
            cout << "Error: Cuenta no encontrada" << endl;
            return false;
        }
        return cuenta->retirar(monto);
    }

    // Método para consultar saldo
    void consultarSaldo(int numeroCuenta) {
        auto cuenta = buscarCuenta(numeroCuenta);
        if (!cuenta) {
            cout << "Error: Cuenta no encontrada" << endl;
            return;
        }
        cuenta->mostrarInfo();
    }

    // Método para mostrar historial
    void mostrarHistorial(int numeroCuenta) {
        auto cuenta = buscarCuenta(numeroCuenta);
        if (!cuenta) {
            cout << "Error: Cuenta no encontrada" << endl;
            return;
        }
        cuenta->mostrarHistorial();
    }

    // Método para mostrar todos los clientes
    void mostrarClientes() const {
        cout << "\n=== CLIENTES DEL BANCO " << nombre << " ===" << endl;
        for (const auto& cliente : clientes) {
            cliente->mostrarInfo();
            cout << "---" << endl;
        }
    }
};

// ===== FUNCIÓN MAIN - DEMOSTRACIÓN =====
int main() {
    // Crear banco
    Banco banco("Banco OOP");

    // Registrar clientes
    cout << "=== REGISTRANDO CLIENTES ===" << endl;
    banco.registrarCliente("Ana López", "12345678A");
    banco.registrarCliente("Carlos Ruiz", "87654321B");

    // Crear cuentas
    cout << "\n=== CREANDO CUENTAS ===" << endl;
    int cuenta1 = banco.crearCuenta("12345678A", AHORROS);
    int cuenta2 = banco.crearCuenta("87654321B", CORRIENTE);
    int cuenta3 = banco.crearCuenta("12345678A", CORRIENTE);

    // Realizar operaciones
    cout << "\n=== REALIZANDO OPERACIONES ===" << endl;
    banco.depositar(cuenta1, 1000.50);
    banco.depositar(cuenta2, 2500.75);
    banco.depositar(cuenta3, 500.00);
    banco.retirar(cuenta1, 200.25);
    banco.depositar(cuenta2, 100.00);

    // Consultar saldos
    cout << "\n=== CONSULTANDO SALDOS ===" << endl;
    banco.consultarSaldo(cuenta1);
    banco.consultarSaldo(cuenta2);

    // Mostrar historiales
    banco.mostrarHistorial(cuenta1);
    banco.mostrarHistorial(cuenta2);

    // Mostrar todos los clientes
    banco.mostrarClientes();

    return 0;
}

