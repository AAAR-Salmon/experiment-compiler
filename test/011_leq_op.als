define a;
array b[101];

a = 0;
while (a < 101) {
  b[a] = 0;
  a = a + 1;
}

a = 2;
b[1] = 1;
while (a <= 50) {
  b[a] = b[a - 1] + b[a - 2];
  a = a + 1;
}
