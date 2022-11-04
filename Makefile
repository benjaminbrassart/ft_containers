# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 16:42:56 by bbrassar          #+#    #+#              #
#    Updated: 2022/11/04 16:53:04 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_STD = ./main_std
NAME_FT = ./main_ft

NAME = $(NAME_STD) $(NAME_FT)

CXX = c++
CXXFLAGS += -Wall
CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -std=c++98
CXXFLAGS += -I src/

SRC = main.cpp

all: $(NAME)

$(NAME_STD): $(SRC)
	$(CXX) $(CXXFLAGS) -DSTD $^ -o $@

$(NAME_FT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean fclean:
	rm -f $(NAME)

re: fclean all

ifndef COUNT
COUNT = 42
endif

run: $(NAME)
	@for i in `seq $(COUNT)`; do \
		$(NAME_STD) $$i > .tmp_std; \
		$(NAME_FT) $$i > .tmp_ft; \
		diff .tmp_std .tmp_ft || (echo "Failed at $i" >&2 && exit 1); \
	done
	@rm -f .tmp_std .tmp_ft

.PHONY: all clean fclean re run
