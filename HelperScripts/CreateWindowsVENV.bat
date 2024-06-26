ECHO "Starting setting up venv for development"
python3.12 -m venv "SW\DMMvenv"
SW\DMMvenv\Scripts\activate.bat
python.exe -m pip install --upgrade pip
pip3 install -r ".\SW\DMM\requirements.txt"
ECHO "Finnished setting up venv for development"