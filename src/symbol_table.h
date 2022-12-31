#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct SymbolTable {
  char *name;
  int offset;
  int size;
  struct SymbolTable *next;
} SymbolTable;

SymbolTable* createSymbolTable();
int hasSymbol(SymbolTable *table, char *name);
SymbolTable* searchSymbol(SymbolTable *table, char *name);
SymbolTable* addSymbol(SymbolTable *table, char *name, int size);
int sizeOfSymbolTable(SymbolTable *table);

#endif
