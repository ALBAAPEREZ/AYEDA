/**
 * ************ PRÁCTICA 2 *************
 * @file main.cc
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-22
 * @brief Programa principal. Este programa se encarga de hacer un autómata celular. 
 * En este programa se recibe por línea de comandos el tamaño del retículo, el tipo de frontera 
 * y el archivo de configuración inicial. Encontramos las funciones Usage, checkArgs, SaveToFile 
 * y CellEvolution. Cada una de estas funciones se encarga de una tarea específica.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

#include "Cell.h"
#include "Lattice.h"

/**
 * @brief Función que imprime el modo de empleo del programa
 * Si no se especifica ningún argumento o se especifica --help, se imprime el modo de empleo
 * @param argc número de argumentos
 * @param argv nombre de los argumentos
 */
void Usage(int argc, char* argv[]) {
  if (argc == 1) {
    std::cout << "No se han introducido argumentos. Pruebe con '" << argv[0] << " --help' para más información" << std::endl;
    exit(EXIT_FAILURE);
  }
  if ((argc == 2 && std::string(argv[1]) == "--help") || std::string(argv[1]) == "-h") {
    std::cout << "Modo de empleo: " << argv[0] << " -size <M> <N> -border <type> [0|1] [-init <file>]" << std::endl;
    std::cout << "Donde: " << std::endl;
    std::cout << "  -size <M> <N> : Tamaño del retículo (número de filas M y número de columnas N) obligatorio" << std::endl;
    std::cout << "  -border <type> [0|1]: Tipo de frontera. Puede ser 'open', 'periodic', 'reflective' o 'sin frontera'. Obligatorio." << std::endl;
    std::cout << "  -init <file> : Archivo de configuración inicial (opcional)" << std::endl;
    std::cout << std::endl;
    std::cout << "Funcionalidades del programa:" << std::endl;
    std::cout << "  Este programa se encarga de hacer un autómata celular. Este es un modelo matemático y computacional para un sistema dinámico ";
    std::cout << "  que evoluciona en pasos discretos. Es adecuado para modelar sistemas naturales que puedan ser" << std::endl;
    std::cout << "  descritos como una colección masiva de objetos simples que interactúan localmente." << std::endl;
    std::cout << std::endl;
    std::cout << "Comandos del usuario durante la simulación:" << std::endl;
    std::cout << "  'x': Finaliza la ejecución del programa" << std::endl;
    std::cout << "  'n': Calcula y muestra la siguiente generación" << std::endl;
    std::cout << "  'L': Calcula y muestra las siguientes cinco generaciones" << std::endl;
    std::cout << "  'c': Los comandos 'n' y 'L' dejan de mostrar el estado del tablero y sólo se muestra la población" << std::endl;
    std::cout << "  's': Salva el tablero a un fichero" << std::endl;
    std::cout << std::endl;
    std::cout << "Ejemplo de uso con -size: " << argv[0] << " -size 10 10 -border open 1 " << std::endl;
    std::cout << "Ejemplo de uso con -init: " << argv[0] << " -border open 1 -init file.txt" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Funcion que se encarga de comprobar los argumentos
 * Hace todo el control de versiones de los argumentos.
 * @param argc es el número de argumentos
 * @param argv es el nombre de los argumentos
 * @param size tamaño del reticulo
 * @param borderType tipo de frontera que se le asigna al retículo por linea de comandos
 */
void checkArgs(int argc, char* argv[], int& row_num, int& column_num, BorderType& bordertype, std::string& file_name) {
  // Set default values to row_num and column_num to avoid uninitialized variables
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    // Check that at least one argument has been entered
    if (argc < 2) {
      std::cerr << "Incorrect usage. You must provide at least one argument." << std::endl;
      exit(EXIT_FAILURE);
    }
    // If argv[i] is -size
    if (arg == "-size") {
      if (i + 2 < argc && isdigit(argv[i+1][0]) && isdigit(argv[i+2][0])) {
        row_num = std::stoi(argv[++i]);
        column_num = std::stoi(argv[++i]);
        if (row_num <= 0 || column_num <= 0) {
          std::cerr << "El tamaño del retículo debe ser un número entero positivo" << std::endl;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "Tamaño del retículo no encontrado. Use '-size <n>'" << std::endl;
        exit(EXIT_FAILURE);
      }
      // Fronteras del retículo --> open, periodic, reflective, noborder
      if (i + 1 < argc && std::string(argv[i + 1]) == "-border") {
        i++;
        if (i + 1 < argc) {
          std::string borderArg = argv[++i];
          if (borderArg == "open") {
            bordertype = OPEN;
          } else if (borderArg == "periodic") {
            bordertype = PERIODIC;
          } else if (borderArg == "reflective") {
            bordertype = REFLECTIVE;
          } else if (borderArg == "noborder") {
            bordertype = NOFRONTER;
          }
          if (i + 1 < argc && isdigit(argv[i+1][0])) {
            int option = std::stoi(argv[++i]);
            if (option != 0 && option != 1) {
              std::cerr << "La opción de frontera abierta debe ser 0 o 1" << std::endl;
              exit(EXIT_FAILURE);
            }
          }
        } else {
          std::cerr << "Tipo de frontera no encontrado. Use '-border <type>'" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
  // Si argv[i] es -border
  } else if (arg == "-border") {
      if (i + 1 < argc) {
        std::string borderArg = argv[++i];
        if (borderArg == "open") {
          bordertype = OPEN;
          if (i + 1 < argc && isdigit(argv[i+1][0])) {
            int option = std::stoi(argv[++i]);
            if (option != 0 && option != 1) {
              std::cerr << "La opción de frontera abierta debe ser 0 o 1" << std::endl;
              exit(EXIT_FAILURE);
            }
          } else {
            std::cerr << "Opción de frontera abierta no encontrada. Use '-border open <option>'" << std::endl;
            exit(EXIT_FAILURE);
          }
        } else if (borderArg == "periodic") {
          bordertype = PERIODIC;
        } else if (borderArg == "reflective") {
          bordertype = REFLECTIVE;
        } else if (borderArg == "noborder") {
          bordertype = NOFRONTER;
        } else {
          std::cerr << "Tipo de frontera no reconocido. Use '-border <type>'" << std::endl;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "Tipo de frontera no encontrado. Use '-border <type>'" << std::endl;
        exit(EXIT_FAILURE);
      }
    // Si existe un fichero de configuración inicial
    } else if (arg == "-init") {
      if (i + 1 < argc) {
        file_name = argv[++i];
      } else {
        std::cerr << "Archivo de configuración inicial no encontrado. Use '-init <filename>'" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else {
      std::cerr << "Unrecognized argument: " << arg << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

/**
 * @brief Función para guardar el tablero en un archivo
 * Lo que hace es guardar el tablero en un archivo utilizando el operador de inserción
 * @param lattice reticulo a guardar en el archivo
 * @param iteration número de iteración
 * @param filename nombre del archivo nombre del archivo de salida
 */
void SaveToFile(const Lattice& lattice, std::ofstream& output_file) {
  // Comprobamos si el archivo se ha abierto correctamente y guardamos el tablero en el archivo
  if (output_file.is_open()) {
    output_file << lattice; 
  } else {
    std::cerr << "Unable to open file for saving." << "\n";
  }
}

/**
 * @brief Función que evoluciona el autómata celular
 * Se encarga de evolucionar el autómata celular.
 * La simulación se puede detener en cualquier momento pulsando un carácter elegido como fin de ejecución.
 * En este caso, se detiene la simulación si el usuario pulsa la tecla 'x'.
 * @param lattice reticulo a evolucionar 
 */
void CellEvolution(Lattice& lattice, const std::string& filename = "") {
  std::string lattice_aux = "";
  // Si no se especifica un nombre de archivo, se guarda en output.txt
  std::string file_name = filename.empty() ? "output.txt" : filename;
  std::ofstream output_file(file_name, std::ios::out);
  unsigned iteration = 0;
  char user_input;
  // Variable para controlar la visualización del estado del tablero
  bool show_board = true;
  std::cout << std::endl;
  std::cout << " OPTIONS:" << std::endl;
  std::cout << "Press 'x' to quit" << std::endl;
  std::cout << "Press 'n' for next generation" << std::endl; 
  std::cout << "Press 'L' for the next five generations" <<std::endl;
  std::cout << "Press 'c' to show population " << std::endl;
  std::cout << "Press's' to save, or 'Enter' to continue:" << std::endl;
  std::cout << std::endl;
  do {
    // Si el usuario pulsa 's' se guarda el tablero en un archivo
    if (show_board && user_input != 's') {
      std::cout << lattice << "Iteration: " << iteration << std::endl;
      lattice.SaveToString(lattice_aux);
      lattice_aux += "Iteration: " + std::to_string(iteration++) + '\n';
    } else {
      std::cout << "Population: " << lattice.Population() << std::endl;
    }
    // Se lee el carácter que introduce el usuario
    user_input = std::cin.get();
    // Se limpia el buffer del teclado
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Dependiendo de la opción que elija el usuario se ejecuta una acción
    switch (user_input) {
      case 'x':
        std::cout << "Ending simulation." << std::endl;
        break;
      case 'n':
        lattice.NextGeneration();
        break;
      case 'L':
        for (int i = 0; i < 5; ++i) {
          lattice.NextGeneration();
          std::cout << lattice << "Iteration: " << iteration++ << std::endl;
        }
        break;
      case 'c':
        lattice.Population();
        std::cout << "Population: " << lattice.Population() << std::endl;
        break;
      case 's':
        output_file << lattice_aux;
        std::cout << "Board saved to file: " << file_name << "\n";
        break;
      default:
        break;
    }
    // Mientras que el usuario no pulse la tecla 'x', se sigue evolucionando
  } while (user_input != 'x');
  output_file.close();
}

/**
 * @brief Programa principal main
 * Aquí se recibe por línea de comandos el tamaño del retículo, el tipo de frontera y el archivo de configuración inicial
 * A partir de estos datos se crea el retículo y se evoluciona el autómata celular.
 * La simulación se puede detener en cualquier momento pulsando un carácter elegido como fin de ejecución.
 * @param argc numero de argumentos
 * @param argv nombre de los argumentos
 * @return int retorna 0 si se ejecuta correctamente
 */
int main(int argc, char* argv[]) {
  // Utilización del programa
  Usage(argc, argv);
  int row_num, column_num;
  BorderType borderType;
  std::string borderType_aux{argv[4]};
  std::string filename;
  // Asignamos el tipo de frontera
  if (borderType_aux == "open") {
    borderType = OPEN;
  } else if (borderType_aux == "periodic") {
    borderType = PERIODIC;
  } else if (borderType_aux == "reflective") {
    borderType = REFLECTIVE;
  } else if (borderType_aux == "noborder") {
    borderType = NOFRONTER;
  }
  // Comprobamos los argumentos
  checkArgs(argc, argv, row_num, column_num, borderType, filename);
  // Si se pasa la opcion -size se llama al constructor con size sin archivo de configuración inicial
  if (filename.empty()) {
    std::cout << std::endl;
    std::cout << "Arguments parsed successfully:" << std::endl;
    std::cout << "Row number: " << row_num << std::endl;
    std::cout << "Column number: " << column_num << std::endl;
    std::cout << "Border type: " << borderType << std::endl;
    std::cout << std::endl;
    std::cout << std::atoi(argv[2]) << " " << std::atoi(argv[3]) << std::endl;
    Lattice lattice(borderType, argv);
    CellEvolution(lattice);
  } else {
    // Se llama al segundo constructor que lee filas y columnas del archivo de configuración inicial
    Lattice lattice( borderType, filename);
    CellEvolution(lattice);
  }
  return 0;
}