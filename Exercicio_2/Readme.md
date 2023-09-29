# _Explicação Funcional do segundo exercício_

### Primeiramente vamos aos arquios selecionados e o que eles representam

- Hardware_codigo_2.txt e Codigo.c - Os 2 arquivos contém o código a ser compilado no [TinkerCad](https://www.tinkercad.com/).
- hardware_2.png - Contem a foto dos componentes utilizados para a criação do circuito e suas respectivas conexões.
- Hardware_arduino_codigo_2.brd - Projeto baixado para extensão de arquio do TinkerCad, para acessar o projeto por completo, [clique aqui](https://www.tinkercad.com/things/kBqXELWnsU8?sharecode=M1fLLSJsGpzJYUHipqED0eSZwWNBIgcEVLzrvT0b_pU).
- Hardware_PDF_2.pdf - Arquivo baixado pelo TinkerCad, mostra a estrutura do circuito de forma mais técnica.

### _Explicação Técnica_

O circuito a seguir exemplifica uma trena digital utilizando o sensor de distância HC-SR04, no qual ao simulado é possivel escolher um raio de distância dentro das suas limitações,
o circuito é responsável por fazer a leitura desta distãncia e exibir ela em um display LCD, mostrando o seu respectio valor.
Além disso, no próprio console do TinkerCad foi feita uma estrutura condicional no qual é verificado a distância escolhida e se ela for maior que 100 é exibida uma mensagem no monitor serial
para seguir o trajeto, caso contrário, para desviar do objeto, simulando um trajeto com obstáculos.

