import socket

HOST = '127.0.0.1'
PORT = 9090

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))
print(f"[CLIENT] Подключён к {HOST}:{PORT}")

message = "Hello World!"
client_socket.sendall(message.encode('utf-8'))
print(f"[CLIENT] Отправлено: {message}")

data = client_socket.recv(1024).decode('utf-8')
print(f"[CLIENT] Получено от сервера: {data}")

client_socket.close()
print("[CLIENT] Завершено.")
