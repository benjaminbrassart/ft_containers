# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/18 01:49:14 by bbrassar          #+#    #+#              #
#    Updated: 2022/09/06 05:08:06 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
# CXXFLAGS += -Werror
CXXFLAGS += -c
CXXFLAGS += -MMD -MP
CXXFLAGS += -std=c++98
CXXFLAGS += -I$(DIR_SRC)
CXXFLAGS += -I$(DIR_CONTAINERS)

ifeq ($(DEBUG), true)

CXXFLAGS += -g3
CXXFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address

endif

NAME = ft_containers

DIR_CONTAINERS = src
DIR_SRC = test

SRC = main.cpp
OBJ = $(SRC:%.cpp=$(DIR_SRC)/%.o)
DEP = $(OBJ:.o=.d)

$(NAME): $(OBJ)
	c++ $^ -o $@ $(LDFLAGS) $(LDLIBS)

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
