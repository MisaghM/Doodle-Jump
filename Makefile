PATH_SRC    := src
PATH_LIB    := lib
PATH_BUILD  := build
PATH_BIN    := $(PATH_BUILD)/bin
PATH_OBJ    := $(PATH_BUILD)/obj
PATH_DEP    := $(PATH_OBJ)/dep
PATH_OUTPUT := output

include common_vars.mk

LDFLAGS  += -L "$(PATH_LIB)"/libSDL
LDLIBS   += -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf
CPPFLAGS += -I include

OUT_EXE := doodle_jump.exe

#----------------------------------------

VPATH = $(PATH_SRC):\
		$(PATH_SRC)/RSDL:\
		$(PATH_SRC)/utils:\
		$(PATH_SRC)/scenes:\
		$(PATH_SRC)/platforms:\
		$(PATH_SRC)/enemies:\
		$(PATH_SRC)/items

FILES = main.cpp RSDL/rsdl.cpp system.cpp input_manager.cpp sequence_manager.cpp spritesheet.cpp utils/calc.cpp \
		game_object.cpp doodle.cpp button.cpp menu_ufo.cpp \
		scenes/scene.cpp scenes/menu_scene.cpp scenes/game_scene.cpp scenes/pause_scene.cpp scenes/gameover_scene.cpp \
		platforms/platform_normal.cpp platforms/platform_breakable.cpp platforms/platform_movable.cpp \
		enemies/enemy_normal.cpp \
		items/spring.cpp

FILES_OBJ = $(patsubst %, $(PATH_OBJ)/%.o, $(basename $(notdir $(FILES))))
FILES_DEP = $(patsubst %, $(PATH_DEP)/%.d, $(basename $(notdir $(FILES))))

#----------------------------------------

all: $(PATH_BIN)/$(OUT_EXE)

$(PATH_BIN)/$(OUT_EXE): $(FILES_OBJ)
	 $(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	 $(COPY) $@ $(PATH_OUTPUT) > $(NULL_DEVICE)

DEPFLAGS = -MT $@ -MMD -MP -MF $(PATH_DEP)/$*.d

$(PATH_OBJ)/%.o: %.cpp
$(PATH_OBJ)/%.o: %.cpp $(PATH_DEP)/%.d | $(PATH_BUILD) $(PATH_BIN) $(PATH_OBJ) $(PATH_DEP)
	 $(CC) $(CPPFLAGS) -c $(DEPFLAGS) $< -o $@

.PRECIOUS: $(FILES_DEP)
$(FILES_DEP): ;
-include $(FILES_DEP)

#----------------------------------------

$(PATH_BUILD): ; $(MKDIR) $@
$(PATH_BIN): ; $(MKDIR) $@
$(PATH_OBJ): ; $(MKDIR) $@
$(PATH_DEP): ; $(MKDIR) $@

.PHONY: all clean clean-obj clean-dep clean-exe delete-build run help

clean: clean-obj clean-dep clean-exe
clean-obj: ; $(RM) $(PATH_OBJ)/*.o
clean-dep: ; $(RM) $(PATH_DEP)/*.d
clean-exe: ; $(RM) $(PATH_BIN)/$(OUT_EXE)
delete-build: ; $(RMDIR) $(PATH_BUILD)

ARGS ?=
run: ; cd $(PATH_OUTPUT) && ./$(OUT_EXE) $(ARGS)

help:
	@echo Targets: all clean clean-obj clean-dep clean-exe delete-build run
	@echo (make run ARGS="arg1 arg2...")
