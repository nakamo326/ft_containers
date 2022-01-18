NAME := tester

SHELL := /bin/bash
CXX := clang++
CXXFLAGS := -std=c++11 -MMD -MP -DDEBUG -g -fsanitize=integer -fsanitize=address
LIBS := -lpthread
INCLUDES := -I. -I./includes

# ==== Enter latest release URL ==== #
GTEST_URL := https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
GTEST_RELEASE := googletest-$(basename $(basename $(notdir $(GTEST_URL))))

SRCDIR := ../srcs
OBJDIR := ../objs
MAIN_SUFFIX := main.cpp
SRCFILE := $(filter-out %$(MAIN_SUFFIX),$(shell find $(SRCDIR) -type f))
OBJS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.o))
DEPS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.d))

# ==== Path to test ==== #
TESTDIR := ../tests
TOBJDIR := tobjs
TESTS := $(wildcard $(TESTDIR)/*.cpp)
TOBJS = $(patsubst $(TESTDIR)%,$(TOBJDIR)%,$(TESTS:.cpp=.o))
TDEPS = $(patsubst $(TESTDIR)%,$(TOBJDIR)%,$(TESTS:.cpp=.d))

GTSRCDIR := gtest
GTOBJDIR := gobjs
.SECONDARY: $(GTESTSRC)
GTESTSRC := $(GTSRCDIR)/gtest-all.cc $(GTSRCDIR)/gtest_main.cc
GTOBJS   := $(patsubst $(GTSRCDIR)%,$(GTOBJDIR)%,$(GTESTSRC:.cc=.o))
GTDEPS   := $(patsubst $(GTSRCDIR)%,$(GTOBJDIR)%,$(GTESTSRC:.cc=.d))


all: $(NAME)
-include $(DEPS) $(TDEPS) $(GTDEPS)

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

$(GTESTSRC): $(GTSRCDIR)
	@:

$(GTSRCDIR): $(GTEST_RELEASE)
	python3 $(GTEST_RELEASE)/googletest/scripts/fuse_gtest_files.py .
	cp $(GTEST_RELEASE)/googletest/src/gtest_main.cc gtest/gtest_main.cc

$(GTEST_RELEASE):
	if [ ! -f $(notdir $(GTEST_URL)) ]; then curl -OL $(GTEST_URL); fi
	tar -xzf $(notdir $(GTEST_URL)) $(GTEST_RELEASE) && $(RM) $(notdir $(GTEST_URL))

clean:
	$(RM) $(TOBJS)
	$(RM) -r $(TOBJDIR)

.PHONY: all clean