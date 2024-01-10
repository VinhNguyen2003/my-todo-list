CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iincludes

SRCDIR = src
OBJDIR = obj
SRCFILES = $(wildcard $(SRCDIR)/*.cc)
MAIN = main.cc
SOURCES = $(SRCFILES) $(MAIN)
OBJECTS = $(SRCFILES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o) $(MAIN:%.cc=$(OBJDIR)/%.o)
TARGET = todo_app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cc
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)
