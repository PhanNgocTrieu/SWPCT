import time
from . import applicationlist
from . import logger as Lg
from . import commander as Cmd
from . import eula as Eula
import random

launch_commander = "luna-send -n 1 -f luna://com.webos.applicationManager/launch"

class ApplicationSender:
    def __init__(self):
        self.module_name = "ApplicationSender"
        self.logger = Lg.Logger(self.module_name, use_file=True, filename=f"{self.module_name}.log")
        self.console = Lg.Logger(self.module_name, use_file=False)
        self.commander = Cmd.Commander()
        self.eula = Eula.EulaApplication()
        self.make_log("Application sender initialized.")

    def checking_eula(self):
        self.make_log("Checking EULA")
        eula_result = self.eula.do_check_eula()
        if (eula_result == False):
            self.make_log("EULA not agreed.")
            return self.eula.enable_eula()
        self.make_log(f"EULA result: {eula_result}")
        return True

    def do_execute(self):
        if (self.checking_eula()):
            self.execute()


    def execute(self):
        while True:
            random_value = random.randint(0, len(self.get_applications()) - 1)
            random_application = applicationlist.applications[random_value]
            self.make_log(f"Generated random value: {random_value}")
            self.make_log(f"Pick application: {random_application}")
            self.send_application(random_application)
            self.wait(1)

    def send_application(self, application):
        if application not in applicationlist.applications:
            self.log(f"Application {application} not found.")
            return

        apphome_result = self.do_send_apphome()
        self.make_log(f"Sending to app home: {apphome_result['returnValue']}")

        self.wait(5)
        self.make_log(f"Sending application: {application}")
        app_result = self.do_send_app(application)
        self.make_log(f"Sending to application: {app_result['returnValue']}")
        self.wait(5)

    def make_log(self, message):
        self.logger.log(message)
        self.console.log(message)

    def get_applications(self):
        return applicationlist.applications

    def do_send_apphome(self):
        args = "\'{\"id\":\"com.webos.app.home\"}\'"
        return self.commander.send_command(f"{launch_commander} {args}")

    def do_send_app(self, application):
        args = f"\'{{\"id\":\"{application}\"}}\'"
        return self.commander.send_command(f"{launch_commander} {args}")

    def wait(self, seconds):
        time.sleep(seconds)

