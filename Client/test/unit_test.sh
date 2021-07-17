#!/bin/bash

##############################
# 单元测试
##############################

cd $(dirname $0) || exit

## 是否进行单元测试
#if [ "$1" == "ON" ]; then
#  UNIT_TEST="true"
#  echo "进行单元测试！"
#else
#  UNIT_TEST="false"
#  echo "不进行单元测试！"
#fi

# 单元测试开关
UNIT_TEST="false"

# 读取旧的 MD5
MD5_PATH="./build/CMakeLists.txt.md5"

if [ -f ${MD5_PATH} ]; then
  oldMD5="$(cat ${MD5_PATH})"
else
  oldMD5=""
fi

# 是否重新编译
if [ "$1" == "ON" ]; then
  oldMD5=""
fi

echo "旧的MD5=${oldMD5}"

# 计算当前的 MD5
newMD5="$(md5sum ../CMakeLists.txt | awk '{print $1}')"
echo "新的MD5=${newMD5}"

# 如果 MD5 相等，不需要重新 cmake
if [ "${oldMD5}" == "${newMD5}" ]; then
  cd ./build || exit
else
  echo "MD5不相等，正在重新编译..."
  rm -rf ./build && mkdir ./build && cd ./build || exit

  if [ ${UNIT_TEST} == "true" ]; then
    cmake ../.. -DUNIT_TEST=YES || (echo "cmake失败！" && exit)
  else
    cmake ../.. || (echo "cmake失败！" && exit)
  fi

  # 保存新的 MD5
  touch CMakeLists.txt.md5 || (echo "有问题！" && exit)
  echo "${newMD5}" >CMakeLists.txt.md5
fi

echo "============================================================="
echo "PWD=$(pwd)"

# 编译
make -j8 || exit

echo "============================================================="

function onSigInt() {
    echo " ( Ctrl+C ) "
}

# 捕获键盘 Ctrl+C
trap onSigInt INT

# 运行
chmod +x ./runCommunication
./runCommunication || (echo ">>> 执行异常!" && exit)

echo "============================================================="

# 统计覆盖率
if [ ${UNIT_TEST} == "true" ]; then
  echo "覆盖率统计..."
  rm -rf ./覆盖率结果/
  lcov --capture --directory ./ --output-file all.info || exit
  # 移除不需要统计的文件
  lcov --remove all.info '/usr/include/*' '*/test/*' '*/ThirdPartyLayer/*' '*/BaseLayer/*' -o result.info || exit
  # 可视化
  genhtml result.info --output-directory ./覆盖率结果/ || exit
fi
