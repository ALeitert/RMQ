# List of files.
Cpps = $(filter-out main.cpp,$(wildcard *.cpp))
Outs = $(Cpps:.cpp=.o)
All = main.cpp $(Outs)
AllDeb = $(All:.o=.deb.o)

# Name of program file (without extension)
ExeName = rmq


# --- Main Compiling ---

$(ExeName).out: $(All)
	g++ -Wall -Wextra -O3 $(All) -o $@

%.o: %.cpp %.h
	g++ -Wall -Wextra -O3 -c $< -o $@

run: $(ExeName).out
	./$<


# --- Debuging ---

$(ExeName).deb.out: $(AllDeb)
	g++ -Wall -Wextra -g $(AllDeb) -o $@

%.deb.o: %.cpp %.h
	g++ -Wall -Wextra -g -c $< -o $@

valgrind: $(ExeName).deb.out
	valgrind ./$<


# --- Clean-Up ---

clean:
	rm -f *.o *.out *.debug
