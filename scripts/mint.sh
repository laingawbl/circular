
./scripts/get_source_files.sh
test $? -eq 0 || { echo "could not get source files"; exit 1; }

cp cmake/SourceLists.{,official.}cmake