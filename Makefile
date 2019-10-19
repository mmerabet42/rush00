COMPILER = clang++
CFLAGS = -Wall -Wextra -Werror

NAME = ft_retro

_SOURCES = GameEntity.cpp Point.cpp Behavior.cpp momo_main.cpp Scene.cpp
SOURCES = $(addprefix srcs/,$(_SOURCES))

_INCLUDES = LinkedList.hpp List.hpp Pair.hpp GameEntity.hpp Point.hpp
INCLUDES = $(addprefix incs/,$(_INCLUDES))

OBJECTS = $(SOURCES:.cpp=.o)

all:
	@make $(NAME)

$(NAME): $(OBJECTS)
	@echo "Compiling $(NAME)..."
	@$(COMPILER) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(NAME) done."

%.o: %.cpp $(INCLUDES) Makefile
	@$(COMPILER) $(CFLAGS) -o $@ -c $< -I incs

clean:
	@rm -rf $(OBJECTS)

fclean:
	@make clean
	@rm -rf $(NAME)

re:
	@make fclean
	@make all
