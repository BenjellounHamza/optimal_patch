# optimal_patch
I constract an optimal patch that transform a source file to a target file. The term optimal here means that the patch generated by my algorithm contains the smallest operations that transform a file to another.
for example if we wont to transform this source file to this target file:

the source file contains: <br/>
S1 <br/>
S2 <br/>
S3 <br/>

and target file contains: <br/>

S1 <br/>
T1 <br/>
T2 <br/>

we have different way we can do : <br/>
+ 1 T1 <br/>
+ 1 T2 <br/>
- 2 S2 <br/>
- 3 S3 <br/>
or <br/>
= 1 T1 <br/>
= 1 T2 <br/>
as we see, each of this two patch have different cost.
Let us present the cost of each instruction in the patch befor begin:

The operation "+k\nL_new\n" which means the addition of the line L_new of the source file after the line k in the target file. (it costs 10 + the size of L_new). <br/>

The operation "=k\nL_old\nL_new\n" that replaces the line k: L_old in the target file with L_new (it costs 10 + the size of the L_new). <br/>

The operation "-k\nL_old\n" that remove the line K : L_old from the target file (it costs 10). <br/>

Note:<br/>
We can changes the cost of this different operation in the algorithm easly if we wont.<br/>

the algorithm use the dynamic programmation that based on the following Bellman Equation:<br/>
f(i,j) = min(f(i,j-1) + C(i,j), f(i-1, j-1) + 10 + size_of_L_j, f(i-1, j) + 10)


