import socket

def send_data_to_socket_server(host, port, message: str):
    try:
        # Create a socket object
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        # Connect to the server
        client_socket.connect((host, port))
        print(f"Connected to {host}:{port}")
        
        # Send data
        client_socket.send(message.encode())
        print(f"Sent: {message}")
        
        # Receive response (optional)
        response = client_socket.recv(1024)
        print(f"Received: {response.decode()}")
        
        # Close the connection
        client_socket.close()
        print("Connection closed")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    host = "127.0.0.1"  # Change to the server's IP address if needed
    port = 8180         # Port number
    #message = "https://myrient.erista.me/files/No-Intro/Nintendo%20-%20Game%20Boy/10-Pin%20Bowling%20%28USA%29%20%28Proto%29.zip"  # Message to send
    message = "http://ipv4.download.thinkbroadband.com/1GB.zip"
    
    send_data_to_socket_server(host, port, message)