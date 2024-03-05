mkdir -p bin
cp -R ./res bin/res
./buildCore.sh linux
zip -r -q bin/Nemesis_Linux.zip bin