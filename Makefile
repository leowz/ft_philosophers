
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zweng <zweng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 12:41:50 by zweng             #+#    #+#              #
#    Updated: 2023/05/09 16:50:23 by zweng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- varaibles -----

CC 				= gcc
NAME 			= philo
NAME_BI 		= $(NAME)/$(NAME)
BONUS_NAME 		= philo_bonus
BONUS_NAME_BI 	= $(BONUS_NAME)/$(BONUS_NAME)
LIB_NAME	 	= lib
HEADER_PATH 	= $(NAME)/includes
BHEADER_PATH	= $(BONUS_NAME)/includes
C_PATH 			= $(NAME)/srcs
BC_PATH 		= $(BONUS_NAME)/srcs
LIB_PATH 		= $(LIB_NAME)
OBJ_PATH		= obj/$(NAME)
BOBJ_PATH		= obj/$(BONUS_NAME)
LIBOBJ_PATH		= obj

# ---------------- transformation ------------------ #

HEADER 			= $(HEADER_PATH)/$(NAME).h

CFILES      	= $(notdir $(foreach D, $(C_PATH), $(wildcard $(D)/*.c)))
BCFILES     	= $(notdir $(foreach D, $(BC_PATH), $(wildcard $(D)/*.c)))
LIBCFILES     	= $(notdir $(foreach D, $(LIB_PATH), $(wildcard $(D)/*.c)))

OBJS_NAME		= $(patsubst %.c, %.o, $(CFILES)) 
BOBJS_NAME		= $(patsubst %.c, %.o, $(BCFILES)) 
LIBOBJS_NAME	= $(patsubst %.c, %.o, $(LIBCFILES)) 
DFILES_NAME		= $(patsubst %.c, %.d, $(CFILES)) 
BDFILES_NAME	= $(patsubst %.c, %.d, $(BCFILES))
LIBDFILES_NAME	= $(patsubst %.c, %.d, $(LIBCFILES))

LDFLAGS 		= -lpthread

DPFLAGS 		= -MD -MP 

CFLAGS 			=  $(foreach D, $(HEADER_PATH), -I$(D)) $(DPFLAGS) \
					-Wall -Wextra -Werror 
BCFLAGS 		=  $(foreach D, $(BHEADER_PATH), -I$(D)) $(DPFLAGS) \
					-Wall -Wextra -Werror 

DEBUGF 			= -fsanitize=address -g

# ----- part automatic -----
SRCS 		= $(addprefix $(C_PATH)/,$(CFILES)) 
BSRCS 		= $(addprefix $(BC_PATH)/,$(BCFILES)) 
LIBSRCS 	= $(addprefix $(LIB_PATH)/,$(LIBCFILES)) 
OBJS 		= $(addprefix $(OBJ_PATH)/,$(OBJS_NAME))
BOBJS 		= $(addprefix $(BOBJ_PATH)/,$(BOBJS_NAME))
LIBOBJS 	= $(addprefix $(LIBOBJ_PATH)/,$(LIBOBJS_NAME))
DFLS 		= $(addprefix $(OBJ_PATH)/,$(DFILES_NAME))
BDFLS 		= $(addprefix $(BOBJ_PATH)/,$(BDFILES_NAME))
LIBDFLS 	= $(addprefix $(LIBOBJ_PATH)/,$(LIBDFILES_NAME))

# ----- Colors -----
BLACK		:="\033[1;30m"
RED			:="\033[1;31m"
GREEN		:="\033[1;32m"
PURPLE		:="\033[1;35m"
CYAN		:="\033[1;36m"
WHITE		:="\033[1;37m"
EOC			:="\033[0;0m"
#  # ==================

# ----- part rules -----
all: $(NAME_BI) $(BONUS_NAME_BI)

$(NAME_BI): $(OBJS) $(LIBOBJS)
	@$(CC) $(OBJS) $(LIBOBJS) $(LDFLAGS) $(DEBUGF) -o $@
	@printf $(GREEN)"$(NAME) Finish linking\n"$(EOC)

$(BONUS_NAME_BI): $(BOBJS) $(LIBOBJS)
	@$(CC) $(BOBJS) $(LIBOBJS) $(LDFLAGS) $(DEBUGF) -o $@
	@printf $(GREEN)"$(BONUS_NAME) Finish linking\n"$(EOC)

$(LIBOBJ_PATH)/%.o:$(LIB_PATH)/%.c | $(OBJ_PATH)
	@printf $(GREEN)"compiling %s\n"$(EOC) $@
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)/%.o:$(C_PATH)/%.c | $(OBJ_PATH)
	@printf $(GREEN)"compiling %s\n"$(EOC) $@
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BOBJ_PATH)/%.o:$(BC_PATH)/%.c | $(BOBJ_PATH)
	@printf $(GREEN)"compiling %s\n"$(EOC) $@
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) 2> /dev/null

$(BOBJ_PATH):
	@mkdir -p $(BOBJ_PATH) 2> /dev/null

clean: 
	@rm -f $(OBJS) $(DFLS) $(BOBJS) $(BDFLS) $(LIBOBJS) $(LIBDFLS)
	@rm -rf obj 2> /dev/null
	@printf $(GREEN)"$(NAME) $(BONUS_NAME) clean\n"$(EOC)


fclean: clean
	@/bin/rm -f $(NAME_BI) $(BONUS_NAME_BI)
	@printf $(GREEN)"$(NAME) $(BONUS_NAME) fclean\n"$(EOC)

-include $(DFILES)
-include $(BDFILES)
-include $(LIBDFILES)

test:
	echo $(arg1)

re: fclean all

norme:
	@norminette $(SRCS)
	@norminette $(HEADER_PATH)/*.h

.PHONY: clean fclean re norme all philo philo_bonus
