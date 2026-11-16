# Trabalho 1 – Remodelagem do Banco de Dados da Loja Cerrado

## 1. Introdução

Neste trabalho será feita uma remodelagem do banco de dados da Loja Cerrado, utilizando como base os conteúdos apresentados nos slides das aulas.

O objetivo é melhorar a organização do banco de dados, permitindo controlar os clientes, pedidos, produtos e estoques de uma maneira mais simples e eficiente.

Também será adicionada uma tabela de SKU, que servirá para identificar as diferentes versões de cada produto.

## 2. Descrição do projeto

A Loja Cerrado trabalha com a venda de diferentes produtos e precisa de um sistema para organizar suas informações.

O banco de dados deverá permitir:

- Cadastrar clientes.
- Cadastrar produtos.
- Registrar pedidos e vendas.
- Controlar a quantidade de produtos no estoque.
- Identificar as variações dos produtos por meio de SKUs.
- Consultar informações sobre as vendas.

Com essas funcionalidades, será mais fácil acompanhar as operações da loja e evitar erros no controle das informações.

## 3. Remodelagem do banco de dados

Nos slides, o banco de dados original possui quatro tabelas principais: CLIENTE, PEDIDO, PRODUTO e ITEM. Também existe uma tabela ESTOQUE, apresentada como uma extensão.

Para melhorar esse modelo, será adicionada uma nova tabela chamada SKU.

As tabelas terão as seguintes funções:

- **CLIENTE:** guarda o nome e a cidade dos clientes.
- **PEDIDO:** registra os pedidos realizados pelos clientes.
- **PRODUTO:** armazena os produtos disponíveis na loja.
- **SKU:** identifica as diferentes versões de cada produto.
- **ESTOQUE:** controla a quantidade disponível de cada SKU.
- **ITEM:** registra os produtos e suas quantidades dentro dos pedidos.

## 4. Relacionamentos

As tabelas terão os seguintes relacionamentos:

- Um cliente pode realizar vários pedidos.
- Cada pedido pertence a um cliente.
- Um pedido pode possuir vários itens.
- Um produto pode possuir vários SKUs.
- Cada SKU pertence a um produto.
- Cada SKU possui um registro de estoque.
- Um SKU pode aparecer em vários itens de pedidos.

Esses relacionamentos ajudam a manter os dados organizados e evitam a repetição desnecessária de informações.

## 5. Cadastro dos produtos e SKUs

Para realizar a remodelagem, serão utilizados cinco produtos que servirão como exemplo:

| Produto | Categoria | Quantidade de SKUs |
|---|---|---:|
| Teclado | Periféricos | 5 |
| Mouse | Periféricos | 5 |
| Cadeira | Móveis | 5 |
| Monitor | Eletrônicos | 5 |
| Mesa | Móveis | 5 |

Cada produto terá cinco variações diferentes, totalizando 25 SKUs.

Exemplos:

- **Teclado:** ABNT2, mecânico, membrana, RGB e sem fio.
- **Mouse:** com fio, sem fio, gamer, ergonômico e Bluetooth.
- **Cadeira:** escritório, gamer, executiva, presidente e ergonômica.
- **Monitor:** 19, 22, 24 e 27 polegadas e ultrawide.
- **Mesa:** escritório, gamer, madeira, compacta e em L.

Cada variação terá seu próprio código e preço, facilitando a identificação dos produtos.

## 6. Criação do banco de dados

Primeiro, será criado o banco de dados utilizando o MySQL.

```sql
CREATE DATABASE loja_cerrado;
USE loja_cerrado;
```

Depois, serão criadas as tabelas:

