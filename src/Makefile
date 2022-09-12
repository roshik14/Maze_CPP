.PHONY: all tests clean install dist dvi uninstall leaks run

CXX = g++
CXXFLAGS = -lgtest -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
OS:=$(shell uname -s)
TEXI2HTML = makeinfo --no-split --html --no-warn

SOURCES = src/Controller/*.cc src/Model/WaveAlgorithm/*.cc src/Model/*.cc src/Model/Drawer/*.cc src/View/*.cc
HEADERS = src/Controller/*.h src/Model/WaveAlgorithm/*.h *.h src/Model/*.h src/Model/Drawer/*.h src/View/*.h

TEST_GENERATOR_SRCS = src/Tests/labyrinth_generator_test.cc Model/elleralgorithm.cc
TEST_SEARCHER_SRCS = src/Tests/labyrinth_searcher_test.cc Model/WaveAlgorithm/*.cc Model/fileManager.cc Model/elleralgorithm.cc
TEST_CAVE_SRC = src/Tests/cave_generator_test.cc Model/cave_generator.cc Model/filemanager.cc

BUILD_SRC = src/Controller src/Model src/View src/main.cc src/*.h src/Maze.pro

SUP = --suppress=

all: install run

tests: Tests/labyrinth_generator_test.cc Tests/labyrinth_searcher_test.cc Tests/cave_generator_test.cc
	@$(CXX) $(CHECKFLAGS) $(TEST_GENERATOR_SRCS) -o generator_test $(CXXFLAGS)
	@$(CXX) $(CHECKFLAGS) $(TEST_SEARCHER_SRCS) -o searcher_test $(CXXFLAGS)
	@$(CXX) $(CHECKFLAGS) $(TEST_CAVE_SRC) -o cave_test $(CXXFLAGS)
	@./generator_test
	@./searcher_test
	@./cave_test

clean:
	@/bin/rm -rf *.o generator_test searcher_test cave_test *.out moc_* info.html *.tar

install: uninstall
	mkdir ../build
	cp -r $(BUILD_SRC) ../build/
	cd ../build; qmake -makefile Maze.pro
	make -C ../build
	make clean -C ../build

dist: 
	@tar -zcf Maze.tar * Makefile *.tex

dvi: info.tex
	$(TEXI2HTML) info.tex
	open info.html

uninstall:
	@rm -rf ../build

leaks: tests
ifeq ($(OS), Darwin)
	@leaks --atExit -- ./generator_test ./searcher_test
else
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./generator_test ./searcher_test
endif

cppcheck:
	@cppcheck --enable=all --std=c++17 --language=c++ $(SUP)unusedFunction $(SUP)missingInclude $(SUP)unmatchedSuppression $(SOURCES)

style:
	@cp -r ../materials/linters/.clang-format ./
	@clang-format -n $(SOURCES) $(HEADERS)
	@rm -rf .clang-format

run:
ifeq ($(OS), Darwin)
	./../build/Maze.app/Contents/MacOS/Maze
else
	./../build/Maze
endif

