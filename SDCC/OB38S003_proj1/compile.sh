#! /bin/sh

## remove files before compile, to get errors
make clean

make

rm flasher/main.ihx
cp build/*.ihx flasher/main.ihx

## Instructions for Empty C Project
## Add compiler Make for Makefile
## Select the Project in Project Explorer
## Project-Properties (Alt+Enter)
## - Go to Builders
## - Uncheck all native builders (CDT or Scanner etc)
## - Click in New
## - - Click in OK (Program)
## - - Put a name ("make_OB38S003")
## - - In Location put: /usr/bin/sh
## - - In Working directory put: ${project_loc}
## - - In Arguments put: compile.sh
## - - Click in OK
## - - Click in Apply and Close
##
## Instructions for OB38S003
## - - Add programmer OB38S003
## Select the Project in Project Explorer
## Project-Properties (Alt+Enter)
## - Go to Builders
## - Uncheck all native builders (CDT or Scanner etc)
## - Click in New
## - - Click in OK (Program)
## - - Put a name ("flash_OB38S003")
## - - In Location put: /flasher/flash.sh
## - - In Working directory put: ${project_loc}/flasher
## - - In Arguments put:
## - - Click in OK
## - - Click in Apply and Close
##
## Select the Project in Project Explorer
## Project-Properties (Alt+Enter)
## - Go to Builders
## [x] make_OB38S003
## [ ] flash_OB38S003
##
## Configure Run As
## Menu Run
## Click in Run Configurations
## Add new launch configuration in Launch Group
## Set name ("launch_OB38S003")
## Click in Add
## Select "flash_OB38S003" in "Program"
## Click Ok
## Click Apply and Close
##
## Usage
## Click in Build 'Release' icon (Hammer)
## Click in Run icon near menu "Edit" to burn the w1209