########################################################
# 通用编译生成.obj文件模板，需要被makefile文件include
# 标签：all           -  编译所有obj
#       clean         -  清除所有.o .d文件
# 输出：../build/*.o  ../build/*.d
########################################################

INCLUDEDIRS := $(addprefix -I,$(INCLUDEDIRS))

# 源文件
SOURCES = $(wildcard *.c)

# obj文件和依赖文件
OBJDIR := ../build
$(shell mkdir $(OBJDIR) -p)
OBJS := $(patsubst %.c, %.o, $(SOURCES))
OBJS := $(addprefix $(OBJDIR)/, $(OBJS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

# 编译选项
CC = gcc
CFLAGS = -c -g -Wall -MMD

.PHONY: all clean

all: $(OBJS)

-include $(DEPS)

$(OBJDIR)/%.o: %.c
	@echo Compiling $< ...
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $(DEFINES) $< -o $@

clean:
	rm -rf $(OBJDIR)
