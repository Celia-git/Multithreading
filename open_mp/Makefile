CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -fopenmp
LDFLAGS = -lm -pthread -fopenmp

SERIAL_SRC = serial_primecount.cpp
PARALLEL_C11_SRC = parallel_primecount_c11.cpp
PARALLEL_OMP_SRC = parallel_primecount_omp.cpp
SERIAL_OBJ = $(SERIAL_SRC:.cpp=.o)
PARALLEL_C11_OBJ = $(PARALLEL_C11_SRC:.cpp=.o)
PARALLEL_OMP_OBJ = $(PARALLEL_OMP_SRC:.cpp=.o)
SERIAL_TARGET = serial_primecount
PARALLEL_C11_TARGET = parallel_primecount_c11
PARALLEL_OMP_TARGET = parallel_primecount_omp

PYTHON = python
PRIME_SCRIPT = genprimes.py
CSV_SCRIPT = create_csv.py


.PHONY: all clean primes csv

all: $(SERIAL_TARGET) $(PARALLEL_C11_TARGET) $(PARALLEL_OMP_TARGET)

$(SERIAL_TARGET): $(SERIAL_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(PARALLEL_C11_TARGET): $(PARALLEL_C11_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(PARALLEL_OMP_TARGET): $(PARALLEL_OMP_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
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
	rm -f $(SERIAL_TARGET) $(PARALLEL_C11_TARGET) $(PARALLEL_OMP_TARGET) *.o *.csv