mkdir -p build
cp -R ./res build/res
cp ./shell.html build/shell.html
./buildCore.sh web
zip -r -q docs/Nemesis_Web.zip docs
mv docs/Nemesis.html docs/index.html