```sql
CREATE TABLE CLIENTE (
    cid INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(100) NOT NULL,
    cidade VARCHAR(100) NOT NULL
);

CREATE TABLE PRODUTO (
    rid INT PRIMARY KEY,
    descricao VARCHAR(100) NOT NULL,
    categoria VARCHAR(50) NOT NULL
);

CREATE TABLE SKU (
    sku_id INT PRIMARY KEY AUTO_INCREMENT,
    rid INT NOT NULL,
    codigo_sku VARCHAR(30) UNIQUE NOT NULL,
    variacao VARCHAR(100) NOT NULL,
    preco DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (rid) REFERENCES PRODUTO(rid)
);

CREATE TABLE ESTOQUE (
    sku_id INT PRIMARY KEY,
    saldo INT NOT NULL DEFAULT 0,
    FOREIGN KEY (sku_id) REFERENCES SKU(sku_id),
    CHECK (saldo >= 0)
);

CREATE TABLE PEDIDO (
    pid INT PRIMARY KEY AUTO_INCREMENT,
    cid INT NOT NULL,
    status ENUM(
        'PENDENTE',
        'CONCLUIDO',
        'CANCELADO'
    ) DEFAULT 'PENDENTE',
    FOREIGN KEY (cid) REFERENCES CLIENTE(cid)
);

CREATE TABLE ITEM (
    pid INT NOT NULL,
    sku_id INT NOT NULL,
    qtd INT NOT NULL,
    preco DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (pid, sku_id),
    FOREIGN KEY (pid) REFERENCES PEDIDO(pid),
    FOREIGN KEY (sku_id) REFERENCES SKU(sku_id)
);
```

## 7. Inserção dos produtos

Depois de criar as tabelas, serão cadastrados os cinco produtos principais.

```sql
INSERT INTO PRODUTO VALUES
(10, 'Teclado', 'Perifericos'),
(20, 'Mouse', 'Perifericos'),
(30, 'Cadeira', 'Moveis'),
(40, 'Monitor', 'Eletronicos'),
(50, 'Mesa', 'Moveis');
```

Em seguida, serão cadastradas as variações de cada produto.

```sql
INSERT INTO SKU
(rid, codigo_sku, variacao, preco)
VALUES
(10, 'TEC001', 'Teclado ABNT2', 100.00),
(10, 'TEC002', 'Teclado Mecanico', 180.00),
(10, 'TEC003', 'Teclado Membrana', 70.00),
(10, 'TEC004', 'Teclado RGB', 220.00),
(10, 'TEC005', 'Teclado Sem Fio', 150.00),

(20, 'MOU001', 'Mouse Com Fio', 40.00),
(20, 'MOU002', 'Mouse Sem Fio', 65.00),
(20, 'MOU003', 'Mouse Gamer', 120.00),
(20, 'MOU004', 'Mouse Ergonomico', 90.00),
(20, 'MOU005', 'Mouse Bluetooth', 85.00),

(30, 'CAD001', 'Cadeira Escritorio', 350.00),
(30, 'CAD002', 'Cadeira Gamer', 750.00),
(30, 'CAD003', 'Cadeira Executiva', 500.00),
(30, 'CAD004', 'Cadeira Presidente', 600.00),
(30, 'CAD005', 'Cadeira Ergonomica', 900.00),

(40, 'MON001', 'Monitor 19 Polegadas', 450.00),
(40, 'MON002', 'Monitor 22 Polegadas', 600.00),
(40, 'MON003', 'Monitor 24 Polegadas', 850.00),
(40, 'MON004', 'Monitor 27 Polegadas', 1200.00),
(40, 'MON005', 'Monitor Ultrawide', 1600.00),

(50, 'MES001', 'Mesa Escritorio', 250.00),
(50, 'MES002', 'Mesa Gamer', 450.00),
(50, 'MES003', 'Mesa Madeira', 500.00),
(50, 'MES004', 'Mesa Compacta', 180.00),
(50, 'MES005', 'Mesa Em L', 650.00);
```

Para começar, cada SKU terá dez unidades no estoque.

```sql
INSERT INTO ESTOQUE (sku_id, saldo)
SELECT sku_id, 10 FROM SKU;
```

