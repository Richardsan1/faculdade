# Server

## Requisitos

### Arquitetura
- deve escutar na porta 12346
- deve utilizar protocolo TCP
- ao criar uma nova conexão deve dar um novo accept
- proteger a memoria compartilhada

### Comandos
- CONSULTAR: Retorna o valor atual. Ex: "Estoque atual: 10".
- COMPRAR:
    - Se estoque > 0: decrementa e responde "Compra realizada. Estoque restante: X".
    - Se estoque == 0: responde "ERRO: Produto esgotado".

