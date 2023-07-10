# TheOneSDL
 The One created with C++ and SDL2
 Tileset Game Engine Prototype made with SDL2 and C++

# Jacob Lowe

# Instructions to compile

# Environment Variables to add
Search environment variables in your search bar then click Environment Variables
Then click new under system variables for each of the following

C:\msys64\mingw64\bin

C:\ProgramData\chocolatey\bin

# Install MSYS2 to install MinGW
https://www.msys2.org/
Open Msys2
Install MinGW with the following command. This will install the compiler that the make file will use
```
pacman -S mingw-w64-x86_64-gcc
```

# Install Chocolatey in an Admin Powershell
```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```
Once chocolatey is installed install make
# Install make in a new command prompt
```
choco install make -y
```


# Compile Program with make and execute
Navigate to where you downloaded and extracted TheOne to
Compiles program
`
```
make
```
Cleans up all object files (use this if you edit code in a header file or delete a specific object file you edited)
```
make clean
```
Execute program
```
.\TheOne.exe
```
