NAME := exe

SHELL := /bin/bash
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -MMD -MP -std=c++98 -pedantic-errors -Wshadow

INCLUDES := -I./includes

SRCFILE := $(shell find srcs -type f)

SRCDIR := srcs
OBJDIR := objs
OBJS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.o))
DEPS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.d))

YLW := \e[33m
GRN := \e[32m
YLW := \e[33m
BLU := \e[34m
MGN := \e[35m
CYN := \e[36m
NC := \e[m

ALIGN := $(shell tr ' ' '\n' <<<"$(SRCFILE)" | awk -v len=0 -F "" 'NF>len{len=NF}END{print len}')

all: $(NAME)
-include $(DEPS)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ $(INCLUDES) -o $@
	@echo -e "flags  : $(YLW)$(CXXFLAGS)$(NC)"
	@echo -e "build  : $(GRN)$^$(NC)\n\t=> $(BLU)$@$(NC)" 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(*D)
	@$(CXX) $(CXXFLAGS) -c $< $(INCLUDES) -o $@
	@echo -en "compile: $(MGN)$^$(NC)"
	@echo -en "$$(yes ' ' | head -n $$(expr $(ALIGN) - $$((`echo $^ | wc -m` - 1))) | tr -d '\n') -> "
	@echo -e "$(GRN)$@$(NC)"

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

GTESTDIR := googletest

test:
	make -C $(GTESTDIR)
