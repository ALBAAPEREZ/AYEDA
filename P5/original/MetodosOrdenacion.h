/**
 * @file MetodosOrdenacion.h
 * @author ALBA PÉREZ alu0101513768@ull.edu.es
 * @version 0.1
 * @date 2024-03-25
 * @brief Aqui se implementa una libreria de metodos de ordenacion
 * Encontramos todos los metodos de ordenacion que se van a implementar
 * en el programa principal.
 * 1. Cuadraticos --> Insercion, seleccion y de intercambio(burbuja y shaker)
 * 2. Logaritmicos --> QuickSort, MergeSort y HeapSort
 * 3. Otros --> ShellSort, TimSort y RadixSort
 */

#ifndef METODOSORDENACION_H
#define METODOSORDENACION_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#include "Algoritmos.h"
#include "Sequence.h"
#include "Nif.h"

/**
 * /////////////////////// BASE ///////////////////////
 * @brief Clase abstracta que define los metodos de ordenacion
 * Contiene el metodo virtual puro Sort que se va a implementar en las clases hijas
 * de los metodos de ordenacion.
 * Como atributos contiene el tamaño de la secuencia, la secuencia y un booleano que
 * sirve para mostrar la traza completa o no.
 * @tparam Key clave que se va a ordenar
 */
template <class Key>
class MetodosOrdenacion {
 public:
  MetodosOrdenacion(unsigned size, StaticSequence<Key>* secuencia, bool traza) 
  : secuencia_(secuencia) {
    setSize(size);
    setTraza(traza);
  }
  // metodo nulo que se va a implementar en las clases hijas
  virtual void Sort() = 0;
  // Getters
 protected:
  virtual bool getTraza() { return traza_; }
  virtual unsigned getSize() { return size_; }
  virtual StaticSequence<Key>* getSecuencia() { return secuencia_; }
  // Setters
  virtual void setTraza(bool traza) { traza_ = traza; }
  virtual void setSize(unsigned size) { size_ = size; } 
  virtual void setSecuencia(StaticSequence<Key>* secuencia) { secuencia_ = secuencia; }

 private:
  unsigned size_;
  StaticSequence<Key>* secuencia_;
  bool traza_; // atributo que sirve para mostrar la traza completa o no
};

///////////////////////////////////////////////////////////////////
//////////////////////////// INSERCION ////////////////////////////
/**
 * @brief Clase insertionsort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de insercion.
 * El metodo de inserccion consiste en recorrer la secuencia de izquierda a derecha
 * se compara el elemento actual con los elementos anteriores y se van desplazando
 * a la derecha los elementos mayores que el actual. Su complejidad es O(n^2).
*/
template <class Key>
class InsertionSort : public MetodosOrdenacion<Key> {
 public:
  InsertionSort(unsigned size, StaticSequence<Key>* secuencia, bool traza);
  void Sort();
};

