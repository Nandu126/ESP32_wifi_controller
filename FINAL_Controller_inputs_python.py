import pygame
import socket
import struct
import time

pygame.init()

# Initialize the joystick
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

# Server address and port
server_address = '192.168.50.29'  # Replace with the IP address of your ESP32
server_port = 10000

# Create a socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to the server
    client_socket.connect((server_address, server_port))

    done = False
    while not done:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

        # Read and print the left Y-axis, right X-axis, and right Y-axis values
        left_y = joystick.get_axis(1)
        right_x = joystick.get_axis(2)
        
        # Read trigger values
        l2_trigger = joystick.get_axis(4)
        r2_trigger = joystick.get_axis(5)

        # Read button states
        r1_button = joystick.get_button(10)
        l1_button = joystick.get_button(9)
        x_button = joystick.get_button(0)

        # Send the values to the ESP32 as integers
        client_socket.send(b'I1')  # Send type identifier for integer
        client_socket.send(struct.pack('i', int(left_y)))
        
        client_socket.send(b'I2')
        client_socket.send(struct.pack('i', int(right_x)))

        client_socket.send(b'I3')
        client_socket.send(struct.pack('i', int(x_button)))
        
        client_socket.send(b'I4')
        client_socket.send(struct.pack('i', int(l2_trigger)))
        
        client_socket.send(b'I5')
        client_socket.send(struct.pack('i', int(r2_trigger)))

        client_socket.send(b'I6')
        client_socket.send(struct.pack('i', int(r1_button)))

        client_socket.send(b'I7')
        client_socket.send(struct.pack('i', int(l1_button)))
        
        # Add a short delay to control the sending rate
        time.sleep(0.001)  # Adjust the delay as needed

finally:
    # Close the socket and the joystick (usually not reached in an infinite loop)
    client_socket.close()
    joystick.quit()