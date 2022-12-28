LEX = flex
YACC = bison

.PHONY: test clean

test: build/alang
	./build/alang <test/001_sum.als >build/001_sum.s
	./build/alang <test/002_fact.als >build/002_fact.s
	./build/alang <test/003_fizzbuzz.als >build/003_fizzbuzz.s
	./build/alang <test/004_eratosthenes.als >build/004_eratpsthenes.s
	./build/alang <test/010_varindex_assign.als >build/010_varindex_assign.s
	./build/alang <test/011_leq_op.als >build/011_leq_op.s
	./build/alang <test/012_array.als >build/012_array.s
	./build/alang <test/013_division.als >build/013_division.s
	./build/alang <test/014_prime.als >build/014_prime.s
	./build/alang <test/015_mod.als >build/015_mod.s

build/ast: src/ast.c src/ast.h build/ast_debug.o
	$(CC) -DMAIN src/ast.c build/ast_debug.o -o build/ast -g

build/alang: build/alang.yy.c build/alang.tab.c build/ast.o build/ast_debug.o build/codegen.o build/symbol_table.o build/asm_builder.o
	$(CC) -DYYERROR_VERBOSE $^ -o $@ -Isrc -l fl -l y -g

build/alang.yy.c: src/alang.l
	$(LEX) -o $@ $<

build/alang.tab.c: src/alang.y
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
