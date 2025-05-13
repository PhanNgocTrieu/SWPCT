from . import applicationsender
from . import eula
from . import logger
from . import environment
import json

class FunctionalController:
    def __init__(self):
        self.module_name = "FunctionalController"
        self.logger = logger.Logger(self.module_name, use_file=True, filename=f"{self.module_name}.log")
        self.console = logger.Logger(self.module_name, use_file=False)
        self.appsender = applicationsender.ApplicationSender()
        self.logger.log("Functional controller initialized.")
        self.eulaObject = eula.EulaApplication()
        self.env = False
        self.eula = False

    def __del__(self):
        self.logger.log("Functional controller is being destroyed.")

    def get_data(self):
        return self.data

    def do_initialization(self):
        self.logger.log("Initialization started.")

        envir = environment.get_enviroment()
        if (envir == False):
            environment.set_environment("QA2")

        self.env = True
        ret = self.eulaObject.get_eula()
        if (ret == False):
            response = self.eulaObject.enable_eula()
            if (response['returnValue'] == False):
                return False
            self.eula = True

        return True

    def do_installation(self):
        self.logger.log("Installation started.")
        self.appsender.install(self.eula)
        self.logger.log("Installation finished.")

    def execute(self):
        if (self.eula == False or self.env != False):
            self.logger.log(f"Execution failed due to environment: {self.env} and eula: {self.eula}")
            return

        self.logger.log("Execution started.")
        self.appsender.execute()
        self.logger.log("Execution finished.")

    def get_data_length(self):
        return len(self.data)