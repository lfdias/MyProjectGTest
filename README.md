# General
Please follow the instructions below to install the tutorial BEFORE YOU ARRIVE to the tutorial. We strongly suggest you do this a few days before the conference, so you have some time to deal with installation issues, if you encounter any. 
We will not spend time in the tutorial on installations, and arriving with a PC that is not ready would mean you will spend much of the tutorial time on mundane installations. 
If you encounter problems installing, try first Google, ChatGPT, Microsoft CoPilot or your favourite knowledge source. If all else fails, contact the tutorial owner Luis Dias  at l.dias@andersenlab.com

#############
## Windows ##
#############

# Pre-requisites  

The instructions below assume the following:
- You are running Windows 10 or 11 (the instructions were tested on Windows 11)
- You have an internet connection
- You have a github account.
   --> If not: Go to https://github.com/signup and create one.


# Step 1: Install WSL on your machine
- Open a Windows command shell ("cmd") and run the following command. It will take a few minutes to complete. 
```
wsl --install -d Ubuntu-22.04
```

When the installation is complete, it will prompt you to define a username and a password. Remember your username and password - you may need them in the future. 

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

In order to copy the tutorial files from git, you will need to have a Personal Access Token. Here is how to generate a Personal Access Token:

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

You will be prompted for your GitHub username and password... BUT!!! instead of the password, paste your Personal Access Token. 

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



#############
### Linux ###
#############


