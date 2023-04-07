CXX=g++
CXXFLAGS=-Isrc/Include
LDFLAGS=-Lsrc/lib -lSDL2 -lSDL2_ttf -lSDL2_image

all: TheOne

TheOne: main.o Application.o Player.o Physics.o Terrain.o
	$(CXX) $(LDFLAGS) $^ -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Application.o: Application.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Physics.o: Physics.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Terrain.o: Terrain.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o TheOne
