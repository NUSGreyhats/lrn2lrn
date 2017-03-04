all: compile_c_source

compile_c_source:
	for f in $$(ls ./src/); do \
		gcc -O0 ./src/$$f -o ./build/$${f%.*}; \
	done
