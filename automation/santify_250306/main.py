from app import logger as Lg
from app import applicationsender as As
import random
import time

def main():
    sender = As.ApplicationSender()
    logger = Lg.Logger("Main", use_file=False)

    while True:
        random_value = random.randint(0, len(sender.get_applications()) - 1)
        random_application = sender.get_applications()[random_value]
        logger.log(f"Generated random value: {random_value}")
        logger.log(f"Pick application: {random_application}")
        sender.send_application(random_application)
        time.sleep(1)

if __name__ == '__main__':
    main()


