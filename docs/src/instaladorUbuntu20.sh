#!/bin/bash

sudo apt update

# ----------------------------------------------
#
# CRIAÇÃO DO AMBIENTE
#
# ----------------------------------------------

mkdir -p ~/UnBeatables
chmod 777 ~/UnBeatables
cd ~/UnBeatables || exit 1
mkdir -p Choregraphe NAOqi Workspace CoppeliaSim
chmod -R 777 Choregraphe NAOqi Workspace CoppeliaSim
cd ~/UnBeatables/Workspace || exit 1
mkdir -p Simulation Public
chmod -R 777 Simulation Public

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

if ! command -v python3 &>/dev/null; then
  echo "Instalando Python3..."
  sudo apt install -y python3 python3-pip
fi
echo "Python3 instalado com sucesso: $(python3 --version)"

if ! command -v pyenv &>/dev/null; then
  echo "Instalando e configurando pyenv..."
  sudo apt update && sudo apt install -y \
        make build-essential libssl-dev zlib1g-dev \
        libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm \
        libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev
  curl https://pyenv.run | bash
  # shellcheck disable=SC2016
  # shellcheck disable=SC2129
  echo 'PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
  # shellcheck disable=SC2016
  echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
  # shellcheck disable=SC2016
  echo 'eval "$(pyenv init --path)"' >> ~/.bashrc
  # shellcheck disable=SC2016
  echo 'eval "$(pyenv init -)"' >> ~/.bashrc
  # shellcheck disable=SC2016
  echo 'eval "$(pyenv virtualenv-init -)"' >> ~/.bashrc
  # shellcheck disable=SC1090
  source ~/.bashrc

  export PYENV_ROOT="$HOME/.pyenv"
  export PATH="$PYENV_ROOT/bin:$PATH"
  eval "$(pyenv init --path)"
  eval "$(pyenv init -)"
  eval "$(pyenv virtualenv-init -)"
fi
echo "Pyenv instalado com sucesso: $(pyenv --version)"

if ! pyenv versions | grep -q "2.7.18"; then
  echo "Instalando Python 2.7.18..."
  pyenv install 2.7.18
fi
echo "Versões do Python disponíveis: $(pyenv versions)"

if ! pyenv virtualenvs | grep -q "UnBeatables"; then
  echo "Criando virtualenv 'UnBeatables'..."
  pyenv virtualenv 2.7.18 UnBeatables

  echo "alias python2='pyenv activate UnBeatables && python'" >> ~/.bashrc
  # shellcheck disable=SC1090
  source ~/.bashrc
fi
echo "Ambientes virtuais disponíveis: $(pyenv virtualenvs)"

# shellcheck disable=SC2164
cd ~/UnBeatables/NAOqi
if [ ! -d "pynaoqi-python2.7-2.8.6.23-linux64-20191127_152327" ]; then
  echo "Instalando e extraindo NAOqi Python..."
  wget "https://community-static.aldebaran.com/resources/2.8.6/pynaoqi-python2.7-2.8.6.23-linux64-20191127_152327.tar.gz"
  tar -xvzf pynaoqi-python2.7-2.8.6.23-linux64-20191127_152327.tar.gz
  rm -rf pynaoqi-python2.7-2.8.6.23-linux64-20191127_152327.tar.gz
  # shellcheck disable=SC2016
  echo 'export PYTHONPATH=${PYTHONPATH}:~/UnBeatables/NAOqi/pynaoqi-python2.7-2.8.6.23-linux64-20191127_152327/lib/python2.7/site-packages' >> ~/.bashrc
  # shellcheck disable=SC1090
  source ~/.bashrc
fi

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

# shellcheck disable=SC2164
cd ~/UnBeatables/NAOqi
if [ ! -d "naoqi-sdk-2.8.5.10-linux64" ]; then
  echo "Instalando e extraindo NAOqi C++..."
  wget "https://community-static.aldebaran.com/resources/2.8.5/naoqi-sdk-2.8.5.10-linux64.tar.gz"
  tar -xvzf naoqi-sdk-2.8.5.10-linux64.tar.gz
  rm -rf naoqi-sdk-2.8.5.10-linux64.tar.gz
