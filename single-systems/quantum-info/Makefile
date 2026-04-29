NAME := quantum_info
CC := cc
CFLAGS := -Wall -Wextra -I../../libft/includes -I../../libtensr/includes -I../../libquantum/includes
LDFLAGS := -L../../libft -L../../libtensr -L../../libquantum -lquantum -ltensr -lft -lm

SRC := main.c
OBJ := main.o

all: $(NAME)

../../libft/libft.a:
	@make -C ../../libft

../../libtensr/libtensr.a:
	@make -C ../../libtensr

../../libquantum/libquantum.a:
	@make -C ../../libquantum

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) ../../libft/libft.a ../../libtensr/libtensr.a ../../libquantum/libquantum.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
