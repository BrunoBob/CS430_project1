CS 430 Cpmuter graphics : Project 1

Small program to convert ppm file in P3 to P6 or the opposite

To use the programe :

	- Clone the project
	- make
	- ppmrw type_of_conversion input.ppm ouput.ppm
		(type of conversion = 3 or 6)

Return

	 0 = DONE
	 1 = Wrong number of arg
	 2 = Wrong type of conversion
	 3 = Error opening file : file dont exist
	 4 = Format not ppm P3 or ppm P6
	 5 = File corrupted : Can't read image size