## 8. Consultas SQL

Também serão utilizadas algumas consultas para buscar informações no banco de dados.

**Consulta 1 – Mostrar os produtos e suas variações:**

```sql
SELECT
    p.descricao,
    s.codigo_sku,
    s.variacao,
    s.preco
FROM PRODUTO p
INNER JOIN SKU s
ON p.rid = s.rid;
```

Essa consulta mostra os produtos cadastrados e suas respectivas variações.

**Consulta 2 – Consultar o estoque:**

```sql
SELECT
    s.codigo_sku,
    s.variacao,
    e.saldo
FROM SKU s
INNER JOIN ESTOQUE e
ON s.sku_id = e.sku_id;
```

Essa consulta mostra quantas unidades estão disponíveis de cada SKU.

**Consulta 3 – Mostrar os produtos que ainda não foram vendidos:**

```sql
SELECT s.codigo_sku, s.variacao
FROM SKU s
LEFT JOIN ITEM i
ON s.sku_id = i.sku_id
WHERE i.sku_id IS NULL;
```

Essa consulta identifica os SKUs que ainda não aparecem em nenhum pedido.

**Consulta 4 – Calcular o valor dos pedidos:**

```sql
SELECT
    pid,
    SUM(qtd * preco) AS total
FROM ITEM
GROUP BY pid;
```

Essa consulta calcula o valor total de cada pedido.

## 9. Controle de estoque e transações

Uma parte importante do projeto é o controle do estoque.

Como apresentado nos slides, uma venda não pode ser registrada pela metade. Por exemplo, não seria correto diminuir a quantidade do estoque sem registrar o pedido correspondente.

Para evitar esse problema, serão utilizadas transações.

Exemplo:

```sql
START TRANSACTION;

UPDATE ESTOQUE
SET saldo = saldo - 2
WHERE sku_id = 1
AND saldo >= 2;

SELECT ROW_COUNT();

-- Se a baixa funcionar:
-- Registrar o pedido e o item.

-- Se ocorrer algum erro:
ROLLBACK;

-- Se tudo funcionar corretamente:
-- COMMIT;
```

O COMMIT confirma as alterações, enquanto o ROLLBACK desfaz as alterações quando acontece algum problema.

## 10. Propriedades ACID

As propriedades ACID também serão utilizadas no projeto.

- **Atomicidade:** garante que uma venda seja realizada completamente ou desfeita.
- **Consistência:** impede que informações inválidas sejam armazenadas.
- **Isolamento:** evita problemas quando duas pessoas tentam comprar o mesmo produto ao mesmo tempo.
- **Durabilidade:** garante que os dados confirmados sejam mantidos mesmo depois de uma falha no sistema.

Essas propriedades ajudam a manter o banco de dados funcionando corretamente.

## 11. Segurança e backup

Para proteger as informações da loja, também serão utilizados alguns cuidados:

- Criar usuários com permissões diferentes.
- Utilizar senhas para acessar o banco.
- Fazer backups regularmente.
- Testar a restauração dos dados.
- Utilizar índices para melhorar algumas consultas.

Também é importante verificar se os backups realmente funcionam, pois apenas salvar os arquivos não garante que será possível recuperar as informações.

## 12. Conclusão

Com esse trabalho, foi possível entender melhor como funciona a organização de um banco de dados e como podemos melhorar uma estrutura que já existe.

A principal mudança foi a criação da tabela SKU, que permite cadastrar diferentes versões de um mesmo produto e controlar o estoque de cada uma separadamente.

Também foram utilizados comandos SQL, relacionamentos entre tabelas, consultas, transações e propriedades ACID, seguindo os conteúdos apresentados nas aulas.

Concluindo, a remodelagem deixa o banco de dados da Loja Cerrado mais organizado e facilita o controle dos produtos, pedidos e estoques.
