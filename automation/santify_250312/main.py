from app import logger as Lg
from app import functionalcontroller as Fc

def main():
    log = Lg.Logger("Main", use_file=True, filename="Main.log")
    log.log("Main started.")
    fnctrl = Fc.FunctionalController()
    fnctrl.do_initialization()
    fnctrl.execute()
    log.log("Main finished.")


if __name__ == '__main__':
    main()


