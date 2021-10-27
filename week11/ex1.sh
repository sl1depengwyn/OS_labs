dd if=/dev/urandom of=lofs.img bs=1000MB count=1
sudo losetup -f lofs.img
sudo mkfs.ext4 $(losetup -a | grep 'lofs.img' | awk '{print $1}' | cut -d ':' -f 1)
mkdir -p lofsdisk
sudo mount $(losetup -a | grep 'lofs.img' | awk '{print $1}' | cut -d ':' -f 1) lofsdisk/
