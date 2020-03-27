COMPILE = gcc -g
TESTOUTPUTS = test-*.o test-*.out
ALLOUTPUTS = a.out *.o $(TESTOUTPUTS)

server: server.o queue-read.o linkedlist.o
	$(COMPILE) $^ -o $@.out

test-parser: test-parser.o parser.o queue-read.o linkedlist.o
	$(COMPILE) $^ -o $@.out

test-parser.o: test-parser.c
	$(COMPILE) -c $<

server.o: server.c
	$(COMPILE) -c $<

queue-read.o: queue-read.c queue-read.h
	$(COMPILE) -c $<

parser.o: parser.c parser.h
	$(COMPILE) -c $<

linkedlist.o: linkedlist.c linkedlist.h
	$(COMPILE) -c $<

clean:
	-rm -f $(ALLOUTPUTS)

clean-tests:
	-rm -f $(TESTOUTPUTS)

clean-build:
	make clean
	make

