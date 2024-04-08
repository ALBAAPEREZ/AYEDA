/**
 * @file Lattice2D.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice2D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo bidimensional.
 */

#include "Lattice2D.h"

/**
 * @brief Construct a new Lattice 2 D< Position Type>:: Lattice 2 D object
 * Constructor de la clase Lattice2D que se encarga de leer el tamaño del retículo y el estado de cada celda
 * @tparam PositionType Posición de la celda
 * @param file  fichero de entrada
 * @param factory fábrica de celdas
 */
template <typename PositionType>
Lattice2D<PositionType>::Lattice2D(std::fstream& file, FactoryCell<PositionType>& factory) {
  int dim;
  file >> dim;
  // Comprobamos que la dimensión sea correcta
  if (dim != 2) {
    throw ac_exception("Error: Dimensiones incorrectas");
  }
  int rows, cols;
  file >> rows >> cols;
  cells_.resize(rows);
  // Leemos el tamaño del retículo
  for (int i = 0; i < rows; i++) {
    cells_[i].resize(cols);
  }
  // Leemos el estado de cada celda
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      char State;
      file >> State;
      cells_[i][j] = factory.CreateCell(*new PositionType(2, i, j), State);
    }
  }
}

/**
 * @brief Destroy the Lattice 2 D< Position Type>:: Lattice 2 D object
 * Destructor de la clase Lattice2D que se encarga de liberar la memoria de cada celda
 * @tparam PositionType Posición de la celda
 */
template <typename PositionType>
Lattice2D<PositionType>::~Lattice2D() {
  for (int i = 0; i < cells_.size(); i++) {
    for (int j = 0; j < cells_[i].size(); j++) {
      delete cells_[i][j];
    }
  }
}

/**
 * @brief Método que se encarga de calcular el siguiente estado de todas las celdas del retículo.
 * se utiliza el método NextState de la clase Cell.
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
void Lattice2D<PositionType>::NextGeneration() {
  // Calculamos el siguiente estado de todas las celdas
  for (int i = 0; i < cells_.size(); i++) {
    for (int j = 0; j < cells_[i].size(); j++) {
      cells_[i][j]->NextState(*this);
    }
  }
  // Actualizamos el estado de todas las celdas
  for (int i = 0; i < cells_.size(); i++) {
    for (int j = 0; j < cells_[i].size(); j++) {
      cells_[i][j]->UpdateState();
    }
  }
}

/**
 * @brief Método que se encarga de decir cuántas celdas están en estado vivo.
 * @tparam PositionType Posición de la celda
 * @return std::size_t retorna el número de celdas vivas
 */
template <typename PositionType>
std::size_t Lattice2D<PositionType>::Population() const {
  std::size_t population = 0;
  for (int i = 0; i < cells_.size(); i++) {
    for (int j = 0; j < cells_[i].size(); j++) {
      // Comprobamos si la celda está viva
      if (cells_[i][j]->GetState() == '1') {
        population++;
      }
    }
  }
  return population;
}

/**
 * @brief Método que se encarga de mostrar el estado de todas las celdas del retículo.
 * @tparam PositionType posición de la celda
 * @param os flujo de salida
 * @return std::ostream&  flujo de salida
 */
template <typename PositionType>
std::ostream& Lattice2D<PositionType>::Display(std::ostream& os) const {
  for (int i = 0; i < cells_.size(); i++) {
    for (int j = 0; j < cells_[i].size(); j++) {
      os << cells_[i][j];
    }
    os << std::endl;
  }
  return os;
}