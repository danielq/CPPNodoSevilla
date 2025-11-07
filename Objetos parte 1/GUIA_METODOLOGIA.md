# Guía Práctica: Metodología OOP para Descomponer Problemas

## 🎯 Introducción

Esta guía te enseñará paso a paso cómo usar la metodología orientada a objetos para descomponer cualquier problema en objetos y sus relaciones. Seguiremos un proceso sistemático que puedes aplicar a cualquier situación.

---

## 📋 Proceso en 5 Pasos

### **PASO 1: Leer y Entender el Problema**

Antes de escribir código, debes entender completamente qué se te pide.

**Ejemplo:**
> "Necesito un sistema para gestionar una biblioteca donde los usuarios pueden prestar libros."

**Preguntas clave:**
- ¿Qué entidades principales aparecen? (biblioteca, usuarios, libros)
- ¿Qué acciones se necesitan? (prestar, devolver, registrar)
- ¿Qué información necesito guardar? (títulos, nombres, fechas)

---

### **PASO 2: Identificar los Objetos (Sustantivos)**

Subraya o anota todos los **sustantivos** del problema. Cada sustantivo importante puede ser un objeto.

**Ejemplo del problema de biblioteca:**

| Sustantivo | ¿Es un objeto? | ¿Por qué? |
|------------|----------------|-----------|
| Sistema | ❌ No | Es demasiado genérico |
| Biblioteca | ✅ Sí | Entidad principal que gestiona todo |
| Usuarios | ✅ Sí | Tienen información propia (nombre, ID) |
| Libros | ✅ Sí | Tienen información propia (título, autor, ISBN) |
| Préstamos | ✅ Tal vez | Podría ser un objeto o solo una relación |

**Resultado:** Identificamos 3 objetos principales: `Biblioteca`, `Usuario`, `Libro`

---

### **PASO 3: Identificar Atributos y Métodos**

Para cada objeto, determina:
- **Atributos**: ¿Qué información tiene? (datos)
- **Métodos**: ¿Qué puede hacer? (acciones)

#### **Plantilla para cada objeto:**

```
OBJETO: [Nombre]
  - Atributos:
    * [atributo1]: tipo
    * [atributo2]: tipo
  - Métodos:
    * [metodo1](): descripción
    * [metodo2](): descripción
```

#### **Ejemplo: Objeto Libro**

```
OBJETO: Libro
  - Atributos:
    * titulo: string
    * autor: string
    * isbn: string
    * disponible: bool
  - Métodos:
    * prestar(): cambia disponible a false
    * devolver(): cambia disponible a true
    * estaDisponible(): retorna el estado
```

#### **Ejemplo: Objeto Usuario**

```
OBJETO: Usuario
  - Atributos:
    * nombre: string
    * id: int
    * librosPrestados: vector<string> (ISBNs)
  - Métodos:
    * agregarLibro(isbn): añade un libro a su lista
    * devolverLibro(isbn): quita un libro de su lista
    * mostrarInfo(): muestra información del usuario
```

#### **Ejemplo: Objeto Biblioteca**

```
OBJETO: Biblioteca
  - Atributos:
    * libros: vector<Libro>
    * usuarios: vector<Usuario>
  - Métodos:
    * agregarLibro(): añade un libro al catálogo
    * agregarUsuario(): registra un usuario
    * prestarLibro(): realiza un préstamo
    * devolverLibro(): realiza una devolución
```

---

### **PASO 4: Identificar Relaciones entre Objetos**

Determina cómo se conectan los objetos. Usa estas preguntas:

- **¿"Tiene" o "Contiene"?** → Composición o Agregación
- **¿"Usa" o "Se relaciona con"?** → Asociación
- **¿"Es un"?** → Herencia (no aplicado en estos ejercicios básicos)

#### **Tipos de Relaciones:**

1. **Composición (Tiene - vida dependiente)**
   - El objeto contiene otros objetos
   - Si se destruye el contenedor, se destruyen los contenidos
   - Ejemplo: `Biblioteca` **tiene** `Libros` → Cuando se cierra la biblioteca, los libros desaparecen

2. **Agregación (Tiene - vida independiente)**
   - El objeto referencia otros objetos
   - Los objetos referenciados pueden existir independientemente
   - Ejemplo: `Pedido` **tiene** `Productos` → Los productos pueden existir sin el pedido

3. **Asociación (Se relaciona con)**
   - Conexión temporal o contextual entre objetos
   - Ejemplo: `Usuario` **presta** `Libro` → Relación temporal

#### **Diagrama de relaciones para Biblioteca:**

```
Biblioteca
  ├── tiene muchos → Libro (composición)
  ├── tiene muchos → Usuario (composición)
  │
Libro
  └── puede estar prestado a → Usuario (asociación)

Usuario
  └── puede tener muchos → Libro (asociación)
```

