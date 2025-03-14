

class Network:
    def __init__(self, usr, pwd):
        self.usr = usr
        self.pwd = pwd

    def connect(self):
        return True

    def get_data(self):
        return [self.usr, self.pwd]

    def send_data(self, data):
        pass

    def disconnect(self):
        pass

class NetworkController:
    def __init__(self, usr, pwd):
        self.network = Network(usr, pwd)
        self.network.connect()

    def get_data(self):
        return self.network.get_data()

    def send_data(self, data):
        self.network.send_data(data)

    def disconnect(self):
        self.network.disconnect()