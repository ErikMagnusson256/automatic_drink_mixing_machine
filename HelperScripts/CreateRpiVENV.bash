#!/bin/bash
python3.11 -m venv "SW/DMMvenv" 
source SW/DMMvenv/bin/activate
python -m pip install --upgrade pip --break-system-packages
pip3 install -r "SW/DMM/requirements_rpi.txt" --break-system-packages
source SW/DMMvenv/bin/activate