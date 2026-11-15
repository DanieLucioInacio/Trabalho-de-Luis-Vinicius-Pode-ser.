# Problema do Jantar dos Filósofos

## 1. Introdução

O Problema do Jantar dos Filósofos é um exemplo utilizado na área de programação para demonstrar situações de concorrência e compartilhamento de recursos. Neste trabalho, foi desenvolvido um programa em C++ que representa cinco filósofos sentados ao redor de uma mesa, compartilhando cinco garfos. O objetivo é permitir que todos consigam realizar suas refeições sem que dois filósofos utilizem o mesmo garfo ao mesmo tempo.

## 2. Funcionamento do programa

O programa utiliza threads para representar os cinco filósofos, permitindo que suas atividades aconteçam de forma concorrente. Cada filósofo alterna entre pensar e comer. Para conseguir comer, ele precisa utilizar os dois garfos disponíveis ao seu lado.

Para organizar o acesso aos garfos, foi utilizada uma fila FIFO (First In, First Out), na qual o primeiro filósofo a solicitar os recursos tem prioridade para utilizá-los. Também foi utilizado um mutex para controlar o acesso às informações compartilhadas e evitar conflitos durante a execução. Quando um filósofo termina de comer, ele devolve os garfos, permitindo que outro possa utilizá-los.

## 3. Como compilar e executar

Para testar o programa, é necessário abrir o terminal do VS Code na pasta onde está localizado o arquivo `Filosofoscodigo.cpp`. Primeiro, deve ser realizada a compilação utilizando o comando abaixo:

```bash
g++ Filosofoscodigo.cpp -o Filosofoscodigo -std=c++17 -pthread
```

Após a compilação, caso não apareçam erros, o programa poderá ser executado com o seguinte comando:

```bash
./Filosofoscodigo
```

## 4. Testes e resultados

Durante a execução, o terminal apresenta as ações realizadas pelos filósofos, indicando quando cada um está pensando, entrando na fila, comendo e terminando sua refeição. Ao final, o programa apresenta a quantidade de refeições realizadas por cada filósofo e o total de refeições concluídas.

O resultado esperado é que cada um dos cinco filósofos consiga comer três vezes, totalizando quinze refeições. Caso todos consigam atingir essa quantidade, será exibida a mensagem de confirmação: "[OK] Todos conseguiram comer 3 vezes!".

## 5. Conclusão

A realização deste trabalho permitiu compreender melhor os conceitos de concorrência e sincronização em C++. Através do uso de threads, mutex e fila FIFO, foi possível desenvolver uma solução para organizar o acesso aos recursos compartilhados e evitar conflitos entre os filósofos. O programa também permite verificar se todos conseguiram realizar suas refeições conforme o esperado.