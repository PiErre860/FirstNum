/* first      Release 1.04-20260416
   --------------------------------
   ~© (1991-2026) //  GNU/GPL ver.2
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
   Minor Revision        13-12-2024
   Last Update & Rev.    16-04-2026
   Public release        18-04-2026
   --------------------------------
   Genuine Compiling with:
   Lattice®-SAS C Release 5.05
   for MC680x0 on AMIGA® Computers
   --------------------------------
   Recompiling for UNIX®/POSIX
   and GNU/Linux for X86 with:
   GNU/GCC Release >= 4.4.5
   Option compiling:
   -std=c99 First104.c -o first -lm
   --------------------------------
   FIRST PUBLIC RELEASE 1.03
   LAST PUBLIC RELEASE 1.04
   GNU/GENERAL PUBLIC LICENSE V.2
   --------------------------------
   LANGUAGE COMPILING = ENGLISH
   Row 98 -- ENGLISH / ITALIANO
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
#include <pwd.h>
#include <dirent.h>

/* Definizioni generali. */
#define NAME    "first"
#define VERSION "1.04-20260416"
#define CPYLEFT "~© (1991-2026)"
#define LANG    "FLANG="
#define ENDL    "_END"

#define KO   printf("---K.O.\n\n");
#define OK   printf("+++Ok.\n\n");
#define WARN   1
#define Ok     0

/* Definizioni limiti */
#define NMAX   255
#define HELP   425
#define NPR    0UL   /* Valore di ritorno per un numero primo. */
#define ZUDV   0UL   /* Convenzione per il numero zero. */
#define UNDV   1UL   /* Convenzione per il numero uno. */
#define MAX    20
#define RANGE  262144
#define LN_MAX 4294967296UL

/* Definizioni lingue locali */
#define EN 1   /* Lingua inglese, sigla. */
#define IT 2   /* Lingua italiana, sigla. */
#define ES 3   /* Lingua spagnola, sigla. */
#define FR 4   /* Lingua francese, sigla. */
#define PT 5   /* Lingua portoghese, sigla. */
#define DE 6   /* Lingua tedesca, sigla. */

#define ENGLISH   1   /* Info in inglese. */
#define ITALIANO  2   /* Info in italiano. */
#define ESPANOL   3   /* Info in spagnolo. */
#define FRANCAIS  4   /* Info in francese. */
#define PORTUGUES 5   /* Info in portoghese. */
#define DEUTCHE   6   /* Info in tedesco. */


/* Dichiarazione di funzioni globali. */
unsigned long primenumber(unsigned long);
short cfglang(short *);
void show(unsigned long, unsigned long);
void about(char *,char *,char *);

/* Dichiarazione di vettori di caratteri. */
char nfile[NMAX];   /* Array contenente il 'percorso/nome_file' di configurazione lingua. */

/* Impostazione della lingua di default. */
/* Dichiarazione di variabile globale. */
static short lngdef=ENGLISH;

/* Dichiarazioni di variabili globali. */
static short lang;
short ncx=0,flg=0,bklng=0;
char *pnd,*pnf;
char *pmsl,*pesr;
char *home,*usr;
int args=1,lb=0,ls=0;
FILE *fp,*fp0;
DIR *dp;

