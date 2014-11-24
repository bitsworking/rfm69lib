"""
You can see all commands with `$ fab -l`. Typical usages:
"""
import os
import time
from fabric.api import local, run, env, put, get

RASPBERRY_PATH = "/opt/rfm69/"

# Change to fabfile directory, to make relative paths work
DIR_SCRIPT = os.path.dirname(os.path.realpath(__file__))
os.chdir(DIR_SCRIPT)

env.use_ssh_config = True

# Default hosts
if not env.hosts:
    env.hosts = ["usblooper"]

def upload():
    """ Upload python script to RFIDPi """
    put("*", RASPBERRY_PATH)

def uploadx():
    """ Upload python script to RFIDPi """
    put("*.c", RASPBERRY_PATH)    
    put("*.h", RASPBERRY_PATH)    
    put("Makefile", RASPBERRY_PATH)

# def build():
    # run