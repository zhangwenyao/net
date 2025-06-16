
CUR_DIR		= $(shell pwd)
CUR_OBJ_DIR	= $(subst $(ROOT_DIR),$(ROOT_OBJ),$(CUR_DIR))

SUB_DIRS	= $(foreach x,$(shell ls -l | grep ^d | awk '{print $$9}'),"$(CUR_DIR)/$(x)")

$(shell mkdir -p $(CUR_OBJ_DIR))

CUR_SOURCE_C	= $(wildcard $(addprefix $(CUR_DIR)/*,$(EXTS_C)))
CUR_OBJS_C	= $(foreach x,$(EXTS_C),$(patsubst %$(x),$(CUR_OBJ_DIR)/%.o,$(filter %$(x),$(notdir $(CUR_SOURCE_C)))))
CUR_DEPS_C	= $(CUR_OBJS_C:%.o=%.d)

CUR_SOURCE_CC	= $(wildcard $(addprefix $(CUR_DIR)/*,$(EXTS_CC)))
CUR_OBJS_CC	= $(foreach x,$(EXTS_CC),$(patsubst %$(x),$(CUR_OBJ_DIR)/%.o,$(filter %$(x),$(notdir $(CUR_SOURCE_CC)))))
CUR_DEPS_CC	= $(CUR_OBJS_CC:%.o=%.d)


.PHONY: all subdirs

all:			$(CUR_OBJ_DIR) $(CUR_DEPS_C) $(CUR_OBJS_C) $(CUR_DEPS_CC) $(CUR_OBJS_CC) subdirs

subdirs:
	@for subdir in $(SUB_DIRS) ; do make -C $$subdir ; done


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

