import subprocess
import json
import time
import os
import logger as Lg
import select
import threading

launch_commander = "luna-send -n 1 -f luna://com.webos.applicationManager/launch"
args_home = "\'{\"id\":\"com.webos.app.home\"}\'"
permission="mount -o remount,rw /"


class Commander:
    _instance = None
    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            cls._instance = super(Commander, cls).__new__(cls, *args, **kwargs)
        return cls._instance

    def __init__(self):
        if not hasattr(self, 'initialized'):
            self.module_name = "Commander"
            self.logger = Lg.Logger(self.module_name, use_file=True, filename=f"{self.module_name}.log")
            self.console = Lg.Logger(self.module_name, use_file=False)
            self.make_log("Commander initialized.")
            self.mount = False
            self.initialized = True

    def write_output_to_file(self, process, json_path, timeout, start_time, flags):
        json_file = open(json_path, "w")
        try:
            while True:
                reads = [process.stdout.fileno(), process.stderr.fileno()]
                ret = select.select(reads, [], [], timeout)
                if ret[0]:
                    for fd in ret[0]:
                        if fd == process.stdout.fileno():
                            output = process.stdout.readline()
                            json_file.write(output)
                            if output:
                                start_time = time.time()  # Reset the timer on new output
                        elif fd == process.stderr.fileno():
                            error = process.stderr.readline()
                if time.time() - start_time > timeout:
                    process.kill()
                    break

                if process.poll() is not None:
                    break

        except Exception as e:
            self.make_log(f"Exception occurred: {str(e)}")

        finally:
            flags['file'] = True
            process.stdout.close()
            process.stderr.close()
            process.wait()
            json_file.close()




    def install_command(self, command, application="installer"):
        if not self.mount:
            self.mounting()

        self.make_log(f"Sending command: {command}")
        process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout_data = []
        stderr_data = []
        start_time = time.time()
        timeout = 30  # Timeout after 30 seconds of inactivity
        string_data = ""
        flags = {'file': False}

        curDir = os.getcwd()
        if not os.path.exists(curDir + "/install"):
            os.makedirs("install")

        # Create a JSON file to store the output
        json_path = f"{curDir}/install/{application}.json"
        self.console.log(f"Writing output to {json_path}")


        thread = threading.Thread(target=self.write_output_to_file, args=(process, json_path, timeout, start_time, flags))
        thread.start()
        thread.join()

        # try:
        #     while True:
        #         reads = [process.stdout.fileno(), process.stderr.fileno()]
        #         ret = select.select(reads, [], [], timeout)
        #         if ret[0]:
        #             for fd in ret[0]:
        #                 if fd == process.stdout.fileno():
        #                     output = process.stdout.readline()
        #                     string_data += output.strip()
        #                     if output:
        #                         stdout_data.append(output.strip())
        #                         start_time = time.time()  # Reset the timer on new output
        #                 elif fd == process.stderr.fileno():
        #                     error = process.stderr.readline()
        #                     if error:
        #                         stderr_data.append(error.strip())
        #         if time.time() - start_time > timeout:
        #             self.make_log("Timeout: No output received for 10 seconds.")
        #             process.kill()
        #             break
        #         if process.poll() is not None:
        #             break

        # except Exception as e:
        #     self.make_log(f"Exception occurred: {str(e)}")

        # finally:
        #     self.make_log("Closing stdout and stderr")
        #     process.stdout.close()
        #     process.stderr.close()
        #     process.wait()

        while not flags['file']:
            time.sleep(1)

        # try:
        #     stdout_json = json.dumps(stdout_data)
        # except json.JSONDecodeError as e:
        #     self.make_log(f"JSON decode error: {str(e)}")
        #     stdout_json = json.dumps(stdout_data)
        json_objects = self.convert_to_json_objects(string_data)
        self.print_jsonobjects(json_objects)
        # self.make_log(f"stdout_data: {json_objects}")
        return string_data, stderr_data

    def print_jsonobjects(self, json_objects):
        for obj in json_objects:
            self.make_log(f"JSON object: {obj}")

    def convert_to_json_objects(self,data):
        try:
            # Split the data into individual JSON strings
            json_strings = data.split('}{')
            json_strings = [s + '}' if not s.endswith('}') else s for s in json_strings]
            json_strings = ['{' + s if not s.startswith('{') else s for s in json_strings]

            # Parse each JSON string into a dictionary
            json_objects = [json.loads(json_str) for json_str in json_strings]
            return json_objects

        except json.JSONDecodeError as e:
            self.make_log(f"JSON decode error: {str(e)}")
            return []


    def another_install(self, command):
        # if not self.mount:
        #     self.mounting()
        self.make_log(f"Sending command: {command}")
        process = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        return process.stdout, process.stderr

    def launch_command(self, command):
        if not self.mount:
            self.mounting()
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
        return result.stdout, result.stderr


    def mounting(self):
        if not self.mount:
            self.make_log("Mounting filesystem")
            os.system(permission)
            self.mount = True

    def do_command(self, command):
        self.logger.log(f"Sending command: {command}")
        if not self.mount:
            self.mounting()
        os.system(command)

    def make_log(self, message):
        self.logger.log(message)
        self.console.log(message)

    def wait(self, seconds):
        time.sleep(seconds)