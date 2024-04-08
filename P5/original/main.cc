/**
 * @file main.cc
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-03-25
 * @brief Programa principal donde se hace uso de las funciones auxiliares.
 * Se encarga de ordenar una secuencia de elementos utilizando diferentes métodos de ordenación.
 * Se hace uso de las funciones auxiliares para el manejo de la línea de comandos.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "FuncionesAuxiliares.h"
#include "Sequence.h"
#include "MetodosOrdenacion.h"
#include "Nif.h"
#include "Algoritmos.h"

// macros de colores
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

/**
 * @brief Función principal del programa.
 * Se encarga de comprobar que se han pasado los argumentos necesarios y de parsearlos.
 * Códigos para cada funcion de ordenación:
 * 0. Inserción
 * 1. Selección
 * 2. Burbuja
 * 3. Shake
 * 4. Heap
 * 5. QuickSort
 * 6. MergeSort
 * 7. ShellSort
 * 8. Timsort
 * 9. RadixSort
 * @param argc Número de argumentos pasados por línea de comandos.
 * @param argv nombre del programa y argumentos pasados por línea de comandos.
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
  // Mostramos los argumentos pasados por línea de comandos
  std::string border = "\033[1;31m+----------------------------------------+\033[0m"; // Red
  std::cout << border << std::endl;
  std::cout << "\033[1;31m|\033[0m\033[1;32mArgumentos pasados por línea de comandos\033[0m\033[1;31m|\033[0m" << std::endl; // Green text, Red bars
  std::cout << border << std::endl;
  std::cout << "\033[1;31m|\033[0m\033[1;32m Tamaño de la secuencia: \033[0m" << std::setw(14) << std::right << options.sequenceSize << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
  std::cout << "\033[1;31m|\033[0m\033[1;32m Tipo de ordenación:     \033[0m" << std::setw(14) << std::right << options.ordenationType << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
  std::cout << "\033[1;31m|\033[0m\033[1;32m Introducción de datos:  \033[0m" << std::setw(14) << std::right << options.introducingData << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
  std::cout << "\033[1;31m|\033[0m\033[1;32m Mostrar traza:          \033[0m" << std::setw(14) << std::right << options.trace << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
  std::cout << "\033[1;31m|\033[0m\033[1;32m Nombre del fichero:     \033[0m" << std::setw(14) << std::right << options.fileName << "\033[1;31m |\033[0m" << std::endl; // Green text, Red bars
  std::cout << border << std::endl;
      
  // dependiendo si es manual, random o fichero se crea la secuencia
  std::fstream file;
  if (options.introducingData == "file") {
    file.open(options.fileName);
    if (!file) {
      std::cerr << "Error: no se pudo abrir el archivo" << std::endl;
      return EXIT_FAILURE;
    }
  }
  // se crea la secuencia a ordenar
  StaticSequence<Nif>* sequencia_a_ordenar;
  if (options.introducingData == "manual") {
    std::cout << RED << "\n========================================\n";
    std::cout << "  Se introducen los datos manualmente";
    std::cout << "\n========================================\n\n" << RESET;
    sequencia_a_ordenar = new StaticSequence<Nif>(options.sequenceSize, std::string("manual"));
  } else if (options.introducingData == "random") {
    std::cout << RED << "\n========================================\n";
    std::cout << "  Se generan los datos aleatoriamente";
    std::cout << "\n========================================\n\n" << RESET;
    sequencia_a_ordenar = new StaticSequence<Nif>(options.sequenceSize, std::string("random"));
  } else if (options.introducingData == "file") {
    std::cout << RED << "\n========================================\n";
    std::cout << "  Se leen los datos del fichero";
    std::cout << "\n========================================\n\n" << RESET;
    sequencia_a_ordenar = new StaticSequence<Nif>(options.sequenceSize, file);
  } else {
    std::cerr << "Error: introducción de datos no válida" << std::endl;
    return EXIT_FAILURE;
  }

  // dependiendo del tipo de ordenación se llama a la función correspondiente 
  MetodosOrdenacion<Nif>* metodo_ordenacion;
  switch (std::stoi(options.ordenationType)) {
    case 0:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por inserción";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new InsertionSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 1: 
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por selección";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new SelectionSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 2:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por burbuja";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new BubbleSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 3:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por shake";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new ShakerSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 4:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por heapsort";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new HeapSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 5:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por quicksort";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new QuickSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 6:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por mergesort";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new MergeSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 7:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por shellsort";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new ShellSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 8:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por timsort";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new TimSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    case 9:
      std::cout << GREEN << "\n========================================================\n";
      std::cout << "Se ha seleccionado el método de ordenación por radixsort";
      std::cout << "\n========================================================\n\n" << RESET;
      metodo_ordenacion = new RadixSort<Nif>(options.sequenceSize, sequencia_a_ordenar, options.trace);
      metodo_ordenacion->Sort();
      break;
    default:
      std::cerr << "Error: método de ordenación no válido" << std::endl;
      return EXIT_FAILURE;
  }
  // liberamos la memoria
  delete sequencia_a_ordenar;
  delete metodo_ordenacion;
  return 0;
}