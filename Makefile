LEX = flex
YACC = bison

.PHONY: test clean

test: build/compiler
	./build/compiler <test/001_sum.src >build/001_sum.s
	./build/compiler <test/002_fact.src >build/002_fact.s
	./build/compiler <test/003_fizzbuzz.src >build/003_fizzbuzz.s
	./build/compiler <test/004_eratosthenes.src >build/004_eratosthenes.s
	./build/compiler <test/010_varindex_assign.src >build/010_varindex_assign.s
	./build/compiler <test/011_leq_op.src >build/011_leq_op.s
	./build/compiler <test/012_array.src >build/012_array.s
	./build/compiler <test/013_division.src >build/013_division.s
	./build/compiler <test/014_prime.src >build/014_prime.s
	./build/compiler <test/015_mod.src >build/015_mod.s

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
