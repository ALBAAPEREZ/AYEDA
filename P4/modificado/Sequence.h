/**
 * @file Sequence.h
 * @author ALBA PÉREZ RODRÍGUEZ alu0101513768@ull.edu.es
 * @version 0.1
 * @date 2024-03-08
 * @copyright Copyright (c) 2024
 * @brief Clase abstracta que define una secuencia de elementos.
 * Esta se define para  la dispersion de tipo abierto y cerrado.
 * Para la dispersion de tipo abierto se usará la clase DynamicSequence
 * Para la dispersion de tipo cerrado se usará la clase StaticSequence
 * Esta clase contiene los métodos virtuales puros Search, Insert y IsFull.
 */

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <list>

/**
 * /////////////////////// BASE ///////////////////////
 * @brief Clase abstracta que define una secuencia de elementos.
 * Esta se define para  la dispersion de tipo abierto y cerrado.
 * Para la dispersion de tipo abierto se usará la clase DynamicSequence
 * Para la dispersion de tipo cerrado se usará la clase StaticSequence
 * Esta clase contiene los métodos virtuales puros Search, Insert y IsFull.
 * @tparam Key clave que se va a dispersar
 */
template<class Key>
class Sequence {
 public:  
  virtual bool Search(const Key& k) const = 0;
  virtual bool Insert(const Key& k) = 0;
  virtual bool IsFull() const = 0;
  virtual ~Sequence() {};
};

/////////////////////// DINÁMICA ///////////////////////

/**
 * @brief Clase DynamicSequence que hereda de Sequence
 * Contiene los métodos Search, Insert y IsFull que se van a implementar para la dispersion de tipo abierto.
 * @tparam Key clave que se va a dispersar
 */
template<class Key>
class DynamicSequence : public Sequence<Key> {
 public:
  // Constructor por defecto
  DynamicSequence() = default;
  bool Search(const Key& k) const;
  bool Insert(const Key& k);
  bool IsFull() const;
  size_t Size() const { return lista_.size(); }
  const std::list<Key>& getList() const { return lista_;}
  Key operator[](int i);
  bool isInList(const Key& k) const;

 private:
  std::list<Key> lista_; // Lista enlazada que sirve para meter todos los elementos en la tabl
};

// ========================= MÉTODOS =========================
/**
 * @brief Método de la clase DynamicSequence que se encarga de buscar un elemento en la lista
 * Lo que hace es recorrer lalista entera, si encuentra el elemento devuelve un "true".
 * aumentando el tamaño de la lista. Si no lo encuentra devuelve un "false"
 * @tparam Key clave que se va a dispersar
 * @param k clave que se va a buscar
 * @return true true si el elemento ya está en la lista
 * @return false false si el elemento no está en la lista
 */
template <class Key>
bool DynamicSequence<Key>::Search(const Key& k) const {
  int position{0};
  for (auto& element : lista_) {
    if (element == k) {
      return true;
    }
    position++;
  }
  return false; // No hemos encontrado el elemento
}

/**
 * @brief Método que se encarga de insertar un elemento en la lista
 * Si no existe el elemento en la lista de sinonimos de la posición correspondiente de la tabla hash, se añade al final
 * Si se ha podido añadir el elemento en la lista, se devuelve un "true"
 * Si no se ha podido añadir el elemento en la lista, se devuelve un "false"
 * @tparam Key clave que se va a dispersar
 * @param k clave que se va a insertar
 * @return true retorna true si el elemento se ha podido insertar en la secuencia
 * @return false retorna false si el elemento no se ha podido insertar en la secuencia
 */
template <class Key>
bool DynamicSequence<Key>::Insert(const Key& k) {
  if (!Search(k)) {
    lista_.push_back(k); // Se añade el elemento al final de la lista
    std::cout << "El elemento se pudo insertar correctamente en la secuencia" << std::endl;
    return true;
  }
  std::cout << "No se pudo insertar el elemento en la secuencia" << std::endl;
  return false; // No se ha podido añadir el elemento en la lista
}

/**
 * @brief Método que se encarga de comprobar si la lista está llena
 * Para la dispersion de tipo abierto, la lista nunca estará llena, por lo que siempre devolverá un "false"
 * @tparam Key Clave que se va a dispersar
 * @return true retorna true si la lista está llena
 * @return false nunca estará llena, por lo que siempre devolverá un "false"
 */
template <class Key>
bool DynamicSequence<Key>::IsFull() const {
  return false;
}

/**
 * @brief Sobrecarga del operador []
 * Sirve para acceder a un elemento de la lista
 * @tparam Key clave que se va a dispersar
 * @param i indice del elemento que se quiere acceder
 * @return Key clave que se quiere acceder
 */
