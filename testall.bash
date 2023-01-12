#!/bin/bash

declare -a tests=(
  "test/001_sum.src             test/001_sum.globlmem"
  "test/002_fact.src            test/002_fact.globlmem"
  "test/003_fizzbuzz.src        test/003_fizzbuzz.globlmem"
  "test/004_eratosthenes.src    test/004_eratosthenes.globlmem"
  "test/010_varindex_assign.src test/010_varindex_assign.globlmem"
  "test/011_leq_op.src          test/011_leq_op.globlmem"
  "test/012_array.src           test/012_array.globlmem"
  "test/013_division.src        test/013_division.globlmem"
  "test/014_prime.src           test/014_prime.globlmem"
  "test/015_mod.src             test/015_mod.globlmem"
)

for pair in "${tests[@]}"; do
  set $pair
  source=$1
  globlmem=$2
  testname=$(echo $source | perl -pe 's|test/(.*).src|$1|')
  
  echo -n "test $testname: "
  if ./mapstest.pl build/compiler $source $globlmem >/dev/null; then
    printf "\033[32m%s\033[0m\n" pass
  else
    printf "\033[31m%s\033[0m\n" failed
  fi
done
