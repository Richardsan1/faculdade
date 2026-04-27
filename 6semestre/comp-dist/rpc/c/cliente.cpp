#include <iostream>
#include <string>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "notas.grpc.pb.h"

class NotasClient {
public:
    NotasClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(gerencia_notas::GerenciadorNotas::NewStub(channel)) {}

    void AdicionarNotaExemplo(const std::string& ra, const std::string& disciplina, float nota_val) {
        gerencia_notas::AdicionaNotaRequest request;
        request.set_ra(ra);
        request.set_cod_disciplina(disciplina);
        request.set_ano(2025);
        request.set_semestre(1);
        request.set_nota(nota_val);

        gerencia_notas::StatusResponse reply;
        grpc::ClientContext context;
        grpc::Status status = stub_->AdicionarNota(&context, request, &reply);

        if (status.ok()) {
            std::cout << "Resposta do servidor: " << reply.msg() << std::endl;
        } else {
            std::cout << "Erro RPC: " << status.error_code() << ": " << status.error_message() << std::endl;
        }
    }

    // CHAMADA DO DESAFIO (STREAMING)
    void ListarNotasExemplo(const std::string& ra) {
        gerencia_notas::AlunoRequest request;
        request.set_ra(ra);
        
        grpc::ClientContext context;
        gerencia_notas::Nota nota_recebida;
        
        std::unique_ptr<grpc::ClientReader<gerencia_notas::Nota>> reader(
            stub_->ListarNotasAluno(&context, request));

        std::cout << "\n--- Listando todas as notas do aluno " << ra << " (DESAFIO) ---" << std::endl;
        while (reader->Read(&nota_recebida)) {
            std::cout << " - Disciplina: " << nota_recebida.cod_disciplina() 
                      << ", Nota: " << nota_recebida.nota() << std::endl;
        }

        grpc::Status status = reader->Finish();
        if (!status.ok()) {
            std::cout << "Erro no streaming: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<gerencia_notas::GerenciadorNotas::Stub> stub_;
};

int main(int argc, char** argv) {
    // Comunicação com o servidor local. Lembre-se de usar a mesma porta do servidor alvo (50051 Python, 50052 C++).
    NotasClient client(grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));
    
    client.AdicionarNotaExemplo("456", "CIC0002", 8.5);
    client.AdicionarNotaExemplo("456", "CIC0003", 9.0);
    client.ListarNotasExemplo("456");
    
    return 0;
}