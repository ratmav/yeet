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
1. start virtualbox and create a new virtual machine (2 cores, 4gb ram, 25gb disk should be comfortable on recent hardware, resize to what works best on your host).