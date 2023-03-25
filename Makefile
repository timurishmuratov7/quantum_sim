CXX = g++ 
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Iinclude 
LIBS = 

SRCDIR = src
INCDIR = include
OBJDIR = obj
HEADERS = $(wildcard $(INCDIR)/*.h)

$(info $$HEADERS is [${HEADERS}])

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TARGET = run_quantum

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(info $$SRCS is [${SRCS}])

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean

clean:
	rm -f quantum_sim *.o