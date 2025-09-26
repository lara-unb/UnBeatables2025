from gameController import GameController
import threading
import unboard

def updateUnboard(data):
  unboard.gamePhase = data['gamePhase']
  unboard.gameState = data['state']
  unboard.setPlay = data['setPlay']
  unboard.firstHalf = data['firstHalf']
  unboard.kickingTeam = data['kickingTeam']
  unboard.secsRemaining = data['secsRemaining']

  teamData = data['TeamInfo'][0] if data['TeamInfo'][0]['teamNumber'] == unboard.teamNumber else data['TeamInfo'][1]
  
  unboard.score = teamData['score']
  playerData = teamData['RobotInfo'][unboard.playerNumber]

  unboard.penalty = playerData['penalty']
  unboard.secsTillUnpenalised = playerData['secsTillUnpenalised']





def main():
  gameController = GameController()
  thread = threading.Thread(target=gameController.startListeners)
  thread.daemon = True  # Allow threads to be killed when main program exits
  thread.start()

  while True:
    try:
      if (not gameController.packet_queue.empty()): 
        data = gameController.packet_queue.get()
    except Exception as e:
      print("The error is: ",e)