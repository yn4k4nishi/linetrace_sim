# linetrace_sim
ライントレースのシュミレータ

## 環境
ubuntu 18.04, 20.04

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

### python3を使う場合
`python3-dev`ではダメで、`sudo apt install python3.8-dev`でいけた(Ubuntu20.04)
