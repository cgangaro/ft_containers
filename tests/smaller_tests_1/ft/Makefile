NAME			=		 test1_ft

HEADER			=		../incs/cam/iterator_traits.hpp \
						../incs/cam/reverse_iterator.hpp \
						../incs/cam/pair.hpp \
						../incs/cam/bidirectional_iterator.hpp \
						../incs/cam/BSTNode.hpp \
						../incs/cam/map.hpp \
						main.cpp \

CC				=		@clang++

CFLAGS			=		-Wall -Werror -Wextra

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