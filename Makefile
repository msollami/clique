# TODO - convert to cmake

CXX=clang++

all: dcs dhcs rcs rhcs

dcs: dcs.cpp
	$(CXX) -o dcs dcs.cpp -O3

dhcs: dhcs.cpp
	$(CXX) -o dhcs dhcs.cpp -O3

rcs: rcs.cpp
	$(CXX) -o rcs rcs.cpp -O3

rhcs: rhcs.cpp
	$(CXX) -o rhcs rhcs.cpp -O3

clean:
	rm -f dcs dhcs rcs rhcs *.o
