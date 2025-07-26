#!/bin/bash

sudo apt update

# ----------------------------------------------
#
# CRIAÇÃO DO AMBIENTE
#
# ----------------------------------------------

cd ~/
mkdir UnBeatables

# ----------------------------------------------
#
# INSTALAÇÃO DO NAOqi PYTHON
#
# ----------------------------------------------

if ! command -v curl &>/dev/null; then
  echo "Instalando curl..."
  sudo apt update && sudo apt install -y curl
fi
echo "Curl instalado com sucesso: $(curl --version | awk '{print $2; exit}')"

# ----------------------------------------------
#
# INSTALAÇÃO DO NAOqi C++
#
# ----------------------------------------------

sudo apt-get install build-essential

if ! command -v cmake &>/dev/null; then
  echo "Instalando cmake..."
  sudo apt-get install -y cmake
fi
echo "Cmake instalado com sucesso: $(cmake --version)"

if [ ! -d "$HOME/UnBeatables/naoqi-sdk-2.8.5.10-linux64" ]; then
  echo "Instalando e extraindo NAOqi C++..."
  wget "https://community-static.aldebaran.com/resources/2.8.5/naoqi-sdk-2.8.5.10-linux64.tar.gz"
  tar -xvzf naoqi-sdk-2.8.5.10-linux64.tar.gz
  rm -rf naoqi-sdk-2.8.5.10-linux64.tar.gz
fi