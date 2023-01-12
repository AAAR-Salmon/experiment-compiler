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
  i = i + 1;
}

i = 0;
while(i * i <= N) {
  if (isprime[i] != 0) {
    j = i * 2;
    while(j <= N){
      isprime[j] = 0;
      j = j + i;
    }
  }
  i = i + 1;
}
