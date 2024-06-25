#!/bin/bash
python3.12 -m venv "SW/DMMvenv"
python -m pip install --upgrade pip
pip3 install -r ".\SW\DMM\requirements_rpi.txt"
ECHO "Finnished setting up venv for development"