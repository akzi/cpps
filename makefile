#添加规则

release = true

include Rules.mk

#引用头文件路径
INC_DIRS += -I./cpps/
SRC_FILES += $(wildcard ./cpps/*.c*)

#宏定义修改
MACROS += -DREDIS_EXPORT
libpath = ./$(BIN_DIR)

GEN_EXE = ./$(BIN_DIR)/libcpps


$(shell mkdir -p $(OBJ_DIR)/cpps)

.PHONY: all

all: $(OBJ_FILES)
	$(CPP) $(CPPFLAGS) $(PIC) $(INC_DIRS) $(GEN_OBJS) $(LIB_DIRS) $(LNK_LIBS) -o $(GEN_EXE)

#工程生成文件清理	
clean: force
	$(RM) $(PCH)
	$(RM) $(OUT_DIR)

force:
