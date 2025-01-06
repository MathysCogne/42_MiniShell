NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = include

SRC = minishell.c \
\
		parsing/parsing.c \
			parsing/tokenization/input_parser.c \
			parsing/tokenization/put_input.c \
			parsing/tokenization/token_utils.c \
			parsing/tokenization/tokenization.c \
\
			parsing/analyse_semantic/semantic.c \
			parsing/analyse_semantic/command_utils.c \
			parsing/analyse_semantic/extract_args.c \
			parsing/analyse_semantic/redirection_handler.c \
			parsing/analyse_semantic/find_path_and_cmd.c \
\
			parsing/quote_expand/expand.c \
			parsing/quote_expand/quote_expand.c \
			parsing/quote_expand/quote_handler.c \
			parsing/quote_expand/check_single_quotes.c \
\
			parsing/utils_parsing/cleanup.c \
			parsing/utils_parsing/init_struct_env.c \
			parsing/utils_parsing/debug.c \
\
		exec/process/exec.c \
			exec/process/exec_error.c \
			exec/process/exec_process.c \
			exec/process/here_doc.c \
			exec/signal/signal.c \
\
		builtins/echo.c \
		builtins/env.c \
		builtins/pwd.c \
		builtins/cd.c \
\
		utils/split/split_helper.c \
		utils/split/split_minishell.c \
		utils/split/split_quote_helper.c \
		utils/split/split_redir_helper.c \
		utils/is_external_command.c \
		utils/is_builtin_command.c \
		utils/ft_tablen.c \
		utils/get_shell_name.c \


OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

BUILD = $(OBJDIR)/.build

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)/include
LDFLAGS =  -L$(LIBFT_DIR) -L/opt/homebrew/opt/readline/lib
LIBS =  $(LIBFT) -lreadline -lhistory


CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3 -I$(LIBFT_INCLUDE) -I/opt/homebrew/opt/readline/include
AR = ar
ARFLAGS = rcs

#################################
#          COMPIL MODE          #
#################################
VERBOSE ?= 0
ifeq ($(VERBOSE),1)
  V := 
else
  V := @
endif

#################################
#             COLORS            #
#################################
RED     := "\033[1;31m"
GREEN   := "\033[1;32m"
RESET   := "\033[0m"

#################################
#            EXECUTABLE         #
#################################

all: $(NAME)

$(NAME): $(BUILD)

$(BUILD): $(LIBFT) $(OBJ)
	@clear
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(BONUS_OBJ) $(LIBS) $(MLXFLAGS) -o $(NAME)
	$(V)echo $(GREEN)"[$(NAME)] Executable created ✅"$(RESET)
	@touch $@

#################################
#        OBJ & DEP FILES        #
#################################
$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

DEP = $(OBJ:.o=.d)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

#################################
#             LIBFT             #
#################################
# Libft - Branch 'V.mini_shell_24_12_2024' (No update before push) #TODO CHANGE BRACH UPDATE FPRINTF
$(LIBFT):
	@$(V)echo '[$(NAME)] Downloading my Libft from github.com...'$(RESET)
	$(V)@git clone https://github.com/MathysCogne/MyLibft_GNL_Printf.git libft > /dev/null 2>&1
	@$(V)echo '[$(NAME)] Compiling Libft...'$(RESET)
	$(V)$(MAKE) --silent -C $(LIBFT_DIR)
	@$(V)echo '[$(NAME)] Libft build successfully'

#################################
#             CLEAN             #
#################################
	
clean:
	$(V)echo $(RED)'[$(NAME)] Cleaning objects'$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(NAME)
	$(V)echo $(RED)'[libft] Remove directory'$(RESET)
	@rm -rf $(LIBFT_DIR)


#################################
#             NORME             #
#################################
norme:
	@if norminette | grep "Error" > norminette_errors.txt; then \
		echo $(RED)"[$(NAME)] Norme KO"$(RESET); \
		cat norminette_errors.txt | awk 'BEGIN {FS=":"; OFS=":"} \
		/^src/ || /^libft/ {print "\n" $$0} \
		/^Error/ {sub(/^Error: /, ""); print "  ➜ " $$0}'; \
	else \
		echo $(GREEN)"[$(NAME)] Norme ok ✅"$(RESET); \
	fi
	@rm -f norminette_errors.txt

#################################
#             TEST              #
#################################
test: all norme
	$(V)echo $(GREEN)"[$(NAME)] Running $(NAME) with valgrind"$(RESET)
	$(V)valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=valgrind.supp ./$(NAME)


re: fclean all

regen:
	makemyfile

.PHONY: all clean fclean re bonus regen norme test
.DEFAULT_GOAL := all
