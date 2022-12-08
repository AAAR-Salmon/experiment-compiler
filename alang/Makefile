LEX = flex
YACC = bison

.PHONY: test clean

test: build/alang
	./build/alang <test/001_sum.als
	./build/alang <test/002_fact.als
	./build/alang <test/003_fizzbuzz.als

build/alang: build/alang.yy.c build/alang.tab.c
	$(CC) -DYYERROR_VERBOSE $^ -o $@ -l fl -l y

build/alang.yy.c: src/alang.l
	$(LEX) -o $@ $<

build/alang.tab.c: src/alang.y
	$(YACC) -d -o $@ $<

clean:
	rm -rf build/*
