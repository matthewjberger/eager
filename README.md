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
# Prerequisites

####Note: If you're using NoMachine at the University of Nevada, Reno, the following steps are not required. The library has already been built from source and installed on NoMachine.

Ogre 3D must be installed. If it isn't installed you should build it from the source with the following commands.  Mercurial is required to clone the repo.


#### Ubuntu (or any Debian-Based Linux distribution)

Download the required dependencies:

``` bash
sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev libcppunit-dev libboost1.58-* libois-dev mercurial cmake g++ gdb
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
