#! /usr/bin/env python3

import time
import os

def main():
    # add a wawit time after bootup before running the script
    time.sleep(60)

    # get to the home directory
    os.chdir(os.path.expanduser("~"))

    # check if an rsync have already been run today
    if os.path.exists(f"home_server/aziz-work/laptop_backup/$(date +%Y-%m-%d)"):
        os.system("notify-send 'Rsync backup' 'Backup already ran today' --icon=dialog-information")
        exit(0)
    else:
        os.makedirs(f"home_server/aziz-work/laptop_backup/$(date +%Y-%m-%d)", exist_ok=True)
        # send a notification of the start of the process
        os.system("notify-send 'Rsync backup' 'Backup started' --icon=dialog-information")

        # run rsync to backup home directory to home_server and send a notification of the start and end of the process
        os.system("rsync -avp --exclude='home_server' --exclude='Nextcloud' --exclude='.cache' --exclude='.conda' --exclude='.cargo' --exclude='.local/share' /home/ home_server/$USER-work/laptop_backup/$(date +%Y-%m-%d)")

        # send a notification of the end of the process
        os.system("notify-send 'Rsync backup' 'Backup completed' --icon=dialog-information")
        exit(0)

if __name__ == "__main__":
    main()