#include "../include/terminos.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Termino::Termino() {
  set_kick_data();
}
Termino::~Termino() {}

void Termino::set_kick_data() {
  // default -> right position
  wall_kick_data[{0, 1}] = {{-1,0}, {-1,+1}, {0,-2}, {-1, -2}};
  // right -> default position
  wall_kick_data[{1, 0}] = {{+1,0}, {+1,-1}, {0,+2}, {+1, +2}};
  // right -> upside down position
  wall_kick_data[{1, 2}] = {{+1,0}, {+1,-1}, {0,+2}, {+1, +2}};
  // upside down -> right position
  wall_kick_data[{2, 1}] = {{-1,0}, {-1,+1}, {0,-2}, {-1, -2}};
  //  upside down -> left position
  wall_kick_data[{2, 3}] = {{+1,0}, {+1,+1}, {0,-2}, {+1, -2}};
  // ledt -> upside down position
  wall_kick_data[{3, 2}] = {{-1,0}, {-1,-1}, {0,+2}, {-1, +2}};
  // left ->  default position
  wall_kick_data[{3, 0}] = {{-1,0}, {-1,-1}, {0,+2}, {-1, +2}};
  // default -> left position
  wall_kick_data[{0, 3}] = {{+1,0}, {+1,+1}, {0,-2}, {+1, -2}};
}

struct I : Termino {
  I() {
    x_start = 3;
    y_start = 18;

    coordinates[0] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}};
    coordinates[1] = {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
    coordinates[2] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
    coordinates[3] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};

    colour_map_key = 1;

    set_kick_data();
  }
  ~I() {}

  // I piece kick data with arika's modifications
  // the I piece is the only piece along side the O piece that has different wall kick data
  void set_kick_data() override {
    // default -> right position
    wall_kick_data[{0, 1}] = {{-2,0}, {+1,0}, {+1,+2}, {-2, -1}};
    // right -> default position
    wall_kick_data[{1, 0}] = {{+2,0}, {-1,0}, {+2,+1}, {-1, -2}};
    // right -> upside down position
    wall_kick_data[{1, 2}] = {{-1,0}, {+2,0}, {-1,+2}, {+2, -1}};
    // upside down -> right position
    wall_kick_data[{2, 1}] = {{-2,0}, {+1,0}, {-2,+1}, {+1, -1}};
    //  upside down -> left position
    wall_kick_data[{2, 3}] = {{+2,0}, {-1,0}, {+2,+1}, {-1, -1}};
    // ledt -> upside down position
    wall_kick_data[{3, 2}] = {{+1,0}, {-2,0}, {+1,+2}, {-2, -1}};
    // left ->  default position
    wall_kick_data[{3, 0}] = {{-2,0}, {+1,0}, {-2,+1}, {+1, -2}};
    // default -> left position
    wall_kick_data[{0, 3}] = {{+2,0}, {-1,0}, {-1,+2}, {+2, -1}};
  }
} I;

struct J : Termino {
  J() {
    x_start = 3;
    y_start = 19;

    coordinates[0] = {{0, 1}, {0, 2}, {1, 1}, {2, 1}};
    coordinates[1] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
    coordinates[2] = {{0, 1}, {1, 1}, {2, 1}, {2, 0}};
    coordinates[3] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};

    colour_map_key = 2;
  }
  ~J() {}
} J;

struct L : Termino {
  L() {
    x_start = 3;
    y_start = 19;

    coordinates[0] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};
    coordinates[1] = {{1, 0}, {1, 1}, {1, 2}, {2, 0}};
    coordinates[2] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
    coordinates[3] = {{0, 2}, {1, 2}, {1, 1}, {1, 0}};

    colour_map_key = 3;
  }
  ~L() {}
} L;

