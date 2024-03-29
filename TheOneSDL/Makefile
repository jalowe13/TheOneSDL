# Makefile for The One
#Copyright (C) [2024] [Jacob Lowe]
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>



CXX=g++


EXE = TheOne
IMGUI_DIR = ./imgui
# VCPKG Source using the current user profile
MSYS2_ROOT := C:/msys32
MSYS2_TARGET_TRIPLET := mingw64

#Icon
# Application Icon
ICON = icon.ico
# Resource Script
RC = icon.rc
# Icon Object
RES = icon.o

# Im GUI Compilation
SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp $(IMGUI_DIR)/backends/imgui_impl_sdlrenderer2.cpp
# Game Compilation
SOURCES += Application.cpp Entity.cpp Player.cpp Enemy.cpp Physics.cpp Terrain.cpp EntityManager.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))


# Swap between Windows and Unix installs
ifeq ($(OS),Windows_NT)
    RM = del /Q
	ECHO_MESSAGE = "MinGW"
	CXXFLAGS = -std=c++14 -I$(MSYS2_ROOT)/$(MSYS2_TARGET_TRIPLET)/include  -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
	LDFLAGS := -L$(MSYS2_ROOT)/$(MSYS2_TARGET_TRIPLET)/lib 
	CXXFLAGS += -g -Wall -Wformat
	LIB_LIST = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -ljsoncpp -static-libgcc -static-libstdc++ -lgdi32 -lopengl32 -limm32
else
    RM = rm -f
	LDFLAGS= -Lusr/include
	CXXFLAGS = -std=c++14 -I$(MSYS2_ROOT)/$(MSYS2_TARGET_TRIPLET)/include  -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
	LDFLAGS := -L$(MSYS2_ROOT)/$(MSYS2_TARGET_TRIPLET)/lib
	CXXFLAGS += -g -Wall -Wformat
	LIB_LIST = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -ljsoncpp
endif

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ifeq ($(OS),Windows_NT)
$(RES): $(RC)
	windres -O coff -i $(RC) -o $(RES)
all: $(EXE)
	@echo Build complete for Windows $(ECHO_MESSAGE)
$(EXE): $(OBJS) $(RES)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIB_LIST)
else
all: $(EXE)
	@echo Build complete for Linux $(ECHO_MESSAGE)
$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIB_LIST)
endif

# Swap between Windows and Unix installs
ifeq ($(OS),Windows_NT)
    RM = del /Q
else
    RM = rm -f
endif

# Clean all object files
cleanall:
	$(RM) $(filter-out imgui.o imgui_widgets.o imgui_tables.o imgui_impl_sdlrenderer2.o imgui_impl_sdl2.o imgui_draw.o imgui_demo.o, $(wildcard *.o))

# Clean specific object file, used more if a header file is edited and not detected as a change
clean:
	$(RM) $(filter-out $@,$(MAKECMDGOALS:%=%.o))
