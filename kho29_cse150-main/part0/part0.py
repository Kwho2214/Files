import argparse
import sys

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
    if not validate_arguments(args):
        
    #print(args.port)
    #print(args.directory)
        print(args.port, args.directory)

if __name__ == "__main__":
    main()
