./ex1.sh
sudo chmod 777 lofsdisk
echo "Maxim" > lofsdisk/file1
echo "Filonov" > lofsdisk/file2
gcc ex2.c -o lofsdisk/ex2.out
mkdir -p lofsdisk/bin
shrd="$(ldd /bin/{bash,cat,echo,ls} | egrep -o '/lib.*\.[0-9]')"
cp -v /bin/{bash,cat,echo,ls} lofsdisk/bin
for i in $shrd
do
cp -v --parents $i lofsdisk
done
sudo chroot lofsdisk ./ex2.out > ex2.txt
echo "" >> ex2.txt
lofsdisk/ex2.out >> ex2.txt


