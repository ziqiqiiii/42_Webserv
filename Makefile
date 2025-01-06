####### MAKEFILE #######

### Variables

SRCS_PATH		=	./srcs/
OBJS_PATH		=	./objs/
HEAD_PATH		=	./includes/

FILES			=	main.cpp \
					$(addprefix Client/, Socket.cpp)
					
HEAD_FILES		=	Socket.hpp

SRCS			=	${addprefix ${SRCS_PATH}, ${FILES}}
OBJS			=	${addprefix ${OBJS_PATH}, ${FILES:.cpp=.o}}
DEPS			=	${addprefix ${OBJS_PATH}, ${FILES:.cpp=.d}}
HEAD			=	${addprefix ${HEAD_PATH}, ${HEAD_FILES}}

NAME			=	webserver

CC				=	g++
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -std=c++98


### Commandes

all:			${NAME}

${NAME}:		${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${OBJS_PATH}%.o:	${SRCS_PATH}%.cpp
				mkdir -p ${dir $@}
				${CC} -c ${CFLAGS} -MMD -MP -I${HEAD_PATH} $< -o $@

clean:
				${RM} ${OBJS_PATH}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

test: all
	./$(NAME) 3 5 9 7 4
-include : ${DEPS}

uml: 
	dot -Tpng http_server_uml.dot -o http_server_uml.png

.PHONY:			all clean fclean re