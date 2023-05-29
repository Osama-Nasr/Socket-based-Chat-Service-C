# Socket-based Chat Service

This is a simple chat service implemented using sockets and TCP in C. It allows devices to send and receive messages over a network. The chat service consists of two scripts: `client.c` and `server.c`.

## Client Script (`client.c`)

The `client.c` script represents a chat client that connects to the server. Each client can send and receive messages. Here's how to use the script:

1. Open a terminal.

2. Compile the client script:
   - Execute the following command:
     ```
     gcc client.c -o client
     ```

3. Run the client script:
   - Execute the following command:
     ```
     ./client <IP address>
     ```
   - Replace `<IP address>` with the IP address of the device running the server script.

4. Chatting:
   - Enter messages in the client's terminal to send them to the other connected client.
   - The messages will be displayed in the respective client's terminal.

## Server Script (`server.c`)

The `server.c` script acts as the chat server. It listens for incoming connections from clients and relays messages between them. Here's how to use the script:

1. Open a terminal.

2. Compile the server script:
   - Execute the following command:
     ```
     gcc server.c -o server
     ```

3. Run the server script:
   - Execute the following command:
     ```
     ./server
     ```

## Notes

- The chat service uses TCP/IP sockets, which provide reliable and ordered message delivery.
- The server script listens for incoming connections from clients and relays messages between them.
- The client script connects to the server and allows users to send and receive messages.
- The server listens on port 8080, and the clients connect to this port.
- The server supports up to two clients (defined by `MAX_CLIENTS` in `server.c`).
- Multiple instances of the client script can be run to facilitate chat sessions between different users.
- Type a message in the client's terminal and press Enter to send it to the other connected client.
- To exit the chat session, simply close the client's terminal or use Ctrl+C to terminate the server script.

Please note that this is a basic implementation for educational purposes. It does not include advanced features like authentication, encryption, or error handling. Feel free to modify and enhance the code to suit your specific requirements.

**Disclaimer:** Ensure that you have the necessary permissions to establish connections and communicate over the network.
