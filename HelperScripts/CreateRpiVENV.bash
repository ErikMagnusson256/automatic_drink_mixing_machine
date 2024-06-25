#!/bin/bash
python3.11 -m venv "SW/DMMvenv"
python -m pip install --upgrade pip
pip3 install -r "SW\DMM\requirements_rpi.txt" --break-system-packages
ECHO "Finnished setting up venv for development"