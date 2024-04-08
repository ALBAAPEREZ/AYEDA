/**
 * @file FuncionesAuxiliares.cc
 * @author ALBA PÉREZ RODRÍGUEZ 
 * @version 0.1
 * @date 2024-03-25
 * @brief Funciones auxiliares que se van a usar en el main.
 * Se define las funcoines de usage, parseargs y un struct para guardar los argumentos. 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "FuncionesAuxiliares.h"

/**
 * @brief Funcion que imprime un mensaje rodeado de 
 * asteriscos en forma de caja. La utilizaremos para mostrar
 * mensajes de error o información.
 * @param message mensaje que se quiere mostrar en la caja.
 */
void PrintBox(const std::string& message) {
  int length = message.length();
  std::cout << std::string(length + 4, '*') << std::endl;
  std::cout << "* " << message << " *" << std::endl;
  std::cout << std::string(length + 4, '*') << std::endl;
}

/**
 * @brief Funcion que muestra el uso del programa.
 * Si no se han introducido argumentos, se muestra un mensaje de error. Las opciones -h y --help
 * muestran el modo de uso del programa.
 * 1. La opcion  -size <s> : Tamaño de la secuencia (s) obligatorio
 * 2. La opcion  -ord <m> : Código que identifica un método de ordenación (m) obligatorio
 * 3. La opcion  -init <i> : Forma de introducir los datos de la secuencia
 * 4. La opcion  -trace <y|n> : Indica si se muestra o no la traza durante la ejecución
 * @param argc número de argumentos pasados por línea de comandos.
 * @param argv nombre del programa y argumentos pasados por línea de comandos.
 */
void Usage(int argc, char* argv[]) {
  if (argc == 1) {
    PrintBox("No se han introducido argumentos. Pruebe con '" + std::string(argv[0]) + " --help' para más información");
    exit(EXIT_FAILURE);
  }
  if ((argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h"))) {
    PrintBox("Funcionalidades del programa:");
    std::cout << "  Este programa se encarga de ordenar una secuencia de elementos utilizando diferentes métodos de ordenación." << std::endl;
    std::cout << std::endl;
    PrintBox("Modo de empleo:");
    std::cout << "  " << argv[0] << " -size <s> -ord <m> -init <i> [f] -trace <y|n>" << std::endl;
    std::cout << "Donde:" << std::endl;
    std::cout << "  -size <s>   : Tamaño de la secuencia (s) obligatorio" << std::endl;
    std::cout << "  -ord <m>    : Código que identifica un método de ordenación (m) obligatorio" << std::endl;
    std::cout << "  -init <i>   : Forma de introducir los datos de la secuencia" << std::endl;
    std::cout << "                i=manual" << std::endl;
    std::cout << "                i=random" << std::endl;
    std::cout << "                i=file f=nombre del fichero de entrada" << std::endl;
    std::cout << "  -trace <y|n>: Indica si se muestra o no la traza durante la ejecución" << std::endl;
    std::cout << std::endl;
    PrintBox("Ejemplos de uso:");
    std::cout << "  " << argv[0] << " -size 100 -ord 1 -init manual -trace y" << std::endl;
    std::cout << "  " << argv[0] << " -size 100 -ord 1 -init file fichero.txt -trace n" << std::endl;
    std::cout << "  " << argv[0] << " -size 100 -ord 1 -init random -trace y" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Función que comprueba los argumentos pasados por línea de comandos.
 * Se comprueba que se han pasado los argumentos obligatorios. 
 * Si no se han pasado, se muestra el modo de uso del programa.
 * @param argc Número de argumentos pasados por línea de comandos.
 * @param argv nombre del programa y argumentos pasados por línea de comandos.
 * @return Options retorna una estructura Options que contiene las opciones que se pueden pasar por línea de comandos.
 */
Options ParseArguments(int argc, char* argv[]) {
  Usage(argc, argv);
  Options options;
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-size") {
      if (i + 1 < argc) {
        options.sequenceSize = std::stoi(argv[i + 1]);
      } else {
        std::cerr << "El tamaño de la secuencia es obligatorio" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    if (std::string(argv[i]) == "-ord") {
      if (i + 1 < argc) {
        options.ordenationType = std::string(argv[i + 1]);
      } else {
        std::cerr << "El método de ordenación es obligatorio" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    if (std::string(argv[i]) == "-init") {
      if (i + 1 < argc) {
        options.introducingData = std::string(argv[i + 1]);
        if (options.introducingData == "file") {
          if (i + 2 < argc) {
            options.fileName = std::string(argv[i + 2]);
          } else {
            std::cerr << "El nombre del fichero es obligatorio" << std::endl;
            exit(EXIT_FAILURE);
          }
        }
      } else {
        std::cerr << "La forma de introducir los datos es obligatoria" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    if (std::string(argv[i]) == "-trace") {
      if (i + 1 < argc) {
        if (std::string(argv[i + 1]) == "y") {
          options.trace = true;
        } else if (std::string(argv[i + 1]) == "n") {
          options.trace = false;
        } else {
          std::cerr << "El valor de trace debe ser 'y' o 'n'" << std::endl;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "El valor de trace es obligatorio" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  return options;
}