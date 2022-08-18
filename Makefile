# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/18 01:49:14 by bbrassar          #+#    #+#              #
#    Updated: 2022/08/18 02:02:42 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++
CXXFLAGS += -Wall
CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -c
CXXFLAGS += -MMD -MP
CXXFLAGS += -g3

NAME = ft_containers

DIR_SRC = test

SRC = main.cpp
OBJ = $(SRC:%=%.o)
DEP = $(OBJ:.o=.d)

$(NAME): $(OBJ:%=$(DIR_SRC)/%)
	c++ $^ -o $@

$(DIR_SRC)/%.o: $(DIR_SRC)/%
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

-include $(DEP)

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	$(RM) -r $(OBJ) $(DEP)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
