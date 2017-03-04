all: compile_x64 compile_x86

compile_x64:
	for f in $$(ls ./src/); do \
		gcc -O0 ./src/$$f -o ./build/$${f%.*}_x64; \
	done

compile_x86:
	for f in $$(ls ./src/); do \
		gcc -m32 -O0 ./src/$$f -o ./build/$${f%.*}_x86; \
	done
