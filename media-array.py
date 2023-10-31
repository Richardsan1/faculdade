# 5) Faça um programa que peça quatro notas de 4 alunos como valores reais entre 0 e 10,
# calcule e armazene num vetor a média de cada aluno, 
# imprima o número de alunos aprovados com média maior ou igual a 7.0. 
# Implemente três funções, 
# uma primeira de entrada para ler cada nota, validar se cada nota está no intervalo entre 0 e 10 e inserir a média de cada aluno em um vetor. 
# Uma segunda função para verificar e contabilizar quantos alunos estão aprovados. 
# Uma terceira função para imprimir as médias dos alunos e a quantidade de alunos aprovados, 
# esta última função possui um argumento contendo o número de alunos aprovados. 

def GetGrades():
    AllAverages = []

    for i in range(4):
        SumGrades = 0
        
        j = 0
        while j < 4:
            ActualGrade = float(input(f"Digite a nota {j+1} do aluno {i+1}: "))
    
            if ActualGrade >10 or ActualGrade < 0:
                print("número inválido")
                continue
    
            SumGrades += ActualGrade
            j+=1
        
        print()
        
        AllAverages.append(SumGrades/4)
    
    return AllAverages

def ApprovedStudents(Students):
    approved = 0
    
    for Student in Students:
        if Student > 7.0:
            approved+=1
    
    return approved

def PrintStudents(Grades, Approved):
    print("="*40)
    print("A média de cada aluno: ")
    i=1
    for Grade in Grades:
        print(f"-> média do aluno {i}: {Grade:.1f}")
        i+=1

    print(f"\nEstudantes aprovados: {Approved}")
    print("="*40)

grades = GetGrades()
PrintStudents(grades, ApprovedStudents(grades))