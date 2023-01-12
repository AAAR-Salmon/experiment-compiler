LEX = flex
YACC = bison

.PHONY: test clean

test: build/compiler
	./testall.bash

build/ast: src/ast.c src/ast.h build/ast_debug.o
	$(CC) -DMAIN src/ast.c build/ast_debug.o -o build/ast -g

build/compiler: build/compiler.yy.c build/compiler.tab.c build/ast.o build/ast_debug.o build/codegen.o build/symbol_table.o build/asm_builder.o
	$(CC) -DYYERROR_VERBOSE $^ -o $@ -Isrc -l fl -l y -g

build/compiler.yy.c: src/compiler.l
	$(LEX) -o $@ $<

build/compiler.tab.c: src/compiler.y
	$(YACC) -d -o $@ $<

build/ast.o: src/ast.c
	$(CC) -c $^ -o $@ -g

build/ast_debug.o: src/ast_debug.c src/ast_debug.h
	$(CC) -c src/ast_debug.c -o $@ -g

build/codegen.o: src/codegen.c src/codegen.h
	$(CC) -c src/codegen.c -o $@ -g

build/symbol_table.o: src/symbol_table.c src/symbol_table.h
	$(CC) -c src/symbol_table.c -o $@ -g

build/asm_builder.o: src/asm_builder.c src/asm_builder.h
	$(CC) -c src/asm_builder.c -o $@ -g

clean:
	rm -rf build/*
