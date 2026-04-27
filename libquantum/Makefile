NAME := libquantum.a
CC := cc
CFLAGS := -Wall -Werror -Wextra -Iincludes -I../libtensr/includes -I../libft/includes
ARCHIVE := ar rcs

SRC_DIR := src
OBJ_DIR := obj

SRCS := $(addprefix $(SRC_DIR)/, \
			$(addprefix basis/, basis_bra.c basis_ket.c))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(ARCHIVE) $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
