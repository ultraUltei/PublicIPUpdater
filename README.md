# PublicIPUpdater
This small C program monitors the public IP of your system and automatically sends an email notification whenever it changes. It works by checking the network interface status and comparing the current public IP with the last known IP stored in a file.  

---

## Requirements

- Linux system  
- `msmtp` (or a similar mail client) installed and properly configured  

---

## Installation

1. Download `publicip-daemon.c` and `sendmail.sh` and place them in the same directory.  
2. Compile the daemon:

   ```bash
   gcc -o publicip-daemon publicip-daemon.c
   
3. Place publicip.start in /etc/local.d/ so that it runs at system startup. Make sure to modify it with your network interface and correct path to the daemon:
   ```bash
   #!/bin/bash
   cd /path/to/your/directory && ./publicip-daemon /sys/class/net/<your network interface>/operstate &

4. Ensure both scripts are executable:
   ```bash
   chmod +x sendmail.sh publicip-daemon /etc/local.d/publicip.start

## Tips

In publicip-daemon.c there are two #define values that control the monitoring intervals:

`ONLINE_CYCLE` Time in seconds between checks when internet is available (default 10 minutes).

`OFFLINE_CYCLE` Time in seconds between checks when no internet access is detected (default 5 minutes).

You can modify these values to adjust how frequently the daemon checks for IP changes or connectivity issues.

---

## Usage

Once installed and the system is rebooted, the daemon will run in the background automaticly.
