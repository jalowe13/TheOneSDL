# Makefile for The One
# Jacob Lowe

CXX=g++

# Include Flags
# -g is a debugging flag
CXXFLAGS = -Isrc/Include -g


# Swap between Windows and Unix installs
ifeq ($(OS),Windows_NT)
    RM = del /Q
	LDFLAGS= -Lsrc/lib
	LIB_LIST = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
else
    RM = rm -f
	LDFLAGS= -Lusr/include
	LIB_LIST = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
endif



all: TheOne
TheOne: main.o Application.o Player.o Enemy.o Physics.o Terrain.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o Application.o Player.o Enemy.o Physics.o Terrain.o -o TheOne  $(LIB_LIST)
Application.o: Application.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c Application.cpp $(LIB_LIST)
main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c main.cpp $(LIB_LIST)
Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c Player.cpp $(LIB_LIST)
Enemy.o: Enemy.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c Enemy.cpp $(LIB_LIST)
Physics.o: Physics.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c Physics.cpp $(LIB_LIST)
Terrain.o: Terrain.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c Terrain.cpp $(LIB_LIST)

# Swap between Windows and Unix installs
ifeq ($(OS),Windows_NT)
    RM = del /Q
else
    RM = rm -f
endif

clean:
	$(RM) *.o
