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
mkdir ./tmp;
echo "STL" | cat > ./tmp/test_STL.in && cat "$test_file" >> ./tmp/test_STL.in;
echo -e "Tree\nBS" | cat > ./tmp/test_BS.in && cat "$test_file" >> ./tmp/test_BS.in;
echo -e "Tree\nAVL" | cat > ./tmp/test_AVL.in && cat "$test_file" >> ./tmp/test_AVL.in;
echo -e "Tree\nSplay" | cat > ./tmp/test_Splay.in && cat "$test_file" >> ./tmp/test_Splay.in;
echo -e "Tree\nTreap" | cat > ./tmp/test_Treap.in && cat "$test_file" >> ./tmp/test_Treap.in;
echo "SkipList" | cat > ./tmp/test_SkipList.in && cat "$test_file" >> ./tmp/test_SkipList.in;

for file in ./tmp/*.in; do
    echo "Running test for ${file%.*}...";
    ./test < "$file" > "${file%.*}.out";
done;

for file in ./tmp/*.out; do
    echo "Comparing files $output_file and $file...";
    diff "$output_file" "$file";
done;

echo "Cleaning up...";
rm -rf ./tmp test;

exit 0;
