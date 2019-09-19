# C++ - BinarySearchTree Class

The folder includes a templated binary search tree implemented accordingly to the exam requirements.

### Folder structure

- The **docs** folder contains the Doxyfile used to automatically generate the documentation. 
The Doxygen documentation is contained in two subfolders: **html** and **latex**.

- The **include/src** folder contains the implementation of the binary search tree class, called BST. 
The source code is organized as follows: the declaration of functions and member variables was put in *BST.h*, in order to preserve
clarity on the structure of the implementation. 
The file *BST_NestedClasses.hxx* contains the implementation of the subclasses together with their methods. Finally, the file *BST_Methods.hxx*
contains the methods of BST class.

- The **tests** folder contains the results of the tests made to ensure a correct behaviour for the BST class. The tests code is contained in the folder include/src, more precisely in the 
file *BST_Tests.cpp*. On the other hand, we measured the performances of our tree, file *BST_Performances.cpp* in include/src folder.
The subfolder **graphical_results** contains the plots of the performance analysis.

## Compilation and Execution

The Makefile has been created to automatically compile the BST code. In particular, the command
`make tests.o `
generates a *test.o* executable that encompasses all the tests we performed to the implementation of the BST class.

The command 
`make perfprmances.o `
generates a benchmark.o executable that measures the performances of my implementation (the execution time is quite long).

The command `make docs` generates the documentation inside the docs folder. 

The command `make` performs all the commands above. 
