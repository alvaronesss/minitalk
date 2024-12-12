################################################################################
#                              MAKEFILE - PROJECT                              #
################################################################################

#                                     CONFIG                                   #
NAME_CLIENT        := client
NAME_SERVER        := server
CC                 := gcc
FLAGS              := -Wall -Wextra -Werror -g #-fsanitize=address,undefined

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_CLIENT        := client.c
SRCS_SERVER        := server.c

OBJS_CLIENT        := $(SRCS_CLIENT:.c=.o)
OBJS_SERVER        := $(SRCS_SERVER:.c=.o)

################################################################################
#                                  COLOR CONFIG                                #
################################################################################

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
CYAN 		:= \033[1;36m
RM		    := rm -f

################################################################################
#                                 MAKE RULES                                   #
################################################################################

all: $(NAME_CLIENT) $(NAME_SERVER)

# Regla para compilar el ejecutable client
$(NAME_CLIENT): $(OBJS_CLIENT)
	@echo "$(GREEN)Compilando $(YELLOW)$(NAME_CLIENT)$(CLR_RMV)..."
	$(CC) $(FLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT)
	@echo "$(GREEN)$(NAME_CLIENT) creado$(CLR_RMV) ✔️"

# Regla para compilar el ejecutable server
$(NAME_SERVER): $(OBJS_SERVER)
	@echo "$(GREEN)Compilando $(YELLOW)$(NAME_SERVER)$(CLR_RMV)..."
	$(CC) $(FLAGS) -o $(NAME_SERVER) $(OBJS_SERVER)
	@echo "$(GREEN)$(NAME_SERVER) creado$(CLR_RMV) ✔️"

# Regla genérica para compilar archivos .o a partir de .c
%.o: %.c
	@echo "$(CYAN)Compilando $< $(CLR_RMV)..."
	$(CC) $(FLAGS) -c $< -o $@

# Regla para limpiar los archivos objeto
clean:
	@$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)
	@echo "$(RED)Archivos objeto eliminados$(CLR_RMV) ✔️"

# Regla para limpiar los binarios y los archivos objeto
fclean: clean
	@$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	@echo "$(RED)Binarios $(NAME_CLIENT) y $(NAME_SERVER) eliminados$(CLR_RMV) ✔️"

# Regla para recompilar todo desde cero
re: fclean all

################################################################################
#                               PHONY TARGETS                                  #
################################################################################

.PHONY: all clean fclean re
