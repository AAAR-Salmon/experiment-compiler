LEX = flex

count: src/count.l
	$(LEX) -o build/count.yy.c $<
	$(CC) build/count.yy.c -o build/$@ -l fl

verb: src/verb.l
	$(LEX) -o build/verb.yy.c $<
	$(CC) build/verb.yy.c -o build/$@ -l fl

clean:
	rm -rf build/*
