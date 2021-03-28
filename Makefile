BASEDIR = ./
TARGET := run
INCLUDE += -I./include
LDFLAGS +=  -ldl -L./lib -lrestart -lm
CXXFLAGS += -rdynamic -Wl,-export-dynamic
include $(BASEDIR)/buildenv.mk