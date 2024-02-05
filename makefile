# Makefile by S739_Lucie - January 16th 2024
# ====== Everything Command Calls related ======

MAKEFLAGS += --no-print-directory
RM += -r

# ========= Everything project related =========

PROJ    := libLuEngineCPP
TARGET  := $(PROJ).a
COMP    := g++
LINK    := ar -rcs

STATIC_PATH := errorLib

ifdef OS
	STATIC_PATH := C:/CustomLibs
else ifeq ($(shell uname), Linux)
	STATIC_PATH := /usr/local
endif

STATIC_LIB_PATH := $(STATIC_PATH)/lib
STATIC_H_PATH   := $(STATIC_PATH)/include/LuEngineCPP

# ========== Everything files related ==========

INC_DIR   := include
SRC_DIR   := src
OBJ_DIR   := objs

HDS_FILES := $(wildcard $(INC_DIR)/*.hpp) $(wildcard $(INC_DIR)/**/*.hpp)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.d)

# ========== Everything flags related ==========

O_FLAGS := -I include -O3 -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -Wno-missing-field-initializers

ifdef OS
	O_FLAGS += -I C:/CustomLibs/include
endif

# =========== Every usable functions ===========

# Basic Build

all:
	@$(MAKE) --silent build

install:
	@$(MAKE) --silent build

ifdef OS
	@mkdir -p $(STATIC_LIB_PATH)
	@echo Installing $(TARGET) at C:/CustomLibs/lib/
	@cp --update $(TARGET) $(STATIC_LIB_PATH)/$(TARGET)

	@mkdir -p $(STATIC_H_PATH)/
	@echo Installing the headers at $(STATIC_H_PATH)/
	@echo Installing LuEngine.hpp
	@cp --update LuEngine.hpp $(STATIC_PATH)/include/LuEngine.hpp
	@$(MAKE) --silent installHeaders

else ifeq ($(shell uname), Linux)
	@mkdir -p $(STATIC_LIB_PATH)
	@echo Installing $(TARGET) at /usr/local/lib/
	@cp --update $(TARGET) $(STATIC_LIB_PATH)/$(TARGET)

	@mkdir -p $(STATIC_H_PATH)/
	@echo Installing the headers at $(STATIC_H_PATH)/
	@cp --update LuEngine.hpp $(STATIC_PATH)/include/LuEngine.hpp
	@$(MAKE) --silent installHeaders

else
	@echo Can't automatically install this lib on your system
endif

installHeaders: $(HDS_FILES:$(INC_DIR)/%.hpp=$(STATIC_H_PATH)/%.hpp)
$(STATIC_H_PATH)/%.hpp: $(INC_DIR)/%.hpp
	@echo installing $(notdir $(basename $@))
	@cp --update $< $@

libHeader: 
	@$(RM) LuEngine.hpp
	@touch LuEngine.hpp
	@echo "#ifndef LU_ENGINE_HPP" >> LuEngine.hpp
	@echo "#define LU_ENGINE_HPP" >> LuEngine.hpp
	@echo "" >> LuEngine.hpp
	@./createLibHeader.sh
	@echo "" >> LuEngine.hpp
	@echo "#endif  // LU_ENGINE_HPP" >> LuEngine.hpp

build: $(TARGET) 
	@$(MAKE) --silent libHeader

$(TARGET): $(OBJ_FILES)
	@echo Linking the static library
	@$(LINK) $@ $^

# Obj and Header files compiling

objects: $(OBJ_FILES)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Compiling $(notdir $(basename $@))
	@mkdir -p $(dir $@)
	@$(COMP) -c $< -o $@ $(O_FLAGS)

# File Cleaners

cleanAll:
	@$(MAKE) clean
	$(RM) $(PROJ).a
	$(RM) $(PROJ).lib
	$(RM) $(PROJ)_debug.a
	$(RM) $(PROJ)_debug.lib
	$(RM) LuEngine.hpp
	$(CLS)

clean: 
	$(RM) $(OBJ_DIR)

cleanInstall:
	$(RM) $(STATIC_LIB_PATH)/$(TARGET)
	$(RM) $(STATIC_H_PATH)
	$(RM) $(STATIC_PATH)/include/LuEngine.hpp

# Makefile Debugging/Usefull Functions

rebuild:
	@$(MAKE) --silent cleanAll
	@$(MAKE) --silent build

reinstall:
	@$(MAKE) --silent cleanAll
	@$(MAKE) --silent cleanInstall
	@$(MAKE) --silent install

# Makefile Debugging/Usefull Functions
showOS: 
ifdef OS
	@echo Windows
else ifeq ($(shell uname), Linux)
	@echo Linux
else
	@echo ERROR
endif

showFiles:
	@echo Header files
	@echo $(HDS_FILES)
	@echo 
	@echo Source files
	@echo $(SRC_FILES)
	@echo 
	@echo Object files
	@echo $(OBJ_FILES)
	@echo 
	@echo Dep files
	@echo $(DEP_FILES)
	@echo 
	@echo Install paths
	@echo "lib path     :" $(STATIC_LIB_PATH)
	@echo "headers path :" $(STATIC_H_PATH)
