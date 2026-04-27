NAME := classical_info
CC := cc
CFLAGS := -Wall -Wextra -I../../libft/includes -I../../libtensr/includes -I../../libquantum/includes
LIBS := -L../../libft -L../../libtensr -L../../libquantum -lquantum -ltensr -lft -lm

SRC := main.c
OBJ := main.o

DEPENDS := libft/libft.a libtensr/libtensr.a libquantum/libquantum.a

all: $(DEPENDS) $(NAME)

libft/libft.a:
	@make -C ../../libft

libtensr/libtensr.a:
	@make -C ../../libtensr

libquantum/libquantum.a:
	@make -C ../../libquantum

$(NAME): libft/libft.a libtensr/libtensr.a libquantum/libquantum.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C ../../libft clean
	@make -C ../../libtensr clean
	@make -C ../../libquantum clean
	@rm -f $(OBJ)

fclean: clean
	@make -C ../../libft fclean
	@make -C ../../libtensr fclean
	@make -C ../../libquantum fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