template <class Key>
Key DynamicSequence<Key>::operator[](int i) {
  auto it{lista_.begin()};
  std::advance(it, i);
  return *it;
}

/**
 * @brief Método que se encarga de comprobar si un elemento está en la lista
 * Si el elemento está en la lista, se devuelve un "true"
 * @tparam Key Clave que se va a dispersar
 * @param k clave que se va a busca
 * @return true retorna true si el elemento está en la list
 * @return false retorna false si el elemento no está en la lista
 */
template <class Key>
bool DynamicSequence<Key>::isInList(const Key& k) const {
  for (auto& element : lista_) {
    if (element == k) {
      return true;
    }
  }
  return false;
}


/////////////////////// ESTÁTICA ///////////////////////

/**
 * @brief Clase StaticSequence que hereda de Sequence.
 * Se define para la dispersion de tipo cerrado. Esta se define como un array de tamaño fijo.
 * @tparam Key clave que se va a dispersar
 */
template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence();
  StaticSequence(size_t blocksize);
  bool Search(const Key& key) const override;
  bool Insert(const Key& key) override;
  bool IsFull() const;
  size_t Size() const { return numberElements_; }
  const Key getData(int i) const { return block_[i]; }

 private:
  size_t blocksize_; // Tamaño del bloque
  int numberElements_; // Número de elementos
  std::vector<Key> block_; // vector estático
};

// ========================= MÉTODOS =========================

/**
 * @brief Constructor por defecto de la clase StaticSequence
 * Inicializa el tamaño actual de la secuencia a 0
 * y el tamaño del bloque a 0
 * @tparam Key clave que se va a dispersar
 */
template <class Key>
StaticSequence<Key>::StaticSequence() : blocksize_(0), numberElements_(0) {}

/**
 * @brief Construct a new Static Sequence< Key>:: Static Sequence object
 * Constructor de la clase StaticSequence que inicializa el tamaño del bloque
 * Lo que se hace es inicializar el número de elementos a 0 y el tamaño del 
 * bloque al tamaño que se le pasa. Además, se reserva el espacio de memoria
 * @tparam Key 
 * @param blocksize 
 */
template <class Key>
StaticSequence<Key>::StaticSequence(size_t blocksize)  {
  numberElements_ = 0;  
  blocksize_ = blocksize;   
}

/**
 * @brief Método de la clase StaticSequence que se encarga de buscar un elemento en la secuencia
 * Lo que hace es recorrer la secuencia entera, si encuentra el elemento devuelve un "true".
 * Si no lo encuentra devuelve un "false"
 * @tparam Key clave que se va a dispersar
 * @param key clave que se va a buscar
 * @return true true si el elemento ya está en la secuencia
 * @return false false si el elemento no está en la secuencia
 */
template <class Key>
bool StaticSequence<Key>::Search(const Key& key) const {
  int position{0};
  // Recorremos la secuencia entera
  for (auto& elements: block_) {
    if (elements == key) {
      return true; 
    }
    position++;
  }
  return false; 
}

/**
 * @brief Método que se encarga de insertar un elemento en la secuencia
 * Si no existe el elemento en la secuencia, se añade al final
 * Si se ha podido añadir el elemento en la secuencia, se devuelve un "true"
 * Si no se ha podido añadir el elemento en la secuencia, se devuelve un "false"
 * @tparam Key clave que se va a dispersar
 * @param key clave que se va a insertar
 * @return true retorna true si el elemento se ha podido insertar en la secuencia
 * @return false retorna false si el elemento no se ha podido insertar en la secuencia
 */
template <class Key>
bool StaticSequence<Key>::Insert(const Key& key) {
  // Comprobamos si se puede introducir el elemento
  if (!IsFull() && !Search(key)) {  
    numberElements_++;          
    block_.push_back(key);  
    std::cout << "El elemento " << key << " se pudo introducir correctamente en la secuencia" << std::endl;
    return true;  // Se pudo introducir el elemento, retornamos "true"
  }
  std::cout << "El elemento " << key << " NO se pudo introducir correctamente en la secuencia" << std::endl;
  return false;  // No se pudo introducir el elemento, retornamos "false"
}

/**
 * @brief Método que se encarga de comprobar si la secuencia está llena
 * Si el tamaño actual de la secuencia es igual al tamaño del bloque, la secuencia está llena
 * @tparam Key clave que se va a dispersar
 * @return true retorna true si la secuencia está llena
 * @return false retorna false si la secuencia no está llena
 */
template <class Key>
bool StaticSequence<Key>::IsFull() const {
  // Si el número de elementos actual es igual al tamaño total, es que está
  if (numberElements_ == blocksize_) {
    return true;
  }
  return false;  // El bloque todavía no está lleno, retornamos "false"
}

#endif // SEQUENCE_H