CC := cc
CFLAGS := -Wall -Wextra

LIBRARIES := libft/libft.a libtensr/libtensr.a libquantum/libquantum.a

all: $(LIBRARIES)

# Build libraries
libft/libft.a:
	@$(MAKE) -C libft

libtensr/libtensr.a:
	@$(MAKE) -C libtensr

libquantum/libquantum.a:
	@$(MAKE) -C libquantum

# Clean targets (libraries only)
clean:
	@$(MAKE) -C libft clean
	@$(MAKE) -C libtensr clean
	@$(MAKE) -C libquantum clean

fclean: clean
	@$(MAKE) -C libft fclean
	@$(MAKE) -C libtensr fclean
	@$(MAKE) -C libquantum fclean

re: fclean all

.PHONY: all clean fclean re
