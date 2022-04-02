#include <assert.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

int N;
char **info = new char *[N];

char Tran(char ch) {
  if (ch < 97) {    // 大写
    return ch + 32; // 变小写
  }
  return ch - 32; // 变大写
}

void Zig(int &y, int &x, int level) {
  /*{{{*/
  int start = level - 1;
  int end = N - level;
  int gap = end - start;

  if (y == start) {
    if (x != start) {
      y += gap - (end - x);
    }
    x = end;
  } else if (y == end) {
    if (x != end) {
      y -= gap - (x - start);
    }
    x = start;
  } else if (x == start) {
    if (y != start) {
      x += gap - (y - start);
    }
    y = start;
  } else {
    if (y != end) {
      x -= gap - (end - y);
    }
    y = end;
  }
  /*}}}*/
}

void PrintAll() {
  for (int j = 0; j < N; ++j) {
    cout << info[j] << endl;
  }
}

void LeftShift(int y) {
  y -= 1;
  char temp = info[y][0];
  for (int i = 1; i < N; ++i) {
    info[y][i - 1] = Tran(info[y][i]);
  }
  info[y][N - 1] = Tran(temp);
}

void RightShift(int y) {
  y -= 1;
  char temp = info[y][0];
  for (int i = N - 1; i > 0; ++i) {
    info[y][i - 1] = Tran(info[y][i]);
  }
  info[y][0] = Tran(temp);
}

void UpperShift(int x) {
  x -= 1;
  char temp = info[0][x];
  for (int i = 1; i < N; ++i) {
    info[i - 1][x] = Tran(info[i][x]);
  }
  info[N - 1][x] = Tran(temp);
}

void Rotate(int level) {
  char current_char;
  char temp_char;
  int x;
  int y;
  int start = level - 1;
  int end = N - level;

  if (start == end) {
    info[start][start] = Tran(info[start][start]);
  } else {
    for (int j = start; j < end; ++j) {
      y = start;
      x = j;
      current_char = Tran(info[y][x]);
      for (int i = 0; i < 4; ++i) {
        Zig(y, x, level);
        temp_char = info[y][x];
        info[y][x] = current_char;
        current_char = Tran(temp_char);
      }
    }
  }
}

void Do() {
  int i;
  int M;
  vector<char *> x;
  vector<char *>::iterator it;
  vector<string> type;
  string op;

  cin >> N;

  for (i = 0; i < N; ++i) {
    info[i] = new char[N];
    cin >> info[i];
  }

  int nr;
  cin >> M;
  i = 0;
  while (1) {
    if (i == M) {
      break;
    }
    cin >> op;
    if (!op.compare("print_it!")) {
      PrintAll();
    } else {
      cin >> nr;
      if (!op.compare("clockwise_rotation")) {
        Rotate(nr);
      } else if (!op.compare("anticlockwise_rotation")) {
      } else if (!op.compare("left_shift")) {
        LeftShift(nr);
      } else if (!op.compare("right_shift")) {
        RightShift(nr);
      } else if (!op.compare("upper_shift")) {
        UpperShift(nr);
      }
    }
    i += 1;
  }
}

void Test() {
  /*{{{*/
  // test
  int x, y;
  N = 4;

  x = 0;
  y = 0;
  Zig(x, y, 1);
  assert(x == 3);
  assert(y == 0);

  x = 1;
  y = 0;
  Zig(x, y, 1);
  assert(x == 3);
  assert(y == 1);

  x = 2;
  y = 0;
  Zig(x, y, 1);
  assert(x == 3);
  assert(y == 2);

  x = 3;
  y = 0;
  Zig(x, y, 1);
  assert(x == 3);
  assert(y == 3);

  x = 3;
  y = 0;
  Zig(x, y, 1);
  assert(x == 3);
  assert(y == 3);

  x = 3;
  y = 1;
  Zig(x, y, 1);
  assert(x == 2);
  assert(y == 3);

  x = 3;
  y = 2;
  Zig(x, y, 1);
  assert(x == 1);
  assert(y == 3);

  x = 3;
  y = 3;
  Zig(x, y, 1);
  assert(x == 0);
  assert(y == 3);

  x = 0;
  y = 3;
  Zig(x, y, 1);
  assert(x == 0);
  assert(y == 0);

  x = 0;
  y = 2;
  Zig(x, y, 1);
  assert(x == 1);
  assert(y == 0);

  x = 0;
  y = 1;
  Zig(x, y, 1);
  assert(x == 2);
  assert(y == 0);

  x = 1;
  y = 1;
  Zig(x, y, 2);
  assert(x == 2);
  assert(y == 1);

  x = 2;
  y = 1;
  Zig(x, y, 2);
  assert(x == 2);
  assert(y == 2);

  x = 2;
  y = 2;
  Zig(x, y, 2);
  assert(x == 1);
  assert(y == 2);

  x = 1;
  y = 2;
  Zig(x, y, 2);
  assert(x == 1);
  assert(y == 1);

  N = 1;
  x = 0;
  y = 0;
  Zig(x, y, 1);
  assert(x == 0);
  assert(y == 0);

  N = 5;
  x = 0;
  y = 0;
  Zig(x, y, 1);
  assert(x == 4);
  assert(y == 0);

  x = 0;
  y = 1;
  Zig(x, y, 1);
  assert(x == 3);
  assert(y == 0);

  x = 0;
  y = 1;
  Zig(x, y, 1);
  assert(x == 3);
  assert(y == 0);

  /*}}}*/
}

int main() { Do(); }
