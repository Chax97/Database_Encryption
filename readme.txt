
****************************** read me *******************************

[1] all assignment info will be inside ASSIGNMENT_INFO folder
    - add whatever text info or notes related to the assignment into this folder

[2] your individual .c files
    - we will all work on our individual designated code in the [yourname].c files
    - how this will work? we'll designate people to work on certain FUNCTIONS for the whole
      program, which will be called in the main.c file - 
            1. write your function prototype ONLY in the header.h file
            2. then copy that function prototype without the ; into your .c file and write
               the function code in your .c file, as well as the block comment for it.
            3. compile to see if your code works
    - to see if your INDIVIDUAL .c code COMPILES only, look at the very top of your .c file,
      i've written a compilation code for you to copy paste to do it for you.
    - NOTE: this will only compile your code and show you any errors in your code to fix, it
      won't make a [yourname].out file for you to see your output. Keep editing your code until
      it compiles with ZERO errors (there will be no error messages).
    - to see your code output, we will have to compile every .c file together using "make" and
      then execute ./main.out

[3] how to use makefile:
    - type "make" into the terminal to compile all .c files together and produce a main.out
    - type "./main.out" to see the output of the main.c (basically the whole program)
    - type "make clean" to clean up all the .o files (and main.out) that are made.
            - we'll have to "make clean" and "make" again to see any changes within main.c
            - any changes in any other .c file doesn't need to be "make clean"ed and changes
              can be updated just by typing "make" again.

[4] do's and don't's
    - DO NOT edit the makefile
    - DO NOT change any .c filenames
    - DO NOT delete any .c files
    - DO NOT delete the ASSIGNMENT_INFO folder (please)
    - DO add any new information you feel is relevant into a .txt file inside the ASSIGNMENT_INFO folder,
      or into an already existing .txt file where appropriate.
    - please do not last minute your code and thus delay the group, let us know if there's anything you
      can't do or need help with.
    - DO help each other out whenever someone is stuck, and DO let us know if you need help anywhere.



