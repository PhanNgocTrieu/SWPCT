import time
import os
class Logger:
    def __init__(self, module_name : str, use_file : bool = False, filename : str = "log.txt"):
        self.module_name = module_name
        self.use_file = use_file
        if self.use_file:
            file_log = self.make_log_dir() + "/" + filename
            self.filename = file_log
            self.fd = open(self.filename, 'a')
            self.log(f"Logger for {self.module_name} is starting in file mode")
        else:
            self.log(f"Logger for {self.module_name} is starting in console mode")

    def make_log_dir(self):
        curDir = os.getcwd();
        if (os.path.exists(curDir + "/log") == False):
            os.mkdir(curDir + "/log")

        # remove log file
        os.remove(curDir + "/log" + self.filename)

        return curDir + "/log"

    def __str__(self):
        return f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] [{self.module_name}]"

    def remove_all_files(self):
        if self.use_file:
            os.remove(self.filename)
            self.log(f"Logger for {self.module_name} in file mode is removed")
        else:
            self.log(f"Logger for {self.module_name} in console mode is removed")

    def log(self, message):
        if self.use_file:
            self.log_file(message)
        else:
            print(f"{self} {message}")

    def log_file(self, message):
        message = f"{self} {message}\n"
        self.fd.write(message)

    def __del__(self):
        if self.use_file:
            self.log(f"Logger for {self.module_name} in file mode is closed")
            self.use_file = False
            self.fd.close()
        else:
            self.log(f"Logger for {self.module_name} in console mode is closed")
