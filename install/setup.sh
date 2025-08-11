#!/bin/bash

sudo apt update

if ! command -v curl &>/dev/null; then
  echo "Instalando curl..."
  sudo apt update && sudo apt install -y curl
fi
echo "Curl instalado com sucesso: $(curl --version | awk '{print $2; exit}')"

sudo apt-get install -y build-essential libopencv-dev

if ! command -v cmake &>/dev/null; then
  echo "Instalando cmake..."
  sudo apt-get install -y cmake
fi
echo "Cmake instalado com sucesso: $(cmake --version)"

if [ ! -d "../lib/NAOqi" ]; then
  echo "Diretório ../lib/NAOqi não existe. Criando e instalando NAOqi..."
  mkdir ../lib/NAOqi
  # shellcheck disable=SC2164
  cd ../lib/NAOqi

  echo "Instalando e extraindo NAOqi C++ no diretório ../lib/NAOqi..."
  wget "https://community-static.aldebaran.com/resources/2.8.5/naoqi-sdk-2.8.5.10-linux64.tar.gz"
  tar -xvzf naoqi-sdk-2.8.5.10-linux64.tar.gz
  rm -f naoqi-sdk-2.8.5.10-linux64.tar.gz
fi

