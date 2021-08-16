# List of files.
Hpps = $(wildcard *.hpp)
Cpps = $(filter-out main.cpp,$(wildcard *.cpp))
Outs = $(Cpps:.cpp=.o)
All = main.cpp $(Outs)
AllDeb = $(All:.o=.deb.o)

# Name of program file (without extension)
ExeName = rmq

# Allows parallel processing.
MAKEFLAGS = -j 24



# --- Main Compiling ---

$(ExeName).out: $(All) $(Hpps)
	g++ -Wall -Wextra -O3 $(All) -o $@

%.o: %.cpp %.h
	g++ -Wall -Wextra -O3 -c $< -o $@

run: $(ExeName).out
	./$<


# --- Debuging ---

$(ExeName).deb.out: $(AllDeb) $(Hpps)
	g++ -Wall -Wextra -g $(AllDeb) -o $@

%.deb.o: %.cpp %.h
	g++ -Wall -Wextra -g -c $< -o $@

valgrind: $(ExeName).deb.out
	valgrind ./$<


# --- Clean-Up ---

clean:
	rm -f *.o *.out *.debug
