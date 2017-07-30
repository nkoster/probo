This is a very simple TEST virus program that runs in Linux.

* This is a DANGEROUS experiment - Use only in a secured lab setup!

#### Bootstrap procedure

````
g++ -O -Wall -std=c++11 hi.cpp -o hi
g++ -O -Wall -std=c++11 v.cpp -o v_tmp && cat v_tmp hi >v && chmod +x v
ls -l v_tmp
````

Make sure the size of `v_tmp` is `MYSIZE` in the `v.cpp` source. Do another

````
g++ -O -Wall -std=c++11 v.cpp -o v_tmp && cat v_tmp hi >v && chmod +x v
````

#### Start

Run the virus bootstrap executable in a directory that contains other executables:

````
./v
````

This will infect one executable per run, until all files are infected.

Infected files run like normal. The orginal code will be executed by the virus code.

By default, only executables in the current directory are infected.

Imagine what will happen when the default will be `/bin/`, runing as root or with sudo rights.

#### To Do

* Use the original file's time-stamp for the infected file
* Add a fixed list of programs that will be attacked
