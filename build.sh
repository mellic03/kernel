make -s


# Download the latest Limine binary release.
# git clone https://github.com/limine-bootloader/limine.git --branch=v5.x-branch-binary --depth=1
 
# Build limine utility.
make -C limine
 
# Create a directory which will be our ISO root.
mkdir -p iso_root
 
# Copy the relevant files over.
cp -v myos.elf limine.cfg limine/limine-bios.sys \
      limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/
 
# Create the EFI boot tree and copy Limine's EFI executables over.
mkdir -p iso_root/EFI/BOOT
cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/
 
# Create the bootable ISO.
xorriso -as mkisofs -b limine-bios-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot limine-uefi-cd.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        iso_root -o image.iso
 
# Install Limine stage 1 and 2 for legacy BIOS boot.
./limine/limine bios-install image.iso


mkdir -p output
mv image.iso output/image.iso
cp -R iso_root output/.
# rm -R iso_root


# Run in qemu
qemu-system-x86_64 -boot d -cdrom output/image.iso -m 4096 -no-reboot