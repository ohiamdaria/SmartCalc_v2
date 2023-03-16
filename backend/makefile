CC          := gcc
WARNINGS    := -Wall -Werror -Wextra 
CFLAGS      := -std=c11 -pedantic $(WARNINGS)
INC_CHECK   := $(shell pkg-config --cflags check)
LFLAGS      ?= $(shell pkg-config --libs check) 

ifeq ($(shell uname), Linux)
	LFLAGS = $(shell pkg-config --libs check) -lcheck_pic -lpthread -lrt -lsubunit -lm
endif

TEST_FLAGS  := --coverage -c -g

OBJ_DIR     := obj
TEST_SRC_DIR:= tests
TEST_OBJ_DIR:= tests_obj
GCOV_OBJ_DIR:= gcov_res
CALC_DIR		:= ./backend

TEST_SRC  := $(shell find $(TEST_SRC_DIR) -maxdepth 1 -name "*.c")
search_wildcards := $(addsuffix /s21_*.c,$(CALC_DIR)) 
CALC_SRC  := $(wildcard s21*.c)

TEST_OBJ  := $(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o)))
CALC_OBJ  := $(patsubst %.c, %.o, $(CALC_SRC))
GCOV_OBJ  := $(addprefix $(GCOV_OBJ_DIR)/, $(patsubst %.c, %.o, $(CALC_SRC)))

CALC_TEST := calc_test.c
CALC_LIB	:= s21_smartcalc.a 


all: clean $(CALC_LIB) test gcov_report

test: $(CALC_LIB)  $(TEST_OBJ_DIR)/main.o $(TEST_OBJ)
	$(CC) $(LFLAGS) $(TEST_OBJ) $(TEST_OBJ_DIR)/main.o $(CALC_LIB)  -o test
	- ./test

$(CALC_LIB): $(CALC_OBJ)
	ar rc $(CALC_LIB) $(CALC_OBJ)
	ranlib 	$(CALC_LIB)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(TEST_OBJ_DIR)/main.o: $(CALC_TEST) 
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC)  $(INC_CHECK) -c -o $(TEST_OBJ_DIR)/main.o $(CALC_TEST)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(INC_CHECK) -c $^ -o $@


gcov_report: $(TEST_OBJ_DIR)/main.o $(GCOV_OBJ) $(MATRIX_SRC)
	ar rc $(CALC_LIB) $(GCOV_OBJ)
	ranlib 	s21_smartcalc.a
	$(CC) $(LFLAGS) --coverage $(TEST_OBJ) $(TEST_OBJ_DIR)/main.o s21_smartcalc.a -o test
	- ./test
	gcovr	-r	.	--html	--html-details	-o	coverage_report.html
	rm	-rf	*.o	*.out	*.gcno	*.gcna	*gcda
	open	./coverage_report.html


$(GCOV_OBJ_DIR)/%.o: %.c
	@mkdir -p $(GCOV_OBJ_DIR)
	$(CC) $(CFLAGS) $(TEST_FLAGS) $^ -o $@

.PHONY: clean_lib
clean: clean_bin
	rm -f *.gcda 
	rm -f *.gcov 
	rm -f *.gcno 
	rm -f coverage.info
	rm -f test
	rm -f s21_smartcalc.a
	rm -rf obj
	rm -rf tests_obj
	rm -rf gcov_res
	rm	-rf	*.o	*.out *.gcno *.gcna	*.html *.gcda *.css	*.exe


clean_bin: 
	rm -f $(CALC_OBJ) 
	rm -f $(TEST_OBJ) 
	rm -f $(GCOV_OBJ) 

rebuild: clean clean_lib clean_bin all