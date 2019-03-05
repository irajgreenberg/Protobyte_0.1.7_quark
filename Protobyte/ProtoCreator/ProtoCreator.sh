#!/bin/bash
# Create new Protobyte project with new name - **for Dev work only**
# This should eventualy be converted to C++ prog using Boost FileSystem
# for cross-platform compatibility.

cp  -r ../ProtoTemplate/__Protobyte_Project_Template__ ../Projects
cd ../Projects

projName=$1

# Create unique prooject name if none provided
if [ -z "$projName" ]
  then
  	#http://stackoverflow.com/questions/1401482/yyyy-mm-dd-format-date-in-shell-script
  	DATE=`date +%Y%m%d%H%M%S`
    projName="sketch_"$DATE
fi

# Rename Solution directory
mv __Protobyte_Project_Template__ $projName
cd $projName

# Create .sln file with project name
sed "s/__Protobyte_Project_Template__/$projName/g" __Protobyte_Project_Template__.sln > $projName.sln
rm __Protobyte_Project_Template__.sln

# Set write permissions on .sln file
#chmod 777 $projName.sln

# Rename Project directory
mv __Protobyte_Project_Template__ $projName
cd $projName

# Rename Project and filter
mv *.vcxproj $projName.vcxproj
mv *.vcxproj.filters $projName.vcxproj.filters

ls -a
start .
