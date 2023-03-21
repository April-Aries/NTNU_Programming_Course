all:
	gcc -c mystring.c -o mystring.o
	gcc hw0101.c mystring.o -o hw0101
	gcc -c insert.c -o insert.o
	gcc hw0102.c insert.o -o hw0102
	gcc -c abacus.c -o abacus.o
	gcc hw0103.c abacus.o -o hw0103
	gcc hw0104.c -o hw0104
	gcc -c oop.c -o oop.o
	gcc hw0105.c oop.o -o hw0105
clean:
	rm -rf mystring.o
	rm -rf hw0101
	rm -rf insert.o
	rm -rf hw0102
	rm -rf abacus.o
	rm -rf hw0103
	rm -rf hw0104
	rm -rf oop.o
	rm -rf hw0105
test:
	gcc hw0104.c -o hw0104
