/**
 * ************ PRÁCTICA 2 *************
 * @file Lattice.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-22
 * @brief Creación de la clase Retículo. 
 * En esta clase se definen los métodos y atributos necesarios para crear y almacenar las 
 * células que representan el espacio celular. 
 * Controla la evolución y lleva la cuenta de las generaciones. 
 * Se definen los métodos necesarios para la creación del retículo, la evolución del autómata 
 * celular y la impresión del estado del retículo.
 * Ademas, tenemos los atributos privados de la clase, que son el vector de vectores de células, 
 * el número de filas y columnas y el tipo de frontera.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <new>
#include <limits>
#include <utility>
#include <sstream>

#ifndef LATTICE_H
#define LATTICE_H

#include "Cell.h"

/**
 * @brief Enumerado que representa los tres posibles tipos de frontera
 * Puede ser abierta, periodica, refleciva o sin frontera
 */
enum BorderType { PERIODIC, REFLECTIVE, OPEN, NOFRONTER };

// Declaración adelantada de la clase Cell
class Cell;

/**
 * @brief Clase Retículo 
 * Esta clase contiene los métodos y atributos necesarios para crear y almacenar las 
 * células que representan el espacio celular. Controla la evolución y lleva la cuenta de las generaciones.
 */
class Lattice {
 public:
  // Constructores de la clase
  // Constructor para cuando se le pasa -size
  Lattice(const BorderType& border, char* argv[]);
  // Constructor para cuando se pasa -init
  Lattice(const BorderType& border, std::string& filename, char* argv[]);
  // Destructor de la clase
  ~Lattice();
  // Metodos
  void requestUserInput(int i, int j);
  void applyBorders(const BorderType& borderType, char* argv[]);
  // Getters de la clase
  int getRows() const { return rows_; }
  int getColumns() const { return columns_; }
  // método que devuelve la célula en la posición dada.
  const Cell& getCell(const Position&) const;
  // getter de border
  const BorderType& getBorder() const;
  // setter para filas
  void setRows(int);
  // setter para columnas
  void setColumns(int);
  // método que evoluciona el autómata celular.
  void NextGeneration();
  std::string SaveToString(std::string& lattice);
  // Funcion para saber cuantas celulas vivas hay cada generacion
  std::size_t Population() const;
  // método que imprime el estado del retículo.
  friend std::ostream& operator<<(std::ostream&, const Lattice&);
  // Sobrecarga del oprador []  para acceder a las células
  Cell& operator[](const Position&);

 private:
  // Vector de vectores de células --> matriz de células
  std::vector<std::vector<Cell*>> cells_;
  int rows_;
  int columns_;
  // tipo de frontera
  BorderType borderType_;
};

// Sobrecarga del operador de salida
std::ostream& operator<<(std::ostream&, const Lattice&);

#endif // LATTICE_H