/**
 * ************ PRÁCTICA 1 *************
 * @file Cell.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-07
 * @brief Creación de la clase Autómata Celular. Esta es un modelo matemático y computacional para un sistema dinámico que
 * evoluciona en pasos discretos.
 * Los elementos básicos son
 * 1. espacio celular, consiste en un retículo [4] que se define sobre un espacio infinito regular n-dimensional. Puede ser una línea, espacio unidimensional; un plano, espacio
 * bidimensional, etc. Cada división homogénea del espacio se denomina celda o célula.
 * 2. n conjunto de estados, también denominado alfabeto. Cada célula toma un estado de este conjunto finito.
 * 3. Una vecindad define al conjunto finito de células consideradas adyacentes a una dada, así como 
 * la posición relativa de cada célula vecina respecto a ella.
 * 4. Una función de transición local, define cómo debe cambiar el estado de cada célula 
 * dependiendo de su estado anterior y de los estados anteriores de las células de su vecindad.
 * 5. Condiciones de frontera, en las implementaciones prácticas no es posible definir un retículo infinito, sino que se utilizan retículos finitos
 * 
 */

#include <iostream>
#include <vector>

#include "Lattice.h"

#ifndef CELL_H
#define CELL_H

// Declaración adelantada de la clase Lattice
class Lattice;

// Deficion de tipos --> similar a typedef
using State = bool;
using Position = int;

/**
 * @brief Enumerado que representa los dos posibles estados de una célula
 * DEAD REPRESENTA EL ESTADO 0
 * ALIVE REPRESENTA EL ESTADO 1
 */
enum StateValue { DEAD, ALIVE };

/**
 * @brief La célula, Cell,es responsable de encapsular su estado binario y su posición dentro del
 * retículo unidimensional que representa al espacio celular. También es responsable de
 * conocer su vecindad y su función de transición
 * 
 */
class Cell {
 public:
  // Constructor por defecto
  Cell() {}
  // El constructor de la célula recibe como parámetro su posición dentro del retículo, y
  // de forma opcional su estado en la configuración inicial. Por defecto, la célula se
  // crea con estado «0».
  Cell(const Position&, const State&);
  // Getters y setters de la clase
  State getState() const { return state_; }
  // método modificador para poder establecer la configuración inicial.
  void setState(State);
  // recibe el retículo por parámetro y calcula el siguiente estado sin evolucionar.
  int NextState(const Lattice&);
  // la evolución del autómata celular consiste en hacer que cada célula actualice su valor de estado.
  void UpdateState();
  // MODIFICACION --> REGLA 30
  int Rule30(const Lattice& lattice);
  // método que imprime el estado de la célula.
  friend std::ostream& operator<<(std::ostream&, const Cell&);
 private:
  State state_; // estado de la célula
  Position position_; // posición de la célula
  State next_state_; // siguiente estado de la célula, siguiente generacion
};

// Sobrecarga del operador de salida
std::ostream& operator<<(std::ostream&, const Cell&);

#endif // CELL_H