# ecgen-cpp 项目上下文

## 项目概述

ecgen-cpp 是一个用于现代 C++ 的组合生成器库，专门用于枚举各种组合数学对象。该项目使用 C++20 协程简化编码，并采用现代 CMake 实践进行构建管理。

## 主要功能

- **Gray码生成器**: 只返回每次的“增量”变化，而不是完整列表
- **C++20 协程**: 使用协程简化生成器的实现
- **多种组合对象**: 支持排列、组合、集合划分、Gray码等的生成
- **现代 CMake**: 采用现代 CMake 实践，支持包安装和依赖管理
- **测试套件**: 集成测试套件，支持代码覆盖率

## 核心组件

### 1. 排列生成 (perm.hpp/perm.cpp)
- `sjt_gen`: 使用 Steinhaus-Johnson-Trotter 算法生成排列
- `ehr_gen`: 使用 Eades-Hickey-Read 算法生成排列
- 提供计算阶乘的编译时函数 `Factorial`

### 2. 组合生成 (combin.hpp/combin.cpp)
- `emk_comb_gen`: 使用同质旋转门算法生成组合
- 提供计算组合数的编译时函数 `Combination`

### 3. 集合划分生成 (set_partition.hpp/set_partition.cpp)
- `set_partition_gen`: 生成集合划分
- 提供计算第二类 Stirling 数的编译时函数 `Stirling2nd`

### 4. Gray码生成 (gray_code.hpp/gray_code.cpp)
- `brgc_gen`: 生成二进制反射 Gray 码

## 技术特点

- 使用 C++20 协程实现递归生成器
- 头文件优先的库设计
- 现代 CMake 配置，使用 CPM.cmake 管理依赖
- 支持编译时计算（constexpr 函数）
- 遵循现代 C++ 编码规范

## 构建系统

项目使用 CMake 进行构建，支持以下子项目：
- 主库 (ecgen)
- 测试套件 (test)
- 独立可执行文件 (standalone)
- 文档生成 (documentation)

## 开发约定

- 使用 clang-format 和 cmake-format 进行代码格式化
- 遵循现代 C++ 最佳实践
- 使用 doctest 进行单元测试
- 支持静态分析工具和 sanitizer