CC		=	g++

RM		= 	rm -rf

SRC_DIR	=	src/

SRC_BOMBS_DIR	=	src/Bombs/

SRC_BONUS_DIR	=	src/Bonus/

SRC_INTERFACE_DIR=	src/Interface/

SRC_IA_DIR      =   ia/

LUA_DIRECTORY   =   $(SRC_IA_DIR)lua-5.3.2/src

IRRLICHT_DIR	=	Irrlicht/irrlicht-1.8.3

SRC		=	$(SRC_DIR)main.cpp						\
			$(SRC_DIR)IrrlichtController.cpp				\
			$(SRC_DIR)Intro.cpp		                		\
			$(SRC_DIR)AGameObject.cpp					\
			$(SRC_DIR)Player.cpp						\
			$(SRC_DIR)ACharacter.cpp					\
			$(SRC_DIR)Wall.cpp						\
			$(SRC_DIR)BomberMap.cpp						\
			$(SRC_DIR)EventGame.cpp						\
			$(SRC_DIR)AController.cpp					\
			$(SRC_DIR)MotionController.cpp					\
			$(SRC_DIR)KeysController.cpp					\
			$(SRC_DIR)GameManager.cpp					\
			$(SRC_DIR)Texture.cpp						\
			$(SRC_DIR)GameObjectTimeContainer.cpp				\
			$(SRC_DIR)Props.cpp						\
			$(SRC_DIR)Color.cpp						\
			$(SRC_DIR)SoundManager.cpp					\
			$(SRC_DIR)AGameObjectFactory.cpp				\
			$(SRC_DIR)Ranking.cpp                           		\
			$(SRC_DIR)WallOfEnd.cpp						\
			$(SRC_DIR)DangerMap.cpp                         		\
			$(SRC_DIR)WallOfDead.cpp					\
			$(SRC_DIR)LoadHighScore.cpp					\
			$(SRC_DIR)HighScore.cpp						\
			$(SRC_INTERFACE_DIR)PlayerSelectionBox.cpp 			\
			$(SRC_INTERFACE_DIR)KeySelectionBox.cpp 			\
			$(SRC_INTERFACE_DIR)UIEventReceiver.cpp 			\
			$(SRC_INTERFACE_DIR)UIManager.cpp				\
			$(SRC_INTERFACE_DIR)PlayerSelectionBoxContainer.cpp		\
			$(SRC_INTERFACE_DIR)PlayerInfo.cpp				\
			$(SRC_INTERFACE_DIR)GameOver.cpp 		        	\
			$(SRC_INTERFACE_DIR)MapSelectionBox.cpp 		        	\
			$(SRC_IA_DIR)IAPlayer.cpp   					\
			$(SRC_IA_DIR)LuaFunctions.cpp					\
			$(SRC_IA_DIR)LuaBomberMap.cpp                   		\
			$(SRC_IA_DIR)LuaGameObjectArray.cpp             		\
			$(SRC_IA_DIR)LuaVector2.cpp                     		\
			$(SRC_BOMBS_DIR)ABomb.cpp					\
			$(SRC_BOMBS_DIR)BombContainer.cpp				\
			$(SRC_BOMBS_DIR)AtomicBomb.cpp					\
			$(SRC_BOMBS_DIR)FragBomb.cpp					\
			$(SRC_BOMBS_DIR)MineBomb.cpp					\
			$(SRC_BOMBS_DIR)MiniBomb.cpp					\
			$(SRC_BOMBS_DIR)TrackerBomb.cpp					\
			$(SRC_BOMBS_DIR)FireBomb.cpp					\
			$(SRC_BOMBS_DIR)Explosion.cpp					\
			$(SRC_BONUS_DIR)ABonus.cpp					\
			$(SRC_BONUS_DIR)AItem.cpp					\
			$(SRC_BONUS_DIR)BonusSpeed.cpp					\
			$(SRC_BONUS_DIR)BonusPower.cpp					\
			$(SRC_BONUS_DIR)BonusFragBomb.cpp				\
			$(SRC_BONUS_DIR)BonusAtomicBomb.cpp				\
			$(SRC_BONUS_DIR)BonusTrackerBomb.cpp				\
			$(SRC_BONUS_DIR)BonusFireBomb.cpp				\
			$(SRC_BONUS_DIR)BonusBombPass.cpp				\
			$(SRC_BONUS_DIR)BonusBiggestMan.cpp				\
			$(SRC_BONUS_DIR)BonusSmallestMan.cpp				\
			$(SRC_BONUS_DIR)BonusInvincible.cpp				\
			$(SRC_BONUS_DIR)ItemThrow.cpp					\
			$(SRC_BONUS_DIR)ItemMineBomb.cpp				\

OBJ			=	$(SRC:%cpp=%o)

NAME		=	bomberman

BinPath 	=	./

DESTPATH 	=	$(BinPath)/$(NAME)$(SUF)

CPPFLAGS	=	-W -Wall -Wextra -Werror -std=c++11 -pthread

CPPFLAGS	+=	 -Wno-unused-parameter -Wno-unused-variable

CPPFLAGS	+=	-I$(IRRLICHT_DIR)/include -I./include

CPPFLAGS	+=	-I$(SRC_IA_DIR) #delete when ia in SRC

CPPFLAGS	+=	-I./fmod/inc

#-I/usr/X11R6/include

CPPFLAGS	+=	-O3 -ffast-math

LDFLAGS 	=   -lpthread

LDFLAGS 	+=  -L $(IRRLICHT_DIR)/lib/$(SYSTEM) -lIrrlicht

DEBUG   = no

INSTALL = no

ifeq ($(DEBUG),yes)
    CPPFLAGS  +=  -D DEBUG
endif

ifneq ($(INSTALL),no)
    CPPFLAGS  +=  -DBINDIR='"$(INSTALL)"'
endif

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

$(NAME)	:	$(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(DESTPATH)
	@echo -e "\033[0;33m${NAME} Compiled\033[0;00m"

install:
	./install.sh

all	:	$(NAME)

clean 	:
	@echo -e "\033[0;31mRemoving Objects\033[0;00m"
	@$(RM) $(OBJ)

fclean	:	clean
	@echo -e "\033[0;31mRemoving ${NAME}\033[0;00m"
	@$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re install

ifeq ($(OS),Windows_NT)
SYSTEM=Win32-gcc
SUF=.exe
CPPFLAGS    +=  -D_IRR_STATIC_LIB_
LDFLAGS     +=  -lgdi32 -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lopengl32 -ld3dx9d -lwinmm -lm
LDFLAGS     +=  -lm -static-libstdc++
LDFLAGS		+=	lua53.dll
else
LDFLAGS 	+= -L/usr/X11R6/lib$(LIBSELECT) -lGL -lXxf86vm -lXext -lX11 -lXcursor
LDFLAGS 	+=  -L./fmod/lib/x86_64 -Wl,-R./fmod/lib/x86_64 -lfmod
LDFLAGS 	+=  -L $(LUA_DIRECTORY) -llua
LDFLAGS		+= -ldl
SYSTEM=Linux
endif

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif
