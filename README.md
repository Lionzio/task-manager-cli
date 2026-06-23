# Task Manager CLI (`task-cli`)

![Language](https://img.shields.io/badge/Language-C99-00599C.svg?style=flat-square&logo=c)
![Platform](https://img.shields.io/badge/Platform-Windows%2011-0078D4.svg?style=flat-square&logo=windows)
![Build](https://img.shields.io/badge/Build-GNU%20Make-F34F29.svg?style=flat-square)
![Persistence](https://img.shields.io/badge/Persistence-Custom%20TXT-10E781.svg?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-flat.svg?style=flat-square)

Uma ferramenta de Linha de Comando (CLI) de altíssimo desempenho para gerenciamento de tarefas do dia a dia, escrita estritamente em **C Puro (Padrão C99)**. 

Desenvolvida como prova de conceito de engenharia de software nativa, a aplicação dispensa totalmente o uso de SGBDs externos, operando sobre um motor próprio de serialização de texto plano e manipulação direta de memória estática na *Stack*.

---

## ⚡ Por que C Puro?

Numa era dominada por aplicações baseadas em Electron que consomem 500MB de RAM para exibir uma lista de afazeres, o `task-cli` propõe o caminho inverso:
- **Alocação de Memória Zero-Heap:** Ausência intencional de `malloc()`/`free()`. Todas as entidades de domínio possuem fronteiras fixas e seguras na Pilha, mitigando completamente o risco de *Memory Leaks*.
- **Executável Portátil (~100KB):** Graças à linkagem estática (`-static`), o binário final pode ser executado em qualquer máquina Windows 64-bit sem que o usuário possua o MinGW ou *runtimes* da Microsoft instalados.
- **Segurança Robusta de I/O:** Escudos de sanitização implementados sobre `strncpy` e `strtok`, prevenindo *Buffer Overflows* e corrupção de colunas por dados nulos.

---

## 🚀 Funcionalidades

- `add` — Injeção de novas tarefas com cálculo automático de ID e carimbo UTC de criação.
- `list` — Renderizador de relatórios em tabela ASCII responsiva com auto-truncamento de títulos longos (`%-30.30s`).
- `done` — Mutação atômica de estado para `[Concluido]`.
- `delete` — Extirpação permanente de registros utilizando algoritmo de **Deslocamento Contíguo de Memória** (*Left Shift*).

---

## 💻 Manual de Uso (PowerShell)

Acesse a pasta onde o executável `task-cli.exe` está localizado e passe os argumentos:

### 1. Cadastrando uma tarefa
```powershell
.\bin\task-cli.exe add "Estudar Algoritmos" "Implementar QuickSort" 3
```
*(Prioridades aceitas: `1` = Baixa | `2` = Média | `3` = Alta)*

### 2. Exibindo o painel de tarefas
```powershell
.\bin\task-cli.exe list
```

**Saída de renderização no console:**
```text
+------+--------------------------------+----------+----------------+------------+
| ID   | Titulo                         | Priorid. | Status         | Data       |
+------+--------------------------------+----------+----------------+------------+
| 1    | Dominar I/O em C               | Alta     | [Em Progresso] | 23/06/2026 |
| 2    | Estudar Algoritmos             | Alta     | [Pendente]     | 23/06/2026 |
+------+--------------------------------+----------+----------------+------------+
```

### 3. Concluindo e Deletando
```powershell
.\bin\task-cli.exe done 2
.\bin\task-cli.exe delete 1
```

---

## 🏗️ Arquitetura do Sistema

O projeto respeita o princípio da **Separação de Conceitos (SoC)**, isolando a regra de negócios da infraestrutura de leitura de disco:

```text
task-manager-cli/
├── bin/                 <-- Binário de distribuição isolado (task-cli.exe)
├── data/                <-- Camada de Persistência Física
│   └── tasks.txt        <-- (Base delimitada por Pipes '|')
├── include/             <-- Contratos de Domínio (.h)
│   ├── task.h           <-- Entidade Task e Enums de Estado
│   └── file_io.h        <-- Assinaturas de Serialização
├── src/                 <-- Módulos de Implementação (.c)
│   ├── main.c           <-- Roteador de Comandos CLI (Parser de argv)
│   ├── task.c           <-- Motor de Memória (CRUD e ASCII Table)
│   └── file_io.c        <-- Motor de I/O (fopen, fgets, strtok)
├── tests/
│   └── test_main.c      <-- Suíte de testes automatizada
└── Makefile             <-- Orquestrador de compilação GNU Make
```

---

## 🧪 Rodando a Suíte de Testes (QA)

O motor do sistema é coberto por asserções matemáticas nativas (`<assert.h>`). Para auditar a integridade lógica da sua compilação local, execute:

```powershell
make test
```

A saída esperada atestará a aprovação dos 3 anéis de estresse:
```text
=== EXECUTANDO SUÍTE DE TESTES UNITÁRIOS (assert.h) ===
  [PASSED] Validações de Domínio (Rejeição NULL e vazios)
  [PASSED] Mecanismo de Compactação e Shift Left
  [PASSED] Motores de Serialização e Desserialização (I/O)

-> SUÍTE APROVADA: O código está matematicamente seguro.
```

---

## ⚙️ Instruções de Compilação (Para Desenvolvedores)

### Pré-requisitos:
- **OS:** Windows 10 / 11 (64-bit)
- **Toolchain:** `MinGW-w64` (GCC) + `GNU Make`

Clone o repositório:
```powershell
git clone [https://github.com/Lionzio/task-manager-cli.git](https://github.com/Lionzio/task-manager-cli.git)
cd task-manager-cli
```

Gerando a build de desenvolvimento:
```powershell
make
```

Gerando a build de **Release de Alta Otimização** (Portátil):
```powershell
make release
```

---

## ⚖️ Licença

Este projeto é distribuído sob a licença **MIT**. Você é livre para utilizá-lo, modificá-lo e distribuí-lo para fins acadêmicos ou comerciais.