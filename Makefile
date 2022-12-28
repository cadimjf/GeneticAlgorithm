CC = g++
CFLAGS = -Wall -O3
LDFLAGS =
OBJFILES = Common\Random.o Common\MyUtil.o Common\Parameter.o Common\ParameterSet.o GeneticAlgorithm\Individual.o GeneticAlgorithm\GeneticAlgorithm.o main.o
TARGET = OptimizationAlgorithms


all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm $(OBJFILES) $(TARGET) *~