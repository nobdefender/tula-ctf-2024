from socketserver import *
from main import main


class Handler(StreamRequestHandler):
    def print(self, *w):
        s = ('\n'.join([str(i) for i in w]) + '\n').encode('utf-8')
        self.request.sendall(s)

    def input(self, w=""):
        if len(w) != 0:
            self.request.sendall(w.encode('utf-8'))
        return self.rfile.readline().strip().decode('utf-8')

    def handle(self) -> None:
        try:
            main(lambda *w: self.print(*w), lambda w="": self.input(w))
        except Exception as e:
            self.print(e)


if __name__ == '__main__':
    # Есть Address already in use? Подожди 1 минуту
    HOST, PORT = 'localhost', 9999

    with ThreadingTCPServer((HOST, PORT), Handler) as server:
        print('listen on', HOST, PORT)
        server.serve_forever()
