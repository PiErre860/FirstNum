/* first      Release 1.03-20241213
   --------------------------------
   ~© (1991-2024) //  GNU/GPL ver.2
   Written by G. B.  Alias PiErre60
   --------------------------------
   and other...
   --------------------------------
   History:
   Created               30-06-1991
   Update                23-02-1993
   Porting GNU-gcc       21-08-2010
   First update          07-02-2019
   First revision        29-08-2020
   Last revision         13-12-2024
   --------------------------------
   Genuine Compiling with:
   Lattice®-SAS C Release 5.05
   for MC680x0 on AMIGA® Computers
   --------------------------------
   Recompiling for UNIX®/POSIX
   and GNU/Linux for X86 with:
   GNU/GCC Release 4.4
   Option compiling:
   cc -lm -ansi First102.c -o first
   --------------------------------
   FIRST PUBLIC RELEASE 1.03
   GNU/GENERAL PUBLIC LICENSE V.2
   --------------------------------
   LANGUAGE COMPILING = ENGLISH
   Row 73 -- ENGLISH / ITALIANO
   -------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>

/* Definizioni generali */
#define WARN   1
#define Ok     0

#define NMAX   255
#define HELP   425
#define NPR    2UL
#define NDIVS  0UL
#define ZDIVS  0UL
#define UNCL   1UL
#define MAX    20
#define RANGE  65536
#define LN_MAX 4294967296UL

#define EN 1   /* Lingua inglese, sigla */
#define IT 2   /* Lingua italiana, sigla */
#define ES 3   /* Lingua spagnola, sigla */
#define FR 4   /* Lingua francese, sigla */
#define PT 5   /* Lingua portoghese, sigla */
#define DE 6   /* Lingua tedesca, sigla */

#define ENGLISH   1   /* Info in inglese */
#define ITALIANO  2   /* Info in italiano */
#define ESPANOL   3   /* Info in spagnolo */
#define FRANCAIS  4   /* Info in francese */
#define PORTUGUES 5   /* Info in portoghese */
#define DEUTCHE   6   /* Info in tedesco */

#define VERSION "1.03"
#define LANG    "FLANG="
#define ENDL    "_END"

/* dichiarazione di funzioni globali */
unsigned long primenumber(unsigned long);
short cfglang(short *);
void show(unsigned long, unsigned long);
void about(char *);

/* Dichiarazione di vettori di caratteri */
char nfile[NMAX];    /* Array contenente il 'percorso/nome_file' di configurazione lingua. */

/* Impostazione della lingua di default */
/* Dichiarazione di variabile globale */
static short lngdef=ENGLISH;

/* Dichiarazioni di variabili globali */
static short lang;
short flg=0,bklng=0;
char *pnd,*pnf;
char *pmsl,*pesr;
char *home,*usr;
int lb=0,ls=0;
FILE *fp,*fp0;
DIR *dp;

