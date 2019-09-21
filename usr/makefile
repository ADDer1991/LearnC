# 目标文件
TARGET = LearnC.out

# 宏定义
DEFINES = 

# 模块目录
MODULEDIR := ../common \
             ../io \
			 ../unittest \
			 ../main

# 头文件路径
INCLUDEDIRS := ../../common/inc \
              ../../io/inc \
              ../../main/inc \
			  ../../unittest/inc

export INCLUDEDIRS

# 源文件
SOURCEDIR := $(addsuffix /src,$(MODULEDIR))
SOURCES := $(addsuffix /*.c,$(SOURCEDIR))
SOURCES := $(wildcard $(SOURCES))

# OBJ文件和依赖文件
OBJS := $(patsubst %.c,%.o,$(SOURCES))
OBJS := $(subst /src/,/build/,$(OBJS))

.PHONY: all clean

all:
	@for srcdir in $(SOURCEDIR); \
	do \
	make -C $$srcdir all; \
	done
	$(CC) -o $(TARGET) $(OBJS)

clean:
	@for srcdir in $(SOURCEDIR); \
	do \
	make -C $$srcdir clean; \
	done
	rm -rf $(TARGET)

