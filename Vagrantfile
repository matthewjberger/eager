# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://atlas.hashicorp.com/search.
  config.vm.box = "v0rtex/xenial64"


  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  config.vm.synced_folder ".", "/home/vagrant/Code/eager"

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  config.vm.provider "virtualbox" do |vb|
    # Display the VirtualBox GUI when booting the machine
    vb.gui = true

    # Customize the amount of memory on the VM:
    vb.memory = "2048"
  end

  # Enable provisioning with a shell script. Additional provisioners such as
  # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
  # documentation for more information about their specific syntax and use.
  #
  # This will install xfce, as well as build and install the ogre 3D library from source.
  config.vm.provision "shell", inline: <<-SHELL
    apt-get update
    apt-get upgrade
    apt-get install -y xfce4 virtualbox-guest-dkms virtualbox-guest-utils virtualbox-guest-x11
    sed -i 's/allowed_users=.*$/allowed_users=anybody/' /etc/X11/Xwrapper.config
    apt-get install -y libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev libcppunit-dev libboost1.58-* libois-dev mercurial cmake g++ gdb doxygen
    hg clone https://bitbucket.org/sinbad/ogre
	cd ogre
	hg pull
	hg update v1-9
	mkdir build
	cd build
	cmake ..
	make -j4
	make install
	cd ../../
	rm -rf ogre
  SHELL
end
