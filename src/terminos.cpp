#include "../include/terminos.h"
#include <cstdlib>

struct I : Termino {
  I() {
    x_start = 3;
    y_start = 20;

    coordinates[0] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}};
    coordinates[1] = {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
    coordinates[2] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
    coordinates[3] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};

    inner = AQUA;
    outer = DARK_AQUA;
  }
  ~I() {}
} I;

struct J : Termino {
  J() {
    x_start = 3;
    y_start = 20;

    coordinates[0] = {{0, 1}, {0, 2}, {1, 1}, {2, 1}};
    coordinates[1] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
    coordinates[2] = {{0, 1}, {1, 1}, {2, 1}, {2, 0}};
    coordinates[3] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};

    inner = BLUE;
    outer = DARK_BLUE;
  }
  ~J() {}
} J;

struct L : Termino {
  L() {
    x_start = 3;
    y_start = 20;

    coordinates[0] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};
    coordinates[1] = {{1, 0}, {1, 1}, {1, 2}, {2, 0}};
    coordinates[2] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
    coordinates[3] = {{0, 2}, {1, 2}, {1, 1}, {1, 0}};

    inner = ORANGE;
    outer = DARK_ORANGE;
  }
  ~L() {}
} L;

struct O : Termino {
  O() {
    x_start = 3;
    y_start = 20;

    coordinates[0] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    coordinates[1] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    coordinates[2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    coordinates[3] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

    inner = YELLOW;
    outer = DARK_YELLOW;
  }
  ~O() {}
} O;

struct Z : Termino {
  Z() {
    x_start = 3;
    y_start = 20;

    coordinates[0] = {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
    coordinates[1] = {{1, 2}, {1, 1}, {2, 1}, {2, 0}};
    coordinates[2] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    coordinates[3] = {{0, 2}, {0, 1}, {1, 1}, {1, 0}};

    inner = GREEN;
    outer = DARK_GREEN;
  }
  ~Z() {}
} Z;

struct T : Termino {
  T() {
    x_start = 3;
    y_start = 20;

    coordinates[0] = {{0, 1}, {1, 1}, {2, 1}, {1, 2}};
    coordinates[1] = {{1, 0}, {1, 1}, {1, 2}, {2, 1}};
    coordinates[2] = {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
    coordinates[3] = {{1, 0}, {1, 1}, {1, 2}, {0, 1}};

    inner = PURPLE;
    outer = DARK_PURPLE;
  }
  ~T() {}
} T;

struct S : Termino {
  S() {
    x_start = 3;
    y_start = 20;

    coordinates[0] = {{0, 2}, {1, 2}, {1, 1}, {2, 1}};
    coordinates[1] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}};
    coordinates[2] = {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
    coordinates[3] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};

    inner = RED;
    outer = DARK_RED;
  }
  ~S() {}
} S;

Termino* get_next_termino() {
  // this is bad but i wanted to show PIETER A PROTOTYPE BUT HE HAS TAKEN SO LONG I MIGHT JUST FIX THIS AND MAKE IT WORK CORRECTLY
  int random_term = rand() % 7;

  switch (random_term) {
    case 0: {
      return &I;
      break;
    }
    case 1: {
      return &J;
      break;
    }
    case 2: {
      return &L;
      break;
    }
    case 3: {
      return &O;
      break;
    }
    case 4: {
      return &Z;
      break;
    }
    case 5: {
      return &T;
      break;
    }
    case 6: {
      return &S;
      break;
    }
  }

  return &Z;
}

Termino* get_preview_termino() {
  return &I;
}
