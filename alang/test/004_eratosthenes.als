define N;
define i;
define j;
define k;
array a[1001];
N = 1000;
i = 1;
while (i <= N) {
  a[i] = 1;
  i = i + 1;
}
i = 2;
while(i <= N/2) {
  j = 2;
  while(j <= N/i){
    k = i * j;
    a[k] = 0;
    j = j + 1;
  }
  i = i + 1;
}
