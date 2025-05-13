from app import logger as Lg
from app import applicationsender as As
import random
import time

def main():
    sender = As.ApplicationSender()
    logger = Lg.Logger("Main", use_file=False)
    logger.log("Main started.")

    logger.log("Executing sender for application")
    sender.execute()



    logger.log("Main finished.")


if __name__ == '__main__':
    main()


