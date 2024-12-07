LIBS="-lm -lraylib -lGL -lpthread -ldl -lrt -lX11"
OPTS="-std=c99 -Wall"
INC_DIR="-Iinc/"
FILES="*.c"
OUT_NAME="game"

gcc $FILES $INC_DIR $LIBS $OPTS -o $OUT_NAME
