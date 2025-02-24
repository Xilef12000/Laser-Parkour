sudo apt update
sudo apt install python3-virtualenv
virtualenv --python=/usr/bin/python3 microPython
sudo apt-get install build-essential libreadline-dev libffi-dev git pkg-config gcc-arm-none-eabi libnewlib-arm-none-eabi
sudo apt install cmake
cd microPython/
source bin/activate
mkdir project
cd project/
git clone --recurse-submodules https://github.com/micropython/micropython.git
# 2992e3495630a8b83683db28241d638dbc53c911
cd micropython/mpy-cross/
make
cd ../ports/rp2/
make BOARD=RPI_PICO_W
# test build-RPI_PICO_W/firmware.uf2
cp -r ../../../../../lib-to-freeze/* modules/
make BOARD=RPI_PICO_W
# flash  build-RPI_PICO_W/firmware.uf2
