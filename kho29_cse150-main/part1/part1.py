import sys
import argparse
import os
from os.path import exists
from datetime import datetime, timezone

def arguments():
    input = argparse.ArgumentParser(description="Reads a port number and a root file directory from the command line.")
    input.add_argument("-p", "--port", type=int, required=True, help="Port number for the server")
    input.add_argument("-d", "--directory", required=True, help="Root file directory for the server")
    return input.parse_args()

def validate_arguments(args):
    well_known_ports = set(range(0, 1024))
    registered_ports = set(range(1024, 49152))

    if(args.port != 80 and args.port in well_known_ports):
        sys.stdout.write("Well-known port number " + str(args.port) + " entered - could cause a conflict.\n")
        return False
    if(args.port != 80 and args.port in registered_ports):
        sys.stdout.write("Registered port number " + str(args.port) + " entered - could cause a conflict.\n")
        return False
    if(args.port > 49152):
        sys.stderr.write("Terminating program, port number is not allowed.\n")
        sys.exit(1)

def main():
    args = arguments()
    if not args:
        sys.stderr.write("Invalid arguments\n")
    else:
        #print(args.port, args.directory)  From part0
        directory_holder = str(args.directory)
        file_name = "{}/helloWorld.html".format(directory_holder)
        #print(file_name)
        file_exists = exists(file_name)
        if file_exists and os.path.splitext(file_name)[1].lower() == '.html':
            with open(file_name, "r") as file:
                content = file.read()
                content_size = os.stat(file_name).st_size

            if(os.path.splitext(file_name)[1].lower() == '.html'):
                content_type = 'text/html'
            date_info = os.stat(file_name)
            response_time = datetime.utcnow()
            mod_time = datetime.fromtimestamp(date_info.st_mtime, tz=timezone.utc)
        
            sys.stdout.write("HTTP/1.1 200 OK\r\n")
            sys.stdout.write("Content-Length: {}\r\n".format(content_size))
            sys.stdout.write("Content-Type: {}\r\n".format(content_type))
            sys.stdout.write("Date: {}\r\n".format(response_time.strftime('%a, %d %b %Y %H:%M:%S GMT')))
            sys.stdout.write("Last-Modified: {}\r\n".format(mod_time.strftime('%a, %d %b %Y %H:%M:%S GMT')))
            sys.stdout.write("\r\n")  # End of headers
            sys.stdout.write("{}\r\n".format(content))
'''
            with open("output.txt", "w") as output_file:
                output_file.write(f"HTTP/1.1 200 OK\r\n")
                output_file.write(f"Content-Length: {content_size}\r\n")
                output_file.write(f"Content-Type: {content_type}\r\n")
                output_file.write(f"Date: {response_time.strftime('%a, %d %b %Y %H:%M:%S GMT')}\r\n")
                output_file.write(f"Last-Modified: {mod_time.strftime('%a, %d %b %Y %H:%M:%S GMT')}\r\n")
                output_file.write("\r\n")  # End of headers
                output_file.write(f"{content}\r\n")
                
'''


if __name__ == "__main__":
    main()