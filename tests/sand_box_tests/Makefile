NAME			=		 test_map

HEADER			=		Map/bidirectional_iterator.hpp \
						Map/map_reverse_iterator.hpp \
						Map/pair.hpp \
						Map/RBT.hpp \
						Map/map.hpp \
						cam/bidirectional_iterator.hpp \
						cam/BSTNode.hpp \
						cam/pair.hpp \
						cam/reverse_iterator.hpp \
						cam/map.hpp \
						cam/vector_iterator.hpp \
						cam/vector.hpp \
						main.cpp

CC				=		@clang++

CFLAGS			=		-Wall -Wextra -Werror -g3

SRCS			=		main.cpp

OBJS			=		$(SRCS:.cpp=.o)

all				:		$(NAME)


$(NAME)		: $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "\033[34m[$(NAME)] Compiled\033[0m"

%.o: %.cpp
		$(CC) $(CFLAGS) -c $< -o $@

clean		:
		@echo "\033[32m[$(NAME)] Clean\033[0m"
		@rm -f $(OBJS)

fclean		:
		@echo "\033[32m[$(NAME)] Clean\033[0m"
		@rm -f $(OBJS)
		@rm -f $(NAME)

re			:		fclean all

.PHONY: all bonus clean fclean re