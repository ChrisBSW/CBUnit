#pragma once

namespace CBUnit
{
  class ExpectTraits
  {
  public:
    static constexpr bool hasEquals = true;
    static constexpr bool hasGreaterThan = false;
    static constexpr bool hasGreaterThanOrEqual = false;
    static constexpr bool hasLessThan = false;
    static constexpr bool hasLessThanOrEqual = false;
  };
}

