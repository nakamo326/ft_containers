NAME := tester

SHELL := /bin/bash
CXX := clang++
CXXFLAGS := -std=c++11 -DDEBUG -g -fsanitize=integer -fsanitize=address
LIBS := -lpthread
INCLUDES := -I. -I./includes

SRCDIR := ../srcs
OBJDIR := ../objs
MAIN := main.cpp
SRCFILE := $(filter-out %$(MAIN),$(shell find $(SRCDIR) -type f))
OBJS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.o))

TESTDIR := ../tests
TOBJDIR := tobjs
TESTS := $(wildcard $(TESTDIR)/*.cpp)
TOBJS = $(patsubst $(TESTDIR)%,$(TOBJDIR)%,$(TESTS:.cpp=.o))

GTSRCDIR := gtest
GTOBJDIR := gobjs
.SECONDARY: $(GTESTSRC)
GTESTSRC := $(GTSRCDIR)/gtest-all.cc $(GTSRCDIR)/gtest_main.cc
GTOBJS   := $(patsubst $(GTSRCDIR)%,$(GTOBJDIR)%,$(GTESTSRC:.cc=.o))


all: $(NAME)

$(NAME): $(OBJS) $(GTOBJS) $(TOBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $@
	./$@
	$(RM) $@

$(GTOBJDIR)/%.o: $(GTSRCDIR)/%.cc
	@mkdir -p $(GTOBJDIR)
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDES) -o $@

$(TOBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(TOBJDIR)/$(*D)
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDES) -o $@

# ==== Install Google Test ==== #
$(GTSRCDIR)/%.cc: $(GTSRCDIR)
	@:

$(GTSRCDIR): 
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -xzf release-1.11.0.tar.gz googletest-release-1.11.0
	python3 googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py .
	cp googletest-release-1.11.0/googletest/src/gtest_main.cc gtest/gtest_main.cc
	$(RM) release-1.11.0.tar.gz

clean:
	$(RM) $(TOBJS)
	$(RM) -r $(TOBJDIR)

.PHONY: all clean