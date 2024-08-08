#!/bin/bash

# This script automates the installation of Arch Linux based on the provided guide.
# It assumes you are booting from an Arch Linux live USB and have a connected internet.

# Function to check if a command exists
command_exists() {
  command -v "$1" >/dev/null 2>&1
  return $?
}

# Function to prompt for user input with a default value
prompt_default() {
  read -p "$1 [${2:-}]" -r -e -i "${2:-}" input
  echo "$input"
}

# Function to install packages with pacman
install_packages() {
  echo "Installing packages: $@"
  sudo pacman -S --noconfirm "$@"
}

# Function to enable a service
enable_service() {
  echo "Enabling service: $@"
  sudo systemctl enable "$@"
}

# Function to configure the boot loader
configure_bootloader() {
  echo "Configuring boot loader..."
  sudo bootctl install
  sudo nano /boot/loader/entries/arch.conf
  echo "title [Arch]" >> /boot/loader/entries/arch.conf
  echo "linux /vmlinuz-linux" >> /boot/loader/entries/arch.conf
  echo "initrd /initramfs-linux.img" >> /boot/loader/entries/arch.conf
  echo "options root=PARTUUID=$(blkid -s PARTUUID -o value /dev/$root_partition) rw" >> /boot/loader/entries/arch.conf
  sudo cat /boot/loader/entries/arch.conf
}

# Function to install a desktop environment
install_desktop() {
  echo "Installing desktop environment: $1"
  case "$1" in
    plasma)
      install_packages plasma
      ;;
    gnome)
      install_packages gnome
      ;;
    xfce)
      install_packages xfce4 xfce4-goodies
      ;;
    qtile)
      install_packages qtile qtile-extras
      ;;
    i3)
      install_packages i3-wm i3status i3lock
      ;;
    sway)
      install_packages sway swaylock swayidle
      ;;
    hyprland)
      install_packages hyprland-git
      ;;
    dwm)
      install_packages dwm
      ;;
    *)
      echo "Invalid desktop environment. Please choose from: plasma, gnome, xfce, qtile, i3, sway, hyprland"
      exit 1
      ;;
  esac
}

# Function to install a display manager
install_display_manager() {
  echo "Installing display manager: $1"
  case "$1" in
    sddm)
      install_packages sddm
      enable_service sddm.service
      ;;
    gdm)
      install_packages gdm
      enable_service gdm.service
      ;;
    lightdm)
      install_packages lightdm lightdm-gtk-greeter
      enable_service lightdm.service
      ;;
    *)
      echo "Invalid display manager. Please choose from: sddm, gdm, lightdm"
      exit 1
      ;;
  esac
}

# Function to install an AUR helper
install_aur_helper() {
  echo "Installing AUR helper: $1"
  case "$1" in
    paru)
      git clone https://aur.archlinux.org/paru.git
      cd paru
      makepkg -si
      ;;
    yay)
      git clone https://aur.archlinux.org/yay.git
      cd yay
      makepkg -si
      ;;
    *)
      echo "Invalid AUR helper. Please choose from: paru, yay"
      exit 1
      ;;
  esac
}

# Check if internet connection is available
echo "Checking internet connection..."
ping -c 1 archlinux.org > /dev/null 2>&1
if [ $? -ne 0 ]; then
  echo "No internet connection detected. Please connect to the internet."
  exit 1
fi

# Check if boot mode is UEFI
echo "Checking boot mode..."
if command_exists efivar; then
  echo "Boot mode: UEFI"
  boot_mode="UEFI"
else
  echo "Boot mode: BIOS"
  boot_mode="BIOS"
fi

# Prompt for disk to install on
disk_device=$(prompt_default "Enter the disk device to install on (e.g., /dev/sda): ")

# Prompt for root partition size
root_partition_size=$(prompt_default "Enter the size of the root partition (in GiB): ")

# Prompt for home partition size
home_partition_size=$(prompt_default "Enter the size of the home partition (in GiB): ")

# Prompt for username
username=$(prompt_default "Enter your username: ")

# Prompt for desktop environment
desktop_environment=$(prompt_default "Choose a desktop environment (plasma, gnome, xfce, qtile, i3, sway, hyprland): ")

# Prompt for display manager
display_manager=$(prompt_default "Choose a display manager (sddm, gdm, lightdm): ")

# Prompt for AUR helper
aur_helper=$(prompt_default "Choose an AUR helper (paru, yay): ")

# Wipe the disk and partition it
echo "Wiping the disk and partitioning..."
sudo gdisk $disk_device
echo "x" | sudo gdisk $disk_device
echo "z" | sudo gdisk $disk_device
echo "y" | sudo gdisk $disk_device
echo "n" | sudo gdisk $disk_device
echo "p" | sudo gdisk $disk_device
echo "1" | sudo gdisk $disk_device
echo "" | sudo gdisk $disk_device
echo "+1024M" | sudo gdisk $disk_device
echo "t" | sudo gdisk $disk_device
echo "1" | sudo gdisk $disk_device
echo "EF00" | sudo gdisk $disk_device
echo "n" | sudo gdisk $disk_device
echo "p" | sudo gdisk $disk_device
echo "2" | sudo gdisk $disk_device
echo "" | sudo gdisk $disk_device
echo "+16G" | sudo gdisk $disk_device
echo "t" | sudo gdisk $disk_device
echo "2" | sudo gdisk $disk_device
echo "8200" | sudo gdisk $disk_device
echo "n" | sudo gdisk $disk_device
echo "p" | sudo gdisk $disk_device
echo "3" | sudo gdisk $disk_device
echo "" | sudo gdisk $disk_device
echo "+$root_partition_sizeG" | sudo gdisk $disk_device
echo "t" | sudo gdisk $disk_device
echo "3" | sudo gdisk $disk_device
echo "8300" | sudo gdisk $disk_device
echo "n" | sudo gdisk $disk_device
echo "p" | sudo gdisk $disk_device
echo "4" | sudo gdisk $disk_device
echo "" | sudo gdisk $disk_device
echo "+$home_partition_sizeG" | sudo gdisk $disk_device
echo "t" | sudo gdisk $disk_device
echo "4" | sudo gdisk $disk_device
echo "8300" | sudo gdisk $disk_device
echo "w" | sudo gdisk $disk_device
echo "y" | sudo gdisk $disk_device
echo "q" | sudo gdisk $disk_device

