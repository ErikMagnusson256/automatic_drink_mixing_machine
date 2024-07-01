#!/bin/bash
sudo apt install libxcb-cursor0

chmod +x GUI/UI/screen1.ui
chmod +x GUI/UI/screen2.ui

sudo apt-get install -y liblgpio-dev
sudo ldconfig
git clone --depth=1 https://github.com/endail/hx711
cd hx711
make && sudo make install