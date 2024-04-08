/**
 * @file Nif.h
 * @author ALBA PEREZ 
 * @version 0.1
 * @date 2024-03-26
 * @brief Clase Nif que representa la parte numérica del número de identificación fiscal.
 * Encapsula un número entero de 8 dígitos, e implementa las operaciones necesarias para
 * poder utilizarlo como tipo de dato Key. 
 */

#ifndef NIF_H
#define NIF_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

/**
 * @brief Clase Nif que representa la parte numérica del número de identificación fiscal.
 * Encapsula un número entero de 8 dígitos, e implementa las operaciones necesarias para
 * poder utilizarlo como tipo de dato Key.
 * 
 */
class Nif {
 public:
  // Constructor por defecto crea un Nif aleatorio
  Nif();
  Nif(const long& other);
  Nif(const Nif& other);
  bool operator==(const Nif& other) const;
  bool operator<(const Nif& other) const;
  bool operator>(const Nif& other) const;
  bool operator!=(const Nif& other) const;
  Nif operator=(const Nif& other);
  bool operator<=(const Nif& other) const;
  operator long() const { return value_; }
  friend std::ostream& operator<<(std::ostream& os, const Nif& nif);

 private:
  long value_; // Número de identificación fiscal
};

/////////////////////////// METODOS ///////////////////////////

/**
 * @brief Constructor por defecto de la clase Nif.
 * Genera un Nif aleatorio.
*/
Nif::Nif() {
  srand(time(nullptr));
  value_ = rand() % 100000000;
}

/**
 * @brief Constructor de copia de la clase Nif.
 * @param other Nif que se va a copiar.
*/
Nif::Nif(const Nif& other) {
  value_ = other.value_;
}


/**
 * @brief Constructor de copia de la clase Nif.
 * @param other Nif que se va a copiar.
*/
Nif::Nif(const long& other) {
  value_ = other;
}

/**
 * @brief Sobrecarga del operador < para comparar dos Nif.
 * @param other Nif con el que se va a comparar.
 * @return true si el Nif es menor que other, false en caso contrario.
*/
bool Nif::operator==(const Nif& other) const {
  return value_ == other.value_;
}

/**
 * @brief Sobrecarga del operador < para comparar dos Nif.
 * @param other Nif con el que se va a comparar.
 * @return true si el Nif es menor que other, false en caso contrario.
*/
bool Nif::operator<(const Nif& other) const {
  return value_ < other.value_;
}

/**
 * @brief Sobrecarga del operador > para comparar dos Nif.
 * @param other Nif con el que se va a comparar.
 * @return true si el Nif es mayor que other, false en caso contrario.
*/
bool Nif::operator>(const Nif& other) const {
  return value_ > other.value_;
}

/**
 * @brief Sobrecarga del operador != para comparar dos Nif.
 * @param other Nif con el que se va a comparar.
 * @return true si el Nif es distinto que other, false en caso contrario.
*/
bool Nif::operator!=(const Nif& other) const {
  return value_ != other.value_;
}

/**
 * @brief Sobrecarga del operador = para asignar un Nif a otro.
 * @param other Nif que se va a asignar.
 * @return Nif& Nif asignado.
*/
Nif Nif::operator=(const Nif& other) {
  if (this != &other) {
    value_ = other.value_;
  }
  return *this;
}

/**
 * @brief Sobrecarga del operador <= para comparar dos Nif.
 * @param other Nif con el que se va a comparar.
 * @return true si el Nif es menor o igual que other, false en caso contrario.
*/
bool Nif::operator<=(const Nif& other) const {
  return value_ <= other.value_;
}

/**
 * @brief Sobrecarga del operador << para mostrar un Nif.
 * @param os flujo de salida.
 * @return flujo de salida.
*/
std::ostream& operator<<(std::ostream& os, const Nif& nif) {
  os << nif.value_;
  return os;
}


#endif // NIF_H