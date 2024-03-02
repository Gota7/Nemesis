docker run --env-file toolchains/$1.env -v "$(pwd):/Nemesis" --rm -it $(docker build -q . )
sudo chown -R $USER:$USER build
sudo chown -R $USER:$USER bin