---

### **PASO 5: Implementar en C++**

Ahora que tienes el diseño, escribe el código siguiendo esta estructura:

#### **5.1. Crear las clases con atributos privados**

```cpp
class Libro {
private:
    string titulo;
    string autor;
    string isbn;
    bool disponible;
    
public:
    // Constructor y métodos
};
```

#### **5.2. Implementar constructores**

```cpp
Libro(string t, string a, string i) 
    : titulo(t), autor(a), isbn(i), disponible(true) {}
```

#### **5.3. Implementar getters y setters**

```cpp
string getTitulo() const { return titulo; }
bool estaDisponible() const { return disponible; }
void prestar() { disponible = false; }
```

#### **5.4. Establecer relaciones usando punteros**

```cpp
class Biblioteca {
private:
    vector<shared_ptr<Libro>> libros;      // Composición
    vector<shared_ptr<Usuario>> usuarios;  // Composición
};
```

#### **5.5. Implementar métodos que usan las relaciones**

```cpp
bool prestarLibro(string isbn, int usuarioId) {
    auto libro = buscarLibro(isbn);
    auto usuario = buscarUsuario(usuarioId);
    
    if (!libro || !usuario) return false;
    if (!libro->estaDisponible()) return false;
    
    libro->prestar();
    usuario->agregarLibro(isbn);
    return true;
}
```

---

## 🔍 Ejemplo Completo: Problema del Banco

### **Problema:**
"Sistema bancario donde los clientes pueden tener cuentas y realizar depósitos y retiros."

### **PASO 1: Entender el problema**
- Clientes pueden abrir cuentas
- Pueden depositar y retirar dinero
- Necesito registrar las transacciones

### **PASO 2: Identificar objetos**
- Cliente ✅
- Cuenta ✅
- Transaccion ✅
- Banco ✅

### **PASO 3: Atributos y métodos**

**Cliente:**
- Atributos: nombre, DNI, cuentas
- Métodos: agregarCuenta(), mostrarInfo()

**Cuenta:**
- Atributos: número, saldo, tipo, titular, transacciones
- Métodos: depositar(), retirar(), consultarSaldo()

**Transaccion:**
- Atributos: ID, tipo, monto, fecha, cuentaId
- Métodos: mostrarInfo()

**Banco:**
- Atributos: nombre, clientes, cuentas
- Métodos: registrarCliente(), crearCuenta(), depositar(), retirar()

### **PASO 4: Relaciones**

```
Banco
  ├── tiene muchos → Cliente (composición)
  ├── tiene muchas → Cuenta (composición)
  │
Cliente
  └── tiene muchas → Cuenta (composición)
      │
Cuenta
  └── tiene muchas → Transaccion (composición)
```

### **PASO 5: Implementación**
→ Ver archivo `ejercicio2_banco.cpp`

---

## ✅ Checklist para Descomponer un Problema

Usa esta lista para asegurarte de no olvidar nada:

- [ ] ¿Entiendo completamente el problema?
- [ ] ¿Identifiqué todos los objetos principales?
- [ ] ¿Definí los atributos de cada objeto?
- [ ] ¿Definí los métodos de cada objeto?
- [ ] ¿Identifiqué las relaciones entre objetos?
- [ ] ¿Determiné el tipo de cada relación (composición/agregación/asociación)?
- [ ] ¿Diseñé cómo se comunicarán los objetos?
- [ ] ¿Puedo explicar el diseño a otra persona?

---

## 🎓 Consejos Finales

1. **Empieza simple**: No intentes resolver todo de una vez. Identifica primero los objetos básicos.

2. **Piensa en el mundo real**: Los objetos suelen representar cosas del mundo real. ¿Cómo funcionaría esto físicamente?

3. **Una responsabilidad por objeto**: Cada objeto debe tener una responsabilidad clara. Si un objeto hace demasiadas cosas, divídelo.

4. **Las relaciones son clave**: Entender cómo se relacionan los objetos es fundamental para un buen diseño.

5. **Prototipa primero**: No tengas miedo de hacer un diseño simple primero y mejorarlo después.

6. **Usa diagramas**: Dibujar diagramas simples puede ayudarte a visualizar las relaciones.

---

## 📚 Recursos Adicionales

- **Ejercicio 1**: Sistema de Biblioteca (ejemplo básico)
- **Ejercicio 2**: Sistema Bancario (composición múltiple)
- **Ejercicio 3**: Sistema de Tienda (relaciones complejas)

Cada ejercicio demuestra progresivamente conceptos más avanzados de OOP.

---

**¡Practica con estos ejercicios y aplica la metodología a tus propios problemas!** 🚀

