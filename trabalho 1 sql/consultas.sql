USE loja_cerrado;

-- Consulta 1: mostrar os produtos e suas variacoes
SELECT
    p.descricao,
    s.codigo_sku,
    s.variacao,
    s.preco
FROM PRODUTO p
INNER JOIN SKU s
ON p.rid = s.rid;

-- Consulta 2: consultar o estoque
SELECT
    s.codigo_sku,
    s.variacao,
    e.saldo
FROM SKU s
INNER JOIN ESTOQUE e
ON s.sku_id = e.sku_id;

-- Consulta 3: mostrar os produtos que ainda nao foram vendidos
SELECT s.codigo_sku, s.variacao
FROM SKU s
LEFT JOIN ITEM i
ON s.sku_id = i.sku_id
WHERE i.sku_id IS NULL;

-- Consulta 4: calcular o valor dos pedidos
SELECT
    pid,
    SUM(qtd * preco) AS total
FROM ITEM
GROUP BY pid;
