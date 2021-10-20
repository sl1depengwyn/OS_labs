mkdir -p week1
echo "Maxim Filonov" > week1/file.txt
mkdir -p week10
link week1/file.txt week10/_ex2.txt
find . -inum $(stat -c '%i' week1/file.txt) > ex2.txt
rm -f $(find . -inum $(stat -c '%i' week1/file.txt)) >> ex2.txt

