# mimiscript-compiler

## compile python to mimsicript C project

## linux下测试mimiscript内核(推荐ubuntu20.04)：

step1: 拉取项目
``` shell
git clone https://github.com/mimilib/mimiscript
cd mimiscript
git submodule init && git submodule update
```
step2: 安装编译链
``` shell
sudo apt update
sudo apt install -y clang llvm cmake zlib1g-dev
```

step3: 编译项目
```
cd mimiproject
sh init.sh # 第一次编译前运行，之后就不用运行了 
sh make.sh # 编译项目
```

step4: 运行demo
``` shell	
bin/msc-linux.bin
```
