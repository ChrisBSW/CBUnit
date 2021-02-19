#pragma once
#include "ExpectBase.hpp"
#include "ExpectLogic.hpp"
#include "Expect/Error/TestExpectationFailure.hpp"
#include "TestStructure/TestError.hpp"

namespace CBUnit
{
  namespace
  {
    struct TestExpectationLessThanOrEqualText {static constexpr const char* text = "to be less than or equal to";};
    template <typename T, class Logic> using TestExpectationLessThanOrEqualFailure = TestExpectationFailure<T, Logic, TestExpectationLessThanOrEqualText>; 

    struct TestExpectationAtMostText {static constexpr const char* text = "to be at most";};
    template <typename T, class Logic> using TestExpectationAtMostFailure = TestExpectationFailure<T, Logic, TestExpectationAtMostText>; 
  }

  template <class T, class Logic = ExpectLogic>
  class ExpectLessThanOrEqual: public virtual ExpectBase<T>
  {
  public:
    void lessThanOrEqual(T expected) const
    {
      if (Logic::logic(this->actual() < expected))
      {
        throw TestExpectationLessThanOrEqualFailure<T, Logic>(this->actual(), expected, this->filename(), this->lineNumber());
      }
    }

    //aliases
    void lte(T expected) const {lessThanOrEqual(expected);}
  };

  template <class T, class Logic = ExpectLogic>
  class ExpectAtMost: public virtual ExpectBase<T>
  {
  public:
    void most(T expected) const
    {
      if (Logic::logic(this->actual() < expected))
      {
        throw TestExpectationAtMostFailure<T, Logic>(this->actual(), expected, this->filename(), this->lineNumber());
      }
    }
  };
}
