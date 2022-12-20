LEX = flex
YACC = bison

.PHONY: test clean

test: build/alang
	./build/alang <test/001_sum.als
	./build/alang <test/002_fact.als
	./build/alang <test/003_fizzbuzz.als
	./build/alang <test/004_eratosthenes.als

build/ast: src/ast.c src/ast.h build/ast_debug.o
	$(CC) -DMAIN src/ast.c build/ast_debug.o -o build/ast

build/alang: build/alang.yy.c build/alang.tab.c build/ast.o build/ast_debug.o
	$(CC) -DYYERROR_VERBOSE $^ -o $@ -Isrc -l fl -l y

build/alang.yy.c: src/alang.l
	$(LEX) -o $@ $<

build/alang.tab.c: src/alang.y
	$(YACC) -d -o $@ $<

build/ast.o: src/ast.c
	$(CC) -c $^ -o $@

build/ast_debug.o: src/ast_debug.c src/ast_debug.h
	$(CC) -c src/ast_debug.c -o $@

build/symbol_table.o: src/symbol_table.c src/symbol_table.h
	$(CC) -c src/symbol_table.c -o $@ -g

clean:
	rm -rf build/*
