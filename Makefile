PATH_SRC    := src
PATH_LIB    := lib
PATH_BUILD  := build
PATH_BIN    := $(PATH_BUILD)/bin
PATH_OBJ    := $(PATH_BUILD)/obj
PATH_DEP    := $(PATH_OBJ)/__dep__
PATH_OUTPUT := output

include common_vars.mk

LDFLAGS  += -L $(PATH_LIB)/libSDL
LDLIBS   += -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf
CPPFLAGS += -I include

OUT_EXE := doodle_jump.exe

#----------------------------------------

VPATH = $(PATH_SRC)

FILES   = $(patsubst src/%, %, $(shell find $(PATH_SRC) -name "*.cpp" -type f))
FOLDERS = $(patsubst src/%, %, $(shell find $(PATH_SRC) -mindepth 1 -type d))

FILES_DEP = $(patsubst %, $(PATH_DEP)/%.d, $(basename $(FILES)))
FILES_OBJ = $(patsubst %, $(PATH_OBJ)/%.o, $(basename $(FILES)))

#----------------------------------------

all: $(PATH_BIN)/$(OUT_EXE)

$(PATH_BIN)/$(OUT_EXE): $(FILES_OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(COPY) $@ $(PATH_OUTPUT) > $(NULL_DEVICE)

DEPFLAGS    = -MT $@ -MMD -MP -MF $(PATH_DEP)/$*.dTMP
POSTCOMPILE = @$(MOVE) $(PATH_DEP)/$*.dTMP $(PATH_DEP)/$*.d > $(NULL_DEVICE) && touch $@

$(PATH_OBJ)/%.o: %.cpp
$(PATH_OBJ)/%.o: %.cpp $(PATH_DEP)/%.d | directories
	$(CC) $(CPPFLAGS) -c $(DEPFLAGS) $< -o $@
	$(POSTCOMPILE)

.PRECIOUS: $(FILES_DEP)
$(FILES_DEP): ;
-include $(FILES_DEP)

#----------------------------------------

directories: $(PATH_BUILD) $(PATH_BIN) $(PATH_OBJ) $(PATH_DEP) nested-folders
nested-folders: $(addprefix $(PATH_OBJ)/, $(FOLDERS)) $(addprefix $(PATH_DEP)/, $(FOLDERS))

$(PATH_BUILD): ; $(MKDIR) $@
$(PATH_BIN): ; $(MKDIR) $@
$(PATH_OBJ): ; $(MKDIR) $@
$(PATH_DEP): ; $(MKDIR) $@

$(addprefix $(PATH_OBJ)/, $(FOLDERS)): ; @$(MKDIR) $@
$(addprefix $(PATH_DEP)/, $(FOLDERS)): ; @$(MKDIR) $@

#----------------------------------------

.PHONY: all directories nested-folders \
		clean clean-obj clean-dep clean-exe delete-build \
		run help

clean: clean-obj clean-dep clean-exe
clean-obj: ; $(RMDIR) $(PATH_OBJ)/*
clean-dep: ; $(RMDIR) $(PATH_DEP)/*
clean-exe: ; $(RM) $(PATH_BIN)/$(OUT_EXE)
delete-build: ; $(RMDIR) $(PATH_BUILD)

ARGS ?=
run: ; @cd $(PATH_OUTPUT) && ./$(OUT_EXE) $(ARGS)

help:
	@echo Targets: all clean clean-obj clean-dep clean-exe delete-build run
	@echo '(make run ARGS="arg1 arg2...")'
