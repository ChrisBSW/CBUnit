#pragma once
#include "ExpectTo.hpp"
#include "ExpectIs.hpp"

#include "Expect/Chains/ExpectEquals.hpp"

#include <string>
namespace CBUnit
{
  namespace
  {
    template <class Logic> class TestExpectationContainFailure {};
  
    template <> class TestExpectationContainFailure<ExpectLogic>: public TestError
    {
    public:
      TestExpectationContainFailure(const std::string& actual, const std::string& expected, const char* filename, uint32_t lineNumber):
        TestError(TestExpectationMessageBuilder::buildMessage(actual, expected, "to contain"), filename, lineNumber)
      {}
    };

    template <> class TestExpectationContainFailure<ExpectInvertingLogic>: public TestError
    {
    public:
      TestExpectationContainFailure(const std::string& actual, const std::string& expected, const char* filename, uint32_t lineNumber):
        TestError(TestExpectationMessageBuilder::buildMessage(actual, expected, "not to contain"), filename, lineNumber)
      {}
    };
  }

  template <typename Logic> class ExpectToString: public ExpectEquals<std::string, Logic>
  {
  public:
    void contain(const std::string& value)
    {
      if (Logic::logic(this->actual().find(value) == std::string::npos))
      {
        throw TestExpectationContainFailure<Logic>(this->actual(), value, this->filename(), this->lineNumber());
      }
    }
  };

  template <typename T, typename Logic> class ExpectTo<T, Logic, typename std::enable_if<ExpectIs<T>::string>::type>: public ExpectToString<Logic> {};
}