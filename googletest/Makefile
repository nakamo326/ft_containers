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
TESTS := $(wildcard $(TESTDIR)/*.cpp)


GTSRCDIR := gtest
GTESTSRC = $(wildcard $(GTSRCDIR)/*.cc)
GTOBJDIR := objs
GTOBJS = $(patsubst $(GTSRCDIR)%,$(GTOBJDIR)%,$(GTESTSRC:.cc=.o))

PYTHON = $(shell which python)
ifeq ($(shell which python),)
PYTHON = $(shell which python3)
endif

all: $(NAME)

print: $(GTSRCDIR)
	@echo $(GTESTSRC)
	@echo $(GTOBJS)

$(NAME): $(GTSRCDIR) $(OBJS) $(GTOBJS)
	$(CXX) $(CXXFLAGS) \
	$(TESTS) $(filter-out $(GTSRCDIR),$^) $(INCLUDES) $(LIBS) -o $@
	./$@
	$(RM) $@

$(GTOBJDIR)/%.o: $(GTESTDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDES) -o $@

# ==== Install Google Test ==== #
$(GTSRCDIR):
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar --remove-file -xzf release-1.11.0.tar.gz googletest-release-1.11.0
	$(PYTHON) googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py .
	cp googletest-release-1.11.0/googletest/src/gtest_main.cc gtest/gtest_main.cc
