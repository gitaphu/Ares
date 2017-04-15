// VirtualMethodTable
#pragma once

/*
Description:
A virtual method table is a mechanism used in a programming language
to support dynamic dispatch (or run-time method binding).
--
Whenever a class defines a virtual function (or method),
most compilers add a hidden member variable to the class which points to a
so called virtual method table (VMT or Vtable).
This VMT is basically an array of pointers to (virtual) functions.
At runtime these pointers will be set to point to the right function,
because at compile time,
it is not yet known if the base function is to be called or a derived one
implemented by a class that inherits from the base class.
--
https://en.wikipedia.org/wiki/Virtual_method_table
*/
class CVMT {
private:
  std::uintptr_t** m_ppiBaseClass = nullptr; // Base Class, unsigned interger capable of storing this as a pointer.
  std::unique_ptr<std::uintptr_t[]> m_piCurrentVFT = nullptr;
  std::uintptr_t* m_piOriginalVFT = nullptr;
  std::size_t m_strTotalFunctions = 0; // Represent the total amount of functions.
public:

  CVMT(void) = default; // Default constructor.

  CVMT(void* pBaseClass) {

    this->m_ppiBaseClass = static_cast<std::uintptr_t**>(pBaseClass);

    while (static_cast<std::uintptr_t*>(*this->m_ppiBaseClass)[this->m_strTotalFunctions])
      ++this->m_strTotalFunctions;

    const std::size_t m_strTableSize = this->m_strTotalFunctions * sizeof(std::uintptr_t);

    this->m_piOriginalVFT = *this->m_ppiBaseClass;
    this->m_piCurrentVFT = std::make_unique<std::uintptr_t[]>(this->m_strTotalFunctions);

    std::memcpy(this->m_piCurrentVFT.get(), this->m_piOriginalVFT, m_strTableSize);

    *this->m_ppiBaseClass = this->m_piCurrentVFT.get();

  };

  ~CVMT() { // Default deconstructor.
    *this->m_ppiBaseClass = this->m_piOriginalVFT;
  };

  template <typename Fn = void*> inline const Fn GetOriginalFunction(std::size_t strFunctionIndex) { // Grab the original function using its index from the baseclass.
    return reinterpret_cast<Fn>(this->m_piOriginalVFT[strFunctionIndex]);
  }

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

};
