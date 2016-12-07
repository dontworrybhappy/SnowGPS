#!/usr/bin/env python2.7

import getopt
import os
import sys
import signal

# Global Variables

v = False
t = 3
command = ''
count = 1

PROGRAM_NAME = os.path.basename(sys.argv[0])

# Functions

def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def usage(exit_code=0):
	print '''Usage: timeout.py [-t SECONDS] command...

Options:

      -t SECONDS  Timeout duration before killing command (default is 10 seconds)
      -v          Display verbose debugging output
'''.format(PROGRAM_NAME)
	sys.exit(1)

def handler(signum, frame):
	debug('Alarm triggered after {} seconds', t)
	debug('Killing PID {}', pid)
	os.kill(pid, signal.SIGTERM)
	debug('Disabling Alarm....')
	debug('Process {} terminated with exit status {}' , pid, signum)
	#print "HANDLER"
	
def debug(message, *args):
	if v:
		print message.format(*args)


'''def signal.signal(
	signal.SIGALRM,
	handler
)'''

# Parse Command line arguments
try:
    options, arguments = getopt.getopt(sys.argv[1:], "ht:v")
except getopt.GetoptError as e:
    error(e)

for option, value in options:
	if option == '-h':
		usage(0)
	elif (option == '-v'):
		v = True
	elif (option == '-t'):
		t = int(value)

	if len(option) == 1:
		usage(1)


command = arguments


#testing parsing of command line
'''print command
print v
print t'''

# Main Execution

try:
	debug('Forking...')
	pid = os.fork()
	
except OSError as e:# Error
	error('Unable to fork: {}', e)

if pid == 0:    # Child
	try:
		#print command
		debug('Executing command...')
        	os.execvp( command[0], command)
		
	except OSError as e:
		error('Unable to exec: {}', e)
else:           # Parent
	debug('Enabling alarm...')
	signal.signal(signal.SIGALRM, handler)
	signal.alarm(int(t))
	
	try:
		debug('Waiting...')
		pid, status = os.wait()
		

	except OSError as e:
		pid, status = os.wait()
	
	sys.exit(status)



