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

UNAME = ${shell uname}

SRCS_LIST =	main.c \
			hook.c \
			draw.c \
			image.c \
			player.c \
			init.c \
			map.c \
			texture.c \
			collision.c \
			checklines.c

ifeq (${UNAME}, Linux)
	SRCS_LIST += linux.c
else
	SRCS_LIST += macos.c
endif

SRCS =		${addprefix ${DIR_S}, ${SRCS_LIST}}

OBJS =		${SRCS:${DIR_S}%.c=${DIR_O}%.o}

# Define les keycode suivant l'OS
ifeq (${UNAME}, Linux)
	ESC = KEY_ESC=65307
	W = KEY_W=119
	A = KEY_A=97
	S = KEY_S=115
	D = KEY_D=100
	UP = KEY_UP=65362
	DOWN = KEY_DOWN=65364
	LEFT = KEY_LEFT=65361
	RIGHT = KEY_RIGHT=65363
else
	ESC = KEY_ESC=53
	W = KEY_W=13
	A = KEY_A=0
	S = KEY_S=1
	D = KEY_D=2
	UP = KEY_UP=126
	DOWN = KEY_DOWN=125
	LEFT = KEY_LEFT=123
	RIGHT = KEY_RIGHT=124
endif
KEYCODES =  -D $(ESC) -D $(W) -D $(A) -D $(S) -D $(D) -D $(UP) -D $(DOWN) -D $(LEFT) -D $(RIGHT)

# Compile la MiniLibX suivant l'OS
ifeq (${UNAME}, Linux)
	DIR_MLX = mlx_linux/
	MLX_LNK	= -L $(DIR_MLX) -lmlx -lXext -lX11 -lbsd -lm
else
	DIR_MLX = mlx_macos/
	MLX_LNK	= -L $(DIR_MLX) -l mlx -framework OpenGL -framework AppKit
endif
MLX_INC = -I ${DIR_MLX}
MLX =	${DIR_MLX}libmlx.a

# Compile la Libft
DIR_LIBFT = libft/
LIBFT_INC = -I ${DIR_LIBFT}
LIBFT =	${DIR_LIBFT}libft.a
FT_LNK = -L ${DIR_LIBFT} -l ft

LIBS = ${FT_LNK} ${MLX_LNK}

# ${NAME}: title ${LIBFT} ${MLX} ${OBJS}
${NAME}: ${LIBFT} ${MLX} ${OBJS}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: ${NAME} Objects were created${GREY}"
	${CC} ${OBJS} ${LIBS} -o ${NAME}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: ${NAME} created !"

${LIBFT}:
	@echo "[$(GREENGREEN)${NAME}$(RESET)]: Creating Libft...${GREY}"
	${MAKE} -sC ${@D}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: Libft Objects were created"

${MLX}:
	@echo "[$(GREENGREEN)${NAME}$(RESET)]: Creating MLX...$(GREY)"
	${MAKE} -sC ${@D}
	@echo "$(RESET)[$(GREENGREEN)${NAME}$(RESET)]: MLX Objects were created"
	@echo "${RESET}[$(GREENGREEN)${NAME}$(RESET)]: Creating ${NAME} Objects...${GREY}"

all: ${NAME}

${DIR_O}%.o:${DIR_S}%.c
	@printf "\033[38;5;240m"
	@mkdir -p ${DIR_O}
	${CC} ${CFLAGS} ${KEYCODES} ${LIBFT_INC} ${MLX_INC} -I ${DIR_H} -o $@ -c $<

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