# start-up shell

alias proto="cd C:\/Users\/Frys\/Dev\/Protobyte_0.1.7_quark\/Protobyte"
alias dev="cd C:\/Users\/Frys\/Dev"

# git stuff
alias gs='git status'
alias gl='git log'
alias addAll='git add *'
alias pull='git pull'
alias push='git push'

# Explicitly declare global Project name variable
newName=''

# Function checks Protobyte Project name to avoid unintentional overwriting
checkName(){

	# msg array
	msgs=( 
		'Project '$newName' was Successsfully Created' 
		'Warning: Protobyte project names may not contain any spaces. Project '$newName' was Successsfully Created'  
		'Warning: Protobyte project names may not contain any spaces and a maximum of 4 separate keywords. Project '$newName' was Successsfully Created' 
		)

	if [ -d "../Projects\/"$newName ]
	then
    	echo 'Error: Project' $newName 'already exists'
    	ls ../Projects
   		# wait for user action to exit function
   		read -p "Please press any key to continue."
   	else 
   		case $argCount in

	  	1)
			echo ${msgs[0]}
			;;
		2)
			echo ${msgs[1]}
			;;
		3)
			echo ${msgs[1]}
			;;
		4)
			echo ${msgs[1]}
			;;
		*)	
			echo ${msgs[2]}
			;;

		esac

		createProject
	   	fi
}

# Function creates Protobyte project with unique, custom name
createProject(){
	# We made it this far, so
	./*.sh $newName
}


#Function for short-cut Protobyte project creation
start() { 

# Get arg count and solve for any number
# Max 4 seperate keywords may be strung together
# Additional keywords are disregarded
# A unique name is generated with no passed args
	argCount=$#
	arg1=$1
	arg2=$2
	arg3=$3
	arg4=$4

	#Get us in correct directory with ProtCreator Script
	cd C:\/Users\/Frys\/Dev\/Protobyte_0.1.7_quark\/Protobyte\/ProtoCreator

	
case $argCount in

  0)
	echo 'Warning: Protobyte Project Successsfully Created Using Automatic Naming' 
	./*.sh
    ;;

  1)
    newName=$arg1
	checkName 
    ;;

  2)
  	newName=$arg1
	newName+='_'
	newName+=$arg2
	checkName
    ;;

  3)
    newName=$arg1
	newName+='_'
	newName+=$arg2
	newName+='_'
	newName+=$arg3
	checkName
    ;;

  4)
    newName=$arg1
	newName+='_'
	newName+=$arg2
	newName+='_'
	newName+=$arg3
	newName+='_'
	newName+=$arg4
	checkName
    ;;

  *)
    newName=$arg1
	newName+='_'
	newName+=$arg2
	newName+='_'
	newName+=$arg3
	newName+='_'
	newName+=$arg4
	checkName
    ;;
esac

}


alias pcreate='start'