/* Sezione principale: funzione main() */
int main(int argc,char **argv) {
	unsigned long primenumber(unsigned long);
	short cfglang(short *);
	void show(unsigned long, unsigned long);
	void about(char *);

	/* Dichiarazioni di variabili esterne */
	extern short flg,bklng,lang,lngdef;
	extern char *pnd,*pnf;
	extern char *pmsl,*pesr;
	extern char *home,*usr;
	extern int lb,ls;

	/* Dichiarazioni di variabili locali */
	unsigned long numl=NPR,numh=NPR;
	char mark='\0',optn='\0',optz='\0';
	char h='\0',e='\0',l='\0',p='\0';
	char esr[5],msl[6],nd[16],lask[2],laskdef[24],lasklng[12];
	char *plask,*plaskdef,*vers=VERSION;
	char *plaskln0,*plaskln1,*plaskln2,*plaskln3,*plaskln4;
	int help=0;
	short ce=0;

	/* Inizializzazione di variabili static ed esterne */
	lang=lngdef;

	/* Inizializzazione puntatori */
	plaskdef=laskdef;
	plaskln0=lasklng;
	plask=lask;
	pesr=esr;
	pmsl=msl;
	pnd=nd;
	pnf=nfile;

	/* Definizione della lingua pre-impostata per init-ask. */
	if(lngdef==ENGLISH) {
		plaskdef="ENGLISH (Default)";
		plaskln0="ITALIANO";
		plaskln1="ESPAÑOL";
		plaskln2="FRANÇAIS";
		plaskln3="PORTUGÛES";
		plaskln4="DEUTCHE";
	}
	else if(lngdef==ITALIANO) {
	  plaskdef="ITALIANO (Predefinita";
	  plaskln0="ENGLISH";
		plaskln1="ESPAÑOL";
	  plaskln2="FRANÇAIS";
	  plaskln3="PORTUGÛES";
	  plaskln4="DEUTCHE";
	}
	else if(lngdef==ESPANOL) {
	  plaskdef="ESPAÑOL (Defecto)";
	  plaskln0="ENGLISH";
		plaskln1="ITALIANO";
	  plaskln2="FRANÇAIS";
	  plaskln3="PORTUGÛES";
	  plaskln4="DEUTCHE";
	}
	else if(lngdef==FRANCAIS) {
	  plaskdef="FRANÇAIS (Défaut)";
	  plaskln0="ENGLISH";
		plaskln1="ITALIANO";
	  plaskln2="ESPAÑOL";
	  plaskln3="PORTUGÛES";
	  plaskln4="DEUTCHE";
	}
	else if(lngdef==PORTUGUES) {
	  plaskdef="PORTUGÛES (Padrão)";
	  plaskln0="ENGLISH";
		plaskln1="ITALIANO";
	  plaskln2="ESPAÑOL";
	  plaskln3="FRANÇAIS";
	  plaskln4="DEUTCHE";
	}
	else {
		if(lngdef==DEUTCHE) {
			plaskdef="DEUTCHE (Standard)";
			plaskln0="ENGLISH";
			plaskln1="ITALIANO";
		  plaskln2="ESPAÑOL";
		  plaskln3="FRANÇAIS";
		  plaskln4="PORTUGÛES";
		}
	}

	/* Inizializzazione degli identificatori del file di configurazione. */
	pmsl=LANG; pmsl=msl;
	pesr=ENDL; pesr=esr;

	/* Ottiene il nome dell'utente */
	ls=strlen(pmsl),lb=strlen(pesr);
	if((usr=getenv("USER"))==NULL) {

		/* Esecuzione se non viene trovato il nome dell'utente. */
		/* Non posso ottenere il nome dell'utente. */
		if(lang==ENGLISH)
			printf("Error: I can not open file [.fstlang.cfg].\n");
	  if(lang==ITALIANO)
			printf("Errore: Non posso aprire il file [.fstlang.cfg].\n");
		else if(lang==ESPANOL)
	    printf("Error: No se puede abrir el archivo [.fstlang.cfg].\n");
	  else if(lang==FRANCAIS)
	    printf("Erreur : impossible d'ouvrir le fichier [.fstlang.cfg].\n");
	  else if(lang==PORTUGUES)
	    printf("Erro: Não é possível abrir o arquivo [.fstlang.cfg].\n");
	  else {
	    if(lang==DEUTCHE)
	      printf("Fehler: Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
	  }
	  return(printf("---K.O.\n\n"));
	}

	/* Ottiene il percorso della directory dell'utente. */
	struct passwd *pwd=getpwuid(getuid());
	if(pwd==NULL) {

		/* Esecuzione se non viene trovata la path della directory home. */
		/* Non posso ottenere il path della directory home. */
		if(lang==ENGLISH) {
		  printf("Error: Directory path does not exist.\n");
			printf("I can not open file [.fstlang.cfg].\n");
		}
		else if(lang==ITALIANO) {
		  printf("Errore: Percorso Directory inesistente.\n");
			printf("Non posso aprire il file [.fstlang.cfg].\n");
	  }
	  else if(lang==ESPANOL) {
	    printf("Error: La ruta del directorio no existe.\n");
	    printf("No se puede abrir el archivo [.fstlang.cfg].\n");
	  }
	  else if(lang==FRANCAIS) {
	    printf("Erreur : le chemin du répertoire n?existe pas.\n");
	    printf("Impossible d'ouvrir le fichier [.fstlang.cfg].\n");
	  }
	  else if(lang==PORTUGUES) {
	    printf("Erro: o caminho do diretorio não existe.\n");
	    printf("Não é possível abrir o arquivo [.fstlang.cfg].\n");
	  }
	  else {
	    if(lang==DEUTCHE) {
	      printf("Fehler: Der Verzeichnispfad existiert nicht.\n");
	      printf("Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
	    }
	  }
	  return(printf("---K.O.\n\n"));
	}

	/* Percorso della directory dell'utente. */
	home=pwd->pw_dir;

	/* Apertura di [.fstlang.cfg] in lettura. */
	snprintf(pnf,sizeof(nfile),"%s/.fstlang.cfg",home);
	if((fp0=fopen(pnf,"r"))==NULL) {

		/* Init-Ask (1) */
		/* Viene eseguito se non esiste il file di configurazione. */
		if(lngdef==ENGLISH) {
			printf("\n Language:\n");
			printf("  1 = %s\n",plaskdef);   /* Inglese */
			printf("  2 = %s\n",plaskln0);   /* Italiano */
			printf("  3 = %s\n",plaskln1);   /* Spagnolo */
			printf("  4 = %s\n",plaskln2);   /* Francese */
			printf("  5 = %s\n",plaskln3);   /* Portoghese */
			printf("  6 = %s\n",plaskln4);   /* Tedesco */
			printf(" Choose? ");
		}
		else if(lngdef==ITALIANO) {
		  printf("\n Lingua:\n");
		  printf("  1 = %s\n",plaskln0);   /* Inglese. */
			printf("  2 = %s\n",plaskdef);   /* Italiano */
			printf("  3 = %s\n",plaskln1);   /* Spagnolo */
		  printf("  4 = %s\n",plaskln2);   /* Francese */
		  printf("  5 = %s\n",plaskln3);   /* Portoghese */
		  printf("  6 = %s\n",plaskln4);   /* Tedesco */
		  printf(" Scegliere? ");
		}
		else if(lngdef==ESPANOL) {
		  printf("\n Lengua:\n");
		  printf("  1 = %s\n",plaskln0);   /* Inglese */
		  printf("  2 = %s\n",plaskln1);   /* Italiano */
		  printf("  3 = %s\n",plaskdef);   /* Spagnolo */
		  printf("  4 = %s\n",plaskln2);   /* Francese */
		  printf("  5 = %s\n",plaskln3);   /* Portoghese */
		  printf("  6 = %s\n",plaskln4);   /* Tedesco */
		  printf(" ¿Escoger? ");
		}
		else if(lngdef==FRANCAIS) {
		  printf("\n Langue:\n");
		  printf("  1 = %s\n",plaskln0);   /* Inglese */
		  printf("  2 = %s\n",plaskln1);   /* Italiano */
		  printf("  3 = %s\n",plaskln2);   /* Spagnolo */
		  printf("  4 = %s\n",plaskdef);   /* Francese */
		  printf("  5 = %s\n",plaskln3);   /* Portoghese */
		  printf("  6 = %s\n",plaskln4);   /* Tedesco */
		  printf(" Choisir? ");
		}
		else if(lngdef==PORTUGUES) {
		  printf("\n Lìngua:\n");
		  printf("  1 = %s\n",plaskln0);   /* Inglese */
		  printf("  2 = %s\n",plaskln1);   /* Italiano */
		  printf("  3 = %s\n",plaskln2);   /* Spagnolo */
		  printf("  4 = %s\n",plaskln3);   /* Francese */
		  printf("  5 = %s\n",plaskdef);   /* Portoghese */
		  printf("  6 = %s\n",plaskln4);   /* Tedesco */
		  printf(" Escolher? ");
		}
		else {
			if(lngdef==DEUTCHE) {
			  printf("\n Zunge:\n");
				printf("  1 = %s\n",plaskln0);   /* Inglese */
				printf("  2 = %s\n",plaskln1);   /* Italiano */
				printf("  3 = %s\n",plaskln2);   /* Spagnolo */
			  printf("  4 = %s\n",plaskln3);   /* Francese */
			  printf("  5 = %s\n",plaskln4);   /* Portoghese */
			  printf("  6 = %s\n",plaskdef);   /* Tedesco. */
				printf(" Wählen? ");
			}
		}
		while((*plask=getchar())!='\n')
			plask++;
		plask=lask;
		if(*plask=='\n')
			lang=lngdef;
		else
			lang=atoi(plask),bklng=lang;
		putchar('\n');

		/* Se la lingua non esiste usa quella prestabilita */
    if(!lang||lang>6)
      lang=lngdef;

		/* Esecuzione in caso il file di configurazione sia assente o inaccessibile. */
		if(lang==ENGLISH) {
			printf("The configuration file [.fstlang.cfg] will be created.\n");
			printf("English language setting.\n");
	  }
		else if(lang==ITALIANO) {
			printf("Il file di configurazione [.fstlang.cfg] è stato creato.\n");
			printf("Impostazione per la lingua italiana.\n");
		}
		else if(lang==ESPANOL) {
		  printf("Se ha creado el archivo de configuración [.fstlang.cfg].\n");
		  printf("Configuración del idioma español.\n");
		}
		else if(lang==FRANCAIS) {
		  printf("Le ficher de configuration [.fstlang.cfg] a été créé.\n");
		  printf("Configuration de la langue français.\n");
		}
		else if(lang==PORTUGUES) {
		  printf("O arquivo de configuração [.fstlang.cfg] foi criado.\n");
		  printf("Configuração da língua portuguesa.\n");
		}
		else {
		  if(lang==DEUTCHE) {
		    printf("Die Konfigurationsdatei [.fstlang.cfg] wurde erstellt.\n");
		    printf("Einstellung für deutsche Sprache.\n");
		  }
		}

		/* Apertura di .fstlang.cfg in scrittura.  */
		snprintf(pnf,sizeof(nfile),"%s/.fstlang.cfg",home);
		if((fp=fopen(pnf,"w"))==NULL) {

			/* Esecuzione se il file di configurazione non si può aprire. */
			if(lang==ENGLISH) {
			  printf("Error: I can not open file [.fstlang.cfg]!\n");
			  printf("Ok. The default language will be kept.\n");
			  lang=lngdef;
			}
			else if(lang==ITALIANO) {
				printf("Errore: Non posso aprire il file [.fstlang.cfg]!\n");
				printf("Ok. Sarà mantenuta la lingua preimpostata.\n");
				lang=lngdef;
			}
			else if(lang==ESPANOL) {
			  printf("Error: No se puede abrir el archivo [.fstlang.cfg].\n");
			  printf("Se mantendrá el idioma predeterminado.\n");
			}
		  else if(lang==FRANCAIS) {
		    printf("Erreur : impossible d'ouvrir le fichier [.fstlang.cfg].\n");
			  printf("La langue par défault sera conservée.\n");
			  lang=lngdef;
		  }
		  else if(lang==PORTUGUES) {
		    printf("Erro: Não é possível abrir o arquivo [.fstlang.cfg].\n");
			  printf("O idioma padrão será mantido.\n");
			  lang=lngdef;
		  }
		  else {
		    if(lang==DEUTCHE) {
		      printf("Fehler: Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
			    printf("Die Standardsprache bleibt erhalten.\n");
			    lang=lngdef;
		    }
		  }
		}
		else {

			/* Memorizzazione del nuovo stato del flag per la selezione della lingua. */
			pmsl=LANG; fputs(pmsl,fp);   /* Stringa identificativa iniziale. */
			ce=(short)fputc(lang,fp);        /* Flag impostazione lingua. */
			pesr=ENDL; fputs(pesr,fp);   /* Stringa identificativa finale. */
			if(ce!=bklng) {

				/* Esecuzione in caso in cui la lingua non sia stata salvata. */
				if(lang==ENGLISH) {
					printf("Error: File [.fstlang.cfg] not changed!\n");
					lang=lngdef;
				}
				else if(lang==ITALIANO) {
					printf("Errore: File [.fstlang.cfg] non cambiato!\n\n");
					lang=lngdef;
				}
				else if(lang==ESPANOL) {
				  printf("Error: ¡El archivo [.fstlang.cfg] no ha cambiado!\n\n");
				  lang=lngdef;
				}
				else if(lang==FRANCAIS) {
				  printf("Erreur : fishier [.fstlang.cfg] non modifié !\n\n");
				  lang=lngdef;
				}
				else if(lang==PORTUGUES) {
				  printf("Erro: Arquivo [.fstlang.cfg] não alterado!\n\n");
				  lang=lngdef;
				}
				else {
				  if(lang==DEUTCHE) {
				    printf("Fehler: Datei [.firstlang.cfg] nicht geändert!\n\n");
				    lang=lngdef;
				  }
				}
			}
		}
		fclose(fp);
		if(ce==bklng)
			return(printf("+++Ok.\n\n"));
		return(printf("---K.O.\n\n"));
	}
	else {

		/* Lettura dello stato del flag per la selezione della lingua dal file .firstlang.cfg */
		pmsl=LANG,pesr=ENDL;
		pnd=fgets(pmsl,ls,fp0);
		if(pnd!=NULL) {

		/* Esecuzione se il file di configurazione non si può aprire. */
			if(lang==ENGLISH)
			  printf("Error: I can not open file [.fstlang.cfg].\n");
			else if(lang==ITALIANO)
				printf("Errore: Non posso aprire il file [.fstlang.cfg].\n");
			else if(lang==ESPANOL)
        printf("Error: No se puede abrir el archivo [.fstlang.cfg].\n");
      else if(lang==FRANCAIS)
        printf("Erreur : impossible d'ouvrir le fichier [.fstlang.cfg].\n");
      else if(lang==PORTUGUES)
        printf("Erro: Não é possível abrir o arquivo [.fstlang.cfg].\n");
      else {
        if(lang==DEUTCHE)
          printf("Fehler: Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
      }
      return(printf("---K.O.\n\n"));
		}
		fseek(fp0,-5L,SEEK_END);   /* Sposta l'offest di inizio file.  */
		lang=fgetc(fp0);
		fclose(fp0);
		if(lang>6)
			lang=lngdef;
	}

	/* Esegue senza argomenti */
	if(argc==1) {
		about(vers);
		return Ok;
	}

	/* Esegue con un argomento */
	if(argc == 2) {
		mark=(char)tolower(**(argv+1));
		optn=(char)tolower((int)argv[1][1]);
		optz=(char)tolower((int)argv[1][2]);
		if(isdigit(**(argv+1))) {
			numl=(unsigned long)atof(*(argv+1));
			numh=numl;
		}

		/* Cambio della lingua impostata. */
		/* Impostazione della lingua inglese. */
		if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='N') {
			lang=ENGLISH,bklng=lang;
			if(!cfglang(&lang))
				return Ok;
			else
				return WARN;
		}

		/* Impostazione della lingua italiana. */
		else if(*(*(argv+1))=='I'&&*(*(argv+1)+1)=='T') {
			lang=ITALIANO,bklng=lang;
			if(!cfglang(&lang))
				return Ok;
			else
				return WARN;
		}

		/* Impostazione della lingua spagnola. */
		else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='S') {
			lang=ESPANOL,bklng=lang;
			if(!cfglang(&lang))
				return Ok;
			else
				return WARN;
		}

		/* Impostazione della lingua francese. */
		else if(*(*(argv+1))=='F'&&*(*(argv+1)+1)=='R') {
			lang=FRANCAIS,bklng=lang;
			if(!cfglang(&lang))
				return Ok;
			else
				return WARN;
		}

		/* Impostazione della lingua portoghese. */
		else if(*(*(argv+1))=='P'&&*(*(argv+1)+1)=='T') {
			lang=PORTUGUES,bklng=lang;
			if(!cfglang(&lang))
				return Ok;
			else
				return WARN;
		}

    /* Impostazione della lingua tedesca. */
		else if(*(*(argv+1))=='D'&&*(*(argv+1)+1)=='E') {
		  lang=DEUTCHE,bklng=lang;
		  if(!cfglang(&lang))
				return Ok;
			else
	  	  return WARN;
    }
    else {
      if(**(argv+1)!='-'&&!isdigit(**(argv+1))) {
        if(bklng!=EN&&bklng!=IT&&bklng!=ES&&bklng!=FR&&bklng!=PT&&bklng!=DE) {
          if(lang==ENGLISH)
            printf("Error: Language not supported!\n");
          else if(lang==ITALIANO)
            printf("Errore: Lingua non supportata!\n");
          else if(lang==ESPANOL)
            printf("Error: ¡Idioma no compatible!\n");
          else if(lang==FRANCAIS)
            printf("Erreur : Langue non prise en charge !\n");
          else if(lang==PORTUGUES)
            printf("Erro: Idioma não suportado!\n");
          else {
            if(lang==DEUTCHE)
              printf("Fehler: Sprache nitch unterstützt!\n");
          }
          if(!cfglang(&lang))
				    return Ok;
			    else
	  	      return WARN;
        }
      }
    }

		/* Opzione per l'aiuto compatto */
		if((mark=='-')&&(optn=='h')) {
			if(optz!='\0') {

			  /* Visualizza messaggio per opzione erata */
				if(lang==ENGLISH)
					return(printf("Error: Wrong option!\n\n"));
				else if(lang==ITALIANO)
					return(printf("Errore: Opzione errata!\n\n"));

			  else if(lang==ESPANOL)
			    return(printf("Error: ¡Opción incorrecta!\n\n"));

			  else if(lang==FRANCAIS)
			    return(printf("Erreur : Mauvaise option !\n\n"));

			  else if(lang==PORTUGUES)
			    return(printf("Erro: Opção errada!\n\n"));

			  else {
			    if(lang==DEUTCHE)
			      return(printf("Fehler: Falsche Option!\n\n"));
			  }
			}
			else {

			  /* Visualizza l'aiuto compatto */
				if(lang==ENGLISH) {
					printf("\nTo use: first --help  Display extended help,\n");
					printf("     or first [VALUE]  Report whether the number is prime,\n");
					printf("     or first [MINIMUM VALUE] [MAXIMUM VALUE]\n");
					printf("               Display a list of prime numbers.\n\n");
					return Ok;
				}
				else if(lang==ITALIANO) {
					printf("\nUsare: first --help  Visualizza l'aiuto esteso,\n");
					printf("     o first [VALORE]  Informa se il valore è un numero primo,\n");
					printf("     o first [VALORE MINIMO] [VALORE MASSIMO]\n");
					printf("              Visualizza una lista di numeri primi.\n\n");
					return Ok;
				}

				else if(lang==ESPANOL) {
				  printf("\nUso: first --help  Muesta ayuda extendida, \n");
				  printf("   o first [VALOR]  Informar si el número es primo,\n");
				  printf("   o first [VALOR MINIMO] [VALOR MÁXIMO]\n");
				  printf("            Muestra una lista de números primos.\n");
				  return Ok;
				}

				else if(lang==FRANCAIS) {
				  printf("\nUtilisation: first --help  Afficher l'aide éntendue,\n");
				  printf("          ou first [VALEUR]  Indiquer si le nombre est premier,\n");
				  printf("          ou first [VALEUR MINIMALE] [VALEUR MAXIMALE]\n");
				  printf("                    Affiche une liste de nombres premiers.\n");
				  return Ok;
				}

				else if(lang==PORTUGUES) {
				  printf("\nUse: first --help  Exibe ajuda estendida,\n");
				  printf("  ou first [VALOR]  Informa se o número é primo,\n");
				  printf("  ou first [VALOR MINIMO] [VALOR MÁXIMO]\n");
				  printf("            Exibe uma lista de números primos.\n");
				  return Ok;
				}

				else {
				  if(lang==DEUTCHE) {
				    printf("\nVerwenden: first --help  Erweiterte Hilfe anzeigen,\n");
				    printf("      oder first [WERT]  Melden Sie,ob die Zahl eine Primzahl ist,\n");
				    printf("      oder first [MINIMALWERT] [MAXIMALWERT]\n");
				    printf("                  Zeigt eine Liste von Primzahlen an.\n");
				    return Ok;
				  }
				}
			}
			return WARN;
		}

		/* Opzione per l'aiuto esteso */
		else if((mark=='-')&&(optn=='-')) {
			h=(char)tolower((int)argv[1][2]);
			e=(char)tolower((int)argv[1][3]);
			l=(char)tolower((int)argv[1][4]);
			p=(char)tolower((int)argv[1][5]);
			help=(int)(h+e+l+p);
			if(help==HELP) {

			  /* Visualizza l'aiuto esteso */
				printf("\nfirst  Release %s\n",vers);
				printf("(~© (1991-2024) GNU/GPL2)\n\n");
				if(lang==ENGLISH) {
					printf("To use: first [OPTION] [VALUE [VALUE]]  Usage syntax model.\n");
					printf("        first  About and help.\n");
					printf("        first -h  Quick help.\n");
					printf("        first --help  This help.\n");
					printf("        first [VALUE]  Informs whether the value is a prime number.\n");
					printf("        first [MINIMUM VALUE] [MAXIMUM VALUE]  List of prime number.\n\n");
					printf("Series width: maximum value - minimum value + 1 <= 65535\n");
					printf("Standard text terminal display: 80 columns 24 rows recommended.\n");
					printf("To redirect output to a file use > or >>\n");
					printf("Examples: first [MINIMUM VALUE] [MAXIMUM VALUE] > filename  Save in file.\n");
					printf("       or first [MINIMUM VALUE] [MAXIMUM VALUE] >> file_name  Add to file.\n\n");
					printf("    type: first 12345\n");
					printf("          first 11134 12399\n");
					printf("          first 100001 165535 > $HOME/prime\n\n");
					return Ok;
				}
				else if(lang==ITALIANO) {
					printf("Usare: first [OPZIONE] [VALORE [VALORE]]  Modello della sintassi d'uso.\n");
					printf("       first  Informazioni ed aiuto.\n");
					printf("       first -h  Aiuto rapido.\n");
					printf("       first --help  Questo aiuto.\n");
					printf("       first [VALORE]  Informa se il valore è un numero primo.\n");
					printf("       first [VALORE MINIMO] [VALORE MASSIMO]  Lista di numeri primi.\n\n");
					printf("Ampiezza della serie: valore massimo - valore minimo + 1 <= 65535\n");
					printf("Visualizzazione su terminale di testo standard: raccomandato 80 colonne, 24 righe.\n");
					printf("Per la redirezione dell'uscita verso un file, usare > o >>\n");
					printf("Esempi: first [VALORE MINIMO] [VALORE MASSIMO] > nomefile  Salva nel file.\n");
					printf("      o first [VALORE MINIMO] [VALORE MASSIMO] >> nome_file  Aggiungi al file.\n\n");
					printf("digitare: first 12345\n");
					printf("          first 11134 12399\n");
					printf("          first 100001 165535 > $HOME/prime\n\n");
					return Ok;
				}
				else if(lang==ESPANOL) {
				  printf("Uso: first [OPCIÓN] [VALOR [VALOR]]  Modelo de sintaxis de uso.\n");
				  printf("     first  Información y ayuda.\n");
				  printf("     first -h  Ayuda rápida.\n");
				  printf("     first --help  Esta ayuda.\n");
				  printf("     first [VALOR]  Informa si el valor es un número primo.\n");
				  printf("     first [VALOR] [VALOR]  Lista de números primos.\n\n");
				  printf("Ampliación de la serie: valor máximo - valor minimo + 1 <= 65535\n");
				  printf("Pantalla de terminal de texto estándar: 80 columnas, se recomiendar 24 filas.\n");
				  printf("Para redirigir la salida a un archivo, utilice > o >>\n");
				  printf("Ejemplos: first [VALOR MÍNIMO] [VALOR MÁXIMO] > nombre_archivo  Guardar en archivo.\n");
				  printf("        o first [VALOR MÍNIMO] [VALOR MÁXIMO] > nombre_archivo  Añadir el archivo.\n\n");
				  printf("Tipo: first 12345\n");
				  printf("      first 11134 12399\n");
				  printf("      first 100001 165535 > $HOME/prime\n\n");
				  return Ok;
				}
				else if(lang==FRANCAIS) {
				  printf("Utiliser: first [OPTION] [VALEUR [VALEUR]]  Modèle de syntaxe d'utilisation.\n");
				  printf("          first  Informations et aide.\n");
				  printf("          first -h  Aide rapide.\n");
				  printf("          first --help  Cette aide.\n");
				  printf("          first [VALEUR]  Indique si la valeur est un nombre premier.\n");
				  printf("          first [VALEUR] [VALEUR]  Liste des nombres premiers.\n\n");
				  printf("Largeur de la série : valeur maximale - valeur minimale + 1 <= 65535\n");
				  printf("Affichage du terminal texte standard: 80 colonnes, 24 lignes recommandées.\n");
				  printf("Pour rediriger la sortie vers un fichier, utilisez > ou >>\n");
				  printf("Exemples : first [VALEUR MIN] [VALEUR MAX] > nom_ficher  Enregistrer dans le ficher.\n");
				  printf("        ou first [VALEUR MIN] [VALEUR MAX] > nom_ficher  Ajouter ou ficher.\n\n");
				  printf("Taper : first 12345\n");
				  printf("        first 11134 12399\n");
				  printf("        first 100001 165535 > $HOME/prime\n\n");
				  return Ok;
				}
				else if(lang==PORTUGUES) {
				  printf("Usar: first [OPÇÃO] [VALOR [VALOR]]  Modelo de sintaxe de uso.\n");
				  printf("      first  Informações e ajuda.\n");
				  printf("      first -h  Ajuda rápida.\n");
				  printf("      first --help  Esta ajuda.\n");
				  printf("      first [VALOR]  Informa se o valor é um número primo.\n");
				  printf("      first [VALOR] [VALOR]  Lista de números primos.\n\n");
				  printf("Largura da série: valor máximo - valor minimo + 1 <=65535\n");
				  printf("Exibição de terminal de texto padrão: 80 colunas, 24 linhas recomendadas.\n");
				  printf("Para redirecionar a saída para um arquivo use > ou >>\n");
				  printf("Exemplos: first [VALOR MÍNIMO] [VALOR MÁXIMO] > nome_arquivo  Salvar em arquivo.\n");
				  printf("       ou first [VALOR MÍNIMO] [VALOR MÁXIMO] > nome_arquivo  Adicionar ao arquivo.\n\n");
				  printf("Tipo: first 12345\n");
				  printf("      first 11134 12399\n");
				  printf("      first 100001 165535 > $HOME/prime\n\n");
				  return Ok;
				}
				else {
				  if(lang==DEUTCHE) {
				    printf("Verwenden: first [OPTION] [WERT [WERT]]  Verwendungssyntaxmodell.\n");
				    printf("           first  Informationen und Hilfe.\n");
				    printf("           first -h  Schnelle Hilfe.\n");
				    printf("           first --help  Diese Hilfe.\n");
				    printf("           fisrt [WERT]  Gibt an, ob der Wert eine Primzahl ist.\n");
				    printf("           first [WERT] [WERT]  Liste der Primzahlen.\n\n");
				    printf("Serienbreite: Maximalwert - Mininimalwert + 1 <= 65535\n");
				    printf("Standard-Textterminalanzeige: 80 Spalten, 24 Zeilen empfohlen.\n");
				    printf("Um die Ausgabe in eine Datei umzuleiten, verwenden Sie > oder >>\n");
				    printf("Beispiele: first [Minimalwert] [Maximalwert] > Dateiname  In Datei speichern.\n");
				    printf("      oder first [Minimalwert] [Maximalwert] > Dateiname  Zur Datei hinzufügen.\n\n");
				    printf("Typ: first 12345\n");
				    printf("     first 11134 12399\n");
				    printf("     first 100001 165535 > $HOME/prime\n\n");
				    return Ok;
				  }
				}
				return WARN;
			}
			else {
				if(lang==ENGLISH)
					return(printf("Error: Bad or missing option.\n\n"));
				else if(lang==ITALIANO)
					return(printf("Errore: Opzione errata o mancante.\n\n"));
				else if(lang==ESPANOL)
				  return(printf("Error: Opción incorrecta o faltante.\n\n"));
				else if(lang==FRANCAIS)
				  return(printf("Erreur : option incorrecte ou manquante.\n\n"));
				else if(lang==PORTUGUES)
				  return(printf("Erro: Opção incorreta ou ausente.\n\n"));
				else {
				  if(lang==DEUTCHE)
				    return(printf("Fehler: Falsche oder fehlende Option.\n\n"));
				}
			}
		}
		else if(!isdigit(**(argv+1))) {
		  if(lang==ENGLISH)
				return(printf("Error: Wrong and/or missing argument!\n\n"));
			else if(lang==ITALIANO)
				return(printf("Errore: Argomento errato e/o mancante.\n\n"));
			else if(lang==ESPANOL)
			  return(printf("Error: ¡Argumento incorrecto o faltante!\n\n"));
			else if(lang==FRANCAIS)
			  return(printf("Erreur : argument incorrect et/ou manquant !\n\n"));
			else if(lang==PORTUGUES)
			  return(printf("Erro: Argumento incorreto e/ou ausente!\n\n"));
			else {
			  if(lang==DEUTCHE)
			    return(printf("Fehler: Falsches und/oder fehlendes Argument!\n\n"));
			}
		}
	}

	/* Esegue con due argomenti */
	if(argc==3) {
	  if(!flg) flg=1;
		if(isdigit(**(argv+1))&&isdigit(**(argv+2))) {
			numl=(unsigned long)atof(*(argv+1));
			numh=(unsigned long)atof(*(argv+2));
		}
		else {
			if(lang==ENGLISH)
				return(printf("Error: Bad arguments!\n\n"));
			if(lang==ITALIANO)
				return(printf("Errore: Argomento errato!\n\n"));
			if(lang==ESPANOL)
			  return(printf("Error: ¡Tema incorrecto!\n\n"));
			if(lang==FRANCAIS)
			  return(printf("Erreur : suject incorrect !\n\n"));
			if(lang==PORTUGUES)
			  return(printf("Erro: Tópico incorreto!\n\n"));
			else {
			  if(lang==DEUTCHE)
			    return(printf("Fehler: Falsches Thema!\n\n"));
			}
		}
	}

	/* Esegue con più di due argomenti */
	if(argc>3) {
		if(lang==ENGLISH)
			return(printf("Error: Too many arguments!\n\n"));
		if(lang==ITALIANO)
			return(printf("Errore: Troppi argomenti!\n\n"));
		if(lang==ESPANOL)
			return(printf("Error: ¡Demasiados temas!\n\n"));
	  if(lang==FRANCAIS)
			return(printf("Erreur : trop de suject !\n\n"));
	  if(lang==PORTUGUES)
			return(printf("Erro: Muitos tópicos!\n\n"));
	  else {
	    if(lang==DEUTCHE)
			  return(printf("Fehler: Zu viele Themen!\n\n"));
	  }
	}

	/* Controllo dei valori numerici in ingresso  */
	if(numl>LN_MAX||numh>LN_MAX) {
		if(lang==ENGLISH)
			return(printf("Error: Values out of range!\n\n"));
		if(lang==ITALIANO)
			return(printf("Errore: Valori fuori limite!\n\n"));
		if(lang==ESPANOL)
			return(printf("Error: Valores fuera de limite!\n\n"));
	  if(lang==FRANCAIS)
			return(printf("Erreur : valeurs hors limites !\n\n"));
	  if(lang==PORTUGUES)
			return(printf("Erro: Valores fora do limite!\n\n"));
	  else {
	    if(lang==DEUTCHE)
			  return(printf("Fehler: Werte außerhalb des Grenzwerts!\n\n"));
	  }
	}
	if(numh<numl) {
		if(lang==ENGLISH)
			return(printf("Error: Arguments or values has been inverted.\n\n"));
		if(lang==ITALIANO)
			return(printf("Errore: Argomenti o valori invertiti.\n\n"));
		if(lang==ESPANOL)
			return(printf("Error: Argumentos o valores invertidos.\n\n"));
	  if(lang==FRANCAIS)
			return(printf("Erreur : Arguments ou valeurs inversés.\n\n"));
	  if(lang==PORTUGUES)
			return(printf("Erro: Argumentos ou valores invertidos.\n\n"));
	  else {
	    if(lang==DEUTCHE)
			  return(printf("Fehler: Argumente oder Werte vertauscht.\n\n"));
	  }
	}
	if((numh-numl+1)>RANGE) {
		if(lang==ENGLISH) {
			printf("Error: Range too large (v.max - v.min + 1 > 65536 values).\n");
			return(printf(" v.max = Highest value in the series.\n"
			 " v.min = Lowest value in the series.\n\n"));
		}
		if(lang==ITALIANO) {
			printf("Errore: Serie troppo ampia (v.max - v.min + 1 > 65536 valori).\n");
			return(printf(" v.max = Valore più alto della serie.\n"
			 " v.min = Valore più basso della serie.\n\n"));
		}
		if(lang==ESPANOL) {
			printf("Error: Serie es demasiado grande (v.max - v.min + 1 > 65536 valores).\n");
			return(printf(" v.max = Valor más alto de la serie.\n"
			 " v.min = Valor más bajo de la serie.\n\n"));
		}
	  if(lang==FRANCAIS) {
			printf("Erreur : série trop grande (v.max - v.min + 1 > 65536 valeurs).\n");
			return(printf(" v.max = Valeur la plus elevée de la série.\n"
			 " v.min = Valeur la plus basse de la série.\n\n"));
		}
	  if(lang==PORTUGUES) {
			printf("Erro: Serie muito grande (v.max - v.min + 1 > 65536 valores).\n");
			return(printf(" v.max = Maior valor da serie.\n"
			 " v.min = Menor valor da serie.\n\n"));
		}
	  else {
	    if(lang==DEUTCHE) {
			  printf("Fehler: Serie zu groß (v.max - v.min + 1 > 65536 Werte).\n");
			  return(printf(" v.max = Höchster Wert der Serie.\n"
			 " v.min = Niedrigster Wert der Reihe.\n\n"));
			}
	  }
	}
	/* --------------------------------------------------------------- */
	show(numl,numh);   /* chiama la funzione che stampa i numeri primi */
	return(putchar('\n'));
	/* --------------------------------------------------------------- */
}

/* -------------------------------------------- */
/* Funzione primenumber(), trova i numeri primi */
/* -------------------------------------------------------------------------- */
/* L'algoritmo di questa funzione è sottoposto al CopyLeft ~© 1991-2024,
   ed alla GNU Public License version 2 e 3 di Free Software Foundation.
   Rif. http://www.gnu.org/copyleft
        http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
        http://www.gnu.org/licenses/gpl-3.0.html

   Creato da G. B. alias PiErre60 (Italy) [prime=primenum(number) ~© 1990-1991],
   e successive modifiche ~© 1997-2001-2010-2024.  */
/* -------------------------------------------------------------------------- */
unsigned long primenumber(unsigned long number) {

  /* Dichiarazione di variabili locali */
	unsigned long nbase=0UL,ndivs=2UL,divsf=0UL;

	if(number==0) {
		divsf=0;
		return ZDIVS;   /* Lo zero per convenzione è considerato pari, non classificabile. */
	}
	if(number==1) {
		divsf=0;
		return UNCL;    /* Il numero uno viene considerato non classificabile, non primo. */
	}
	if(number==2)
		return NPR;    /* Il due è considerato numero primo². */
	nbase=(unsigned long)sqrt((double)number);
	nbase++;
	while(nbase>=ndivs) {
		if(!(number%ndivs))
			divsf=ndivs,ndivs=nbase;
		ndivs++;
	}
	if(!divsf)
		return NPR;
	else
		return NDIVS;
}

/* ------------------------------------------ */
/* Funzione show(), visualizza i numeri primi */
void show(unsigned long numb, unsigned long numt) {

  /* Dichiarazioni di funzioni */
  unsigned long primenumber(unsigned long);

  /* Dichiarazioni di variabili esterne */
  extern short lang;
  extern short flg;

  /* Dichiarazioni di variabili locali */
	unsigned long nums;
	unsigned int count=0,pcount=0;
	short clp=0,ncl=0;
	nums=numb;
	if(!flg&&((primenumber(nums)==NDIVS)&&nums>UNCL)) {
	  if(lang==ENGLISH)
	    printf("%ld is not a prime number.\n",nums);
	  else if(lang==ITALIANO)
	    printf("%ld non è un numero primo.\n",nums);
	  else if(lang==ESPANOL)
	    printf("%ld no es un número primo.\n",nums);
	  else if(lang==FRANCAIS)
	    printf("%ld n'est pas un nombre premier.\n",nums);
	  else if(lang==PORTUGUES)
	    printf("%ld não é um número primo.\n",nums);
	  else {
	    if(lang==DEUTCHE)
	      printf("%ld ist keine Primzahl.\n",nums);
	  }
	  return;
	}
  if(!flg&&((primenumber(nums)==NPR)&&nums>UNCL)) {
	  if(lang==ENGLISH)
	    printf("%ld it is a prime number.\n",nums);
	  else if(lang==ITALIANO)
	    printf("%ld è un numero primo.\n",nums);
	  else if(lang==ESPANOL)
	    printf("%ld es un número primo.\n",nums);
	  else if(lang==FRANCAIS)
	    printf("%ld est un nombre premier.\n",nums);
	  else if(lang==PORTUGUES)
	    printf("%ld é um número primo.\n",nums);
	  else {
	    if(lang==DEUTCHE)
	      printf("%ld ist eine Primzahl.\n",nums);
	  }
	  return;
	}
	if(nums==ZDIVS&&!flg) {
	  if(lang==ENGLISH)
	    printf("Zero is conventionally considered unclassifiable.\n");
	  else if(lang==ITALIANO)
	    printf("Lo zero per convenzione è considerato on classificabile.\n");
	  else if(lang==ESPANOL)
	    printf("El cero por convención se considera inclasificable.\n");
	  else if(lang==FRANCAIS)
	    printf("Zéro par convention est considéré comme inclassable.\n");
	  else if(lang==PORTUGUES)
	    printf("Zero por convenção é considerado inclassificável.\n");
	  else {
	    if(lang==DEUTCHE)
	      printf("Null gilt per Konvention als nicht klassifizierbar.\n");
	  }
	  return;
	}
	if(nums==UNCL&&!flg) {
	  if(lang==ENGLISH) {
	    printf("The number one is considered unclassifiable:");
	    printf("Not a prime number.\n");
	  }
	  else if(lang==ITALIANO) {
	    printf("Il numero uno viene considerato non classificabile:");
	    printf("Non è un numero primo.\n");
	  }
	  else if(lang==ESPANOL) {
	    printf("El número uno se considera inclasificable:\n");
	    printf("no es un número primo.\n");
	  }
	  else if(lang==FRANCAIS) {
	    printf("Le nombre un est considéré comme inclassable :\n");
	    printf("ce n'est pas un nombre premier.\n");
	  }
	  else if(lang==PORTUGUES) {
	    printf("O número um é considerato inclassificavel:\n");
	    printf("não é um número primo.\n");
	  }
	  else {
	    if(lang==DEUTCHE) {
	      printf("Die Zahl Eins gilt als nicht klassifizierbar:\n");
	      printf("Sie ist keine Primzahl.\n");
	    }
	  }
	  return;
	}
	while(nums<=numt) {
	  if(nums<2) nums=2;
		if(primenumber(nums)) {
			if(clp==ncl) {
				clp=0;
				printf("\n");
			}
			if(nums<100000) {
				ncl=10;
				printf("%6lu\t",nums);
			}
			if((nums>99999) && (nums<1000000)) {
				ncl=9;
				if(nums==100003) {
					clp=0;
					printf("\n\n");
				}
				printf("%7lu\t",nums);
			}
			if((nums>999999)&&(nums<100000000)) {
				ncl=5;
				if(nums==1000003) {
					clp=0;
					printf("\n\n");
				}
				printf("%9lu\t",nums);
			}
			if(nums>99999999) {
				ncl=5;
				printf("%9lu\t",nums);
			}
			pcount++,clp++;
		}
		nums++,count++;
	}
	if(numb<numt) {
    if(lang==ENGLISH) {
		  printf("\n\nProcessing %u values.",count);
		  printf("\nContens %u prime numbers.\n",pcount);
	  }
	  else if(lang==ITALIANO) {
		  printf("\n\nProcessati %u valori.",count);
		  printf("\nPresenti %u numeri primi.\n",pcount);
	  }
	  else if(lang==ESPANOL) {
	    printf("\n\nProcesó %u valores.",count);
	    printf("\nHay %u números primos.\n",pcount);
	  }
	  else if(lang==FRANCAIS) {
	    printf("\n\nTraité %u valeurs.",count);
	    printf("\nIl existe %u nombres premiers.\n",pcount);
	  }
	  else if(lang==PORTUGUES) {
	    printf("\n\nProcessado %u valores.",count);
	    printf("\nExistem %u números primos.\n",pcount);
	  }
	  else {
	    if(lang==DEUTCHE) {
	      printf("\n\n%u Werte verarbeitet.",count);
	      printf("\nEs gibt %u primzahlen.\n",pcount);
	    }
	  }
	}
	putchar('\n');
  return;
}

/* -------------------------------------------------------------------- */
/* Funzione per la riscrittura del file di configurazione per la lingua */
short cfglang(short *fllang) {

	/* Dichiarazioni di funzioni. */
	int filemsg(short *,unsigned long *);

	/* Dichiarazione di variabili esterne. */
	extern short lngdef,lang;
	extern char *pnd,*pnf;
	extern char *pmsl,*pesr;
	extern char *home,*usr;
	extern int ls,lb;
	extern short bklng;
	extern FILE *fp;

	/* Definizione di variabili locali. */
	short ce;

	/* Corpo funzione. */
	/* ottiene il nome dell'utente  */
	ls=strlen(pmsl),lb=strlen(pesr);
	if((usr=getenv("USER"))==NULL) {
		/* Esecuzione se non viene trovato il nome dell'utente. */
		/* Non posso ottenere il nome dell'utente. */
		if(lang==ENGLISH)
			printf("Error: I can not open file [.fstlang.cfg].\n");
	  if(lang==ITALIANO)
			printf("Errore: Non posso aprire il file [.fstlang.cfg].\n");
		else if(lang==ESPANOL)
	    printf("Error: No se puede abrir el archivo [.fstlang.cfg].\n");
	  else if(lang==FRANCAIS)
	    printf("Erreur : impossible d'ouvrir le fichier [.fstlang.cfg].\n");
	  else if(lang==PORTUGUES)
	    printf("Erro: Não é possível abrir o arquivo [.fstlang.cfg].\n");
	  else {
	    if(lang==DEUTCHE)
	      printf("Fehler: Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
	  }
	  return(printf("---K.O.\n\n"));
	}

	/* ottiene il percorso della directory dell'utente. */
	struct passwd *pwd=getpwuid(getuid());
	if(pwd==NULL) {
		/* Esecuzione se non viene trovata la path della directory home. */
		/* Non posso ottenere il path della directory home. */
		if(lang==ENGLISH) {
		  printf("Error: Directory path does not exist.\n");
			printf("I can not open file [.fstlang.cfg].\n");
		}
		else if(lang==ITALIANO) {
		  printf("Errore: Percorso Directory inesistente.\n");
			printf("Non posso aprire il file [.fstlang.cfg].\n");
	  }
	  else if(lang==ESPANOL) {
	    printf("Error: La ruta del directorio no existe.\n");
	    printf("No se puede abrir el archivo [.fstlang.cfg].\n");
	  }
	  else if(lang==FRANCAIS) {
	    printf("Erreur : le chemin du répertoire n?existe pas.\n");
	    printf("Impossible d'ouvrir le fichier [.fstlang.cfg].\n");
	  }
	  else if(lang==PORTUGUES) {
	    printf("Erro: o caminho do diretorio não existe.\n");
	    printf("Não é possível abrir o arquivo [.fstlang.cfg].\n");
	  }
	  else {
	    if(lang==DEUTCHE) {
	      printf("Fehler: Der Verzeichnispfad existiert nicht.\n");
	      printf("Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
	    }
	  }
	  return(printf("---K.O.\n\n"));
	}

	/* Percorso della directory dell'utente. */
	home=pwd->pw_dir;

	/* Apertura di .firstlang.cfg in scrittura. */
	snprintf(pnf,sizeof(nfile),"%s/.fstlang.cfg",home);
	if((fp=fopen(pnf,"w"))==NULL) {

		/* Esecuzione se il file di configurazione non si può aprire. */
		/* Non posso ottenere l'accesso al file di configurazione. */
		if(lang==ENGLISH) {
			printf("Error: I can not open file [.fstlang.cfg].\n");
			printf("The default language will be kept.\n");
		}
		else if(lang==ITALIANO) {
			printf("Errore: Non posso aprire il file [.fstlang.cfg].\n");
			printf("Sarà mantenuta la lingua preimpostata.\n");
		}
		else if(lang==ESPANOL) {
		  printf("Error: No se puede abrir el archivo [.fstlang.cfg].\n");
		  printf("Se mantendrá el idioma predeterminado.\n");
		}
		else if(lang==FRANCAIS) {
		  printf("Erreur : impossible d'ouvrir le fichier [.fstlang.cfg].\n");
		  printf("La langue par défault sera conservée.\n");
		}
		else if(lang==PORTUGUES) {
		  printf("Erro: Não é possível abrir o arquivo [.fstlang.cfg].\n");
		  printf("O idioma padrão será mantido.\n");
		}
		else {
		  if(lang==DEUTCHE) {
		    printf("Fehler: Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
		    printf("Die Standardsprache bleibt erhalten.\n");
		  }
		}
		return(printf("---K.O.\n\n"));
	}
	else {
	/* Controllo congruenza codice lingua. */
		if(!*fllang||*fllang>6)
			*fllang=lngdef;

		/* Memorizzazione del nuovo stato del flag per la selezione della lingua. */
		pmsl=LANG; fputs(pmsl,fp);   /* Stringa identificativa iniziale. */
		ce=(short)fputc(*fllang,fp);        /* Flag impostazione lingua. */
		pesr=ENDL; fputs(pesr,fp);   /* Stringa identificativa finale. */
		if(ce!=bklng) {

			/* Esecuzione in caso in cui il file non sia salvato */
			if(lang==ENGLISH)
				printf("File [.fstlang.cfg] not changed.\n");
			else if(lang==ITALIANO)
				printf("File [.fstlang.cfg] non cambiato.\n");
			else if(lang==ESPANOL)
	      printf("El archivo [.fstlang.cfg] no ha cambiado.\n");
	    else if(lang==FRANCAIS)
	      printf("Fichier [.fstlang.cfg] non modifié.\n");
	    else if(lang==PORTUGUES)
	      printf("Arquivio [.fstlang.cfg] não alterado.\n");
	    else {
	      if(lang==DEUTCHE)
	        printf("Datei [.fstlang.cfg] nicht geändert.\n");
	    }
	    fclose(fp);
	    return(printf("---K.O.\n\n"));
		}

		/* Se non ci sono errori */
		if(ce==bklng) {
		  if(lang==ENGLISH) {
		    printf("Rewrite the configuration file.\n");
			  printf("English language setting.\n");
	    }
		  else if(lang==ITALIANO) {
		    printf("File di configurazione modificato.\n");
			  printf("Impostazione per la lingua italiana.\n");
	    }
	    else if(lang==ESPANOL) {
	      printf("El archivo de configuración cambió.\n");
	      printf("Configuración del idioma español.\n");
	    }
	    else if(lang==FRANCAIS) {
	      printf("Fichier de configuration modifié.\n");
	      printf("Configuration de la langue français.\n");
	    }
	    else if(lang==PORTUGUES) {
	      printf("Arquivo de configuração alterado.\n");
	      printf("Configuração da língua portuguesa.\n");
	    }
	    else {
	      if(lang==DEUTCHE) {
	        printf("Konfigurationsdatei geändert.\n");
	        printf("Einstellung für deutsche Sprache.\n");
	      }
	    }
		  fclose(fp);
		  return(printf("+++Ok.\n\n"));
		}
		return(printf("---K.O.\n\n"));
	}
}

/* ------------------------------------------------------- */
/* Funzione about(), visualizza informazioni sul programma */
void about(char *ver) {

  /* Dichiarazione di variabile esterna */
	extern short lang;

	printf("\nfirst          Release %s\n",ver);
	printf("---------------------------\n");
	printf("    ~© (1991-2024) GNU/GPL2\n");
	printf("    by G. B. Alias PiErre60\n\n");
	if(lang==ENGLISH) {
		printf("To use: first -h  Quick help,\n");
		printf("     or first --help  Detailed help.\n\n");
		return;
	}
	if(lang==ITALIANO) {
		printf("Usare: first -h  Aiuto rapido,\n");
		printf("     o first --help  Aiuto dettagliato.\n\n");
		return;
	}
	if(lang==ESPANOL) {
	  printf("Uso: first -h Ayuda rápida,\n");
	  printf("   o first --help Ayuda detallada.\n\n");
	  return;
	}
	if(lang==FRANCAIS) {
	  printf("Utilisation : first -h Aide rapide,\n");
	  printf("           ou first --help Aide détaillée.\n\n");
	  return;
	}
	if(lang==PORTUGUES) {
	  printf("Use: first -h Ajuda rápida,\n");
	  printf("  ou first --help Ajuda detalhada.\n\n");
	  return;
	}
	else {
	  if(lang==DEUTCHE) {
	    printf("Benutzen: first -h Schnelle Hilfe,\n");
	    printf("     oder first --help Detaillierte Hilfe.\n\n");
	    return;
	  }
	}
}

/* END */
