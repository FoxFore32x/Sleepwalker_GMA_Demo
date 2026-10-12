#
# GameMaker Anywhere
# Copyright (C) 2026 Ralcactus, Rosemary Peony
#

TARGET := output/$(notdir $(CURDIR)).elf

SOURCES := \
    source \
    source/helpers \
    source/rooms \
    source/objects \
    source/gm_funcs \
    source/custom_funcs

INCLUDES := $(SOURCES)

KOS_ROMDISK_DIR := data

CFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
CPPFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))

OBJS := $(patsubst %.c,build/%.o,$(CFILES)) \
        $(patsubst %.cpp,build/%.o,$(CPPFILES)) \
        romdisk.o

INCLUDE_FLAGS := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))
INCLUDE_FLAGS += -I$(KOS_PORTS)/include/raylib

KOS_CFLAGS += $(INCLUDE_FLAGS) -Draylib -Ddc
KOS_CXXFLAGS += $(INCLUDE_FLAGS) -Draylib -Ddc

.PHONY: all clean run dist

all: $(TARGET)

include $(KOS_BASE)/Makefile.rules

$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	kos-c++ -o $@ $(OBJS) -lraylib -lGL -lm

build/%.o: %.c
	mkdir -p $(dir $@)
	kos-cc $(KOS_CFLAGS) -c $< -o $@

build/%.o: %.cpp
	mkdir -p $(dir $@)
	kos-c++ $(KOS_CXXFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -f $(TARGET) romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist: $(TARGET)
	$(KOS_STRIP) $(TARGET)