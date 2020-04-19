# linetrace_sim
ライントレースのシュミレータ

## 環境
ubuntu 18.04

## 実行する
```
$ mkdir build && cd build
$ cmake ..
$ make
$ ./linetrace_sim
```

clionの場合は緑色の三角ボタンを押せばいいはず

## 依存関係
- cmake
- [matplotlibcpp](https://github.com/lava/matplotlib-cpp)

`sudo apt-get install python-matplotlib python-numpy python2.7-dev`