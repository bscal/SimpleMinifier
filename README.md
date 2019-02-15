# SimpleMinifier
Simple C++ project that combines and minifies files.

Built and tested with Visual Studio 2017

This program can minify and combine files. I only tested minify with javascript.

# Running the program
For Windows
`start SimpleMinifer.exe -m index.js index.min.js -c file1.js file2.js combinded.js`


	`-m [input file] [output file]` - Will read the input, minify it, write it to output.
	
	
	`-c [input file1] [input file2] [output file]` - Will read both inputs and write in output file
	
	

# Bugs and things to fix
* Files need to be in the same directory as the exe
