#pragma once
#include "Expect/Chains/ExpectLogic.hpp"
#include "ExpectSelect.hpp"

namespace CBUnit
{
  //default ExpectToBeAt has nothing
  template <typename T, typename Logic, typename Enabler = void> class ExpectToBeAt {};

  template <typename T, typename Logic> class ExpectToBeAtBase: public ExpectToBeAt<T, Logic> 
  {
  public:
    ExpectToBeAtBase(const T& actual, const char* filename, uint32_t lineNumber) {}
  };
}

