# Readme

## About

This is a randomized algorithm for computing a lower bound on the clique number of a graph.

* DCS = "Deterministic Clique Search"
* DHCS = "Deterministic Hyperclique Search"
* RCS = "Randomized Clique Search"
* RHCS = "Randomized Hyperclique Search"

## Running

### Compilation:

```
$ make all
```

### Graphs

Works with standard dimacs files:

```
$ ./dcs benchmarks/brock800_4.clq 3 12

OK! 207643 Pairs Have Been Read
799 800
Clique: 13 | 15 56 61 264 276 282 292 401 415 467 477 619 752
Time: 0.169433
```


### Hypergraphs

Currently these programs only work on 3-uniform hypergraphs, specified as in a text file as a list of edges:

```
1 2 3
1 2 6
1 2 7
1 2 8
1 2 9
1 2 10

...
14 32 53
```
where each line represents an edge in the hypergraph of vertices 1, 2, ..., n.

With the deterministic algorithm there is no stopping criterion:

```
$ ./dhcs benchmarks/t136.txt

3912 1304 Triples Have Been Read
25 26 27
min: 7 max: 27
min: 11 max: 26
min: 13.7577 max: 25
min: 13.7577 max: 24
min: 12.7361 max: 23
min: 11.7103 max: 22
min: 14.9257 max: 21
min: 14.9257 max: 20
min: 14.9257 max: 19
min: 14.851 max: 18
min: 13.9197 max: 17
min: 14.7759 max: 16
min: 15 max: 15

Clique: 15 | 10 11 12 13 14 16 18 19 20 21 22 23 25 26 27
Time: 0.000127
```


With the randomized algorithm you can specify the size of clique to search for:

```
$ ./rhcs benchmarks/t136.txt 12

3912 1304 Triples Have Been Read
Table: 28
done = 0  se.size = 405420  max = 6
done = 0  se.size = 330494  max = 9
Solution found of length 12!
10 12 14 16 18 19 20 21 22 25 26 27
done = 1  se.size = 1328  max = 12
Time: 0.721758
```
