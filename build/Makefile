CFLAGS = -Wall -g -I
CXXFLAGS = -g
LDFLAGS = -std=c++11 -lstdc++ 
SOURCES = ../src/main.cpp \
		  ../src/sinusDrawing.cpp \
		  ../src/spectrumDrawing.cpp \
		  ../src/AMModulation.cpp \
		  ../src/PMModulation.cpp \
		  ../src/ASKModulation.cpp \
		  ../src/FSKModulation.cpp \
		  ../src/PSKModulation.cpp \
		  ../src/ASKDemodulation.cpp \
		  ../src/PSKDemodulation.cpp \
		  ../src/FSKDemodulation.cpp

NAME = prog

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(NAME)
