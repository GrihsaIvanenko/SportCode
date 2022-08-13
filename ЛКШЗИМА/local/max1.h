#include <cassert>

long long GetN() {
  return 4;
}
long long GetElement(long long i) {
    switch (i) {
    case 0:
        return 0;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 1;
    }
    assert(false);
}
