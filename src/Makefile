# Компилятор
CC = g++

# Флаги компиляции
CFLAGS = -Wall -Werror -Wextra -std=c++20 -pedantic-errors
LDFLAGS = -lgtest -lgtest_main -lpthread

# Директории
SRC_DIR = s21_containers
TEST_DIR = tests
OBJ_DIR = obj
GCOV_DIR = obj/gcov
TESTS_OBJ_DIR = obj/tests
REPORT_DIR = report

# Цели
TARGET = test
GCOV_TARGET = gcov_report
LIBRARY = s21_containers.a
GCOV_LIBRARY = s21_containers_gcov.a

LCOV_FLAGS = -fprofile-arcs -ftest-coverage
TEST_FUNC = $(wildcard ./tests/*.cpp)
TEST_FLAGS = -L/usr/local/lib -lgtest -pthread -L/usr/local/lib -lgtest_main -DUNIT_TEST

# Исходные файлы
SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/s21_AVL_Tree/*.cpp $(SRC_DIR)/s21_set/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
GCOV_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(GCOV_DIR)/%.o,$(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(TESTS_OBJ_DIR)/%.o,$(TEST_SRCS))

.PHONY: all test gcov_report clean rebuild style leaks valgrind

all: test

test: $(TARGET)

install_lib:
	sudo apt update
	sudo apt install gcc
	sudo apt install lcov
	sudo apt install valgrind

install_gtest:
	sudo apt install libgtest-dev
	sudo apt install cmake
	sudo cmake -S /usr/src/googletest -B /usr/src/googletest/build
	sudo cmake --build /usr/src/googletest/build
	sudo cp -r /usr/src/googletest/googletest/include/gtest /usr/local/include/
	sudo cp /usr/src/googletest/build/lib/*.a /usr/local/lib/

gcov_report: clean
	$(CC) $(CFLAGS) $(LCOV_FLAGS) $(TEST_FUNC) -o test $(TEST_FLAGS) -lgcov
	./test
	lcov --ignore-errors mismatch --capture --directory . --output-file coverage.info
	lcov --remove coverage.info "/usr/*" "tests" --output-file coverage.info.cleaned
	genhtml coverage.info.cleaned --output-directory coverage

$(TARGET): $(TESTS_OBJ_DIR) $(OBJ_DIR) $(LIBRARY) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBRARY) $(LDFLAGS) -o $@
	@echo "\n\033[0;32mRunning tests...\033[0m\n"
	@./$(TARGET)

$(LIBRARY): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(TESTS_OBJ_DIR):
	@mkdir -p $(TESTS_OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(REPORT_DIR) $(GCOV_DIR) $(TESTS_OBJ_DIR)
	rm -f *.a *.o *.gcno *.gcda *.gcov coverage.info
	rm -f $(TARGET) $(GCOV_TARGET)

rebuild: clean all

clang:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n --style=file $$(find . -type f \( -name "*.tpp" -o -name "*.h" -o -name "*.cpp" \))
	rm -f .clang-format

clang-fix:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i --style=file $$(find . -type f \( -name "*.tpp" -o -name "*.h" -o -name "*.cpp" \))
	rm -f .clang-format

leaks:
	leaks --atExit -- ./$(TARGET)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)