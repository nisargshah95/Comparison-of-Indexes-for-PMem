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
```
git clone https://github.com/sfu-dis/bztree.git
cd bztree
mkdir build & cd build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DPMEM_BACKEND=PMDK -DGOOGLE_FRAMEWORK=0 -DBUILD_TESTS=0 ..
make
```
