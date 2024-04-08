/**
 * @file Lattice.cc
 * @author ALBA PEREZ
 * @version 0.1
 * @date 2024-03-03
 * @brief IMplementación de la clase Lattice. Esta posee un método que se encarga de mostrar el retículo
 * Además, se sobrecarga el operador de salida para mostrar el retículo Y se implementa el constructor y el destructor de la clase
 * 
 */

#include "Lattice.h"

/**
 * @brief Construct a new Lattice< Position Type>:: Lattice object
 * Constructor de la clase Lattice, por defecto
 * @tparam PositionType Posición de la celda
 */
template <typename PositionType>
Lattice<PositionType>::Lattice() {}

/**
 * @brief Destroy the Lattice< Position Type>:: Lattice object
 * Destructor de la clase Lattice que se encarga de liberar la memoria de cada celda
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
Lattice<PositionType>::~Lattice() {}

/**
 * @brief Método que se encarga de devolver el tamaño del retículo
 * @tparam PositionType Posición de la celda
 * @param os Flujo de salida
 * @return std::ostream& referencia al flujo de salida
 */
template <typename PositionType>
std::ostream& Lattice<PositionType>::Display(std::ostream& os) const {
  return os;
}

/**
 * @brief sobrecarga del operador de salida para mostrar el retículo
 * Se encarga de mostrar el retículo
 * @tparam PositionType Posición de la celda
 * @param os Flujo de salida
 * @param lattice retículo a mostrar
 * @return std::ostream& flujo de salida
 */
template <typename PositionType>
std::ostream& operator<<(std::ostream& os, const Lattice<PositionType>& lattice) {
  return lattice.Display(os);
}