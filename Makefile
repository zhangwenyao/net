
TARGET		= net.exe

export ROOT_DIR	= $(shell pwd)
export ROOT_OBJ	= $(ROOT_DIR)/obj
DIR_BIN		= $(ROOT_DIR)/bin
DIR_INC		= $(ROOT_DIR)/include
BIN_TARGET	= $(DIR_BIN)/$(TARGET)
datecmd		= date +%Y%m%d-%T.%3N

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

#export CC	= gcc
#export CXX	= g++
# export CC	= gcc-11
# export CXX	= g++-11
export CC	= clang
export CXX	= clang++
#export CC	= icc
#export CXX	= icpc

USER_DEFINES	=
# ifdef DEBUG
#	export CFLAGS	= ${USER_DEFINES} -Wall -O0 -I$(DIR_INC) -g -fopenmp -DDEBUG
#	export CXXFLAGS	= ${USER_DEFINES} -Wall -O0 -I$(DIR_INC) -g -fopenmp -DDEBUG -std=c++11
#	export LDFLAGS	= -Wall -O0 -g -DDEBUG -fopenmp
# else
#	export CFLAGS	= ${USER_DEFINES} -Wall -O3 -I$(DIR_INC) -fopenmp
#	export CXXFLAGS	= ${USER_DEFINES} -Wall -O3 -I$(DIR_INC) -fopenmp -std=c++11
#	export LDFLAGS	= -Wall -O3 -fopenmp
# endif
ifdef DEBUG
	export CFLAGS	= ${USER_DEFINES} -Wall -O0 -I$(DIR_INC) -g -DDEBUG
	export CXXFLAGS	= ${USER_DEFINES} -Wall -O0 -I$(DIR_INC) -g -DDEBUG -std=c++11
	export LDFLAGS	= -Wall -O0 -g -DDEBUG
else
	export CFLAGS	= ${USER_DEFINES} -Wall -O3 -I$(DIR_INC)
	export CXXFLAGS	= ${USER_DEFINES} -Wall -O3 -I$(DIR_INC) -std=c++11
	export LDFLAGS	= -Wall -O3
endif


.PHONY: all subdirs execute executea run logrun clean cleanall rebuild rebuildrun debug debugrun logdebugrun debugrebuild debugrebuildrun

all:		$(CUR_OBJ_DIR) $(CUR_OBJS_C) $(CUR_OBJS_CC) subdirs $(BIN_TARGET)
ifneq ($(USER_DEFINES),)
	@echo "USER_DEFINES=${USER_DEFINES}"
endif

subdirs:
	@for subdir in $(SUB_DIRS) ; do make -C $$subdir ; done

execute:
	@${datecmd}
	$(BIN_TARGET)
ifneq ($(USER_DEFINES),)
	@echo "USER_DEFINES=${USER_DEFINES}"
endif
	@${datecmd}

logexecute:
	@${datecmd}
	$(ROOT_DIR)/script/logrun.sh $(BIN_TARGET)
ifneq ($(USER_DEFINES),)
	@echo "USER_DEFINES=${USER_DEFINES}"
endif
	@${datecmd}

run:	all execute

logrun:	all logexecute

clean:
	rm -rf $(shell find $(ROOT_OBJ) -name "*.o")
	rm -rf $(shell find $(ROOT_OBJ) -name "*.d")

cleanall:	clean
	rm -rf $(BIN_TARGET)

rebuild:	cleanall all

rebuildrun:	cleanall run

debug:
	make DEBUG=1 all

debugrun:	debug run

logdebugrun:	debug logrun

debugrebuild:	cleanall debug

debugrebuildrun:	cleanall debugrun


$(CUR_OBJ_DIR)/%.d:	$(CUR_DIR)/%.c
	@set -e; $(CC) $(CFLAGS) -MM $< | sed 's,\($*\)\.o[ :]*,$(CUR_OBJ_DIR)/\1.o $@ : ,g' > $@

$(CUR_OBJ_DIR)/%.o:	$(CUR_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(CUR_OBJ_DIR)/%.d:	$(CUR_DIR)/%.cc
	@set -e; $(CXX) $(CXXFLAGS) -MM $< | sed 's,\($*\)\.o[ :]*,$(CUR_OBJ_DIR)/\1.o $@ : ,g' > $@

$(CUR_OBJ_DIR)/%.o:	$(CUR_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(CUR_OBJ_DIR)/%.d:	$(CUR_DIR)/%.cpp
	@set -e; $(CXX) $(CXXFLAGS) -MM $< | sed 's,\($*\)\.o[ :]*,$(CUR_OBJ_DIR)/\1.o $@ : ,g' > $@

$(CUR_OBJ_DIR)/%.o:	$(CUR_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BIN_TARGET):		$(shell find $(ROOT_OBJ) -name "*.o")
	$(CXX) $(LDFLAGS) -o $@ $(shell find $(ROOT_OBJ) -name "*.o")


-include $(CUR_DEPS_C)
-include $(CUR_DEPS_CC)

