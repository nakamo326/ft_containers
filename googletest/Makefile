CXX := clang++
INCLUDES := -I./includes

# ---- Google Test ---- #
GTESTDIR := .
GTEST := $(GTESTDIR)/gtest $(GTESTDIR)/googletest-release-1.11.0
TESTDIR := ../tests
TESTSRC := $(shell find tests -type f)

PYTHON = $(shell which python)
ifeq ($(shell which python),)
PYTHON = $(shell which python3)
endif

$(GTEST):
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar --remove-file -xvzf release-1.11.0.tar.gz googletest-release-1.11.0
	$(PYTHON) googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(GTESTDIR)

all: $(GTEST)
	$(CXX) -std=c++11 $(TESTDIR)/gtest.cpp $(GTESTDIR)/gtest/gtest-all.cc \
	$(GTESTDIR)/googletest-release-1.11.0/googletest/src/gtest_main.cc \
	$(TESTSRC) -DDEBUG -g -fsanitize=integer -fsanitize=address \
	-I$(GTESTDIR) -I$(INCLUDES) -lpthread -o tester
	./tester
	$(RM) tester
