CC = g++
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm -pthread

SERIAL_SRC = serial_primecount.cpp
PARALLEL_SRC = parallel_primecount.cpp
SERIAL_OBJ = $(SERIAL_SRC:.cpp=.o)
PARALLEL_OBJ = $(PARALLEL_SRC:.cpp=.o)
SERIAL_TARGET = serial_primecount
PARALLEL_TARGET = parallel_primecount

PYTHON = python
PRIME_SCRIPT = genprimes.py
CSV_SCRIPT = create_csv.py


.PHONY: all clean primes csv

all: $(SERIAL_TARGET) $(PARALLEL_TARGET)

$(SERIAL_TARGET): $(SERIAL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(PARALLEL_TARGET): $(PARALLEL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

primes:
	i=100000; \
	while [ $$i -le 1000000 ]; do \
		$(PYTHON) $(PRIME_SCRIPT) $$i primes_$${i}.txt; \
		i=$$(($$i + 100000)); \
	done

csv:
	$(PYTHON) $(CSV_SCRIPT)

clean:
	rm -f $(SERIAL_TARGET) $(PARALLEL_TARGET) *.o *.csv