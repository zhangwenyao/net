
TARGET		= net.exe

export ROOT_DIR	= $(shell pwd)
export ROOT_OBJ	= $(ROOT_DIR)/obj
DIR_BIN		= $(ROOT_DIR)/bin
DIR_INC		= $(ROOT_DIR)/include
BIN_TARGET	= $(DIR_BIN)/$(TARGET)

CUR_DIR		= $(shell pwd)
CUR_OBJ_DIR	= $(subst $(ROOT_DIR),$(ROOT_OBJ),$(CUR_DIR))

SUB_DIRS	= $(ROOT_DIR)/src

$(shell mkdir -p $(ROOT_OBJ))
$(shell mkdir -p $(CUR_OBJ_DIR))
$(shell mkdir -p $(DIR_BIN))

export EXTS_HC	= .h
export EXTS_C	= .c
CUR_SOURCE_C	= $(wildcard $(addprefix $(CUR_DIR)/*,$(EXTS_C)))
CUR_OBJS_C	= $(foreach x,$(EXTS_C),$(patsubst %$(x),$(CUR_OBJ_DIR)/%.o,$(filter %$(x),$(notdir $(CUR_SOURCE_C)))))
CUR_DEPS_C	= $(CUR_OBJS_C:%.o=%.d)

export EXTS_HCC	= .hpp
export EXTS_CC	= .cc .cpp
CUR_SOURCE_CC	= $(wildcard $(addprefix $(CUR_DIR)/*,$(EXTS_CC)))
CUR_OBJS_CC	= $(foreach x,$(EXTS_CC),$(patsubst %$(x),$(CUR_OBJ_DIR)/%.o,$(filter %$(x),$(notdir $(CUR_SOURCE_CC)))))
CUR_DEPS_CC	= $(CUR_OBJS_CC:%.o=%.d)


#export CC	= clang
#export CXX	= clang++
export CC	= icc
export CXX	= icpc
ifdef DEBUG
	export CFLAGS	= -Wall -O0 -I$(DIR_INC) -g -DDEBUG
	export CXXFLAGS	= -Wall -O0 -I$(DIR_INC) -g -DDEBUG -std=c++11
	export LDFLAGS	= -Wall -O0 -g -DDEBUG
else
	export CFLAGS	= -Wall -O3 -I$(DIR_INC)
	export CXXFLAGS	= -Wall -O3 -I$(DIR_INC) -std=c++11
	export LDFLAGS	= -Wall -O3
endif


.PHONY: all subdirs clean cleanall rebuild run rebuildrun debug debugrebuild debugrun debugrebuildrun

all:		$(CUR_OBJ_DIR) $(CUR_OBJS_C) $(CUR_OBJS_CC) subdirs $(BIN_TARGET)

subdirs:
	@for subdir in $(SUB_DIRS) ; do make -C $$subdir ; done

clean:
	rm -rf $(shell find $(ROOT_OBJ) -name "*.o")
	rm -rf $(shell find $(ROOT_OBJ) -name "*.d")

cleanall:	clean
	-rm -rf $(BIN_TARGET)

rebuild:	cleanall all

run:
	-reset && make all && $(BIN_TARGET)

rebuildrun:	cleanall run

debug:
	make DEBUG=1 all

debugrebuild:	cleanall debug

debugrun:
	-reset && make debug && $(BIN_TARGET)

debugrebuildrun:	cleanall debugrun

$(CUR_OBJ_DIR)/%.d:	$(CUR_DIR)/%.c
	@set -e; $(CC)  -MM $< $(CFLAGS) | sed 's,\($*\)\.o[ :]*,$(CUR_OBJ_DIR)/\1.o $@ : ,g' > $@

$(CUR_OBJ_DIR)/%.o:	$(CUR_DIR)/%.c
	$(CC)  -o $@ -c $< $(CFLAGS)

$(CUR_OBJ_DIR)/%.d:	$(CUR_DIR)/%.cc
	@set -e; $(CXX) -MM $< $(CXXFLAGS)| sed 's,\($*\)\.o[ :]*,$(CUR_OBJ_DIR)/\1.o $@ : ,g' > $@

$(CUR_OBJ_DIR)/%.o:	$(CUR_DIR)/%.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(CUR_OBJ_DIR)/%.d:	$(CUR_DIR)/%.cpp
	@set -e; $(CXX) -MM $< $(CXXFLAGS)| sed 's,\($*\)\.o[ :]*,$(CUR_OBJ_DIR)/\1.o $@ : ,g' > $@

$(CUR_OBJ_DIR)/%.o:	$(CUR_DIR)/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(BIN_TARGET):		$(shell find $(ROOT_OBJ) -name "*.o")
	$(CXX) -o $@ $(LDFLAGS) $(shell find $(ROOT_OBJ) -name "*.o")


-include $(CUR_DEPS_C)
-include $(CUR_DEPS_CC)

