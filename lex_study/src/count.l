%{
  int count_char = 0;
  int count_alphabet = 0;
  int count_num = 0;
  int count_line = 0;
%}
%%
[a-zA-Z]  count_alphabet++; count_char++;
[0-9]     count_num++; count_char++;
\n        count_line++; count_char++;
.         count_char++;
%%
int main(void) {
  yylex();
  printf("characters: %d\n", count_char);
  printf("alphabets: %d\n", count_alphabet);
  printf("numbers: %d\n", count_num);
  printf("lines: %d\n", count_line);
  return 0;
}
