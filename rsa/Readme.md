# Readme

项目结构如下
.
├── BigInt.cc
├── BigInt.hh
├── Decrypt.cc
├── Encrypt.cc
├── Makefile
├── RSA.cc
├── RSA.hh
├── Readme.md
├── bin
│   ├── decrypt
│   └── encrypt
├── encrypted.txt
├── obj
│   ├── BigInt.o
│   ├── Decrypt.o
│   ├── Encrypt.o
│   └── RSA.o
├── private.key
└── public.key

其中 public.key 和 private.key 分别保存公钥和私钥 第一行为指数，第二行为模数

进入 rsa 目录运行如下指令重新编译

```cmd
make clean;make
```

编译完成后，二进制文件会保存到 bin 目录下，包含两个文件：encrypt 和 decrypt，分别可以加密和解密

执行如下的命令可以运行 encrypt 和 decrypt

```cmd
cd rsa
./bin/encrypt
./bin/decrypt
```
