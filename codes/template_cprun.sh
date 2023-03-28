# alias cprun="/home/cprun.sh"
PROG_NAME=$1
OUT_NAME="${PROG_NAME%.*}"
g++ -std=c++17 -DLOCAL $PROG_NAME -o $OUT_NAME.out
if [[ $? == 0 ]]; then
    ./$OUT_NAME.out
fi
