##
## EPITECH PROJECT, 2024
## makefile
## File description:
## task 01
##

## .o FILES DIRECTORY
OBJ_DIR = obj
# FILES
SRC	=	src/lib/split_str.c 		\
		src/lib/my_strlen.c 		\
		src/lib/my_strncmp.c 		\
		src/lib/my_strcmp.c 		\
		src/lib/my_strncpy.c		\
		src/lib/my_strcat.c 		\
		src/lib/free.c 				\
		src/lib/linked_lists.c 		\
		src/lib/my_strdup.c 		\
		src/lib/array_to_str.c 		\
		src/lib/my_array_len.c 		\
		src/lib/total_array_len.c 	\
		src/lib/mini_printf.c 		\
		src/lib/my_strcpy.c 		\
		src/lib/my_get_nbr.c 		\
		src/lib/types.c 			\
		src/lib/str_lowcase.c 		\
		src/utils/types.c 	 		\
		src/utils/data_struct.c 	\
		src/utils/open_file.c 		\
		src/utils/trim_array.c 		\
		src/utils/copy_instance.c 	\
		src/utils/convert.c 		\
		src/pandas/df_read_csv.c 	\
		src/pandas/df_write_csv.c 	\
		src/pandas/df_shape.c 		\
		src/pandas/df_head.c 		\
		src/pandas/df_info.c 		\
		src/pandas/df_describe.c 	\
		src/pandas/df_tail.c 		\
		src/pandas/df_get_value.c 	\
		src/pandas/df_apply.c 		\
		src/pandas/df_get_unique_values.c 	\
		src/pandas/df_free.c 		\

# COLORS
RED=\033[31m
GREEN=\033[32m
WHITE=\033[37m
BOLD=\033[1m
RESET=\033[0m

# VARIABLES
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
CFLAGS = -Wextra -Wall -W -Werror -I include -lm
CC = ar rcs
NAME = libcuddle.a

# PRINT COMPILATION
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e "$(GREEN)$(BOLD)[COMPILING]:\t$(RESET)$(GREEN)$<$(RESET)"
	@gcc $(CFLAGS) -c $< -o $@

# PRINT AND THEN COMPILE
all: pre-compile $(NAME)

# PRINT INFO
pre-compile:
	@echo -e "$(WHITE)$(BOLD)\t$(WHITE)[COMPILATION...]$(RESET)"
	@mkdir -p $(OBJ_DIR)

# COMPILATION
$(NAME): $(OBJ)
	@$(CC) $(NAME) $(OBJ)
	@echo -e "$(WHITE)$(BOLD)\t[COMPILED SUCCESSFULLY]"
	@echo -e "[READY]:$(RESET)$(WHITE)\t$(NAME)$(RESET)"


# CLEAN OBJECT FILES
clean:
	@echo -e "$(WHITE)$(BOLD)\t[CLEANING OBJ...]$(RESET)"
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo -e "$(RED)$(BOLD)[CLEAN]:\t$(RESET)$(RED)$(OBJ_DIR)$(RESET)"; \
		rm -rf $(OBJ_DIR); \
	fi

# CLEAN EXEC / LIB
fclean:
	@echo -e "$(WHITE)$(BOLD)\t[CLEANING EXEC/LIB...]"
	@echo -e "$(RED)[CLEAN]:\t$(RESET)$(RED)$(NAME)$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) clean -s
	@rm -f test

# CLEAN EVERYTHING AND RE-COMPILE
re: fclean all

.PHONY: test

test: $(OBJ)
	@$(MAKE) re -s
	@gcc -o test tests/main.c $(CFLAGS) -L. -lcuddle -lm
