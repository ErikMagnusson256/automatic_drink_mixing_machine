#!/bin/bash
python3.12 -m venv "SW\DMMvenv"
SW\DMMvenv\Scripts\activate.bat
python.exe -m pip install --upgrade pip
pip3 install -r ".\SW\DMM\requirements_rpi.txt"
ECHO "Finnished setting up venv for development"