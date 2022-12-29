CC = g++
CFLAGS = -Wall -O3
LDFLAGS =
OBJFILES = Common/Random.o Common/MyUtil.o Common/Parameter.o Common/ParameterSet.o Common/Population.o Common/OptimizationMethod.o GeneticAlgorithm/Individual.o GeneticAlgorithm/GeneticAlgorithm.o HillClimbing/HillClimbing.o main.o
TARGET = OptimizationAlgorithms.exe


all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(TARGET) $(OBJFILES) *~