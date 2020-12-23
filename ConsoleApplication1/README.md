试验在 c/c++ 中使用 python

最简单的一次输出 Hello world 的尝试，竟然陆陆续续折腾整个工作日才见到了输出。特点：

- Debug/Release x86 模式可用；
- 移除 x64 模式；
- 不依赖系统环境变量；

# 报错备忘

> Fatal Python error: initfsencoding: unable to load the file system codec

虽然设置了 PATH 环境变量，但无影响。新增 PYTHONHOME 环境变量后重启 ide 解决

> 无法解析的外部符号 __imp__Py_Finalize

x86 版本的项目，无法使用 64 位的 python，切换项目编译选项 x64。反之亦然

利用 anaconda 保证 64 位和 32 位的 python 共存

在 cmd 中执行 `set CONDA_FORCE_32BIT=1`，只在当前窗口的生命周期内有效，所以只能在此窗口内部署 32 位 python 虚拟环境：

- `conda create -n py35_x32 python=3.5` 新建 py35_x32 虚拟环境之后，使用 python 报错：
    > Fatal Python error: Py_Initialize: can't initialize sys standard streams

- `conda create -n py35_x32 python=3` 报错（但进入了 python 交互环境）
    > AttributeError: module 'importlib._bootstrap_external' has no attribute '_w_long'，

暂时 **放弃折腾 x86 x64 共存**，卸载 64 安装 32 位版本

## 避免改动环境变量

可以不改动操作系统（或用户）的 `PATH` 环境变量，通过 `conda init` 命令使 cmd.exe/powershell 启动时加载配置文件，新增 shell 的命令查找路径（同时也使 visual code 顺利执行）

在源码中使用 `Py_SetPythonHome(L"C:/Users/nielo/anaconda3");` 避免修改系统环境变量（新增 `PYTHONHOME`）

> fatal error LNK1104: 无法打开文件“python37_d.lib”

无法下载 python_d.lib，解决方案以取巧改动 `pyconfig.h` 为主:
- 高明点的 `#undef _DEBUG`
- 更杂乱的直接修改文本

Vcpkg 能够使用 python_d.lib（也必须使用，上述魔改 `pyconfig.h` 的方式反而会造成其他冲突），但 怎么配置有效的 `PYTHONHOME` 变量呢

——其实此时的报错已经是 python 包管理范畴了，需更进一步的学习


## 相关环境变量

`PYTHONHOME` 更改标准 Python 库的位置。——不需要

`PYTHONPATH` 增加模块文件默认搜索路径。_不需要

python.exe 在 anaconda3/
conda.exe 在 anaconda3/scripts/