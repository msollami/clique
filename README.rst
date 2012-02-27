========
Clique
========

This is a randomized algorithm for computing a lower bound on the clique number of a graph.

* DCS = "Deterministic Clique Search"
* DHCS = "Deterministic Hyperclique Search"
* RCS = "Randomized Clique Search"
* RHCS = "Randomized Hyperclique Search"


Running
============
* Compilation
    $ g++ DCS.cpp -O3 -o DCS
    $ g++ DHCS.cpp -O3 -o DHCS
    $ g++ RCS.cpp -O3 -o RCS
    $ g++ RHCS.cpp -O3 -o RHCS

* Works with standard dimacs files
    $ ./program file samples clique
    $ ./DCS ./benchmarks/brock800_4.clq 3 12


Benchmarks
========
Graph			best O/Omega
brock800_4.clq		12/26
wap07a.col	        38/?	
keller5.clq		/27

{{"dsjc1000.1.col", 20, None}, {"dsjc1000.5.col", 83, 
   None}, {"dsjc1000.9.col", 223, None}, {"dsjc250.5.col", 28, 
   None}, {"dsjc500.1.col", 12, None}, {"dsjc500.5.col", 48, 
   None}, {"dsjc500.9.col", 126, None}, {"dsjr500.1c.col", 84, 
   84}, {"dsjr500.5.col" 122, 122}, {"flat1000_50_0.col" 50, 
   50}, {"flat1000_60_0.col" 60, 60}, {"flat1000_76_0.col", 82, 
   76}, {"flat300_26_0.col", 26, 26}, {"flat300_28_0.col", 28, 
   28}, {"latin_square.col" 98, None}, {"le450_15c.col", 15, 
   15}, {"le450_15d.col", 15, 15}, {"le450_25c.col", 25, 
   25}, {"le450_25d.col", 25, 25}};

* https://github.com/msollami/Clique