# linux_setup.sh - Setup script for linux
# Copyright (C) [2024] [Jacob Lowe]
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>
# Jacob Lowe
# Setup for Linux

# This resets the path back to the script file location
SCRIPT_PATH=$(dirname $(realpath "$0"))

echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "Installing git and base-devel"
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
sudo pacman -Syu --noconfirm base-devel git
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "Installing git and base-devel"
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
sudo pacman -Syu --noconfirm base-devel git
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "Installing yay"
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
cd /opt
sudo git clone https://aur.archlinux.org/yay-git.git
sudo chown -R $USER ./yay-git
cd yay-git
makepkg -si --noconfirm

echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "Installing Packages..."
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
sudo pacman -Syu --noconfirm make boost cmake gcc jsoncpp
sudo yay -S --noconfirm sdl2 sdl2_image sdl2_ttf
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "Compiling program for the first time..."
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo Setting SDL_VIDEODRIVER to wayland or x11
export SDL_VIDEODRIVER=wayland,x11
echo The Current Graphics Driver is "$SDL_VIDEODRIVER"
cd $SCRIPT_PATH
sudo make
echo
echo
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "Install complete! Press any key to close the window."
echo "You can now compile program by using the command"
echo "> make"
echo "You make also delete all compiled files by typing"
echo "> make cleanall"
echo "Launch the game by typing the following or just click the exe in the directory"
echo "> ./TheOne"
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
