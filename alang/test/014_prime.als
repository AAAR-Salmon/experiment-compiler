define N;
define i;
define j;
array isprime[1001];

N = 1000;

isprime[0] = 0;
isprime[1] = 0;

i = 2;
while (i <= N) {
  isprime[i] = 1;
  j = 2;
  while (j < N) {
    if (i % j == 0) {
      isprime[i] = 0;
    }
    j = j + 1;
  }
  i = i + 1;
}
