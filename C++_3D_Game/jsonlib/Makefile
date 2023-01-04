##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## [MAYEUL]: no_my_get_one_line, no return_nb_how
##

# COLOR CODE #
RED			=	\e[91m
BLUE		=	[39m[38;5;33m
TURQUOISE	=	\e[96m
GREEN		=	\e[32m
BLINK_RED	=	\e[91;5m
BOLD_GREEN	=	\e[32;1m
NO_BLINK	=	\e[25m
VIOLET		=	[39m[38;5;63m
END			=	\e[0m
VERTCLAIR	=	[39m[38;5;155m
ORANGE		=	[39m[38;5;220m
NUAGE		=	[39m[38;5;153m
ROUGE_SANS 	=	[39m[38;5;196m
BLEU_FONCER	=	[39m[38;5;12m
JAUNE		=	[39m[38;5;226m
ROSE		=	[39m[38;5;198m
POURPRE		=	[39m[38;5;183m

# PRINT MODE #

CREATE_FILST_TIME = echo -e "$(BLUE)** CREATE FIRST TIME LIB **$(END)"
CREATE_FILST_TIME_END = echo -e "$(BLUE)** CREATE FIRST TIME LIB END **$(END)"

VPATH = src:./
VPATH += src/Type:./

SRC+=

include ./constant/.src.mk $(SRC)

HEADERS_DIR	= include include/Exeption include/Type

ADD_HEADERS_DIR = $(addprefix -I./, $(HEADERS_DIR))

CXXFLAGS	+= 	$(ADD_HEADERS_DIR) -Wall -W -Wextra -std=c++2a -fPIC -g3

FIND_TMP = $(shell find . -type d | grep build)

PROJECT := $(shell realpath .)

USER := $(shell whoami)

AR								=	ar rc

NAME							=	libmy.a

RM								=	rm -f

define test_fonctionnel =
#!/bin/bash
	ret_test=0
	font_black_purple="\033[38;5;13m"
	font_normal="\033[40;37;0m"
	font_big_noir_bleu_foncer="\033[38;5;33;1m"

	if [ -e tmp_find_error ]; then
		test -s tmp_find_error
		ret_test=$(echo $?)
		# echo -e $ret_test
		if [ $ret_test -eq 0 ]; then
			echo -e "${font_black_purple}** NOFINK TO DO LIB **${font_normal}"
		else
			echo -e "${font_big_noir_bleu_foncer}** SOMEFINK WAS MODIFIE LIB **${font_normal}"
		fi
	fi
endef

vpath %.o build

OBJ	= $(SRC:.cpp=.o)

all : $(NAME)

%.o:	%.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $< && (echo -e "\e[32m[OK]\033[0m\e[1m\e[32m" "$(BLUE)" "$(CXXFLAGS)" "\e[32m" $< "\033[0m") || (echo -e "\e[91;5m[KO]\e[25m" $<)

check_tmp_file :	$(FIND_TMP) $(OBJ)
	@if [ ! -d "build" ]; then mkdir build/; mv $(OBJ) build/; ${CREATE_FILST_TIME_END}; $(RM) tmp_find_error; else mv -f *.o build 2> tmp_find_error; true; fi

is_create_tmp: $(FIND_TMP)
	@if [ ! -d "build" ]; then $(CREATE_FILST_TIME); fi

run_makefile:
	@echo -e "$(ROSE)_____$(JAUNE)BEGIN MAKEFILE: $(BLEU_FONCER)$(PROJECT)$(ROSE)_____$(END)"

stop_makefile:
	@echo -e "$(ROSE)_____$(JAUNE)END MAKEFILE: $(BLEU_FONCER)$(PROJECT)$(ROSE)_____ $(POURPRE)$(USER)$(END)"

compile:	$(OBJ)
	@$(AR) $(NAME) $(addprefix build/, $(OBJ)) && (echo -e "$(VERTCLAIR)ar rc $(ORANGE) $(NAME) $(NUAGE) $(addprefix build/, $(OBJ))")

$(NAME): run_makefile is_create_tmp $(OBJ) check_tmp_file rite_test compile stop_makefile

clean:
	@$(RM)	$(NAME)
	@$(RM) 	tmp_find_error

fclean: clean
	@rm -rf build

rite_test: ; @$(value test_fonctionnel)
	@$(RM) 	tmp_find_error

.ONESHELL:

.PHONY	:	rite_test fclean clean is_create_tmp check_tmp_file