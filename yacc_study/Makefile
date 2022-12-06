LEX = flex
YACC = bison

arith: build/arith.yy.c build/arith.tab.c
	$(CC) $^ -o build/$@ -l fl -l y

build/arith.yy.c: src/arith.l
	$(LEX) -o $@ $<

build/arith.tab.c: src/arith.y
	$(YACC) -d -o $@ $<

clean:
	rm -rf build/*
