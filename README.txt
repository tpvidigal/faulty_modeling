Fault-Tolerant Control System Modeling in SystemC
Case of Study: Pitch of Aircraft

# General informations ########################################################

Thesis Graduation Project - Computer Engineering
Universidade de Brasília, 2016

Author:  Tiago Pereira Vidigal
Advisor: Daniel Chaves Café


## Structure ###################################################################

doc/: Documentation generated using Doxygen
hdr/: Header files
src/: Source files
tb/:  Testbenches directories


## Author's Makefile ###########################################################

How to use it:
- Makefile-backup is the backup of the Makefile used by the author
- Edit the first lines to match your configurations and testbench you want to run
 ______________________________________________________
|                                                      |
| #Project particularities                             |
| TARGET = ...                <---- Name of simulation executable file to generate
| SYSTEMC = ...               <---- Path for your systemc-X.X.X directory
| TARGET_ARCH = ...           <---- Architecture of computer (linux64 for example)
| SRCDIR = src                                         |
| HDRDIR = hdr                                         |
| TBDIR  = tb/tb_...          <---- Select testbench directory to run
|                                                      |
| ...                                                  |
|______________________________________________________|


## Documentation ###############################################################

Documentation can be generated using Doxygen.
A Doxyfile present in the root can be used.
The folder "doc" will be generated.

It's recommended to use the html version.
Simply click on the file "doc/html/index.html".
A page with the documentation should open in your default internet browser.


## Notes #######################################################################

.gitignore: This file excludes some files being added with 'git add --all'

