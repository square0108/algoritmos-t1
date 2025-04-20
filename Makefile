# Variables
# Se debe usar -O0 para que el compilador no optimice el loop en donde se realiza la medición de tiempo. (fuente: leonardlover/uhr)
CXXFLAGS = -I include/ -Wall -Wextra -O0
SRC = src/main.cpp src/testing_functions.cpp src/brute_force.cpp src/divide_and_conquer.cpp
TARGET = run

# El comando de compilación de todo!!!!!
# CXX es g++ (default)
all:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET) 

# Cuando hacemos make clean
clean:
	rm -f $(TARGET)

# Estas son palabras reservadas por make por si existe algun archivo con estos nombres.
.PHONY: all clean
