
# Laboratório de Computação Distribuída: Interoperabilidade com gRPC

Este documento detalha as instruções para a compilação e execução do sistema de gerenciamento de notas, demonstrando a comunicação RPC via gRPC entre as linguagens Python e C++.

## Pré-requisitos do Ambiente

Para compilar e executar ambas as versões do laboratório, o ambiente (preferencialmente Linux/Ubuntu) deve possuir as seguintes ferramentas e bibliotecas instaladas no terminal:

Dependências para Python:
pip install grpcio grpcio-tools

Dependências para C++:
sudo apt update
sudo apt install -y build-essential autoconf libtool pkg-config cmake libgflags-dev libgtest-dev clang libc++-dev libprotobuf-dev protobuf-compiler libgrpc-dev libgrpc++-dev protobuf-compiler-grpc

---

## Instruções de Execução

Certifique-se de que todos os arquivos fonte (notas.proto, códigos .py e .cpp, e o CMakeLists.txt) estão no mesmo diretório raiz antes de prosseguir.

### 1. Geração da Infraestrutura (Python)
Antes de rodar a aplicação Python, é necessário gerar os stubs e skeletons a partir do contrato Protobuf. Na raiz do projeto, execute:

```bash
python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. notas.proto
```

### 2. Executando a versão em Python
Abra duas janelas de terminal na raiz do projeto e inicie os processos sequencialmente:

Terminal 1 (Servidor): 
```bash 
python servidor.py
```
Terminal 2 (Cliente): 
```bash 
python cliente.py 
```

### 3. Compilando e Executando a versão em C++
A construção dos binários em C++ é gerenciada pelo CMake e deve ser feita em um diretório isolado para não poluir a raiz do projeto. No terminal, a partir da raiz, execute os seguintes passos:

1. Crie o diretório de build e acesse-o:
```bash
mkdir build && cd build
```
2. Gere os arquivos de configuração do CMake:
```bash
cmake ..
```
3. Compile os executáveis:
```bash
make
```
Após a finalização do processo de compilação (100%), execute os binários gerados de dentro da pasta `build`:

Terminal 1 (Servidor): ./servidor_cpp
Terminal 2 (Cliente): ./cliente_cpp

Observação de Interoperabilidade: O servidor Python opera na porta 50051 e o servidor C++ na porta 50052. Isso permite que ambos os servidores fiquem ativos simultaneamente no mesmo ambiente sem conflitos de porta durante a avaliação.