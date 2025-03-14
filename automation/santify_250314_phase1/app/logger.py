import time
import os
class Logger:
    def __init__(self, module_name : str, use_file : bool = False, filename : str = "log.txt"):
        self.module_name = module_name
        self.use_file = use_file

        if use_file:
            curDir = os.getcwd();
            if (os.path.exists(curDir + "/log" + filename) == True):
                os.remove(curDir + "/log/" + filename)

            self.file_log = curDir + "/log/" + filename
            self.fd = open(self.file_log, 'a')
            self.log(f"Logger for {self.module_name} is starting in file mode")
        else:
            self.log(f"Logger for {self.module_name} is starting in console mode")


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
        if self.use_file:
            message = f"{self} {message}\n"
            self.fd.write(message)

    def __del__(self):
        if self.use_file:
            self.log(f"Logger for {self.module_name} in file mode is closed")
            self.use_file = False
            self.fd.close()
        else:
            self.log(f"Logger for {self.module_name} in console mode is closed")


class Message:
    instance = None
    def __new__(cls):
        if not hasattr(cls, 'instance'):
            cls.instance = super(Message, cls).__new__(cls)
        return cls.instance

    def __init__(self, message : str):
        self.message = f'{"message": {message}}'

    def __str__(self):
        return self.message

    def get_message(self):
        return self.message