void hw
=======

[r&d skills exercise #1](https://docs.google.com/document/d/1U1PTHOdcUMUCC1rkcZGMazNkQCOCfjCV8aRPjYLxLEg/edit?ts=60073946)

![](https://upload.wikimedia.org/wikipedia/commons/9/96/Animated_glider_emblem.gif)

### setup (n0)

#### platform details

* host: [macos](https://support.apple.com/guide/mac-help/welcome/mac) v11.1
  * package management: [homebrew](https://docs.brew.sh/)
    * packages:
        * [virtualbox](https://www.virtualbox.org/wiki/Documentation) - virtualization platform: `brew install --cask virtualbox`
        * [vagrant](https://www.vagrantup.com/docs) - manage target vm: `brew install --cask vagrant`
        * [shellcheck](https://github.com/koalaman/shellcheck#how-to-use) - lint shell (bash) scripts: `brew install shellcheck`
        * [ansible](https://docs.ansible.com/ansible/latest/index.html) - run tasks on target: `brew install ansible`
        * [task](https://taskfile.dev/#/) - run tasks on host, like gnu make: `brew install go-task/tap/go-task`
        * `./bash/get_debian.sh` dependencies (`brew install $PACKAGE`)
            * [wget](https://www.gnu.org/software/wget/manual/)
            * [gnupg](https://gnupg.org/documentation/manuals/gnupg/)
            * [grep](https://www.gnu.org/software/grep/manual/)
            * [nmap](https://nmap.org/book/man.html)
* target: [debian](https://www.debian.org/doc/) v.10.7.0 (current as of january 24th, 2021)

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
* **default** (convenience wrapper): `$ task`
    1. run the **shutdown_target** task
* **get_debian**: `$ task get_debian`
    1. download a debian v10.7.0 iso
    1. download checksums
    1. download pgp signature
    1. import debian signing key
    1. verify pgp signature
    1. confirm iso checksum
* **reset_target**: `$ task reset_target` (n5)
    1. stop target
    1. restore "clean ready" snapshot (see target setup)
    1. start target
    1. wait for ssh to come up on target
* **shutdown_target**: `$ task shutdown_target`
    1. run the **test** task
    1. stop target
* **test**: `$ task test`
    1. run the **build** task
    1. check for module messages on target via `dmesg`