/**
 * @brief Construct a new Insertion Sort< Key>:: Insertion Sort object
 * Constructor de la clase InsertionSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
InsertionSort<Key>::InsertionSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  InsertionSort<Key>::setSize(size);
  InsertionSort<Key>::setSecuencia(secuencia);
  InsertionSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase InsertionSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de insercion
 * Se llama a la funcion Insercion que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void InsertionSort<Key>::Sort() {
  InsertionSortFunction<Key>(InsertionSort<Key>::getSecuencia(), InsertionSort<Key>::getTraza());
}


///////////////////////////////////////////////////////////////////
//////////////////////////// SELECCION ////////////////////////////
/**
 * @brief Clase SelectionSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de seleccion.
 * El metodo de sekeccion consiste en buscar en la secuencia el elemento mas pequeño e
 * intercambiarlo con el primer elemento. Despues se busca el segundo elemento mas pequeño
 * y se intercambia con el segundo elemento de la secuencia. Asi sucesivamente. Su complejidad
 * es O(n^2).
*/
template <class Key>
class SelectionSort : public MetodosOrdenacion<Key> {
 public:
  SelectionSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Selection Sort< Key>:: Selection Sort object
 * Constructor de la clase SelectionSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
SelectionSort<Key>::SelectionSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  SelectionSort<Key>::setSize(size);
  SelectionSort<Key>::setSecuencia(secuencia);
  SelectionSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase SelectionSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de seleccion
 * Se llama a la funcion Seleccion que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void SelectionSort<Key>::Sort() {
  SelectionSortFunction<Key>(*SelectionSort<Key>::getSecuencia(), SelectionSort<Key>::getSize(), SelectionSort<Key>::getTraza());
}


///////////////////////////////////////////////////////////////////
//////////////////////////// INTERCAMBIO //////////////////////////
//////////////////////////// BUBBLE SORT //////////////////////////
/**
 * @brief Clase BubbleSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de intercambio (burbuja).
 * El metodo de burbuja consiste en recorrer la secuencia de izquierda a derecha
 * comparando los elementos adyacentes y si estan desordenados se intercambian.
 * Su complejidad es O(n^2).
*/
template <class Key>
class BubbleSort : public MetodosOrdenacion<Key> {
 public:
  BubbleSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Bubble Sort< Key>:: Bubble Sort object
 * Constructor de la clase BubbleSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
BubbleSort<Key>::BubbleSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  BubbleSort<Key>::setSize(size);
  BubbleSort<Key>::setSecuencia(secuencia);
  BubbleSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase BubbleSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de burbuja
 * Se llama a la funcion Burbuja que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void BubbleSort<Key>::Sort() {
  BubbleSortFunction<Key>(*BubbleSort<Key>::getSecuencia(), BubbleSort<Key>::getSize(), BubbleSort<Key>::getTraza());
}


///////////////////////////////////////////////////////////////////
//////////////////////////// INTERCAMBIO //////////////////////////
//////////////////////////// SHAKER SORT //////////////////////////
/**
 * @brief Clase ShakerSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de intercambio (shaker).
 * El metodo de shaker es una mejora del metodo de burbuja. Consiste en recorrer la secuencia
 * de izquierda a derecha y de derecha a izquierda alternativamente. Su complejidad es O(n^2).
*/
template <class Key>
class ShakerSort : public MetodosOrdenacion<Key> {
 public:
  ShakerSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Shaker Sort< Key>:: Shaker Sort object
 * Constructor de la clase ShakerSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
ShakerSort<Key>::ShakerSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  ShakerSort<Key>::setSize(size);
  ShakerSort<Key>::setSecuencia(secuencia);
  ShakerSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase ShakerSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de shaker
 * Se llama a la funcion Shaker que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void ShakerSort<Key>::Sort() {
  ShakeSortFunction<Key>(*ShakerSort<Key>::getSecuencia(), ShakerSort<Key>::getSize(), ShakerSort<Key>::getTraza());
}


///////////////////////////////////////////////////////////////////
//////////////////////////// HEAPSORT ////////////////////////////
/**
 * @brief Clase HeapSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de heapsort.
 * El metodo de heapsort consiste en crear un monticulo a partir de la secuencia
 * y despues ir extrayendo el elemento mayor y colocandolo al final de la secuencia.
 * Su complejidad es O(n log n).
*/
template <class Key>
class HeapSort : public MetodosOrdenacion<Key> {
 public:
  HeapSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Heap Sort< Key>:: Heap Sort object
 * Constructor de la clase HeapSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
HeapSort<Key>::HeapSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  HeapSort<Key>::setSize(size);
  HeapSort<Key>::setSecuencia(secuencia);
  HeapSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase HeapSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de heapsort
 * Se llama a la funcion Heapsort que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void HeapSort<Key>::Sort() {
  heapSortFunction<Key>(*this->getSecuencia(), (this->getSecuencia()->getSize() - 1), this->getTraza());
}

///////////////////////////////////////////////////////////////////
//////////////////////////// QUICKSORT ////////////////////////////
/**
 * @brief Clase QuickSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de quicksort.
 * El metodo de quicksort consiste en elegir un pivote y coloc
 * ar los elementos menores a la izquierda y los mayores a la derecha.
 * Su complejidad es O(n log n).
 * Se ha implementado el quicksort con el pivote en la primera posicion.
 * Se ha implementado el quicksort con el pivote en la ultima posicion.
 * Se ha implementado el quicksort con el pivote en la posicion central.
 */
template <class Key>
class QuickSort : public MetodosOrdenacion<Key> {
 public:
  QuickSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Quick Sort< Key>:: Quick Sort object
 * Constructor de la clase QuickSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
QuickSort<Key>::QuickSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  QuickSort<Key>::setSize(size);
  QuickSort<Key>::setSecuencia(secuencia);
  QuickSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase QuickSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de quicksort
 * Se llama a la funcion Quicksort que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void QuickSort<Key>::Sort() {
  quickSort<Key>(*this->getSecuencia(), this->getTraza());
}


///////////////////////////////////////////////////////////////////
//////////////////////////// MERGESORT ////////////////////////////
/**
 * @brief Clase MergeSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de mergesort.
 * El metodo de mergesort consiste en dividir la secuencia en dos mitades y ordenarlas
 * de forma recursiva. Despues se mezclan las dos mitades ordenadas. Su complejidad es O(n log n).
*/
template <class Key>
class MergeSort : public MetodosOrdenacion<Key> {
 public:
  MergeSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Merge Sort< Key>:: Merge Sort object
 * Constructor de la clase MergeSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
MergeSort<Key>::MergeSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  MergeSort<Key>::setSize(size);
  MergeSort<Key>::setSecuencia(secuencia);
  MergeSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase MergeSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de mergesort
 * Se llama a la funcion Mergesort que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void MergeSort<Key>::Sort() {
  mergeSort<Key>(*this->getSecuencia(), 0, (this->getSecuencia()->getSize() - 1), this->getTraza());
}


///////////////////////////////////////////////////////////////////
//////////////////////////// SHELLSORT ////////////////////////////
/**
 * @brief Clase ShellSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de shellsort.
 * El metodo de shellsort es una mejora del metodo de insercion. Consiste en comparar
 * elementos separados por una distancia d y despues ir reduciendo esa distancia.
 * Su complejidad es O(n^2).
*/
template <class Key>
class ShellSort : public MetodosOrdenacion<Key> {
 public:
  ShellSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Shell Sort< Key>:: Shell Sort object
 * Constructor de la clase ShellSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
ShellSort<Key>::ShellSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  ShellSort<Key>::setSize(size);
  ShellSort<Key>::setSecuencia(secuencia);
  ShellSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase ShellSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de shellsort
 * Se llama a la funcion Shellsort que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void ShellSort<Key>::Sort() {
  double alfa;
  do { // Nos aseguramos de que el usuario introduce un alfa correcto
    std::cout << "Introduce el valor de alfa: ";
    while(!(std::cin >> alfa)) {
      std::cin.clear(); // limpia el estado de error
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descarta la entrada incorrecta
      std::cout << "Entrada inválida. Por favor, introduce un número: ";
    }
  } while (alfa < 0 || 1 < alfa);
  shellSort<Key>(*ShellSort<Key>::getSecuencia(), alfa, ShellSort<Key>::getTraza());
}


///////////////////////////////////////////////////////////////////
//////////////////////////// TIMSORT ////////////////////////////
/**
 * @brief Clase TimSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de timsort.
 * El metodo de timsort es una mejora del metodo de mergesort. Consiste en dividir
 * la secuencia en bloques y ordenarlos con el metodo de insercion. Despues se mezclan
 * los bloques ordenados. Su complejidad es O(n log n).
*/
template <class Key>
class TimSort : public MetodosOrdenacion<Key> {
 public:
  TimSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Tim Sort< Key>:: Tim Sort object
 * Constructor de la clase TimSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
TimSort<Key>::TimSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  TimSort<Key>::setSize(size);
  TimSort<Key>::setSecuencia(secuencia);
  TimSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase TimSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de timsort
 * Se llama a la funcion Timsort que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void TimSort<Key>::Sort() {
  timSort<Key>(*TimSort<Key>::getSecuencia(), TimSort<Key>::getTraza());
}


///////////////////////////////////////////////////////////////////
//////////////////////////// RADIXSORT ////////////////////////////
/**
 * @brief Clase RadixSort que hereda de MetodosOrdenacion
 * Contiene el metodo Sort que se va a implementar para ordenar la secuencia
 * mediante el metodo de radixsort.
 * El metodo de radixsort consiste en ordenar los elementos de la secuencia
 * por digitos. Su complejidad es O(n).
*/
template <class Key>
class RadixSort : public MetodosOrdenacion<Key> {
 public:
  RadixSort(unsigned size, StaticSequence<Key>* secuencia, bool traza = false);
  void Sort();
};

/**
 * @brief Construct a new Radix Sort< Key>:: Radix Sort object
 * Constructor de la clase RadixSort que inicializa los atributos de la clase
 * La secuencia se pasa por parametro y el tamaño se calcula con el metodo size()
 * @tparam Key Clave que se va a ordenar
 * @param size tamaño de la secuencia
 * @param secuencia secuencia que se va a ordenar
 * @param traza traza que se va a mostrar o no
 */
template <class Key>
RadixSort<Key>::RadixSort(unsigned size, StaticSequence<Key>* secuencia, bool traza) : MetodosOrdenacion<Key>(size, secuencia, traza) {
  RadixSort<Key>::setSize(size);
  RadixSort<Key>::setSecuencia(secuencia);
  RadixSort<Key>::setTraza(traza);
}

/**
 * @brief Metodo Sort de la clase RadixSort
 * Este metodo se encarga de ordenar la secuencia mediante el metodo de radixsort
 * Se llama a la funcion Radixsort que se encuentra en el archivo Algoritmos.h
 * @tparam Key Clave que se va a ordenar
 */
template <class Key>
void RadixSort<Key>::Sort() {
  radixSort<Key>(*RadixSort<Key>::getSecuencia(), RadixSort<Key>::getTraza());
}

#endif // METODOSORDENACION_H

