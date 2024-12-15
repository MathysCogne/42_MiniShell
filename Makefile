NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = include

SRC = minishell.c \
\
		parsing/parsing.c \
			parsing/handle_input/delete_input.c \
			parsing/handle_input/get_input.c \
			parsing/handle_input/put_input.c \
			parsing/handle_input/tokenization.c \
\
			parsing/analys_semantic/analys_semantic.c \
\
			parsing/utils/init_struct_env.c \
			parsing/utils/is_external_command.c \
			parsing/utils/is_internal_command.c \
			parsing/utils/debug.c \
\
		exec/exec.c \
\
		utils/ft_split_minishell.c \
		utils/free_split.c


OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

BUILD = $(OBJDIR)/.build

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)/include
LDFLAGS =  -L$(LIBFT_DIR)
LIBS =  $(LIBFT) -lreadline -lhistory


CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3 -I$(LIBFT_INCLUDE)
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

all: clear $(NAME)

$(NAME): $(BUILD)

$(BUILD): $(LIBFT) $(OBJ)
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
# Libft - Branch 'V.mini_talk_07_12_2024' ### TODO BRANCH MINISHELL BEFORE PUSH
$(LIBFT):
	@$(V)echo '[$(NAME)] Downloading my Libft from github.com...'$(RESET)
	$(V)@git clone https://github.com/MathysCogne/MyLibft_GNL_Printf.git libft > /dev/null 2>&1
	@$(V)echo '[$(NAME)] Compiling Libft...'$(RESET)
	$(V)$(MAKE) --silent -C $(LIBFT_DIR)
	@$(V)echo '[$(NAME)] Libft build successfully'

#################################
#             CLEAN             #
#################################
clear:
	@clear

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
	@if norminette | grep -B1 "Error"; then \
		echo $(RED)"Norme KO"$(RESET); \
	else \
		echo $(GREEN)"Norme ok ✅"$(RESET); \
	fi

#################################
#             TEST              #
#################################
test: norme
	$(V)echo $(GREEN)"Running pgrm with valgrind..."$(RESET)
	$(V)valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp ./$(NAME)


re: fclean all

regen:
	makemyfile

.PHONY: all clean fclean re bonus regen norme test install uninstall distclean format lint docs
.DEFAULT_GOAL := all
