define i;
define N;
array mods[25];

N = 24;
i = 1;
mods[0] = 0 - 1;
while (i <= N) {
  mods[i] = N % i;
  i = i + 1;
}

