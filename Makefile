# Compiler related stuff...
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Project Paths
OBJ_PATH = build
SRC_PATH = src
KINEMATICS_PATH = src/kinematics

# Source files
SRCS = $(wildcard $(SRC_PATH)/*.cpp) $(wildcard $(KINEMATICS_PATH)/*.cpp)
OBJS = $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(filter-out $(KINEMATICS_PATH)/%.cpp,$(SRCS)))
OBJS += $(patsubst $(KINEMATICS_PATH)/%.cpp,$(OBJ_PATH)/kinematics/%.o,$(wildcard $(KINEMATICS_PATH)/*.cpp))

# SFML Paths/Flags
SFML_PATH = /opt/homebrew/Cellar/sfml/2.6.1
SFML_INCLUDE_PATH = $(SFML_PATH)/include
SFML_LIB_PATH = $(SFML_PATH)/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Targets
all: directories app

app: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -L$(SFML_LIB_PATH) $(SFML_LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(SFML_INCLUDE_PATH) -I$(SRC_PATH)

$(OBJ_PATH)/kinematics/%.o: $(KINEMATICS_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(SFML_INCLUDE_PATH) -I$(SRC_PATH)

directories:
	mkdir -p $(OBJ_PATH)/kinematics

clean:
	rm -rf $(OBJ_PATH) app

.PHONY: all clean directories