#常用编译选项、引用库、命令等在此统一定义
#引入本文件前需要设置：BASEDIR、TARGET、SOURCE
#BASEDIR是代码根目录
#TARGET是生成的文件名
#SOURCE是代码源文件的类型，默认是c
COMPILE_DEBUG = 1
CXX := gcc
AR := ar

ifeq ($(SOURCE),)
SOURCE := c
endif

ifeq ($(COMPILE_DEBUG), 1)
CXXFLAGS += -std=c99 -Wall -O0 -g
else
CXXFLAGS += -std=c99 -Wall -O2
endif 

LDFLAGS +=

DEFINES += 

INCLUDE +=

LIBARAY +=

SOURCE_PATH := $(shell pwd)
BUILD_PATH := build

SOURCES := $(patsubst ./%.$(SOURCE), %.$(SOURCE), $(foreach dir, $(shell find -maxdepth 3 -type d), $(wildcard $(dir)/*.$(SOURCE))))
OBJECTS := $(patsubst %.$(SOURCE), $(BUILD_PATH)/%.o, $(SOURCES))
DEPENDS := $(patsubst %.o, %.d, $(OBJECTS))

TARGET_OBJECTS := $(filter-out %unittest.o, $(OBJECTS))
# UNITTEST_OBJECTS := $(filter-out %main.o, $(OBJECTS))

target: $(TARGET)

# unittest: $(UNITTEST_OBJECTS)

# -include $(DEPENDS)

test:
	echo $(SOURCES) $(OBJECTS)

$(TARGET) : $(TARGET_OBJECTS)
ifneq ($(findstring .a, $(TARGET)),)
	$(AR) crv $@ $^
else
ifneq ($(findstring .so, $(TARGET)),)
	$(CXX) $(CXXFLAGS) -shared -fPIC $^ $(LIBARAY) $(LDFLAGS) -o $@
else
	$(CXX) $(CXXFLAGS) $^ $(LIBARAY) $(LDFLAGS) -o $@
endif
endif

$(TARGET_UNITTEST) : $(UNITTEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LIBARAY) $(LDFLAGS) -o $@

$(BUILD_PATH)/%.o :$(SOURCE_PATH)/%.$(SOURCE)
	@mkdir -p $(dir $(OBJECTS))
	@$(CXX) $(INCLUDE) $(CXXFLAGS) -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<
	$(CXX) $(DEFINES) $(INCLUDE) $(CXXFLAGS) -o $@ -c $<


clean:
	rm -f $(TARGET) $(TARGET_UNITTEST)
	rm -f $(OBJECTS) *.o *.d
	rm -rf $(BUILD_PATH)