// VirtualMethodTable
#include "../../Ares.h"

inline bool CVMT::HookFunction(void* pNewFunction, const std::size_t strFunctionIndex) {

  if (strFunctionIndex > this->m_strTotalFunctions) // Make sure you're not calling a function that doesn't exist. :P
    return false;

  this->m_piCurrentVFT[strFunctionIndex] = reinterpret_cast<std::uintptr_t>(pNewFunction); // Take the old pointer to the VFUNC and replace it with our own.

  return true;

}

inline bool CVMT::UnhookFunction(const std::size_t strFunctionIndex) {

  if (strFunctionIndex > this->m_strTotalFunctions) // Make sure you're not calling a function that doesn't exist.
    return false;

  this->m_piCurrentVFT[strFunctionIndex] = this->m_piOriginalVFT[strFunctionIndex];

  return true;

}

inline std::size_t CVMT::GetTotalFunctions() {
  return this->m_strTotalFunctions;
}
