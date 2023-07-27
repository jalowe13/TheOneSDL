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
