# gcc 4.8
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y

#clang 3.6
curl -sSL "http://llvm.org/apt/llvm-snapshot.gpg.key" | sudo -E apt-key add -
echo "deb http://llvm.org/apt/precise/ llvm-toolchain-precise-3.6 main" | sudo tee -a /etc/apt/sources.list > /dev/null
#sudo add-apt-repository llvm-toolchain-precise-3.6 -y

# sdl2
sudo add-apt-repository ppa:zoogie/sdl2-snapshots -y

sudo apt-get update -qq
sudo apt-get install -qq libsdl2-dev
sudo apt-get install -qq libsdl2-mixer-dev
sudo apt-get install -qq libsdl2-image-dev
sudo apt-get install -qq libglew1.6-dev
sudo apt-get install -qq libglm-dev
sudo apt-get install -qq mesa-common-dev


if [ "$CXX" = "clang++" ]; then sudo apt-get install -qq clang-3.6; fi
if [ "$CXX" = "clang++" ]; then export CXX="clang++-3.6" CC="clang-3.6"; fi
if [ "$CXX" = "g++" ]; then sudo apt-get install -qq g++-4.9; fi
if [ "$CXX" = "g++" ]; then export CXX="g++-4.9" CC="gcc-4.9"; fi
