CC=g++ -std=c++17
GCOVR = $(shell which gcovr || echo "/usr/bin/gcovr")
GOOGLE_TEST_FLAGS = -lgtest
GCOV_FLAGS = -fprofile-exclude-files=test/unit_tests.cpp -fprofile-arcs -ftest-coverage

all: install

install:
	cd view && cmake --build . --target all

install_package:
	sudo apt-get install libvulkan-dev

test: install
	@$(CC) --coverage $(GOOGLE_TEST_FLAGS) test/unit_tests.cpp model/stack.cpp model/calculator.cpp model/credit.cpp controller/calculator.controller.hpp
	./a.out

gcov_report: test
	gcov test/unit_tests.cpp model/stack.cpp model/calculator.cpp
	$(GCOVR) -r . --html --html-details -o calculator.html --exclude 'main\.cpp' --exclude 'tests/.*' --exclude 'stack.cpp'
	make open-gcov

open-gcov:
	@echo "OPEN REPORT..."
	open calculator.html

open:
ifeq ($(shell uname -s),Darwin)
	chmod +x view/calculator.app/Contents/MacOS/calculator
	cd view/calculator.app/Contents/MacOS/ && ./calculator
else
	chmod +x view/build/calculator
	cd view/build/ && ./calculator
endif

uninstall:
ifeq ($(shell uname -s),Darwin)
	rm -rf view/calculator.app/
else
	rm -rf view/build/
endif

clang-check:
	clang-format -n ../src/**.c ../src/**.h calc_functions/*.c calc_functions/*.h unit_tests/*.c Qt_calculator/*.cpp Qt_calculator/*.c Qt_calculator/*.h

clang:
	clang-format -i ../src/**.c ../src/**.h calc_functions/*.c calc_functions/*.h unit_tests/*.c Qt_calculator/*.cpp Qt_calculator/*.c Qt_calculator/*.h

clean:
	@rm -rf *.o
	@rm -f main
	@rm -f ./a.out *.gcda *.gcno
	@rm -f *.css *.html
	@rm -f about.pdf about.log about.aux
	@rm -f calculator.zip

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
