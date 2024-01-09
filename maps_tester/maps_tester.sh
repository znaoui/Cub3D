#!/bin/bash

os=$(uname)
RED='\033[0;31m'
ORANGE='\033[0;33m'
GREEN='\033[0;32m'
WHITE='\033[0m'

test_map()
{
	echo -e "$1 : ${ORANGE}...${WHITE}\c"
	result=$(../cub3D "$1" 2>&1)
	if [[ "$result" == "Error parsing map"* ]] || [[ "$result" == "Fatal error"* ]]; then
		echo -e " ${GREEN}OK${WHITE}"
	else
		echo -e " ${RED}FAIL${WHITE}"
	fi
	echo -e "$1 ${ORANGE}LEAKS${WHITE} : ${ORANGE}...${WHITE}\c"
	if [ "$os" = "Darwin" ]; then
		leaks --atExit -- ../cub3D "$1" > leaks_result 2>&1
		leak=$(cat leaks_result | grep LEAK);
		if [ "$leak" = "" ]; then
			echo -e " ${GREEN}OK${WHITE}"
		else
			echo -e " ${RED}FAIL${WHITE}"
		fi
	else
		valgrind -- ../cub3D "$1" > leaks_result 2>&1
		leak=$(cat leaks_result | grep "ERROR SUMMARY: 0");
		if [ "$leak" != "" ]; then
			echo -e " ${GREEN}OK${WHITE}"
		else
			content=$(<leaks_result)
			echo "$content" >> leaks_logs
			echo -e " ${RED}FAIL${WHITE}"
		fi
	fi
}

rm -rf leaks_logs
make -C ../

if [ "$?" != "0" ]; then
	echo -e "${RED}COMPILATION FAILED${WHITE}"
else
	if [ "$os" = "Darwin" ] || [ "$os" = "Linux" ]; then
		for i in *.cub*; do
			test_map "$i"
		done
	rm -rf ./leaks_result
	fi
fi