fi

eval "$(pyenv init --path)"
eval "$(pyenv init -)"
eval "$(pyenv virtualenv-init -)"
pyenv activate UnBeatables
  if ! command -v qibuild &>/dev/null; then
    echo "Instalando qibuild..."
    pip install qibuild
    qitoolchain create sdkv6 ~/UnBeatables/NAOqi/naoqi-sdk-2.8.5.10-linux64/toolchain.xml
    # shellcheck disable=SC2164
    cd ~/UnBeatables/Workspace
    qibuild init
    qibuild add-config configsdk -t sdkv6 --default
    qibuild
    # shellcheck disable=SC2016
    echo 'PATH=$PATH:$HOME/.local/bin' >> ~/.bashrc
  fi
  echo "Qibuild instalado com sucesso: $(qibuild --version)"
pyenv deactivate

# ----------------------------------------------
#
# INSTALAÇÃO DO CHOREGRAPHE
#
# ----------------------------------------------

# shellcheck disable=SC2164
cd ~/UnBeatables/Choregraphe/
if [ ! -d "choregraphe-2.8.8-ubuntu2204" ]; then
  echo "Baixando e extraindo Choregraphe..."
  wget "https://community-static.aldebaran.com/resources/2.8.8/choregraphe-2.8.8-ubuntu2204-standalone.tar.gz"
  tar -xvzf choregraphe-2.8.8-ubuntu2204-standalone.tar.gz
  rm -rf choregraphe-2.8.8-ubuntu2204-standalone.tar.gz
  # TODO ver o que a libz.so.1 faz (pq tinha que mexer nela)
fi

# ----------------------------------------------
#
# INSTALAÇÃO DOS REPOSITÓRIOS
#
# ----------------------------------------------

if ! command -v git &>/dev/null; then
  echo "Instalando git..."
  sudo apt install git -y
fi
echo "Git instalado com sucesso: $(git --version)"

# shellcheck disable=SC2164
cd ~/UnBeatables/Workspace/Public
if [ ! -d "Unbeatables-Public" ]; then
  echo "Baixando e extraindo public..."
  git clone https://github.com/lara-unb/Unbeatables-Public.git
  pyenv activate UnBeatables
  # TODO COLOCAR A VERSAO DO DOCKER
  pip install flask
  pip install flask_socketio
  pip install construct
  pip install opencv-python
  pyenv deactivate
fi

# shellcheck disable=SC2164
cd ~/UnBeatables/Workspace/Simulation
if [ ! -d "UnBeatables_Simulation" ]; then
  echo "Baixando e extraindo simulation..."
  git clone https://github.com/lara-unb/UnBeatables_Simulation.git
  # shellcheck disable=SC2164
  cd ~/UnBeatables/Workspace/Simulation/UnBeatables_Simulation/Cpp-Scripts/
  pyenv activate UnBeatables
  qibuild configure
  qibuild make
  pyenv deactivate
fi

# ----------------------------------------------
#
# INSTALAÇÃO DOS COPPELIASIM
#
# ----------------------------------------------

# shellcheck disable=SC2164
cd ~/UnBeatables/CoppeliaSim/
if [ ! -d "CoppeliaSim_Edu_V4_9_0_rev6_Ubuntu20_04" ]; then
  echo "Baixando e extraindo CoppeliaSim..."
  wget "https://downloads.coppeliarobotics.com/V4_9_0_rev6/CoppeliaSim_Edu_V4_9_0_rev6_Ubuntu20_04.tar.xz"
  tar -xvJf CoppeliaSim_Edu_V4_9_0_rev6_Ubuntu20_04.tar.xz
  rm -rf CoppeliaSim_Edu_V4_9_0_rev6_Ubuntu20_04.tar.xz
fi