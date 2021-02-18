#pragma once
#include "ExpectBase.hpp"
#include "ExpectLogic.hpp"
#include "TestExpectationMessageBuilder.hpp"
#include "TestStructure/TestError.hpp"

#include <sstream>

namespace CBUnit
{
  namespace
  {
    template <class T> std::string buildWithinMessage(const T& delta)
    {
      std::stringstream ss;
      ss << "to be within ";
      ss << delta;
      ss << " of";
      return ss.str();
    }

    template <class T> std::string buildNotWithinMessage(const T& delta)
    {
      return std::string("not ") + buildWithinMessage(delta);
    }

    template <class T, class Logic> class TestExpectationWithinFailure {};
  
    template <class T> class TestExpectationWithinFailure<T, ExpectLogic>: public TestError
    {
    public:
      TestExpectationWithinFailure(const T& actual, const T& expected, const T& delta, const char* filename, uint32_t lineNumber):
        TestError(TestExpectationMessageBuilder::buildMessage(actual, expected, buildWithinMessage(delta)), filename, lineNumber)
      {}
    };

    template <class T> class TestExpectationWithinFailure<T, ExpectInvertingLogic>: public TestError
    {
    public:
      TestExpectationWithinFailure(const T& actual, const T& expected, const T& delta, const char* filename, uint32_t lineNumber):
        TestError(TestExpectationMessageBuilder::buildMessage(actual, expected, buildNotWithinMessage(delta)), filename, lineNumber)
      {}
    };
  }

  template <class T, class Logic = ExpectLogic>
  class ExpectWithin: public ExpectBaseMixin<T>
  {
  public:
    ExpectWithin(const T& delta, const T& actual, const char* filename, uint32_t lineNumber):
      ExpectBaseMixin<T>(actual, filename, lineNumber),
      _delta(delta)
    {}
        
    void of(const T& expected) const
    {
      auto min = expected - _delta;
      auto max = expected + _delta;
      if (Logic::logic(this->actual() >= min && this->actual() >= max))
      {
        throw TestExpectationWithinFailure<T, Logic>(this->actual(), expected, _delta, this->filename(), this->lineNumber());
      }
    }
  private:
    const T& _delta;
  };
}