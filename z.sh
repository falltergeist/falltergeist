#cd lib/libfalltergeist
rm -f ./falltergeist
cmake .
make
#cd ../../
falltergeist > x.log
#falltergeist
