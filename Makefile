NAME = exe

CXX = clang++
CFLAGS = -Wall -Wextra -Werror -MMD -MP -std=c++98 -pedantic-errors -Wshadow
INCLUDES = -I./includes

SRCFILE = $(shell find srcs -type f)

SRCDIR = srcs
OBJDIR = objs
OBJS = $(subst $(SRCDIR), $(OBJDIR), $(SRCFILE:.cpp=.o))
DEPS = $(subst $(SRCDIR), $(OBJDIR), $(SRCFILE:.cpp=.d))

all: $(NAME)
-include $(DEPS)

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) $^ $(INCLUDES) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(*D)
	$(CXX) $(CFLAGS) -c $< $(INCLUDES) -o $@

clean:
	$(RM) $(OBJS) $(DEPS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

