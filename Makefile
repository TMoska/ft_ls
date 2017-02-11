# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/09 17:36:12 by tmoska            #+#    #+#              #
#    Updated: 2017/02/11 19:49:07 by tmoska           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC 		= gcc
# GCC 		= clang -fsanitize=memory
NAME 		= ft_ls
FLAGS 		= -Wall -Werror -Wextra -g

LIB_PATH	= libft
LIB			= $(LIB_PATH)/libft.a
LIB_LINK	= -L $(LIB_PATH) -lft

INC_DIR 	= includes
ING_FILES = ft_ls.h
INC_FLAGS 	= -I./includes -I $(LIB_PATH)/includes

SRC_DIR 	= srcs
SRC_FILES 	= main.c listing.c failures.c directories.c printing.c \
	  		  do_single_directory.c dir_files.c sorting.c formatting.c \
	  		  print_file_permissions.c print_files_and_directories.c \
	  		  replacements.c options_printing.c bonus_options.c utils.c \
	  		  cleaning.c

SOURCES		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJECTS		= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJECTS)
	@$(CC) $(FLAGS) -o $@ $^ $(LIB_LINK)
	@echo "\033[0;32mSuccess: \033[0mft_ls compiled"
	@echo "\033[0;32mDone"

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c $(INC_DIR)/$(INC_FILES)
	@$(CC) $(FLAGS) $(INC_FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJECTS)
	@make clean -C $(LIB_PATH)

fclean: clean
	@rm -f $(NAME)
	@find . \( -name ".DS_Store" \) -delete
	@make fclean -C $(LIB_PATH)
	
re: fclean all
