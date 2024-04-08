/**
 * @file Cell.cc
 * @author ALBA PEREZ  
 * @version 0.1
 * @date 2024-03-03
 * @brief 
 * 
 */

#include "Cell.h"

/**
 * @brief Sobrecaarga del operador de salida para mostrar la celda
 * Se encarga de mostrar la celda
 * @tparam PositionType Posición de la celda
 * @param os  Stream de salida
 * @param cell  Celda a mostrar
 * @return std::ostream& 
 */
template <typename PositionType>
std::ostream& operator<<(std::ostream& os, const Cell<PositionType>& cell) {
  return cell.Display(os);
}