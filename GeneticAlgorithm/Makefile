CC = g++
CFLAGS = -Wall -O3
LDFLAGS =
OBJFILES = Random.o MyUtil.o Gene.o Chromosome.o Individual.o GeneticAlgorithm.o main.o
TARGET = GA


all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~