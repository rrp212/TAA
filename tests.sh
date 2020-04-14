#!/bin/bash

TEMP_DIR="temp"
RES_DIR="results"
TEST_CPP="test.cpp"
TEST_OUT="test.out"
GEN_OUT="gen.out"
DS_NAMES=("STL" "Tree\nBS" "Tree\nAVL" "Tree\nSplay" "Tree\nTreap" "SkipList")

print_usage() {
    echo -e "Usage: $0 OPTION FILE1 FILE2
    Test data structures or generate expexted output file according to STL implementation.\n
    -r\tFILE1 is test input and FILE2 is expected output
    -g\tFILE1 is test input and FILE2 is output
    -h\tShow usage\n"
}

check_input() {
    if [ "$#" -ne 2 ]; then
	echo "Error: no input files"
	print_usage
	exit 1
    else if [ ! -f "$1" ]; then
	     echo "Error: $1 not a file"
	     print_usage
	     exit 1
	 else if [ ! -f "$2" ]; then
		  echo "Error: $2 not a file"
		  print_usage
		  exit 1
	      fi
	 fi
    fi
}

create_tmp() {
    echo "Creating directories..."
    mkdir -p "$TEMP_DIR"
    mkdir -p "$RES_DIR"
}

compile_test() {
    echo "Compiling $TEST_CPP..."
    g++ "$TEST_CPP" -o "$TEMP_DIR/$TEST_OUT"
}

make_tests() {
    echo "Making tests..."
    for ds in "${DS_NAMES[@]}"; do
	OUTPUT="${ds//Tree\\n}_$(basename $1)"
	echo -e "$ds" | cat > "$TEMP_DIR/$OUTPUT" \
	    && cat "$1" >> "$TEMP_DIR/$OUTPUT" \
	    && echo "$OUTPUT"
    done
}

try_tests() {
    echo "Running tests..."
    for file in "$TEMP_DIR"/*.in; do
	OUTPUT="${file%.*}.output"
	echo "$(basename $OUTPUT)"
	(time "./$TEMP_DIR/$TEST_OUT" < "$file" > "$OUTPUT") 2>&1 | tee -a "$OUTPUT"
	# add space
    done
}

check_tests() {
    echo "Generating results..."
    for file in "$TEMP_DIR"/*.output; do
	echo "Checking if expected output matches for $(basename $file)..."
	OUTPUT="$RES_DIR/$(basename ${file%.*})_$(date +"%Y%m%d%H%M%S").result"
	TIME="$(tail -n 3 $file)"
	(head -n -4 "$file") > "$TEMP_DIR/content"
	echo "$TIME" > "$OUTPUT"
	DIFF="$(diff $1 $TEMP_DIR/content)"
	if [ "$DIFF" == "" ]; then
	    echo "All OK" | tee -a "$OUTPUT"
	else
	    echo "$DIFF" | tee -a "$OUTPUT"
	fi
    done
}

create_test() {
    "./$TEMP_DIR/$TEST_OUT" < "$1" > "$2"
}

cleanup() {
    echo "Cleaning up..."
    rm -rf "$TEMP_DIR"
}

run_tests() {
    check_input "$1" "$2"
    create_tmp
    compile_test
    make_tests "$1"
    try_tests
    check_tests "$2"
    cleanup
}

gen_test() {
    check_input "$1" "$1"
    create_tmp
    compile_test
    create_test "$1" "$2"
    cleanup
}

while getopts "hrg" option; do
    case "$option" in
	h) print_usage
	   ;;
	r) run_tests "$2" "$3"
	   ;;
	g) gen_test "$2" "$3"
	   ;;
	\?) echo "illegal option: -$option"
	    print_usage
	    exit 1
	    ;;
    esac
done

if [ "$OPTIND" -eq 1 ]; then
    echo "Error: no options"
    print_usage
fi
exit 0
