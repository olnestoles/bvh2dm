BIN2=BvhConv
OBJ_DIR = objs
MKDIR = mkdir -p

EIGEN_DIR = /usr/include/eigen3

INC = -I./ \
	-I$(EIGEN_DIR)

CC = clang++
CFLAGS2 = -std=c++11 -O3 -g -Wall -fPIC 

SRC_DIRS = lib/json/

SRC_FILES2 = main.cpp Motion.cpp KinTree.cpp SpAlg.cpp RBDUtil.cpp Shape.cpp Rand.cpp MathUtil.cpp JsonUtil.cpp FileUtil.cpp BVHReader.cpp $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)*.cpp))
OUT_DIRS = $(addprefix $(OBJ_DIR)/, $(SRC_DIRS))
OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(SRC_FILES)))
OBJ2 = $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(SRC_FILES2)))

default: build

build: $(BIN2)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) -c -g $(CFLAGS2) $(INC) -o $@ $<
	
$(BIN2): $(OUT_DIRS) $(OBJ2)
	$(CC) -g $(CFLAGS2) $(OBJ2) $(LIBS) -o $@

$(OUT_DIRS):
	$(MKDIR) $(OUT_DIRS)
	
clean:
	- rm -f -r $(OUT_DIRS) $(BIN) $(OBJ) $(OBJ_DIR) BvhConv
