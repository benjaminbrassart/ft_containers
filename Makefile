# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/18 01:49:14 by bbrassar          #+#    #+#              #
#    Updated: 2022/08/18 02:20:34 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++
CXXFLAGS += -Wall
CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -c
CXXFLAGS += -MMD -MP
CXXFLAGS += -g3
CXXFLAGS += -I$(DIR_SRC)
CXXFLAGS += -I$(DIR_CONTAINERS)

NAME = ft_containers

DIR_CONTAINERS = src
DIR_SRC = test

SRC = main.cpp
OBJ = $(SRC:%.cpp=$(DIR_SRC)/%.o)
DEP = $(OBJ:.o=.d)

$(NAME): $(OBJ)
	c++ $^ -o $@

$(DIR_SRC)/%.o: $(DIR_SRC)/%.cpp
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
