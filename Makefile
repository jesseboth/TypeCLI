CC := gcc
CFLAGS := -g -Wall -std=c99 -fPIC -D_DEFAULT_SOURCE -lm -pthread
CODE   := src/wordFile.c src/linked_list.o src/words.o src/terminal.o src/timer.o src/params.o src/utility/util.o
C_CODE := src/wordFile.c src/linked_list.c src/words.c src/terminal.c src/timer.c src/params.c src/utility/util.c


TESTS := $(wildcard tests/*)
TESTS := $(subst .c,,$(TESTS))
TESTS := $(subst tests/,,$(TESTS))
TESTS := $(filter-out _template,$(TESTS))

all: a.out run

a.out: $(CODE) src/main.o
	$(CC) -o $@ $^ $(CFLAGS)

run:
	@echo " "
	@./a.out
	@echo " "

debug: $(CODE) src/main.o
	$(CC) -o $@ $^ $(CFLAGS)
	@gdb ./a.out

asm:
	$(CC) -S $(C_CODE)

test: $(TESTS)
	@echo
	@for test in $^; do                                    		\
		printf "\nRunning %-s\n" "$$test";               		 \
		(./$$test && printf "Result  %-30s: ✔\n" "$$test";) || 	\
		printf "Result  %-30s: ❌\n" "$$test";       			\
	done
	@echo

# to create an object file from a source C file.
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
 

# This pattern will build any self-contained test file in tests/.  If
# your test file needs more support, you will need to write an explicit
# rule for it.
#
# To add a test, create a file called tests/testname.c that contains a
# main function and all of the relevant test code, then add the basename
# of the file (e.g., testname in this example) to TESTS, above.
%: tests/%.o $(CODE)
	@$(CC) -o $@ $^

clean:
	rm -f $(TESTS) a.out
	rm -f src/*.o tests/*.o *~ src/*~ tests/*~  *.s

# See previous assignments for a description of .PHONY
.PHONY: all clean