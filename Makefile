# RUN PROJECT: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s ./minishell

NAME = minishell

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

CFLAGS = #-Wall -Wextra -Werror

RLIB = -lreadline

INCLUDES = minishell.h inc/builtins.h inc/executor.h inc/parser.h inc/signals.h inc/structs.h inc/tokenizer.h

RM = rm -f

BUILT_INS = src/builtins/ft_echo.c \
						src/builtins/ft_pwd.c \
						src/builtins/ft_env.c \
						src/builtins/ft_unset.c \
						src/builtins/ft_cd.c \
						src/builtins/ft_exit.c \
						src/builtins/ft_export.c \
						src/builtins/export_to_env.c \
						src/builtins/change_to_directory.c \
						src/builtins/export_utils.c \
						src/builtins/unset_var_env.c \

EXECUTOR = src/executor/executor.c \
					src/executor/dirty_parse.c \
					src/executor/get_cmd_path.c

TOKENIZER =	src/tokenizer/token_generator.c \
			src/tokenizer/token_list.c \
			src/tokenizer/token_cleaner.c

PARSER = src/parser/get_path.c \
			src/parser/parse_utils.c

SIGNAL = src/signals/signal_reception.c	

GENERAL = src/general/main.c \
			src/general/error_management.c \
			src/general/free_utils.c \
			src/general/general_utils.c

VALGRIND			= valgrind
VALGRIND_OPT		+= --suppressions=readline.supp
VALGRIND_OPT		+= --trace-children=yes
VALGRIND_OPT		+= --track-origins=yes
VALGRIND_OPT		+= --track-fds=yes
VALGRIND_OPT		+= --leak-check=full
VALGRIND_OPT		+= --show-leak-kinds=all
EXC_NAME			= $(dir $(NAME))$(notdir $(NAME))

OBJS = ${BUILT_INS:.c=.o} ${EXECUTOR:.c=.o} ${TOKENIZER:.c=.o} ${GENERAL:.c=.o} ${PARSER:.c=.o} ${SIGNAL:.c=.o}

$(NAME): $(OBJS) $(INCLUDES)
		$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT) $(RLIB)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

clean:
		$(RM) $(OBJS)
		cd $(LIBFTDIR) && make clean

fclean: clean
		$(RM) $(NAME)
		cd $(LIBFTDIR) && make fclean

re: fclean all

valgrind:
					@echo -e '\033[33m$(VALGRIND) \033[36m$(VALGRIND_OPT) \033[0m-- $(EXC_NAME)'
					@$(VALGRIND) $(VALGRIND_OPT) -- $(EXC_NAME)

.PHONY = all clean fclean re bonus debug valgrind
