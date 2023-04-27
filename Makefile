#Compiler and Linker
CC          	= cc

#The Target Binary Program
NAME			= bin/philo

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR			= philo
INCDIR			= include
BUILDDIR		= obj
TARGETDIR		= bin
SRCEXT			= c
OBJEXT			= o

#Flags, Libraries and Includes
# CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=thread
CFLAGS      = -Wall -Wextra -Werror -g -O2
INCDEP      = -I$(INCDIR)

SOURCES     =	philo/free.c	\
				philo/actions.c	\
				philo/mutexes.c	\
				philo/philosophers.c	\
				philo/init_philosophers.c	\
				philo/utils.c	\
				philo/utils2.c	\
				philo/data.c	\
				philo/msg_queue.c	\
				philo/int_to_string.c	\
				philo/helper.c	\
				philo/print_data.c	\c
				philo/timing.c	\
				philo/work_load.c	\
				philo/dispatch.c	\
				philo/dispatch2.c	\
				philo/params.c	\
				philo/thread.c	\
				philo/special_cases.c	\
				philo/main.c	\

OBJECTS			= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(NAME)

#Remake
remake: cleaner all
	
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)	

fclean: clean
	@$(RM) -rf $(TARGETDIR)
	
re:	fclean all

$(NAME): $(OBJECTS) 
	@$(CC) $(CFLAGS) $(INCDEP) -o $(NAME) $^

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCDEP) -c -o $@ $<

.PHONY: all clean fclean re