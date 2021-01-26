void hw
=======

[r&d skills exercise #1](https://docs.google.com/document/d/1U1PTHOdcUMUCC1rkcZGMazNkQCOCfjCV8aRPjYLxLEg/edit?ts=60073946)

![](https://upload.wikimedia.org/wikipedia/commons/9/96/Animated_glider_emblem.gif)

### setup (n0)

#### platform details

* host: [macos](https://support.apple.com/guide/mac-help/welcome/mac) v11.1
  * package management: [homebrew](https://docs.brew.sh/)
    * packages:
      * [shellcheck](https://github.com/koalaman/shellcheck#how-to-use) - lint shell (bash) scripts: `brew install shellcheck`
      * [ansible](https://docs.ansible.com/ansible/latest/index.html) - run tasks on target: `brew install ansible`
      * [task](https://taskfile.dev/#/) - run tasks on host, like gnu make: `brew install go-task/tap/go-task`
      * `./bash/get_debian.sh` dependencies (`brew install $PACKAGE`)
        * [wget](https://www.gnu.org/software/wget/manual/)
        * [gnupg](https://gnupg.org/documentation/manuals/gnupg/)
        * [grep](https://www.gnu.org/software/grep/manual/)
        * [nmap](https://nmap.org/book/man.html)
  * virtualization: [virtualbox](https://www.virtualbox.org/wiki/Documentation)
* target: [debian](https://www.debian.org/doc/) v.10.7.0 (current as of january 24th, 2021)

#### host setup

1. download the [latest macos virtualbox version](https://download.virtualbox.org/virtualbox/6.1.18/VirtualBox-6.1.18-142142-OSX.dmg).
1. submit virtualbox `.dmg` installer to [https://www.virustotal.com/gui/home/upload] to verify installer.
1. run the virtualbox installer on the host.
1. run the iso download and verification script `$ ./bash/get_debian.sh`.
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
    * install grub on `/dev/sda`
    * let the target boot
    * login as admin user

#### target setup

**assumes host setup is complete and that you're logged into the target as the admin user.**

1. open a terminal and elevate to root: `$ su`
1. give the admin user sudo privileges (n1):
    1. add the admin user to the sudo group: `# /sbin/usermod -aG sudo ratmav`
    1. open the sudoers file: `# /sbin/visudo`
    1. add the folling to the sudoers file (n3):

        ```shell
        # passwordless sudo for admin user for all commands.
        ratmav ALL=(ALL) NOPASSWD: ALL
        ```

1. restart the target: `# shutdown -r now`
1. log back in as the admin user.
1. confirm ssh is up and running: `$ sudo systemctl status sshd`
1. shutdown the target: `$ sudo shutdown -h now`
1. in the virtualbox gui **on the host**, open the network settings for the target.
    1. attach the target to the "Bridged Adapter"
    1. select the currently used network interface on the host.
1. start the target system and log in as the admin user.
1. ping google to confirm network access: `$ ping google.com`
1. confirm ssh access **from host**: `$ ssh ratmav@void-hw`
1. ssh to target and add your public ssh key to the admin user's list of authorized keys (n5).
1. confirm ssh key-based login from host to target.
1. test ansible access: `$ ansible --inventory ./ansible/hosts.yml -m ping void-hw`
1. shutdown target.
1. snapshot target (**be a shame if you couldn't fallback easily**):
    * name: "clean ready"
    * notes:

        ```
        admin user: ratmav
        admin pass: password
        ssh pubkey: ratmav@protonmail.com
        ```

1. boot target if you're ready to move on.

#### workflow

1. walk through the host setup steps.
1. walk through the target setup steps.
1. iterate on kernel module source.

##### tasks

_confirm target is running and accessbile via ssh keys._

* **build**: `$ task build`
    1. run the **reset_target** task
    1. upgrade
        * all system packages
        * development tools
        * kernel headers
    1. copy source from host to target
    1. build source on target
    1. install module on target
    1. reboot target
* **default**: `$ task`
    * convenience wrapper; will run the **build** task.
* **get_debian**: `$ task get_debian`
    1. download a debian v10.7.0 iso
    1. download checksums
    1. download pgp signature
    1. import debian signing key
    1. verify pgp signature
    1. confirm iso checksum
* **reset_target**: `$ task reset_target`
    1. stop target
    1. restore "clean ready" snapshot (see target setup)
    1. start target
    1. wait for ssh to come up on target

## notes

**n0**: **r&d and mvp code very often isn't, and doesn't need to be, production ready**: this work just gives me a springboard for other projects and it was honestly fun to make. business priorities dictate how much time anyone should spend on this kind of thing (but you're probably better off in the future to make the effort asap).

**n1**: this is a throwaway system and _should not_ have any sensitive data on it.

**n2**: it might be interesting and useful to have some sort of kickstart script or whatever to automate the target os setup after the host resources are allocated and target boots initially for os installation. for that matter, vargrant might actually be useful. docker...probably not since containers have the kernel abstracted away.

**n3**: this is essentially making the admin user a second root, on a non-r&d system it's best to observe the principle of least privilege. however, muscle memory from prepending commands with `sudo` made the admin user worthwhile for me.

**n4**: can probably use ansible to automate target setup steps 1-10 with tasks running on the host and then the target.

**n5**: at this point, you should be able to start the target in headless mode with virtualbox and work over ssh if you'd like.
