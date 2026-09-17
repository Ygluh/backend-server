import socket

HOST = '127.0.0.1'
PORT = 9090

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((HOST, PORT))
server_socket.listen(1)

print(f"[SERVER] Слушаю на {HOST}:{PORT}...")

conn, addr = server_socket.accept()
print(f"[SERVER] Подключён клиент: {addr}")

data = conn.recv(1024).decode('utf-8')
print(f"[SERVER] Получено: {data}")

response = f"[SERVER] {data}"
conn.sendall(response.encode('utf-8'))
print(f"[SERVER] Отправлено: {response}")

conn.close()
server_socket.close()
print("[SERVER] Завершено.")
