MODULES = HarmonyEngine

ASSETS_DIR = $(MODULES)/assets

SRC_FILES = $(MODULES)/src/*.cpp $(MODULES)/src/*/*.cpp
OBJ_FILES = $(MODULES)/bin/*.o $(MODULES)/bin/*/*.o
APP_PATH = $(MODULES)/build/$(MODULES)

SRC = $(wildcard $(SRC_FILES))
OBJ = $(subst $(MODULES)/src, $(MODULES)/bin, $(SRC:.cpp=.o))

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
COMPILER_FLAGS = -w -std=c++11

ifeq ($(DEBUG),yes)
	COMPILER_FLAGS += -g
endif

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -lglfw  -lGLEW -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

$(MODULES)/bin/%.o: $(MODULES)/src/%.cpp
	$(CC) -o $@ -c $< $(COMPILER_FLAGS)

$(MODULES) : $(OBJ)
		$(CC) $(OBJ) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(APP_PATH);
		$(CP) -R $(ASSETS_DIR) $(MODULES)/build/

clean:
		$(RM) -rf $(OBJ_FILES)
		$(RM) -rf $(MODULES)/src/*o
		$(RM) -rf $(MODULES)/build/assets
		$(RM) -rf $(APP_PATH)