GREEN=\033[32m
YELLOW=\033[33m
RED=\033[31m
BLUE=\033[34m
BACK=\033[42m
BOLD=\033[1m
RESET=\033[0m


CPP = c++

CPPFLAGS = -Wall -Werror -Wextra -std=c++98 -g

DFLAGS = -MD -MP

MAKEFLAGS = -j$(nproc) --no-print-directory

RM = rm -rf

NAME = RPN

SRCS = main.cpp RPN.cpp

OBJSDIR = objs

OBJS = $(addprefix ${OBJSDIR}/, ${SRCS:.cpp=.o})

DEPS = $(addprefix ${OBJSDIR}/, ${SRCS:.cpp=.d})


all: ${NAME}

$(NAME): $(OBJS)
		@${CPP} ${CPPFLAGS} ${DFLAGS} -o $@ $^
		@echo "${BACK}${RED}${BOLD} Successfuly built ${NAME} ${RESET}"

${OBJSDIR}/%.o : %.cpp
		@mkdir -p ${dir $@}
		@echo "${BLUE}${BOLD}Compiling $<${RESET}"
		@${CPP} ${CPPFLAGS} ${DFLAGS} -c $< -o $@

clean:
		@echo "${YELLOW}${BOLD}Deleting object files${RESET}" 
		@${RM} ${OBJSDIR}

fclean: clean
		@echo "${RED}${BOLD}Deleting executable${RESET}"
		@${RM}	${NAME} 

re:		fclean
		${MAKE} all

-include ${DEPS}

.PHONY:	all clean fclean re