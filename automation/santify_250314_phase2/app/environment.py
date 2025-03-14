from . import commander as Cmd
from . import logger as Lg
file_log = Lg.Logger("Environment", use_file=True, filename="Environment.log")
console = Lg.Logger("Environment", use_file=False)

def get_enviroment():
    response = Cmd.Commander().send_command("luna-send -n 1 -f luna://com.webos.service.sdx/getServer '{}'")
    file_log.log(f"Response: {response}")
    console.log(f"Response: {response}")
    return response['serverIndex'] == 'Production'


def set_environment(env):
    response = Cmd.Commander().send_command(f"luna-send -n 1 -f luna://com.webos.service.sdx/setServer '{{\"serverIndex\":\"{env}\"}}'")
    file_log.log(f"Response: {response}")
    console.log(f"Response: {response}")
    if response['returnValue'] == True:
        return True
    return False