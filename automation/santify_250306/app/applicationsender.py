import time
from . import applicationlist
from . import logger as Lg
from . import commander as Cmd

launch_commander = "luna-send -n 1 -f luna://com.webos.applicationManager/launch"

class ApplicationSender:
    def __init__(self):
        self.module_name = "ApplicationSender"
        self.logger = Lg.Logger(self.module_name, use_file=True, filename=f"{self.module_name}.log")
        self.console = Lg.Logger(self.module_name, use_file=False)
        self.commander = Cmd.Commander()
        self.make_log("Application sender initialized.")

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

