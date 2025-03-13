from . import logger as Lg
from . import commander as Cmd
import time

disable_eula = """
luna-send -n 1 -f luna://com.webos.settingsservice/setSystemSettings '{
    "settings": {
        "eulaStatus": {
            "customAdAllowed": false,
            "takeOnAllowed": false,
            "additional3Allowed": false,
            "acrOnAllowed": false,
            "additionalDataAllowed": false,
            "networkAllowed": true,
            "chpAllowed": false,
            "acrAllowed": false,
            "additional4Allowed": false,
            "voice2Allowed": false,
            "additional1Allowed": false,
            "acrGdprAllowed": false,
            "remoteDiagAllowed": false,
            "acrAdAllowed": false,
            "generalTermsAllowed": false,
            "additional5Allowed": false,
            "additional2Allowed": false,
            "shoppingOnAllowed": false,
            "voiceAllowed": false,
            "cookiesAllowed": false,
            "customadsAllowed": false,
            "thirdPartySharingAllowed": false,
            "veranceOnAllowed": false
        }
    }
}'
"""


enable_eula = """
luna-send -n 1 -f luna://com.webos.settingsservice/setSystemSettings '{
    "settings": {
        "eulaStatus": {
            "customAdAllowed": false,
            "takeOnAllowed": false,
            "additional3Allowed": false,
            "acrOnAllowed": false,
            "additionalDataAllowed": false,
            "networkAllowed": true,
            "chpAllowed": true,
            "acrAllowed": false,
            "additional4Allowed": false,
            "voice2Allowed": false,
            "additional1Allowed": false,
            "acrGdprAllowed": false,
            "remoteDiagAllowed": false,
            "acrAdAllowed": false,
            "generalTermsAllowed": true,
            "additional5Allowed": false,
            "additional2Allowed": false,
            "shoppingOnAllowed": false,
            "voiceAllowed": false,
            "cookiesAllowed": false,
            "customadsAllowed": false,
            "thirdPartySharingAllowed": false,
            "veranceOnAllowed": false
        }
    }
}'
"""

class EulaApplication:
    _instance = None

    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super(EulaApplication, cls).__new__(cls)
        return cls._instance

    def __init__(self):
        if not hasattr(self, 'initialized'):  # Ensure __init__ is only called once
            self.logger = Lg.Logger("EulaApplication", use_file=True, filename="EulaApplication.log")
            self.commander = Cmd.Commander()
            self.eula_flag = self.get_eula()
            self.initialized = True

    # def sequence_confirm_eula(self):
    #     # sending to request launch eula
    #     Command_sequences = [
    #         self.request_launch_eula,
    #         self.request_confirm_eula,
    #         self.request_confirm_eula,
    #         self.request_agree
    #     ]
    #     # Running sequence
    #     for command in Command_sequences:
    #         command()

    def enable_eula(self):
        return self.commander.send_command(enable_eula)

    def disable_eula(self):
        return self.commander.send_command(disable_eula)


    # def request_launch_eula(self):
    #     self.commander.send_command("luna-send -n 1 -f luna://com.webos.applicationManager/launch '{\"id\":\"com.webos.app.firstuse\"}'")
    #     time.sleep(5)

    # def request_confirm_eula(self):
    #     self.commander.send_command("luna-send -n 1 -f luna://com.webos.service.networkinput/sendSpecialKey '{\"inputType\":\"\",\"key\":\"'ENTER'\",\"type\":1}'")
    #     self.commander.send_command("luna-send -n 1 -f luna://com.webos.service.networkinput/sendSpecialKey '{\"inputType\":\"\",\"key\":\"'ENTER'\",\"type\":0}'")

    # def request_agree(self):
    #     self.commander.send_command("luna-send -n 1 -f luna://com.webos.service.networkinput/sendSpecialKey '{\"inputType\":\"\",\"key\":\"'RIGHT'\",\"type\":1}'")
    #     self.commander.send_command("luna-send -n 1 -f luna://com.webos.service.networkinput/sendSpecialKey '{\"inputType\":\"\",\"key\":\"'RIGHT'\",\"type\":0}'")
    #     time.sleep(0.5)
    #     self.commander.send_command("luna-send -n 1 -f luna://com.webos.service.networkinput/sendSpecialKey '{\"inputType\":\"\",\"key\":\"'ENTER'\",\"type\":1}'")
    #     self.commander.send_command("luna-send -n 1 -f luna://com.webos.service.networkinput/sendSpecialKey '{\"inputType\":\"\",\"key\":\"'ENTER'\",\"type\":0}'")

    def get_eula(self):
        response = self.commander.send_command("luna-send -n 1 -f luna://com.webos.settingsservice/getSystemSettings '{\"keys\":[\"eulaStatus\"]}'")
        if (response["settings"]["eulaStatus"]["generalTermsAllowed"] == False
            or response["settings"]["eulaStatus"]["networkAllowed"] == False
            or response["settings"]["eulaStatus"]["chpAllowed"] == False):
            return False
        return True

    def do_check_eula(self):
        return self.eula_flag
