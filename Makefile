#Compiler and Linker
CC          	:= cc

#The Target Binary Program
NAME			:= bin/philo

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR			:= src
INCDIR			:= include
BUILDDIR		:= obj
TARGETDIR		:= bin
SRCEXT			:= c
OBJEXT			:= o

#Flags, Libraries and Includes
# CFLAGS      := -Wall -Wextra -Werror -g -fsanitize=thread
CFLAGS      := -Wall -Wextra -Werror -g -O2
INCDEP      := -I$(INCDIR)


SOURCES     :=	src/free.c	\
				src/mutexes.c	\
				src/philosophers.c	\
				src/utils.c	\
				src/data.c	\
				src/msg_queue.c	\
				src/helper.c	\
				src/print_data.c	\
				src/timing.c	\
				src/work_load.c	\
				src/params.c	\
				src/thread.c	\
				src/main.c	\

OBJECTS			:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(NAME)

#Remake
remake: cleaner all
	
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)
	@$(RM) $(NAME)

fclean: clean
	@$(RM) -rf $(TARGETDIR)
	
re:	fclean all

#Link
$(NAME): $(OBJECTS) 
	@$(CC) $(CFLAGS) $(INCDEP) -o $(NAME) $^

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCDEP) -c -o $@ $<

.PHONY: all clean fclean re