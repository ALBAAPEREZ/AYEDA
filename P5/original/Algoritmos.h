/**
 * @file Algoritmos.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-03-25
 * @copyright Copyright (c) 2024
 * @brief Fichero que contiene todos los algorithmos de ordenación.
 * Se definen los algoritmos de ordenación que se van a usar en el main:
 * 1. Inserción --> recorre la lista de elementos de izquierda a derecha y va insertando 
 *                  cada uno de ellos en su posición correcta.
 * 2. Selección --> busca el menor elemento de la lista y lo intercambia con el primero. 
 *                  Luego busca el segundo menor y lo intercambia con el segundo, y así sucesivamente.
 * 3. Burbuja --> recorre la lista de elementos de izquierda a derecha y va comparando 
 *                cada elemento con el siguiente, intercambiándolos de posición si están en el orden equivocado.
 * 4. ShakeSort --> es una variante del algoritmo de la burbuja que recorre la lista en ambas direcciones.
 * 5. HeapSort --> es un algoritmo de ordenación basado en la estructura de datos del montículo.
 * 6. QuickSort --> es un algoritmo de ordenación que divide la lista de elementos en dos sublistas,
 *                  y luego ordena las sublistas de forma recursiva.
 * 7. MergeSort --> es un algoritmo de ordenación que divide la lista de elementos en sublistas más 
 *                  pequeñas, las ordena y luego las fusiona para obtener una lista ordenada.
 * 8. ShellSort --> es una variante del algoritmo de inserción que divide la lista en sublistas más 
 *                  pequeñas
 * 9. Timsort --> es un algoritmo de ordenación híbrido que combina el algoritmo de ordenación por
 *                inserción y el algoritmo de ordenación por mezcla.          
 * 10. RadixSort --> es un algoritmo de ordenación que ordena los elementos de la lista basándose en
 *                  los dígitos de los números.
 */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "MetodosOrdenacion.h"
#include "Sequence.h"
#include "Nif.h"

///////////////////////// INSERTION ///////////////////////
/**
 * @brief Función que ordena una secuencia de elementos utilizando el algoritmo de inserción.
 * El algoritmo de inserción recorre la lista de elementos de izquierda a derecha y va insertando
 * cada uno de ellos en su posición correcta.  
 * @tparam Key clave que se va a dispersar
 * @param seq secuencia de elementos que se va a ordenar
 * @param trace true si se quiere mostrar la traza, false en caso contrario
 */
