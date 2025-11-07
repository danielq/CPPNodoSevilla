/*
 * EJERCICIO 3: SISTEMA DE GESTIÓN DE TIENDA
 * 
 * PROBLEMA: Crear un sistema para gestionar productos, clientes, pedidos y ventas
 * 
 * METODOLOGÍA OOP - DESCOMPOSICIÓN:
 * 1. IDENTIFICAR OBJETOS:
 *    - Producto: tiene código, nombre, precio, stock
 *    - Cliente: tiene ID, nombre, email, tipo (regular/premium)
 *    - ItemPedido: tiene producto, cantidad, subtotal
 *    - Pedido: tiene ID, fecha, cliente, lista de items, total
 *    - Tienda: gestiona productos, clientes y pedidos
 * 
 * 2. IDENTIFICAR RELACIONES:
 *    - Tienda tiene muchos Productos (composición)
 *    - Tienda tiene muchos Clientes (composición)
 *    - Tienda tiene muchos Pedidos (composición)
 *    - Pedido tiene un Cliente (asociación)
 *    - Pedido tiene muchos ItemPedido (composición)
 *    - ItemPedido tiene un Producto (asociación)
 * 
 * 3. CONCEPTOS OOP APLICADOS:
 *    - Encapsulación: datos privados con métodos públicos
 *    - Composición: objetos dentro de otros objetos
 *    - Asociación: relaciones entre objetos
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

// ===== ENUMS =====
enum TipoCliente { REGULAR, PREMIUM };

// ===== CLASE PRODUCTO =====
class Producto {
private:
    int codigo;
    string nombre;
    double precio;
    int stock;

public:
    Producto(int cod, string nom, double prec, int stk)
        : codigo(cod), nombre(nom), precio(prec), stock(stk) {}

    int getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }

    // Método para reducir stock
    bool reducirStock(int cantidad) {
        if (cantidad > stock) {
            return false;
        }
        stock -= cantidad;
        return true;
    }

    // Método para aumentar stock
    void aumentarStock(int cantidad) {
        stock += cantidad;
    }

    void mostrarInfo() const {
        cout << "[" << codigo << "] " << nombre 
             << " - Precio: $" << fixed << setprecision(2) << precio
             << " - Stock: " << stock << endl;
    }
};

// ===== CLASE CLIENTE =====
class Cliente {
private:
    int id;
    string nombre;
    string email;
    TipoCliente tipo;

public:
    Cliente(int i, string nom, string mail, TipoCliente t)
        : id(i), nombre(nom), email(mail), tipo(t) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getEmail() const { return email; }
    TipoCliente getTipo() const { return tipo; }

    // Método para calcular descuento según tipo
    double getDescuento() const {
        return (tipo == PREMIUM) ? 0.10 : 0.0; // 10% descuento para premium
    }

    void mostrarInfo() const {
        string tipoStr = (tipo == PREMIUM) ? "PREMIUM" : "REGULAR";
        cout << "Cliente #" << id << ": " << nombre << " (" << tipoStr << ")" << endl;
        cout << "Email: " << email << endl;
    }
};

// ===== CLASE ITEMPEDIDO =====
class ItemPedido {
private:
    shared_ptr<Producto> producto;
    int cantidad;
    double subtotal;

public:
    ItemPedido(shared_ptr<Producto> prod, int cant)
        : producto(prod), cantidad(cant) {
        subtotal = producto->getPrecio() * cantidad;
    }

    shared_ptr<Producto> getProducto() const { return producto; }
    int getCantidad() const { return cantidad; }
    double getSubtotal() const { return subtotal; }

    void mostrarInfo() const {
        cout << "  " << producto->getNombre() 
             << " x " << cantidad 
             << " = $" << fixed << setprecision(2) << subtotal << endl;
    }
};

// ===== CLASE PEDIDO =====
class Pedido {
private:
    int id;
    string fecha;
    shared_ptr<Cliente> cliente;
    vector<shared_ptr<ItemPedido>> items;
    double subtotal;
    double descuento;
    double total;
    static int contadorPedidos;

public:
    Pedido(shared_ptr<Cliente> cli)
        : cliente(cli), subtotal(0.0), descuento(0.0), total(0.0) {
        id = ++contadorPedidos;
        // Obtener fecha actual
        time_t ahora = time(0);
        tm* tiempo = localtime(&ahora);
        stringstream ss;
        ss << put_time(tiempo, "%Y-%m-%d %H:%M:%S");
        fecha = ss.str();
    }

    int getId() const { return id; }
    string getFecha() const { return fecha; }
    shared_ptr<Cliente> getCliente() const { return cliente; }
    double getTotal() const { return total; }

    // Método para agregar item al pedido
    bool agregarItem(shared_ptr<Producto> producto, int cantidad) {
        if (cantidad <= 0) {
            cout << "Error: La cantidad debe ser mayor a 0" << endl;
            return false;
        }

        if (!producto->reducirStock(cantidad)) {
            cout << "Error: Stock insuficiente para " << producto->getNombre() << endl;
            return false;
        }

        items.push_back(make_shared<ItemPedido>(producto, cantidad));
        recalcularTotal();
        return true;
    }

    // Método para recalcular total
    void recalcularTotal() {
        subtotal = 0.0;
        for (const auto& item : items) {
            subtotal += item->getSubtotal();
        }
        descuento = subtotal * cliente->getDescuento();
        total = subtotal - descuento;
    }

    // Método para mostrar información del pedido
    void mostrarInfo() const {
        cout << "\n=== PEDIDO #" << id << " ===" << endl;
        cout << "Fecha: " << fecha << endl;
        cliente->mostrarInfo();
        cout << "\nItems:" << endl;
        for (const auto& item : items) {
            item->mostrarInfo();
        }
        cout << "\nSubtotal: $" << fixed << setprecision(2) << subtotal << endl;
        if (descuento > 0) {
            cout << "Descuento (" << (cliente->getDescuento() * 100) 
                 << "%): -$" << descuento << endl;
        }
        cout << "TOTAL: $" << total << endl;
    }
};

// Inicializar contador estático
int Pedido::contadorPedidos = 0;

// ===== CLASE TIENDA =====
class Tienda {
private:
    string nombre;
    vector<shared_ptr<Producto>> productos;
    vector<shared_ptr<Cliente>> clientes;
    vector<shared_ptr<Pedido>> pedidos;

    // Métodos auxiliares
    shared_ptr<Producto> buscarProducto(int codigo) {
        for (auto& producto : productos) {
            if (producto->getCodigo() == codigo) {
                return producto;
            }
        }
        return nullptr;
    }

    shared_ptr<Cliente> buscarCliente(int id) {
        for (auto& cliente : clientes) {
            if (cliente->getId() == id) {
                return cliente;
            }
        }
        return nullptr;
    }

public:
    Tienda(string nom) : nombre(nom) {}

    // Métodos para gestionar productos
    void agregarProducto(int codigo, string nombre, double precio, int stock) {
        if (buscarProducto(codigo)) {
            cout << "Error: Producto ya existe" << endl;
            return;
        }
        productos.push_back(make_shared<Producto>(codigo, nombre, precio, stock));
        cout << "Producto agregado: " << nombre << endl;
    }

    void mostrarProductos() const {
        cout << "\n=== CATÁLOGO DE PRODUCTOS ===" << endl;
        for (const auto& producto : productos) {
            producto->mostrarInfo();
        }
    }

    // Métodos para gestionar clientes
    void registrarCliente(int id, string nombre, string email, TipoCliente tipo) {
        if (buscarCliente(id)) {
            cout << "Error: Cliente ya registrado" << endl;
            return;
        }
        clientes.push_back(make_shared<Cliente>(id, nombre, email, tipo));
        cout << "Cliente registrado: " << nombre << endl;
    }

    void mostrarClientes() const {
        cout << "\n=== CLIENTES REGISTRADOS ===" << endl;
        for (const auto& cliente : clientes) {
            cliente->mostrarInfo();
            cout << "---" << endl;
        }
    }

    // Método para crear pedido
    shared_ptr<Pedido> crearPedido(int clienteId) {
        auto cliente = buscarCliente(clienteId);
        if (!cliente) {
            cout << "Error: Cliente no encontrado" << endl;
            return nullptr;
        }

        auto pedido = make_shared<Pedido>(cliente);
        pedidos.push_back(pedido);
        cout << "Pedido #" << pedido->getId() << " creado para " 
             << cliente->getNombre() << endl;
        return pedido;
    }

    // Método para agregar item a pedido
    bool agregarItemAPedido(int pedidoId, int codigoProducto, int cantidad) {
        auto pedido = find_if(pedidos.begin(), pedidos.end(),
            [pedidoId](const shared_ptr<Pedido>& p) {
                return p->getId() == pedidoId;
            });

        if (pedido == pedidos.end()) {
            cout << "Error: Pedido no encontrado" << endl;
            return false;
        }

        auto producto = buscarProducto(codigoProducto);
        if (!producto) {
            cout << "Error: Producto no encontrado" << endl;
            return false;
        }

        return (*pedido)->agregarItem(producto, cantidad);
    }

    // Método para mostrar pedido
    void mostrarPedido(int pedidoId) {
        auto pedido = find_if(pedidos.begin(), pedidos.end(),
            [pedidoId](const shared_ptr<Pedido>& p) {
                return p->getId() == pedidoId;
            });

        if (pedido == pedidos.end()) {
            cout << "Error: Pedido no encontrado" << endl;
            return;
        }

        (*pedido)->mostrarInfo();
    }

    // Método para mostrar todos los pedidos
    void mostrarPedidos() const {
        cout << "\n=== TODOS LOS PEDIDOS ===" << endl;
        if (pedidos.empty()) {
            cout << "No hay pedidos registrados" << endl;
        } else {
            for (const auto& pedido : pedidos) {
                pedido->mostrarInfo();
            }
        }
    }

    // Método para calcular ventas totales
    double calcularVentasTotales() const {
        double total = 0.0;
        for (const auto& pedido : pedidos) {
            total += pedido->getTotal();
        }
        return total;
    }
};

// ===== FUNCIÓN MAIN - DEMOSTRACIÓN =====
int main() {
    // Crear tienda
    Tienda tienda("Tienda OOP");

    // Agregar productos
    cout << "=== AGREGANDO PRODUCTOS ===" << endl;
    tienda.agregarProducto(101, "Laptop", 999.99, 10);
    tienda.agregarProducto(102, "Mouse", 25.50, 50);
    tienda.agregarProducto(103, "Teclado", 75.00, 30);
    tienda.agregarProducto(104, "Monitor", 299.99, 15);

    // Registrar clientes
    cout << "\n=== REGISTRANDO CLIENTES ===" << endl;
    tienda.registrarCliente(1, "Pedro Martínez", "pedro@email.com", REGULAR);
    tienda.registrarCliente(2, "Laura Sánchez", "laura@email.com", PREMIUM);

    // Mostrar catálogo y clientes
    tienda.mostrarProductos();
    tienda.mostrarClientes();

    // Crear pedidos
    cout << "\n=== CREANDO PEDIDOS ===" << endl;
    auto pedido1 = tienda.crearPedido(1);
    auto pedido2 = tienda.crearPedido(2);

    // Agregar items a pedidos
    cout << "\n=== AGREGANDO ITEMS A PEDIDOS ===" << endl;
    tienda.agregarItemAPedido(1, 101, 1); // Laptop
    tienda.agregarItemAPedido(1, 102, 2); // Mouse x2
    tienda.agregarItemAPedido(1, 103, 1); // Teclado

    tienda.agregarItemAPedido(2, 104, 2); // Monitor x2 (cliente premium con descuento)
    tienda.agregarItemAPedido(2, 102, 1); // Mouse

    // Mostrar pedidos
    tienda.mostrarPedido(1);
    tienda.mostrarPedido(2);

    // Mostrar estado de productos
    cout << "\n=== ESTADO ACTUAL DE PRODUCTOS ===" << endl;
    tienda.mostrarProductos();

    // Mostrar ventas totales
    cout << "\n=== RESUMEN DE VENTAS ===" << endl;
    cout << "Ventas totales: $" << fixed << setprecision(2) 
         << tienda.calcularVentasTotales() << endl;

    return 0;
}

