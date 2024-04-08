/**
 * @file Lattice1D.cc
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice1D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional.
 */

#include "Lattice1D.h"
#include "ac_exception.h"
#include "Position.h"
#include "FactoryCell.h"
#include "Cell.h"

/**
 * @brief Construct a new Lattice 1 D< Position Type>:: Lattice 1 D object
 * Constructor de la clase Lattice1D que se encarga de leer el tamaño del retículo y el estado de cada celda
 * @tparam PositionType Posición de la celda
 * @param file  fichero de entrada
 * @param factory fábrica de celdas
 */
template <typename PositionType>
Lattice1D<PositionType>::Lattice1D(std::fstream& file, FactoryCell<PositionType>& factory) {
  int dim;
  file >> dim;
  // Comprobamos que la dimensión sea correcta
  if (dim != 1) {
    throw ac_exception("Error: Dimensiones incorrectas");
  }
  // Leemos el tamaño del retículo
  file >> size_;
  cells_.resize(size_);
  char State;
  for (int i = 0; i < size_; i++) {
    file >> State;
    cells_[i] = factory.CreateCell(State);
  }
}

/**
 * @brief Construct a new Lattice 1 D< Position Type>:: Lattice 1 D object
 * Constructor de la clase Lattice1D que se encarga de inicializar el tamaño del retículo y el estado de cada celda
 * @tparam PositionType Posición de la celda
 * @param size tamaño del retículo
 * @param factory fábrica de celdas
 */
template <typename PositionType>
Lattice1D<PositionType>::Lattice1D(int size, FactoryCell<PositionType>& factory) : size_(size) {
  // Inicializamos el vector de celdas
  cells_.resize(size_);
  for (int i = 0; i < size_; i++) {
    cells_[i] = factory.CreateCell();
  }
}

/**
 * @brief Destroy the Lattice 1 D< Position Type>:: Lattice 1 D object
 * Destructor de la clase Lattice1D que se encarga de liberar la memoria de cada celda
 * @tparam PositionType Posición de la celda
 */
template <typename PositionType>
Lattice1D<PositionType>::~Lattice1D() {
  for (int i = 0; i < size_; i++) {
    delete cells_[i];
  }
}

/**
 * @brief Método que se encarga de calcular el siguiente estado de todas las celdas del retículo.
 * Para ello, se utiliza el método NextState de la clase Cell
 * @tparam PositionType   Posición de la celda
 */
template <typename PositionType>
void Lattice1D<PositionType>::NextGeneration() {
  for (int i = 0; i < size_; i++) {
    cells_[i]->NextState(*this);
  }
  for (int i = 0; i < size_; i++) {
    cells_[i]->UpdateState();
  }
}

/**
 * @brief Setters and Getters
 * Se encargan de cambiar y devolver el tamaño del retículo
 * @tparam PositionType posición de la celda
 * @param size  nuevo tamaño del retículo
 */
template <typename PositionType>
void Lattice1D<PositionType>::SetSize(int size) {
  size_ = size;
  cells_.resize(size_);
}

/**
 * @brief Método que se encarga de devolver el tamaño del retículo
 * @tparam PositionType posición de la celda
 * @return int tamaño del retículo
 */
template <typename PositionType>
int Lattice1D<PositionType>::GetSize() const {
  return size_;
}

/**
 * @brief Método que se encarga de devolver el número de celdas vivas del retículo
 * Para ello, se recorre el vector de celdas y se comprueba si el estado de cada celda es kAlive
 * @tparam PositionType Posición de la celda
 * @return std::size_t recuento de celdas vivas
 */
template <typename PositionType>
std::size_t Lattice1D<PositionType>::Population() const {
  std::size_t population = 0;
  for (int i = 0; i < size_; i++) {
    if (cells_[i]->GetState() == State::kAlive) {
      population++;
    }
  }
  return population;
}

/**
 * @brief Metodo que se encarga de mostrar el estado de todas las celdas del retículo
 * Para ello, se recorre el vector de celdas y se utiliza el método Display de la clase Cell
 * @tparam PositionType Posición de la celda
 * @param os flujo de salida
 * @return std::ostream& flujo de salida
 */
template <typename PositionType>
std::ostream& Lattice1D<PositionType>::Display(std::ostream& os) const {
  for (int i = 0; i < size_; i++) {
    cells_[i]->Display(os);
  }
  return os;
}
