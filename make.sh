LIBS="-lSDL2 -lm -lSDL2_image -lSDL2_ttf -lSDL2_mixer"
OPTS="-std=c99 -Wall"
INC_DIR="-Iinc/"
FILES="*.c"
OUT_NAME="game"

gcc $FILES $INC_DIR $LIBS $OPTS -o $OUT_NAME
