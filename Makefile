SRCS = philo.c \
		libft_tools.c \
		parser.c \
		linked_listF.c \
		log.c \
		tools.c \

OBJS = ${SRCS:.c=.o}


NAME = philo

FLAGS = -Wall -Wextra -Werror  #-g -fsanitize=address


all : $(NAME)

$(NAME) : ${OBJS}
		@gcc  ${OBJS} -g -o$(NAME) -pthread
		@rm -f ${OBJS} 


clean :
		@rm -f ${OBJS}
fclean : clean
		@rm -f $(NAME)
re : fclean
		make all

		# gcc checker.c list_utils.c comds.c get_next_line.c get_next_line_utils.c helpers.c helpers2.c
