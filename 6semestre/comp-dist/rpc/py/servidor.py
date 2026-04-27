import grpc
from concurrent import futures
import notas_pb2
import notas_pb2_grpc

# Armazenamento em memória
db_notas = {}

class GerenciadorNotasServicer(notas_pb2_grpc.GerenciadorNotasServicer):

    def AdicionarNota(self, request, context):
        chave = f"{request.ra}_{request.cod_disciplina}"
        if chave in db_notas:
            return notas_pb2.StatusResponse(
                sucesso=False, 
                msg="Nota já existe para este aluno/disciplina. Use AlterarNota."
            )
        
        nota = notas_pb2.Nota(
            ra=request.ra, 
            cod_disciplina=request.cod_disciplina, 
            ano=request.ano, 
            semestre=request.semestre, 
            nota=request.nota
        )
        db_notas[chave] = nota
        
        return notas_pb2.StatusResponse(sucesso=True, msg="Nota adicionada com sucesso!")

    def AlterarNota(self, request, context):
        chave = f"{request.ra}_{request.cod_disciplina}"
        if chave not in db_notas:
            return notas_pb2.StatusResponse(sucesso=False, msg="Nota não encontrada.")
            
        db_notas[chave].ano = request.ano
        db_notas[chave].semestre = request.semestre
        db_notas[chave].nota = request.nota
        
        return notas_pb2.StatusResponse(sucesso=True, msg="Nota alterada com sucesso!")

    def ConsultarNota(self, request, context):
        chave = f"{request.ra}_{request.cod_disciplina}"
        if chave in db_notas:
            return notas_pb2.ConsultaNotaResponse(sucesso=True, nota=db_notas[chave])
        return notas_pb2.ConsultaNotaResponse(sucesso=False, msg_erro="Nota não encontrada.")

    def CalcularMedia(self, request, context):
        notas_aluno = [n.nota for n in db_notas.values() if n.ra == request.ra]
        if not notas_aluno:
            return notas_pb2.MediaResponse(sucesso=False, media=0.0, msg_erro="Aluno sem notas.")
        
        media = sum(notas_aluno) / len(notas_aluno)
        return notas_pb2.MediaResponse(sucesso=True, media=media)

    # IMPLEMENTAÇÃO DO DESAFIO (Server Streaming)
    def ListarNotasAluno(self, request, context):
        for nota in db_notas.values():
            if nota.ra == request.ra:
                yield nota

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    notas_pb2_grpc.add_GerenciadorNotasServicer_to_server(GerenciadorNotasServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Servidor gRPC Python rodando na porta 50051.")
    server.wait_for_termination()

if __name__ == '__main__':
    serve()