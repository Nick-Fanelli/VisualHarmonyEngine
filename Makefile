Game = Game
HarmonyEngine = HarmonyEngine

ASSETS_DIR = $(HarmonyEngine)/assets

SRC_FILES = $(HarmonyEngine)/src/*.cpp $(HarmonyEngine)/src/*/*.cpp
OBJ_FILES = $(HarmonyEngine)/bin/*.o $(HarmonyEngine)/bin/*/*.o
APP_PATH = $(HarmonyEngine)/build/$(HarmonyEngine)

GAME_SRC_FILES = $(Game)/src/*.cpp $(Game)/src/*/*.cpp
GAME_OBJ_FILES = $(Game)/bin/*.o $(Game)/bin/*/*.o
GAME_APP_PATH = $(Game)/build/$(Game)

SRC = $(wildcard $(SRC_FILES))
OBJ = $(subst $(HarmonyEngine)/src, $(HarmonyEngine)/bin, $(SRC:.cpp=.o))

GAME_SRC = $(wildcard $(GAME_SRC_FILES))
GAME_OBJ = $(subst $(Game)/src, $(Game)/bin, $(SRC:.cpp=.o))

CC = g++
RM = rm
CP = cp

# TODO: Add the Windows Location
# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++14

ifeq ($(DEBUG),yes)
	COMPILER_FLAGS += -g
endif

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -lglfw  -lGLEW -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

$(HarmonyEngine)/bin/%.o: $(HarmonyEngine)/src/%.cpp
	$(CC) -o $@ -c $< $(COMPILER_FLAGS)

$(HarmonyEngine) : $(OBJ)
		$(CC) $(OBJ) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(APP_PATH);
		$(CP) -R $(ASSETS_DIR) $(HarmonyEngine)/build/
		
clean:
		$(RM) -rf $(OBJ_FILES)
		$(RM) -rf $(HarmonyEngine)/src/*o
		$(RM) -rf $(HarmonyEngine)/build/assets
		$(RM) -rf $(APP_PATH)