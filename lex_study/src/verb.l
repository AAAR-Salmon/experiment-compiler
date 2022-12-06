%%
(is|am|are|were|was)  printf("%s: is a verb.\n", yytext);
[^\n\t ]+             printf("%s: is not a verb.\n", yytext);
[\n\t ]               ;
%%
int main(void) {
  yylex();
  return 0;
}
