#include "testlib.h"
#include <cmath>

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);

  double pans = ouf.readDouble(), jans = ans.readDouble();

  if (fabs(pans - jans) < 1e-5 || (fabs(pans - jans) / jans) < 1e-5)
    quitf(_ok, "Accepted\n");
  else
    quitf(_wa, "Wrong answer, expected %f, found %f\n", jans, pans);
}