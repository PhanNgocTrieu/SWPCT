import subprocess
import json
import time
from . import logger as Lg

launch_commander = "luna-send -n 1 -f luna://com.webos.applicationManager/launch"
args_home = "\'{\"id\":\"com.webos.app.home\"}\'"

class Commander:
    def __init__(self):
        self.module_name = "Commander"
        self.logger = Lg.Logger(self.module_name, use_file=True, filename=f"{self.module_name}.log")
        self.console = Lg.Logger(self.module_name, use_file=False)
        self.make_log("Commander initialized.")

    def send_command(self, command):
        self.make_log(f"Sending command: {command}")
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return json.loads(result.stdout)

    def make_log(self, message):
        self.logger.log(message)
        self.console.log(message)

    def wait(self, seconds):
        time.sleep(seconds)