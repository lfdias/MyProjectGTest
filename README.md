# Install WSL in your machine (windows command line)
wsl --install
After this open WSL command line 

# GIT 
VERSION: git --version
INSTALL: sudo apt install git
REMOVE: sudo apt remove git


# STEP 1 - Cmake 
INSTALL: sudo apt install cmake=3.22.1-1ubuntu1.22.04.2
REMOVE: sudo apt remove --purge cmake

# STEP 2 - Google Tests
INSTALL: sudo apt install libgtest-dev=1.11.0-3
REMOVE: sudo apt remove --purge libgtest-dev

# Step 3 - Install project pre requirements
Go to project folder example "C:\Users\l.dias\Desktop\GIT_repositories\gtests_master>" and run the command:
pip install -r requirements.txt