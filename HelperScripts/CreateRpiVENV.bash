#!/bin/bash
python3.11 -m venv "SW/DMMvenv" 
python -m pip install --upgrade pip --break-system-packages
pip3 install -r "SW/DMM/requirements_rpi.txt"