#!/bin/bash
#Program:
#	This program is the lab5 for Linux course.It can automated compress 
#       file and classify files.
#History:
# 2022/10/20    V-test 
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
PATH_LAB=~/Desktop/Linux_Week5_Lab/Linux_Week5_Lab
sudo chmod 755 $PATH_LAB/student_id
sudo mkdir $PATH_LAB/compressed_files/zip
sudo mkdir $PATH_LAB/compressed_files/rar
sudo mkdir $PATH_LAB/compressed_files/tar.gz
sudo mkdir $PATH_LAB/compressed_files/unknown
Line_id_file=`wc -l $PATH_LAB/student_id`
export a=$(echo $Line_id_file | cut -d" " -f 1)
cd $PATH_LAB
sudo touch missing_list
sudo touch wrong_list
sudo chmod 777 missing_list
sudo chmod 777 wrong_list
for student in `seq $a`
do       
	st_id=`head -n ${student} $PATH_LAB/student_id | tail +${student}`
	file=`sudo find $PATH_LAB/compressed_files -name "*$st_id*"`
	extension=$(echo $file | cut -d"." -f 2)
	if [ -z $file ]
	then
		sudo echo "$st_id" >> missing_list
	elif [ "$extension" = "zip" ]
	then
 		sudo mv $file $PATH_LAB/compressed_files/zip/
	elif [ "$extension" = "tar" ]
	then
		tmp=$(echo $file | cut -d"." -f 1)
		sudo mv $file $tmp
		sudo mv $tmp $PATH_LAB/compressed_files/tar.gz/
	elif [ "$extension" = "rar" ]
	then
		sudo mv $file $PATH_LAB/compressed_files/rar/
	else
		sudo mv $file $PATH_LAB/compressed_files/unknown/
		sudo echo "$st_id" >> wrong_list
	fi
done
cd $PATH_LAB/compressed_files/zip/
sudo unzip "*.zip"
cd $PATH_LAB/compressed_files/rar/
sudo unrar e "*.rar"
cd $PATH_LAB/compressed_files/tar.gz/
for file in $PATH_LAB/compressed_files/tar.gz/*
do
	tmp="$file.tar.gz"
	sudo mv $file $tmp
	sudo gzip -d $tmp 	
done
for file_tar in $PATH_LAB/compressed_files/tar.gz/*
do
	sudo tar -xvf $file_tar
done
exit 0
