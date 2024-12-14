import sys
import argparse
import os
from os.path import exists
from datetime import datetime, timezone
import socket
import csv

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

def create_server_socket(port):
    server_socket = socket.socket()
    server_socket.bind(("127.0.0.1", port))
    server_socket.listen(1)
    return server_socket

def client_request(connection_socket, root_directory, client_ip, client_port, server_ip, server_port):
    request = connection_socket.recv(1024).decode('utf-8')
    #print(request)
    csvfile = open('kho29SocketOutput.csv', 'a', newline='')
    writer = csv.writer(csvfile)

    if not request:
        sys.stderr.write("Failed to decode\n")
        sys.exit(1)
    # Parse the HTTP request
    request_lines = request.split('\n')
    method, path, _ = request_lines[0].split()
    # Construct the full file path
    file_path = os.path.join(root_directory, path[1:])  # Remove leading "/"'
    chunk = 1024

    # 505
    #print(request_lines[0].split()[-1])
    if ("HTTP/1.1" != request_lines[0].split()[-1]):
        status_code = "HTTP/1.1 505 HTTP Version Not Supported\r\n"
        response_time = datetime.utcnow()
        date = "Date: {}\r\n".format(response_time.strftime('%a, %d %b %Y %H:%M:%S GMT'))
        connection = "Connection: close\r\n"
        response = status_code + date + connection
        connection_socket.sendall(response.encode())
        connection_socket.close()
        sys.stdout.write("Connection to {}, {} is now closed.\n".format(client_ip, client_port))
        with open("kho29HTTPResponse.txt", 'a+', newline='') as f:
            f.write(response)
        writer.writerow(["Client request served", "4-Tuple:", server_ip, server_port, client_ip, client_port, "Requested URL", path, status_code, "Bytes transmitted:", len(response.encode())])
    
    #501
    elif(method != "GET"):
        status_code = "HTTP/1.1 501 Not Implemented\r\n"
        response_time = datetime.utcnow()
        date = "Date: {}\r\n".format(response_time.strftime('%a, %d %b %Y %H:%M:%S GMT'))
        connection = "Connection: close\r\n"
        response = status_code + date + connection
        connection_socket.sendall(response.encode())
        connection_socket.close()
        sys.stdout.write("Connection to {}, {} is now closed.\n".format(client_ip, client_port))
        with open("kho29HTTPResponse.txt", 'a+', newline='') as f:
            f.write(response)
        writer.writerow(["Client request served", "4-Tuple:", server_ip, server_port, client_ip, client_port, "Requested URL", path, status_code, "Bytes transmitted:", len(response.encode())])
    
    #404
    elif(not os.path.isfile(file_path)):
        status_code = "HTTP/1.1 404 Not Found\r\n"
        response_time = datetime.utcnow()
        date = "Date: {}\r\n".format(response_time.strftime('%a, %d %b %Y %H:%M:%S GMT'))
        connection = "Connection: close\r\n"
        response = status_code + date + connection
        connection_socket.sendall(response.encode())
        connection_socket.close()
        sys.stdout.write("Connection to {}, {} is now closed.\n".format(client_ip, client_port))
        with open("kho29HTTPResponse.txt", 'a+', newline='') as f:
            f.write(response)
        writer.writerow(["Client request served", "4-Tuple:", server_ip, server_port, client_ip, client_port, "Requested URL", path, status_code, "Bytes transmitted:", len(response.encode())])
    
    #200
    elif(exists(file_path) and os.path.isfile(file_path)):
        file_extension = os.path.splitext(file_path)[1].lower()
        response_time = datetime.utcnow()
        date_info = os.stat(file_path)
        mod_time = datetime.fromtimestamp(date_info.st_mtime, tz=timezone.utc)
        with open(file_path, "rb") as file:
            body = file.read()
            content_size = os.stat(file_path).st_size
            
        # Determine the Content-Type based on the file extension
        if file_extension == '.html':
            content_type = "text/html"
        elif file_extension == '.csv':
            content_type = 'csv'
        elif file_extension in ['.png', '.jpg', '.gif']:
            content_type = 'image/' + file_extension[1:]
        elif file_extension == '.zip':
            content_type = 'application/zip'
        elif file_extension == '.txt':
            content_type = 'text/plain'
        elif file_extension == ".doc":
            content_type = 'application/msword'
        elif file_extension == ".docx":
            content_type = 'application/vnd.openxmlformats-officedocument.wordprocessingml.document'
        status_code = "HTTP/1.1 200 OK\r\n"
        content_length = "Content-Length: {}\r\n".format(content_size)
        type_header = "Content-Type: {}\r\n".format(content_type)
        last_mod = "Last-Modified: {}\r\n".format(mod_time.strftime('%a, %d %b %Y %H:%M:%S GMT'))
        date = "Date: {}\r\n".format(response_time.strftime('%a, %d %b %Y %H:%M:%S GMT'))
        connection = "Connection: close\r\n"
        newline = "\r\n"
        response = status_code + content_length + type_header + date + last_mod + connection + newline
        connection_socket.sendall(response.encode())
        connection_socket.sendall(body)

        #response_header for csv file
        response_header = status_code + content_length + type_header + date + last_mod + connection + newline
        connection_socket.close()
        sys.stdout.write("Connection to {}, {} is now closed.\n".format(client_ip, client_port))
        with open("kho29HTTPResponse.txt", 'a+', newline='') as f:
            f.write(response_header)
        writer.writerow(["Client request served", "4-Tuple:", server_ip, server_port, client_ip, client_port, "Requested URL", path, status_code, "Bytes transmitted:", len(response.encode())])

def main():
    args = arguments()

    if not args:
        sys.stderr.write("Invalid arguments\n")
        sys.exit(1)

    server_socket = create_server_socket(args.port)
    ip_address, port = server_socket.getsockname()
    sys.stdout.write("Welcome socket created: {}, {}\n".format(ip_address, port)) #change to 2.7.6
    while True:
        connection_socket, client_address = server_socket.accept()
        client_ip, client_port = client_address
        sys.stdout.write("Connection socket created: {}, {}\n".format(client_ip, client_port)) #change to 2.7.6
        client_request(connection_socket, args.directory, client_ip, client_port, ip_address, args.port)

if __name__ == "__main__":
    main()
