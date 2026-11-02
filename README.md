# YOLOv8 NCNN C++ 端侧部署 (YOLOv8 NCNN C++ Deployment)

本项目是一个基于 C++ 和 NCNN 框架的 YOLOv8 目标检测端侧推理 Demo。实现了从模型加载、图像预处理到前向推理的完整链路，并在 Linux 环境下成功编译运行。

## 🛠️ 技术栈 (Tech Stack)
*   **编程语言**: C++ (C++11)
*   **深度学习框架**: NCNN
*   **图像处理**: OpenCV
*   **构建工具**: CMake
*   **开发环境**: Ubuntu (WSL2)

## 📂 文件结构 (File Structure)
*   `main.cpp`: 核心推理代码，包含预处理和模型前向传播。
*   `CMakeLists.txt`: 项目构建配置，链接了 OpenCV 和 NCNN，并解决了 OpenMP 依赖。
*   `yolov8n.param` / `yolov8n.bin`: 转换好的 NCNN 格式模型文件。
*   `test.jpg` / `result.jpg`: 测试图片及推理输出结果。

## 🚀 编译与运行 (Build & Run)

### 1. 编译 (Build)
```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
