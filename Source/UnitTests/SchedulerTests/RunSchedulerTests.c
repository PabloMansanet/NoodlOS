#include <stdio.h>

extern int testsScheduler(void);

int main()
{
  int totalFailedTests = 0;
  totalFailedTests += testsScheduler();

  printf(__FILE__" has finished running\r\n");
  if (totalFailedTests > 0)
    printf("Number of failed tests: %d\r\n\r\n", totalFailedTests);
  else
    printf("All tests passed!\r\n\r\n");

  return (totalFailedTests != 0);
}
