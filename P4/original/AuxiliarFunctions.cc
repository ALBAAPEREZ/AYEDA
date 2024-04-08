/**
 * @file AuxiliarFunctions.h
 * @author ALBA PÉREZ
 * @version 0.1
 * @date 2024-03-10
 * @copyright Copyright (c) 2024
 * @brief Funciones auxiliares.
 * Contamos con la funcio usage que nos muestra el modo de uso del programa.
 * Funciones que compruebam los argumentos pasados por línea de comandos. 
 * Si son incorrectos, muestra el modo de uso.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "AuxiliarFunctions.h"

/**
 * @brief Funcion que muestra el modo de uso del programa.
 * Si se introduce el comando --help o -h, se muestra el modo de uso del programa.
 * -ts es el tamaño de la tabla. OBLIGATORIO.
 * -fd es el código que identifica a una función de dispersión. OBLIGATORIO.
 * -hash es la técnica de dispersión a utilizar. OBLIGATORIO. 
 * -bs es el tamaño del bloque. Sólo para dispersión CERRADA.
 * -fe es el código que identifica a una función de exploración. Sólo para dispersión CERRADA. 
 * @param argc parámetro que cuenta el número de argumentos pasados por línea de comandos.
 * @param argv parámetro que almacena los argumentos pasados por línea de comandos.
 */
void Usage(int argc, char* argv[]) {
  if (argc == 1) {
    std::cout << "No se han introducido argumentos. Pruebe con '" << argv[0] << " --help' para más información" << std::endl;
    exit(EXIT_FAILURE);
  }
  if ((argc == 2 && std::string(argv[1]) == "--help") || std::string(argv[1]) == "-h") {
    std::cout << std::endl;
    std::cout << "Modo de empleo: " << argv[0] << " -ts <s> -fd <f> -hash <open|close> -bs <s> -fe <f>" << std::endl;
    std::cout << "Donde: " << std::endl;
    std::cout << "  -ts <s> : Tamaño de la tabla (s) obligatorio" << std::endl;
    std::cout << "  -fd <f> : Código que identifica a una función de dispersión (f) obligatorio" << std::endl;
    std::cout << "  -hash <open|close> : Técnica de dispersión a utilizar. Implica el tipo de secuencia utilizada para el parámetro Container. Obligatorio." << std::endl;
    std::cout << "  -bs <s> : Tamaño del bloque. Sólo para dispersión cerrada." << std::endl;
    std::cout << "  -fe <f> : Código que identifica a una función de exploración. Sólo para dispersión cerrada." << std::endl;
    std::cout << std::endl;
    std::cout << "Funcionalidades del programa:" << std::endl;
    std::cout << "  Este programa se encarga de realizar operaciones de dispersión en una tabla utilizando diferentes técnicas y funciones." << std::endl;
    std::cout << std::endl;
    std::cout << "Ejemplo de uso para dispersion cerrada: " << argv[0] << " -ts 100 -fd 1 -hash close -bs 10 -fe 2" << std::endl;
    std::cout << "Ejemplo de uso para disperion abierta: " << argv[0] << " -ts 100 -fd 1 -hash open" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Función que comprueba los argumentos pasados por línea de comandos.
 * Se comprueba que se han pasado los argumentos obligatorios. 
 * Si no se han pasado, se muestra el modo de uso del programa.
 * @param argc parámetro que cuenta el número de argumentos pasados por línea de comandos.
 * @param argv almacena los argumentos pasados por línea de comandos.
 * @return Options retorna una estructura Options que contiene las opciones que se pueden pasar por línea de comandos.
 */
Options ParseArguments(int argc, char* argv[]) {
  // Comprobamos que se han pasado los argumentos obligatorios
  Options options;
  bool hasTableSize = false;
  bool hasDispersionFunction = false;
  bool hasHashType = false;
  bool hasBlockSize = false;
  bool hasExplorationFunction = false;
  // Si se han pasado menos de 4 argumentos, faltan argumentos obligatorios
  if (argc < 4) {
    std::cerr << "Faltan argumentos obligatorios.\n";
    Usage(argc, argv);
    throw std::invalid_argument("Faltan argumentos obligatorios.");
  }
  // Recorremos la lista de argumentos
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-ts") {
      if (i + 1 < argc) {
        options.tableSize = std::stoi(argv[i + 1]);
        hasTableSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -ts");
      }
    } else if (arg == "-fd") {
      if (i + 1 < argc) {
        options.dispersionFunction = argv[i + 1];
        hasDispersionFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -fd");
      }
    } else if(arg == "-hash") {
      if (i + 1 < argc) {
        options.hashType = argv[i + 1];
        hasHashType = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -hash");
      }
    } else if (arg == "-bs") {
      if (i + 1 < argc) {
        options.blockSize = std::stoi(argv[i + 1]);
        hasBlockSize = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción -bs");
      }
    } else if (arg == "-fe") {
      if (i + 1 < argc) {
        options.explorationFunction = argv[i + 1];
        hasExplorationFunction = true;
        ++i;
      } else {
        throw std::invalid_argument("Falta el argumento para la opción " + arg);
      }
    } else {
      throw std::invalid_argument("Opción desconocida");
    }
  }
  if (!hasTableSize || !hasDispersionFunction || !hasHashType) {
    throw std::invalid_argument("Faltan argumentos oobligatorios");
  }
  return options;
}
