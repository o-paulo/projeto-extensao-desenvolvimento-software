CREATE TABLE Pessoa_Fisica (
	id_cliente INT PRIMARY KEY,
	cpf VARCHAR(11) NOT NULL UNIQUE,
	rg VARCHAR(20) NOT NULL UNIQUE,
	data_nascimento DATE,
	genero VARCHAR(100)
);

CREATE TABLE Pessoa_juridica (
	id_cliente INT PRIMARY KEY,
	cnpj VARCHAR(14) NOT NULL UNIQUE,
	razao_social VARCHAR(255) NOT NULL
);

CREATE TABLE Clientes (
	id_cliente INT PRIMARY KEY,
	nome VARCHAR(40) NOT NULL,
	endereco VARCHAR(100),
	email VARCHAR(255),
	telefone VARCHAR(15),

	id_pessoa_fisica INT,
	id_pessoa_juridica INT,

CONSTRAINT fk_pessoa_fisica
        FOREIGN KEY (id_pessoa_fisica)
        REFERENCES pessoa_fisica(id_cliente),

CONSTRAINT fk_pessoa_juridica
        FOREIGN KEY (id_pessoa_juridica)
        REFERENCES pessoa_juridica(id_cliente)
);

CREATE TABLE Funcionarios(
	id_funcionario INT PRIMARY KEY,
	nome VARCHAR(30),
	telefone VARCHAR(15),
	cpf VARCHAR(11) NOT NULL UNIQUE
);

CREATE TABLE fornecedores (
	cnpj_fornecedor VARCHAR(14) PRIMARY KEY,
	nome_fornecedor VARCHAR(40) NOT NULL UNIQUE,
	email VARCHAR(255),
	telefone VARCHAR(15),
	endereco VARCHAR(255)
);

CREATE TABLE Categorias (
	id_categoria INT PRIMARY KEY,
	nome_categoria VARCHAR(100) NOT NULL UNIQUE,
	tipo_categoria VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE Produtos (
    id_produto INT PRIMARY KEY,
    nome_produto VARCHAR(100) NOT NULL UNIQUE,

    id_categoria INT,
    cnpj_fornecedor VARCHAR(18),

    CONSTRAINT fk_categoria
        FOREIGN KEY (id_categoria)
        REFERENCES categorias(id_categoria),

    CONSTRAINT fk_fornecedor
        FOREIGN KEY (cnpj_fornecedor)
        REFERENCES fornecedores(cnpj_fornecedor)
);

CREATE TABLE Pedidos (
	id_pedido INT PRIMARY KEY,
	data_pedido DATE,

	id_funcionario INT,
	id_cliente INT,
	id_produto INT,

	CONSTRAINT fk_funcionario
		FOREIGN KEY (id_funcionario)
		REFERENCES funcionarios(id_funcionario),

	CONSTRAINT fk_cliente
		FOREIGN KEY (id_cliente)
		REFERENCES clientes(id_cliente),

	CONSTRAINT fk_produto
		FOREIGN KEY (id_produto)
		REFERENCES produtos(id_produto)
);

INSERT INTO Pessoa_Fisica VALUES
(1,'11111111111','MG123456','1995-03-10','Masculino'),
(2,'22222222222','SP987654','2000-07-21','Feminino'),
(3,'33333333333','RJ456789','1988-11-02','Masculino');

INSERT INTO Pessoa_Juridica VALUES
(4,'12345678000199','Tech Solutions LTDA'),
(5,'98765432000155','Mercado Central SA');

INSERT INTO Clientes VALUES
(1,'João Silva','Rua A, 100','joao@email.com','11999999999',1,NULL),
(2,'Maria Souza','Rua B, 200','maria@email.com','11888888888',2,NULL),
(3,'Carlos Lima','Rua C, 300','carlos@email.com','11777777777',3,NULL),
(4,'Tech Solutions','Av Paulista, 1000','contato@tech.com','1133333333',NULL,4),
(5,'Mercado Central','Av Brasil, 500','mercado@email.com','1144444444',NULL,5);

INSERT INTO Funcionarios VALUES
(1,'Ana Costa','11911111111','44444444444'),
(2,'Pedro Santos','11922222222','55555555555'),
(3,'Lucas Martins','11933333333','66666666666');

INSERT INTO Fornecedores VALUES
('11111111000110','Fornecedor Tech','tech@forn.com','1130000000','São Paulo'),
('22222222000120','Distribuidora Info','info@forn.com','1140000000','Campinas'),
('33333333000130','Global Eletrônicos','global@forn.com','1150000000','Rio de Janeiro');

ALTER TABLE categorias
DROP CONSTRAINT categorias_tipo_categoria_key;

INSERT INTO Categorias VALUES
(1,'Notebooks','Eletrônicos'),
(2,'Smartphones','Eletrônicos'),
(3,'Periféricos','Acessórios');

INSERT INTO Produtos VALUES
(1,'Notebook Dell i7',1,'11111111000110'),
(2,'iPhone 13',2,'22222222000120'),
(3,'Mouse Gamer RGB',3,'33333333000130'),
(4,'Notebook Lenovo',1,'11111111000110'),
(5,'Teclado Mecânico',3,'22222222000120');

INSERT INTO Pedidos VALUES
(1,'2024-01-10',1,1,1),
(2,'2024-01-11',2,2,2),
(3,'2024-01-12',1,3,3),
(4,'2024-01-15',3,4,4),
(5,'2024-01-18',2,5,5);

INSERT E FINALIZAÇÃO

DELETE FROM pedidos;

DELETE FROM produtos;

DELETE FROM categorias;

INSERT INTO Categorias VALUES
(1,'Sensores Inteligentes','IoT'),
(2,'Automação Residencial','IoT'),
(3,'Wearables','IoT'),
(4,'Dispositivos Industriais','IoT'),
(5,'Segurança Inteligente','IoT');

INSERT INTO Produtos VALUES
(1,'Sensor de Temperatura WiFi',1,'11111111000110'),
(2,'Lâmpada Smart LED',2,'22222222000120'),
(3,'Smartwatch Health Monitor',3,'33333333000130'),
(4,'Controlador Industrial IoT',4,'11111111000110'),
(5,'Câmera de Segurança Inteligente',5,'22222222000120'),
(6,'Sensor de Presença Zigbee',1,'33333333000130'),
(7,'Tomada Inteligente WiFi',2,'11111111000110');

SELECT * FROM Clientes;
  
SELECT * FROM Fornecedores;
  
SELECT * FROM Funcionarios;
  
SELECT
p.id_pedido,
p.data_pedido,
f.nome AS Funcionario,
c.nome AS Cliente,
pr.nome_produto,
FROM Pedidos p,
JOIN Funcionarios f ON p.id_funcionario = f.id_funcionario,
JOIN Clientes c ON p.id_cliente = c.id_cliente,
JOIN Produtos pr ON p.id_produto = pr.id_produto;

SELECT
    c.nome,
    pf.cpf,
    pf.rg,
    pf.data_nascimento,
    pf.genero,
    c.email,
    c.telefone
FROM Pessoa_Fisica
JOIN Clientes c
ON pf.id_cliente = c.id_pessoa_fisica;
