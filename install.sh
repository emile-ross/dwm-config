#!/usr/bin/env bash

bold=$(tput bold)
undr=$(tput smul)
ends=$(tput sgr0)

# TODO: make a printing function with the standard format used
# ( simplifies the program with less variables {bold} & {ends} )

print_step(){
	echo "${bold}${undr}Step $1 / 3${ends}"
}

# compiles a program using the makefile
build(){
	cd $2
	make install
	if [ $? -eq 0 ]
	then
		echo "${bold}${undr}Compiled $1 successfully${ends}"
	else
		echo "${bold}${undr}Errors during $1 compilation. Check the compilation log.${ends}"
		cd ..
		exit
	fi
	cd ..
}

# check for root privileges
if [ "$EUID" -ne 0 ]
then 
	echo "${bold}${undr}Elevated privileges are needed for installing any package${ends}"
	exit 1
fi

# install dependencies
print_step 1
pacman -S base-devel xorg-server libx11 libxft git xorg-xinit

print_step 2
echo -n "INFO: "
if ! command -v yay >/dev/null 2>&1 
then
	echo -e "${bold}${undr}yay could not be found\nInstalling yay...${ends}"
	# install yay here
	git clone https://aur.archlinux.org/yay.git
	cd yay/
	makepkg -si
	cd ..
else
	echo "${bold}${undr}yay was found${ends}"
fi

print_step 3
# building st & dwm
build dwm dwm/
build st st/

# building dwl
sudo mkdir -p /etc/ly/custom-sessions
build dwl dwl/
cp dwl/dwl.desktop /etc/ly/custom-sessions/dwl-custom.desktop

# get the username and convert it to a home directory
USER_HOME=$(getent passwd "$SUDO_USER" | cut -d: -f6)
cp dwl/startup-dwl.sh "$USER_HOME/.local/bin/dwl-startup"

echo "Installation is complete"

