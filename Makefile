SOURCES := rf-banking.cpp rf-bankingMain.cpp
OBJDIR := build/obj
BINDIR := build/bin
TARGET := $(BINDIR)/banking
OBJECTS := $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -pedantic
DOXYGEN ?= doxygen

ifeq ($(OS),Windows_NT)
	TARGET := $(BINDIR)/banking.exe
	RM := del /Q
	MKDIR := if not exist build\obj mkdir build\obj && if not exist build\bin mkdir build\bin
	RUN := $(TARGET)
else
	RM := rm -f
	MKDIR := mkdir -p $(OBJDIR) $(BINDIR)
	RUN := ./$(TARGET)
endif

.PHONY: all build docs run clean debug

all: clean build run

build: docs
	$(MAKE) $(TARGET)

docs: Doxyfile
	$(DOXYGEN) $<

$(TARGET): $(OBJDIR) $(BINDIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJDIR):
	$(MKDIR)

$(BINDIR):
	$(MKDIR)

$(OBJDIR)/%.o: %.cpp rf-banking.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(RUN)
debug: CXXFLAGS += -g
debug: build

clean:
	$(RM) $(OBJECTS) $(TARGET)
