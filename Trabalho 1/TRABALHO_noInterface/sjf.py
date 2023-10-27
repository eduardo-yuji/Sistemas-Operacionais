import sys
from Processes import Processes

def definePaths(argv):
    arqPath = argv[1]
    saida1Path = argv[2]
    return arqPath, saida1Path

def abrirArq(paths):
    saida1 = open(paths[1], "w")
    return saida1

def leituraArq(arq):
    p = []

    with open(arq, 'r') as arquivo:
        linhas = arquivo.readlines()

    nomes = linhas[0].strip().split(';')
    temposCPU = linhas[1].strip().split(';')
    temposCheg = linhas[2].strip().split(';')

    for i in range(min(len(nomes), len(temposCPU)) - 1):
        nome = nomes[i + 1]

        tempoCPU = temposCPU[i + 1]
        try:
            tempoCPU = int(tempoCPU)
            if tempoCPU <= 0:
                print(f"Erro no tempo de CPU do processo {nome}\n")
                continue
        except ValueError:
            print(f"Erro no tempo de CPU do processo {nome}\n")
            continue

        tempoCheg = temposCheg[i + 1]
        try:
            tempoCheg = int(tempoCheg)
            if tempoCheg < 0:
                print(f"Erro no tempo de chegada do processo {nome}\n")
                continue
        except ValueError:
            print(f"Erro no tempo de chegada do processo {nome}\n")
            continue

        processo = Processes(nome, tempoCPU, tempoCheg)
        p.append(processo)

    return p

def SJFescalonador(processos):
    tempo_atual = 0
    fila_execucao = []
    relatorio = []
        
    while processos or fila_execucao:

        #for p in processos:
        #   if p.tempoCheg <= tempo_atual:          
        #       fila_execucao.append(p)
        #        processos.remove(p)

        processosNaoExec = [p for p in processos if p.tempoCheg <= tempo_atual]
        fila_execucao.extend(processosNaoExec)
        for p in processosNaoExec:
            processos.remove(p)

        if fila_execucao:
            fila_execucao.sort(key=lambda x: x.tempoRestante)     

            processo_em_execucao = fila_execucao[0]
            processo_em_execucao.tempoRestante -= 1
            for processo in fila_execucao[1:]:
                processo.tempoEspera += 1
            if processo_em_execucao.tempoRestante == 0:
                processo_em_execucao.final = tempo_atual + 1
                fila_execucao.pop(0)
            relatorio.append((tempo_atual, processo_em_execucao.nome))
            tempo_atual += 1
        else:
            tempo_atual += 1

    return relatorio


def gerarLinhaTempo(relatorio):
    linha_tempo = ""
    tempo_atual = 0
    for tempo, processo in relatorio:
        linha_tempo += f"|{tempo_atual}|---{processo}---|"
        tempo_atual = tempo + 1
    linha_tempo += f"{tempo_atual}|"
    return linha_tempo

def escritaRelatorio1(arq, processos, relatorio):
    with open(arq, 'w') as saida:
        saida.write("Processos na Fila do Shortest Job First:\n")
        for processo in processos:
            saida.write(f"{processo.nome} ")
        saida.write("\nTempo de CPU requerida pelos processos:\n")
        for processo in processos:
            saida.write(f"{processo.tempoCPU} ")
        saida.write("\nTempo de Chegada dos processos:\n")
        for processo in processos:
            saida.write(f"{processo.tempoCheg} ")
        saida.write("\n\nLinha do tempo:\n")
        saida.write(gerarLinhaTempo(relatorio))

        tempo_resp = []
        tempo_espera = []
        for processo in processos:
            tempo_resp.append(processo.final - processo.tempoCheg)
            tempo_espera.append(processo.tempoEspera)
        
        saida.write("\n\nTempo de Resposta:\n")
        for processo in processos:
            saida.write(f"{processo.nome} ")
        saida.write("\n")
        for tr in tempo_resp:
            saida.write(f"{tr} ")

        saida.write("\n\nTempo de Espera:\n")
        for processo in processos:
            saida.write(f"{processo.nome} ")
        saida.write("\n")
        for tr in tempo_espera:
            saida.write(f"{tr} ")
    
        avg_tempo_resposta = sum(tempo_resp) / len(tempo_resp)
        avg_tempo_espera = sum(tempo_espera) / len(tempo_espera)
        saida.write(f"\n\nTempo Médio de Resposta: {avg_tempo_resposta:.2f}\n")
        saida.write(f"Tempo Médio de Espera: {avg_tempo_espera:.2f}\n")
        
                    
if __name__ == "__main__":

    paths = definePaths(sys.argv)
    processos = leituraArq(paths[0])
    saida = abrirArq(paths)
    relatorio= SJFescalonador(processos.copy())
    escritaRelatorio1(paths[1], processos, relatorio)