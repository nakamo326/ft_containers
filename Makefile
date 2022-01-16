NAME := exe

CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -MMD -MP -std=c++98 -pedantic-errors -Wshadow
INCLUDES := -I./includes

SRCFILE := $(shell find srcs -type f)

SRCDIR := srcs
OBJDIR := objs
OBJS = $(subst $(SRCDIR), $(OBJDIR), $(SRCFILE:.cpp=.o))
DEPS = $(subst $(SRCDIR), $(OBJDIR), $(SRCFILE:.cpp=.d))

ALIGN := $(shell echo $(SRCFILE) | tr ' ' '\n' | while read line; do echo \
	$$((`echo $$line | wc -m` - 1)); done | awk '{if(m<$$1) m=$$1} END{print m}')

all: $(NAME)
-include $(DEPS)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ $(INCLUDES) -o $@
	@printf "flags  : \e[33m%s\e[m\n" "$(CXXFLAGS)"
	@printf "compile: \e[32m%s\e[m\n  => \e[34m%s\e[m\n" "$^" $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(*D)
	@$(CXX) $(CXXFLAGS) -c $< $(INCLUDES) -o $@
	@printf "compile: \e[35m%s\e[m%s -> \e[32m%s\e[m\n" $^ \
	"$$(yes ' ' | head -n $$(expr $(ALIGN) - $$((`echo $^ | wc -m` - 1))) | tr -d '\n')" $@

clean:
	$(RM) $(OBJS) $(DEPS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.PHONY: debug
debug: CXXFLAGS += -g -fsanitize=integer -fsanitize=address -DDEBUG
debug: re

# ---- Google Test ---- #
GTESTDIR := googletest
gtest := $(GTESTDIR)/gtest $(GTESTDIR)/googletest-release-1.11.0
TESTDIR := .
TESTSRC := $(shell find tests -type f)

PYTHON = $(shell which python)
ifeq ($(shell which python),)
PYTHON = $(shell which python3)
endif

$(gtest):
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -xvzf release-1.11.0.tar.gz googletest-release-1.11.0
	$(RM) -f release-1.11.0.tar.gz
	$(PYTHON) googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(GTESTDIR)
	mv googletest-release-1.11.0 $(GTESTDIR)

# -lpthreadいるか確認
.PHONY: test
test: $(gtest) 
	clang++ -std=c++11 $(TESTDIR)/gtest.cpp $(GTESTDIR)/gtest/gtest-all.cc \
	$(GTESTDIR)/googletest-release-1.11.0/googletest/src/gtest_main.cc \
	$(TESTSRC) -DDEBUG -g -fsanitize=integer -fsanitize=address \
	-I$(GTESTDIR) -I$(INCLUDES) -lpthread -o tester
	./tester
	$(RM) tester