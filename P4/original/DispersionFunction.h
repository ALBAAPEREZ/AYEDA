/**
 * @file DispersionFunction.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @brief alu0101513768@ull.edu.es
 * @version 0.1
 * @date 2024-03-08
 * @copyright Copyright (c) 2024
 * @brief Clase abstracta que define la función de dispersión, de la que 
 * heredaran las clases DispersionModulo, DispersionSuma y DispersionPseudoaleatoria.
 * En esta clase solo se define el operador () para que se pueda usar como función.
 * Hacemos uso de template con class Key que será la clave que se va a dispersar.
 * En este fichero encontramos las clases:
 * 1. DispersionFunction
 * 2. DispersionModulo
 * 3. DispersionSuma
 * 4. DispersionPseudoaleatoria
 */

#ifndef DISPERSIONFUNCTION_H
#define DISPERSIONFUNCTION_H

#include <iostream>
#include <cstdlib>

#include "ExplorationFunctions.h"

/**
 * /////////////////////// BASE ///////////////////////
 * @brief Clase abstracta que define la función de dispersión
 * Definimos el oeradaor () para que se pueda usar como función
 * De esta clase abstracta se desarrollaran tres clases genericas
 * 1. La clase DispersionModulo
 * 2. La clase DispersionSuma
 * 3. La clase DispersionPseudoaleatoria
 * @tparam Key clave que se va a dispersar
 */
template<class Key>
class DispersionFunction {
 public: 
  // Operador () que hace que la clase se comporte como una función
  virtual unsigned operator()(const Key& k) const = 0;
};

/**
 * /////////////////////// SUMA ///////////////////////
 * @brief Clase DispersionSuma que hereda de DispersionFunction
 * Contiene un constructor propio de la clase que se encarga de inicializar el tamaño de la tabla hash
 * y el operador () que hace que la clase se comporte como una función
 * Como atributo privado tendremos el tamaño de la tabla hash
 * @tparam Key clave que se va a dispersar en foma de suma. Basada en la suma, h(k) = sum(ki) % tableSize
 */
template <class Key>
class DispersionSum : public DispersionFunction<Key> {
 public:
  // Constructor propio de la clase que se encarga de inicializar el tamaño de la tabla hash
  DispersionSum(const unsigned n) : tableSize_(n) {}
  ~DispersionSum() {}
  // Operador () que hace que la clase se comporte como una función
  unsigned operator()(const Key& k) const;

 private:
  unsigned tableSize_; // tamaño de la tabla hash
};

/**
 * @brief Método que hace la dispersión de la clave k en forma de suma.
 * La suma es: h(k) = sum(ki) % tableSize 
 * Para ello, lo que hacemos es que mientras el número sea mayor que 0, 
 * sumamos todos los dígitos del número de la clave k y cuando ya no haya más dígitos,
 * le hacemos el módulo con el tamaño de la tabla hash.
 * El auxiliar con el que trabajamos es un long para que pueda almacenar números grandes.
 * @tparam Key clave que se va a dispersar en foma de suma. Basada en la suma, h(k) = sum(ki) % tableSize
 * @param k vlave que se va a dispersar
 * @return unsigned retorna el resultado de la dispersión
 */
template <class Key>
unsigned DispersionSum<Key>::operator()(const Key& k) const {
  unsigned suma{0};
  long aux{k};
  // Mientras el número sea mayor que 0, sumamos todos los dígitos del número
  while (aux > 0) {
    suma += aux % 10;
    aux /= 10;
  }
  // Después de sumar todos los dígitos del número le hacemos el módulo con el tamaño de la tabla hash
  return (suma % tableSize_);
}


/**
 * /////////////////////// MÓDULO ///////////////////////
 * @brief Clase DispersionModulo que hereda de DispersionFunction
 * Contiene un constructor propio de la clase que se encarga de inicializar el tamaño de la tabla hash
 * y el operador () que hace que la clase se comporte como una función
 * Como atributo privado tendremos el tamaño de la tabla hash
 * @tparam Key clave que se va a dispersar en foma de módulo ---> Módulo, h(k) = k % tableSize
 */
template<class Key>
class DispersionModule : public DispersionFunction<Key> {
 public:
  // Constructor propio de la clase que se encarga de inicializar el tamaño de la tabla hash
  DispersionModule(const unsigned n) : tableSize_(n) {}
  ~DispersionModule() {}
  // Operador () que hace el módulo de la clave k con el tamaño de la tabla hash.
  unsigned operator()(const Key& k) const { return k % tableSize_; }

 private:
  unsigned tableSize_; // tamaño de la tabla hash
};


/**
 * /////////////////////// PSEUDOALEATORIA ///////////////////////
 * @brief Clase DispersionPseudoaleatoria que hereda de DispersionFunction
 * Contiene un constructor propio de la clase que se encarga de inicializar el tamaño de la tabla hash
 * y el operador () que hace que la clase se comporte como una función
 * Como atributo privado tendremos el tamaño de la tabla hash
 * Contamos con template con class Key que será la clave que se va a dispersar.
 * @tparam Key clave que se va a dispersar en foma pseudoaleatoria. 
 * Pseudoaleatoria, h(k) = {srand(k); rand()}.
 */
template<class Key>
class DispersionPseudorandom : public DispersionFunction<Key> {
 public:
  // Constructor propio de la clase que se encarga de inicializar el tamaño de la tabla hash
  DispersionPseudorandom(const unsigned n) : tableSize_(n) {}
  ~DispersionPseudorandom() {}
  unsigned operator()(const Key& k) const;

 private:
  unsigned tableSize_; // tamaño de la tabla hash
}; 

/**
 * @brief Método que hace la dispersión de la clave k en forma pseudoaleatoria.
 * Pseudoaleatoria, h(k) = {srand(k); rand()}.
 * Para ello, lo que hacemos es que hacemos uso de srand(k) para que la semilla sea la clave k
 * y después hacemos uso de rand() para que nos devuelva un número pseudoaleatorio.
 * @tparam Key clave que se va a dispersar en foma pseudoaleatoria.
 * @param k clave que se va a dispersar
 * @return unsigned retorna el resultado de la dispersión
 */
template <class Key>
unsigned DispersionPseudorandom<Key>::operator()(const Key& k) const {
  srand(k);
  return rand() % tableSize_;
}

#endif // DISPERSIONFUNCTION_H