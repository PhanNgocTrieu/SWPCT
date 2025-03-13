import time
from . import applicationlist
from . import logger as Lg
from . import commander as Cmd
from . import eula as Eula
import random

launch_commander = "luna-send -n 1 -f luna://com.webos.applicationManager/launch"
install_appPkg = "luna-send -n 1 -f luna://com.webos.service.pkgInstall/install"
install_appSrv = "luna-send -n 1 -f luna://com.webos.service.appinstallService/install"
find_ipk = "find / | grep ipk"

class ApplicationSender:
    def __init__(self):
        self.module_name = "ApplicationSender"
        self.logger = Lg.Logger(self.module_name, use_file=True, filename=f"{self.module_name}.log")
        self.console = Lg.Logger(self.module_name, use_file=False)
        self.commander = Cmd.Commander()
        self.eula = Eula.EulaApplication()
        self.make_log("Application sender initialized.")

    def get_list_ipks(self):
        [stdout, stderror] = self.commander.launch_command(find_ipk)

        if stderror:
            self.make_log(f"Error: {stderror}")
            return []

        ipk_list = []
        ids = []
        for line in stdout.splitlines():
            if line.endswith(".ipk"):
                # append ipks to list
                ipk_list.append(line)

                # getting id from ipk
                id = line.replace("/mnt/lg/appstore/preinstall/", "").split('_')[0]

                # insert id to ids if not exists
                if id not in ids:
                    ids.append(id)

        return ipk_list, ids

    def install(self, eula_flag):
        if eula_flag:
            [ipks, ids] = self.get_list_ipks()

            for app in applicationlist.install_app:
                self.make_log(f"Installing application: {app}")
                self.do_install_appPkg(app)
                self.wait(5)


        self.logger.log("Installation finished.")


    def do_install_appService(self, id, ipkUrl, subscribe):
        args = f"\'{{\"id\":\"{id}\",\"ipkUrl\":\"{ipkUrl}\",\"subscribe\":{subscribe}}}\'"
        return self.commander.send_command(f"{install_appPkg} {args}")

    def do_install_appPkg(self, args):
        id = f"\'{{\"id\":\"{args}\"}}\'"
        return self.commander.send_command(f"{install_appPkg} {id}")

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

