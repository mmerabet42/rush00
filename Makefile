COMPILER = clang++
CFLAGS = -Wall -Wextra -Werror

NAME = ft_retro

_SOURCES = GameEntity.cpp Point.cpp Behavior.cpp Scene.cpp main.cpp Star.cpp
SOURCES = $(addprefix srcs/,$(_SOURCES))

_INCLUDES = LinkedList.hpp List.hpp Pair.hpp GameEntity.hpp Point.hpp \
			Star.hpp Scene.hpp CanonicalForm.hpp Behavior.hpp
INCLUDES = $(addprefix incs/,$(_INCLUDES))

OBJECTS = $(SOURCES:.cpp=.o)

all:
	@make $(NAME)

$(NAME): $(OBJECTS)
	@echo "Compiling $(NAME)..."
	@$(COMPILER) $(CFLAGS) $(OBJECTS) -o $(NAME) -lncurses
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
