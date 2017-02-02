# Eager
An ogre c++ project template that uses premake to generate a makefile.

# Building your Project

Check the prerequisites section if anything fails here.

#### GNU Make (Linux)
```bash
git clone https://github.com/matthewjberger/eager your-project-name
cd your-project-name
./premake5 gmake
````

For a debug build:

```bash
make -C build
```

Your project can then be found in the `bin/debug` directory.

If you want a release build:
```bash
make -C build config=release
```
# Vagrant

This will generate an ubuntu virtual machine with XFCE and the ogre 3D library installed.

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

The virtual machine will be downloaded and then opened in virtual box. You can login with the password `vagrant`. The files in this repo are in the folder `~/Code/eager~` which is also shared with the host.

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

Build OGRE concurrently:
```bash
make -j4 # The -j switch tells make to use multiple threads, speeding up the build a bit.
```

Install the library:
```bash
sudo make install
```
