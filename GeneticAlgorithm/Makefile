CC = g++
CFLAGS = -Wall -fopenmp -O3 -I/C/MinGW/lib/gcc/mingw32/6.3.0/include
LDFLAGS =
OBJFILES = Random.o MyUtil.o Gene.o Chromosome.o Individual.o GeneticAlgorithm.o main.o
TARGET = geneticalgorithm

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~