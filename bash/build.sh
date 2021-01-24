#!/usr/bin/env bash

build() {
  ansible-playbook --inventory ./ansible/hosts.yml -l void-hw ./ansible/build.yml
}

main() {
  build
}

main "$@"
