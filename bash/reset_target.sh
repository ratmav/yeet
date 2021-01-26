#!/usr/bin/env bash

VM_NAME="void-hw"
SNAPSHOT_NAME="clean ready"

target_restore() {
  VBoxManage snapshot void-hw restore "$SNAPSHOT_NAME"
}

# TODO: wait on ssh.
target_start() {
  VBoxManage startvm void-hw --type headless
  until nmap $VM_NAME -p ssh | grep open; do
    echo "waiting on ssh."
    sleep 3
  done
  echo "target ready."
}

target_stop() {
  until VBoxManage showvminfo void-hw | grep State | grep -q 'powered off'; do
    echo "stopping target."
    VBoxManage controlvm $VM_NAME acpipowerbutton
    sleep 3
  done
}

main() {
  target_stop
  target_restore
  target_start
}

main "$@"