/* Sezione principale: funzione main() */
int main(int argc,char **argv) {
  unsigned long primenumber(unsigned long);
  short cfglang(short *);
  void show(unsigned long, unsigned long);
  void about(char *,char *,char *);

  /* Dichiarazioni di variabili esterne. */
  extern short ncx,flg,bklng,lang,lngdef;
  extern char *pnd,*pnf;
  extern char *pmsl,*pesr;
  extern char *home,*usr;
  extern int args,lb,ls;

  /* Dichiarazioni di variabili locali */
  unsigned long numl=NPR,numh=NPR;
  char mark='\0',optn='\0',optz='\0';
  char h='\0',e='\0',l='\0',p='\0';
  char esr[5],msl[6],nd[16],lask[2],laskdef[24],lasklng[12];
  char *plask,*plaskdef;
  char *vers=VERSION,*name=NAME,*cpyleft=CPYLEFT;
  char *plaskln0,*plaskln1,*plaskln2,*plaskln3,*plaskln4;
  int help=0;
  short ce=0;

  /* Inizializzazione di variabili static ed esterne. */
  lang=lngdef;

  /* Inizializzazione puntatori. */
  plaskdef=laskdef;
  plaskln0=lasklng;
  plask=lask;
  pesr=esr;
  pmsl=msl;
  pnd=nd;
  pnf=nfile;

  /* Definizione della lingua pre-impostata per init-ask. */
  if(lngdef==ENGLISH) {
    plaskdef="ENGLISH (Default)";   /* Inglese - Inglese. */
    plaskln0="ITALIANO";            /* Inglese - Italiano. */
    plaskln1="ESPAÑOL";             /* Inglese - Spagnolo. */
    plaskln2="FRANÇAIS";            /* Inglese - Francese. */
    plaskln3="PORTUGÛES";           /* Inglese - Portoghese. */
    plaskln4="DEUTCHE";             /* Inglese - Tedesco. */
  }
  else if(lngdef==ITALIANO) {
    plaskdef="ITALIANO (Predefinita)";   /* Italiano - Italiano. */
    plaskln0="ENGLISH";                  /* Italiano - Inglese. */
    plaskln1="ESPAÑOL";                  /* Italiano - Spagnolo. */
    plaskln2="FRANÇAIS";                 /* Italiano - Francese. */
    plaskln3="PORTUGÛES";                /* Italiano - Portoghese. */
    plaskln4="DEUTCHE";                  /* Italiano - Tedesco. */
  }
  else if(lngdef==ESPANOL) {
    plaskdef="ESPAÑOL (Defecto)";   /* Spagnolo - Spagnolo. */
    plaskln0="ENGLISH";             /* Spagnolo - Inglese. */
    plaskln1="ITALIANO";            /* Spagnolo - Italiano. */
    plaskln2="FRANÇAIS";            /* Spagnolo - Francese. */
    plaskln3="PORTUGÛES";           /* Spagnolo - Portoghese. */
    plaskln4="DEUTCHE";             /* Spagnolo - Tedesco. */
  }
  else if(lngdef==FRANCAIS) {
    plaskdef="FRANÇAIS (Défaut)";   /* Francese - Francese. */
    plaskln0="ENGLISH";             /* Francese - Inglese. */
    plaskln1="ITALIANO";            /* Francese - Italiano. */
    plaskln2="ESPAÑOL";             /* Francese - Spagnolo. */
    plaskln3="PORTUGÛES";           /* Francese - Portoghese. */
    plaskln4="DEUTCHE";             /* Francese - Tedesco. */
  }
  else if(lngdef==PORTUGUES) {
    plaskdef="PORTUGÛES (Padrão)";   /* Portoghese - Portoghese. */
    plaskln0="ENGLISH";              /* Portoghese - Inglese. */
    plaskln1="ITALIANO";             /* Portoghese - Italiano. */
    plaskln2="ESPAÑOL";              /* Portoghese - Spagnolo. */
    plaskln3="FRANÇAIS";             /* Portoghese - Francese. */
    plaskln4="DEUTCHE";              /* Portoghese - Tedesco. */
  }
  else {
    if(lngdef==DEUTCHE) {
      plaskdef="DEUTCHE (Standard)";   /* Tedesco - Tedesco. */
      plaskln0="ENGLISH";              /* Tedesco - Inglese. */
      plaskln1="ITALIANO";             /* Tedesco - Italiano. */
      plaskln2="ESPAÑOL";              /* Tedesco - Spagnolo. */
      plaskln3="FRANÇAIS";             /* Tedesco - Francese. */
      plaskln4="PORTUGÛES";            /* Tedesco - Portoghese. */
    }
  }

  /* Inizializzazione degli identificatori del file di configurazione. */
  pmsl=LANG; pmsl=msl;
  pesr=ENDL; pesr=esr;

  /* Ottiene il nome dell'utente */
  ls=strlen(pmsl),lb=strlen(pesr);
  if((usr=getenv("USER"))==NULL) {

    /* Esegue se non viene trovato il nome dell'utente. */
    /* Non posso ottenere il nome dell'utente. */
    if(lang==ENGLISH)
      printf("Error: I can not open file [.fstlang.cfg].\n");
    else if(lang==ITALIANO)
      printf("Errore: Non posso aprire il file [.fstlang.cfg].\n");
    else if(lang==ESPANOL)
      printf("Error: No se puede abrir el archivo [.fstlang.cfg].\n");
    else if(lang==FRANCAIS)
      printf("Erreur : Impossible d'ouvrir le fichier [.fstlang.cfg].\n");
    else if(lang==PORTUGUES)
      printf("Erro: Não é possível abrir o arquivo [.fstlang.cfg].\n");
    else {
      if(lang==DEUTCHE)
        printf("Fehler: Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
    }
    return KO;
  }

  /* Ottiene il percorso della directory dell'utente. */
  struct passwd *pwd=getpwuid(getuid());
  if(pwd==NULL) {

    /* Esegue se non viene trovata la path della directory home. */
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
      printf("Erreur : Le chemin du répertoire n?existe pas.\n");
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
    return KO;
  }

  /* Percorso della directory dell'utente. */
  home=pwd->pw_dir;

  /* Apertura di [.fstlang.cfg] in lettura. */
  snprintf(pnf,sizeof(nfile),"%s/.fstlang.cfg",home);
  if((fp0=fopen(pnf,"r"))==NULL) {

    /* Init-Ask (1). */
    /* Viene eseguito se non esiste il file di configurazione. */
    if(lngdef==ENGLISH) {
      printf("\n Language:\n");
      printf("  1 = %s\n",plaskdef);   /* Inglese. */
      printf("  2 = %s\n",plaskln0);   /* Italiano. */
      printf("  3 = %s\n",plaskln1);   /* Spagnolo. */
      printf("  4 = %s\n",plaskln2);   /* Francese. */
      printf("  5 = %s\n",plaskln3);   /* Portoghese. */
      printf("  6 = %s\n",plaskln4);   /* Tedesco. */
      printf(" Choose? ");
    }
    else if(lngdef==ITALIANO) {
      printf("\n Lingua:\n");
      printf("  1 = %s\n",plaskln0);   /* Inglese. */
      printf("  2 = %s\n",plaskdef);   /* Italiano. */
      printf("  3 = %s\n",plaskln1);   /* Spagnolo. */
      printf("  4 = %s\n",plaskln2);   /* Francese. */
      printf("  5 = %s\n",plaskln3);   /* Portoghese. */
      printf("  6 = %s\n",plaskln4);   /* Tedesco. */
      printf(" Scegliere? ");
    }
    else if(lngdef==ESPANOL) {
      printf("\n Lengua:\n");
      printf("  1 = %s\n",plaskln0);   /* Inglese. */
      printf("  2 = %s\n",plaskln1);   /* Italiano. */
      printf("  3 = %s\n",plaskdef);   /* Spagnolo. */
      printf("  4 = %s\n",plaskln2);   /* Francese. */
      printf("  5 = %s\n",plaskln3);   /* Portoghese. */
      printf("  6 = %s\n",plaskln4);   /* Tedesco. */
      printf(" ¿Escoger? ");
    }
    else if(lngdef==FRANCAIS) {
      printf("\n Langue:\n");
      printf("  1 = %s\n",plaskln0);   /* Inglese. */
      printf("  2 = %s\n",plaskln1);   /* Italiano. */
      printf("  3 = %s\n",plaskln2);   /* Spagnolo. */
      printf("  4 = %s\n",plaskdef);   /* Francese. */
      printf("  5 = %s\n",plaskln3);   /* Portoghese. */
      printf("  6 = %s\n",plaskln4);   /* Tedesco. */
      printf(" Choisir ? ");
    }
    else if(lngdef==PORTUGUES) {
      printf("\n Lìngua:\n");
      printf("  1 = %s\n",plaskln0);   /* Inglese. */
      printf("  2 = %s\n",plaskln1);   /* Italiano. */
      printf("  3 = %s\n",plaskln2);   /* Spagnolo. */
      printf("  4 = %s\n",plaskln3);   /* Francese. */
      printf("  5 = %s\n",plaskdef);   /* Portoghese. */
      printf("  6 = %s\n",plaskln4);   /* Tedesco. */
      printf(" Escolher? ");
    }
    else {
      if(lngdef==DEUTCHE) {
        printf("\n Zunge:\n");
        printf("  1 = %s\n",plaskln0);   /* Inglese. */
        printf("  2 = %s\n",plaskln1);   /* Italiano. */
        printf("  3 = %s\n",plaskln2);   /* Spagnolo. */
        printf("  4 = %s\n",plaskln3);   /* Francese. */
        printf("  5 = %s\n",plaskln4);   /* Portoghese. */
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

    /* Se la lingua non esiste usa quella prestabilita. */
    if(!lang||lang>6)
      lang=lngdef;

    /* Esegue nel caso il file di configurazione sia assente o inaccessibile. */
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

    /* Apertura di .fstlang.cfg in scrittura. */
    snprintf(pnf,sizeof(nfile),"%s/.fstlang.cfg",home);
    if((fp=fopen(pnf,"w"))==NULL) {

      /* Esegue se il file di configurazione non si può aprire. */
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
        printf("Erreur : Impossible d'ouvrir le fichier [.fstlang.cfg].\n");
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

        /* Esegue nel caso in cui la lingua non sia stata salvata. */
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
          printf("Erreur : Fishier [.fstlang.cfg] non modifié !\n\n");
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
      return OK;
    return KO;
  }
  else {

    /* Lettura dello stato del flag per la selezione della lingua dal file .firstlang.cfg */
    pmsl=LANG,pesr=ENDL;
    pnd=fgets(pmsl,ls,fp0);
    if(pnd!=NULL) {

    /* Esegue se il file di configurazione non si può aprire. */
      if(lang==ENGLISH)
        printf("Error: I can not open file [.fstlang.cfg].\n");
      else if(lang==ITALIANO)
        printf("Errore: Non posso aprire il file [.fstlang.cfg].\n");
      else if(lang==ESPANOL)
        printf("Error: No se puede abrir el archivo [.fstlang.cfg].\n");
      else if(lang==FRANCAIS)
        printf("Erreur : Impossible d'ouvrir le fichier [.fstlang.cfg].\n");
      else if(lang==PORTUGUES)
        printf("Erro: Não é possível abrir o arquivo [.fstlang.cfg].\n");
      else {
        if(lang==DEUTCHE)
          printf("Fehler: Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
      }
      return KO;
    }
    fseek(fp0,-5L,SEEK_END);   /* Sposta l'offest di inizio file. */
    lang=fgetc(fp0);
    fclose(fp0);
    if(lang>6)
     lang=lngdef;
  }

  /* Esegue senza argomenti. */
  if(argc==1) {
    about(name,vers,cpyleft);
    return Ok;
  }

  /* Esegue con un argomento. */
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

    /* Opzione per l'aiuto compatto. */
    if((mark=='-')&&(optn=='h')) {
      if(optz!='\0') {

        /* Visualizza messaggio per opzione erata. */
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

        /* Visualizza l'aiuto compatto. */
        if(lang==ENGLISH) {
          printf("\n%s  Version %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
          printf("\rTo use: first --help  Display extended help,\n");
          printf("     or first [VALUE]  Report whether the number is prime,\n");
          printf("     or first [MINIMUM VALUE] [MAXIMUM VALUE]\n");
          printf("               Display a list of prime numbers.\n\n");
          return Ok;
        }
        else if(lang==ITALIANO) {
          printf("\n%s  Version %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
          printf("\rUsare: first --help  Visualizza l'aiuto esteso,\n");
          printf("     o first [VALORE]  Informa se il valore è un numero primo,\n");
          printf("     o first [VALORE MINIMO] [VALORE MASSIMO]\n");
          printf("              Visualizza una lista di numeri primi.\n\n");
          return Ok;
        }
        else if(lang==ESPANOL) {
          printf("\n%s  Version %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
          printf("\rUso: first --help  Muesta ayuda extendida, \n");
          printf("   o first [VALOR]  Informar si el número es primo,\n");
          printf("   o first [VALOR MINIMO] [VALOR MÁXIMO]\n");
          printf("            Muestra una lista de números primos.\n");
          return Ok;
        }
        else if(lang==FRANCAIS) {
          printf("\n%s  Version %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
          printf("\rUtilisation: first --help  Afficher l'aide éntendue,\n");
          printf("          ou first [VALEUR]  Indiquer si le nombre est premier,\n");
          printf("          ou first [VALEUR MINIMALE] [VALEUR MAXIMALE]\n");
          printf("                    Affiche une liste de nombres premiers.\n");
          return Ok;
        }
        else if(lang==PORTUGUES) {
          printf("\n%s  Version %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
          printf("\rUse: first --help  Exibe ajuda estendida,\n");
          printf("  ou first [VALOR]  Informa se o número é primo,\n");
          printf("  ou first [VALOR MINIMO] [VALOR MÁXIMO]\n");
          printf("            Exibe uma lista de números primos.\n");
          return Ok;
        }
        else {
          if(lang==DEUTCHE) {
            printf("\n%s  Version %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
            printf("\rVerwenden: first --help  Erweiterte Hilfe anzeigen,\n");
            printf("      oder first [WERT]  Melden Sie,ob die Zahl eine Primzahl ist,\n");
            printf("      oder first [MINIMALWERT] [MAXIMALWERT]\n");
            printf("                  Zeigt eine Liste von Primzahlen an.\n");
            return Ok;
          }
        }
      }
      return WARN;
    }

    /* Opzione per l'aiuto esteso. */
    else if((mark=='-')&&(optn=='-')) {
      h=(char)tolower((int)argv[1][2]);
      e=(char)tolower((int)argv[1][3]);
      l=(char)tolower((int)argv[1][4]);
      p=(char)tolower((int)argv[1][5]);
      help=(int)(h+e+l+p);
      if(help==HELP) {

        /* Visualizza l'aiuto esteso. */
        if(lang==ENGLISH) {
          printf("\n%s  Version %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
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
          printf("type: first 12345\n");
          printf("      first 1 65536\n");
          printf("      first 111000 123999\n");
          printf("      first 100001 165536 > $HOME/list_of_prime\n");
          printf("      first 10000  75535 >> $HOME/list_of_prime\n");
          printf("      first 123450000 123459999 | less\n\n");
          return Ok;
        }
        else if(lang==ITALIANO) {
          printf("\n%s  Versione %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
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
          printf("          first 1 65536\n");
          printf("          first 111000 123999\n");
          printf("          first 100001 165536 > $HOME/lista_di_primi\n");
          printf("          first 10000  75535 >> $HOME/lista_di_primi\n");
          printf("          first 123450000 123459999 | less\n\n");
          return Ok;
        }
        else if(lang==ESPANOL) {
          printf("\n%s  Versión %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
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
          printf("      first 1 65536\n");
          printf("      first 111000 123999\n");
          printf("      first 100001 165536 > $HOME/lista_de_primos\n");
          printf("      first 10000  75535 >> $HOME/lista_de_primos\n");
          printf("      first 123450000 123459999 | less\n\n");
          return Ok;
        }
        else if(lang==FRANCAIS) {
          printf("\n%s  Version %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
          printf("Utiliser : first [OPTION] [VALEUR [VALEUR]]  Modèle de syntaxe d'utilisation.\n");
          printf("           first  Informations et aide.\n");
          printf("           first -h  Aide rapide.\n");
          printf("           first --help  Cette aide.\n");
          printf("           first [VALEUR]  Indique si la valeur est un nombre premier.\n");
          printf("           first [VALEUR] [VALEUR]  Liste des nombres premiers.\n\n");
          printf("Largeur de la série : valeur maximale - valeur minimale + 1 <= 65535\n");
          printf("Affichage du terminal texte standard: 80 colonnes, 24 lignes recommandées.\n");
          printf("Pour rediriger la sortie vers un fichier, utilisez > ou >>\n");
          printf("Exemples : first [VALEUR MIN] [VALEUR MAX] > nom_ficher  Enregistrer dans le ficher.\n");
          printf("        ou first [VALEUR MIN] [VALEUR MAX] > nom_ficher  Ajouter ou ficher.\n\n");
          printf("Taper : first 12345\n");
          printf("        first 1 65536\n");
          printf("        first 111000 123999\n");
          printf("        first 100001 165536 > $HOME/liste_des_premiers\n");
          printf("        first 10000  75535 >> $HOME/liste_des_premiers\n");
          printf("        first 123450000 123459999 | less\n\n");
          return Ok;
        }
        else if(lang==PORTUGUES) {
          printf("\n%s  Versão %s\n",name,vers);
          printf("(%s GNU/GPL2)\n\n",cpyleft);
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
          printf("      first 1 65536\n");
          printf("      first 111000 123999\n");
          printf("      first 100001 165536 > $HOME/lista_de_primos\n");
          printf("      first 10000  75535 >> $HOME/lista_de_primos\n");
          printf("      first 123450000 123459999 | less\n\n");
          return Ok;
        }
        else {
          if(lang==DEUTCHE) {
            printf("\n%s  Version %s\n",name,vers);
            printf("(%s GNU/GPL2)\n\n",cpyleft);
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
            printf("     first 1 65536\n");
            printf("     first 111000 123999\n");
            printf("     first 100001 165536 > $HOME/Liste_der_Primzahlen\n");
            printf("     first 10000  75535 >> $HOME/Liste_der_Primzahlen\n");
            printf("     first 123450000 123459999 | less\n\n");
            return Ok;
          }
        }
        return WARN;
      }

      /* Esegue se l'opzione è errata. */
      else {
        if(lang==ENGLISH)
          return(printf("Error: Bad or missing option.\n\n"));
        else if(lang==ITALIANO)
          return(printf("Errore: Opzione errata o mancante.\n\n"));
        else if(lang==ESPANOL)
          return(printf("Error: Opción incorrecta o faltante.\n\n"));
        else if(lang==FRANCAIS)
          return(printf("Erreur : Option incorrecte ou manquante.\n\n"));
        else if(lang==PORTUGUES)
          return(printf("Erro: Opção incorreta ou ausente.\n\n"));
        else {
          if(lang==DEUTCHE)
            return(printf("Fehler: Falsche oder fehlende Option.\n\n"));
        }
      }
    }

    /* Esegue se l'argomento è assente o errato. */
    else if(!isdigit(**(argv+1))) {
      if(lang==ENGLISH)
        return(printf("Error: Wrong and/or missing argument!\n\n"));
      else if(lang==ITALIANO)
        return(printf("Errore: Argomento errato e/o mancante.\n\n"));
      else if(lang==ESPANOL)
        return(printf("Error: ¡Argumento incorrecto o faltante!\n\n"));
      else if(lang==FRANCAIS)
        return(printf("Erreur : Argument incorrect et/ou manquant !\n\n"));
      else if(lang==PORTUGUES)
        return(printf("Erro: Argumento incorreto e/ou ausente!\n\n"));
      else {
        if(lang==DEUTCHE)
          return(printf("Fehler: Falsches und/oder fehlendes Argument!\n\n"));
      }
    }
  }

  /* Esegue con due argomenti. */
  if(argc==3) {
    if(!flg) flg=1;
    if(isdigit(**(argv+1))&&isdigit(**(argv+2))) {
      numl=(unsigned long)atof(*(argv+1));
      numh=(unsigned long)atof(*(argv+2));
    }

    /* Esegue se un argomento è errato. */
    else {
      if(lang==ENGLISH)
        return(printf("Error: Bad arguments!\n\n"));
      else if(lang==ITALIANO)
        return(printf("Errore: Argomento errato!\n\n"));
      else if(lang==ESPANOL)
        return(printf("Error: ¡Tema incorrecto!\n\n"));
      else if(lang==FRANCAIS)
        return(printf("Erreur : Suject incorrect !\n\n"));
      else if(lang==PORTUGUES)
        return(printf("Erro: Tópico incorreto!\n\n"));
      else {
        if(lang==DEUTCHE)
          return(printf("Fehler: Falsches Thema!\n\n"));
      }
    }
  }

  /* Esegue con più di due argomenti. */
  if(argc>3) {
    if(lang==ENGLISH)
      return(printf("Error: Too many arguments!\n\n"));
    else if(lang==ITALIANO)
      return(printf("Errore: Troppi argomenti!\n\n"));
    else if(lang==ESPANOL)
      return(printf("Error: ¡Demasiados temas!\n\n"));
    else if(lang==FRANCAIS)
      return(printf("Erreur : Trop de suject !\n\n"));
    else if(lang==PORTUGUES)
      return(printf("Erro: Muitos tópicos!\n\n"));
    else {
      if(lang==DEUTCHE)
        return(printf("Fehler: Zu viele Themen!\n\n"));
    }
  }

  /* Controllo dei valori numerici in ingresso. */
  if(numl>LN_MAX||numh>LN_MAX) {
    if(lang==ENGLISH)
      return(printf("Error: Values out of range!\n\n"));
    else if(lang==ITALIANO)
      return(printf("Errore: Valori fuori limite!\n\n"));
    else if(lang==ESPANOL)
      return(printf("Error: Valores fuera de limite!\n\n"));
    else if(lang==FRANCAIS)
      return(printf("Erreur : valeurs hors limites !\n\n"));
    else if(lang==PORTUGUES)
      return(printf("Erro: Valores fora do limite!\n\n"));
    else {
      if(lang==DEUTCHE)
        return(printf("Fehler: Werte außerhalb des Grenzwerts!\n\n"));
    }
  }

  /* Controllo disposizione argomenti in ingresso. */
  if(numh<numl) {
    if(lang==ENGLISH)
      return(printf("Error: Arguments or values has been inverted.\n\n"));
    else if(lang==ITALIANO)
      return(printf("Errore: Argomenti o valori invertiti.\n\n"));
    else if(lang==ESPANOL)
      return(printf("Error: Argumentos o valores invertidos.\n\n"));
    else if(lang==FRANCAIS)
      return(printf("Erreur : Arguments ou valeurs inversés.\n\n"));
    else if(lang==PORTUGUES)
      return(printf("Erro: Argumentos ou valores invertidos.\n\n"));
    else {
      if(lang==DEUTCHE)
        return(printf("Fehler: Argumente oder Werte vertauscht.\n\n"));
    }
  }

  /* Controllo conformità e limiti argomenti in ingresso. */
  if((numh-numl+1)>RANGE) {
    if(lang==ENGLISH) {
      printf("Error: Range too large (v.max - v.min + 1 > 65536 values).\n");
      return(printf(" v.max = Highest value in the series.\n"
       " v.min = Lowest value in the series.\n\n"));
    }
    else if(lang==ITALIANO) {
      printf("Errore: Serie troppo ampia (v.max - v.min + 1 > 65536 valori).\n");
      return(printf(" v.max = Valore più alto della serie.\n"
       " v.min = Valore più basso della serie.\n\n"));
    }
    else if(lang==ESPANOL) {
      printf("Error: Serie es demasiado grande (v.max - v.min + 1 > 65536 valores).\n");
      return(printf(" v.max = Valor más alto de la serie.\n"
       " v.min = Valor más bajo de la serie.\n\n"));
    }
    else if(lang==FRANCAIS) {
      printf("Erreur : Série trop grande (v.max - v.min + 1 > 65536 valeurs).\n");
      return(printf(" v.max = Valeur la plus elevée de la série.\n"
       " v.min = Valeur la plus basse de la série.\n\n"));
    }
    else if(lang==PORTUGUES) {
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

  /* --------------------------------------------------------------------- */
  /* Trova la posizione per incolonnamento in funzione del valore massimo. */
  if(numh>0&&numh<10) ncx=1;
  else if(numh<100) ncx=2;
  else if(numh<1000) ncx=3;
  else if(numh<10000) ncx=4;
  else if(numh<100000) ncx=5;
  else if(numh<1000000) ncx=6;
  else if(numh<10000000) ncx=7;
  else if(numh<100000000) ncx=8;
  else if(numh<1000000000) ncx=9;
  else {
    if(numh<=10000000000) ncx=10;
  }
  args=argc;
  show(numl,numh);   /* Chiama la funzione che stampa i numeri primi. */
  return(putchar('\n'));
  /* ---------------------------------------------------------------- */
}

/* -------------------------------------------- */
/* Funzione primenumber(), trova i numeri primi */
unsigned long primenumber(unsigned long number) {

/* ------------------------------------------------------------------ */
/* L'algoritmo di questa funzione è sottoposto al CopyLeft ~© 1991-2024,
   ed alla GNU Public License version 2 e 3 di Free Software Foundation.
   Rif. http://www.gnu.org/copyleft
        http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
        http://www.gnu.org/licenses/gpl-3.0.html

   Creato da G. B. alias PiErre60 (Italy)
   [prime=primenum(number) ~© 1990-1991],
   e successive modifiche ~© 1997-2001-2010-2026.  */
/* ------------------------------------------------------------------ */

  /* Dichiarazione di variabili locali */
  unsigned long ndivf=2UL,divsf=0UL;

  if(number==0) {
    divsf=0;
    return ZUDV;   /* Lo zero per convenzione è considerato pari, non classificabile¹. */
  }
  if(number==1) {
    divsf=0;
    return UNDV;    /* Il numero uno viene considerato non classificabile, non primo³. */
  }
  if(number==2)
    return NPR;    /* Il due è considerato numero primo². */
  while((ndivf*ndivf)<=number) {        /* Ricerca del fattore primo di scomposizione del - */
    if(ndivf>3) ++ndivf;                /* numero. Se il numero è divisibile, nella - */
    if(!(number%ndivf))                 /* variabile "divsf" è presente un fattore primo - */
      divsf=ndivf,ndivf=number/ndivf;   /* valido per il quale esso risulta divisibile. */
    ndivf++;
  }
  if(!divsf)
    return NPR;     /* Il numero è primo, se uno qui non viene considerato³. */
  else
    return divsf;   /* Il numero è divisibile: il fattore primo risultante è divsf stesso. */
}

/* ¹ Per convenzione il fattore minimo di scomposizione di zero è considerato pari ad uno. */
/* ² Il due è ovviamente primo poichè è divisibile solo per se stesso e per l'unità. */
/* ³ Il numero uno è indefinito e per convenzione non è considerato primo, poiché - */
/*   è divisibile solo per sè stesso. Qui per praticità viene considerato come lo zero. */

/* ------------------------------------------- */
/* Funzione show(), visualizza i numeri primi. */
void show(unsigned long numb, unsigned long numt) {

  /* Dichiarazioni di funzioni. */
  unsigned long primenumber(unsigned long);

  /* Dichiarazioni di variabili esterne. */
  extern int args;
  extern short lang;
  extern short ncx,flg;

  /* Dichiarazioni di variabili locali. */
  unsigned long nums;
  unsigned int count=0,pcount=0,scount=0;
  short clp=0,ncl=10;
  nums=primenumber(numb);
  if(numb==ZUDV&&!flg) {
    if(lang==ENGLISH) {
      printf("Zero is conventionally considered unclassifiable.\n");
      printf("It is neither a divisible number nor a prime number.\n");
    }
    else if(lang==ITALIANO) {
      printf("Lo zero per convenzione è considerato non classificabile.\n");
      printf("Non è né un numero divisibile né un numero primo.\n");
    }
    else if(lang==ESPANOL) {
      printf("El cero por convención se considera inclasificable.\n");
      printf("No es ni un número divisible ni un número primo.\n");
    }
    else if(lang==FRANCAIS) {
      printf("Zéro par convention est considéré comme inclassable.\n");
      printf("Ce n'est ni un nombre divisible ni un nombre premier.\n");
    }
    else if(lang==PORTUGUES) {
      printf("Zero por convenção é considerado inclassificável.\n");
      printf("Não é um número divisivel nem um número primo.\n");
    }
    else {
      if(lang==DEUTCHE) {
        printf("Null gilt per Konvention als nicht klassifizierbar.\n");
        printf("Es handelt sich weder um eine teilbare Zahl noch um eine Primzahl.\n");
      }
    }
    return;
  }
  else if(numb==UNDV&&!flg) {
    if(lang==ENGLISH) {
      printf("The number one is considered unclassifiable.\n");
      printf("Not a prime number.\n");
    }
    else if(lang==ITALIANO) {
      printf("Il numero uno viene considerato non classificabile.\n");
      printf("Non è un numero primo.\n");
    }
    else if(lang==ESPANOL) {
      printf("El número uno se considera inclasificable.\n");
      printf("No es un número primo.\n");
    }
    else if(lang==FRANCAIS) {
      printf("Le nombre un est considéré comme inclassable.\n");
      printf("Ce n'est pas un nombre premier.\n");
    }
    else if(lang==PORTUGUES) {
      printf("O número um é considerato inclassificavel.\n");
      printf("Não é um número primo.\n");
    }
    else {
      if(lang==DEUTCHE) {
        printf("Die Zahl Eins gilt als nicht klassifizierbar.\n");
        printf("Sie ist keine Primzahl.\n");
      }
    }
    return;
  }
  else if(nums==NPR&&!flg) {
    if(lang==ENGLISH)
      printf(" %ld it is a prime number.\n",numb);
    else if(lang==ITALIANO)
      printf(" %ld è un numero primo.\n",numb);
    else if(lang==ESPANOL)
      printf(" %ld es un número primo.\n",numb);
    else if(lang==FRANCAIS)
      printf(" %ld est un nombre premier.\n",numb);
    else if(lang==PORTUGUES)
      printf(" %ld é um número primo.\n",numb);
    else {
      if(lang==DEUTCHE)
        printf(" %ld ist eine Primzahl.\n",numb);
    }
    return;
  }
  else if(nums&&!flg) {
    if(lang==ENGLISH)
      printf(" %ld is divisible by %ld.\n",numb,nums);
    else if(lang==ITALIANO)
      printf(" %ld è divisibile per %ld.\n",numb,nums);
    else if(lang==ESPANOL)
      printf(" %ld es divisible por %ld.\n",numb,nums);
    else if(lang==FRANCAIS)
      printf(" %ld est divisible par %ld.\n",numb,nums);
    else if(lang==PORTUGUES)
      printf(" %ld é divisível por %ld.\n",numb,nums);
    else {
      if(lang==DEUTCHE)
        printf(" %ld ist durch %ld teilbar.\n",numb,nums);
    }
    return;
  }
  else {
    if(args==3) {
      if(lang==ENGLISH)
        printf("\nSeries from number: %lu to number: %lu\n\n",numb,numt);
      else if(lang==ITALIANO)
        printf("\nSerie dal numero: %lu al numero: %lu\n\n",numb,numt);
      else if(lang==ESPANOL)
        printf("\nSerie del número: %lu al número: %lu\n\n",numb,numt);
      else if(lang==FRANCAIS)
        printf("\nSerie allant du numéro : %lu au numéro : %lu\n\n",numb,numt);
      else if(lang==PORTUGUES)
        printf("\nSerie do número: %lu ao número: %lu\n\n",numb,numt);
      else {
        if(lang==DEUTCHE)
          printf("\nSerien von Nummer: %lu bis Nummer: %lu\n\n",numb,numt);
      }
    }
    nums=numb;
    if(nums==0) nums=1;
    while(nums<=numt) {
      if(numt<10) ncl=19;
      if(numt>=10&&numt<100) ncl=19;
      if(numt>=100&&numt<1000) ncl=16;
      if(numt>=1000&&numt<10000) ncl=14;
      if(numt>=10000&&numt<100000) ncl=12;
      if(numt>=100000&&numt<1000000) ncl=11;
      if(numt>=1000000&&numt<10000000) ncl=10;
      if(numt>=10000000&&numt<100000000) ncl=9;
      if(numt>=100000000&&numt<1000000000) ncl=8;
      if(numt>=1000000000) ncl=7;
      if(!(primenumber(nums))) {
        if(clp==ncl) {
          clp=0;
          printf("\n");
        }
        if(clp) {
          if(numt>=1000000000) printf("    ");
          else printf("   ");
        }
        else
          printf(" ");
        if(ncx==1) printf("%1lu",nums);
        else if(ncx==2) printf("%2lu",nums);
        else if(ncx==3) printf("%3lu",nums);
        else if(ncx==4) printf("%4lu",nums);
        else if(ncx==5) printf("%5lu",nums);
        else if(ncx==6) printf("%6lu",nums);
        else if(ncx==7) printf("%7lu",nums);
        else if(ncx==8) printf("%8lu",nums);
        else if(ncx==9) printf("%9lu",nums);
        else {
          if(ncx==10) printf("%10lu",nums);
        }
        pcount++,clp++;
      }
      nums++,count++;
    }
    if(numb<=numt) {
      if(!pcount||(numb==0&&numt==1)) {
        if(lang==ENGLISH)
          printf("The given series does not contain any prime numbers.");
        else if(lang==ITALIANO)
          printf("La serie indicata non contiene numeri primi.");
        else if(lang==ESPANOL)
          printf("La serie dada no contiene nigún número primo.");
        else if(lang==FRANCAIS)
          printf("La série donnée ne contient aucun nombre premier.");
        else if(lang==PORTUGUES)
          printf("A série apresentada näo contém nenhum número primo.");
        else {
          if(lang==DEUTCHE)
            printf("Die gegebene Zahlenreihe enthält keine Primzahlen.");
        }
      }
    }
    if(numb<=numt) {
      if(lang==ENGLISH) {
        if(pcount==1)
          printf("\n\n-----------------------");
        else
          printf("\n\n-------------------------");
        scount=pcount;
      }
      else if(lang==ITALIANO) {
        if(pcount==1)
          printf("\n\n-------------------------");
        else
          printf("\n\n----------------------------");
        scount=pcount;
      }
      else if(lang==ESPANOL) {
        if(count==1&&pcount!=0)
          printf("\n\n------------------");
        else
          printf("\n\n--------------------");
        scount=count;
      }
      else if(lang==FRANCAIS) {
        if(pcount==1)
          printf("\n\n--------------------------");
        else
          printf("\n\n----------------------------");
        scount=pcount;
      }
      else if(lang==PORTUGUES) {
        if(pcount==1)
          printf("\n\n---------------------");
        else
          printf("\n\n------------------------");
        scount=pcount;
      }
      else {
        if(lang==DEUTCHE) {
          if(count==1)
            printf("\n\n--------------------");
          else
            printf("\n\n---------------------");
          scount=count;
        }
      }
      if(scount<10)
        printf("-");
      else if(scount>=10&&scount<100)
        printf("--");
      else if(scount>=100&&scount<1000)
        printf("---");
      else if(scount>=1000&&scount<10000)
        printf("----");
      else if(scount>=10000&&scount<100000)
        printf("-----");
      else {
        if(scount>=100000)
          printf("------");
      }
      if(lang==ENGLISH) {
        if(count==1)
          printf("\n%u number processed.",count);
        else
          printf("\n%u numbers processed.",count);
        if(pcount==1)
          printf("\nThere is %u prime number.\n",pcount);
        else
          printf("\nThere are %u prime numbers.\n",pcount);
      }
      else if(lang==ITALIANO) {
        if(count==1)
          printf("\nElaborato %u numero.",count);
        else
          printf("\nElaborati %u numeri.",count);
        if(pcount==1)
          printf("\nÈ presente %u numero primo.\n",pcount);
        else
          printf("\nSono presenti %u numeri primi.\n",pcount);
      }
      else if(lang==ESPANOL) {
        if(count==1)
          printf("\n%u número procesado.",count);
        else
          printf("\n%u números procesados.",count);
        if(pcount==1)
          printf("\nHay %u número primo.\n",pcount);
        else
          printf("\nHay %u números primos.\n",pcount);
      }
      else if(lang==FRANCAIS) {
        if(count==1)
          printf("\n%u nombre traité.",count);
        else
          printf("\n%u nombres traités.",count);
        if(pcount==1)
          printf("\nIl existe %u nombre premier.\n",pcount);
        else
          printf("\nIl existe %u nombres premiers.\n",pcount);
      }
      else if(lang==PORTUGUES) {
        if(count==1)
          printf("\n%u número processado.",count);
        else
          printf("\n%u números processados.",count);
        if(pcount==1)
          printf("\nExiste %u número primo.\n",pcount);
        else
          printf("\nExistem %u números primos.\n",pcount);
      }
      else {
        if(lang==DEUTCHE) {
          if(count==1)
            printf("\n%u Nummer verarbeitet.",count);
          else
            printf("\n%u Nummern verarbeitet.",count);
          if(pcount==1)
            printf("\nEs gibt %u Primzahl.\n",pcount);
          else
            printf("\nEs gibt %u Primzahlen.\n",pcount);
        }
      }
      if(lang==ENGLISH) {
        if(pcount==1)
          printf("-----------------------");
        else
          printf("-------------------------");
        scount=pcount;
      }
      else if(lang==ITALIANO) {
        if(pcount==1)
          printf("-------------------------");
        else
          printf("----------------------------");
        scount=pcount;
      }
      else if(lang==ESPANOL) {
        if(count==1&&pcount!=0)
          printf("------------------");
        else
          printf("--------------------");
        scount=count;
      }
      else if(lang==FRANCAIS) {
        if(pcount==1)
          printf("--------------------------");
        else
          printf("----------------------------");
        scount=pcount;
      }
      else if(lang==PORTUGUES) {
        if(pcount==1)
          printf("---------------------");
        else
          printf("------------------------");
        scount=pcount;
      }
      else {
        if(lang==DEUTCHE) {
          if(count==1)
            printf("--------------------");
          else
            printf("---------------------");
          scount=count;
        }
      }
      if(scount<10)
        printf("-\n");
      else if(scount>=10&&scount<100)
        printf("--\n");
      else if(scount>=100&&scount<1000)
        printf("---\n");
      else if(scount>=1000&&scount<10000)
        printf("----\n");
      else if(scount>=10000&&scount<100000)
        printf("-----");
      else {
        if(scount>=10000)
          printf("------\n");
      }
    }
    putchar('\n');
    return;
  }
}

/* --------------------------------------------------------------------- */
/* Funzione per la riscrittura del file di configurazione per la lingua. */
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
  /* Ottiene il nome dell'utente. */
  ls=strlen(pmsl),lb=strlen(pesr);
  if((usr=getenv("USER"))==NULL) {

    /* Esegue se non viene trovato il nome dell'utente. */
    /* Non posso ottenere il nome dell'utente. */
    if(lang==ENGLISH)
      printf("Error: I can not open file [.fstlang.cfg].\n");
    else if(lang==ITALIANO)
      printf("Errore: Non posso aprire il file [.fstlang.cfg].\n");
    else if(lang==ESPANOL)
      printf("Error: No se puede abrir el archivo [.fstlang.cfg].\n");
    else if(lang==FRANCAIS)
      printf("Erreur : Impossible d'ouvrir le fichier [.fstlang.cfg].\n");
    else if(lang==PORTUGUES)
      printf("Erro: Não é possível abrir o arquivo [.fstlang.cfg].\n");
    else {
      if(lang==DEUTCHE)
        printf("Fehler: Datei [.fstlang.cfg] kann nicht geöffnet werden.\n");
    }
    return KO;
  }

  /* Ottiene il percorso della directory dell'utente. */
  struct passwd *pwd=getpwuid(getuid());
  if(pwd==NULL) {

    /* Esegue se non viene trovata la path della directory home. */
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
      printf("Erreur : Le chemin du répertoire n?existe pas.\n");
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
    return KO;
  }

  /* Percorso della directory dell'utente. */
  home=pwd->pw_dir;

  /* Apertura di .firstlang.cfg in scrittura. */
  snprintf(pnf,sizeof(nfile),"%s/.fstlang.cfg",home);
  if((fp=fopen(pnf,"w"))==NULL) {

    /* Esegue se il file di configurazione non si può aprire. */
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
      printf("Erreur : Impossible d'ouvrir le fichier [.fstlang.cfg].\n");
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
    return KO;
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

      /* Esegue nel caso in cui il file non sia salvato. */
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
      return KO;
    }

    /* Se non ci sono errori. */
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
      return OK;
    }
    return KO;
  }
}

/* -------------------------------------------------------- */
/* Funzione about(), visualizza informazioni sul programma. */
void about(char *nam,char *ver,char *cpylt) {

  /* Dichiarazione di variabile esterna. */
  extern short lang;

  if(lang==ENGLISH) {
    printf("\n%s    Version %s\n",nam,ver);
    printf("------------------------------\n");
    printf("       %s GNU/GPL2\n",cpylt);
    printf("       by G. B. Alias PiErre60\n\n");
    printf("To use: first -h  Quick help,\n");
    printf("     or first --help  Detailed help.\n");
    printf("     o first [NUMBER [NUMBER]]\n\n");
    return;
  }
  else if(lang==ITALIANO) {
    printf("\n%s   Versione %s\n",nam,ver);
    printf("------------------------------\n");
    printf("       %s GNU/GPL2\n",cpylt);
    printf("       by G. B. Alias PiErre60\n\n");
    printf("Usare: first -h  Aiuto rapido,\n");
    printf("     o first --help  Aiuto dettagliato.\n");
    printf("     o first [NUMERO [NUMERO]]\n\n");
    return;
  }
  else if(lang==ESPANOL) {
    printf("\n%s    Versión %s\n",nam,ver);
    printf("------------------------------\n");
    printf("       %s GNU/GPL2\n",cpylt);
    printf("       by G. B. Alias PiErre60\n\n");
    printf("Uso: first -h Ayuda rápida,\n");
    printf("   o first --help Ayuda detallada.\n");
    printf("   o first [NÚMERO [NÚMERO]]\n\n");
    return;
  }
  else if(lang==FRANCAIS) {
    printf("\n%s    Version %s\n",nam,ver);
    printf("------------------------------\n");
    printf("       %s GNU/GPL2\n",cpylt);
    printf("       by G. B. Alias PiErre60\n\n");
    printf("Utilisation : first -h Aide rapide,\n");
    printf("           ou first --help Aide détaillée.\n");
    printf("           ou first [NOMBRE [NOMBRE]]\n\n");
    return;
  }
  else if(lang==PORTUGUES) {
    printf("\n%s     Versão %s\n",nam,ver);
    printf("------------------------------\n");
    printf("       %s GNU/GPL2\n",cpylt);
    printf("       by G. B. Alias PiErre60\n\n");
    printf("Use: first -h Ajuda rápida,\n");
    printf("  ou first --help Ajuda detalhada.\n");
    printf("  ou first [NÚMERO [NÚMERO]]\n\n");
    return;
  }
  else {
    if(lang==DEUTCHE) {
      printf("\n%s    Version %s\n",nam,ver);
      printf("------------------------------\n");
      printf("       %s GNU/GPL2\n",cpylt);
      printf("       by G. B. Alias PiErre60\n\n");
      printf("Benutzen: first -h Schnelle Hilfe,\n");
      printf("     oder first --help Detaillierte Hilfe.\n\n");
      printf("     oder first [NUMMER [NUMMER]]\n\n");
      return;
    }
  }
}

/* END. */
