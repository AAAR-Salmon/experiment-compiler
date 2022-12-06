LEX = flex

count: src/count.l
	$(LEX) -o build/count.yy.c $<
	$(CC) build/count.yy.c -o build/$@ -l fl

clean:
	rm -rf build/*
