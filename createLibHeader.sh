INC_DIR="include"
for inc_file in "$INC_DIR"/*
do
	echo -n "#include <LuEngineCPP/" >> LuEngine.hpp
	echo -n "${inc_file##*/}" >> LuEngine.hpp
	echo ">" >> LuEngine.hpp
done
