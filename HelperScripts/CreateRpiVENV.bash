#!/bin/bash
python3.11 -m venv "SW/DMMvenv" --break-system-packages
python -m pip install --upgrade pip
pip3 install -r "SW/DMM/requirements_rpi.txt" 
ECHO "Finnished setting up venv for development"