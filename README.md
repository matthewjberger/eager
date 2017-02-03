# Eager
An Ogre3D/C++ project template that uses cmake to generate a makefile.

You can fork this repo and work on the files in the source directory.

# Building your Project

Check the prerequisites section if anything fails here.

#### GNU Make (Linux)

First, clone the repo (or fork it!):

```bash
git clone https://github.com/matthewjberger/eager		
```		

Then to build, use [CMake](https://cmake.org/):

```bash
cd eager
mkdir build
cd build
cmake ..
```    

Your project can then be found in the `bin` directory.

# Vagrant

This will generate an ubuntu virtual machine with eclipse and the Ogre3D library built from source and installed.

1.) [Install Vagrant](https://www.vagrantup.com/downloads.html)

2.) [Install Virtualbox](https://www.virtualbox.org/wiki/Downloads)

3.) Clone this repo with:

```bash
git clone https://github.com/matthewjberger/eager 
cd eager
```

4.) Enter the following command: 

```bash
vagrant up
```
> Username: `vagrant`

> Password: `vagrant`

The virtual machine will be downloaded and then opened in virtual box. You can login with the password `vagrant`. The files in this repo are in the folder `~/Code/eager` which is also shared with the host.

####Note: If there is an issue with the mouse while running a 3D program that captures the mouse, hit `ctrl+home` and then go to `input->mouse integration` and disable it. This can be re-enabled when you're finished running the program.

# Prerequisites

####Note: If you're using NoMachine at the University of Nevada, Reno, the following steps are not required. The library has already been built from source and installed on NoMachine.

Ogre 3D must be installed. If it isn't installed you should build it from the source with the following commands.  Mercurial is required to clone the repo.


#### Ubuntu (or any Debian-Based Linux distribution)

Download the required dependencies:

``` bash
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev libcppunit-dev libboost1.58-* libois-dev mercurial cmake g++ gdb doxygen
```

Clone the repo and grab version 1.9:
```bash
hg clone https://bitbucket.org/sinbad/ogre
cd ogre
hg pull
hg update v1-9
```

Use cmake to generate a makefile:

```bash
mkdir build
cd build
cmake ..
```

Build OGRE:
```bash
make -j5
```

Install the library:
```bash
sudo make install
```
