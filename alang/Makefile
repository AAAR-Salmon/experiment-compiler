LEX = flex
YACC = bison

alang: build/alang.yy.c build/alang.tab.c
	$(CC) $^ -o build/$@ -l fl -l y

build/alang.yy.c: src/alang.l
	$(LEX) -o $@ $<

build/alang.tab.c: src/alang.y
	$(YACC) -d -o $@ $<

clean:
	rm -rf build/*
