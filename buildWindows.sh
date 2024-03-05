mkdir -p bin
cp -R ./res bin/res
./buildCore.sh windows
zip -r -q bin/Nemesis_Windows.zip bin