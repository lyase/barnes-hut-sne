Barnes-Hut-SNE v0.1
-------------------------------------------
© Laurens van der Maaten
Delft University of Technology, 2012
===========================================


DESCRIPTION

This code contains a C++ implementation of Barnes-Hut-SNE as described in the corresponding paper. Please cite this paper whenever you use this code.

The code also contains a Matlab wrapper for the C++ code (fast_tsne.m). Please refer to the help text in fast_tsne.m for more information on the input format for the data. Based on the code in fast_tsne.m, it is straightforward to develop wrappers in other programming languages.


COMPILATION

Compilation of the files is relatively straightforward, but requires a working installation of CBLAS. Please refer to the compile_mac and compile_linux shell scripts to see the required compilation command. Note that paths may be different on your machine, so may have to be changed in order for the files to compile.


LEGAL 

You are free to use, modify, or redistribute this software in any way you want, but only for non-commercial purposes. The use of the software is at your own risk; the authors are not responsible for any damage as a result from errors in the software. 


CONTACT
If you encounter problems with the implementations or have questions about Barnes-Hut-SNE, make sure you read the paper and the online FAQ first! If your question is not answered afterwards, feel free to send me an email at: lvdmaaten@gmail.com

USAGE OF BRANCH   https://github.com/lyase/barnes-hut-sne.git
build bh_tsne with cmake
install required build dependency tested for ubuntu 12.10 & 14.04 
sudo apt-get install git cmake build-essential gfortran libatlas-dev libvtk6-dev swig python-dev
cd /tmp; 
git clone https://github.com/lyase/barnes-hut-sne.git
cd barnes-hut-sne/
rm -rvf build ; mkdir build ; cd build ;  cmake .. ; make ; make test ; cd ..

NOW create data.dat with points  in dim 20;
cd build ./makedata ; cd ..
./makedata=> will create data.dat
try bh_tsne on data.dat => reads data.dat => creates result.dat
cd build; ./bh_tsne
