CC = g++
CFLAGS = -Wall -fopenmp -O3 -std=c++11 -fopenmp
LDFLAGS =
OBJFILES = Random.o MyUtil.o Gene.o Chromosome.o Individual.o GeneticAlgorithm.o main.o
TARGET = GA


all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~