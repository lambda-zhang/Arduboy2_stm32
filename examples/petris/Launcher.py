import os
import subprocess
import datetime

OUTPUT_LOG = "Bootstrap.log"
REPO_URL = "https://github.com/bendapootie/GridGame.git"
REPO_FOLDER = "GridGame"

def OpenSolution():
  os.system(r"start Src\GridGame.sln")

def StartGitGui():
  os.system(r"start git-gui")

def OpenProjectFolder():
  os.system(r"start .")

def CmdFromProjectFolder():
  os.system(r"start cmd .")

def RunGameDebug():
  RunCommand("Data", os.path.abspath(r"Build\x64\Debug\Builder.exe"))

def RunGameRelease():
  RunCommand("Data", os.path.abspath(r"Build\x64\Release\Builder.exe"))

def BuildAll():
  RunCommand("Tools", r"python", ["BuildGridGame.py"])

def PullBuildLaunchTest():
  if (os.path.isdir("Build") == False):
    os.mkdir("Build")
  RunCommand(r"Build", r"python", [os.path.abspath(r"Tools\Bootstrap.py")])
  RunCommand(r"Build\GridGame\Tools", r"python", ["BuildGridGame.py"])
  RunCommand(r"Build\GridGame\Data", os.path.abspath(r"Build\GridGame\Build\x64\Release\Builder.exe"))


# Define all the commands in a data structure so the display and
# selection logic are based on the same thing
commands =[
  {"desc": "Open Solution", "func": OpenSolution},
  {"desc": "Open Git Gui", "func": StartGitGui},
  {"desc": "Open Project Folder", "func": OpenProjectFolder},
  {"desc": "Cmd Prompt from Project Folder", "func": CmdFromProjectFolder},
  {"desc": "Launch Game: Debug x64", "func": RunGameDebug},
  {"desc": "Launch Game: Release x64", "func": RunGameRelease},
  {"desc": "Build all Configurations", "func": BuildAll},
  {"desc": "Pull, build, and launch from Build/GridGame", "func": PullBuildLaunchTest}
]

def Main():
  while (True):
    PrintHeader()
    option = input("Select an option: ")

    try:
      commands[int(option)]["func"]()
    except:
      if (option.upper() == 'X'):
        return;
      print("Unhandled command {0}".format(option))
      
def PrintHeader():
  print()
  print("+==========================================================================+")
  print("| Welcome to the Launcher                                                  |")
  print("+--------------------------------------------------------------------------+")
  print("|  Options                                                                 |")
  for i, command in enumerate(commands):
    s = "|  ({0}) {1}".format(i, command["desc"])
    s += " " * (75 - len(s)) + "|"
    print(s)
  print("|  (X) Exit launcher                                                       |")
  print("+--------------------------------------------------------------------------+")

def RunCommand(folder, command, arguments = [], log_operation = False):
    start_time = TimingStart()
    original_working_directory = os.getcwd()
    try:
        os.chdir(folder)
        os_command = [command] + arguments
        print(os_command)
        result = subprocess.run(os_command)
    finally:
        os.chdir(original_working_directory)
    sync_duration = TimingStop(start_time)
    
    if (log_operation):
        LogStats(OUTPUT_LOG, start_time, sync_duration)

def TimingStart(message = 'Timing Start', do_print = True):
    start = datetime.datetime.now()
    print("{0} - {1}".format(str(start), message))
    return start
    
def TimingStop(start, do_print = True, message = 'Operation took'):
    end = datetime.datetime.now()
    delta = end - start
    if (do_print):
        print("{0} - {1}".format(message, str(delta)))
    return delta

def LogStats(output_file, start_time, sync_duration):
    duration_seconds = sync_duration.total_seconds()
    try:
        f = open(output_file, "a+")
        f.write("{1},{2}\n".format(start_time, duration_seconds))
        f.close()
    finally:
        return


if __name__ == '__main__':
    Main()
