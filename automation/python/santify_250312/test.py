import subprocess
import logging
import threading

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def install_app(app_name, ipk_path):
    def log_output(output):
        with open("log.log", "a") as log_file:
            log_file.write(output)


    def print_output(output):
        print(output)

    command = f"luna-send -i -f luna://com.webos.appInstallService/install '{{\"id\":\"{app_name}\", \"ipkUrl\": \"{ipk_path}\", \"subscribe\":true}}\'"
    stdout, stderr = run_command(command)

    def callback_handler(output):
        log_output(output)
        print_output(output)

    # Create a thread for the callback handler
    callback_thread = threading.Thread(target=callback_handler, args=(stdout,))

    # Start the thread
    callback_thread.start()

    # Wait for the thread to complete
    callback_thread.join()
    return stdout, stderr

def run_command(command):
    logging.info(f"Running command: {command}")
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
    if result.returncode == 0:
        logging.info("Command executed successfully")
    else:
        logging.error(f"Command failed with return code {result.returncode}")
    return result.stdout, result.stderr

if __name__ == "__main__":
    appId = "com.wasukumiao.tv"
    ipk_path = "/home/root/com.wasukumiao.tv_1241673_8.4.7_1718768773015_drm.ipk"
    stdout, stderr = install_app(appId, ipk_path)
    print("Standard Output:\n", stdout)

    print("Reading line by line from stdout:")

    # get kr.co.spotvnow.tvhdapp.v2 from string
    # string = "/mnt/lg/appstore/preinstall/kr.co.spotvnow.tvhdapp.v2_1223604_1.0.1_1697181601933_drm.ipk"
    # app_name = string.replace("/mnt/lg/appstore/preinstall/", "").split('_')[0]
    # logging.info(f"Extracted App Name: {app_name}")
    # print("App Name:", app_name)
