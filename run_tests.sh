#!/bin/bash

usage="$(basename "$0") [-h] [-i test_file] [-o output_file] --- run tests

where:
    -h  show this help text
    -i  test file
    -o  expected output file";

while getopts 'hi:o:' option; do
  case "$option" in
    h) echo "$usage";
       exit 0;
       ;;
    i) test_file="$OPTARG";
       ;;
    o) output_file="$OPTARG";
       ;;
    :) printf "missing argument for -%s\n" "$OPTARG" >&2;
       echo "$usage" >&2;
       exit 1;
       ;;
   \?) printf "illegal option: -%s\n" "$OPTARG" >&2;
       echo "$usage" >&2;
       exit 1;
       ;;
  esac;
done;

shift $((OPTIND - 1));

if [ ! -f "$test_file" ]; then
    echo "test file $test_file is not a file...";
    exit 1;
fi

if [ ! -f "$output_file" ]; then
    echo "expected output file $output_file is not a file...";
    exit 1;
fi

echo "Compiling test.cpp...";
g++ test.cpp -o test;

echo "Generating test files...";
TMP_DIR="./.tmp";
mkdir "$TMP_DIR";
echo "STL" | cat > "$TMP_DIR/test_STL.in" && cat "$test_file" >> "$TMP_DIR/test_STL.in";
echo -e "Tree\nBS" | cat > "$TMP_DIR/test_BS.in" && cat "$test_file" >> "$TMP_DIR/test_BS.in";
echo -e "Tree\nAVL" | cat > "$TMP_DIR/test_AVL.in" && cat "$test_file" >> "$TMP_DIR/test_AVL.in";
echo -e "Tree\nSplay" | cat > "$TMP_DIR/test_Splay.in" && cat "$test_file" >> "$TMP_DIR/test_Splay.in";
echo -e "Tree\nTreap" | cat > "$TMP_DIR/test_Treap.in" && cat "$test_file" >> "$TMP_DIR/test_Treap.in";
echo "SkipList" | cat > "$TMP_DIR/test_SkipList.in" && cat "$test_file" >> "$TMP_DIR/test_SkipList.in";

for file in "$TMP_DIR"/*.in; do
    echo "Running test for $(basename ${file%.*})...";
    ./test < "$file" > "${file%.*}.out";
done;

RES_DIR="./results";
mkdir -p "$RES_DIR";
for file in "$TMP_DIR"/*.out; do
    echo "Checking expected output for $(basename ${file%.*})...";
    DIFF=$(diff "$output_file" "$file");
    if [ "$DIFF" == "" ]; then
	echo "All OK" | tee -a "$RES_DIR/$(basename ${file%.*})_$(date +"%Y%m%d%H%M%S").result";
    else
	echo "$DIFF" | tee -a "$RES_DIR/$(basename ${file%.*})_$(date +"%Y%m%d%H%M%S").result";
    fi;
done;

echo "Cleaning up...";
rm -rf "$TMP_DIR" test;

exit 0;
