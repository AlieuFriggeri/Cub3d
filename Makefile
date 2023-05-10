GREENGREEN = \033[38;5;46m
RED = \033[0;31m
GREY = \033[38;5;240m
RESET = \033[0m

NAME =     cub3d

CC =         gcc
CFLAGS =     -Wall -Wextra -Werror -O3
RM =         rm -rf

DIR_H = headers/
DIR_S =	srcs/
CREATE_DIR_O = @mkdir -p objs
DIR_O =	objs/

SRCS_LIST =	main.c \
			hook.c

SRCS =		${addprefix ${DIR_S}, ${SRCS_LIST}}

OBJS =		${SRCS:${DIR_S}%.c=${DIR_O}%.o}

# Compile la Libft
DIR_LIBFT = libft/
LIBFT_INC = -I ${DIR_LIBFT}
LIBFT =	${DIR_LIBFT}libft.a
FT_LNK = -L ${DIR_LIBFT} -l ft

# Compile la MiniLibX suivant l'OS
ifeq (${shell uname}, Linux)
	DIR_MLX = mlx_linux/
	MLX_LNK	= -L $(DIR_MLX) -lmlx -lXext -lX11 -lbsd -lm
else
	DIR_MLX = mlx_macos/
	MLX_LNK	= -L $(DIR_MLX) -l mlx -framework OpenGL -framework AppKit
endif
MLX_INC = -I ${DIR_MLX}
MLX =	${DIR_MLX}libmlx.a

LIBS = ${FT_LNK} ${MLX_LNK}

# ${NAME}: title ${LIBFT} ${MLX} ${OBJS}
${NAME}: ${LIBFT} ${MLX} ${OBJS}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: Cub3d Objects were created${GREY}"
	${CC} ${OBJS} ${LIBS} -o ${NAME}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: Cub3d created !"

${LIBFT}:
	@echo "[$(GREENGREEN)${NAME}$(RESET)]: Creating Libft...${GREY}"
	${MAKE} -sC ${@D}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: Libft Objects were created"

${MLX}:
	@echo "[$(GREENGREEN)${NAME}$(RESET)]: Creating MLX...$(GREY)"
	${MAKE} -sC ${@D}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: MLX Objects were created"
	@echo "${RESET}[$(GREENGREEN)${NAME}$(RESET)]: Creating Cub3d Objects...${GREY}"

all: ${NAME}

${DIR_O}%.o:${DIR_S}%.c
	@printf "\033[38;5;240m"
	@mkdir -p ${DIR_O}
	${CC} ${CFLAGS} ${LIBFT_INC} ${MLX_INC} -I ${DIR_H} -o $@ -c $<

clean:
	@echo "$(RED) ██████╗██╗     ███████╗ █████╗ ███╗   ██╗██╗███╗   ██╗ ██████╗$(RESET)"
	@echo "$(RED) ██╔════╝██║     ██╔════╝██╔══██╗████╗  ██║██║████╗  ██║██╔════╝$(RESET)"
	@echo "$(RED) ██║     ██║     █████╗  ███████║██╔██╗ ██║██║██╔██╗ ██║██║  ███╗$(RESET)"
	@echo "$(RED) ██║     ██║     ██╔══╝  ██╔══██║██║╚██╗██║██║██║╚██╗██║██║   ██║$(RESET)"
	@echo "$(RED) ╚██████╗███████╗███████╗██║  ██║██║ ╚████║██║██║ ╚████║╚██████╔╝$(RESET)"
	@echo "$(RED)  ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═══╝ ╚═════╝ $(RESET)"
	@echo "[$(RED)${NAME}$(RESET)]: Cleaning ${NAME} Objects...${GREY}"
	${RM} ${OBJS}
	${RM} ${DIR_O}
	@echo "[$(RED)${NAME}$(RESET)]: ${NAME} Objects were cleaned${GREY}"

libclean:
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: Cleaning MLX...${GREY}"
	${MAKE} -sC ${DIR_MLX} clean
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: MLX Objects were cleaned"
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: Cleaning Libft...${GREY}"
	${MAKE} -sC ${DIR_LIBFT} fclean
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: Libft Objects were cleaned"

fclean: clean libclean
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: Cleaning ${NAME}...${GREY}"
	${RM} ${NAME}
	@echo "${RESET}[$(RED)${NAME}$(RESET)]: ${NAME} Executable was cleaned"

re: fclean all

.PHONY: all clean fclean re title libclean 