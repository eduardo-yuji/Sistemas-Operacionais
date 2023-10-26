import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from Processes import Processes  

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

def gerarRelatorio(relatorio):
    tempo_atual = 0
    with open("relatorio.txt", "w") as saida:
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
        for tempo, processo in relatorio:
            saida.write(f"|{tempo_atual}|---{processo}---|")
            tempo_atual = tempo + 1
        saida.write(f"{tempo_atual}|")
     
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
   
# Função para criar uma instância da classe Processes
def criar_processo():
    nome = nomeInput.get()
    tempoCPU = int(cpuInput.get())
    tempoCheg = int(chegadaInput.get())
    
    if tempoCPU <= 0:
        messagebox.showerror("Erro", "Tempo de CPU deve ser maior que zero")
    elif tempoCheg < 0:
        messagebox.showerror("Erro", "Tempo de Chegada não pode ser menor que zero")
    else:
        processo = Processes(nome, tempoCPU, tempoCheg)
        processos.append(processo)
        atualizar_tabela()
        nomeInput.delete(0, "end")
        cpuInput.delete(0, "end")
        chegadaInput.delete(0, "end")
       
# Função para enviar os valores da tabela para os processos
def enviar_para_processos():
    # Aqui você pode percorrer os itens da tabela e enviar os valores para os processos
    for processo in processos:
        print(f"Nome: {processo.nome}, Tempo CPU: {processo.tempoCPU}, Tempo de Chegada: {processo.tempoCheg}")

# Função para atualizar a tabela com os dados dos processos
def atualizar_tabela():
    for i in tabela.get_children():
        tabela.delete(i)

    for processo in processos:
        tabela.insert("", "end", values=(processo.nome, processo.tempoCPU, processo.tempoCheg))
 
if __name__ == "__main__":
    # Janela de inputs
    janela = tk.Tk()
    janela.title("Tabela de Processos")

    # Campos de entrada
    nome = tk.Label(janela, text="Nome:")
    nome.grid(row=0, column=0)
    nomeInput = tk.Entry(janela)
    nomeInput.grid(row=0, column=1)

    tempoCPU = tk.Label(janela, text="Tempo CPU:")
    tempoCPU.grid(row=1, column=0)
    cpuInput = tk.Entry(janela)
    cpuInput.grid(row=1, column=1)

    tempoCheg = tk.Label(janela, text="Tempo de Chegada:")
    tempoCheg.grid(row=2, column=0)
    chegadaInput = tk.Entry(janela)
    chegadaInput.grid(row=2, column=1)

    # Botoes
    criar_processo_button = tk.Button(janela, text="Criar Processo", command=criar_processo)
    criar_processo_button.grid(row=3, column=0, columnspan=2)

    enviar_para_processos_button = tk.Button(janela, text="Enviar Processos", command=janela.destroy)
    enviar_para_processos_button.grid(row=6, column=0, columnspan=2)

    # Criação da tabela
    colunas = ("Nome", "Tempo CPU", "Tempo de Chegada")
    tabela = ttk.Treeview(janela, columns=colunas, show="headings")
    for coluna in colunas:
        tabela.heading(coluna, text=coluna)
        tabela.column(coluna, width=100)
    tabela.grid(row=5, column=0, columnspan=2)

    processos = []  # Armazena as instâncias da classe Processes

    janela.mainloop()

    # Escalona os processos
    relatorio = SJFescalonador(processos.copy())
    gerarRelatorio(relatorio)

    with open("relatorio.txt", "r") as saida_arquivo:
        conteudo_saida = saida_arquivo.read()

    # Janela Outputs
    janelaS = tk.Tk()
    janelaS.title("Processo escalonado por SJF preemptivo")

    texto_saida = tk.Text(janelaS, wrap="word", width=60, height=20)
    texto_saida.insert(tk.END, conteudo_saida)
    texto_saida.config(state=tk.DISABLED)
    texto_saida.pack(padx=10, pady=10)

    janela.mainloop()

    