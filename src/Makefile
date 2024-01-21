CC = gcc
CFLAGS = -std=c++17 -Wall -pedantic -Wextra -IMaze/model
UNITFLAGS1 := $(shell pkg-config --cflags gtest)
UNITFLAGS2 := $(shell pkg-config --libs gtest)

UNITOBJS = ./out/tests.o
OBJS = ./out/cave_model.o ./out/maze_model.o ./out/maze_solver.o
GCOV_FLAGS =

.PHONY: all clean fclean test install uninstall dvi dist gcov_report style_change style_check

all: clean install\

OS := $(shell uname)
ifeq ($(OS), Darwin)
    QMK = qmake
    MZ = Maze.app
	TEST_FLAGS = -DGTEST_HAS_PTHREAD=1 -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main
else
    QMK = qmake6
    MZ = Maze
	TEST_FLAGS = -lgtest -lm

endif

install:
	@echo "Start installation"
	@mkdir -p build
	@cd Maze && $(QMK) > /dev/null && make > /dev/null && rm -rf Makefile && rm -rf ../build/$(MZ) && mv $(MZ) ../build/$(MZ)
	@cp -R build/$(MZ) ~/Desktop/$(MZ)
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf ~/Desktop/$(MZ)
	@rm -rf build/$(MZ)
	@echo "┏==================================┓"
	@echo "┃ Uninstall completed successfully ┃"
	@echo "┗==================================┛"

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p dist
	@cp -R build/$(MZ) dist
	@cp ../README_RUS.md dist && cp ../README.md dist
	@cd dist && tar cvzf Maze.tgz *
	@cd dist && rm -rf $(MZ) README.md README_RUS.md
	@echo "The build was successfully archived"

tests : $(OBJS) $(UNITOBJS)
	$(CC) -o tests $(UNITOBJS) $(OBJS) $(TEST_FLAGS) -lstdc++ -fprofile-arcs -ftest-coverage
	./tests

./out/%.o : ./Maze/model/%.cc
	mkdir -p ./out
	$(CC) $(CFLAGS) $(UNITFLAGS1) $(COV_FLAG) -c $<
	mv ./*.o ./out/

./out/tests.o : ./test/tests.cc
	mkdir -p ./out
	$(CC) $(CFLAGS) -c $< $(UNITFLAGS1)
	mv ./*.o ./out/

coverage:
	@./test
	@echo "┏==================================┓"
	@echo "┃  Testing completed successfully  ┃"
	@echo "┗==================================┛"

gcov_report: GCOV_FLAGS += --coverage
gcov_report: clean test
	@echo "┏=========================================┓"
	@echo "┃     Generating your html report ...     ┃"
	@echo "┗=========================================┛"
	@lcov -t test -o test.info -c -d . --exclude '*/tests/*' --ignore-errors source
	@genhtml --ignore-errors unmapped -o test_html test.info
	@rm -rf *.gc* test/*.gc*
	@rm -rf *.gd* test/*.gd*
	@open ./test_html/index.html

style_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -n Maze/*/*.cc Maze/*/*.h Maze/*.cc Maze/*.h test/*.cc
	@rm ./.clang-format

style_change:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -i Maze/*/*.cc Maze/*/*.h Maze/*.cc Maze/*.h test/*.cc
	@rm ./.clang-format

clean:
	@rm -rf test/testing *.gcno *.gcov Maze/*.o *.gcda *.info gcov_report
	@rm -rf Maze/.qmake.stash Maze/*.user Maze/moc_*
	@rm -rf test/*.gcno test/*.o test/*gcda
	@rm -rf tests test.gcda test.gcno 
	@rm -rf out


fclean: clean
	@rm -rf dist ~/Desktop/$(MZ) build* test_html

