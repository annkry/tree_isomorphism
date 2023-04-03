# tree_isomorphism
To determine whether two n-vertex trees T1 and T2 are isomorphic. The sets of vertices of these trees are denoted by V(T1) and V(T2), respectively. These trees are isomorphic if there exists a bijection f: V(T1) → V(T2) such that for any two vertices u and v in V(T1), they are connected by an edge in T1 if and only if f(u) and f(v) are connected by an edge in T2.  

It is worth to mention that a program that always outputs "YES" (or a program that always outputs "NO") would give many correct answers. Therefore, the input is grouped together; a single test contains multiple instances of the problem described above. The first line of the input contains a single natural number D (1 ≤ D ≤ 20) indicating the number of instances given.  


`input specification`  
The first line contains a single natural number 2 ≤ n ≤ 5 * 105, which is the number of vertices in each of the trees. The vertices are numbered with natural numbers from 1 to n. The next n-1 lines contain the description of tree T1, and the following n-1 lines contain the description of tree T2. Each of the rows describing a tree contains a pair of natural numbers a and b separated by a single space. These numbers satisfy 1 ≤ a ≠ b ≤ n, indicating that there is an edge between vertices a and b in the tree.  

`output specification`  
The program will output D lines. The i-th line will contain the word "YES" if the trees specified in the i-th instance are isomorphic, and "NO" otherwise.


To compile: `g++ -std=gnu++17 -static -DSPRAWDZACZKA main.cpp`  
To run: `./a.out`  
