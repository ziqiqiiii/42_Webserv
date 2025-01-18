####### MAKEFILE #######

### Variables

SRCS_PATH		=	srcs/
OBJS_PATH		=	objs/
HEAD_PATH		=	includes/

# Finds every header in the src directory
FILES			=	$(shell find $(SRCS_PATH) -name '*.cpp')

#Finds every directory and subdirectories in include directory and adds -I
INCLUDES		=	$(addprefix -I, $(shell find $(HEAD_PATH) -type d))

OBJS			=	$(patsubst $(SRCS_PATH)%.cpp, $(OBJS_PATH)%.o, $(FILES))
DEPS			=	$(patsubst $(SRCS_PATH)%.cpp, $(OBJS_PATH)%.d, $(FILES))

NAME			=	webserver

CC				=	c++
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -std=c++98

### Commandes

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.cpp
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -MMD -MP $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
				$(RM) $(OBJS_PATH)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re