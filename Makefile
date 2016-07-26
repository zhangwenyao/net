
TARGET	= net
SRCEXTS	= .c .cpp
DIR_INC	= ./include
DIR_SRC	= ./src
DIR_OBJ	= ./obj
DIR_BIN	= ./bin


CC	= clang
CXX	= clang++

SRC	= $(foreach d,$(DIR_SRC),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
OBJ	= $(foreach x,$(SRCEXTS),$(patsubst %$(x),${DIR_OBJ}/%.o,$(filter %$(x),$(notdir ${SRC}))))
DEP	= $(patsubst %.o,%.d,$(OBJ))
BIN_TARGET = ${DIR_BIN}/${TARGET}

ifdef DEBUG
CFLAGS	= -Wall -O0 -I${DIR_INC} -g -DDEBUG
CXXFLAGS= -Wall -O0 -I${DIR_INC} -g -DDEBUG -std=c++11
LDFLAGS	= -Wall -O0 -g -DDEBUG
else
CFLAGS	= -Wall -O3 -I${DIR_INC}
CXXFLAGS= -Wall -O3 -I${DIR_INC} -std=c++11
LDFLAGS	= -Wall -O3
endif

$(shell mkdir -p ${DIR_OBJ} 2> /dev/null)
$(shell mkdir -p ${DIR_BIN} 2> /dev/null)


.PHONY: all clean cleanall rebuild run debug redebug rundebug

all:$(BIN_TARGET)

${DIR_OBJ}/%.d	:	${DIR_SRC}/%.c
	@set -e; $(CC)  -MM $< $(CFLAGS) | sed 's,\($*\)\.o[ :]*,${DIR_OBJ}/\1.o $@ : ,g' > $@
${DIR_OBJ}/%.d	:	${DIR_SRC}/%.cpp
	@set -e; $(CXX) -MM $< $(CXXFLAGS)| sed 's,\($*\)\.o[ :]*,${DIR_OBJ}/\1.o $@ : ,g' > $@

${DIR_OBJ}/%.o	:	${DIR_SRC}/%.c
	$(CC)  -o $@ -c $< $(CFLAGS)
$(DIR_OBJ)/%.o	:	$(DIR_SRC)/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

-include $(DEP)

$(BIN_TARGET)	:	$(OBJ)
ifeq ($(strip $(SRCEXTS)), .c)	# C file
	$(CC)  -o $@ $^ $(LDFLAGS)
else				# C++ file
	$(CXX) -o $@ $^ $(LDFLAGS)
endif

clean:
	-rm -rf $(OBJ) $(DEP)
cleanall: clean
	-rm -rf $(BIN_TARGET)
	-rmdir $(DIR_OBJ) $(DIR_BIN)

rebuild: cleanall
	make all
run:
	-reset && make all && $(BIN_TARGET)

debug:
	make DEBUG=1
redebug: cleanall
	make debug
rundebug:
	-reset && make debug && $(BIN_TARGET)

