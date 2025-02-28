# Install WSL in your machine (Windows command line)
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




#####################
#####################
#####################
#####################




The installation will complete. You will be in the Linux shell.

run: (Note: you will probably be prompted for your password when you run this command; it's the password you just defined as part of the installation of WSL). 
```
sudo apt-get update
```


# Step 2: Verify that GIT is installed. 
In the Linux shell, run: 
```
git --version
```

If you get a response (something like "git version 2.34.1") - it means git is installed and you can skip to step 3. 
If the response is something like "-bash: /usr/bin/git: No such file or directory"), it means you need to install git: 
```
sudo apt install git
```

To copy the tutorial files from git, you will need to have a Personal Access Token. Here is how to generate a Personal Access Token:

- Log into your git account via a browser
- Go to your GitHub account settings: Click on your username icon at the top-right and select "Settings"

- Navigate to Developer settings > Personal access tokens -> Tokens (classic).

- Click on Generate new token -> Generate new token (classic).
  - Add a Note (something to tell you what this token is for)
  - Select the expiration time ("No Expiration" is NOT recommended from security point of view).
  - Don't change any other settings and scroll to the bottom.
  - Click Generate token
  - Copy the token and save it somewhere. This is the only time you can copy and save the token - so do it!


# Step 3 - Install Cmake 
In the Linux shell, run: 
```
sudo apt install cmake=3.22.1-1ubuntu1.22.04.2
```


# Step 4 - Install Google gtest
In the Linux shell, run: 
```
sudo apt install libgtest-dev=1.11.0-3
```

# Step 5 - Install pip
In the Linux shell, run: 
```
sudo apt install python3-pip
```


# Step 6 - Clone the tutorial code
In the Linux shell, run: 
```
git clone https://github.com/lfdias/gtests_master.git
```

You will be prompted for your GitHub username and password... BUT!!! Instead of using the password, paste your Personal Access Token. 

In the Linux shell, run: 
```
ls
```

You should see a folder named "gtests_master" listed. 



# Step 7 - Install project pre requirements
In the Linux shell, run: 
```
cd ~/gtests_master
pip install -r requirements.txt
```

# Step 8 - Add items to your PATH
In the Linux shell, run: 
```
cd ~
nano ~/.bashrc
```

This will open a text editor. Navigate with the down-arrow to the bottom of this file and add the following line at the end of the file:

export PATH="$HOME/.local/bin:$PATH"

Save and exit by pressing CTRL+X, then Y, and Enter.

Apply the changes immediately by running:

```
source ~/.bashrc
```
