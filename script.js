function trocar(secao) {
    let secoes = document.querySelectorAll('.section');

    secoes.forEach(s => s.classList.remove('active'));

    document.getElementById(secao).classList.add('active');
}

/*MODAL PRODUTO*/

function abrirModal(
    titulo,
    descricao,
    preco,
    precoAntigo,
    desconto,
    imagem
) {

    document.getElementById("tituloProduto").innerText = titulo;

    document.getElementById("descricaoProduto").innerText = descricao;

    document.getElementById("imagemProduto").src = imagem;

    /* PREÇOS */

    if(preco) {

        document.getElementById("precoProduto").innerText = preco;

        document.getElementById("precoAntigoProduto").innerText = precoAntigo;

        document.getElementById("descontoProduto").innerText = desconto;

        document.querySelector(".modal-precos").style.display = "block";

    } else {

        document.querySelector(".modal-precos").style.display = "none";
    }

    document.getElementById("modal").style.display = "flex";
}
function fecharModal() {
    document.getElementById("modal").style.display = "none";
}

/*BUSCA*/
function buscarProduto() {

    let input = document.getElementById("campoBusca").value.toLowerCase();

    let produtos = document.querySelectorAll(".card");

    produtos.forEach(produto => {

        let nome = produto.innerText.toLowerCase();

        produto.style.display = nome.includes(input) ? "block" : "none";

    });
}