# Format the partitions
echo "Formatting partitions..."
sudo mkfs.fat -F32 /dev/${disk_device}1
sudo mkswap /dev/${disk_device}2
sudo swapon /dev/${disk_device}2
sudo mkfs.ext4 /dev/${disk_device}3
sudo mkfs.ext4 /dev/${disk_device}4

# Mount the partitions
echo "Mounting partitions..."
sudo mount /dev/${disk_device}3 /mnt
sudo mkdir /mnt/boot
sudo mkdir /mnt/home
sudo mount /dev/${disk_device}1 /mnt/boot
sudo mount /dev/${disk_device}4 /mnt/home

# Install Arch Linux
echo "Installing Arch Linux..."
install_packages base base-devel linux linux-headers linux-firmware
sudo genfstab -U -p /mnt >> /mnt/etc/fstab
sudo arch-chroot /mnt

# Install additional packages
install_packages nano bash-completion

# Set locale, language, and time zone
echo "Setting locale, language, and time zone..."
sudo nano /etc/locale.gen
echo "en_US.UTF-8 UTF-8" | sudo tee -a /etc/locale.gen
sudo locale-gen
echo "LANG=en_US.UTF-8" | sudo tee /etc/locale.conf
echo "export LANG=en_US.UTF-8" | sudo tee -a /etc/profile
sudo ln -s /usr/share/zoneinfo/Europe/Berlin /etc/localtime
sudo hwclock --systohc --utc

# Set hostname
hostname=$(prompt_default "Enter your hostname: ")
echo "$hostname" | sudo tee /etc/hostname

# Enable 32-bit multilib
echo "Enabling 32-bit multilib..."
sudo nano /etc/pacman.conf
echo "[multilib]" | sudo tee -a /etc/pacman.conf

# Enable trim for SSD
echo "Enabling trim for SSD..."
sudo systemctl enable fstrim.timer

# Update the system
echo "Updating the system..."
sudo pacman -Syy
sudo pacman -Syu

# Set root password
echo "Setting root password..."
sudo passwd

# Create user account
echo "Creating user account..."
sudo useradd -m -g users -G wheel,storage,power -s /bin/bash $username
sudo passwd $username

# Edit sudoers file
echo "Editing sudoers file..."
sudo EDITOR=nano visudo
echo "%wheel ALL=(ALL) ALL" | sudo tee -a /etc/sudoers
echo "Defaults rootpw" | sudo tee -a /etc/sudoers

# Mount efivarfs
echo "Mounting efivarfs..."
sudo mount -t efivarfs efivarfs /sys/firmware/efi/efivars

# Configure boot loader
echo "Configuring boot loader..."
configure_bootloader

# Install Microcode
echo "Installing Microcode..."
if [ "$boot_mode" == "UEFI" ]; then
  install_packages intel-ucode
  sudo nano /boot/loader/entries/arch.conf
  echo "initrd /intel-ucode.img" | sudo tee -a /boot/loader/entries/arch.conf
elif [ "$boot_mode" == "BIOS" ]; then
  install_packages amd-ucode
  sudo nano /boot/loader/entries/arch.conf
  echo "initrd /amd-ucode.img" | sudo tee -a /boot/loader/entries/arch.conf
fi

# Install network manager
echo "Installing network manager..."
install_packages dhcpcd networkmanager
enable_service dhcpcd@eth0.service
enable_service NetworkManager.service

# Install AMD drivers
echo "Installing AMD drivers..."
install_packages xf86-video-amdgpu mesa lib32-mesa vulkan-radeon lib32-vulkan-radeon

# Install desktop environment
install_desktop $desktop_environment

# Install display manager
install_display_manager $display_manager

# Install AUR helper
install_aur_helper $aur_helper

# Install additional software
echo "Installing additional software..."
sudo $aur_helper -S firefox kitty act-bin adobe-source-code-pro-fonts adwaita-cursors adwaita-icon-theme appimagelauncher-bin arandr awesome-terminal-fonts awesome-terminal-fonts-patched bat blueman bluez brightnessctl btop cantarell-fonts cifs-utils conky cpupower-gui-git cups cups-pdf curl discord dmenu docker docker-compose dunst fwupd nm-applet blueman solaar nextcloud-client rofi rsync 1password slack-desktop steam bitwarden-bin ttf-roboto ttf-roboto-mono ttf-roboto-slab visual-studio-code-bin czkawka-gui-bin kvantum nwg-look obsidian picom ranger teams-for-linux-bin theia-bin volumeicon pavucontrol okular git gphoto2 v4l-utils v4l2loopback-dkms ffmpeg linux-headers xdg-desktop-portal-lxqt hunspell flameshot xorg-xsetroot alsa-utils acpilight base-devel extra/git extra/libx11 extra/libxcb extra/libxinerama extra/libxft extra/imlib2

# Exit chroot
echo "Exiting chroot..."
sudo exit

# Unmount partitions
echo "Unmounting partitions..."
sudo umount -R /mnt

# Reboot the system
echo "Rebooting the system..."
sudo reboot