struct O : Termino {
  O() {
    x_start = 4;
    y_start = 20;

    coordinates[0] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    coordinates[1] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    coordinates[2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    coordinates[3] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

    colour_map_key = 4;

    set_kick_data();
  }
  ~O() {}

  void set_kick_data() override {
    // default -> right position
    wall_kick_data[{0, 1}] = {{0,0}, {0,0}, {0,0}, {0, 0}};
    wall_kick_data[{1, 0}] = {{0,0}, {0,0}, {0,0}, {0, 0}};
    wall_kick_data[{1, 2}] = {{0,0}, {0,0}, {0,0}, {0, 0}};
    wall_kick_data[{2, 1}] = {{0,0}, {0,0}, {0,0}, {0, 0}};
    wall_kick_data[{2, 3}] = {{0,0}, {0,0}, {0,0}, {0, 0}};
    wall_kick_data[{3, 2}] = {{0,0}, {0,0}, {0,0}, {0, 0}};
    wall_kick_data[{3, 0}] = {{0,0}, {0,0}, {0,0}, {0, 0}};
    wall_kick_data[{0, 3}] = {{0,0}, {0,0}, {0,0}, {0, 0}};
  }
} O;

struct Z : Termino {
  Z() {
    x_start = 3;
    y_start = 19;

    coordinates[0] = {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
    coordinates[1] = {{1, 2}, {1, 1}, {2, 1}, {2, 0}};
    coordinates[2] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
    coordinates[3] = {{0, 2}, {0, 1}, {1, 1}, {1, 0}};

    colour_map_key = 5;
  }
  ~Z() {}
} Z;

struct T : Termino {
  T() {
    x_start = 3;
    y_start = 19;

    coordinates[0] = {{0, 1}, {1, 1}, {2, 1}, {1, 2}};
    coordinates[1] = {{1, 0}, {1, 1}, {1, 2}, {2, 1}};
    coordinates[2] = {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
    coordinates[3] = {{1, 0}, {1, 1}, {1, 2}, {0, 1}};

    colour_map_key = 6;
  }
  ~T() {}
} T;

struct S : Termino {
  S() {
    x_start = 3;
    y_start = 19;

    coordinates[0] = {{0, 2}, {1, 2}, {1, 1}, {2, 1}};
    coordinates[1] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}};
    coordinates[2] = {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
    coordinates[3] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};

    colour_map_key = 7;
 }
  ~S() {}
} S;

static const int MAX = 7;
static int arrBag[MAX];
static Termino* preview_piece = nullptr;

Termino* get_piece(int piece);

void fill_bag() {
  for (int i = 0; i<MAX;i++) {
    arrBag[i] = i + 1;
  }

  for (int i = 0; i<MAX;i++) {
    int swap = rand() % 7;
    int temp = arrBag[i];
    arrBag[i] = arrBag[swap];
    arrBag[swap] = temp;
  }
}

Termino* next_piece() {
  for (int i = 0; i<MAX;i++) {
    if (arrBag[i] != 0) {
      int piece = arrBag[i];
      arrBag[i] = 0;
      return get_piece(piece);
    }
      //std::cout << "test" << i << std::endl;
  }

  // this is kinda cool if it doesnt return in the top loop
  // it means that all the pieces were taken so it fills the bag and returns the value of the function on the next run
  fill_bag();
  return next_piece();
}

Termino* get_piece(int piece) {
  switch (piece) {
    case 1: {
      return &I;
    }
    case 2: {
      return &J;
    }
    case 3: {
      return &L;
    }
    case 4: {
      return &O;
    }
    case 5: {
      return &Z;
    }
    case 6: {
      return &T;
    }
    case 7: {
      return &S;
    }
  }

  // idk just in case should never actually happen
  return &Z;
}

Termino* get_next_termino() {
  if (!preview_piece) {
    preview_piece = next_piece();
  }

  Termino *next_termino = preview_piece;

  preview_piece = next_piece();

  return next_termino;
}

Termino* get_preview_termino() {
  if (!preview_piece) {
    preview_piece = next_piece();
  }

  return preview_piece;
}

void termino_init() {
  srand(time(NULL));

  for (int i = 0; i<MAX; i++) {
    arrBag[i] = 0;
  }
};
