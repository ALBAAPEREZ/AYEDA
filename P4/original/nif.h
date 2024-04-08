/**
 * @file nif.h
 * @author ALBA PÉREZ RODRÍGUEZ 
 * @version 0.1
 * @date 2024-03-10
 * @copyright Copyright (c) 2024
 * @brief El tipo de dato nif representa la parte numérica del número de identificación fiscal.
 * Encapsula un número entero de 8 dígitos, e implementa las operaciones necesarias para
 * poder utilizarlo como tipo de dato Key.
 */

#ifndef NIF_H
#define NIF_H

#include <iostream>
#include <string>
#include <cstdlib>

/**
 * @brief Clase Nif que representa la parte numérica del número de identificación fiscal.
 * Encapsula un número entero de 8 dígitos, e implementa las operaciones necesarias para
 * poder utilizarlo como tipo de dato Key.
 */
class Nif {
 public:
  // Constructor por defecto crea un Nif aleatorio
  Nif() : value_(std::rand() % 100000000) {}
  // Constructor de cambio de tipo a partir de un dato entero long
  Nif(long value) : value_(value) {}
  // Sobrecarga de los operadores de comparación
  bool operator==(const Nif& other) const;
  bool operator!=(const Nif& other) const;
  // Sobrecarga del operador de cambio de tipo a long
  operator long() const { return value_; }
  friend std::ostream& operator<<(std::ostream& os, const Nif& nif);
  friend std::istream& operator>>(std::istream& is, Nif& nif);
  Nif operator=(const Nif& k);

 private:
  long value_; // Número de identificación fiscal
};

// ========================= MÉTODOS =========================

/**
 * @brief Sobrecarga del operador de comparación !=
 * Sirve para comparar dos Nif Saber si son iguales o no
 * @param other otro Nif
 * @return true retorna true si los dos Nif son diferentes
 * @return false retorna false si los dos Nif son iguales
 */
bool Nif::operator==(const Nif& other) const {
  std::cout << value_ << " == " << other.value_ << std::endl;
  return value_ == other.value_;
}

/**
 * @brief Sobrecarga del operador de comparación !=
 * Sirve para comparar dos Nif Saber si son iguales o no
 * @param other otro Nif
 * @return true retorna true si los dos Nif son diferentes
 * @return false retorna false si los dos Nif son iguales
 */ 
bool Nif::operator!=(const Nif& other) const {
  std::cout << value_ << " != " << other.value_ << std::endl;
  return value_ != other.value_;
}

/**
 * @brief Sobrecarga del operador de entrada >>
 * Sirve para introducir un Nif por teclado
 * @param is flujo de entrada
 * @return std::istream& retorna el flujo de entrada
 */
std::istream& operator>>(std::istream& is, Nif& nif) {
  is >> nif.value_;
  return is;
}

/**
 * @brief Operador de asignación
 * Sirve para asignar un Nif a otro
 * @param k clave que se va a asignar
 * @return Nif retorna el Nif asignado
 */
Nif Nif::operator=(const Nif& k) {
  value_ = k.value_;
  return *this;
}

/**
 * @brief Sobrecarga del operador de salida <<
 * sirve para imprimir un Nif por pantalla
 * @param os flujo de salida
 * @param nif Nif que se va a imprimir
 * @return std::ostream&  retorna el flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const Nif& nif) {
  os << nif.value_;
  return os;
}

#endif // NIF_H