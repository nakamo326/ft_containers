NAME := tester

SHELL := /bin/bash
CXX := clang++
CXXFLAGS = -std=c++11 -MMD -MP -DDEBUG -g -fsanitize=integer -fsanitize=address
LIBS := -lpthread
INCLUDES := -I. -I../includes

# ==== Enter latest release URL ==== #
GTEST_URL := https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
GTEST_RELEASE := googletest-$(basename $(basename $(notdir $(GTEST_URL))))

SRCDIR := ../srcs
OBJDIR := ../objs
SRCFILE := $(shell find $(SRCDIR) -name "*.cpp" -type f)
# === object file of "all" source file, DON'T USE this directly. === #
OBJS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.o))
DEPS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.d))

# === source dir for each target binary. these dir is child of $(SRCDIR) === #
T_SRCDIR := tests
T_OBJS = $(filter $(OBJDIR)/$(T_SRCDIR)/%.o,$(OBJS))
T_DEPS = $(filter $(OBJDIR)/$(T_SRCDIR)/%.d,$(OBJS))

GTSRCDIR := gtest
GTOBJDIR := gobjs
.SECONDARY: $(GTESTSRC)
GTESTSRC := $(GTSRCDIR)/gtest-all.cc $(GTSRCDIR)/gtest_main.cc
GTOBJS   := $(patsubst $(GTSRCDIR)%,$(GTOBJDIR)%,$(GTESTSRC:.cc=.o))
GTDEPS   := $(patsubst $(GTSRCDIR)%,$(GTOBJDIR)%,$(GTESTSRC:.cc=.d))


all: $(NAME)
-include $(DEPS) $(TDEPS) $(GTDEPS)

$(NAME): $(GTOBJS) $(T_OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $@
	./$@ || :
	$(RM) $@

$(GTOBJDIR)/%.o: $(GTSRCDIR)/%.cc
	@mkdir -p $(GTOBJDIR)
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDES) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(*D)
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
	$(RM) $(T_OBJS) $(T_DEPS)
	$(RM) -r $(OBJDIR)/$(T_SRCDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re