template<class Key>
void InsertionSortFunction(StaticSequence<Key>* seq, bool trace) {
  int n = seq->getSize();
  if (!trace) {
    std::cout << "Secuencia original: " << std::endl;
    for (int i = 0; i < n; ++i) {
      std::cout << (*seq)[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
  }
  if (trace) {
   // Imprimir la secuencia original
    std::cout << "Secuencia original: " << std::endl;
    for (int i = 0; i < n; ++i) {
      std::cout << (*seq)[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
    std::cout << std::endl;
  }
  for (int i = 1; i < n; ++i) {
    Key key = (*seq)[i];
    int j = i - 1;
    while (j >= 0 && (*seq)[j] > key) {
      (*seq)[j + 1] = (*seq)[j];
      --j;
    }
    (*seq)[j + 1] = key;    
    if (trace) {
      std::cout << ">>> Iteración " << i << ": ";
      for (int k = 0; k < n; ++k) {
        std::cout << (*seq)[k] << " ";
      }
      std::cout << std::endl;
    }
  }
  if (trace) {
    std::cout << std::endl << "-------------------------------" << std::endl;
    // Imprimir el vector ordenado
    std::cout << "Vector ordenado: " << std::endl;
    for (int i = 0; i < n; ++i) {
      std::cout << (*seq)[i] << " ";
    }
    std::cout << std::endl;
  }
  if (!trace) {
    std::cout << "Vector ordenado:" << std::endl;
    for (int i = 0; i < n; ++i) {
      std::cout << (*seq)[i] << " ";
    }
    std::cout << std::endl;
  }
}

///////////////////////// SELECTION ///////////////////////
/**
 * @brief Función que ordena una secuencia de elementos utilizando el algoritmo de selección.
 * El algoritmo de selección busca el menor elemento de la lista y lo intercambia con el primero.
 * Luego busca el segundo menor y lo intercambia con el segundo, y así sucesivamente.
 * @tparam Key clave que se va a dispersar
 * @param seq secuencia de elementos que se va a ordenar
 * @param trace true si se quiere mostrar la traza, false en caso contrario
*/template <class Key>
void SelectionSortFunction(StaticSequence<Key>& seq, int size, bool trace) {
  // si no se quiere mostrar la traza, se imprime la secuencia original
  if (!trace) {
    std::cout << "Secuencia original: " << std::endl;
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
  }
  if (trace) {
    // Imprimir la secuencia original
    std::cout << "Secuencia original: ";
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
    std::cout << std::endl;
  }
  for (int i = 0; i < size - 1; ++i) {
    int min_index = i;
    for (int j = i + 1; j < size; ++j) {
      if (seq[j] < seq[min_index]) {
        min_index = j;
      }
    }
    if (min_index != i) {
      std::swap(seq[min_index], seq[i]);
    }
    if (trace) {
      std::cout << ">>> Iteración " << i + 1 << ": ";
      for (int k = 0; k < size; ++k) {
        std::cout << seq[k] << " ";
      }
      std::cout << std::endl;
    }
  }
  if (trace) {
    std::cout << std::endl << "-------------------------------" << std::endl;
    // Imprimir el vector ordenado
    std::cout << "Vector ordenado: ";
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
  }
  if (!trace) {
    std::cout << "Vector ordenado:" << std::endl;
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
  }
}

///////////////////////// BUBBLESORT ///////////////////////
/**
 * @brief Función que ordena una secuencia de elementos utilizando el algoritmo de burbuja.
 * El algoritmo de burbuja recorre la lista de elementos de izquierda a derecha y va comparando
 * cada elemento con el siguiente, intercambiándolos de posición si están en el orden equivocado.
 * @tparam Key clave que se va a dispersar
 * @param seq secuencia de elementos que se va a ordenar
 * @param trace true si se quiere mostrar la traza, false en caso contrario
*/
template <class Key>
void BubbleSortFunction(StaticSequence<Key>& seq, int size, bool trace) {
  if (!trace) {
    std::cout << "Secuencia original: " << std::endl;
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
  }
  if (trace) {
    // Imprimir la secuencia original
    std::cout << "Secuencia original: ";
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
    std::cout << std::endl;
  }
  for (int i = 0; i < size - 1; ++i) {
    bool swapped = false;
    for (int j = 0; j < size - i - 1; ++j) {
      if (seq[j] > seq[j + 1]) {
        std::swap(seq[j], seq[j + 1]);
        swapped = true;
      }
    }
    if (!swapped) {
      // Si no hay intercambios en esta pasada, el arreglo ya está ordenado
      break;
    }
    if (trace) {
      std::cout << ">>> Iteración " << i + 1 << ": ";
      for (int k = 0; k < size; ++k) {
        std::cout << seq[k] << " ";
      }
      std::cout << std::endl;
    }
  }
  if (trace) {
    std::cout << std::endl << "-------------------------------" << std::endl;
    // Imprimir el vector ordenado
    std::cout << "Vector ordenado: ";
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
  }
  if (!trace) {
    std::cout << "Vector ordenado:" << std::endl;
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
  }
}

///////////////////////// SHAKESORT ///////////////////////
/**
 * @brief Función que ordena una secuencia de elementos utilizando el algoritmo de shake sort.
 * El algoritmo de shake sort es una variante del algoritmo de la burbuja que recorre la lista en ambas direcciones.
 * @tparam Key clave que se va a dispersar
 * @param seq secuencia de elementos que se va a ordenar
 * @param trace true si se
 * quiere mostrar la traza, false en caso contrario
 */
template <class Key>
void ShakeSortFunction(StaticSequence<Key>& seq, int size, bool trace) {
  if (!trace) {
    std::cout << "Secuencia original: " << std::endl;
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
  }
  if (trace) {
    // Imprimir la secuencia original
    std::cout << "Secuencia original: ";
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
    std::cout << std::endl;
  }
  int left = 0;
  int right = size - 1;
  int iteracion = 0;
  while (left <= right) {
    bool swapped = false;
    for (int i = left; i < right; ++i) {
      if (seq[i] > seq[i + 1]) {
        std::swap(seq[i], seq[i + 1]);
        swapped = true;
      }
    }
    --right;
    if (swapped) {
      ++iteracion;
      if (trace) {
        std::cout << ">>> Iteración " << iteracion << ": ";
        for (int i = 0; i < size; ++i) {
          std::cout << seq[i] << " ";
        }
        std::cout << std::endl;
      }
    }
    swapped = false;
    for (int i = right; i > left; --i) {
      if (seq[i] < seq[i - 1]) {
        std::swap(seq[i], seq[i - 1]);
        swapped = true;
      }
    }
    ++left;
    if (swapped) {
      ++iteracion;
      if (trace) {
        std::cout << ">>> Iteración " << iteracion << ": ";
        for (int i = 0; i < size; ++i) {
          std::cout << seq[i] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
  if (trace) {
    std::cout << std::endl << "-------------------------------" << std::endl;
    // Imprimir el vector ordenado
    std::cout << "Vector ordenado: ";
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
  }
  if (!trace) {
    std::cout << "Vector ordenado:" << std::endl;
    for (int i = 0; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
  }
}


///////////////////////// HEAPSORT ///////////////////////
/**
 * @brief Funcion que convierte un vector en un heap.
 * Un heap es un árbol binario completo que satisface la propiedad de heap.
 * La propiedad de heap es que cada nodo padre tiene un valor mayor o igual que sus hijos.
 * @tparam Key clave que se va a dispersar
 * @param vector vector que se va a convertir en heap
 * @param n número de elementos del vector
 * @param i indice del nodo raíz
 */
template <class Key>
void ConvertirEnHeap(StaticSequence<Nif>& vector, int n, int& i) {
  int largest = i; // Inicializa largest como la raíz, ya que usamos índices basados en 0
  int left = 2 * i + 1; 
  int right = 2 * i + 2;
  // Si el hijo izquierdo es mayor que la raíz
  if (left < n && vector[left] > vector[largest])
    largest = left;
  // Si el hijo derecho es mayor que el mayor hasta ahora
  if (right < n && vector[right] > vector[largest])
    largest = right;
  // Si largest no es la raíz
  if (largest != i) {
    std::swap(vector[i], vector[largest]);
    // Recursivamente convertir en heap el sub-árbol afectado
    ConvertirEnHeap<Key>(vector, n, largest);
  }
}

/**
 * @brief Funcion que ordena una secuencia de elementos utilizando el algoritmo de heapsort.
 * El algoritmo de heapsort es un algoritmo de ordenación basado en la estructura de datos del montículo.
 * @tparam Key clave que se va a dispersar
 * @param vector vector que se va a ordenar
 * @param traza true si se quiere mostrar la traza, false en caso contrario
 */
template <class Key>
void heapSortFunction(StaticSequence<Key>& vector, int size, bool traza) {
  if (!traza) {
    std::cout << "Secuencia original: " << std::endl;
    for (int i = 0; i < size; i++) {
      std::cout << vector[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
  }
  if (traza) {
    // Imprimir la secuencia original
    std::cout << "Secuencia original: ";
    for (int i = 0; i < size; i++) {
      std::cout << vector[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
    std::cout << std::endl;
  }
  // Construir el heap (reorganizar el arreglo)
  for (int i = size / 2 - 1; i >= 0; i--) {
    ConvertirEnHeap<Key>(vector, size, i);
  }
  int iteracion = 0;
  // Extraer un elemento del heap uno por uno
  for (int i = size - 1; i >= 0; i--) {
    // Mover la raíz actual al final
    std::swap(vector[0], vector[i]);
    // Llamar a ConvertirEnHeap en el heap reducido
    int index = 0;
    ConvertirEnHeap<Key>(vector, i, index);
    iteracion++;
    if ((iteracion == 1 || iteracion == size / 4 || iteracion == size / 2 ||
      iteracion == size / 4 * 3 || iteracion == size - 1) && traza) {
      std::cout << ">>> Iteracion " << iteracion << ": ";
      for (int j = 0; j < size; j++) {
        std::cout << vector[j] << " ";
      }
      std::cout << std::endl;
    }
  }
  if (traza) {
    std::cout << std::endl << "-------------------------------" << std::endl;
    // Imprimir el vector ordenado
    std::cout << "Vector ordenado: ";
    for (int i = 0; i < size; i++) {
      std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
  }
  if (!traza) { // Se han introducido los valores aleatoriamente
    std::cout << "Vector ordenado: " << std::endl;
    for (int j = 0; j < size; j++) {
      std::cout << vector[j] << " ";
    }
    std::cout << std::endl;
  }
}

///////////////////////// QUICKSORT ///////////////////////
// Función auxiliar para intercambiar dos elementos en un vector
/**
 * @brief Funcion que intercambia dos elementos en un vector.
 * La función swap recibe un vector y dos índices i y j. Intercambia los elementos en las posiciones i y j.
 * @tparam Key clave que se va a dispersar
 * @param v vector en el que se van a intercambiar los elementos
 * @param i indice del primer elemento
 * @param j segundo indice del elemento
 */
template <class Key>
void swap(StaticSequence<Nif>& v, int i, int j) {
  Key temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

// Función para encontrar el pivote y dividir el vector en dos subvectores
/**
 * @brief Función que selecciona un pivote y divide el vector en dos subvectores.
 * La función Partition selecciona el último elemento del vector como pivote y recorre el vector
 * desde el primer elemento hasta el penúltimo elemento. Si el elemento actual es menor o igual al pivote,
 * incrementa el índice del elemento más pequeño y cambia el elemento actual con el elemento más pequeño.
 * Finalmente, intercambia el elemento más pequeño con el pivote y devuelve el índice del pivote.
 * @tparam Key clave que se va a dispersar
 * @param v vector que se va a ordenar
 * @param low segundo elemento del vector
 * @param high segundo elemento del vector
 * @return int retorna el índice del pivote
 */
template <class Key>
int partition(StaticSequence<Nif>& v, int low, int high) {
  Key pivot = v[high]; // Seleccionamos el último elemento como pivote
  int i = low - 1; // Índice del elemento más pequeño
  for (int j = low; j < high; j++) {
    // Si el elemento actual es menor o igual al pivote
    if (v[j] <= pivot) {
      i++; // Incrementamos el índice del elemento más pequeño
      swap<Key>(v, i, j); // Intercambiamos v[i] y v[j]
    }
  }
  swap<Key>(v, i + 1, high); // Intercambiamos v[i+1] y v[high] (o el pivote)
  return i + 1; // Devolvemos el índice del pivote
}

/**
 * @brief Funcion auxiliar que implementa el algoritmo de QuickSort.
 * La función QuickSortAux recibe un vector, un índice bajo y un índice alto.
 * Si el índice bajo es menor que el índice alto, selecciona un pivote y divide 
 * el vector en dos subvectores.
 * @tparam Key clave que se va a dispersar
 * @param v secuencia de elementos que se va a ordenar
 * @param low primer elemento del vector
 * @param high segundo elemento del vector
 * @param traza true si se quiere mostrar la traza, false en caso contrario
 */
template <class Key>
void quickSortAux(StaticSequence<Key>& v, int low, int high, bool traza, int& iteration) {
  if (low < high) {
    int pi = partition<Key>(v, low, high);
    quickSortAux<Key>(v, low, pi - 1, traza, iteration); // Ordenar el subarreglo izquierdo
    quickSortAux<Key>(v, pi + 1, high, traza, iteration); // Ordenar el subarreglo derecho
  }
  if (traza && low <= high) {
    std::cout << ">>> Iteración " << iteration << ": ";
    for (int i = low; i <= high; i++) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    iteration++;
  }
}

// Función principal que implementa QuickSort
/**
 * @brief Función que ordena una secuencia de elementos utilizando el algoritmo de QuickSort.
 * El algoritmo de QuickSort divide la lista de elementos en dos sublistas, y luego ordena las
 * sublistas de forma recursiva.
 * @tparam Key Clave que se va a dispersar
 * @param v vector que se va a ordenar
 * @param low primer elemento del vector
 * @param high segundo elemento del vector
 * @param traza true si se quiere mostrar la traza, false en caso contrario
 */
template <class Key>
void quickSort(StaticSequence<Nif>& v, bool traza) {
  int low = 0;
  int high = v.getSize() - 1;
  int iteracion = 0;
  if (!traza) {
    std::cout << "Secuencia original: " << std::endl;
    for (int i = low; i <= high; i++) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
  }
  if (traza) {
    // Imprimir la secuencia original
    std::cout << "Secuencia original: ";
    for (int i = low; i <= high; i++) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
    std::cout << std::endl;
  }
  quickSortAux<Key>(v, low, high, traza, iteracion);
  if (traza) {
    std::cout << std::endl << "-------------------------------" << std::endl;
    // Imprimir el vector ordenado
    std::cout << "Vector ordenado: ";
    for (int i = low; i <= high; i++) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl;
  }
  if (!traza) {
    std::cout << "Vector ordenado: " << std::endl;
    for (int i = low; i <= high; i++) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl;
  }
}


///////////////////////// MERGESORT ///////////////////////
// Función auxiliar para realizar el Merge Sort que mezcla las subsecuencias
/**
 * @brief Función que mezcla dos subsecuencias ordenadas en un vector.
 * La función Mezcla recibe un vector, un índice de inicio, un índice intermedio y un índice final.
 * La función crea un vector auxiliar que almacena los elementos ordenados de las dos subsecuencias.
 * @tparam Key clave que se va a dispersar
 * @param v vector que se va a ordenar
 * @param primero primer elemento del vector
 * @param medio medio del vector
 * @param ultimo ultimo elemento del vector
 */
template <class Key>
void Mezcla(StaticSequence<Nif>& v, int primero, int medio, int ultimo) {
  std::vector<Key> aux(ultimo - primero + 1);
  int i{primero}, k{medio + 1}, z{0};
  // Ordenamos los elementos en el vector aux
  while (i <= medio && k <= ultimo) {
    if (v[i] <= v[k]) {
      aux[z++] = v[i++];
    } else {
      aux[z++] = v[k++];
    }
  }
  // Insertamos los elementos restantes de los subvectores en el vector aux
  while (i <= medio) {
    aux[z++] = v[i++];
  }
  while (k <= ultimo) {
    aux[z++] = v[k++];
  }
  // Copiamos todos los elementos de aux hacia v
  for (int i{0}; i < z; ++i) {
    v[primero + i] = aux[i];
  }
}

// Función principal para realizar el Merge Sort
/**
 * @brief Función que ordena una secuencia de elementos utilizando el algoritmo de MergeSort.
 * El algoritmo de MergeSort divide la lista de elementos en sublistas más pequeñas, las ordena y
 * luego las fusiona para obtener una lista ordenada.
 * @tparam Key Clave que se va a dispersar
 * @param v vector que se va a ordenar
 * @param primero primer elemento del vector
 * @param ultimo ultimo elemento del vector
 * @param traza true si se quiere mostrar la traza, false en caso contrario
 */
template <class Key>
void mergeSort(StaticSequence<Key>& v, int primero, int ultimo, bool traza) {
  static int iteracion = 0; // Variable para contar las iteraciones

  // Mostrar la secuencia inicial en la primera iteración
  if (primero == 0 && ultimo == (v.getSize() - 1) && iteracion == 0) {
    std::cout << "Secuencia inicial: " << std::endl;
    std::cout << "-------------------------------" << std::endl;
    for (int i = primero; i <= ultimo; ++i) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl << std::endl;
  }

  if (traza && primero != ultimo) {
    std::cout << ">>> Iteracion " << iteracion << " (antes): ";
    for (int i = 0; i < v.getSize(); ++i) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl;
  }

  if (primero < ultimo) {
    int central{(primero + ultimo) / 2};
    mergeSort<Key>(v, primero, central, traza);  // Ordenamos la sublista izquierda
    mergeSort<Key>(v, (central + 1), ultimo, traza);  // Ordenamos la sublista derecha
    Mezcla<Key>(v, primero, central, ultimo);  // Mezclar los elementos ordenados
  } 

  if (traza && primero != ultimo) {
    std::cout << ">>> Iteracion " << iteracion << " (despues): ";
    for (int i = 0; i < v.getSize(); ++i) {
      std::cout << v[i] << " ";
    }
    iteracion++;
    std::cout << std::endl << std::endl;
  }
  // Mostrar el vector ordenado en la última iteración
  if (primero == 0 && ultimo == (v.getSize() - 1)) {
    std::cout << "Vector ordenado: " << std::endl;
    std::cout << "-------------------------------" << std::endl;
    for (int i = primero; i <= ultimo; ++i) {
      std::cout << v[i] << " ";
    }
    std::cout << std::endl;
  }
}

///////////////////////// SHELLSORT ///////////////////////
// Función auxiliar para realizar el Shell Sort
template <class Key>
void shellSort(StaticSequence<Nif>& vec, double alfa, bool traza) {
  // Secuencia original
  std::cout << std::endl;
  std::cout << "Secuencia original: " << std::endl;
  for (const auto& elem : vec.getValue()) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  int n = vec.getSize();
  for (int intervalo = n / 2; intervalo > 0; intervalo /= 2) {
    for (int i = intervalo; i < n; i += 1) {
      Key temp = vec[i];
      int j;
      for (j = i; j >= intervalo && vec[j - intervalo] > temp; j -= intervalo) {
        vec[j] = vec[j - intervalo];
        // Mostrar la traza si se solicita
        if (traza) {
          std::cout << "δ = " << intervalo << "\t";
          for (const auto& elem : vec.getValue()) {
            std::cout << elem << " ";
          }
          std::cout << "\n-------------------------------\n";
        }
      }
      vec[j] = temp;
    }
  }
  // Mostrar el vector ordenado
  std::cout << std::endl;
  std::cout << "Vector ordenado: " << std::endl;
  for (const auto& elem : vec.getValue()) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}


///////////////////////// TIMSORT ///////////////////////
// Función auxiliar para realizar el Tim Sort
/**
 * @brief Función que ordena una secuencia de elementos utilizando el algoritmo de TimSort.
 * El algoritmo de TimSort es un algoritmo de ordenación híbrido que combina el algoritmo de ordenación
 * por inserción y el algoritmo de ordenación por mezcla.
 * @tparam Key clave que se va a dispersar
 * @param vec vector que se va a ordenar
 * @param traza true si se quiere mostrar la traza, false en caso contrario
 */
template <class Key>
void timSort(StaticSequence<Nif>& vec, bool traza) {
  int n = vec.getSize();
  const int RUN = 32;
  // Ordenar cada sublista de tamaño RUN
  for (int i = 0; i < n; i += RUN) {
    InsertionSortFunction<Key>(&vec, traza);
  }
  // Mezclar las sublistas ordenadas
  for (int size = RUN; size < n; size = 2 * size) {
    for (int left = 0; left < n; left += 2 * size) {
      int mid = left + size - 1;
      int right = std::min((left + 2 * size - 1), (n - 1));
      Mezcla<Key>(vec, left, mid, right);
    }
    // Mostrar la traza si se solicita
    if (traza) {
      std::cout << "Tamaño de la sublista: " << size << std::endl;
      for (const auto& elem : vec.getValue()) {
        std::cout << elem << " ";
      }
      std::cout << std::endl;
      std::cout << "-------------------------------" << std::endl;
    }
  }
}


///////////////////////// RADIXSORT ///////////////////////
// Función auxiliar para obtener el máximo valor en un vector
/**
 * @brief Función que obtiene el valor máximo en un vector
 * Lo que hace es recorrer el vector y comparar cada elemento con el máximo actual.
 * Si el elemento es mayor que el máximo actual, se actualiza el máximo.
 * @tparam Key clave que se va a dispersar
 * @param vec vector en el que se va a buscar el máximo
 * @return int int que representa el valor máximo en el vector
 */
template <class Key>
int obtenerMaximo(StaticSequence<Nif>& vec) {
  Nif maximo = vec[0];
  for (int i = 1; i < vec.getSize(); i++) {
    if (vec[i] > maximo) {
      maximo = vec[i];
    }
  }
  return maximo;
}

// Función para realizar el RadixSort
/**
 * @brief Función que ordena una secuencia de elementos utilizando el algoritmo de RadixSort.
 * La idea detrás del algoritmo de RadixSort es ordenar los elementos de la lista basándose en 
 * los dígitos de los números. primero se ordenan los elementos basándose en el dígito menos
 * significativo, luego en el siguiente dígito menos significativo y así sucesivamente.
 * @tparam Key clave que se va a dispersar
 * @param vec vector que se va a ordenar
 * @param traza true si se quiere mostrar la traza, false en caso contrario
 */
template <class Key>
void radixSort(StaticSequence<Nif>& vec, bool traza) {
  if (!traza) {
    std::cout << "Secuencia original: " << std::endl;
    for (int i = 0; i < vec.getSize(); i++) {
      std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "-------------------------------" << std::endl;
  }
  if (traza) {
    // Imprimir la secuencia original
    std::cout << "Secuencia original: " << std::endl;
    for (int i = 0; i < vec.getSize(); i++) {
      std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
  // Obtener el valor máximo en el vector
  int maximo = obtenerMaximo<Key>(vec);
  int numero_fase = 1;
  // Iterar a través de cada dígito del número, comenzando desde el menos significativo
  for (int exp = 1; maximo / exp > 0; exp *= 10) {
    // Crear un vector de salida y un arreglo de conteo
    std::vector<Key> salida(vec.getSize());
    int conteo[10] = {0};
    // Calcular el conteo de frecuencia para cada dígito
    for (int i = 0; i < vec.getSize(); i++) {
      conteo[(vec[i] / exp) % 10]++;
    }
    // Calcular las posiciones finales de cada elemento en la salida
    for (int i = 1; i < 10; i++) {
      conteo[i] += conteo[i - 1];
    }
    // Colocar cada elemento en su posición correcta en la salida
    for (int i = vec.getSize() - 1; i >= 0; i--) {
      salida[conteo[(vec[i] / exp) % 10] - 1] = vec[i];
      conteo[(vec[i] / exp) % 10]--;
    }
    // Copiar el vector de salida al vector original
    for (int i = 0; i < vec.getSize(); i++) {
      vec[i] = salida[i];
    }
    // Mostrar la traza si se solicita
    if (traza) {
      std::cout << ">>> Fase " << numero_fase++ << ":" << std::endl;
      for (int i = 0; i < vec.getSize(); i++) {
        std::cout << vec[i] << " ";
      }
      std::cout << std::endl;
      std::cout << "-------------------------------" << std::endl;
    }
  }
  // Mostrar el vector ordenado si no se solicita la traza
  if (!traza) {
    std::cout << "Vector ordenado: " << std::endl;
    for (int i = 0; i < vec.getSize(); i++) {
      std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "-------------------------------" << std::endl;
  }
  if (traza) {
    std::cout << std::endl;
    std::cout << "Vector ordenado: " << std::endl;
    for (int i = 0; i < vec.getSize(); i++) {
      std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
  }
};

#endif // ALGORITMOS_H