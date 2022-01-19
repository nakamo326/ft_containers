NAME := exe

SHELL := /bin/bash
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -MMD -MP -std=c++98 -pedantic-errors -Wshadow
INCLUDES := -I./includes


SRCDIR := srcs
OBJDIR := objs
SRCFILE := $(shell find $(SRCDIR) -name "*.cpp" -type f)
OBJS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.o))
DEPS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.d))

# ==== Path to makefile for google test ==== #
GTESTDIR := googletest

# ==== Align length to format compile message ==== #
ALIGN := $(shell tr ' ' '\n' <<<"$(SRCFILE)" | awk -v len=0 -F "" 'NF>len{len=NF}END{print len}')

all: $(NAME)
-include $(DEPS)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ $(INCLUDES) -o $@
	@echo -e "flags  : $(YLW)$(CXXFLAGS)$(NC)\nbuild  : $(CYN)$^$(NC)\n\t=> $(BLU)$@$(NC)" 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(*D)
	@$(CXX) $(CXXFLAGS) -c $< $(INCLUDES) -o $@
	@echo -e "compile: $(MGN)$<$(NC)\
	$$(yes ' ' | head -n $$(expr $(ALIGN) - $$((`echo $< | wc -m` - 1))) | tr -d '\n') -> \
	$(CYN)$@$(NC)"

debug: CXXFLAGS += -g -fsanitize=integer -fsanitize=address -DDEBUG
debug: re

test: $(OBJS)
	$(MAKE) -C $(GTESTDIR)

.PHONY: ref
ref:
	cd ref && ./make_ref.sh

clean:
	$(RM) $(OBJS) $(DEPS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re debug test

# ==== Color define ==== #
YLW := \e[33m
GRN := \e[32m
YLW := \e[33m
BLU := \e[34m
MGN := \e[35m
CYN := \e[36m
NC := \e[m