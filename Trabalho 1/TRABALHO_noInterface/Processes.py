
# Classe Processos com seus atributos

class Processes:
    def __init__(self, nome, tempoCPU, tempoCheg):
        self.nome = nome
        self.tempoCPU = int(tempoCPU)
        self.tempoRestante = int(tempoCPU)
        self.tempoCheg = int(tempoCheg)
        self.inicio = None
        self.final = None
        self.tempoEspera = 0
        self.tempoResposta = 0

    def __lt__(self, other):
        return self.tempoRestante < other.tempoRestante
