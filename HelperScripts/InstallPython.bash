# https://raspberrytips.com/install-latest-python-raspberry-pi/
# Install python on raspberry pi 5b
sudo apt update && sudo apt upgrade -y
wget https://www.python.org/ftp/python/3.12.4/Python-3.12.4.tgz
tar -xf Python-3.12.4.tgz
cd Python-3.12.4
./configure --enable-optimizations
make -j 4
sudo make altinstall
