import time
from . import applicationlist
from . import logger as Lg
from . import commander as Cmd
from . import eula as Eula
import random

launch_commander = "luna-send -n -f luna://com.webos.applicationManager/launch"
install_appPkg = "luna-send -i -f luna://com.webos.service.pkgInstall/install"
install_appSrv = "luna-send -i -f luna://com.webos.appInstallService/install"
find_ipk = "find / | grep ipk"

class ApplicationSender:
    def __init__(self):
        self.module_name = "ApplicationSender"
        self.logger = Lg.Logger(self.module_name, use_file=True, filename=f"{self.module_name}.log")
        self.console = Lg.Logger(self.module_name, use_file=False)
        self.commander = Cmd.Commander()
        self.eula = Eula.EulaApplication()
        self.log("Application sender initialized.")

    def get_list_ipks(self):
        [stdout, stderror] = self.commander.launch_command(find_ipk)

        if stderror:
            self.log(f"Error: {stderror}")
            return []

        ipk_list = []
        ids = []
        for line in stdout.splitlines():
            if line.endswith(".ipk"):
                if "/mnt/lg/appstore" not in line:
                    continue
                # append ipks to list
                ipk_list.append(line)
                # getting id from ipk
                id = line.replace("/mnt/lg/appstore/preinstall/", "").split('_')[0]
                # insert id to ids if not exists
                if id not in ids:
                    ids.append(id)

        applicationlist.applications = ids
        # self.log(f"IPK list: {ipk_list} \n IDS: {ids}")
        return ipk_list, ids

    def install(self, eula_flag):
        if eula_flag:
            [ipks, ids] = self.get_list_ipks()

            for (ipk, id_) in zip(ipks, ids):
                self.log(f"Installing application with id: {id_}")
                if self.do_install_appService(id_, ipk, True):
                    self.log(f"{id_} installed.")

        self.log(f"Installation finished.")
        return True



    def do_install_appService(self, id, ipkUrl, subscribe):
        subscribe = "true" if subscribe else "false"
        args = f"\'{{\"id\":\"{id}\",\"ipkUrl\":\"{ipkUrl}\",\"subscribe\":{subscribe}}}\'"
        return self.commander.install_command(f"{install_appSrv} {args}", id)

    def do_install_appPkg(self, args):
        if (id == "com.webos.app.home"):
            return Lg.Message("Cannot install app home.")

        id = f"\'{{\"id\":\"{args}\"}}\'"
        return self.commander.send_command(f"{install_appPkg} {id}")

    def execute(self):
        count=0
        while True:
            count = count + 1
            random_value = random.randint(0, len(self.get_applications()) - 1)
            random_application = applicationlist.applications[random_value]
            self.log(f"Generated random value: {random_value}")
            self.log(f"Pick application: {random_application}")
            self.send_application(random_application)
            # update timer for sending next application
            self.wait(100)

            if count > 100000:
                break


    def send_application(self, application):
        if application not in applicationlist.applications:
            self.log(f"Application {application} not found.")
            return

        # apphome_result = self.do_send_apphome()
        # self.log(f"launch app home: {apphome_result['returnValue']}")
        # self.wait(1)
        self.log(f"launching: {application}")
        app_result = self.do_send_app(application)
        if app_result['returnValue'] == False:
            self.log(f"Error: {app_result['errorText']}")
        else:
            self.log(f"Result of launch: {app_result['returnValue']}")
        self.wait(100)

    def log(self, message):
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

