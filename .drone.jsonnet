local Unittest() = {
  "kind": "pipeline",
  "type": "docker",
  "name": unittests,
  "steps": [
    {
      "name": "run unittests",
      "image": "nx.benfm.de:5000/drone-container:22.04",
      "environment": {
        "DEBIAN_FRONTEND": "noninteractive"
      },
      "commands": [
        "mkdir build",
        "cd build",
        "cmake -DWITH_UNITTESTS=True -GNinja ..",
        "ninja gtest",
        "./gtest"
      ]
    }
  ]
};

local Build(distribution, build_container) = {
  "kind": "pipeline",
  "type": "docker",
  "name": distribution,
  "steps": [
    {
      "name": "build packages",
      "image": build_container,
      "environment": {
        "DEBIAN_FRONTEND": "noninteractive",
        "DEB_BUILD_OPTIONS": "terse"
      },
      "commands": [
        "dpkg-buildpackage -uc -us -b -j$(nproc)",
        "cp -v ../*.deb debian/"
      ]
    },
    {
      "name": "push packages",
      "image": "nx.benfm.de:5000/drone-push-ubuntu",
      "settings": {
        "repository": distribution
      },
      "when": {
        "branch": [ "main" ]
      }
    }
  ]
};

local Notification(dependencies) = {
  "kind": "pipeline",
  "name": "email-notification",
  "depends_on": dependencies,
  "trigger": {
    "status": [
        "failure",
        "success"
    ]
  },
  "steps": [
    {
      "name": "notify",
      "image": "plugins/email",
      "settings": {
        "host": "mx.benfm.de",
        "from": "drone@benfm.de"
      },
      "when": {
        "status": [ "failure", "success" ]
      }
    }
  ]
};

[
  Unittest(),
  Build("ubuntu-jammy", "nx.benfm.de:5000/drone-container:22.04"),
  Build("ubuntu-noble", "nx.benfm.de:5000/drone-container:24.04"),
  Build("ubuntu-plucky", "nx.benfm.de:5000/drone-container:25.04"),
  Build("debian-trixie", "nx.benfm.de:5000/drone-container:trixie"),
  Notification(["ubuntu-jammy", "ubuntu-noble", "ubuntu-plucky", "debian-trixie"])
]
