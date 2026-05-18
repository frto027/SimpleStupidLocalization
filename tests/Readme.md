This is some test script runs in x86_64 arch.

remember to run `qpm restore` before test this.

install deps in your machine

```bash
dnf install libfmt-devel # for fedora
apt install libfmt-dev   # for ubuntu
```

build and test
```bash
cd tests
make test1.run && ./test1.run
```

add more main functions to mains for test