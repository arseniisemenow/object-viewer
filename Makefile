C = gcc
CFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow -Isrc
CCOV = --coverage
OS := $(shell uname -s)

DIST_DIR:=archive
TESTS_DIRECTORY:=tests
SOURCE_PATH :=src/
DEST_PATH :=build/
APP_NAME :=3d_viewer_cpp
CMAKE_BUILD_TYPE		:=Release
APP_DESTINATION			:=build/3d_viewer_cpp.app/Contents/MacOS/# will be different on another machine

OS_NAME := $(shell uname -o 2>/dev/null || echo "Unknown")

OPEN_COMMAND := open

ifeq ($(OS_NAME), GNU/Linux) # place here all differ variables
    OPEN_COMMAND := xdg-open
	APP_DESTINATION:=build/
endif

QT_MAKEFILE_NAME = qt_Makefile.mk

TEST_SOURCES = $(TESTS_DIRECTORY)/affine_transformations_tests.cc \
			   $(TESTS_DIRECTORY)/tests.cc \
			   $(TESTS_DIRECTORY)/model_loading_tests.cc \
			   $(SOURCE_PATH)Model/Model.cc \
			   $(SOURCE_PATH)Controller/Controller.cc \
			   $(SOURCE_PATH)Model/Transformation/Transformation.cc \
			   $(SOURCE_PATH)Matrix/Matrix.cc \
			   $(SOURCE_PATH)Model/Parser/Parser.cc

all: clean test gcov_report install run

init_project:
	cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
     -S ${SOURCE_PATH} \
     -B ${DEST_PATH}

install: uninstall init_project
	cmake --build ${DEST_PATH} --target ${APP_NAME} -j 4

uninstall:
	@rm -rf ${DEST_PATH}
	@echo "Uninstall finished"

style:
	@find .. -type f -name "*.cc" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.c" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -i -style=Google {} \;
	@echo "style apply is finished"
style_check:
	@find .. -type f -name "*.cc" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.c" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@echo "style check is finished"

run:
	$(APP_DESTINATION)$(APP_NAME)
dvi:
	@$(OPEN_COMMAND) dvi-folder/README.html

untar_obj:
	tar -xf $(TESTS_DIRECTORY)/obj_files/obj_files.tar

test: untar_obj
	$(C) $(CFLAGS) $(TEST_SOURCES) -o app.out -lgtest -lstdc++ -lm
	./app.out

gcov_report: untar_obj
	$(C) $(TEST_SOURCES) $(CFLAGS) $(CCOV) -o test_cov.out -lgtest -lstdc++ -lm
	./test_cov.out
ifeq ($(OS), Linux)
	lcov -t "viewer" -o viewer.info --no-external -c -d .
else
	lcov -t "viewer" --ignore-errors mismatch -o viewer.info --no-external -c -d .
endif
	genhtml -o report viewer.info
	open report/index.html

dist: clean_dist
	mkdir -p ${DIST_DIR}
	cp -rf src ${DIST_DIR}/src
	cp -rf Makefile ${DIST_DIR}
	tar -czvf archive.tar.gz ${DIST_DIR}
	rm -rf ${DIST_DIR}

dist_unpack:
	tar -xzvf archive.tar.gz

clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist
	@echo "Clean finished"

clean_dist:
	@rm -rf archive
	@rm -rf archive.tar.gz

clean_project:

clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find . -type f -name "*.a" -exec rm {} \;
clean_log:
	@find . -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find . -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find . -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find . -type f -name "*.gcda" -exec rm {} \;
	@find . -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find . -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report
