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
        self.eulaObject = eula.EulaApplication()
        self.env = False
        self.eula = False
        self.appInstalled = False
        self.initialized = False

        self.log("Functional controller initialized.")

    def __del__(self):
        self.log("Functional controller is being destroyed.")

    def do_initialization(self):
        self.log("Initialization started.")
        envir = environment.get_enviroment()
        if (envir == False):
            self.log("Environment is not set to Production. set to QA2")
            environment.set_environment("QA2")

        self.env = True
        ret = self.eulaObject.get_eula()
        if (ret == False):
            response = self.eulaObject.enable_eula()
            self.logger.log(f"Response: {response}")
            if (response['returnValue'] == False):
                return False

        self.eula = True

        if (self.eula == True or self.env != True):
            self.initialized = True


        self.do_installation()
        self.log("Initialization finished.")

    def do_installation(self):
        self.log("Installation started.")
        self.appInstalled = self.appsender.install(self.eula)
        self.log("Installation finished.")

    def execute(self):
        if (self.initialized == False or self.appInstalled == False):
            self.log("Execution failed due to initialization or installation failure.")
            return

        self.log("Execution started.")
        self.appsender.execute()
        self.log("Execution finished.")

    def log(self, message):
        self.logger.log(message)
        self.console.log(message)