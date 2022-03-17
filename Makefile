NAME := exe

SHELL := /bin/bash
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -MMD -MP -Wshadow -std=c++98 -pedantic-errors
INCLUDES = -I./includes -I./$(GTESTDIR)

SRCDIR := srcs
OBJDIR := objs
SRCFILE := $(shell find $(SRCDIR) -name "*.cpp" -type f)
# === object file of "all" source file, DON'T USE this directly. === #
OBJS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.o))
DEPS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCFILE:.cpp=.d))

# === source dir for each target binary. these dirs are children of $(SRCDIR) === #
R_SRCDIR := run_src
R_OBJS = $(filter $(OBJDIR)/$(R_SRCDIR)/%.o,$(OBJS))
T_SRCDIR := tests
T_OBJS = $(filter $(OBJDIR)/$(T_SRCDIR)/%.o,$(OBJS))
B_SRCDIR := benchmark
B_OBJS = $(filter $(OBJDIR)/$(B_SRCDIR)/%.o,$(OBJS))

STDBIN = stdbin
FTBIN = ftbin

# ==== Path to makefile for google test ==== #
GTESTDIR := googletest

# ==== Align length to format compile message ==== #
#ALIGN := $(shell tr ' ' '\n' <<<"$(SRCFILE)" | awk -v len=0 -F "" 'NF>len{len=NF}END{print len}')
ALIGN := $(shell tr ' ' '\n' <<<"$(SRCFILE)" | while read line; do echo \
	$$((`echo $$line | wc -m`)); done | awk 'm<$$1{ m=$$1} END{print m}')

all: $(NAME)
-include $(DEPS)

$(NAME): $(R_OBJS)
	@$(CXX) $(CXXFLAGS) $^ $(INCLUDES) -o $@
	@echo -e "flags  : $(YLW)$(CXXFLAGS)$(NC)\nbuild  : $(GRN)$^$(NC)\n=> $(BLU)$@$(NC)" 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(*D)
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDES) -o $@
	@echo -e "compile: $(MGN)$<$(NC)\
	$$(yes ' ' | head -n $$(expr $(ALIGN) - $$((`echo $< | wc -m` - 1))) | tr -d '\n') -> \
	$(GRN)$@$(NC)"

run: all
	./$(NAME)

test: $(T_OBJS)
	:

# google test run
gtest:
	$(MAKE) -C $(GTESTDIR)

# make bench -> ベンチマークテスト。実行時間が長いテストも含む。
# stdライブラリとftライブラリで比較できるように二つのバイナリを用意する。
bench: $(STDBIN) $(FTBIN)
	echo hello

$(STDBIN): $(B_OBJS)
	@$(CXX) $(CXXFLAGS) -DSTD $^ $(INCLUDES) -o $(STDBIN)
	@echo -e "flags  : $(YLW)$(CXXFLAGS)$(NC)\nbuild  : $(GRN)$^$(NC)\n=> $(BLU)$(STDBIN)$(NC)" 

$(FTBIN): $(B_OBJS)
	@$(CXX) $(CXXFLAGS) $^ $(INCLUDES) -o $(FTBIN)
	@echo -e "flags  : $(YLW)$(CXXFLAGS)$(NC)\nbuild  : $(GRN)$^$(NC)\n=> $(BLU)$(FTBIN)$(NC)" 

.PHONY: ref
ref:
	cd ref && ./make_ref.sh

clean:
	$(RM) $(OBJS) $(DEPS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME) $(STDBIN) $(FTBIN)

re: fclean all

debug: CXXFLAGS += -g -fsanitize=integer -fsanitize=address -DDEBUG
debug: re

.PHONY: all clean fclean re debug test gtest run bench

# ==== Color define ==== #
YLW := \033[33m
GRN := \033[32m
YLW := \033[33m
BLU := \033[34m
MGN := \033[35m
CYN := \033[36m
NC := \033[m

# ==== suggest 'j' option of make command ==== #
ifeq ($(shell uname), Linux)
	procs := $$(expr $$(grep cpu.cores /proc/cpuinfo | sort -u | sed 's/[^0-9]//g') + 1)
else
	procs := $$(expr $$(system_profiler SPHardwareDataType | grep Total | sed 's/[^0-9]//g') + 1)
endif

.PHONY: proc
proc:
	@echo -e "please do $(CYN)export MAKEFLAGS=-j$(procs)$(NC)"
