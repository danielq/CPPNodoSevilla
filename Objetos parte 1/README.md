# Ejercicios de Programación Orientada a Objetos en C++

Este repositorio contiene ejercicios prácticos que demuestran cómo usar la metodología orientada a objetos para descomponer problemas en objetos y sus relaciones.

## 📚 Contenido

### Ejercicio 1: Sistema de Biblioteca (`ejercicio1_biblioteca.cpp`)
**Problema:** Gestión de una biblioteca con libros y usuarios.

**Objetos identificados:**
- `Libro`: título, autor, ISBN, estado (disponible/prestado)
- `Usuario`: nombre, ID, lista de libros prestados
- `Biblioteca`: gestiona libros, usuarios, préstamos y devoluciones

**Relaciones:**
- Biblioteca **tiene** muchos Libros (composición)
- Biblioteca **tiene** muchos Usuarios (composición)
- Usuario **puede tener** varios Libros prestados (asociación)
- Libro **puede estar prestado** a un Usuario (asociación)

**Conceptos OOP aplicados:**
- Encapsulación
- Composición
- Asociación
- Métodos de acceso (getters/setters)

---

### Ejercicio 2: Sistema Bancario (`ejercicio2_banco.cpp`)
**Problema:** Gestión de cuentas bancarias y transacciones.

**Objetos identificados:**
- `Cuenta`: número, saldo, tipo (ahorros/corriente), titular
- `Transaccion`: ID, tipo (depósito/retiro), monto, fecha
- `Cliente`: nombre, DNI, lista de cuentas
- `Banco`: gestiona clientes, cuentas y transacciones

**Relaciones:**
- Banco **tiene** muchos Clientes (composición)
- Banco **tiene** muchas Cuentas (composición)
- Cliente **tiene** varias Cuentas (composición)
- Cuenta **tiene** muchas Transacciones (composición)
- Transaccion **pertenece** a una Cuenta (asociación)

**Conceptos OOP aplicados:**
- Encapsulación
- Composición anidada
- Enumeraciones (enums)
- Variables estáticas (contadores)

---

### Ejercicio 3: Sistema de Gestión de Tienda (`ejercicio3_tienda.cpp`)
**Problema:** Gestión de productos, clientes, pedidos y ventas.

**Objetos identificados:**
- `Producto`: código, nombre, precio, stock
- `Cliente`: ID, nombre, email, tipo (regular/premium)
- `ItemPedido`: producto, cantidad, subtotal
- `Pedido`: ID, fecha, cliente, lista de items, total
- `Tienda`: gestiona productos, clientes y pedidos

**Relaciones:**
- Tienda **tiene** muchos Productos (composición)
- Tienda **tiene** muchos Clientes (composición)
- Tienda **tiene** muchos Pedidos (composición)
- Pedido **tiene** un Cliente (asociación)
- Pedido **tiene** muchos ItemPedido (composición)
- ItemPedido **tiene** un Producto (asociación)

**Conceptos OOP aplicados:**
- Encapsulación avanzada
- Composición múltiple
- Asociaciones bidireccionales
- Cálculos dinámicos (descuentos, totales)
- Gestión de inventario

---

## 🎯 Metodología OOP para Descomponer Problemas

### Paso 1: Identificar Objetos
Pregúntate: **¿Qué "cosas" o "entidades" existen en el problema?**
- Busca sustantivos en el enunciado
- Cada objeto representa una entidad del mundo real o conceptual

### Paso 2: Identificar Atributos
Pregúntate: **¿Qué características tiene cada objeto?**
- Propiedades que describen al objeto
- Datos que el objeto necesita almacenar

### Paso 3: Identificar Métodos
Pregúntate: **¿Qué acciones puede realizar cada objeto?**
- Operaciones que el objeto puede ejecutar
- Comportamientos del objeto

### Paso 4: Identificar Relaciones
Pregúntate: **¿Cómo se relacionan los objetos entre sí?**

**Tipos de relaciones:**
- **Composición**: "Tiene" - El objeto contiene otros objetos (destrucción en cascada)
- **Agregación**: "Tiene" - El objeto referencia otros objetos (sin destrucción en cascada)
- **Asociación**: "Se relaciona con" - Conexión entre objetos
- **Herencia**: "Es un" - Especialización de clases (no aplicada en estos ejercicios)

### Paso 5: Implementar en C++
- Definir clases con atributos privados
- Crear constructores
- Implementar métodos públicos (getters, setters, operaciones)
- Establecer relaciones usando punteros o referencias

---

## 🚀 Cómo Compilar y Ejecutar

### Compilación
```bash
# Ejercicio 1
g++ -o ejercicio1 ejercicio1_biblioteca.cpp && ./ejercicio1

# Ejercicio 2
g++ -o ejercicio2 ejercicio2_banco.cpp && ./ejercicio2

# Ejercicio 3
g++ -o ejercicio3 ejercicio3_tienda.cpp && ./ejercicio3
```

### Requisitos
- Compilador C++ compatible con C++11 o superior (g++, clang++, etc.)
- Sistema operativo: Linux, macOS, o Windows con compilador compatible

---

## 📖 Conceptos Clave Aplicados

1. **Encapsulación**: Datos privados protegidos por métodos públicos
2. **Abstracción**: Representación simplificada de entidades del mundo real
3. **Composición**: Objetos complejos formados por objetos más simples
4. **Asociación**: Relaciones entre objetos independientes
5. **Smart Pointers**: Uso de `shared_ptr` para gestión automática de memoria
6. **STL**: Uso de contenedores (`vector`) para colecciones dinámicas

---

## 🎓 Ejercicios Propuestos

Intenta implementar estos ejercicios siguiendo la misma metodología:

1. **Sistema de Reservas de Hotel**
   - Objetos: Hotel, Habitación, Cliente, Reserva
   - Relaciones: Hotel tiene Habitaciones, Cliente hace Reservas

2. **Sistema de Gestión de Estudiantes**
   - Objetos: Estudiante, Curso, Profesor, Calificación
   - Relaciones: Estudiante toma Cursos, Profesor imparte Cursos

3. **Sistema de Transporte**
   - Objetos: Vehículo, Conductor, Ruta, Viaje
   - Relaciones: Conductor maneja Vehículo, Viaje usa Ruta

---

## 📝 Notas

- Todos los ejercicios usan `shared_ptr` para gestión automática de memoria
- Los ejercicios están comentados en español para facilitar el aprendizaje
- Se aplican buenas prácticas de programación orientada a objetos
- Los ejercicios son progresivos: cada uno es más complejo que el anterior

---

## 🤝 Contribuciones

Siéntete libre de mejorar estos ejercicios o agregar más ejemplos siguiendo la misma metodología.

---

**¡Buena suerte con tu aprendizaje de OOP en C++!** 🚀

