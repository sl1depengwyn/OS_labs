echo "Maxim Filonov" > _ex3.txt
chmod a-x _ex3.txt
ls -l _ex3.txt > ex3.txt
chmod u=rwx,o=rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod g=rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
echo "660 in octal is 110110000 in binary that means that file is readable and writable for user and group but not for others" >> ex3.txt
echo "775 -> 111111101 -> everything is allowed for everyone but writing for others" >> ex3.txt
echo "777 -> 111111111 -> everything is allowed for everyone" >> ex3.txt

