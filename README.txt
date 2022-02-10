COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.
    Algorithms Project 1 - RSA
    Author: Jacen Conlan (jcc126@uakron.edu)
    Version: 1.10 02.09.2022
    Purpose: This README covers the important things to know for Algorithms Project 1 - RSA

C++ Big Integer Library and README at: https://mattmccutchen.net/bigint/
sha256 code can be found at: http://www.zedwood.com/article/cpp-sha256-function

The code for this project can be found at: https://github.com/jaccon236/Algorithms_435_RSA_Encryption

% Part 1 - rsa435
    Purpose:
        This program generates the necessary values (listed below) needed for basic RSA encryption and stores them in text files for future access. 
            p: a randomly generated prime number with at least 155 digits (512 bits)
            q: a randomly generated prime number with at least 155 digits (512 bits)
            n: the product of p and q, used for the modulo of signature encryption and decryption
            phi: the product of (p-1) and (q-1); used for calculation of e and d
            e: an odd integer that is relatively prime to phi
            d: the multiplicitive inverse of e modulo(phi)

    Compilation:
        To compile rsa435.cc multiple files are required. This README assumes you have a C++ compiler installed and are able to utilize Makefiles. 
            If this project has been accessed via GitHub, you may skip to step 3.

     1) Put rsa435.cc in the same directory as most of the files from Matt McCutchen's C++ Big Integer Library. 
        The files that are not needed are:
            .gitignore.txt
            ChangeLog
            run-testsuite
            sample.cc
            testsuite.cc

     2) Edit Makefile from the Big Integer Library (You can also create your own Makefile as long as you know how to do this properly)
            1) Change line 52 to be "program = rsa534"
            2) Change line 53 to be "program-objects = rsa435.o"
            3) (Optional) Remove lines 30 through 44 (these lines are used for test-suite which is not needed)
            4) If you are using a Window's machine replace "rm" in line 65 with "del"

     3) Once all required files are in the same directory, run the "make" command or it's equivalent on your system to build the project.
            You may see multiple warnings regarding depreciated code. This is due to the age of the C++ Big Integer Library and they can be ignored.

     4) Assuming everything has been done correctly, the object files for the Big Integer Library, rsa435.o, and rsa435.exe should appear in the directory.
            If they have not, verify that you have followed all of the steps correctly. If you are still having issues, email me any questions you may have.

    Execution:
        Arguments: This program only requires the name of the program and no other arguments to run.
        
        Formatting: Call the program by typing "./rsa534" into the terminal while in the same directory as the program and pressing enter/return.

        Output: This program will output text to the console and text documents.
            1) The console will show progress of the program as it generatres and calculates values and will notify the user when it has completed.
            2) "p_q.txt" contains the generated values of p and q, each on their own line.
            3) "e_n.txt" contains the calculated values of e and n, each on their own line.
            4) "d_n.txt" contains the calculated values of e and n, each on their own line. 

% Part 2 - messageDigest435
    Purpose: 
        This program can perform two tasks. It can either create a digital signature for a text file or verify that a digital signature of a text file is authentic.

    Compilation
        To compile messageDigest435.cc multiple files are required. This README assumes you have a C++ compiler installed and are able to utilize Makefiles. 
            If this project has been accessed via GitHub, you may skip to step 5.

     1) Put messageDigest435.cc in the same directory as most of the files from Matt McCutchen's C++ Big Integer Library. 
        The files that are not needed are:
            .gitignore.txt
            ChangeLog
            run-testsuite
            sample.cc
            testsuite.cc

     2) Obtain copies of or write your own versions of sha256.h and sha256.cpp
            These files can be found at:
                http://www.zedwood.com/article/cpp-sha256-function
                https://github.com/jaccon236/Algorithms_435_RSA_Encryption/tree/main/Part%202%20-%20messageDigest435

     3) Edit Makefile (You can also create your own Makefile as long as you know how to do this properly)
            1) Change line 52 to be "program = messageDigest435"
            2) Change line 53 to be "program-objects = messageDigest435.o"
            3) (Optional) Remove lines 30 through 44 (these lines are used for test-suite which is not needed)
            4) If you are using a Window's machine replace "rm" in line 65 with "del"
            5) Add "sha256.o\" in the "library-objects"
            6) Add "sha256.h\" in the "library-headers"

     4) The files "e_n.txt" and "d_n.txt" generated in Part 1 are required for Part 2.
            Ways to obtain these files:
                Download them from the GitHub at https://github.com/jaccon236/Algorithms_435_RSA_Encryption/tree/main/Part%202%20-%20messageDigest435
                Generate them with rsa435.exe and move them into the proper directory

     5) Once all required files are in the same directory, run the "make" command or it's equivalent on your system to build the project.
            You may see multiple warnings regarding depreciated code. This is due to the age of the C++ Big Integer Library and they can be ignored.

     6) Assuming everything has been done correctly, the object files for the Big Integer Library, sha256.o, messageDigest435.o, and messageDigest435.exe should appear in the directory.
            If they have not, verify that you have followed all of the steps correctly. If you are still having issues, email me any questions you may have.

    Execution:
        Arguments: This program expects multiple arguments.
            1) The name of the program
            2) The 'mode' of the program
                s: create a digital signature for a specified file
                v: verify the digital signature for a specified file
            3) The name of the file to be signed or verified
            4) The name of the file which contains the digital signature (ONLY when argument 2 is 'v')

        Formatting: Replace filename with the name of the text file and filename.signature with the name of the signature file. Make sure to include all file extensions.
            To create a digital signature for a specified file: 
                ./messageDigest435.exe s filename
            
            To verify a digital signature for a specified file (ONLY works if a .signature file exists in the directory already)
                ./messageDigest435.exe v filename filename.signature

        Output: This program will output text to the console and/or a file named file.txt.signature
            1) If argument 2 is 's' the program will create a digital signature of the specified file, store it in a signature file, and inform the user upon completion
            2) If argument 2 is 'v' the program will verify the digital signature in the signature file provided matches that of the file to be verified.
                - If the signatures match the user will be informed that the signature is authentic and the file has not been modified.
                - If the signatures do not match the user will be informed that the signature is not authentic and the file has been modified.
            3) If incorrect formatting of arguments are provided, the program will terminate and prompt the user with their mistake.
            4) If the file name specified does not exist in the current directory, the program will terminate and prompt the user with their mistake.

% END OF README %