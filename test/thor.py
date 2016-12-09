#!/usr/bin/env python2.7

import getopt
import logging
import os
import socket
import sys
import re
import time

# Constants

HOST     = 'google.com'
ADDRESS  = '216.58.216.238'
PORT     = 80
PAGE     = '/'
PROGRAM  = os.path.basename(sys.argv[0])
LOGLEVEL = logging.INFO
PROCESSES= 1
REQUESTS = 1

# Utility Functions

def usage(exit_code=0):
    print >>sys.stderr, '''Usage: {} [-r REQUESTS -p PROCESSES -v] URL
Options:

    -h           Show this help message
    -v           Set logging to DEBUG level

    -r REQUESTS  Number of requests per process (default is 1)
    -p PROCESSES Number of processes (default is 1)
'''.format(PROGRAM)
    sys.exit(exit_code)

# TCPClient Class

class TCPClient(object):

    def __init__(self, address=ADDRESS, port=PORT):
        ''' Construct TCPClient object with the specified address and port '''
        self.logger  = logging.getLogger()                              # Grab logging instance
        self.socket  = socket.socket(socket.AF_INET, socket.SOCK_STREAM)# Allocate TCP socket
        self.address = address                                          # Store address to listen on
        self.port    = port                                             # Store port to lisen on
    def handle(self):
        ''' Handle connection '''
        self.logger.debug('Handle')
        raise NotImplementedError

    def run(self):
        ''' Run client by connecting to specified address and port and then
        executing the handle method '''
        try:
            # Connect to server with specified address and port, create file object
            self.socket.connect((self.address, self.port))
            self.stream = self.socket.makefile('w+')
        except socket.error as e:
            self.logger.error('Could not connect to {}:{}: {}'.format(self.address, self.port, e))
            sys.exit(1)

        self.logger.debug('Connected to {}:{}...'.format(self.address, self.port))

        # Run handle method and then the finish method
        try:
            self.handle()
        except Exception as e:
            self.logger.exception('Exception: {}', e)
        finally:
            self.finish()

    def finish(self):
        ''' Finish connection '''
        self.logger.debug('Finish')
        try:
            self.socket.shutdown(socket.SHUT_RDWR)
        except socket.error:
            pass    # Ignore socket errors
        finally:
            self.socket.close()

# EchoClient Class

class HTTPClient(TCPClient):
    def __init__(self, address=ADDRESS, port=PORT, host=HOST, page=PAGE):
        super(self.__class__,self).__init__(address, port)
        self.host = host
        self.page = page

    def handle(self):
        ''' Handle connection by reading data and then writing it back until EOF '''
        self.logger.debug('Handle')
        # Create request
        dataOut = 'GET {} HTTP/1.0\r\nHost: {}\r\n\r\n'.format(self.page,self.host)
        try:
            self.logger.debug('Write')
            # Write it
            self.stream.write(dataOut)
            self.stream.flush()
            # Read from Server to STDOUT
            self.logger.debug('Read')
            dataIn = self.stream.readline()
            while dataIn:
                sys.stdout.write(dataIn)
                dataIn = self.stream.readline()
        except socket.error:
            pass    # Ignore socket errors

# Main Execution

if __name__ == '__main__':
    # Parse command-line arguments
    try:
        options, arguments = getopt.getopt(sys.argv[1:], "hvr:p:")
    except getopt.GetoptError as e:
        usage(1)

    for option, value in options:
        if option == '-v':
            LOGLEVEL = logging.DEBUG
        elif option == '-r':
            REQUESTS = int(value)
        elif option == '-p':
            PROCESSES = int(value)
        else:
            usage(1)

    if arguments:
        arg = arguments[0]
    else:
        usage(2)

    # Set logging level
    logging.basicConfig(
        level   = LOGLEVEL,
        format  = '[%(asctime)s] %(message)s',
        datefmt = '%Y-%m-%d %H:%M:%S',
    )

    # Parse out URLs
    r = re.match('^(http://)?([^:/]*\.[^:/]*)(:[0-9]+)?(/.*)?$',arg)
    try:
        details = r.groups()  
    except:
        logging.error('Unable to parse {}'.format(arg))
        sys.exit(2)

    HOST = details[1]
    if (details[2]):
        PORT = int(details[2][1:])
    if (details[3]):
        PAGE = details[3]
    
    logging.debug('URL:  {}'.format(arg))
    logging.debug('HOST: {}'.format(HOST))
    logging.debug('PORT: {}'.format(PORT))
    logging.debug('PATH: {}'.format(PAGE))

    # Lookup host address
    try:
        ADDRESS = socket.gethostbyname(HOST)
    except socket.gaierror as e:
        logging.error('Unable to lookup {}: {}'.format(ADDRESS, e))
        sys.exit(1)

    # Run PROCESSES processes
    for p in xrange(PROCESSES):
        logging.debug('Forking')
        # Fork
        pid = os.fork()
        # Spoon
        if pid == 0:
            total = 0
            # Knife
            myPID = os.getpid()
            try:
                # Run REQUESTS requests
                for r in xrange(REQUESTS): 
                    client = HTTPClient(ADDRESS, PORT, HOST, PAGE)
                    start = time.time()
                    client.run()
                    end = time.time()
                    elapsed = end-start
                    total += elapsed
                    client.logger.debug(' {} | Elapsed time: {:.3f} second(s)'.format(myPID, elapsed))
            except KeyboardInterrupt:
                pass
            avgElapsed = total/REQUESTS
            client.logger.debug(' {} | Average elapsed time: {:.3f} second(s)'.format(myPID, avgElapsed))
            os._exit(0)
        
    if pid:
        for p in xrange(PROCESSES):
            f = True
            while f:
                logging.debug('Waiting')
                try:
                    pid, status = os.wait()
                    logging.debug('Process {} terminated with exit status {}'.format(pid,status))
                    f = False
                except OSError:
                    f = True
    

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
