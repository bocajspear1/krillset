#!/bin/sh
echo ""
echo "==========================="
echo "\e[31mRequires builder to run\e[0m"
echo "==========================="

./run_builder.sh

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

cp ./builder/out/test.x86-64.exe ./packer/test.x86-64.exe
cp ./builder/out/test.x86.exe ./packer/test.x86.exe

DIR=packer

echo "Packing samples..."
echo "--------------------------------------"
echo "Output will be in \e[32m${DIR}/out\e[0m"
echo ""--------------------------------------""
cd ${DIR}
mkdir -p ./out
rm ./out/*
DOCKER_BUILDKIT=1 docker build --target artifact --output type=local,dest=. .
cd ..