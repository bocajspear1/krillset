#!/bin/sh

echo "\e[31m"
cat << EOF
  _  __     _ _ _  _____      _   
 | |/ /    (_) | |/ ____|    | |  
 | ' / _ __ _| | | (___   ___| |_ 
 |  < | '__| | | |\___ \ / _ \ __|
 | . \| |  | | | |____) |  __/ |_ 
 |_|\_\_|  |_|_|_|_____/ \___|\__|

EOF
echo "\e[0m"

DIR=metasploit

echo "Building Metasploit samples..."
echo "--------------------------------------"
echo "Output will be in \e[32m${DIR}/out\e[0m"
echo ""--------------------------------------""
cd ${DIR}
mkdir -p ./out
rm ./out/*
DOCKER_BUILDKIT=1 docker build --target artifact --output type=local,dest=. .
cd ..