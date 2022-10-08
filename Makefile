# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 06:45:18 by bbrassar          #+#    #+#              #
#    Updated: 2022/10/08 06:49:10 by bbrassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_TEST = test
SCRIPT=$(DIR_TEST)/test.sh

all: vector map stack

vector map stack:
	$(SCRIPT) $@

.PHONY: clean fclean
clean fclean:
	@$(SCRIPT) $@

.PHONY: re
re: fclean all
