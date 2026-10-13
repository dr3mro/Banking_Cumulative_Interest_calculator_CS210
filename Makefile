TARGET := banking
SOURCES := rf-banking.cpp rf-bankingMain.cpp
OBJDIR := build/obj
OBJECTS := $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -pedantic

ifeq ($(OS),Windows_NT)
	TARGET := banking.exe
	RM := del /Q
	MKDIR := if not exist build\obj mkdir build\obj
	RUN := $(TARGET)
else
	RM := rm -f
	MKDIR := mkdir -p
	RUN := ./$(TARGET)
endif

.PHONY: all build run clean debug

all: clean build run

build: $(TARGET)

$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJDIR):
	$(MKDIR)

$(OBJDIR)/%.o: %.cpp rf-banking.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(RUN)
debug: CXXFLAGS += -g
debug: build

clean:
	$(RM) $(OBJECTS) $(TARGET)
