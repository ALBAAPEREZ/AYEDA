/**
 * @file Sequence.h
 * @author ALBA PÉREZ RODRÍGUEZ alu0101513768@ull.edu.es
 * @version 0.1
 * @date 2024-03-24
 * @copyright Copyright (c) 2024
 * @brief Clase abstracta que define una secuencia de elementos.
 * Se define la clase StaticSequence que hereda de Sequence.
 * Esta clase contiene el operador [] que se va a implementar para permitir
 * que los métodos de ordenación accedan a los elementos de la secuencia.
 * @tparam Key clave que se va a dispersar
 */

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

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
  virtual Key& operator[](const int&) = 0;
};

/**
 * /////////////////////// ESTATICA ///////////////////////
 * @brief Clase StaticSequence que hereda de Sequence 
 * Contiene el operador [] que se va a implementar para permitir
 * que los métodos de ordenación accedan a los elementos de la secuencia.
 * @tparam Key clave que se va a dispersar
 */
template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  // Constructores
  StaticSequence(unsigned int size, const std::string& mode);
  StaticSequence(unsigned int size, std::fstream& filename);
  ~StaticSequence();
  // operador []
  Key& operator[](const int& p) override {
    if (p < 0 || p >= size_) {
      throw std::out_of_range("Posición fuera de rango");
    }
    return value_[p];
  }
  int getSize() { return size_; }
  std::vector<Key> getValue() { return value_; }

 private:
  int size_; // tamaño de la secuencia
  std::vector<Key> value_; // vector de elementos
};

///////////////////////// METODOS ///////////////////////////
/**
 * @brief Constructor de la clase StaticSequence
 * Inicializa la secuencia manualmente o con números aleatorios
 * @param size tamaño de la secuencia
 * @param mode modo de introducción de datos
 */
template <class Key>
StaticSequence<Key>::StaticSequence(unsigned int size, const std::string& mode) {
  long clave;
  if (mode == "manual") { 
    size_ = size;
    value_.resize(size);  // Resize the vector to the desired size
    for (unsigned int i = 0; i < size_; ++i) {
      std::cout << ">>> Introduce un NIF" << (i + 1) << ": ";
      std::cin >> clave;
      if (!std::cin) {
        std::cerr << "Error: Entrada inválida. Ingresa un número" << std::endl;
        std::cin.clear(); // clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
        i--; // decrement i to repeat the current iteration
        continue;
      }
      value_[i] = Key(clave);  // Initialize each element of the vector with the user input
    }
  } else if (mode == "random") { 
    size_ = size;
    value_.resize(size);  // Resize the vector to the desired size
    srand(time(NULL));
    for (unsigned i = 0; i < size_; i++) {
      clave = rand() % 90000000 + 10000000;
      value_[i] = Key(clave);
    }
    std::cout << "La secuencia ha sido generada aleatoriamente." << std::endl;
  } else {
    std::cerr << "Error: modo no válido" << std::endl; 
  } 
}


/**
 * @brief Constructor de la clase StaticSequence
 * Inicializa la secuencia con los datos de un fichero
 * @param size tamaño de la secuencia
 * @param filename nombre del fichero
 */
template <class Key>
StaticSequence<Key>::StaticSequence(unsigned int size, std::fstream& filename) {
  size_ = size;
  value_.resize(size);  // Resize the vector to the desired size
  long clave;
  for (unsigned i = 0; i < size_; i++) {
    filename >> clave;
    value_[i] = Key(clave);
  }
}

/**
 * @brief Destructor de la clase StaticSequence
 * Libera la memoria de la secuencia
 * Se encarga de liberar la memoria de la secuencia mediante el método clear
 */
template <class Key>
StaticSequence<Key>::~StaticSequence() {
  value_.clear();
}

#endif // SEQUENCE_H