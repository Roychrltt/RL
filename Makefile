NAME = game.so

CPP = g++ -std=c++20

CPPFLAGS = -Wall -Werror -Wextra -Wno-shadow -Wconversion -fPIC

INC = -Icpp

SRC_DIR = cpp/
	  
OBJ_DIR = .objs/

SRC_FILES = main.cpp utils.cpp print.cpp

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPPFLAGS) $(INC) -shared -o $(NAME) $(OBJ)
	printf "$(ERASE)$(GREEN)👷 Program$(RESET) $(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)created! 👷\n$(RESET)"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(@D)
	$(CPP) $(CPPFLAGS) $(INC) -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation: $(RESET) $<"

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	printf "$(ERASE)$(GREEN)Fcleaning up...$(RESET)"
	$(RM) ${NAME}
	printf "$(ERASE)🧼 $(GREEN)Fclean finished! 🧼\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re
.SILENT:

# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
ERASE = \033[2K\r
RESET = \033[0m
