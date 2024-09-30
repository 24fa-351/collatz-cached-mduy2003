main: main.c
	gcc -o main main.c collatz.c cache.c

clean:
	rm main

cache: main
	bash cache.sh