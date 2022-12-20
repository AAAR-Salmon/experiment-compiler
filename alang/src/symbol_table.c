#include "symbol_table.h"
#include <string.h>
#include <stdlib.h>

SymbolTable* createSymbolTable() {
  SymbolTable *symbol = malloc(sizeof(SymbolTable));
  symbol->name = "$";
  symbol->offset = 0;
  symbol->size = 0;
  symbol->next = NULL;
  return symbol;
}

int hasSymbol(SymbolTable *table, char *name) {
  if (table == NULL) {
    return 0;
  }
  if (strcmp(table->name, name) == 0) {
    return 1;
  }
  return hasSymbol(table->next, name);
}

SymbolTable* searchSymbol(SymbolTable *table, char *name) {
  if (table == NULL) {
    return 0;
  }
  if (strcmp(table->name, name) == 0) {
    return table;
  }
  return searchSymbol(table->next, name);
}

SymbolTable* addSymbol(SymbolTable *table, char *name, int size) {
  SymbolTable *symbol = malloc(sizeof(SymbolTable));
  symbol->name = name;
  symbol->offset = table->offset + table->size;
  symbol->size = size;
  symbol->next = table;
  return symbol;
}
