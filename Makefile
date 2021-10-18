NAME	=	containers
CC		=	clang++
HEADER	=	sources/* mytestes.hpp
OBJDIR	=	obj
SRC		=	main.cpp

OBJ 	=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
CFLAGS	=	-Wall -Wextra -Werror -std=c++98  #-fsanitize=address -g

ifneq (,$(findstring xterm,${TERM}))
	GREEN := $(shell tput -Txterm setaf 2)
	RESET := $(shell tput -Txterm sgr0)
else
	GREEN := ""
	RESET := ""
endif

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "${GREEN}Ca compile \\o/ \nL'util s'appelle ./$(NAME)\n${RESET}"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $< -o $@

go:	re
	@./$(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)

re: fclean all

.PHONY: clean fclean all re