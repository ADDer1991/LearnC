# 目标文件
TARGET = LearnC.out

# 宏定义
DEFINES = 

# 模块目录
MODULEDIR := ../common \
             ../io \
			 ../main

# 源文件
SOURCEDIR := $(addsuffix /src,$(MODULEDIR))
SOURCES := $(addsuffix /*.c,$(SOURCEDIR))
SOURCES := $(wildcard $(SOURCES))

# OBJ文件和依赖文件
OBJS := $(patsubst %.c,%.o,$(SOURCES))
OBJS := $(subst /src/,/build/,$(OBJS))

.PHONY: all clean obj

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^
	
$(OBJS):
	@for srcdir in $(SOURCEDIR); \
	do \
	make -C $$srcdir all; \
	done

clean:
	@for srcdir in $(SOURCEDIR); \
	do \
	make -C $$srcdir clean; \
	done
	rm -rf $(TARGET)

