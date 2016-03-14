#include "metal_test.h"
#include "fixture.h"

METAL_FIXTURE_DECLARE;
METAL_SETUP{};
METAL_TEARDOWN{};

METAL_TESTS_BEGIN(testsScheduler)
{
   METAL_TEST(trivial_test)
   {
      unsigned int expectedValue = 1;
      METAL_ASSERT_EQ(expectedValue, METAL_FIXTURE.testValue);
   }
}
METAL_TESTS_END
