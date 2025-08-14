#!/bin/bash

sudo apt update

sudo apt install -y sudo apt install libwebkit2gtk-4.1-0 libwebkit2gtk-4.1-dev libjavascriptcoregtk-4.1-0 libjavascriptcoregtk-4.1-dev

if [ ! -d "../lib/GameController3" ]; then
  echo "Diretório ../lib/GameController3 não existe. Criando e instalando GameController3..."
  mkdir ../lib/GameController3
  # shellcheck disable=SC2164
  cd ../lib/GameController3
  wget "https://github.com/RoboCup-SPL/GameController3/releases/download/v5.0.0-rc.3/game_controller-5.0.0-rc.3-x86_64-unknown-linux-gnu.tar.bz2"
  tar -xvjf game_controller-5.0.0-rc.3-x86_64-unknown-linux-gnu.tar.bz2
  rm -f game_controller-5.0.0-rc.3-x86_64-unknown-linux-gnu.tar.bz2
fi

#COLOCAR ISSO ANTES DE INICIAR O GAMECONTROLER CASO ESTEJA NO KDE:
#export WEBKIT_DISABLE_SANDBOX_THIS_IS_DANGEROUS=1
#export WEBKIT_DISABLE_COMPOSITING_MODE=1