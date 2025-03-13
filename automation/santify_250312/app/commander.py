import subprocess
import json
import time
import os
from . import logger as Lg

launch_commander = "luna-send -n 1 -f luna://com.webos.applicationManager/launch"
args_home = "\'{\"id\":\"com.webos.app.home\"}\'"
permission="mount -o remount,rw /"


class Commander:
    _instance = None

    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            cls._instance = super(Commander, cls).__new__(cls, *args, **kwargs)
        return cls._instance

    def __init__(self):
        if not hasattr(self, 'initialized'):
            self.module_name = "Commander"
            self.logger = Lg.Logger(self.module_name, use_file=True, filename=f"{self.module_name}.log")
            self.console = Lg.Logger(self.module_name, use_file=False)
            self.make_log("Commander initialized.")
            self.mount = False
            self.initialized = True

    def send_command(self, command):
        if not self.mount:
            self.mounting()

        self.make_log(f"Sending command: {command}")
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return json.loads(result.stdout)

    def launch_command(self, command):
        if not self.mount:
            self.mounting()
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
        return result.stdout, result.stderr


    def mounting(self):
        if not self.mount:
            self.make_log("Mounting filesystem")
            os.system(permission)
            self.mount = True

    def do_command(self, command):
        self.logger.log(f"Sending command: {command}")
        if not self.mount:
            self.mounting()
        os.system(command)

    def make_log(self, message):
        self.logger.log(message)
        self.console.log(message)

    def wait(self, seconds):
        time.sleep(seconds)