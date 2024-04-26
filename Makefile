CC=g++ -std=c++17 -g
GCOVR = $(shell which gcovr || echo "/usr/bin/gcovr")
GOOGLE_TEST_FLAGS = -lgtest -lgtest_main -pthread
GCOV_FLAGS = -fprofile-exclude-files='test/unit_tests.cpp'
CPP_FILES = model/stack.cpp model/calculator.cpp model/credit.cpp model/validation.cpp
OS = $(shell uname -s)

all: install

install:
ifeq ($(shell uname -s),Darwin)
	cd view && cmake --build . --target all
	make open
else
	cd view && cmake .
	cd view && cmake --build . --target all
	make open
endif

install_package:
	sudo apt-get install libvulkan-dev

test: clean
	@$(CC) $(GCOV_FLAGS) --coverage test/unit_tests.cpp model/stack.cpp model/calculator.cpp model/credit.cpp controller/calculator.controller.hpp $(GOOGLE_TEST_FLAGS)
	./a.out

gcov_report: test
	gcov test/unit_tests.cpp model/stack.cpp model/calculator.cpp
	$(GCOVR) -r . --html --html-details -o calculator.html --exclude 'model/main\.cpp' --exclude 'model/tests/.*' --exclude 'model/stack.cpp' --exclude 'model/stack.hpp' --exclude 'model/calculator.hpp' --exclude 'controller/calculator.controller.hpp'
	make open-gcov

open-gcov:
	@echo "OPEN REPORT..."
	open calculator.html

open:
ifeq ($(shell uname -s),Darwin)
	chmod +x view/calculator.app/Contents/MacOS/calculator
	cd view/calculator.app/Contents/MacOS/ && ./calculator
else
	chmod +x view/calculator
	cd view/ && ./calculator
endif

uninstall:
ifeq ($(shell uname -s),Darwin)
	rm -rf view/calculator.app/
else
	rm -rf view/CMakeFiles/ view/cmake_install.cmake view/CMakeCache.txt view/calculator_autogen view/calculator view/Makefile
endif

clang-check:
	clang-format -n ../src/**.c ../src/**.h calc_functions/*.c calc_functions/*.h unit_tests/*.c Qt_calculator/*.cpp Qt_calculator/*.c Qt_calculator/*.h

clang:
	clang-format -i ../src/**.c ../src/**.h calc_functions/*.c calc_functions/*.h unit_tests/*.c Qt_calculator/*.cpp Qt_calculator/*.c Qt_calculator/*.h

check-format:
	@echo "Checking code format..."
	@find model controller -name '*.cpp' -or -name '*.hpp' | xargs clang-format -style=file -n

code-format:
	@echo "Format code..."
	@find model controller -name '*.cpp' -or -name '*.hpp' | xargs clang-format -style=file -i

clean:
	@rm -rf *.o
	@rm -f main
	@rm -f ./a.out *.gcda *.gcno
	@rm -f *.css *.html
	@rm -f about.pdf about.log about.aux
	@rm -f calculator.zip
	make uninstall

dist:
	zip -r calculator.zip ../../C7_SmartCalc_v1.0-1/

dvi_package:
	sudo apt install texlive-latex-base

dvi:
	open smart_calc_about.pdf

val:
	@make test
ifeq ($(OS), Linux)
	@valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./a.out
else 
ifeq ($(OS), Darwin)
	leaks -atExit -- ./a.out
endif
endif
