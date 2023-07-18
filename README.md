# TheOneSDL
 The One created with C++ and SDL2
 Tileset Game Engine Prototype made with SDL2 and C++

# Jacob Lowe

# Instructions to compile

# Environment Variables to add
Search environment variables in your search bar then click Environment Variables
Then click new under system variables for each of the following

C:\msys64\mingw64\bin

# Step 1: Install MSYS2 to install MinGW for C++ compiler
https://www.msys2.org/
Install Msys2

# Step 2: Run the setup.ps1 script in an Admin Terminal/Powershell to install Chocolatey and MinGW with dependencies
Open a Admin Terminal/Powershell and navagate to the game directory of TheOneSDL that contains dll files
You could copy your path from the file explorer and paste it in the path if you'd like
```
cd (your game path here)
```
Then run the script with the following (The execution bypass is for temporarily running scripts)
```
PowerShell -ExecutionPolicy Bypass
.\setup.ps1
```

# Compile Instructions stated in the setup script

Compiles program
`
```
make
```
Cleans up all object files (use this if you edit code in a header file or delete a specific object file you edited)
```
make cleanall
```
You can also this if the command doesn't work
```
del /Q *.o
```
Execute program
```
.\TheOne.exe
```
