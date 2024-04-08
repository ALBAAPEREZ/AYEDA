/**
 * @file main.cc
 * @author ALBA PÉREZ
 * @version 0.1
 * @date 2024-03-10
 * @copyright Copyright (c) 2024
 * @brief Programa principal que implementa una tabla hash con dispersión de tipo abierto y cerrado.
 * a.. -ts <s>, s es el tamaño de la tabla.
 * b. -fd <f>, f es el código que identifica a una función de dispersión.
 * c. -hash <open|close>, indica la técnica de dispersión a utilizar. Implica el tipo de secuencia utilizada para el parámetro Container.
 * d. -bs <s>, s es el tamaño del bloque. Sólo para dispersión cerrada.
 * e. -fe <f>, f es el código que identifica a una función de exploración. Sólo para dispersión cerrada.
 */

#include <iostream>
#include <string>
#include <iomanip>

#include "AuxiliarFunctions.h"
#include "ExplorationFunctions.h"
#include "DispersionFunction.h"
#include "HashTable.h"
#include "Sequence.h"
#include "nif.h"

/**
 * @brief Funcion principal que implementa una tabla hash con dispersión de tipo abierto y cerrado.
 * Codigos de la función de dispersión:
 * 0. Modulo
 * 1. PseudoRandom
 * 2. Sum
 * Codigos de la función de exploración:
 * 0. Lineal
 * 1. Cuadrática
 * 2. Doble dispersión
 * 3. PseudoRandom
 * 
 * @param argc parámetro que cuenta el número de argumentos pasados por línea de comandos.
 * @param argv parámetro que almacena los argumentos pasados por línea de comandos.
 * @return int retorna 0 si el programa se ha ejecutado correctamente.
 */
int main(int argc, char* argv[]) {
  // Comprobamos que se han pasado los argumentos necesarios
  Usage(argc, argv);
  Options options;
  try {
    options = ParseArguments(argc, argv);
  } catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "\n\n";
  std::cout << "╔════════════════════════════════════════════╗\n";
  std::cout << "║             DATOS DE LA TABLA HASH         ║\n";
  std::cout << "╠════════════════════════════════════════════╣\n";
  std::cout << "║ Tamaño de la tabla:        " << std::setw(10) << std::left << options.tableSize << "      ║\n";
  std::cout << "║ Función de dispersión:     " << std::setw(10) << std::left << options.dispersionFunction << "      ║\n";
  std::cout << "║ Tipo de hash:              " << std::setw(10) << std::left << options.hashType << "      ║\n";
  std::cout << "║ Tamaño del bloque:         " << std::setw(10) << std::left << options.blockSize << "      ║\n";
  std::cout << "║ Función de exploración:    " << std::setw(10) << std::left << options.explorationFunction << "      ║\n";
  std::cout << "╚════════════════════════════════════════════╝\n";
  // punteros a las clases de dispersion y exploracion
  DispersionFunction<Nif>* dispersion = nullptr;
  ExplorationFunction<Nif>* exploration = nullptr;
  // Codigo de funcion de dispersión 
  if (options.dispersionFunction == "0") {
    std::cout << "Funcion de dispersion Modulo" << std::endl;
    dispersion = new DispersionModule<Nif>(options.tableSize);
  } else if (options.dispersionFunction == "1") {
    std::cout << "Funcion de dispersion PseudoRandom" << std::endl;
    dispersion = new DispersionPseudorandom<Nif>(options.tableSize);
  } else if (options.dispersionFunction == "2") {
    std::cout << "Funcion de dispersion Suma" << std::endl;
    dispersion = new DispersionSum<Nif>(options.tableSize);
  } else {
    std::cout << "Código de función de dispersión incorrecto" << std::endl;
    std::cout << "Introduce o 0 para Modulo, 1 para PseudoRandom o 2 para Suma" << std::endl;
    exit(EXIT_FAILURE);
  }
  // codigo de funcion de exploración
  if (options.hashType == "close") {
    if (options.explorationFunction == "0") {
      std::cout << "Funcion de exploracion Lineal" << std::endl;
      exploration = new ExplorationFunctionLineal<Nif>();
    } else if (options.explorationFunction == "1") {
      std::cout << "Funcion de exploracion Cuadratica" << std::endl;
      exploration = new ExplorationFunctionCuadratic<Nif>();
    } else if (options.explorationFunction == "2") {
      std::cout << "Funcion de exploracion Doble dispersión" << std::endl;
      exploration = new ExplorationFunctionDoubleDispersion<Nif>(dispersion);
    } else if (options.explorationFunction == "3") {
      std::cout << "Funcion de exploracion Redispersion" << std::endl;
      exploration = new ExplorationFunctionRedispersion<Nif>();
    } else {
      std::cout << "Código de función de exploración incorrecto" << std::endl;
      std::cout << "Introduce o 0 para Lineal, 1 para Cuadrática, 2 para Doble dispersión o 3 para PseudoRandom" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  // puntero a la clase hashtable dynamic
  HashTable<Nif, DynamicSequence<Nif>>* hashTable_dynamic = nullptr;
  HashTable<Nif, StaticSequence<Nif>>* hashTable_static = nullptr;
  // tipo de hash --> abierta o cerrada
  if (options.hashType == "open") {
    std::cout << "Tabla hash de dispersión abierta" << std::endl;
    hashTable_dynamic = new HashTable<Nif, DynamicSequence<Nif>>(options.tableSize, *dispersion, *exploration);
    hashTable_dynamic->menu();
  } else if (options.hashType == "close") {
    std::cout << "Tabla hash de dispersión cerrada" << std::endl;
    hashTable_static = new HashTable<Nif, StaticSequence<Nif>>(options.tableSize, *dispersion, *exploration, options.blockSize);
    hashTable_static->menu();
  }
  // liberamos memoria
  delete dispersion;
  delete exploration;
  delete hashTable_dynamic;
  delete hashTable_static;
  return 0;
}

