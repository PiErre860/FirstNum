FirstNum, eseguito come comando da una Shell o terminale a riga di comando sui sistemi GNU/Linux (UNIX), 
permette di trovare numeri primi e fattori di divisibilita sia di singoli valori che di intere liste di 
valori intodotti arbitrariariamente; esempio: firstnum 366771 369711, oppure selettivamente con opzioni 
specifiche. il comando dispone di numerose opzioni per discriminare sia la modalità di visualizzzazione 
sia per le operazioni effettuate sulle liste di valori immessi. È possibile effettuare sia la redirezione 
dell'Output verso un file sia effettuare Pipeline verso altri comandi di sistema. 
Il programma è nato per scopi didattici, ma potrebbe avere anche una qualche utilità in altri ambiti. 
Le opzioni ed i modi di visualizzazzione sono stati studiati per fornire una esperienza d'uso diretta ed 
immediata senza fronzoli inutili. Per evitare la produzione di liste troppo lunghe, ogni singola lista 
puo avere un massimo di 65535 elementi. Poiché FirstNum permette anche di produrre liste con valori non 
consecutivi, tale limite si applica anche su tali opzioni. 
Alla fine di ogni lista viene visualizzato un rapporto statistico con i dati inerenti alla lista stessa. 
Vi sono tuttavia opzioni che inibiscono tali rapporti statistici finali, ciò è utile se ad esempio si 
vuole ottenere una concatenazione strutturata di liste redirezionando l'Output verso un file. 
Ovviamente è possibile usare qualunque opzione e redizionare poi l'Ouput verso un file, oppute usare | 
e less per creare una Pipeline per una più comoda visualizzazione paginata. 
Le opzioni "standard" producono sempre alla fine della lista un rapporto statistico inerente ai valori 
della stessa lista. 
Ad esempio: firstnum -f 98765 119713 produce il seguente Output (Lista parziale): 

  98765 = 5 19753 
  98766 = 2 (3^3) 31 59 
  98767 = 283 349 
  98768 = (2^4) 6173 
  98769 = 3 11 41 73 
  ... 
  ... 
  119698 = 2 97 617 
  119699 
  119700 = (2^2) (3^2) (5^2) 7 19 
  119701 
  119702 = 2 11 5441 
  119703 = 3 39901 
  119704 = (2^3) 13 1151 
  119705 = 5 89 269 
  119706 = 2 3 71 281 
  119707 = (7^3) 349 
  119708 = (2^2) 29927 
  119709 = (3^2) 47 283 
  119710 = 2 5 11971 
  119711 = 59 2029 
  119712 = (2^5) 3 29 43 
  119713 = 11 10883 


firstnum 1.08b     Rapporto riassuntivo finale: 
----------------------------------------------- 
Serie totale di numeri:                   20949 
Totale numeri primi:                       1794 
Totale dei numeri divisibili:             19155 
Fattore primo iniziale più alto:            337 
Distanza massima tra numeri primi:           64 
Distanza media tra numeri primi:              7 

Questa mostrata nell'esempio è l'opzione standard di visualizzazione delle liste. 
Le altre opzioni permettono altre forme di visualizzazione, compreso anche, per alcune, l'inibizione del 
rapporto statistico finale, oppure di discriminare solo i numeri primi o quelli divisibili, ma anche di 
poter selezionare periodi di valori specificandone gli estremi e l'intervallo. 
L'opzione -b permette inoltre di produrre una serie di rapporti statistici all'interno di una serie di 
liste di numeri, in tale modo si può osservare la distribuzione dei fattori primi che c'è all'interno di 
una determinata serie. Questa opzione, come altre del genere richiede tre parametri: gli estremi della 
lista delle serie e la lughezza di ogni serie, come ad esempio: firstnum -b 50000 99999 100 
Le opzioni -l e -q permettono rispettivamente di visualizzare liste di numeri primi e numeri divisibili 
con i loro fattori primi di divisibilità, queste due opzioni sono utili per aggregare piu liste, tramite 
redirezione, in un file. 
Le opzioni -pT e -nT invece permettono rispettivamente di visualizzare in forma tabellare, su più colonne, 
una lista di numeri primi e di numeri divisibili da una serie immessa, specificandone gli estremi. 
Con l'opzione --help è possibile avere una panoramica delle opzioni disponibili. 
Il FirstNum è localizzabile in sei diverse lingue: inglese, italiano, francese, spagnolo, portoghese e 
tedesco, la prima volta che si esegue visualizzo un menù dove è possibile modificare la lingua con cui 
verrà visualizzato l'Output in seguito. È possibile comunque cambiare lingua in qualsiasi momento tramite 
le opzioni EN IT FR ES PT  e DE (scritte in maiuscolo senza il trattino iniziale). 
È disponibile una guida d'uso, per il momento solo in lingua italiana, visualizzabile con l'opzione -?m 
Durante l'installazione di FirstNum, usando l'apposito Script fornito, viene creata una cartella nascosta 
( .fnl ) nella cartella utente, che contiene tale guida. In questa cartella vi sono sei file predisposti 
a contenere la guida d'uso in varie lingue, uno di essi è per la guida in italiano. 
