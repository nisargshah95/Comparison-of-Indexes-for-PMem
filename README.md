# Comparison of Indexes for PMem

## Install PMDK on Ubuntu 18.04
1. Install NDCTL - https://docs.pmem.io/persistent-memory/getting-started-guide/installing-ndctl#installing-ndctl-packages-on-linux
    `sudo apt-get install libndctl-dev libndctl6 ndctl`

2. Install PMDK - https://docs.pmem.io/persistent-memory/getting-started-guide/installing-pmdk/installing-pmdk-using-linux-packages#installing-pmdk-using-the-linux-distro-package-repository

    * All Runtime: 
`sudo apt-get install libpmem1 librpmem1 libpmemblk1 libpmemlog1 libpmemobj1 libpmempool1`

    * All Development: 
`sudo apt-get install libpmem-dev librpmem-dev libpmemblk-dev libpmemlog-dev libpmemobj-dev libpmempool-dev libpmempool-dev`

    * All Debug:
`sudo apt-get install libpmem1-debug librpmem1-debug libpmemblk1-debug libpmemlog1-debug libpmemobj1-debug libpmempool1-debug`

## Build BzTree
1. Install latest CMake
```
wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4-Linux-x86_64.sh
chmod +x cmake-3.18.4-Linux-x86_64.sh
./cmake-3.18.4-Linux-x86_64.sh --skip-license --include-subdir --prefix=/usr/local
export PATH=$PATH:/usr/local/cmake-3.18.4-Linux-x86_64/bin
```
2. Build BzTree
```
git clone https://github.com/sfu-dis/bztree.git
cd bztree
```
&nbsp;&nbsp;&nbsp;&nbsp;In CMakeLists.txt:

&nbsp;&nbsp;&nbsp;&nbsp;Line 73 - Change to `GIT_REPOSITORY https://github.com/sfu-dis/pmwcas.git`

&nbsp;&nbsp;&nbsp;&nbsp;Line 86 - Change to `GIT_REPOSITORY https://github.com/sfu-dis/pibench.git`

&nbsp;&nbsp;&nbsp;&nbsp;Line 172 - Change to `set(PMDK_LIB_PATH "/usr/lib/x86_64-linux-gnu" CACHE STRING "PMDK lib install path")`
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DPMEM_BACKEND=PMDK -DGOOGLE_FRAMEWORK=0 -DBUILD_TESTS=0 ..
make
```
    If make fails, open `pmwcas/src/PMWCAS/CMakeLists.txt` from the build directory:
    Line 270 - Change to `set(PMDK_LIB_PATH "/usr/lib/x86_64-linux-gnu" CACHE STRING "PMDK lib install path")`
```
rm -rf pmwcas/src/PMWCAS-build/*
make
```
