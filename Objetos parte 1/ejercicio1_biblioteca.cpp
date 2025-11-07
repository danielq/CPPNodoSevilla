/*
 * EJERCICIO 1: SISTEMA DE BIBLIOTECA
 * 
 * PROBLEMA: Crear un sistema para gestionar una biblioteca
 * 
 * METODOLOGÍA OOP - DESCOMPOSICIÓN:
 * 1. IDENTIFICAR OBJETOS:
 *    - Libro: tiene título, autor, ISBN, estado (disponible/prestado)
 *    - Usuario: tiene nombre, ID, lista de libros prestados
 *    - Biblioteca: gestiona los libros y usuarios, realiza préstamos y devoluciones
 * 
 * 2. IDENTIFICAR RELACIONES:
 *    - Biblioteca tiene muchos Libros (composición/agregación)
 *    - Biblioteca tiene muchos Usuarios (composición/agregación)
 *    - Usuario puede tener varios Libros prestados (asociación)
 *    - Libro puede estar prestado a un Usuario (asociación)
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// ===== CLASE LIBRO =====
class Libro {
private:
    string titulo;
    string autor;
    string isbn;
    bool disponible;

public:
    // Constructor
    Libro(string t, string a, string i) 
        : titulo(t), autor(a), isbn(i), disponible(true) {}

    // Getters
    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    string getISBN() const { return isbn; }
    bool estaDisponible() const { return disponible; }

    // Métodos para cambiar estado
    void prestar() { disponible = false; }
    void devolver() { disponible = true; }

    // Método para mostrar información
    void mostrarInfo() const {
        cout << "Título: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Estado: " << (disponible ? "Disponible" : "Prestado") << endl;
    }
};

// ===== CLASE USUARIO =====
class Usuario {
private:
    string nombre;
    int id;
    vector<string> librosPrestados; // Guardamos ISBNs de los libros

public:
    // Constructor
    Usuario(string n, int i) : nombre(n), id(i) {}

    // Getters
    string getNombre() const { return nombre; }
    int getId() const { return id; }
    vector<string> getLibrosPrestados() const { return librosPrestados; }

    // Métodos para gestionar préstamos
    void agregarLibro(string isbn) {
        librosPrestados.push_back(isbn);
    }

    void devolverLibro(string isbn) {
        for (auto it = librosPrestados.begin(); it != librosPrestados.end(); ++it) {
            if (*it == isbn) {
                librosPrestados.erase(it);
                break;
            }
        }
    }

    // Método para mostrar información
    void mostrarInfo() const {
        cout << "Usuario: " << nombre << " (ID: " << id << ")" << endl;
        cout << "Libros prestados: " << librosPrestados.size() << endl;
        if (!librosPrestados.empty()) {
            cout << "ISBNs: ";
            for (const auto& isbn : librosPrestados) {
                cout << isbn << " ";
            }
            cout << endl;
        }
    }
};

// ===== CLASE BIBLIOTECA =====
class Biblioteca {
private:
    vector<shared_ptr<Libro>> libros;
    vector<shared_ptr<Usuario>> usuarios;

    // Método auxiliar para buscar libro por ISBN
    shared_ptr<Libro> buscarLibro(string isbn) {
        for (auto& libro : libros) {
            if (libro->getISBN() == isbn) {
                return libro;
            }
        }
        return nullptr;
    }

    // Método auxiliar para buscar usuario por ID
    shared_ptr<Usuario> buscarUsuario(int id) {
        for (auto& usuario : usuarios) {
            if (usuario->getId() == id) {
                return usuario;
            }
        }
        return nullptr;
    }

public:
    // Métodos para gestionar libros
    void agregarLibro(string titulo, string autor, string isbn) {
        libros.push_back(make_shared<Libro>(titulo, autor, isbn));
        cout << "Libro agregado: " << titulo << endl;
    }

    void agregarUsuario(string nombre, int id) {
        usuarios.push_back(make_shared<Usuario>(nombre, id));
        cout << "Usuario registrado: " << nombre << endl;
    }

    // Método para realizar préstamo
    bool prestarLibro(string isbn, int usuarioId) {
        auto libro = buscarLibro(isbn);
        auto usuario = buscarUsuario(usuarioId);

        if (!libro) {
            cout << "Error: Libro no encontrado" << endl;
            return false;
        }

        if (!usuario) {
            cout << "Error: Usuario no encontrado" << endl;
            return false;
        }

        if (!libro->estaDisponible()) {
            cout << "Error: El libro ya está prestado" << endl;
            return false;
        }

        libro->prestar();
        usuario->agregarLibro(isbn);
        cout << "Préstamo realizado: " << libro->getTitulo() 
             << " -> " << usuario->getNombre() << endl;
        return true;
    }

    // Método para realizar devolución
    bool devolverLibro(string isbn, int usuarioId) {
        auto libro = buscarLibro(isbn);
        auto usuario = buscarUsuario(usuarioId);

        if (!libro || !usuario) {
            cout << "Error: Libro o usuario no encontrado" << endl;
            return false;
        }

        libro->devolver();
        usuario->devolverLibro(isbn);
        cout << "Devolución realizada: " << libro->getTitulo() 
             << " <- " << usuario->getNombre() << endl;
        return true;
    }

    // Método para mostrar todos los libros
    void mostrarLibros() const {
        cout << "\n=== CATÁLOGO DE LIBROS ===" << endl;
        for (const auto& libro : libros) {
            libro->mostrarInfo();
            cout << "---" << endl;
        }
    }

    // Método para mostrar todos los usuarios
    void mostrarUsuarios() const {
        cout << "\n=== USUARIOS REGISTRADOS ===" << endl;
        for (const auto& usuario : usuarios) {
            usuario->mostrarInfo();
            cout << "---" << endl;
        }
    }
};

// ===== FUNCIÓN MAIN - DEMOSTRACIÓN =====
int main() {
    // Crear una biblioteca
    Biblioteca biblioteca;

    // Agregar libros
    cout << "=== AGREGANDO LIBROS ===" << endl;
    biblioteca.agregarLibro("El Quijote", "Miguel de Cervantes", "978-84-376-0494-7");
    biblioteca.agregarLibro("Cien Años de Soledad", "Gabriel García Márquez", "978-84-376-0495-4");
    biblioteca.agregarLibro("1984", "George Orwell", "978-84-376-0496-1");

    // Registrar usuarios
    cout << "\n=== REGISTRANDO USUARIOS ===" << endl;
    biblioteca.agregarUsuario("Juan Pérez", 1);
    biblioteca.agregarUsuario("María García", 2);

    // Realizar préstamos
    cout << "\n=== REALIZANDO PRÉSTAMOS ===" << endl;
    biblioteca.prestarLibro("978-84-376-0494-7", 1);
    biblioteca.prestarLibro("978-84-376-0495-4", 2);

    // Mostrar estado actual
    biblioteca.mostrarLibros();
    biblioteca.mostrarUsuarios();

    // Realizar devolución
    cout << "\n=== REALIZANDO DEVOLUCIÓN ===" << endl;
    biblioteca.devolverLibro("978-84-376-0494-7", 1);

    // Mostrar estado final
    biblioteca.mostrarLibros();

    return 0;
}

