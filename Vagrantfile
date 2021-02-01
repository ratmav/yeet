Vagrant.configure("2") do |config|
  config.vm.box = "debian/contrib-buster64"

  config.vm.provider "virtualbox" do |v|
    v.name = "yeet"
    v.cpus = 2
    v.memory = 4096
  end

  config.vm.synced_folder "src/", "/src"

  config.vm.provision "shell", inline: "apt-get install --yes python-apt"

  config.vm.provision "ansible" do |ansible|
    ansible.verbose = "v"
    ansible.playbook = "ansible/build.yml"
    # TODO: ansible.playbook = "ansible/test.yml"
  end
end
