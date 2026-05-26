function trocar(secao) {
    let secoes = document.querySelectorAll('.section');

    secoes.forEach(s => s.classList.remove('active'));

    document.getElementById(secao).classList.add('active');
}


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
