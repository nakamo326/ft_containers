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
	@printf "build  : \e[32m%s\e[m\n  => \e[34m%s\e[m\n" "$^" $@

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
