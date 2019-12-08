# vimhook.bufferoutput.wrap_mode = wrap
# vimhook.bufferoutput.filetype = log

CPP_FILE=${1##*/}
OUTPUT_FILE=${CPP_FILE%.cpp}
OUTPUT_DIR="./dist/${1%/*}"

mkdir -p $OUTPUT_DIR

echo "OUTPUT_DIR=${OUTPUT_DIR}"
echo "OUTPUT_FILE=${OUTPUT_FILE}"
g++-8 $1 -o ${OUTPUT_DIR}/${OUTPUT_FILE} && ./${OUTPUT_DIR}/${OUTPUT_FILE}
# g++-8 $1 -Wl,--verbose -H -v -o ${OUTPUT_DIR}/${OUTPUT_FILE} && ./${OUTPUT_DIR}/${OUTPUT_FILE}
