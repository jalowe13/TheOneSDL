# Jacob Lowe
# Dev setup script

# Install Chocolatey
if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
}

# Install make using Chocolatey
choco install make -y

# Set the path to the vcpkg executable
$vcinstall = $env:USERPROFILE
$vcpkg = $env:USERPROFILE + "/vcpkg"

# Install jsoncpp using vcpkg
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
Write-Host "Installing packages..." -ForegroundColor Green
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
cd $vcinstall
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
cd $vcpkg 
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install sdl2 sdl2-ttf sdl2-image --triplet x64-windows
cd $PSScriptRoot

Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
Write-Host "Compiling program for the first time..." -ForegroundColor Green
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
make
# vcpkg install jsoncpp
Write-Host
Write-Host 
Write-Host  
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
Write-Host "Install complete! Press any key to close the window." -ForegroundColor Green
Write-Host "You can now compile program by using the command" -ForegroundColor Yellow
Write-Host "> make"
Write-Host "You make also delete all compiled files by typing" -ForegroundColor Yellow
Write-Host "> make cleanall"
Write-Host "Launch the game by typing the following or just click the exe in the directory" -ForegroundColor Yellow
Write-Host "> .\TheOne.exe"
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
Pause
exit
