yeet
====

[r&d skills exercise #1](https://docs.google.com/document/d/1U1PTHOdcUMUCC1rkcZGMazNkQCOCfjCV8aRPjYLxLEg/edit?ts=60073946)

![](https://upload.wikimedia.org/wikipedia/commons/9/96/Animated_glider_emblem.gif)

## platform details

* host: [macos](https://support.apple.com/guide/mac-help/welcome/mac) (v11.1)
  * package management: [homebrew](https://docs.brew.sh/)
    * packages:
        * [virtualbox](https://www.virtualbox.org/wiki/Documentation) (v6.1.18) - virtualization platform: `brew install --cask virtualbox`
        * [vagrant](https://www.vagrantup.com/docs) (v2.2.14)- manage target vm: `brew install --cask vagrant`
        * [ansible](https://docs.ansible.com/ansible/latest/index.html) (v2.10.4) - run tasks on target: `brew install ansible`
        * [task](https://taskfile.dev/#/) (v3.0.1) - run tasks on host, like gnu make: `brew install go-task/tap/go-task`
* target: [debian](https://www.debian.org/doc/) (vbuster)

## workflow (n0)

go-task is used as a convenience wrapper around vagrant commands to provision the target machine, build and test the kernel module, then teardown the target machine (n1). instead of three commands, developers can just run `task`, which will:

1. download a debian target machine image, if necessary
1. provision the target machine (2 cpu, 4GB ram)
1. upgrade all system packages on the target
1. install development tools
1. kernel headers
1. build source on target via a shared directory
1. install module on target
1. reboot target
1. test for module init message via `dmesg`
1. test for module execution message via `dmesg`
1. test for module exit message via `dmesg`
1. destroy the target

this provides developers with a clean, lean, robust, and easy to use development environment so they can rapidly iterate.

## notes

**n0**: **r&d and mvp code very often isn't, and doesn't need to be, production ready.** that said, a good development harness is often extremely useful and highly reusable.

**n1**: rebuilding and reloading kernel modules on the fly with `modprobe` can be tricky. things like bios settings, etc. may have an impact, so automating the entire target provision-build-test-destroy loop seemed like the simplest and most reliable method. it may be worth researching a more elegant method; however, using a sledgehammer seems to work just fine.

### module implementation

* kernel modules are written to be executed asynchronously and non-blocking, akin to node.js. the reason for this is that since the kernel ties hardware to userspace, kernel modules and device drivers listen for interrupts from character devices (e.g. audio, keyboards, etc.) and block devices (pretty much disks), then process those interrupts accordingly. there are magic methods that essentially are hooks for stuff like module init, exit, and cleanup.
* the c stdlib is for userspace, which makes sense. kernel modules work on ring 0, which is pretty much all root all the time, so developers have to be extremely careful and write the most robust code possible. practically, this means developers can't just import the stdlib headers and run a loop in a main. however, there are kernel "stdlib" headers available for use.
* kthreads are powerful; they can essentially just spawn a thread at the kernel level and pass a pointer to whatever function is desired as the entrypoint.
* it's really cool to hang out in ring 0.

#### references

* [build your own lisp](http://buildyourownlisp.com/contents): c refresher.
* [linux kernel module programming - simplest example](https://sachithmuhandiram.medium.com/linux-kernel-module-programming-simplest-example-c45f2d1b32a7): hello world.
* [writing a linux kernel module](http://derekmolloy.ie/writing-a-linux-kernel-module-part-1-introduction): more depth, like kthreads.
* [module.h](https://github.com/torvalds/linux/blob/master/include/linux/module.h): kernel module api.
