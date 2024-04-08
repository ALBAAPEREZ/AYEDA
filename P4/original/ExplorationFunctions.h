/**
 * @file ExplorationFunction.h
 * @author ALBA PÉREZ alu0101513768@ull.edu.es
 * @version 0.1
 * @date 2024-03-08
 * @copyright Copyright (c) 2024
 * @brief Clase abstracta que define la función de exploración para
 * resolver desbordamientos en tablas hash. En esta clase encontramos el operador 
 * () que se usará como función. El método retorna el desplazamiento hasta la siguiente
 * posición de la tabla a explorar. Hacemos uso de template con class Key.
 * En este fichero encontramos las clases:
 * 1. ExplorationFunction
 * 2. ExplorationFunctionCuadratic
 * 3. ExplorationFunctionDoubleDispersion
 * 4. ExplorationFunctionLineal
 */

#ifndef EXPLORATIONFUNCTION_H
#define EXPLORATIONFUNCTION_H

#include <iostream>
#include <cstdlib>

#include "DispersionFunction.h"

/**
 * /////////////////////// BASE ///////////////////////
 * @brief Clase abstracta que define la función de exploración para 
 * resolver desbordamientos en tablas hash.
 * En esta clase encontramos el operador () que se usará como función.
 * El método retorna el desplazamiento hasta la siguiente posición de la tabla a explorar.
 * Hacemos uso de template con class Key.
 * @tparam Key clave que se va a dispersar
 */
template <class Key>
class ExplorationFunction {
 public: 
  // Operador () que hace que la clase se comporte como una función
  virtual unsigned operator()(const Key& k, unsigned i) const = 0;
};

/**
 * /////////////////////// LINEAL ///////////////////////
 * @brief Clase ExplorationFunctionLineal que hereda de ExplorationFunction
 * Contiene el operador () que hace la exploración de forma lineal.
 * Exploración lineal, g(k,i) = i.
 * Esto se realiza para resolver desbordamientos en tablas hash.
 * @tparam Key clave que se va a dispersar
 */
template <class Key>
class ExplorationFunctionLineal : public ExplorationFunction<Key> {
 public:
  // Realiza la exploración de forma lineal, g(k,i) = i.
  unsigned operator()(const Key& k, unsigned i) const { return ++i; }
};

/**
 * /////////////////////// CUADRÁTICA ///////////////////////
 * @brief Clase ExplorationFunctionCuadratic que hereda de ExplorationFunction
 * Contiene el operador () que hace la exploración de forma cuadrática.
 * Exploración cuadrática, g(k,i) = i^2.
 * Esto se realiza para resolver desbordamientos en tablas hash.
 * @tparam Key clave que se va a dispersar
 */
template <class Key>
class ExplorationFunctionCuadratic : public ExplorationFunction<Key> {
 public:
  // Realiza la exploración de forma cuadrática, g(k,i) = i^2.
  virtual unsigned operator()(const Key& k, unsigned i) const { return i * i; }
};

/**
 * /////////////////////// DOBLE DISPERSIÓN ///////////////////////
 * @brief Clase ExplorationFunctionDoubleDispersion que hereda de ExplorationFunction
 * Contiene el operador () que hace la exploración de forma doble dispersión.
 * Doble dispersión, g(k,i) = f(k) * i.
 * Contamos con un constructor al que se le pasa la función de dispersión f(k) utilizada.
 * Además, tenemos el atributo privado que será la función de dispersión.
 * @tparam Key clave que se va a dispersar
 */
template <class Key>
class ExplorationFunctionDoubleDispersion : public ExplorationFunction<Key> {
 public:
  // Constructor al que se le pasa la función de dispersión f(k) utilizada
  ExplorationFunctionDoubleDispersion(DispersionFunction<Key>* funcion_dispersion) : dispersion_function_(funcion_dispersion) {};
  unsigned operator()(const Key& k, unsigned i) const { return (this->dispersion_function_->operator()(k) * i); }
 private:
  //Función de dispersión que inicializamos en el constructor
  DispersionFunction<Key>* dispersion_function_;
};

/**
 * /////////////////////// REDISPERSIÓN ///////////////////////
 * @brief Clase ExplorationFunctionRedispersion que hereda de ExplorationFunction.
 * Se utiliza para la colisión de claves en tablas hash.
 * Contiene el operador () que hace la exploración de forma de redispersión.
 * Redispersión, g(k,i) = (f^(i)) * (k).
 * @tparam Key clave que se va a dispersar
 */
template <class Key>
class ExplorationFunctionRedispersion : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const;
};

/**
 * @brief Método que hace la exploración de forma de redispersión.
 * Redispersión, g(k,i) = (f^(i)) * (k).
 * Basicamente, lo que hacemos es generar un número aleatorio con la clave k,
 * y a partir de ahí, generamos i - 1 números aleatorios más. Retornamos el último número y
 * ese será el indice de la tabla donde se va a insertar la clave. 
 * @tparam Key clave que se va a dispersar
 * @param k clave 
 * @param i desplazamiento
 * @return unsigned retorna el desplazamiento hasta la siguiente posición de la tabla a explorar.
 */
template <class Key>
unsigned ExplorationFunctionRedispersion<Key>::operator()(const Key& k, unsigned i) const {
  srand(k);
  for (unsigned j{1}; j < i; ++j) {
    rand();
  }
  return rand();
}


#endif // EXPLORATIONFUNCTION_H