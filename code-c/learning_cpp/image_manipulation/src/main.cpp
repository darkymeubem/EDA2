#include "Image.h"
#include <iostream>
int main(int argc, char** argv) {
	Image test("imgs/colered.jpg");
	test.encodeMessage(
R"STEG(Em um mundo cada vez mais moldado pela tecnologia, a forma como interagimos com o conhecimento, com as pessoas e ate com nos mesmos vem passando por uma transformacao silenciosa, porem profunda. Nao se trata apenas de avancos tecnicos ou da criacao de novas ferramentas, mas de uma mudanca estrutural na maneira como percebemos o tempo, o esforco e o aprendizado. O acesso instantaneo a informacao, que antes era visto como um luxo, hoje se tornou uma expectativa basica. No entanto, essa facilidade traz consigo um paradoxo interessante: quanto mais rapido conseguimos respostas, menos tolerantes nos tornamos ao processo de construcao dessas respostas.

Esse fenomeno e especialmente visivel no contexto educacional e no desenvolvimento pessoal. Aprender algo novo, seja programacao, matematica ou qualquer outra habilidade complexa, exige um nivel de frustracao inevitavel. E necessario errar, testar hipoteses, revisar conceitos e persistir mesmo quando os resultados nao aparecem imediatamente. No entanto, em uma era dominada por tutoriais rapidos e solucoes prontas, muitos acabam confundindo consumir informacao com realmente aprender. Assistir a uma explicacao clara pode dar a sensacao de dominio, mas o verdadeiro entendimento so surge quando colocamos a mao na massa e enfrentamos as dificuldades reais do processo.

Outro ponto importante e a relacao entre consistencia e motivacao. Existe uma ideia comum de que precisamos estar motivados para agir, quando, na pratica, muitas vezes e o contrario: a acao consistente e o que gera motivacao ao longo do tempo. Pequenos progressos diarios, mesmo que quase imperceptiveis, se acumulam de forma poderosa. Isso e especialmente verdadeiro em areas como desenvolvimento de software, onde a complexidade dos problemas pode ser intimidadora no inicio. Ao dividir grandes objetivos em etapas menores e manter uma rotina de pratica, o que antes parecia impossivel comeca a se tornar natural.

Alem disso, a capacidade de lidar com a complexidade se torna um diferencial cada vez mais valioso. Em vez de buscar respostas simples para problemas complexos, e necessario desenvolver uma mentalidade que aceite a ambiguidade e esteja disposta a explorar multiplas solucoes. Isso exige nao apenas conhecimento tecnico, mas tambem pensamento critico e criatividade. Em projetos reais, raramente existe uma unica solucao correta; o que existe sao diferentes abordagens, cada uma com seus proprios trade-offs.)STEG");
	test.write("imgs/colered_stego.jpg");
	char buffer[5000] = {0};
	size_t len = 0;
	test.decodeMessage(buffer, &len);

	//printf("Message: %s (%zu bits)\n", buffer, len);

	return 0;
}
