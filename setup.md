setup
=====

## platform details

* host: [macos](https://support.apple.com/guide/mac-help/welcome/mac) v11.1
  * package management: [homebrew](https://docs.brew.sh/)
    * packages:
      * [shellcheck](https://github.com/koalaman/shellcheck#how-to-use) - lint shell (bash) scripts: `brew install shellcheck`
      * `./bash/get_debian.sh` dependencies
        * [wget](https://www.gnu.org/software/wget/manual/)
        * [gnupg](https://gnupg.org/documentation/manuals/gnupg/)
        * [grep](https://www.gnu.org/software/grep/manual/)
  * virtualization: [virtualbox](https://www.virtualbox.org/wiki/Documentation)
* target: [debian](https://www.debian.org/doc/) v.10.7.0 (current as of january 24th, 2021)

## procedure

1. download the [latest macos virtualbox version](https://download.virtualbox.org/virtualbox/6.1.18/VirtualBox-6.1.18-142142-OSX.dmg).
1. submit virtualbox `.dmg` installer to [https://www.virustotal.com/gui/home/upload] to verify installer.
1. run the virtualbox installer on the host.
1. run the iso download and verification script `./bash/get_debian.sh`.
1. if the script emits `**PASS**` at the end of it's output, continue.
1. start virtualbox and create a new virtual machine with the verified iso.
    * target operating system and architecture: debian 64 bit
    * specs (salt to taste for your host):
        * 2 cores
        * 4gb memory
        * 25gb disk
1. start the virtual machine and select the verified 64 bit debian iso.
    * macos' security settings may not be configured to allow oracle-signed executables to run. in this case, follow [these](https://howtogeek.com/658047/how-to-fix-virtualboxs-“kernel-driver-not-installed-rc-1908-error/) steps, **which require a reboot of the host**.
    * i ran into a virtualbox bug where the iso selector gui would crash on initial startup. however, going into the target settings and selecting an iso through the storage section worked.
1. using the virtualbox ui's display connection to the target, install the target os
    * remember, virtualbox will release the keyboard and mouse from the target ui by pressing the left command key by default on macos.
    * target os (debian) settings:
        * hostname: `void-hw`
        * root password: `root` (this is a throwaway system and _should not_ have any sensitive data on it.)
        * admin username: `ratmav`
        * admin password: `root` (this is a throwaway system and _should not_ have any sensitive data on it.)
        * disks: "Guided - use entire disk"; "All files in one partition (recommended for new users)"
        * software selection: **SSH server, standard system utilities, and Debian desktop environment _ONLY_** (desktop in case you'd prefer to work directly on the host through the virtualbox graphical client.)
    * _this is a good time to take a break; the debian package install will take a few minutes._
