# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/27 01:32:08 by bbrassar          #+#    #+#              #
#    Updated: 2022/11/03 00:52:23 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers

CXX = c++
CXXFLAGS += -Wall
CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -std=c++98 -pedantic
CXXFLAGS += -g3
CXXFLAGS += -c
CXXFLAGS += -MMD -MP
CXXFLAGS += -I $(DIR_SRC)
CXXFLAGS += $(shell cat .include_path)

LABEL_COMPILE = COMPILE
LABEL_LINK = LINK
LABEL_REMOVE = REMOVE
LABELS = $(LABEL_COMPILE) $(LABEL_LINK) $(LABEL_REMOVE)

LABEL_MAX_LENGTH = $(shell echo "$(LABELS)" | tr ' ' '\n' | awk '{ print length($0) }' | sort -rn | head -n 1)

RM = rm -f

FT = ft
STD = std

DIR_SRC = src

DIR_OBJ = obj
DIR_OBJ_FT = $(DIR_OBJ)/$(FT)
DIR_OBJ_STD = $(DIR_OBJ)/$(STD)

DIR_BIN = bin
DIR_BIN_FT = $(DIR_BIN)/$(FT)
DIR_BIN_STD = $(DIR_BIN)/$(STD)

SRC = $(patsubst $(DIR_SRC)/%,%,$(wildcard $(DIR_SRC)/**/*.cpp))

OBJ = $(SRC:%.cpp=%.o)

OBJ_FT = $(OBJ:%=$(DIR_OBJ_FT)/%)
OBJ_STD = $(OBJ:%=$(DIR_OBJ_STD)/%)

.PRECIOUS: $(DIR_OBJ)/%.o

BIN = $(SRC:%.cpp=%.out)

BIN_FT = $(BIN:%=$(DIR_BIN_FT)/%)
BIN_STD = $(BIN:%=$(DIR_BIN_STD)/%)

-include $(OBJ_FT:.o=.d) $(OBJ_STD:.o=.d)

.PHONY: all
all: $(NAME)

.PHONY: $(NAME)
$(NAME): $(OBJ_FT) $(BIN_FT) $(OBJ_STD) $(BIN_STD)

.PHONY: $(FT)
$(FT): $(OBJ_FT) $(BIN_FT)

.PHONY: $(STD)
$(STD): $(OBJ_STD) $(BIN_STD)

$(DIR_OBJ_FT)/%.o: $(DIR_SRC)/%.cpp
	@printf -- '│ %-*s │ %s\n' "$(LABEL_MAX_LENGTH)" "$(LABEL_COMPILE)" "$(patsubst $(DIR_OBJ)/%,%,$@)"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -I $(<D) $< -o $@

$(DIR_OBJ_STD)/%.o: $(DIR_SRC)/%.cpp
	@printf -- '│ %-*s │ %s\n' "$(LABEL_MAX_LENGTH)" "$(LABEL_COMPILE)" "$(patsubst $(DIR_OBJ)/%,%,$@)"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -I $(<D) -DSTD $< -o $@

$(DIR_BIN)/%.out: $(DIR_OBJ)/%.o
	@printf -- '│ %-*s │ %s\n' "$(LABEL_MAX_LENGTH)" "$(LABEL_LINK)" "$(patsubst $(DIR_BIN)/%,%,$@)"
	@mkdir -p $(@D)
	@$(CXX) $< -o $@

.PHONY: clean
clean:
	@printf -- '│ %-*s │ %s\n' "$(LABEL_MAX_LENGTH)" "$(LABEL_REMOVE)" "$(DIR_OBJ)"
	@$(RM) -r $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	@printf -- '│ %-*s │ %s\n' "$(LABEL_MAX_LENGTH)" "$(LABEL_REMOVE)" "$(DIR_BIN)"
	@$(RM) -r $(DIR_BIN)

.PHONY: re
re: fclean all

.PHONY: dump
dump:
	@echo $(SRC)
