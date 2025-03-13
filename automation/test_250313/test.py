import logger as Lg
import commander as Cmd
import subprocess
import json

consoleObj = Lg.Logger("test", use_file=False)
commandline = Cmd.Commander()

def read_json(json_data):
    try:
        data = json.loads(json_data)
        consoleObj.log(f"JSON Data: {data}")
        for app in data:
            if app.get("statusValue") == 30:
                consoleObj.log(f"App {app.get('id')} installed successfully")
            else:
                consoleObj.log(f"Failed to install app {app.get('id')}")

    except json.JSONDecodeError as e:
        consoleObj.log(f"Failed to decode JSON: {e}")

def install_app(app_name, ipk_path, subscribe=True):
    output = commandline.send_command(f"luna-send -i -f luna://com.webos.appInstallService/install '{{\"id\":\"{app_name}\", \"ipkUrl\": \"{ipk_path}\", \"subscribe\":{subscribe}}}'")
    return output
    # return ""

def run_command(command):
    consoleObj.log(f"Running command: {command}")
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
    output = process.communicate()
    consoleObj.log(f"Standard Output:\n{output}")

if __name__ == "__main__":
    appId = "com.wavve.ivi"
    ipk_path = "/mnt/lg/appstore/preinstall/com.wavve.ivi_1223782_1.0.4_1697527890244_drm.ipk"
    install_app(appId, ipk_path)
