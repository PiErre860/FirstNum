/* firstnum          Release 1.08b-20250327
   ----------------------------------------
   ~© (2010-2025) F.S.F. GNU/GPL Vers.3
   (Software adatto solo per uso didattico)
   Ideato e scritto in linguaggio ANSI-C99
   da: G. B. alias PiErre60  (Italy)
   con la collaborazione di:
   A.F.F. alias Ferro811 (Italy)
   ----------------------------------------
   Storia:
   Creazione (versioni 0.1>>0.9) 18-12-1990
   Prima Release 1.0             23-12-1990
   Primo Update                  04-01-1991
   Release 1.1                   08-04-1991
   Secondo Update                14-05-1991
   Release 1.2                   16-08-1991
   Terzo Update                  18-02-1992
   Release 1.2.1                 30-03-1992
   Quarto Update                 26-12-1992
   Release 1.3                   02-01-1993
   Debug ed Update               26-02-1993
   Release 1.3a                  07-05-1996
   Debug ed Update minori        05-08-1997
   Release 1.3b                  25-11-1998
   Debug ed Update minori        13-12-2000
   Release 1.3c                  11-12-2000
   Ultima Release Amiga          14-12-2000
   Primo Porting GNU/Linux       13-08-2010
   Primo Update (Release 1.04)   21-08-2010
   Secondo Update (Release 1.05) 03-02-2019
   Terzo Update (Release 1.05a)  29-08-2020
   Release 1.05a (beta)          12-09-2020
   Release 1.07a (beta)          18-12-2020
   Release 1.07b (beta)          19-03-2024
   Release 1.08a (stabile)       27-12-2024
   ----------------------------------------
   Release pubblica GNU-CC       30-03-2025
   ----------------------------------------
   Compilato in origine con:
   Lattice®-SAS® C MC680x0  Vers. 5.05
   per i computers Commodore-AMIGA®
   ----------------------------------------
   Portato e ricompilato in C std.99 per
   UNIX®/POSIX SYS V e GNU/Linux®
   con GNU-CC (C Compiler) Vers. >= 4.4.5
   Opzioni compilazione:
   -std=c99 Firstnum108a.c -o firstnum -lm
   (per la versione finale corrente).
   ----------------------------------------
   Prima Release (stabile) AMIGA:     1.3c
   Ultima Release (stabile) AMIGA:    1.3c
   Prima Release (porting) GNU/GCC:   1.3d
   Prima Release (stabile) GNU-GCC:   1.04
   Ultima Release (stabile) GNU-GCC:  1.08a
   ----------------------------------------

   NOME UFFICIALE DEL PROGRAMMA DEFINITO
   ALLA RIGA 130 = "firstnum"

   VERSIONE DEL CODICE ATTUALE E DEL
   RILASCIO ALLA RIGA 132 = "1.08b"
   ED ALLA RIGA 134 = "108b-20250327"

   LINGUAGGIO PRE-IMPOSTATO = ENGLISH
   ALLA RIGA: 282 = [ENGLISH/ITALIANO/ESPANOL/FRANCAIS/PORTUGUES/DEUTCHE]
   ALLE RIGHE: 288 -> 293 = [FLAG IMPLEMEMTAZIONE PARZIALE DI UNA LINGUA] */

/* =======================================================================
    Questo programma permette di scomporre i numeri naturali nei loro fat-
   tori primi. Ricerca i numeri primi e permette di rilevare alcune carat-
   teristiche  della loro  distribuzione.  Il programma è strutturato  per
   essere eseguito da una Shell e si presenta in modo simile ad un comando
   di sistema. Dispone di molte opzioni che ne differenziano sia la visua-
   lizzazione sia il modo operativo. E' possibile definire liste di numeri
   da scomporre o ricercarvi in esse i numeri primi.  Ogni lista può avere
   un'ampiezza massima di 65535 elementi, mentre il valore massimo scompo-
   nibile di cui viene fornito un risultato corretto è 4294967295.
   Il programma viene fornito «così com'è» senza nessuna forma di garanzia
   esplicita o implicita. L'autore declina ogni responsabilità per eventu-
   ali danni derivanti da un uso improprio, fuori da un contesto puramente
   didattico/educativo e divulgativo.
   ======================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>


/* -------------------- */
/* Definizioni interne. */
/* -------------------- */

/* Generali. */
#define putchar(char) putc(char,stdout)
#define OK        0       /* Uscita corretta da funzione o dal programma. */
#define WARNING   9       /* Uscita corretta da avviso. */
#define ERROR     9999    /* Uscita corretta da errore. */
#define GURU      29999   /* Uscita non corretta da funzione. */
#define NPR       0UL     /* Valore di ritorno per un numero primo. */
#define ZDIVS     1UL     /* Convenzione per il numero zero. */
#define UNCL      1UL     /* Convenzione per il numero uno.  */
#define NDIVS     1UL     /* Valore di ritorno per un numero divisibile. */
#define INL       1UL     /* Inizializiazione variabili a uno. */
#define NFLAG     1U      /* Segnalatore 1. */
#define LFLAG     0U      /* Segnalatore 2. */
#define ENGLISH   1U      /* Info in inglese. */
#define ITALIANO  2U      /* Info in italiano. */
#define ESPANOL   3U      /* Info in spagnolo. */
#define FRANCAIS  4U      /* Info in francese. */
#define PORTUGUES 5U      /* Info in portoghese. */
#define DEUTCHE   6U      /* Info in tedesco. */
#define MSGBASE   100     /* Codici di conferma/errore (100=BaseEnglish, 101=BaseItaliano, etc.). */
#define ERRSBASE  1000    /* Codici errore (1000=BaseEnglish, 1001=BaseItaliano, etc. ). */
#define ERRSHIFT  500     /* Codice errore di traslazione per errori multipli. */
#define HELP      425     /* Codice per l'opzione di Help estesa. */
#define READ      "r"     /* Lettura dal file. */
#define WRITE     "w"     /* Scrittura sul file. */
#define NUL       '\0'    /* Carattere nullo */

/* ---------------------------------------------------------- */
#define NAMEPROG "firstnum"  /* Nome ufficiale del programma. */
/* ---------------------------------------------------------- */
#define VERSION  "1.08b"   /* Versione attuale del programma. */
/* ---------------------------------------------------------- */
#define RELEASE  "1.08b-20250327"    /* Versione di Rilascio. */
/* ---------------------------------------------------------- */

/* Funzione globoptions(). */
#define NOGOPT 0      /* Opzione NOPT (ZERO=nessuna opzione). */
#define GLOB1  300    /* Serie di opzioni: '-K' + '-T' + '-B' + '-V' + '-C'. */
#define GLOB2  400    /* Serie di opzioni: '-Y' + '-S' + '-F' + '-D'. */
#define GLOB3  500    /* Serie di opzioni: '-P' + '-L' + '-Q' + '-N'. */
#define ERRSG  999    /* Condizione di errore: nessuna serie di opzioni valida. */

/* Funzione trueoptions(). */
#define ZERO   0      /* Opzione NOPT (ZERO=nessuna opzione). */
#define ONE    1      /* Serie di opzioni: '-D' + '-Q' + '-K'. */
#define TWO    2      /* Serie di opzioni: '-Y' + '-S' + '-F'. */
#define TREE   3      /* Serie di opzioni: '-P' + '-L'. */
#define FOUR   4      /* Opzione '-N'. */
#define FIVE   5      /* Opzione '-T'. */
#define BSS    10     /* Opzione '-B'. */
#define VRL    20     /* Opzione '-V'. */
#define CMP    30     /* Opzione '-C'. */
#define HLP    100    /* Opzioni speciali QuickHelp e Info: '-H', '-?'. */
#define ISPC   200    /* Opzione speciale HELP: '--'. */
#define ERRS   999    /* Condizione di errore: nessuna opzione valida. */

/* Funzione trueswitch(). */
#define NOSWT   0     /* Switch NSWT (NOSWT=nessuno Switch). */
#define TRUESW  1     /* Gruppo di Switch: 'S', 'U', 'D'. */
#define TRUEPM  2     /* Solo Switch 'P'. */
#define LISTSW  3     /* Solo Switch 'L'. */
#define NCOLTP  5     /* Solo Switch 'T'. */
#define SPECSW  8     /* Gruppo di Switch speciali '?I', '?F' e '?M'. */
#define HELPSW  9     /* Solo Switch speciale '--HELP'. */
#define ERRSW   99    /* Condizione di errore: nessun Switch valido. */

/* Opzioni. */
#define NOPT   '\0'   /* Nessuna opzione usata. */
#define LINF   '?'    /* Opzione per Info. */
#define EHLP   '-'    /* Opzione speciale per Help. */
#define QHLP   'h'    /* Opzione Quick Help. */
#define SYMP   's'
#define FORM   'f'
#define KEYS   'k'
#define TINS   'y'
#define PRIME  'p'
#define DIVS   'd'
#define NSDIV  'q'    /* Da SYMP a CALC, opzioni funzionalità. */
#define PLIST  'l'
#define NPRIM  'n'
#define STAT   't'
#define BASE   'b'
#define VARS   'v'
#define CALC   'c'

/* Switch. */
#define PAGE   '1'    /* Switch speciale abbinato a '?M'. */
#define NSWT   '\0'   /* Nessuno Switch usato. */
#define SSC    'f'    /* Switch speciale_1: '-?F'. */
#define MAN    'm'    /* Switch speciale_2: '-?M'. */
#define ISW    'i'    /* Switch speciale_3: '-?I'. */
#define EHL    'h'    /* Switch speciale 4: '--HELP'. */
#define TBL    't'    /* Switch attivazione incolonnamento. */
#define LST    'l'    /* Switch attivazione identazione. */
#define PME    'p'
#define SEL    's'
#define UPP    'u'    /* Da PME a DOW, Switch di selezione/marcatura. */
#define DOW    'd'

/* Limiti. */
#define NIM     65535U        /* Inizializzazioni variabili al valore massimo. */
#define AEL     63U
#define PEL     1023U         /* AEL, PEL e MEL. Elementi di array statici. */
#define MEL     8191U
#define LMAX    16U           /* Dimensione array nome file per info locale. */
#define NMAX    255U          /* Dimensione array percorso/nomefile selezione lingua. */
#define RANGE   65536U        /* Limite massimo di elementi per una serie. */
#define RGTAB   262144U       /* Limite massimo di elementi per una tabella */
#define UL_MAX  4294967296UL  /* Limite massimo di calcolo. */
#define LANG    "FLANG="
#define ENDL    "_END"

/* Locale. */
#define NOTL   1
#define YESL   0
#define ENFM   ".en_lng_man\0"
#define ITFM   ".it_lng_man\0"
#define ESFM   ".es_lng_man\0"
#define FRFM   ".fr_lng_man\0"
#define PTFM   ".pt_lng_man\0"
#define DEFM   ".de_lng_man\0"

/* Fine definizioni interne. */


/* ---------------------- */
/* Dichiarazioni globali. */
/* ---------------------- */

/* Funzioni. */
unsigned long primenum(unsigned long);   /* Funzione di ricerca del numero primo. */
int errorstype(short *);                 /* Funzione per la gestione degli errori. */
int filemsg(short *,unsigned long *);    /* Funzione per la gestione dei msg di conferma/errore. */
short cfglang(short *);                  /* Funzione per il cambio della lingua (EN-IT-ES-FR-PT-DE). */
short globoptions(void);                 /* Funzione per la gestione dei gruppi di opzioni. */
short trueoptions(void);                 /* Funzione per la gestione delle opzioni e dei gruppi. */
short trueswitch(void);                  /* Funzione per la gestione dei gruppi di Switch. */
short switcherrs(void);                  /* Funzione per il controllo degli Switch sulle opzioni. */
short tpcol(unsigned long,unsigned long,short *);   /* Funzione di visualizzazione a più colonne. */
void primefact(unsigned long,unsigned long);   /* Funzione di scomposizione in fattori primi e stampa. */
void statseries(unsigned short);         /* Funzione per la gestione statistica. */
void about(short *,char *,char *);       /* Funzione per info iniziali di aiuto e presentazione. */
void quickhelp(short *,char *);          /* Funzione per aiuto rapido. */
void helpfunc(short *,char *,char *);    /* Funzione per aiuto dettagliato. */
void contrib(char *,char *);             /* Funzione contributo : scalare di FIRSTNUM. */

/* Vettori. */
unsigned long eval[AEL];      /* Array contenente la serie dei fattori primi. */
unsigned short nprime[PEL];   /* Array contenente le somme dei numeri primi. */
unsigned short ndivs[PEL];    /* Array contenente le somme dei numeri divisibili. */
unsigned short mvect[MEL];    /* Array per la gestione della media dei fattori. */
char nflgm[LMAX];   /* Array contenente il 'nome_file' specifico per il manuale locale. */
char nfile[NMAX];   /* Array contenente il 'percorso/nome_file' di configurazione lingua. */
char nfdir[NMAX];   /* Array contenente il 'percorso/.directory' per il file del manuale in lingua locale. */
char nfman[NMAX];   /* Array contenente il 'percorso/.directory/.nome_file' per il manuale in lingua locale. */

/* Variabili. */
unsigned short swflag=NFLAG,fldp=0U;
unsigned short pmin=NIM,dmin=NIM;
unsigned short pmax,dmax;
unsigned short psum,dsum;
unsigned short dmean,pmean,cntvis=0,cnt=0;
static short lang;
short errscode=0;
short fmesg=0,fsign=0,ncx=1;
char option=NOPT;
char subopt=NSWT;
char flgopt=NSWT;
char *verrel=VERSION,*relrel=RELEASE;
char *nprg=NAMEPROG;
char *pnd,*pnf;
char *pesr,*pmsl;
char *usr,*home,*lngm,*pfdr,*pflm;
int lb=0,ls=0;
FILE *fp,*fp0;
DIR *dp;

/* --------------------- */
/* Default scelta lingua */
/* --------------------- */
static short lngdef=ENGLISH;  /* Selezione lingua default. (ENGLISH, ITALIANO, [ALTRE LINGUE]). */

/* --------------------------- */
/* Segnalazione per lingua non */
/* completamente implementata  */
/* --------------------------- */
static short noten=YESL;
static short notit=YESL;   /* imposta il flag per la visualizzazione del messaggio */
static short notes=NOTL;   /* della lingua non completamente implementata. */
static short notfr=NOTL;   /* YESL = implementazione completa della lingua */
static short notpt=NOTL;   /* NOTL = implementazione parziale della lingua */
static short notde=NOTL;

/* Fine dichiarazioni globali. */


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* +++++++++++++++++++  Inizio della sezione principale  ++++++++++++++++++++ */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */


/* --------------------------------- */
/* Sezione principale del programma. */
/* --------------------------------- */

int main(int argc,char *argv[]) {

/* Dichiarazione di funzioni. */
   unsigned long primenum(unsigned long);
   int errorstype(short *);
   int filemsg(short *,unsigned long *);
   short globoptions(void);
   short trueoptions(void);
   short trueswitch(void);
   short switcherrs(void);
   short tpcol(unsigned long,unsigned long,short *);
   short cfglang(short *);
   void primefact(unsigned long,unsigned long);
   void statseries(unsigned short);
   void about(short *,char *,char *);
   void quickhelp(short *,char *);
   void helpfunc(short *,char *,char *);
   void contrib(char *,char *);

/* Dichiarazione di variabili static. */
   extern short lngdef,lang,ncx;
   extern short noten,notit,notes,notfr,notpt,notde;

/* Dichiarazione di vettori e variabili extern. */
   extern unsigned short pmax,dmax,pmin,dmin,cntvis;
   extern unsigned short dmean,pmean,swflag,fldp;
   extern unsigned short nprime[],ndivs[],mvect[];
   extern short errscode,fmesg,fsign;
   extern char nfile[],nfdir[],nflgm[],nfman[];
   extern char option,subopt,flgopt;
   extern char *pnd,*pnf,*verrel,*relrel,*nprg;
   extern char *pesr,*pmsl;
   extern char *usr,*home,*lngm,*pfdr,*pflm;
   extern int lb,ls;

/* Dichiarazioni di variabili e puntatori locali. */
   float fdist=0.0,fcom=0.0;
   unsigned long num=INL,limit=INL,limt=INL,number=INL;
   unsigned long com=INL,tmp=INL;
   unsigned long divs=0UL,hfatt=0UL,select=1UL,range=1UL,self=0UL;
   unsigned short psegm=0U,dsegm=0U,nseg=1U,lseg=0U,sumprim=0U,sumdivs=0U;
   unsigned short selcount=0U,fler=0U;
   unsigned short pcount=0U,dcount=0U,seltot=0U,flags=LFLAG,hflag=NFLAG;
   unsigned short pdist=0U,hpdist=0U,lpdist=0U,pmdist=0U,npv=0U,flprt=0U;
   unsigned short *pnprime,*pndivs,*pvect;

   char mark=NUL,lask[2],lasklng[12],laskdef[24];
   char cmd[64],*pcmd;
   char esr[5],msl[6],nd[16];
   char h=NUL,e=NUL,l=NUL,p=NUL,X=NUL,chm=NUL;
   char *seq1=NAMEPROG,*seq2=RELEASE,*plask,*plaskdef,ce=EOF;
   char *plaskln0,*plaskln1,*plaskln2,*plaskln3,*plaskln4;
   short flg=0,flgm=0,flgers=0;
   int ctl=0,help=0,a=0,b=0,c=0,i=0;
   for(i=0;i<AEL;++i) cmd[i]=NUL,eval[i]=NUL;
   for(i=0;i<PEL;++i) nprime[i]=NUL,ndivs[i]=NUL;
   for(i=0;i<MEL;++i) mvect[i]=NUL;

/* Inizializzazione di variabili static. */
   lang=lngdef;

/* Inizializzazione del Flag di DEBUG. */
/* Normalmente deve essere posto a zero. */
   fsign=1;     /* Se fsign = 1 allora i 'mesg-rif-errors' per debug sono attivi, altrimenti no. */

/* Inizializzazione puntatori. */
   pnprime=nprime;
   pndivs=ndivs;
   pvect=mvect;
   plaskdef=laskdef;
   plaskln0=lasklng;
   plask=lask;
   pesr=esr;
   pmsl=msl;
   pnd=nd;
   pnf=nfile;
   lngm=nflgm;
   pfdr=nfdir;
   pflm=nfman;
   pcmd=cmd;

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
   else if(lngdef==DEUTCHE) {
      plaskdef="DEUTCHE (Standard)";   /* Tedesco -Tedesco. */
      plaskln0="ENGLISH";              /* Tedesco -Inglese. */
      plaskln1="ITALIANO";             /* Tedesco -Italiano. */
      plaskln2="ESPAÑOL";              /* Tedesco -Spagnolo. */
      plaskln3="FRANÇAIS";             /* Tedesco -Francese. */
      plaskln4="PORTUGÛES";            /* Tedesco -Portoghese. */
   }
   else {

   /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
   /* delle funzionalità interne, delle opzioni e degli Switch. */
      if(fsign) {
         printf("ERROR [LANG] GURU MEDITATION\n\n");
         return GURU;
      }
   }

/* Inizializzazione degli identificatori del file di configurazione. */
   pmsl=LANG; pmsl=msl;
   pesr=ENDL; pesr=esr;

/* Ottiene il nome dell'utente. */
   ls=strlen(pmsl),lb=strlen(pesr);
   if((usr=getenv("USER"))==NULL) {

   /* Esecuzione se non viene trovato il nome dell'utente. */
   /* Non posso ottenere il nome dell'utente. */
   /* Visualizza [Errore: Non posso aprire il file [.firstlang.cfg]!]. */
      fmesg=MSGBASE+lang+20;
      filemsg(&fmesg,&self);
   }

/* Ottiene il percorso della directory dell'utente. */
   struct passwd *pwd=getpwuid(getuid());
   if(pwd==NULL) {

   /* Esecuzione se non viene trovata la path della directory home. */
   /* Non posso ottenere il path della directory home. */
   /* Visualizza [Errore: Non posso aprire il file [.firstlang.cfg]!]. */
      fmesg=MSGBASE+lang+20;
      filemsg(&fmesg,&self);
   }

/* Percorso della directory dell'utente. */
   home=pwd->pw_dir;

/* Apertura di [.firstlang.cfg] in lettura. */
   snprintf(pnf,sizeof(nfile),"%s/.firstlang.cfg",home);
   if((fp0=fopen(pnf,READ))==NULL) {

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
         printf(" Choisir? ");
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
      else if(lngdef==DEUTCHE) {
         printf("\n Zunge:\n");
         printf("  1 = %s\n",plaskln0);   /* Inglese. */
         printf("  2 = %s\n",plaskln1);   /* Italiano. */
         printf("  3 = %s\n",plaskln2);   /* Spagnolo. */
         printf("  4 = %s\n",plaskln3);   /* Francese. */
         printf("  5 = %s\n",plaskln4);   /* Poroghese. */
         printf("  6 = %s\n",plaskdef);   /* Tedesco. */
         printf(" Wählen? ");
      }
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
         printf("ERROR [ASK] GURU MEDITATION\n\n");
         return GURU;
      }
      while((*plask=getchar())!='\n')
         plask++;
      plask=lask;
      if(*plask=='\n')
         lang=lngdef;
      else
         lang=atoi(plask);
      putchar('\n');

   /* Avvertenza per incompleta implementazione di alcune lingue. */
      if(lang==ENGLISH||lang==ESPANOL||lang==FRANCAIS||lang==PORTUGUES||lang==DEUTCHE) {
         fmesg=MSGBASE+lang+50;
         filemsg(&fmesg,&self);
      }
      if(!lang||lang>6)
         lang=lngdef;
   /* --- */

   /* Esecuzione in caso il file di configurazione sia assente o inaccessibile. */
   /* Visualizza [Ok. Il file predefinito [.firstlang.cfg] è stato creato.]. */
      fmesg=MSGBASE+lang+10;
      filemsg(&fmesg,&self);

   /* Apertura di .firstlang.cfg in scrittura.  */
      snprintf(pnf,sizeof(nfile),"%s/.firstlang.cfg",home);
      if((fp=fopen(pnf,WRITE))==NULL) {

      /* Esecuzione se il file di configurazione non si può aprire. */
      /* Visualizza [Errore: Non posso aprire il file [.firstlang.cfg]!]. */
         fmesg=MSGBASE+lang+20;
         filemsg(&fmesg,&self);

      /* Visualizza [Ok. Sarà mantenuta la lingua preimpostata.]. */
         fmesg=MSGBASE+lang+0;
         if(filemsg(&fmesg,&self)==OK)
         lang=lngdef;
      }
      else {

      /* Memorizzazione del nuovo stato del flag per la selezione della lingua. */
         pmsl=LANG; fputs(pmsl,fp);   /* Stringa identificativa iniziale. */
         ce=fputc(lang,fp);        /* Flag impostazione lingua. */
         pesr=ENDL; fputs(pesr,fp);   /* Stringa identificativa finale. */
         if(ce==EOF) {

         /* Esecuzione in caso in cui il file non sia stato salvato. */
         /* Visualizza [Errore: File [.firstlang.cfg] non salvato!]. */
            fmesg=MSGBASE+lang+30;
            filemsg(&fmesg,&self);
            lang=lngdef;
         }
      }
      fclose(fp);
      if(ce!=EOF) {
         printf("\r+++Ok.\n\n");
         return OK;
      }
      printf("\r---K.O.\n\n");
      return ERROR;
   }
   else {

   /* Lettura dello stato del flag per la selezione della lingua dal file [.firstlang.cfg]. */
      pmsl=LANG,pesr=ENDL;
      pnd=fgets(pmsl,ls,fp0);
      if(pnd!=NULL) {

      /* Esecuzione se il file di configurazione non si può aprire. */
      /* Visualizza [Errore: Non posso aprire il file [.firstlang.cfg]!]. */
         fmesg=MSGBASE+lang+20;
         filemsg(&fmesg,&self);
      }
      fseek(fp0,-5L,SEEK_END);   /* Sposta l'offest di inizio file.  */
      lang=fgetc(fp0);
      fclose(fp0);
      if(lang>6)
         lang=lngdef;
   }

/* Estrazione opzione e Switch se presente il trattino. */
/* Deve essere presente almeno un argomento. */
   if(argc>1) {
      if(**(argv+1)=='-') {
         mark=(char)tolower((short)argv[1][0]);
         option=(char)tolower((short)argv[1][1]);
         subopt=(char)tolower((short)argv[1][2]);
         flgopt=(char)tolower((short)argv[1][3]);

      /* trueoptions() ritorna ZERO (0) se l'opzione non viene specificata (NOPT vale '\0'). */
      /* trueswitch() ritorna ERRSW (99) invece di NOSWT (0) se l'opzione non viene specificata. */
      /* switcherrs() ritorna ERROR (1) invece di OK (0) se trueswitch() ritorna ERRSW (99). */
      /* Correzione del problema. */
         if(option==NOPT)
            subopt=NSWT,flgopt=NSWT;

      /* LBLERR_0 */
      /* Segnalazione di errore, aggiuntiva a LBLERR_1. */
         if(option==NOPT&&*(argv+2)!=NULL&&argc<=4) {

         /* Esecuzione se l'opzione è mancante. */
         /* Visualizza [Errore: Opzione mancante!]. */
            errscode=ERRSBASE+lang+30;
            return(errorstype(&errscode));
         }

      /* Se è presente l'opzione '-CLR' senza altri argomenti */
         if(mark=='-'&&option=='c'&&subopt=='l'&&flgopt=='r') {

         /* Apertura di .firstlang.cfg in scrittura.  */
            snprintf(pnf,sizeof(nfile),"%s/.firstlang.cfg",home);
            if((fp=fopen(pnf,WRITE))==NULL) {

            /* Esecuzione se il file di configurazione non si può aprire. */
            /* Visualizza [Errore: Non posso aprire il file [.firstlang.cfg]!]. */
               fmesg=MSGBASE+lang+20;
               filemsg(&fmesg,&self);

             /* Visualizza [Ok. Sarà mantenuta la lingua preimpostata.]. */
                fmesg=MSGBASE+lang+0;
                if(filemsg(&fmesg,&self)==OK)
                return(putchar('\r'));
            }
            else {

            /* Eliminazione del file di configurazione della lingua locale */
               sprintf(pcmd,"rm %s",pnf);
               ctl=system(pcmd);
               if(ctl==-1) {

               /* Esecuzione se il file di configurazione non si può aprire. */
               /* Visualizza [Errore: Non posso accedere al file [.firstlang.cfg]!]. */
                  fmesg=MSGBASE+lang+100;
                  return(filemsg(&fmesg,&self));
               }
            }
            return(printf("+++Ok.\nInitial mode.\n\n"));
         }

      /* Se è presente l'opzione '-RST' senza altri argomenti */
         if(mark=='-'&&option=='r'&&subopt=='s'&&flgopt=='t') {

         /* Reimpostazione della lingua di default. */
            lang=lngdef;
            if(!cfglang(&lang))
               return(printf("\rPreset language mode.\n+++Ok.\n\n"));
            else
               return(printf("\r---K.O. Language not changed!\n\n"));
         }

      /* Se è presente l'opzione '-?' senza nessun Switch. */
         if((mark=='-'&&option=='?')&&subopt==NSWT&&argc==2) {

         /* Visualizzazione info autore e di primo aiuto. */
            if(lang==ENGLISH)
         	     printf("\n%s         Version: %s\n",nprg,verrel);
         	  else if(lang==ITALIANO)
         	     printf("\n%s        Versione: %s\n",nprg,verrel);
         	  else if(lang==ESPANOL)
         	     printf("\n%s         Versión: %s\n",nprg,verrel);
         	  else if(lang==FRANCAIS)
         	     printf("\n%s        Version : %s\n",nprg,verrel);
         	  else if(lang==PORTUGUES)
         	     printf("\n%s          Versão: %s\n",nprg,verrel);
         	  else if(lang==DEUTCHE)
         	     printf("\n%s         Version: %s\n",nprg,verrel);
         	  else {

            /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
            /* delle funzionalità interne, delle opzioni e degli Switch. */
               if(fsign)
                  printf("ERROR [INFO-1] GURU MEDITATION\n\n");
               return GURU;
            }
         	  printf("~© (2010-2025) - GNU/GPL vers.3\n");
         	  printf(" (FSF) Free Software Foundation\n");
         	  if(lang==ENGLISH) {
               printf("Written by G. B. alias PiErre60\n");
               printf(" with the collaboration of:\n");
               printf(" A. F. F. alias Ferro811\n");
            }
         	  else if(lang==ITALIANO) {
         	     printf("Scritto da G. B. alias PiErre60\n");
         	     printf(" con la collaborazione di:\n");
         	     printf(" A. F. F. alias Ferro811\n");
         	  }
         	  else if(lang==ESPANOL) {
               printf("Escrito por G.B. alias PiErre60\n");
               printf(" con la colaboración de:\n");
               printf(" A. F. F. alias Ferro811\n");
            }
            else if(lang==FRANCAIS) {
               printf("Écrit par G. B.  alias PiErre60\n");
               printf(" avec la collaboration de :\n");
               printf(" A. F. F. alias Ferro811\n");
            }
            else if(lang==PORTUGUES) {
               printf("Escrito por G.B. alias PiErre60\n");
               printf(" com a colaboração de:\n");
               printf(" A. F. F. alias Ferro811\n");
            }
            else if(lang==DEUTCHE) {
               printf("Geschrieben von G.B. (PiErre60)\n");
               printf(" in Zusammenarbeit mit:\n");
               printf(" A. F. F. alias Ferro811\n");
            }
            else {

            /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
            /* delle funzionalità interne, delle opzioni e degli Switch. */
               if(fsign)
                  printf("ERROR [INFO-2] GURU MEDITATION\n\n");
               return GURU;
            }
            printf("\n");
            if(lang==ENGLISH) {
         	     printf("Legal notes:\n");
         	     printf(" This software is licensed under\n");
         	     printf("the GNU/GPL v.3 (FSF) license\n");
         	     printf("«as is»  without any form of\n");
         	     printf("express or implied warranties.\n\n");
         	     printf(" The author declines all responsibility\n");
         	     printf("for any damage resulting from improper\n");
         	     printf("use not inherent to a purely educational\n");
               printf("and/or informative context.\n");
         	     printf("For other references:\n");
         	     printf(" https://fsf.org/licenses/\n");
         	     printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
         	     printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
         	  }
         	  else if(lang==ITALIANO) {
         	     printf("Note legali:\n");
         	     printf(" Questo Software è distribuito\n");
         	     printf("sotto licenza (FSF) GNU/GPL v.3\n");
         	     printf("«così com'è» senza alcuna forma\n");
         	     printf("di garanzia implicita e/o esplicita.\n");
         	     printf(" L'autore declina ogni responsabilità\n");
         	     printf("per eventuali danni derivanti da un uso\n");
         	     printf("improprio non inerente ad un contesto\n");
               printf("puramente didattico e/o divulgativo.\n");
         	     printf("Per altri riferimenti:\n");
         	     printf(" https://fsf.org/licenses/\n");
         	     printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
         	     printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
         	  }
         	  else if(lang==ESPANOL) {
         	     printf("Notas legales:\n");
         	     printf(" Este software se distribuye bajo\n");
         	     printf("la licencia GNU/GPL v.3 (FSF)\n");
         	     printf("«tal cual»  sin ningún tipo de\n");
         	     printf("garantía implícita y/o explícita.\n");
         	     printf(" El autor declina toda responsabilidad\n");
         	     printf("por cualquier dãno resultante de un uso\n");
         	     printf("indebido no propio de un contexto\n");
               printf("puramente educativo y/o informativo.\n");
         	     printf("Para otras referencias:\n");
         	     printf(" https://fsf.org/licenses/\n");
         	     printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
         	     printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
         	  }
         	  else if(lang==FRANCAIS) {
         	     printf("Notes légales :\n");
         	     printf(" Ce logiciel est distribué sous\n");
         	     printf("la licence GNU/GPL v.3 (FSF)\n");
         	     printf("«tel quel»  sans aucune forme de\n");
         	     printf("garantie implicite et/ou explicite.\n");
         	     printf(" L'auteur décline toute responsabilité pour\n");
         	     printf("tout dommage résultant d'une utilisation\n");
         	     printf("impropre non inhérente à un contexte\n");
               printf("purement éducatif et/ou informatif.\n");
         	     printf("Pour d'autres références:\n");
         	     printf(" https://fsf.org/licenses/\n");
         	     printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
         	     printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
         	  }
         	  else if(lang==PORTUGUES) {
         	     printf("Notas Legais: \n");
         	     printf(" Este Software é distribuído sob\n");
         	     printf("a licença GNU/GPL v.3 (FSF)\n");
         	     printf("«como está»  sem qualquer forma de\n");
         	     printf("garantia implícita e/ou explícita.\n");
         	     printf(" O autor declina qualquer responsabilidade\n");
         	     printf("por quaisquer danos resultantes de uso\n");
         	     printf("indevido não inerente a um contexto\n");
               printf("puramente educacional e/ou informativo.\n");
         	     printf(" Para outras referências:\n");
         	     printf(" https://fsf.org/licenses/\n");
         	     printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
         	     printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
         	  }
         	  else if(lang==DEUTCHE) {
         	     printf("Rechtliche Hinweise: \n");
         	     printf(" Diese Software wird unter der\n");
               printf("GNU/GPL v.3 (FSF)-Lizenz\n");
      	       printf("„wie besehen“ ohne jegliche implizite\n");
         	     printf("und/oder explizite Garantie vertrieben.\n");
         	     printf(" Der Autor lehnt jede Verantwortung für\n");
         	     printf("Schäden ab, die aus einer unsachgemäßen\n");
         	     printf("Verwendung resultieren, die nicht in einem\n");
               printf("rein pädagogischen und/oder informativen\n");
         	     printf("Kontext erfolgt.\n");
               printf("Für andere Referenzen:\n");
     	         printf(" https://fsf.org/licenses/\n");
         	     printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
         	     printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
         	  }
         	  else {

            /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
            /* delle funzionalità interne, delle opzioni e degli Switch. */
               if(fsign)
                  printf("ERROR [INFO-3] GURU MEDITATION\n\n");
               return GURU;
            }

         /* Uscita forzata */
         	  return OK;
         }
         else {

         /* Esecuzione se all'opzione seguono argomenti. */
            if((mark=='-'&&option=='?')&&subopt==NSWT&&argc!=2) {

            /* Visualizza [Errore: Non è richiesto alcun argomento!]. */
               errscode=ERRSBASE+lang+130;
               return(errorstype(&errscode));
            }
         }

      /* Contributi informativi e nascosti. */
         if((mark=='-'&&option=='?'&&subopt!=NSWT)&&argc==2) {

         /* +++ Contributo nascosto +++ */
            if(subopt==SSC) {    /* Switch 'F'. */

            /* Visualizza [Errore: Opzione errata!]. */
               if(*(*(argv+1)+3)!=NUL) {
                  errscode=ERRSBASE+lang+20;
                  return(errorstype(&errscode));
               }

            /* Visualizza il conributo nascosto. */
               contrib(seq1,seq2);
               printf("\n");
               return OK;
            }
            else if(subopt==MAN) {    /* Switch 'M'. */
               if(flgopt!=NSWT) {
                  if(flgopt!='0'&&flgopt!='1') {

                  /* Visualizza [Errore: Opzione errata!]. */
                     errscode=ERRSBASE+lang+20;
                     return(errorstype(&errscode));
                  }
                  else {
                    if(flgopt=='0') flgm=1;
                    else flgm=0;
                  }
               }
               else flgm=1;

            /* Impostazione variabile stringa per manuale locale. */
               lngm="VOID\0";  /* Azzerata.  */
               if(lang==ENGLISH)
                  lngm=ENFM;   /* .en_lng_man. */
               if(lang==ITALIANO)
                  lngm=ITFM;   /* .it_lng_man. */
               if(lang==ESPANOL)
                  lngm=ESFM;   /* .es_lng_man. */
               if(lang==FRANCAIS)
                  lngm=FRFM;   /* .fr_lng_man. */
               if(lang==PORTUGUES)
                  lngm=PTFM;   /* .pt_lng_man. */
               if(lang==DEUTCHE)
                  lngm=DEFM;   /* .de_lng_man. */

            /* Funzione non implementata. */
               if(lngm==(char *)"VOID\0")
                  fsign=ERROR;   /* Imposta il flag ad errore. */
               else {

               /* Aggiunta della Directory [.fnl] al percorso utente. */
                  snprintf(pfdr,sizeof(nfdir),"%s/.fnl",home);
                  if((dp=opendir(pfdr))==NULL) {

                  /* Esecuzione se il percorso della Directory non si può aprire. */
                  /* visualizza [Errore: Non posso accedere al file del manuale d'uso [.it_lng_man]! */
                     fmesg=MSGBASE+lang+100;
                     filemsg(&fmesg,&self);
                  }
                  else {

                  /* se la Directory esiste aggiunge il nome del file al percorso. */
                        pfdr=strcat(pfdr,"/");
                        pflm=strcat(pfdr,lngm);
                        if((fp0=fopen(pflm,READ))==NULL) {

                     /* Esecuzione se il file di configurazione non si può aprire. */
                     /* Visualizza [Errore: Non posso aprire il file [.xy_lng_man]!]. */
                        fmesg=MSGBASE+lang+100;
                        filemsg(&fmesg,&self);
                     }
                     else {

                     /* Se flgm = 1 visualizza con less; se flgm = 0 su stdout della shell. */
                        if(flgm) {

                        /* Visualizzazione del manuale d,uso. */
                           sprintf(pcmd,"less %s",pflm);
                           ctl=system(pcmd);
                           if(ctl==-1) {

                           /* Esecuzione se il file di configurazione non si può aprire. */
                           /* Visualizza [Errore: Non posso aprire il file [.xy_lng_man]!]. */
                              fmesg=MSGBASE+lang+100;
                              return(filemsg(&fmesg,&self));
                           }
                        }
                        else {

                        /* Lettura del file del manuale d'uso. */
                           while((chm=fgetc(fp0))!=EOF) putchar(chm);
                           fclose(fp0);
                           putchar('\n');
                        }
                     }
                  }
                  return OK;
               }

            /* Controllo assenza caratteri spuri dopo lo Switch 'M'. */
               if(*(*(argv+1)+3)!=NUL) {

               /* Visualizza [Errore: Opzione errata!]. */
                  errscode=ERRSBASE+lang+20;
                  return(errorstype(&errscode));
               }
               if(fsign==ERROR) {

               /* Visualizza un avviso per mancata implementazione della funzionalità. */
                  fmesg=MSGBASE+lang+90;
                  if(filemsg(&fmesg,&self)==OK)
                  lang=lngdef;
                  return OK;
               }
            }

            /* Manuale rapido integrato, Very Good! */
            else if(subopt==ISW) {    /* Switch 'I'. */
               if(*(*(argv+1)+3)!=NUL) {

               /* Visualizza [Errore: Opzione errata!]. */
                  errscode=ERRSBASE+lang+20;
                  return(errorstype(&errscode));
               }
               if(lang==ITALIANO) {
                  printf("\n =======================================================================\n");
                  printf("              %s v.%s   -   Guida rapida.\n",nprg,verrel);
                  printf("  Questo programma permette di scomporre i numeri naturali nei loro fat-\n");
                  printf(" tori primi. Ricerca i numeri primi e permette di rilevare alcune carat-\n");
                  printf(" teristiche  della loro  distribuzione.  Il programma è strutturato  per\n");
                  printf(" essere eseguito da una Shell e si presenta in modo simile ad un comando\n");
                  printf(" di sistema. Dispone di molte opzioni che ne differenziano sia la visua-\n");
                  printf(" lizzazione sia il modo operativo. E' possibile definire liste di numeri\n");
                  printf(" da scomporre nei loro fattori primi oppure di ricercarvi all'interno di\n");
                  printf(" esse i relativi numeri primi. Ogni lista puo' avere un'ampiezza massima\n");
                  printf(" di  65535  elementi, mentre il numero più alto, scomponibile in fattori\n");
                  printf(" primi, in cui viene fornito un risultato corretto è 4294967296.\n");
                  printf("  Il programma ha solamente una  finalità  didattica, può inoltre essere\n");
                  printf(" usato quando serve conoscere i fattori primi di scomposizione di un nu-\n");
                  printf(" mero divisibile, oppure sapere se un  determinato valore  è primo o no.\n");
                  printf(" L'algoritmo che genera i fattori primi (numeri primi e fattori di scom-\n");
                  printf(" posizione) è stato  ampiamente testato  e fornisce sempre assolutamente\n");
                  printf(" risultati esatti e coerenti al contesto.\n");
                  printf("  Allo stato attuale  non risultano  esserci  particolari problematiche,\n");
                  printf(" tuttavia  potrebbero ancora sussistere  dei malfunzionamenti, a livello\n");
                  printf(" generale, nelle funzionalità del programma stesso, non ancora scoperti.\n");
                  printf(" Il programma viene fornito «così com'è» senza nessuna forma di garanzia\n");
                  printf(" esplicita o implicita. L'autore declina ogni responsabilità per eventu-\n");
                  printf(" ali danni derivanti da un uso improprio, fuori da un contesto puramente\n");
                  printf(" didattico e/o informativo.\n");
                  printf(" Esempi delle principali funzionalità:\n\n");
                  printf(" %s 911\n",nprg);
                  printf(" Visualizza se stesso e tutti i suoi fattori primi  di scomposizione, se\n");
                  printf(" il numero è divisibile, altrimenti solo se stesso se è un numero primo,\n");
                  printf(" come riportato in questo esempio: 911 (questo è un numero primo).\n\n");
                  printf(" %s -y 4096\n",nprg);
                  printf(" Visualizza se stesso ed il primo fattore di scomposizione come riporta-\n");
                  printf(" to in questo esempio:  4096 = 2  (il numero è divisibile per due).\n\n");
                  printf(" %s -s 4500\n",nprg);
                  printf(" Visualizza se stesso ed i suoi fattori primi di scomposizione in forma-\n");
                  printf(" to singolo, eventualmente ripetuto per ogni fattore primo, nel seguente\n");
                  printf(" modo esemplificativo: 4500 = 2 2 3 3 5 5 5\n");
                  printf(" Nota: 2 2 3 3 5 5 5 corrisponde a 2 x 2 x 2 x 3 x 3 x 5 x 5 x 5\n\n");
                  printf(" %s -f 123456\n",nprg);
                  printf(" Visualizza se stesso ed i suoi fattori primi di scomposizione in forma-\n");
                  printf(" to esponenziale come mostrato nell'esempio: 123456 = (2^6) 3 643\n");
                  printf(" Nota:  (2^6) 3 643  deve essere letto come  due elevato alla sesta  per\n");
                  printf(" tre per seicentoquarantatre.\n\n");
                  printf(" %s 1000 9999\n",nprg);
                  printf(" I numeri 1000 e 9999 rappresentano gli estremi minimo e massimo inclusi\n");
                  printf(" nella serie numerica indicata da computare. Gli estremi indicati  fanno\n");
                  printf(" parte della serie, la cui lunghezza sarà: (9999 - 1000 + 1) = 9000\n");
                  printf(" Visualizza tutti i numeri compresi nella serie indicata  e tutti i loro\n");
                  printf(" fattori primi  di scomposizione,  evidenziando  anche la successione di\n");
                  printf(" tutti  i numeri primi  in essa  contenuti, come riportato  nel seguente\n");
                  printf(" esempio (lista parziale):\n");
                  printf("  1000 = (2^3) (5^3)\n");
                  printf("  1001 = 7 11 13\n");
                  printf(" ...\n");
                  printf("  1007 = 19 53\n");
                  printf("  1008 = (2^4) (3^2) 7\n");
                  printf(" 1009\n");
                  printf("  1010 = 2 5 101\n");
                  printf(" ...\n");
                  printf("  9996 = (2^2) 3 (7^2) 17 \n");
                  printf("  9997 = 13 769\n");
                  printf("  9998 = 2 4999 \n");
                  printf("  9999 = (3^2) 11 101\n\n");
                  printf(" %s -y 123456 123499\n",nprg);
                  printf(" Visualizza in sequenza una lista composta dal numero stesso seguito dal\n");
                  printf(" primo fattore di scomposizione.  Se il numero è primo  non viene visua-\n");
                  printf(" lizzato ovviamente nessun  fattore primo di scomposizione, come nel se-\n");
                  printf(" guente esempio (lista parziale):\n");
                  printf("   123456 = 2\n");
                  printf("   123457\n");
                  printf("   123458 = 2\n");
                  printf(" ...\n");
                  printf("   123461 = 13\n");
                  printf("   123462 = 2\n");
                  printf("   123463 = 331\n");
                  printf(" ...\n");
                  printf("   123478 = 2\n");
                  printf("   123479\n");
                  printf("   123480 = 2\n");
                  printf("   123481 = 19\n");
                  printf(" ...\n");
                  printf("   123497 = 11\n");
                  printf("   123498 = 2\n");
                  printf("   123499\n\n");
                  printf(" %s -s 123456 123499\n",nprg);
                  printf(" Visualizza in sequenza  tutti i numeri della serie indicata, ognuno dei\n");
                  printf(" quali seguito da tutti i suoi fattori primi di scomposizione. Se un nu-\n");
                  printf(" mero è primo allora non viene visualizzato nulla dopo lo stesso numero.\n");
                  printf(" I fattori primi di scomposizione sono visualizzati tutti singolarmente,\n");
                  printf(" anche ripetuti  piu volte, se necessario. Ogni fattore primo è separato\n");
                  printf(" dal precedente da uno spazio.\n");
                  printf(" Esempio (lista parziale):\n");
                  printf("   123456 = 2 2 2 2 2 2 3 643\n");
                  printf("   123457\n");
                  printf("   123458 = 2 61729\n");
                  printf("   123459 = 3 7 5879\n");
                  printf("   123460 = 2 2 5 6173\n");
                  printf("   123461 = 13 9497\n");
                  printf("   123462 = 2 3 3 19 19 19\n");
                  printf("   123463 = 331 373\n");
                  printf("   123464 = 2 2 2 11 23 61\n");
                  printf(" ...\n");
                  printf("   123497 = 11 103 109\n");
                  printf("   123498 = 2 3 3 3 2287\n");
                  printf("   123499\n\n");
                  printf(" %s -f 1000 1110\n",nprg);
                  printf(" Visualizza in sequenza  tutti i numeri della serie indicata  ognuno dei\n");
                  printf(" quali  seguito da tutti i suoi fattori primi.  Se un numero è primo non\n");
                  printf(" viene visualizzato nulla dopo il numero stesso.\n");
                  printf(" È simile all'opzione -s con la differenza che ogni singolo fattore pri-\n");
                  printf(" mo di scomposizione ripetuto  viene visualizzato con notazione esponen-\n");
                  printf(" ziale; esempio: [1000 = (2^3) (5^3)]  invece di: [1000 = 2 2 2 5 5 5]\n");
                  printf(" '-f'  è l'opzione che genera questa funzione.\n");
                  printf(" '1000' e '1110' sono i valori estremi, minimo e massimo, della serie da\n");
                  printf(" computare e visualizzare.\n\n");
                  printf(" %s -fS 1000 1110 17\n",nprg);
                  printf(" Visualizza la sequenza e tutti i fattori di scomposizione di ogni nume-\n");
                  printf(" ro della serie, compresi i numeri primi, evidenziando  il primo fattore\n");
                  printf(" divisibile  di ogni numero della serie  uguale  a quello indicato  come\n");
                  printf(" discriminante.\n");
                  printf(" -fS'  indicano rispettivamente l'opzione ed il segnalatore.\n");
                  printf(" '1000 e 1110'  costituiscono i valori minimo e massimo della serie.\n");
                  printf(" '17'  è il fattore primo di scomposizione discriminante, che fa riferi-\n");
                  printf(" mento al segnalatore 'S' eventualmente specificato.\n");
                  printf(" Oltre a quello sopra indicato l'opzione -f accetta anche i seguenti se-\n");
                  printf(" gnalatori di discriminazione: 'P' (Primo), 'U' (Sopra) e 'D' (Sotto).\n");
                  printf(" Nell'esempio qui riportato (lista parziale):\n");
                  printf("   1000 = (2^3) (5^3)\n");
                  printf("   1001 = 7 11 13\n");
                  printf("   1002 = 2 3 167\n");
                  printf(" > 1003 = 17 59\n");
                  printf("   1004 = (2^2) 251\n");
                  printf(" ...\n");
                  printf("   1008 = (2^4) (3^2) 7\n");
                  printf("   1009\n");
                  printf("   1010 = 2 5 101\n");
                  printf("   1011 = 3 337 \n");
                  printf(" ...\n");
                  printf(" il numero primo  1003  è preceduto dal simbolo  '>'  perché il suo ini-\n");
                  printf(" ziale fattore primo di scomposizione è appunto 17.\n");
                  printf(" Fa seguito un rapporto statistico riassuntivo sulla serie calcolata:\n\n");
                  printf(" %s %s     Rapporto riassuntivo finale:\n",nprg,verrel);
                  printf(" -----------------------------------------------\n");
                  printf(" Serie totale di numeri:                     111\n");
                  printf(" Totale numeri primi:                         18\n");
                  printf(" Totale dei numeri divisibili:                93\n");
                  printf(" Fattore primo iniziale più alto:             29\n");
                  printf(" Fattore primo selezionato:                   17\n");
                  printf(" Quantità di valori selezionati:               2\n");
                  printf(" Distanza massima tra numeri primi:           18\n");
                  printf(" Distanza media tra numeri primi:              4\n\n");
                  printf(" Quasi tutte le opzioni visualizzano un rapporto staistico finale, salvo\n");
                  printf(" che per le opzioni '-l' e '-q' che non lo prevedono appositamente.\n");
                  printf(" Ogni opzione  visualizza  un  rapporto statistico  diverso  in funzione\n");
                  printf(" della computazione effettuata e della visualizzazione prescelta.\n");
                  printf(" Le opzioni '-y', '-s', '-f' accettano anche i seguenti segnalatori:\n");
                  printf(" 'S' (Selezione) evidenzia con '>'  il fattore primo indicato.\n");
                  printf(" 'P' (Primo)  evidenzia con '>'  tutti i numeri primi.\n");
                  printf(" 'U' (Sopra)  evidenzia con '>'  tutti i fattori primi maggiori o uguali\n");
                  printf(" a quello indicato come fattore primo di riferimento.\n");
                  printf(" 'D' (Sotto)  evidenzia con '>'  tutti i  fattori primi  minori o uguali\n");
                  printf(" a quello indicato come fattore primo di riferimento.\n\n");
                  printf(" Oltre ai segnalatori, o Switch, indicati sopra: 'S', 'P', 'U' e 'D', ci\n");
                  printf(" sono anche  gli Switch  'L' e 'T'  che  sono specifici  per le seguenti\n");
                  printf(" opzioni: '-l', '-q', '-p' e '-n'.\n\n");
                  printf(" I segnalatori sopra indicati: 'P', S', 'U' e 'D', possono essere appli-\n");
                  printf(" cati indifferentemente alle seguenti opzioni: '-y', '-s' ed '-f'.\n");
                  printf(" Le opzioni '-d' e '-k' accettano solo i segnalatori: 'S', 'U', e 'D'.\n");
                  printf(" Le opzioni '-t', '-b', '-c', '-v' e -k non accettano alcun segnalatore.\n");
                  printf(" Lo Switch 'P' NON può essere applicato alle opzioni '-d' e '-k'.\n");
                  printf(" Lo Switch 'L' può essere applicato solo alle opzioni '-l' e '-q'.\n");
                  printf(" Lo Switch 'T' puo essere applicato solo alle opzioni '-n' e '-p'.\n");
                  printf(" Queste opzioni sono riportate in seguito.\n\n");
                  printf(" %s -n 12344 12349\n",nprg);
                  printf(" Visualizza solo i  numeri divisibili  della serie, se un numero è primo\n");
                  printf(" non è visualizzato, ma viene lasciata una riga vuota nella lista.\n");
                  printf(" Nell'esempio qui sotto riportato:\n");
                  printf("  12344\n");
                  printf("  12345\n");
                  printf("  12346\n");
                  printf("\n");
                  printf("  12348\n");
                  printf("  12349\n");
                  printf(" il numero primo 123457 non è visualizzato.\n\n");
                  printf(" %s -d 12344 12388\n",nprg);
                  printf(" Visualizza solo  i numeri divisibili con tutti i loro  fattori primi di\n");
                  printf(" scomposizione compresi nella serie indicata, come avvene  per l'opzione\n");
                  printf(" '-f', ma qui i numeri primi sono ignorati.\n");
                  printf(" Esempio (Lista parziale):\n");
                  printf(" ...\n");
                  printf("   12344 = (2^3) 1543\n");
                  printf("   12345 = 3 5 823\n");
                  printf("   12346 = 2 6173\n");
                  printf("   12348 = (2^2) (3^2) (7^3)\n");
                  printf("   12349 = 53 233\n");
                  printf("   12350 = 2 (5^2) 13 19 \n");
                  printf("   12351 = 3 23 179\n");
                  printf("   12352 = (2^6) 193\n");
                  printf(" ...\n");
                  printf(" Come si può notare il numero primo 12347 viene completamente ignorato.\n\n");
                  printf(" %s -p 99 999\n",nprg);
                  printf(" Visualizza solo  la successione di tutti i numeri primi  compresi nella\n");
                  printf(" serie indicata. E' l'opzione complementare alla '-d'.\n");
                  printf(" Esempio (lista parziale):\n");
                  printf("  101\n");
                  printf("  103\n");
                  printf(" ...\n");
                  printf("  757\n");
                  printf("  761\n");
                  printf("  769\n");
                  printf("  773\n");
                  printf("  787\n");
                  printf("  797\n");
                  printf("  809\n");
                  printf(" ...\n");
                  printf("  991\n");
                  printf("  997\n\n");
                  printf(" %s -k 115 145\n",nprg);
                  printf(" Visualizza una lista di numeri divisibili dove i fattori primi di scom-\n");
                  printf(" posizione sono sempre e solamente due. È simile all'opzione '-d' con la\n");
                  printf(" sola differenza che  vengono visualizzati solo i numeri divisibili  che\n");
                  printf(" hanno esattamente solo due divisori.\n");
                  printf(" Esempio (lista parziale):");
                  printf("   115 = 5 23\n");
                  printf("   118 = 2 59\n");
                  printf("   119 = 7 17\n");
                  printf("   121 = (11^2)\n");
                  printf("   122 = 2 61\n");
                  printf(" ...\n");
                  printf("   141 = 3 47\n");
                  printf("   142 = 2 71\n");
                  printf("   143 = 11 13\n");
                  printf("   145 = 5 29\n\n");
                  printf(" %s -t 1 65535\n",nprg);
                  printf(" Visualizza solo un rapporto statistico dei dati aggregati riferiti alla\n");
                  printf(" serie di valori indicata.]\n");
                  printf(" Il rapporto comprende alcune voci che indicano il numero totale dei va-\n");
                  printf(" lori processati, il numero fattori primi e dei numeri divisibili  della\n");
                  printf(" serie, dell'iniziale  fattore di scomposizione piu alto, della  massima\n");
                  printf(" distanza tra due numeri primi, ed altro ancora.\n");
                  printf(" Esempio:\n\n");
                  printf("  firstnum 1.08b     Rapporto riassuntivo finale:\n");
                  printf("  -----------------------------------------------\n");
                  printf("  Selezione dal numero:                         1\n");
                  printf("  Al numero:                                65535\n");
                  printf("  Serie totale di numeri:                   65535\n");
                  printf("  Totale numeri primi:                       6542\n");
                  printf("  Totale dei numeri divisibili:             58992\n");
                  printf("  Fattore primo iniziale più alto:            251\n");
                  printf("  Distanza massima tra numeri primi:           72\n");
                  printf("  Distanza media tra numeri primi:              6\n\n");
                  printf(" %s -b 1000 5000 5\n",nprg);
                  printf(" Visualizza i dati aggregati  delle serie di valori  da un intervallo di\n");
                  printf(" valori specificato suddivise in sotto-liste contigue  di ampiezza arbi-\n");
                  printf(" traria. Visualizza inoltre una serie di dati statistici riassuntivi.\n");
                  printf(" '-b'  è l'opzione che genera questa funzione.\n");
                  printf(" '1000 e 5000'  costituiscono i valori minimo e massimo della serie.\n");
                  printf(" '5'  indica il numero di suddivisioni della serie.\n");
                  printf(" (Se il numero  di suddivisioni in sotto-liste  non è specificato, viene\n");
                  printf(" considerato sempre uguale a due).\n");
                  printf(" Esempio (lista completa):\n");
                  printf(" Serie da  1000 a  1799 - Numeri Primi  110 - Numeri Divisibili  690\n");
                  printf(" Serie da  1800 a  2599 - Numeri Primi  100 - Numeri Divisibili  700\n");
                  printf(" Serie da  2600 a  3399 - Numeri Primi  100 - Numeri Divisibili  700\n");
                  printf(" Serie da  3400 a  4199 - Numeri Primi   96 - Numeri Divisibili  704\n");
                  printf(" Serie da  4200 a  4999 - Numeri Primi   95 - Numeri Divisibili  705\n");
                  printf(" Segue poi il rapporto statistico riassuntivo.\n\n");
                  printf(" %s %s     Rapporto riassuntivo finale:\n",nprg,verrel);
                  printf(" -----------------------------------------------\n");
                  printf(" Selezione dal numero:                      1000\n");
                  printf(" Al numero:                                 4999\n");
                  printf(" Totale numeri primi:                        501\n");
                  printf(" Totale dei numeri divisibili:              3499\n");
                  printf(" Lunghezza della serie numerica:            4000\n");
                  printf(" Numero delle serie numeriche:                 5\n");
                  printf(" Intervallo numerico delle serie:            800\n");
                  printf(" Media dei numeri primi delle serie:         100\n");
                  printf(" Media dei n. divsibili delle serie:         700\n");
                  printf(" Minimo di numeri primi nelle serie:          95\n");
                  printf(" Massimo di numeri primi nelle serie:        110\n");
                  printf(" Minimo di numeri divisibili nelle serie:    690\n");
                  printf(" Massimo di numeri divisibili nelle serie:   705\n\n");
                  printf(" %s -v 2500 2999 7\n",nprg);
                  printf(" Visualizza una lista selettiva  di numeri divisibili con i loro fattori\n");
                  printf(" primi da  un intervallo specifificato. Il fattore primo indicato deter-\n");
                  printf(" mina la formazione della serie visualizzata.\n");
                  printf(" '-v'  è l'opzione; '2500 2999'  è l'intervallo della serie specificata;\n");
                  printf(" '7'  è il fattore primo che determina la formazione della lista stessa.\n");
                  printf(" Nell'esempio qui riportato si ottiene (lista parziale):\n");
                  printf(" ...\n");
                  printf("  2527 = 7 (19^2)\n");
                  printf("  2569 = 7 367\n");
                  printf("  2597 = (7^2) 53\n");
                  printf("  2611 = 7 373\n");
                  printf("  2639 = 7 13 29\n");
                  printf(" ...\n\n");
                  printf(" %s -c 100001 5000 25\n",nprg);
                  printf(" Visualizza una lista selettiva da una serie  con i loro  fattori primi,\n");
                  printf(" con un intervallo di ampiezza non determinata di N elementi, un periodo\n");
                  printf(" ed un valore iniziale indicati.\n");
                  printf(" '-c' è l'opzione che genera questa funzione.\n");
                  printf(" '100001' è il valore iniziale della serie.\n");
                  printf(" '5000' è il periodo tra i valori della serie.\n");
                  printf(" '25' è il numero di elementi della lista da visualizzare.\n");
                  printf(" L'esempio indicato genera la seguente serie (lista parziale):\n");
                  printf(" ...\n");
                  printf("  110001 = 3 37 991\n");
                  printf("  115001\n");
                  printf("  120001 = (7^2) 31 79\n");
                  printf("  125001 = (3^2) 17 19 43\n");
                  printf("  130001 = 71 1831\n");
                  printf("  135001 = 127 1063\n");
                  printf("  140001 = 3 23 2029\n");
                  printf(" ...\n\n");
                  printf(" %s -l 10000 75000\n",nprg);
                  printf(" Visualizza una lista pulita di soli numeri primi senza nessun altro\n");
                  printf(" elemento di disturbo, sia in testa che coda. I numeri primi sono visua-\n");
                  printf(" lizzati uno per riga. Questa forma di visualizzazione  è utile per pro-\n");
                  printf(" durre lunghe liste da redirigere su file, per successive  elaborazioni.\n");
                  printf(" Esempio di visualizzazione (lista parziale):\n");
                  printf(" ...\n");
                  printf("  74797\n");
                  printf("  74821\n");
                  printf("  74827\n");
                  printf("  74831\n");
                  printf("  74843\n");
                  printf("  74857\n");
                  printf(" ...\n");
                  printf("  74897\n");
                  printf("  74903\n");
                  printf("  74923\n");
                  printf(" ...\n\n");
                  printf(" %s -q 10000 75000\n",nprg);
                  printf(" Visualizza una lista pulita di tutti i numeri divisibili compresi nella\n");
                  printf(" serie indicata con tutti i loro fattori primi di scomposizione, in modo\n");
                  printf(" simile  a quello  dell'opzione '-f' senza tuttavia  nessun  elemento di\n");
                  printf(" disturbo, sia  in testa che in coda. Questa forma  di visualizzazione è\n");
                  printf(" utile  per produrre lunghe liste  formattate  da redirigere su file per\n");
                  printf(" successive elaborazioni.\n");
                  printf(" Esempio di visualizzazione (lista parziale):\n");
                  printf(" ...\n");
                  printf("  49720 = (2^3) 5 11 113 \n");
                  printf("  49721 = 7 7103\n");
                  printf("  49722 = 2 3 8287\n");
                  printf("  49723 = 19 2617\n");
                  printf("  49724 = (2^2) 31 401\n");
                  printf("  49725 = (3^2) (5^2) 13 17\n");
                  printf("  49726 = 2 (23^2) 47\n");
                  printf("  49728 = (2^6) 3 7 37\n");
                  printf(" ...\n");
                  printf("  74995 = 5 53 283\n");
                  printf("  74996 = (2^2) 18749\n");
                  printf("  74997 = (3^2) 13 641\n");
                  printf("  74998 = 2 7 11 487\n");
                  printf(" ...\n\n");
                  printf(" %s -qL 1000001 1065535 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -lL 1000001 1065535 >> percorso/nome_del_file\n",nprg);
                  printf(" Accodano al file indicato, o lo generano se non esiste, rispettivanente\n");
                  printf(" una lista pura di tutti i valori della serie con tutti i loro fattori \n");
                  printf(" primi di scomposizione (-q), oppure una lista di tutti i numeri primi\n");
                  printf(" compresi nella serie (-l).\n\n");
                  printf(" %s -qL 98765 98770\n",nprg);
                  printf(" Visualizza una lista  di numeri divisibili  ed i loro  fattori primi di\n");
                  printf(" scomposizione senza intestazione iniziale e rapposto statistico finale.\n");
                  printf(" Inoltre, viene effettuata una particolare  identazione  che permette di\n");
                  printf(" aggiungere più liste in un unico file con soluzione di continuità quan-\n");
                  printf(" do si usa la redirezione.\n");
                  printf(" Esempio di visualizzazione (lista completa):\n");
                  printf("       98765 = 5 19753\n");
                  printf("       98766 = 2 (3^3) 31 59\n");
                  printf("       98767 = 283 349\n");
                  printf("       98768 = (2^4) 6173\n");
                  printf("       98769 = 3 11 41 73\n");
                  printf("       98770 = 2 5 7 17 83\n\n");
                  printf(" %s -lL 987654321 987654399\n",nprg);
                  printf(" Visualizza unicamente una lista di numeri primi senza intestazione ini-\n");
                  printf(" ziale e rapporto statistico finale. Inoltre viene effettuata una parti-\n");
                  printf(" colare identazione che permette di aggiungere più liste in un unico fi-\n");
                  printf(" le con soluzione di continuità quando si usa la redirezione.\n");
                  printf(" Esempio di visualizzazione (lista completa):\n");
                  printf("   987654323\n");
                  printf("   987654337\n");
                  printf("   987654347\n");
                  printf("   987654359\n");
                  printf("   987654361\n");
                  printf("   987654377\n");
                  printf("   987654379\n");
                  printf("   987654383\n\n");
                  printf(" %s -fS 1000 9999 3 | less\n",nprg);
                  printf(" Utilizza una pipe con il comando di sistema 'less' per visualizzare una\n");
                  printf(" pagina o una riga per volta. L'opzione '-fS' permette di evidenziare il\n");
                  printf(" primo fattore di scomposizione indicato.\n\n");
                  printf(" Alle opzioni '-n' e '-p'  è associabile lo Switch 'T'  per ottenere una\n");
                  printf(" visualizzazione tabellare, come mostrato negli esempi sotto riportati.\n");
                  printf(" Le opzioni '-nT' e '-pT'  permettono di computare delle serie numeriche\n");
                  printf(" con lunghezza fino a 262144 elementi per volta.\n\n");
                  printf(" %s -nT 99 999\n",nprg);
                  printf(" Visualizza solo la successione di tutti i numeri divisibili della serie\n");
                  printf(" indicata, disposti su più colonne. Esempio (Lista parziale):\n");
                  printf("   99    100    102    104    105    106    108    110\n");
                  printf("  111    112    114    115    116    117    118    119\n");
                  printf("  120    121    122    123    124    125    126    128\n");
                  printf(" ...\n");
                  printf("  964    965    966    968    969    970    972    973\n");
                  printf("  974    975    976    978    979    980    981    982\n");
                  printf("  984    985    986    987    988    989    990    992\n");
                  printf("  993    994    995    996    998    999\n\n");
                  printf(" %s -pT 99 999\n",nprg);
                  printf(" Visualizza solo  la successione di tutti i numeri primi della serie in-\n");
                  printf(" dicata, disposti su più colonne. Esempio (Lista parziale):\n");
                  printf("  101    103    107    109    113    127    131    137\n");
                  printf("  139    149    151    157    163    167    173    179\n");
                  printf("  181    191    193    197    199    211    223    227\n");
                  printf(" ...\n");
                  printf("  887    907    911    919    929    937    941    947\n");
                  printf("  953    967    971    977    983    991    997\n\n");
                  printf(" Qui di seguito  sono riportate  tutte le combinazioni  che sono ammesse\n");
                  printf(" tra le varie  opzioni  ed i relativi segnalatori  e/o Switch,  oltre al\n");
                  printf(" numero  di argomenti richiesto. Negli esempi  sono utilizzati valori di\n");
                  printf(" riferimento realistici.  Ogni serie può contenere fino ad un massimo di\n");
                  printf(" 65536 valori. Il valore massimo assoluto analizzabile è: 4294967295\n");
                  printf(" Esempio di calcolo di una serie con il massimo numero di elementi:\n");
                  printf(" (150000 + 65535 - 1) = 215535,  oppure: (500000 - 65535 + 1) = 434465\n");
                  printf(" %s -f 150000 215535\n",nprg);
                  printf(" %s -f 434465 500000\n\n",nprg);
                  printf(" Lista delle opzioni e Switch disponibili di %s:\n",nprg);
                  printf(" %s 1234567890\n",nprg);
                  printf(" %s 1234567890 1234567890\n",nprg);
                  printf(" %s 12345 54321\n",nprg);
                  printf(" %s -t 987654321 987667890\n",nprg);
                  printf(" %s -y 1 65535\n",nprg);
                  printf(" %s -s 1 65535\n",nprg);
                  printf(" %s -f 1 65535\n",nprg);
                  printf(" %s -yP 65536 131071\n",nprg);
                  printf(" %s -sP 65536 131071\n",nprg);
                  printf(" %s -fP 65536 131071\n",nprg);
                  printf(" %s -yS 65535 131070 17\n",nprg);
                  printf(" %s -sS 65535 131070 17\n",nprg);
                  printf(" %s -fS 65535 131070 17\n",nprg);
                  printf(" %s -yU 65536 131071 11\n",nprg);
                  printf(" %s -sU 65536 131071 11\n",nprg);
                  printf(" %s -fU 65536 131071 11\n",nprg);
                  printf(" %s -yD 65537 131072 5\n",nprg);
                  printf(" %s -sD 65537 131072 5\n",nprg);
                  printf(" %s -fD 65537 131072 5\n",nprg);
                  printf(" %s -d 100000 150000\n",nprg);
                  printf(" %s -d 100000 150000\n",nprg);
                  printf(" %s -d 100000 150000\n",nprg);
                  printf(" %s -dS 10000 500000 7\n",nprg);
                  printf(" %s -dU 10000 500000 13\n",nprg);
                  printf(" %s -dD 10000 500000 3\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -kS 35000 100535 23\n",nprg);
                  printf(" %s -kU 35000 100535 19\n",nprg);
                  printf(" %s -kD 35000 100535 11\n",nprg);
                  printf(" %s -p 4050000 4099999\n",nprg);
                  printf(" %s -pT 450000 499999\n",nprg);
                  printf(" %s -n 4050000 4099999\n",nprg);
                  printf(" %s -nT 450000 499999\n",nprg);
                  printf(" %s -l 774579999 774629999\n",nprg);
                  printf(" %s -lL 74579999 74629999\n",nprg);
                  printf(" %s -q 774579999 774629999\n",nprg);
                  printf(" %s -qL 74579999 74629999\n",nprg);
                  printf(" %s -b 5050000 5099999\n",nprg);
                  printf(" %s -b 9050000 9115000 20\n",nprg);
                  printf(" %s -c 1111111 123 40\n",nprg);
                  printf(" %s -v 9000000 9065534 7\n",nprg);
                  printf(" %s -h\n",nprg);
                  printf(" %s -?\n",nprg);
                  printf(" %s -?I\n",nprg);
                  printf(" %s -?M\n",nprg);
                  printf(" %s -?M0\n",nprg);
                  printf(" %s -?M1\n",nprg);
                  printf(" %s -?F\n",nprg);
                  printf(" %s --help\n\n",nprg);
                  printf(" Note:\n");
                  printf(" Sebbene le opzioni  ed i segnalatori, o Switch, si possano scrivere in-\n");
                  printf(" differentemente sia  in minuscolo che maiuscolo, è consigliabile tutta-\n");
                  printf(" via scrivere l'opzione  in minuscolo, ed  il segnalatore in  maiuscolo.\n");
                  printf(" Il segnalatore, quando serve, deve sempre  essere scritto dopo l'opzio-\n");
                  printf(" ne: non è possibile  anteporre  un segnalatore all'opzione. Solo alcune\n");
                  printf(" opzioni  permettono l'uso di un segnalatore.  Ogni opzione  deve essere\n");
                  printf(" preceduta a sua volta  dal trattino orrizzontale, altrimenti  viene ri-\n");
                  printf(" conosciuta come  argomento numerico, salvo nel caso di  EN, IT, ES, FR,\n");
                  printf(" PT e DE che sono opzioni paricolari per l'impostazione della lingua lo-\n");
                  printf(" cale e quindi «vanno usate così come sono» senza anteporvi il trattino.\n");
                  printf("========================================================================\n\n");
               }
               else if(lang==ENGLISH) {
                  printf("\n =======================================================================\n");
                  printf("              %s v.%s   -   Quick Guide.\n",nprg,verrel);
                  printf("  This program permits to decompose natural number in their prime factor\n");
                  printf(" Research prime number and permit to notice some caracteristics of their\n");
                  printf(" distribution. The programme  is structured to be  executed from a Shell\n");
                  printf(" and it's presents in a simil mode to a sistem command.\n");
                  printf(" It have  a lot of options which  they differentiate  both the visualis-\n");
                  printf(" ation and the  operating  mode. Is possible to  define lists  of number\n");
                  printf(" from  decompose in their prime factor  or from research  into their the\n");
                  printf(" relative  prime number. Every list can have a maximum capacyty of elem-\n");
                  printf(" ents, whereas  the  tallest number, modular  in prime factor, in  which\n");
                  printf(" it's supplied a correct result is 4294967296.\n");
                  printf("  The program  only have a didactics end goal can also be used when it's\n");
                  printf(" need  to know  prime factor  of decomposition  of a divisible number or\n");
                  printf(" know if a determinated value is prime or not.\n");
                  printf("  The algoritm that generates prime factor (prime numbers and decomposi-\n");
                  printf(" tion factors) has been  extensively tested and always  provides absolu-\n");
                  printf(" tely exact and context-consistent result.\n");
                  printf(" At the moment there do not appear to be any particular problems, however\n");
                  printf(" may still be some failures, at a general level, in the functionality of\n");
                  printf(" the program itself, not yet discovered.\n");
                  printf(" The program is provided  «as is»  without any form  of warranty, either\n");
                  printf(" express or implied. The author declines all responsibility  for any da-\n");
                  printf(" mage resulting from improper use outside a purely educational and/or .\n");
                  printf(" informational context.\n");
                  printf(" Examples of key features:\n\n");
                  printf(" %s 911\n",nprg);
                  printf(" Display itself and all its prime factor if the number itself is divisi-\n");
                  printf(" ble, otherwise  only itself if it is  a prime number, as shown  in this\n");
                  printf(" example: 911  (this is a prime number).\n\n");
                  printf(" %s -y 4096\n",nprg);
                  printf(" Displays itself and the first factor of decomposition, as shown in this\n");
                  printf(" example:  4096 = 2  (the number is divisible by two).\n\n");
                  printf(" %s -s 4500\n",nprg);
                  printf(" Displays itself and its prime factors of decomposition in single format\n");
                  printf(" optionally  repeated for each prime factor, in the following  exemplary\n");
                  printf(" way: 4500 = 2 2 3 3 5 5 5\n");
                  printf(" Note: 2 2 3 3 5 5 5 correspond to 2 x 2 x 2 x 3 x 3 x 5 x 5 x 5\n\n");
                  printf(" %s -f 123456\n",nprg);
                  printf(" Displays itself and its prime factors in exponential format as shown in\n");
                  printf(" the example: 123456 = (2^6) 3 643\n");
                  printf(" Note:  (2^6) 3 643  need to be red two raised to the sixth  moltiplica-\n");
                  printf(" ted per three  moltiplicated per sixhundred and forty-three.\n\n");
                  printf(" %s 1000 9999\n",nprg);
                  printf(" The numbers 1000  and 9999  represent the minimum and maximum  extremes\n");
                  printf(" included in the numerical series indicated to be computed. The extremes\n");
                  printf(" indicated are part of the series, the length of which will be.\n");
                  printf(" Display all the numbers included in the indicated series and all their\n");
                  printf(" prime factor  of decomposition, also  highlitghing  the sequence of all\n");
                  printf(" the prime numbers contained in it, as show in the following example:\n");
                  printf(" (Partial list)\n");
                  printf("  1000 = (2^3) (5^3)\n");
                  printf("  1001 = 7 11 13\n");
                  printf(" ...\n");
                  printf("  1007 = 19 53\n");
                  printf("  1008 = (2^4) (3^2) 7\n");
                  printf(" 1009\n");
                  printf("  1010 = 2 5 101\n");
                  printf(" ...\n");
                  printf("  9996 = (2^2) 3 (7^2) 17 \n");
                  printf("  9997 = 13 769\n");
                  printf("  9998 = 2 4999 \n");
                  printf("  9999 = (3^2) 11 101\n\n");
                  printf(" %s -y 123456 123499\n",nprg);
                  printf(" Display in sequence a list  composed from the same number followed from\n");
                  printf(" the first factor  of decompostion. If the prime number  dont get visua-\n");
                  printf(" lized  obviusly  none prime factor  of decomposition, like  in the fol-\n");
                  printf(" lowing example (Partial list):\n");
                  printf("   123456 = 2\n");
                  printf("   123457\n");
                  printf("   123458 = 2\n");
                  printf(" ...\n");
                  printf("   123461 = 13\n");
                  printf("   123462 = 2\n");
                  printf("   123463 = 331\n");
                  printf(" ...\n");
                  printf("   123478 = 2\n");
                  printf("   123479\n");
                  printf("   123480 = 2\n");
                  printf("   123481 = 19\n");
                  printf(" ...\n");
                  printf("   123497 = 11\n");
                  printf("   123498 = 2\n");
                  printf("   123499\n\n");
                  printf(" %s -s 123456 123499\n",nprg);
                  printf(" Displays in sequence all the numbers of the given series, each followed\n");
                  printf(" by all its prime factors. If a number is prime then nothing is display-\n");
                  printf(" ed after that number.\n");
                  printf(" The prime factors of decomposition are all displayed individually, even\n");
                  printf(" repeated, if necessary.\n");
                  printf(" Each prime factor is separated from the previous one by space.\n");
                  printf(" Example (partial list):\n");
                  printf("   123456 = 2 2 2 2 2 2 3 643\n");
                  printf("   123457\n");
                  printf("   123458 = 2 61729\n");
                  printf("   123459 = 3 7 5879\n");
                  printf("   123460 = 2 2 5 6173\n");
                  printf("   123461 = 13 9497\n");
                  printf("   123462 = 2 3 3 19 19 19\n");
                  printf("   123463 = 331 373\n");
                  printf("   123464 = 2 2 2 11 23 61\n");
                  printf(" ...\n");
                  printf("   123497 = 11 103 109\n");
                  printf("   123498 = 2 3 3 3 2287\n");
                  printf("   123499\n\n");
                  printf(" %s -f 1000 1110\n",nprg);
                  printf(" Display in sequence every number of the indicated series every of which\n");
                  printf(" followed from  every his prime factor. If a number is prime doesn't get\n");
                  printf(" visualized anything after the same number.\n");
                  printf(" It is similar to the -s option with the difference that each single re-\n");
                  printf(" peated prime factoris displayed in exponential notation.\n");
                  printf(" Example: [1000 = (2^3) (5^3)]  instead of: [1000 = 2 2 2 5 5 5]\n");
                  printf(" '-f' is the option that generates this function.\n");
                  printf(" '1000' and '1110' are the extreme values, respectively minimum and max-\n");
                  printf(" imum, of the series to be computed and displayed.\n\n");
                  printf(" %s -fS 1000 1110 17\n",nprg);
                  printf(" Display the sequence  and every factor of decomposition of every number\n");
                  printf(" of the series included the prime number, highlighting  the first factor\n");
                  printf(" divisible  of every number  of the  series egual  to that indicated  as\n");
                  printf(" discriminated.\n\n");
                  printf(" -fS'  indicate the option and the switch.\n");
                  printf(" '1000 e 1110'  costituted the minimun and maximum factor of the series.\n");
                  printf(" '17' is the first factor of decomposition discriminated referred to the\n");
                  printf("  switch 'S' in case specificated.\n");
                  printf(" further that up indicated -f allow also the following switch of discri-\n");
                  printf(" mination: 'P' (First), 'U' (Above) e 'D' (Under).\n");
                  printf(" In the example here reported (partial list):\n");
                  printf("   1000 = (2^3) (5^3)\n");
                  printf("   1001 = 7 11 13\n");
                  printf("   1002 = 2 3 167\n");
                  printf(" > 1003 = 17 59\n");
                  printf("   1004 = (2^2) 251\n");
                  printf(" ...\n");
                  printf("   1008 = (2^4) (3^2) 7\n");
                  printf("   1009\n");
                  printf("   1010 = 2 5 101\n");
                  printf("   1011 = 3 337\n");
                  printf(" ...\n");
                  printf(" the prime number 1003 is precede  '>'  because his initial prime factor\n");
                  printf(" of decomposition is exactly 17.\n\n");
                  printf(" A statistical report on the calculated series follows:\n\n");
                  printf(" %s %s            Final summary report:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf("Total series of numbers:                      111\n");
                  printf("Total prime numbers:                           18\n");
                  printf("Total divisibles numbers:                      93\n");
                  printf("Highest initial prime factor:                  29\n");
                  printf("Prime factor selected:                         17\n");
                  printf("Quantity of selected values:                    2\n");
                  printf("Maximum distance between prime numbers:        18\n");
                  printf("Average distance between prime numbers:         4\n\n");
                  printf(" Almost all options display  a final statistics report,  except the '-l'\n");
                  printf(" and '-q' options which do not provide one specifically.\n");
                  printf(" Each option displays  a different statistical report  depending  on the\n");
                  printf(" computation performed and the chosen view.\n");
                  printf(" The option '-y', '-s', '-f' allow also the following switches:\n");
                  printf(" 'S' (Selection) highlitgh with '>'  the prime factor indicated.\n");
                  printf(" 'P' (Prime) highlight with '>'  every prime number.\n");
                  printf(" 'U' (Above) highlight with '>'  every prime factor  major  or  egual as\n");
                  printf(" prime factor of referement.\n");
                  printf(" 'D' (Below) highlight with '>'  every prime factor  minor  or egual  as\n");
                  printf(" prime factor of referement.\n\n");
                  printf(" In addition to the switches listed above: 'S', 'P', 'U'  and 'D', there\n");
                  printf(" are also switches  'L' e 'T'  which are specific  to the following opt-\n");
                  printf(" ions: '-l', '-q', '-p' e '-n'.\n");
                  printf(" The above switches: 'P', S', 'U' e 'D', can be applied indifferently\n");
                  printf(" to the following options: '-y', '-s' ed '-f'.\n");
                  printf(" The '-d' e '-k' options only accept switches: 'S', 'U', e 'D'.\n");
                  printf(" The '-t', '-b', '-c', '-v' e -k options do not accept any switches.\n");
                  printf(" The 'P' switch cannot be applied to '-d' e '-k' options.\n");
                  printf(" The 'L' switch can only be applied to '-l' e '-q' options.\n");
                  printf(" The 'T' switch can only be applied to '-n' e '-p' options.\n");
                  printf(" These options are listed below.\n\n");
                  printf(" %s -n 12344 12349\n",nprg);
                  printf(" Display  only  divisible number  of the series, if it's  a prime number\n");
                  printf(" don't get visualized, but is left a empty space in the list.\n");
                  printf(" Example (Partial list):\n");
                  printf("  12344\n");
                  printf("  12345\n");
                  printf("  12346\n");
                  printf("\n");
                  printf("  12348\n");
                  printf("  12349\n");
                  printf(" In the example the prime number 123457 doesn't get visualized.\n\n");
                  printf(" %s -d 12344 12388\n",nprg);
                  printf(" Display only divisible number  which every of their prime factor of de-\n");
                  printf(" composition  included in the indicated series, as happen  in the series\n");
                  printf(" '-f', but here the prime number are ignored.\n\n");
                  printf(" Example (partial list):\n");
                  printf(" ...\n");
                  printf("   12344 = (2^3) 1543\n");
                  printf("   12345 = 3 5 823\n");
                  printf("   12346 = 2 6173\n");
                  printf("   12348 = (2^2) (3^2) (7^3)\n");
                  printf("   12349 = 53 233\n");
                  printf("   12350 = 2 (5^2) 13 19\n");
                  printf("   12351 = 3 23 179\n");
                  printf("   12352 = (2^6) 193\n");
                  printf(" ...\n");
                  printf(" As you can see the prime number 12347 get totally ignorated.\n\n");
                  printf(" %s -p 99 999\n",nprg);
                  printf(" Display only the sequence  of every prime number included  in the indi-\n");
                  printf(" cated series. And the complementary option at the '-d'.\n\n");
                  printf(" Example (partial list):\n");
                  printf("  101\n");
                  printf("  103\n");
                  printf(" ...\n");
                  printf("  757\n");
                  printf("  761\n");
                  printf("  769\n");
                  printf("  773\n");
                  printf("  787\n");
                  printf("  797\n");
                  printf("  809\n");
                  printf(" ...\n");
                  printf("  991\n");
                  printf("  997\n");
                  printf(" %s -k 115 145\n",nprg);
                  printf(" Display a list of divisible numbers where the prime factors are  always\n");
                  printf(" only two.  It is  similar to the '-d' option  except that  only numbers \n");
                  printf("that have exactly two divisors are displayed.\n");
                  printf(" Example (partial list):");
                  printf("   115 = 5 23\n");
                  printf("   118 = 2 59\n");
                  printf("   119 = 7 17\n");
                  printf("   121 = (11^2)\n");
                  printf("   122 = 2 61\n");
                  printf(" ...\n");
                  printf("   141 = 3 47\n");
                  printf("   142 = 2 71\n");
                  printf("   143 = 11 13\n");
                  printf("   145 = 5 29\n\n");
                  printf(" %s -t 1 65535\n",nprg);
                  printf(" Display only a statistic rapport of the data aggregated referred to the\n");
                  printf(" series of value indicated.\n");
                  printf(" The rapport include some voices which indicat the total rapport  of the\n");
                  printf(" processed value, the number  of the  prime factor  and of the divisible\n");
                  printf(" one of the series, of the starter tallest  decomposition factor, of the\n");
                  printf(" maximum distance from two prime number, and still other.\n");
                  printf(" Example:\n\n");
                  printf(" %s %s             Final summary report:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf(" Selection by number:                            1\n");
                  printf(" At number:                                  65535\n");
                  printf(" Total series of numbers:                    65535\n");
                  printf(" Total prime numbers:                         6542\n");
                  printf(" Total divisibles numbers:                   58992\n");
                  printf(" Highest initial prime factor:                 251\n");
                  printf(" Maximum distance between prime numbers:        72\n");
                  printf(" Average distance between prime numbers:         6\n\n");
                  printf(" %s -b 1000 5000 5\n",nprg);
                  printf(" Display aggregated file of the series  of the value from a range of va-\n");
                  printf(" lue specificated subdivision in under-list contiguous of arbitrary lar-\n");
                  printf(" geness. Display also a series of recapitulatory statistic date.\n");
                  printf(" '-b' is the option of the function.\n");
                  printf(" '1000 e 5000' establish the minimum and maximum value of the series.\n");
                  printf(" '5'  indicate the number of subdivision fo the series.\n");
                  printf(" (If the number  of subdivision in under-list  isn't specified, get con-\n");
                  printf(" siderated always alike to two).\n");
                  printf(" Example (whole list):\n");
                  printf(" Series from 1000 to 1799 - Prime numbers = 110 - Divisible numbers = 690\n");
                  printf(" Series from 1800 to 2599 - Prime numbers = 100 - Divisible numbers = 700\n");
                  printf(" Series from 2600 to 3339 - Prime numbers = 100 - Divisible numbers = 700\n");
                  printf(" Series from 3400 to 4199 - Prime numbers =  96 - Divisible numbers = 704\n");
                  printf(" Series from 4200 to 4999 - Prime numbers =  95 - Divisible numbers = 705\n");
                  printf(" The summary statistical report follows.\n\n");
                  printf(" %s %s                   Final summary report:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf(" Selection by number:                         1000\n");
                  printf(" At number:                                   4999\n");
                  printf(" Total prime numbers:                          501\n");
                  printf(" Total divisibles numbers:                    3499\n");
                  printf(" Lenght of the number series:                 4000\n");
                  printf(" Number of numerical series:                     5\n");
                  printf(" Numerical range of series:                    800\n");
                  printf(" Average of primes in the series:              100\n");
                  printf(" Average divisibles in the series:             700\n");
                  printf(" Minimum of prime numbers in the series:        95\n");
                  printf(" Maximum of prime numbers in the series:       110\n");
                  printf(" Minimum of divisible numbers in the series:   690\n");
                  printf(" Maximum of divisible numbers in the series:   705\n\n");
                  printf(" %s -v 250 2999 7\n",nprg);
                  printf(" Display a  selective list  of divisible number  with their prime factor\n");
                  printf(" from a range specificated. The prime factor indicated  define the form-\n");
                  printf(" ation of the visualized series .\n");
                  printf(" '-v' is the option; '250 2999' is the range of the specificated series;\n");
                  printf(" '7' is the  prime factor  which define the formation  of the same list.\n");
                  printf(" In the example here reported you get it (Partial list):\n");
                  printf(" ...\n");
                  printf("  2527 = 7 (19^2)\n");
                  printf("  2569 = 7 367\n");
                  printf("  2597 = (7^2) 53\n");
                  printf("  2611 = 7 373\n");
                  printf("  2639 = 7 13 29\n");
                  printf(" ...\n\n");
                  printf(" %s -c 100001 5000 25\n",nprg);
                  printf(" Display a selection list  from a series which their  prime factor, with\n");
                  printf(" a range  of  largeness  doesn't defined of  N  elements, a period and a\n");
                  printf(" starter value indicated.\n");
                  printf(" '-c' is the option that generates this function.\n");
                  printf(" '100001' is the initial value of the numeric series.\n");
                  printf(" '5000' is the period between the value of the number series.\n");
                  printf(" '25' is the number of list items to display.\n");
                  printf(" The given example generates the following series (Partial list):\n");
                  printf(" ...\n");
                  printf("  110001 = 3 37 991\n");
                  printf("  115001\n");
                  printf("  120001 = (7^2) 31 79\n");
                  printf("  125001 = (3^2) 17 19 43\n");
                  printf("  130001 = 71 1831\n");
                  printf("  135001 = 127 1063\n");
                  printf("  140001 = 3 23 2029\n");
                  printf(" ...\n\n");
                  printf(" %s -l 10000 75000\n",nprg);
                  printf(" Display  a cleaning list of only  prime number without none  other ele-\n");
                  printf(" ment of bother, both in head  and in tail. The prime numbers are visua-\n");
                  printf(" lized one  for line. This form  of visualisation  is useful per produce\n");
                  printf(" long list to be drafted on file, for next elaboration.\n");
                  printf(" Example display (partial list):\n");
                  printf(" ...\n");
                  printf("  74797\n");
                  printf("  74821\n");
                  printf("  74827\n");
                  printf("  74831\n");
                  printf("  74843\n");
                  printf("  74857\n");
                  printf(" ...\n");
                  printf("  74897\n");
                  printf("  74903\n");
                  printf("  74923\n");
                  printf(" ...\n\n");
                  printf(" %s -q 10000 75000\n",nprg);
                  printf(" Display a clearly list of every divisible number included in the series\n");
                  printf(" which every their prime factor of decomposition, in a similar way\n");
                  printf(" at that of the option '-f' without however none element of bother, both\n");
                  printf(" in head  and in tail. This form of visualisation  is useful  to produce\n");
                  printf(" long list formattated from drafted on file for next elaboration.\n");
                  printf(" Example display (partial list):\n");
                  printf(" ...\n");
                  printf("  49720 = (2^3) 5 11 113\n");
                  printf("  49721 = 7 7103\n");
                  printf("  49722 = 2 3 8287\n");
                  printf("  49723 = 19 2617\n");
                  printf("  49724 = (2^2) 31 401\n");
                  printf("  49725 = (3^2) (5^2) 13 17\n");
                  printf("  49726 = 2 (23^2) 47\n");
                  printf("  49728 = (2^6) 3 7 37\n");
                  printf(" ...\n");
                  printf("  74995 = 5 53 283\n");
                  printf("  74996 = (2^2) 18749\n");
                  printf("  74997 = (3^2) 13 641\n");
                  printf("  74998 = 2 7 11 487\n");
                  printf(" ...\n\n");
                  printf(" %s -qL 1000001 1065535 >> path/file_name\n",nprg);
                  printf(" %s -lL 1000001 1065535 >> path/file_name\n",nprg);
                  printf(" Queue to the  indicated file, or they produce it  if it doesn't  exist,\n");
                  printf(" respectively a pure list of every value of the series  with every their\n");
                  printf(" prime factor  of decomposition (-q), or a  list of every  prime numbers\n");
                  printf(" included in the serie (-l).\n\n");
                  printf(" %s -qL 98765 98770\n",nprg);
                  printf(" Display a list of  divisible numbers  and their  prime factors, without\n");
                  printf(" initial header  and  final statistical report. Additionally, a  special\n");
                  printf(" identation is  performed  that allows you  to add multiple lists into a\n");
                  printf(" single file seamlessly when using output redirection.\n");
                  printf(" Example (full list):\n");
                  printf("  98765 = 5 19753\n");
                  printf("  98766 = 2 (3^3) 31 59\n");
                  printf("  98767 = 283 349\n");
                  printf("  98768 = (2^4) 6173\n");
                  printf("  98769 = 3 11 41 73\n");
                  printf("  98770 = 2 5 7 17 83\n\n");
                  printf(" %s -lL 987654321 987654399\n",nprg);
                  printf(" Display only a list  of prime numbers  without initial header and final\n");
                  printf(" statistical report. In addition, a special identation is performed that\n");
                  printf(" allows you to add multiple lists into a single file seamlessly when us-\n");
                  printf(" ing output redirection.\n");
                  printf(" Example (full list):\n");
                  printf("  987654323\n");
                  printf("  987654337\n");
                  printf("  987654347\n");
                  printf("  987654359\n");
                  printf("  987654361\n");
                  printf("  987654377\n");
                  printf("  987654379\n");
                  printf("  987654383\n\n");
                  printf(" %s -fS 1000 9999 3 | more\n",nprg);
                  printf(" Use a pipe  with the system command 'more' to display a page  or a line\n");
                  printf(" at a time. The option  '-fS'  permits to highlight  the first factor of\n");
                  printf(" decomposition indicated.\n\n");
                  printf(" The '-n' e '-p' options can be associated with the 'T' switch to obtain\n");
                  printf(" a tabular display, as shown in the examples below.\n\n");
                  printf(" %s -nT 99 999\n",nprg);
                  printf(" Display only the sequence of all divisible numbers of the given series\n");
                  printf(" arranged in multiple columns. Example (Partial list):\n");
                  printf("   99	   100	  102	   104	  105	   106	  108	   110\n");
                  printf("  111	   112	  114	   115	  116	   117	  118	   119\n");
                  printf("  120	   121	  122	   123	  124	   125	  126	   128\n");
                  printf(" ...\n");
                  printf("  964	   965	  966	   968	  969	   970	  972	   973\n");
                  printf("  974	   975	  976	   978	  979	   980	  981	   982\n");
                  printf("  984	   985	  986	   987	  988	   989	  990	   992\n");
                  printf("  993    994	  995	   996	  998	   999\n\n");
                  printf(" %s -pT 99 999\n",nprg);
                  printf(" Display only the sequence  of all prime number  of the given series ar-\n");
                  printf(" ranged in multiple columns. Example (Partial list):\n");
                  printf("  101    103    107    109    113    127    131    137\n");
                  printf("  139    149    151    157    163    167    173    179\n");
                  printf("  181    191    193    197    199    211    223    227\n");
                  printf(" ...\n");
                  printf("  887    907    911    919    929    937    941    947\n");
                  printf("  953    967    971    977    983    991    997\n");
                  printf(" Below are  all the combinations  that are  allowed  between the various\n");
                  printf(" options and the related switches in addition to the number of arguments\n");
                  printf(" reqired. In the examples below, real reference values have been used.\n");
                  printf(" Each series can  contain up to  maximum  of 65535  values. The absolute\n");
                  printf(" maximum value that can be used is: 4294967295\n");
                  printf(" Example of calculating a series with the maximum number of elements:\n");
                  printf(" (150000 + 65535 - 1) = 215535,  or: (500000 - 65535 + 1) = 434465\n");
                  printf(" %s -f 150000 215535\n",nprg);
                  printf(" %s -f 434465 500000\n\n",nprg);
                  printf(" List of available options and switches for %s:\n",nprg);
                  printf(" %s 1234567890\n",nprg);
                  printf(" %s 1234567890 1234567890\n",nprg);
                  printf(" %s 12345 54321\n",nprg);
                  printf(" %s -t 987654321 987667890\n",nprg);
                  printf(" %s -y 1 65535\n",nprg);
                  printf(" %s -s 1 65535\n",nprg);
                  printf(" %s -f 1 65535\n",nprg);
                  printf(" %s -yP 65536 131071\n",nprg);
                  printf(" %s -sP 65536 131071\n",nprg);
                  printf(" %s -fP 65536 131071\n",nprg);
                  printf(" %s -yS 65535 131070 17\n",nprg);
                  printf(" %s -sS 65535 131070 17\n",nprg);
                  printf(" %s -fS 65535 131070 17\n",nprg);
                  printf(" %s -yU 65536 131071 11\n",nprg);
                  printf(" %s -sU 65536 131071 11\n",nprg);
                  printf(" %s -fU 65536 131071 11\n",nprg);
                  printf(" %s -yD 65537 131072 5\n",nprg);
                  printf(" %s -sD 65537 131072 5\n",nprg);
                  printf(" %s -fD 65537 131072 5\n",nprg);
                  printf(" %s -d 100000 150000\n",nprg);
                  printf(" %s -d 100000 150000\n",nprg);
                  printf(" %s -d 100000 150000\n",nprg);
                  printf(" %s -dS 10000 500000 7\n",nprg);
                  printf(" %s -dU 10000 500000 13\n",nprg);
                  printf(" %s -dD 10000 500000 3\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -kS 35000 100535 23\n",nprg);
                  printf(" %s -kU 35000 100535 19\n",nprg);
                  printf(" %s -kD 35000 100535 11\n",nprg);
                  printf(" %s -p 4050000 4099999\n",nprg);
                  printf(" %s -pT 450000 499999\n",nprg);
                  printf(" %s -n 4050000 4099999\n",nprg);
                  printf(" %s -nT 450000 499999\n",nprg);
                  printf(" %s -l 774579999 774629999\n",nprg);
                  printf(" %s -lL 74579999 74629999\n",nprg);
                  printf(" %s -q 774579999 774629999\n",nprg);
                  printf(" %s -qL 74579999 74629999\n",nprg);
                  printf(" %s -b 5050000 5099999\n",nprg);
                  printf(" %s -b 9050000 9115000 20\n",nprg);
                  printf(" %s -c 1111111 123 40\n",nprg);
                  printf(" %s -v 9000000 9065534 7\n",nprg);
                  printf(" %s -h\n",nprg);
                  printf(" %s -?\n",nprg);
                  printf(" %s -?I\n",nprg);
                  printf(" %s -?M\n",nprg);
                  printf(" %s -?M0\n",nprg);
                  printf(" %s -?M1\n",nprg);
                  printf(" %s -?F\n",nprg);
                  printf(" %s --help\n",nprg);
                  printf(" Notes:\n");
                  printf(" Although the option  and the flag, or switch, the may  be write equally\n");
                  printf(" both in uppercase and in lowercase, is advisable however write the opt-\n");
                  printf(" ion in lowercase, and the switch in uppercase.\n");
                  printf(" The switch, when  it is needed, must  always be write  after the option\n");
                  printf(" it's not possible put before  a switch to the option. Only some options\n");
                  printf(" permits  the use  of the switch. Every option  must come first likewise\n");
                  printf(" from the horizontal hyphen, otherwise get recognise as numeric argument,\n");
                  printf(" except for  EN, IT, ES, FR, PT and DE  which are  particular options to\n");
                  printf(" the local language setting and so  «they need to be used so as they're»\n");
                  printf(" without put before the hyphen.\n");
                  printf("========================================================================\n\n");
               }
               else if(lang==ESPANOL) {
                  printf("\n ================================\n");
                  printf(" NO HAY MANUAL RÁPIDO EN ESPAÑOL,\n");
                  printf("    SOLO EN INGLÉS E ITALIANO.\n");
                  printf(" ================================\n\n");
               }
               else if(lang==FRANCAIS) {
                  printf("\n ========================================\n");
                  printf(" IL N'Y PAS DE MANUEL RAPIDE EN FRANÇAIS,\n");
                  printf("   SEULEMENT EN ANGLAIS ET EN ITALIEN.\n");
                  printf(" ========================================\n\n");
               }
               else if(lang==PORTUGUES) {
                  printf("\n =====================================\n");
                  printf(" NÁ0 HÁ UM MANUAL RÁPIDO EM PORTUGÛES,\n");
                  printf("      APENS EM INGLES E ITALIANO.\n");
                  printf(" =====================================\n\n");
               }
               else if(lang==DEUTCHE) {
                  printf("\n =============================================\n");
                  printf(" EINE KURZANLEITUNG AUF DEUTSCH GIBT ES NUCHT,\n");
                  printf("       NUR AUF ENGLISCH UND ITALIENISCH.\n");
                  printf(" =============================================\n\n");
               }
               else {

               /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
               /* delle funzionalità interne, delle opzioni e degli Switch. */
                  if(fsign)
                     printf("ERROR [QUICK-GUIDE] GURU MEDITATION\n\n");
                  return GURU;
               }
               return OK;
            }
         /* +++ */

            else {
            /* Se gli Switch sono diversi da: 'F', 'M' e 'I'. */
               if(subopt!=SSC&&subopt!=MAN&&subopt!=ISW&&subopt!=NUL) {

               /* Esecuzione se lo Switch è errato. */
               /* Visualizza [Errore: Switch errato!]. */
         		      errscode=ERRSBASE+lang+40;
         		      return(errorstype(&errscode));
         		   }
         	  }
         }
         else {

         /* Esecuzione se all'opzione seguono argomenti. */
            if((mark=='-'&&option=='?')&&argc!=2) {
               if(argc>2&&subopt!=NSWT) {
               /* Visualizza [Errore: Argomento errato e/o mancante!]. */
                  errscode=ERRSBASE+lang+110;
                  return(errorstype(&errscode));
               }

            /* Visualizza [Errore: Non è richiesto alcun argomento!]. */
               errscode=ERRSBASE+lang+130;
               return(errorstype(&errscode));
            }
         }
      /* Fine contributi. */

         /* Se l'opzione è '-H'. */
         if(mark=='-'&&option=='h'&&argc==2) {
         	  if(subopt!=NSWT) {

            /* Esecuzione se l'opzione è errata. */
            /* Visualizza [Errore: Opzione errata!]. */
            /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
         	     errscode=ERRSBASE+ERRSHIFT+lang+20;
         	     errorstype(&errscode);
         	     errscode=ERRSBASE+lang+240;
         	     return(errorstype(&errscode));
         	  }
            quickhelp(&lang,nprg);
            return OK;
         }
         else {

         /* Esecuzione se all'opzione seguono argomenti. */
            if((mark=='-'&&option=='h')&&argc!=2) {

            /* Visualizza [Errore: Non è richiesto alcun argomento!]. */
               errscode=ERRSBASE+lang+130;
               return(errorstype(&errscode));
            }
         }

      /* Help esteso -- Very Good! */
      /* Se l'opzione estesa è: '--HELP'. */
         if(mark=='-'&&option=='-'&&argc==2) {
            if(subopt==NSWT) {

            /* Esecuzione se l'opzione estesa è mancante. */
            /* Visualizza [Errore: Opzione mancante!]. */
               errscode=ERRSBASE+lang+30;
               return(errorstype(&errscode));
            }
            h=(char)tolower((int)argv[1][2]);
            e=(char)tolower((int)argv[1][3]);
            l=(char)tolower((int)argv[1][4]);
            p=(char)tolower((int)argv[1][5]);
            X=(char)tolower((int)argv[1][6]);
            help=(int)(h+e+l+p+X);   /* somma i codici delle lettere. */
            if(help==HELP) {         /* HELP=425, X=0. */
               if(h==104&&e==101&&l==108&&p==112) {
                  helpfunc(&lang,nprg,relrel);
                  return OK;
               }
            }

         /* Esecuzione se l'opzione (HELP) è errata. */
            if(*(*(argv+1)+6)!=NUL) {

            /* Visualizza [Errore: Opzione errata!]. */
               errscode=ERRSBASE+lang+20;
               return(errorstype(&errscode));
            }

         /* Visualizza [Errore: Opzione errata!]. */
            errscode=ERRSBASE+lang+20;
            return(errorstype(&errscode));
         }
         else {

         /* Esecuzione se all'opzione segue Switch errato. */
            if(mark=='-'&&option=='-'&&subopt!='H') {

            /* Visualizza [Errore: Opzione errata!]. */
               errscode=ERRSBASE+lang+20;
               (errorstype(&errscode));
            }

         /* Esecuzione se all'opzione '--' seguono argomenti. */
            if(mark=='-'&&option=='-'&&argc!=2) {

            /* Visualizza [Errore: Non è richiesto alcun argomento!]. */
               errscode=ERRSBASE+lang+130;
               return(errorstype(&errscode));
            }
         }
      /* ------------------------------------------------------------*/

      /* LBLERR_1 >> Errori su opzioni, Switch ed argomenti - INIZIO. */
      /* Segnalazione di errore, aggiuntiva a LBLERR_0. */
         if(trueoptions()==ZERO&&trueswitch()==NOSWT&&*(argv+2)==NULL) {

         /* Esecuzione se mancano l'opzione lo Switch e gli argomenti numerici. */
         /* Visualizza [Errore: Opzione, Switch ed argomenti mancanti!]. */
            errscode=ERRSBASE+lang+80;
            return(errorstype(&errscode));
         }
         if(trueoptions()==ZERO&&trueswitch()==NOSWT&&*(argv+2)!=NULL&&argc>=5) {

         /* Esecuzione se mancano solo l'opzione e lo Switch. */
         /* Visualizza [Errore: Opzione e Switch mancanti!]. */
            errscode=ERRSBASE+lang+0;
            return(errorstype(&errscode));
         }

      /* Se è presente un'opzione con lo Switch e nessun argomento. */
         if(trueoptions()!=ZERO&&trueswitch()!=NOSWT&&argc==2) {

         /* Controlla la presenza di Switch spuri. */
            if(*(*(argv+1)+3)!=NUL) {

            /* Esecuzione se esistono altri Switch oltre a quello che segue l'opzione. */
            /* Visualizza [Errore: Opzione errata!]. */
            /* Visualizza [Errore: Argomenti mancanti!]. */
               errscode=ERRSBASE+ERRSHIFT+lang+20;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+70;
               return(errorstype(&errscode));
            }

         /* Verifica la combinazione di tutte le opzioni con i relativi Switch. */
            if(switcherrs()==ERROR) {

            /* Per opzioni che richiedono almeno un argomento, con esclusione di '-H', '-?' e '--'. */
               if(option!=LINF&&option!=QHLP&&option!=EHLP) {

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-K', '-P', '-N', '-L' e '-Q'. */
                  if(trueoptions()>ZERO&&trueoptions()<FIVE) {
                     if(trueswitch()>=ERRSW) {

                     /* Esecuzione se lo Switch è errato. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+40;
                        errorstype(&errscode);
                     }
                     else {

                     /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                     /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+50;
                        errorstype(&errscode);
                     }
                  }
                  else if(trueoptions()>=ERRS&&trueswitch()<ERRSW) {

                  /* Esecuzione se l'opzione non appartiene al set in presenza di Switch valido. */
                  /* Visualizza [Errore: Opzione errata!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+20;
                     errorstype(&errscode);
                  }
                  else if(trueoptions()<ERRS&&trueswitch()>=ERRSW) {

                  /* Esecuzione se l'opzione non richiede alcun Switch. */
                  /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+240;
                     errorstype(&errscode);
                  }
                  else {

                  /* Se corrispondono alle seguenti opzioni: '-K', -T', '-B', '-V' e '-C'. */
                     if(globoptions()==GLOB1) {

                     /* Esecuzione se l'opzione non richiede alcun Switch. */
                     /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+240;
                        errorstype(&errscode);
                     }

                  /* Se corrispondono alle seguenti opzioni: */
                  /* '-Y', '-S', '-F', '-D', '-P', '-N, '-L', '-Q', '-K', '-T', '-B', '-V' e '-C'. */
                     if(trueoptions()>=HLP) {

                     /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
                     /* Visualizza [Errore: Opzione e/o Switch errati!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+10;
                        errorstype(&errscode);
                     }
                  }
               }
            }
            else {

            /* Esecuzione se l'opzione richiede altri argomenti numerici. */
            /* Visualizza [Errore: Argomenti mancanti!]. */
               errscode=ERRSBASE+lang+70;
               return(errorstype(&errscode));
            }
         }

      /* Se è presente solo l'opzione senza nessun Switch ed argomenti. */
         else {
            if(option!=NOPT&&subopt==NSWT&&argc==2) {
               if(switcherrs()>=ERROR) {
                  if(trueoptions()>=ERRS) {

                  /* Esecuzione se l'opzione non appartiene al set. */
                  /* Visualizza [Errore: Opzione errata!]. */
                  /* Visualizza [Errore: Argomento mancante!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+20;
                     errorstype(&errscode);
                     errscode=ERRSBASE+lang+60;
                     return(errorstype(&errscode));
                  }
               }
               else {
                  if(trueoptions()>ONE&&trueoptions()<TREE) {

                  /* Esecuzione se manca solo l'argomento numerico. */
                  /* Visualizza [Errore: Argomento mancante!]. */
                     errscode=ERRSBASE+lang+60;
                     return(errorstype(&errscode));
                  }
                  else {

                  /* Esecuzione se l'opzione richiede altri argomenti numerici. */
                  /* Visualizza [Errore: Argomenti mancanti!]. */
                     errscode=ERRSBASE+lang+70;
                     return(errorstype(&errscode));
                  }
               }
            }
         }

      /* Per le altre opzioni non processate. */
      /* Se è presente solo l'opzione e lo Switch, senza nessun argomento. */
         if(trueoptions()!=ZERO&&argc==2) {

         /* Esecuzione se mancano solo gli argomenti numerici. */
         /* Visualizza [Errore: Argomenti mancanti!]. */
            errscode=ERRSBASE+lang+70;
            return(errorstype(&errscode));
         }
      /* Se opzione e Switch sono entrambi presenti con tre argomenti numerici. */
         if(trueoptions()!=ZERO&&trueswitch()!=NOSWT&&(argc>=5)) {

         /* Verifica la combinazione di tutte le opzioni con i relativi Switch. */
            if(switcherrs()==ERROR) {

            /* Per opzioni che richiedono almeno un argomento, con esclusione di '-H', '-?' e '--'. */
               if(option!=LINF&&option!=QHLP&&option!=EHLP) {

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-P', '-N', '-L' e '-Q'. */
                  if(trueoptions()>ZERO&&trueoptions()<FIVE) {
                     if(trueswitch()>=ERRSW) {

                     /* Esecuzione se lo Switch è errato. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+40;
                        errorstype(&errscode);
                     }
                     else {

                     /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                     /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+50;
                        errorstype(&errscode);

                     /* Se lo Switch è in formato errato. */
                        if(trueoptions()<ERRS&&switcherrs()==ERROR) {

                        /* Esecuzione se lo Switch è errato. */
                        /* Visualizza [Errore: Switch errato!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+40;
                           errorstype(&errscode);
                        }
                     }
                  }
                  else if(trueoptions()>=ERRS&&trueswitch()<ERRSW) {

                  /* Esecuzione se l'opzione non appartiene al set in presenza di Switch valido. */
                  /* Visualizza [Errore: Opzione errata!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+20;
                     errorstype(&errscode);
                  }
                  else if(trueoptions()<ERRS&&trueswitch()>=ERRSW) {

                  /* Esecuzione se l'opzione non richiede alcun Switch. */
                  /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+240;
                     errorstype(&errscode);
                  }
                  else {

                  /* Se corrispondono alle seguenti opzioni: '-K', -T', '-B', '-V' e '-C'. */
                     if(globoptions()==GLOB1) {

                     /* Esecuzione se l'opzione non richiede alcun Switch. */
                     /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+240;
                        errorstype(&errscode);
                     }

                  /* Se corrispondono alle seguenti opzioni: */
                  /* '-Y', '-S', '-F', '-D', '-P', '-N, '-L', '-Q', '-K', '-T', '-B', '-V' e '-C'. */
                     if(trueoptions()>=HLP) {

                     /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
                     /* Visualizza [Errore: Opzione e/o Switch errati!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+10;
                        errorstype(&errscode);
                     }
                  }
               }
               else return(putchar('\n'));
            }
            if(argc>5) {

            /* Esecuzione se sono presenti troppi argomenti. */
            /* Visualizza [Errore: Troppi Argomenti!]. */
               errscode=ERRSBASE+lang+120;
               return(errorstype(&errscode));
            }
            else {

            /* Se sono presenti opzioni che richiedono solo due argomenti. */
               if(globoptions()==GLOB3||option==STAT) {

               /* Esecuzione se sono presenti troppi argomenti. */
               /* Visualizza [Errore: Troppi Argomenti!]. */
                  errscode=ERRSBASE+lang+120;
                  return(errorstype(&errscode));
               }

            /* Esecuzione per tutti gli altri casi di errore. */
               if(switcherrs()==ERROR)
                  return(putchar('\n'));
            }
         }

      /* Se opzione e Switch sono entrambi presenti con due argomenti. */
         if(trueoptions()!=ZERO&&trueswitch()!=NOSWT&&(argc==4)) {

         /* Verifica la combinazione di tutte le opzioni con i relativi Switch. */
            if(switcherrs()==ERROR) {

            /* Per opzioni che richiedono almeno un argomento, con esclusione di '-H', '-?' e '--'. */
               if(option!=LINF&&option!=QHLP&&option!=EHLP) {

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-P', '-N', '-L', '-Q' e '-K'. */
                  if(trueoptions()>ZERO&&trueoptions()<FIVE) {
                     if(trueswitch()>=ERRSW) {

                     /* Esecuzione se lo Switch è errato. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+40;
                        errorstype(&errscode);
                     }
                     else {

                     /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                     /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+50;
                        errorstype(&errscode);

                     /* Se lo Switch è in formato errato. */
                        if(trueoptions()<ERRS&&switcherrs()==ERROR) {

                        /* Esecuzione se lo Switch è errato. */
                        /* Visualizza [Errore: Switch errato!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+40;
                           errorstype(&errscode);
                        }
                     }
                  }
                  else if(trueoptions()>=ERRS&&trueswitch()<ERRSW) {

                  /* Esecuzione se l'opzione non appartiene al set in presenza di Switch valido. */
                  /* Visualizza [Errore: Opzione errata!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+20;
                     errorstype(&errscode);
                  }
                  else if(trueoptions()<ERRS&&trueswitch()>=ERRSW) {

                  /* Esecuzione se l'opzione non richiede alcun Switch. */
                  /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+240;
                     errorstype(&errscode);
                  }
                  else {

                  /* Se corrispondono alle seguenti opzioni: '-K', '-T', '-B', '-V' e '-C'. */
                     if(globoptions()==GLOB1) {

                     /* Esecuzione se l'opzione non richiede alcun Switch. */
                     /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+240;
                        errorstype(&errscode);
                     }

                  /* Se corrispondono alle seguenti opzioni: */
                  /* '-Y', '-S', '-F', '-D', '-P', '-N, '-L', '-Q', '-K', '-T', '-B', '-V' e '-C'. */
                     if(trueoptions()>=HLP) {

                     /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
                     /* Visualizza [Errore: Opzione e/o Switch errati!]. */
                        errscode=ERRSBASE+lang+10;
                        return(errorstype(&errscode));
                     }
                  }
               }
               if(globoptions()<=GLOB2&&(option!=BASE&&option!=STAT)) {

               /* Esecuzione se manca un solo argomento numerico. */
               /* Visualizza [Errore: Argomento mancante!]. */
                  errscode=ERRSBASE+lang+60;
                  return(errorstype(&errscode));
               }
               else return(putchar('\n'));
            }
            else {

            /* Se le opzioni sono diverse da '-P', '-L', '-Q', '-N', + '-T' e '-B'. */
               if(globoptions()!=GLOB3&&(option!=BASE&&option!=STAT)
                &&(subopt!=PME&&subopt!=LST)) {

               /* Esecuzione se manca un solo argomento numerico. */
               /* Visualizza [Errore: Argomento mancante!]. */
                  errscode=ERRSBASE+lang+60;
                  return(errorstype(&errscode));
               }
               else {

               /* Se una delle opzioni è presente nei due gruppi di globoptions(): */
               /* '-K', '-T', '-B', '-V', '-C'. */
                  if(globoptions()==GLOB1) {

                  /* Esecuzione se lo Switch non è previsto dall'opzione. */
                  /* Visualizza [Errore: l'opzione non accetta alcun tipo di Switch!]. */
                     errscode=ERRSBASE+lang+240;
                     return(errorstype(&errscode));
                  }
               }
            }
         }

      /* Se opzione e Switch sono entrambi presenti con un solo argomento. */
         if(trueoptions()!=ZERO&&trueswitch()!=NOSWT&&(argc==3)) {

         /* Verifica la combinazione di tutte le opzioni con i relativi Switch. */
            if(switcherrs()==ERROR) {

            /* Per opzioni che richiedono almeno un argomento, con esclusione di '-H', '-?' e '--'. */
               if(option!=LINF&&option!=QHLP&&option!=EHLP) {

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-P', '-N', '-L', '-Q' e '-K'. */
                  if(trueoptions()>ZERO&&trueoptions()<FIVE) {
                     if(trueswitch()>=ERRSW) {

                     /* Esecuzione se lo Switch è errato. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+40;
                        errorstype(&errscode);
                     }
                     else {

                     /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                     /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+50;
                        errorstype(&errscode);

                     /* Se lo Switch è in formato errato. */
                        if(trueoptions()<ERRS&&switcherrs()==ERROR) {

                        /* Esecuzione se lo Switch è errato. */
                        /* Visualizza [Errore: Switch errato!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+40;
                           errorstype(&errscode);
                        }
                     }
                  }
                  else if(trueoptions()>=ERRS&&trueswitch()<ERRSW) {

                  /* Esecuzione se l'opzione non appartiene al set in presenza di Switch valido. */
                  /* Visualizza [Errore: Opzione errata!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+20;
                     errorstype(&errscode);
                  }
                  else if(trueoptions()<ERRS&&trueswitch()>=ERRSW) {

                  /* Esecuzione se l'opzione non richiede alcun Switch. */
                  /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+240;
                     errorstype(&errscode);
                  }
                  else {

                  /* Se corrispondono alle seguenti opzioni: '-K', '-T', '-B', '-V' e '-C'. */
                     if(globoptions()==GLOB1) {

                     /* Esecuzione se l'opzione non richiede alcun Switch. */
                     /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+240;
                        errorstype(&errscode);
                     }

                  /* Se corrispondono alle seguenti opzioni: */
                  /* '-Y', '-S', '-F', '-D', '-P', '-N, '-L', '-Q', '-K' '-T', '-B', '-V' e '-C'. */
                     if(trueoptions()>=HLP) {

                     /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
                     /* Visualizza [Errore: Opzione e/o Switch errati!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+10;
                        errorstype(&errscode);
                     }
                  }
               }
               if((globoptions()==GLOB2&&trueswitch()>NOSWT)
                ||((globoptions()==GLOB1&&trueswitch()>NOSWT)
                &&(option!=STAT&&option!=BASE))) {

               /* Esecuzione se mancano solo gli argomenti numerici. */
               /* Visualizza [Errore: Argomenti mancanti]. */
                  errscode=ERRSBASE+lang+70;
                  return(errorstype(&errscode));
               }
               else {

               /* Esecuzione se manca un solo argomento numerico. */
               /* Visualizza [Errore: Argomento mancante!]. */
                  errscode=ERRSBASE+lang+60;
                  return(errorstype(&errscode));
               }
            }
            else {
               if(option!=BASE&&globoptions()!=GLOB3&&(subopt!=PME&&subopt!=LST)) {

               /* Esecuzione se mancano due o più argomenti numerici. */
               /* Visualizza [Errore: Argomenti mancanti!]. */
                  errscode=ERRSBASE+lang+70;
                  return(errorstype(&errscode));
               }
               else {

               /* Esecuzione se manca un solo argomento numerico. */
               /* Visualizza [Errore: Argomento mancante!]. */
                  errscode=ERRSBASE+lang+60;
                  return(errorstype(&errscode));
               }
            }
         }

      /* Se sono presenti solo l'opzione '-C' o l'opzione '-V' senza Switch con due argomenti. */
         if((trueoptions()==CMP||trueoptions()==VRL)&&trueswitch()==NOSWT&&argc==4) {

         /* Esecuzione se manca un solo argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* Se è presente l'opzione '-C' o l'opzione '-V' senza Switch e con un solo argomento. */
         if((trueoptions()==CMP||trueoptions()==VRL)&&trueswitch()==NOSWT&&(argc==3)) {

         /* Esecuzione se mancano due o più argomenti numerici. */
         /* Visualizza [Errore: Argomenti mancanti!]. */
            errscode=ERRSBASE+lang+70;
            return(errorstype(&errscode));
         }

      /* Se è presente l'opzione '-D', '-Q' oppure '-K' senza Switch e con un solo argomento. */
         if(trueoptions()==ONE&&trueswitch()==NOSWT&&(argc==3)) {

         /* Esecuzione se manca un argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* Se è presente l'opzione '-P' o l'opzione '-L' senza Switch e con un solo argomento. */
         if(trueoptions()==TREE&&trueswitch()==NOSWT&&(argc==3)) {

         /* Esecuzione se manca un argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* Se è presente l'opzione '-N' o l'opzione 'T' senza Switch e con un solo argomento. */
         if((trueoptions()==FOUR||trueoptions()==FIVE)
          &&trueswitch()==NOSWT&&(argc==3)) {

         /* Esecuzione se manca un argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* Esecuzione se le condizioni si sono verificate, valido per tutte le - */
      /* combinazioni di opzioni, Switch con numero di argomenti inferiore a tre. */
         if(trueoptions()>=ERRS&&trueswitch()>=ERRSW) {

         /* Esecuzione se l'opzione e lo Switch sono errati. */
         /* Visualizza [Errore: Opzione e/o Switch errati!]. */
            errscode=ERRSBASE+lang+10;
            return(errorstype(&errscode));
         }
         if(trueoptions()>=ERRS) {

         /* Esecuzione se l'opzione è errata. */
         /* Visualizza [Errore: Opzione errata!]. */
            errscode=ERRSBASE+lang+20;
            return(errorstype(&errscode));
         }
         if(trueswitch()>=ERRSW) {

         /* Esecuzione se lo Switch è errato. */
         /* Visualizza [Errore: Switch errato!]. */
            errscode=ERRSBASE+lang+40;
            return(errorstype(&errscode));
         }
         if(switcherrs()>=ERROR) {

         /* Esecuzione se lo Switch è usato con un opzione errata. */
         /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
            errscode=ERRSBASE+lang+50;
            return(errorstype(&errscode));
         }

      /* ------------------------------------------------------------------- */
      /* Controllo dei valori digitati se esiste solo un argomento numerico. */
      /* Una opzione è sempre presente. Non è mai presente uno Switch. */
         if(argc==3) {

         /* Controllo della lunghezza degli argomenti numerici. */
         /* E'unico argomento numerico previsto sempre preceduto da un'opzione. */
            if(argc==3&&isdigit(**(argv+2))) {
               for(a=0;a<=10;a++) {
                  if(isdigit(*(*(argv+2)+a))) {
                     if(*(*(argv+2)+(a+1))==NUL)
                        break;
                  }
               }
               if(a>=10) {

               /* Visualizza:[Errore: Ordine di grandezza superato!]. */
               /* Visualizza [Errore: Valore troppo grande!]. */
                  errscode=ERRSBASE+lang+260;
                  errorstype(&errscode);
                  errscode=ERRSBASE+lang+180;
                  return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per il primo ed unico argomento numerico. */
            if(!isdigit(**(argv+2))) {

            /* Visualizza [Errore: Argomento errato e/o mancante!]. */
               errscode=ERRSBASE+lang+100;
               return(errorstype(&errscode));
            }
            for(a=0;a<=10;a++) {
               if(isdigit(*(*(argv+2)+a))) {
                  if(*(*(argv+2)+(a+1))==NUL)
                     break;
               }
               if(*(*(argv+2)+(a+1))!=NUL&&!isdigit(*(*(argv+2)+(a+1)))) {

               /* Visualizza [Errore: Argomento errato!]. */
                  errscode=ERRSBASE+lang+90;
                  return(errorstype(&errscode));
               }
            }

         /* Se è presente un opzione compatibile con lo Switch 'P'. */
            if(trueoptions()!=ZERO&&trueswitch()==TRUEPM&&switcherrs()==OK) {

            /* Visualizza [Errore: Argomento mancante!]. */
               errscode=ERRSBASE+lang+60;
               return(errorstype(&errscode));
            }
         }

      /* ----------------------------------------------------------------- */
      /* Controllo dei valori digitati se esistono due argomenti numerici. */
      /* Una opzione è sempre presente. Può essere presente uno Switch. */
         if(argc==4) {

         /* Controllo della lunghezza degli argomenti numerici. */
         /* E'il primo argomento numerico sempre preceduto da un'opzione. */
            if(argc==4&&isdigit(**(argv+2))) {
               for(a=0;a<=10;a++) {
                  if(isdigit(*(*(argv+2)+a))) {
                     if(*(*(argv+2)+(a+1))==NUL)
                        break;
                  }
               }
               if(a>=10)
                  flgers+=1;
            }

         /* E' il secondo argomento numerico sempre preceduto da un'opzione. */
            if(argc==4&&isdigit(**(argv+3))) {
               for(b=0;b<=10;b++) {
                  if(isdigit(*(*(argv+3)+b))) {
                     if(*(*(argv+3)+(b+1))==NUL)
                        break;
                  }
               }
               if(b>=10)
               /* impostazione flag per visualizzazione errore. */
                  flgers+=1;
            }

         /* Visualizza il messaggio di errore in base allo stato del flag 'flgers'. */
         /* Se flgers = 0; nessun errore. Non visualizza nulla. */
         /* Se flgers = 1; Visualizza: [Errore: Valore troppo grande!]. */
         /* Se flgers = 2; Visualizza: [Errore: Valori troppo grandi!]. */
            if(flgers==1) {

            /* Visualizza:[Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valore troppo grande!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+180;
               return(errorstype(&errscode));
            }
            if(flgers==2) {

            /* Visualizza:[Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valori troppo grandi!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+210;
               return(errorstype(&errscode));
            }

         /* Controlla la presenza di Switch spuri sull'opzione. */
            if(!subopt) {    /* Se lo Switch è assente. */
               if(*(*(argv+1)+2)!=NUL) {

               /* Esecuzione se esistono altri Switch oltre a quello che segue l'opzione. */
               /* Visualizza [Errore: Opzione errata!]. */
                  errscode=ERRSBASE+lang+20;
                  return(errorstype(&errscode));
               }
            }
            else {    /* Se è presente uno Switch. */
               if(*(*(argv+1)+3)!=NUL) {

               /* Esecuzione se esistono altri Switch oltre a quello che segue l'opzione. */
               /* Visualizza [Errore: Opzione errata!]. */
                  errscode=ERRSBASE+lang+20;
                  return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per il primo dei due argomenti numerici. */
            if(!isdigit(**(argv+2))) {

            /* Visualizza [Errore: Argomento errato e/o mancante!]. */
               errscode=ERRSBASE+lang+100;
               return(errorstype(&errscode));
            }
            for(a=0;a<=10;a++) {
               if(isdigit(*(*(argv+2)+a))) {      /* Controlla la presenza di Switch spuri. */
                  if(*(*(argv+2)+(a+1))==NUL)
                     break;
               }
               if(*(*(argv+2)+(a+1))!=NUL&&!isdigit(*(*(argv+2)+(a+1)))) {

               /* Visualizza [Errore: Argomento errato!]. */
                  errscode=ERRSBASE+lang+90;
                  return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per il secondo dei due argomenti numerici. */
            if(!isdigit(**(argv+2))) {

            /* Visualizza [Errore: Argomento errato e/o mancante!]. */
               errscode=ERRSBASE+lang+100;
               return(errorstype(&errscode));
            }
            for(b=0;b<=10;b++) {
               if(isdigit(*(*(argv+3)+b))) {
                  if(*(*(argv+3)+(b+1))==NUL)
                     break;
               }
               if(*(*(argv+3)+(b+1))!=NUL&&!isdigit(*(*(argv+3)+(b+1)))) {

               /* Visualizza [Errore: Argomento errato!]. */
                  errscode=ERRSBASE+lang+90;
                  return(errorstype(&errscode));
               }
            }
         }
         else {

         /* Se esistono troppi argomenti numerici (1). */
            if(argc>4&&subopt==NSWT) {
               if(option!=BASE&&option!=VARS&&option!=CALC) {

               /* Visualizza [Errore: Troppi argomenti!]. */
                  errscode=ERRSBASE+lang+120;
                  return(errorstype(&errscode));
               }
            }
            if(argc>4&&subopt!=NSWT) {
               if(subopt==PME) {

               /* Visualizza [Errore: Troppi argomenti!]. */
                  errscode=ERRSBASE+lang+120;
                  return(errorstype(&errscode));
               }
            }
         }

      /* ----------------------------------------------------------------- */
      /* Controllo dei valori digitati se esistono tre argomenti numerici. */
      /* Una opzione è sempre presente. - Uno Switch è sempre presente. */
         if(argc==5) {

         /* Controllo della lunghezza degli argomenti numerici. */
         /* E'il primo argomento numerico sempre preceduto da un'opzione. */
            if(argc==5&&isdigit(**(argv+2))) {
               for(a=0;a<=10;a++) {
                  if(isdigit(*(*(argv+2)+a))) {
                     if(*(*(argv+2)+(a+1))==NUL)
                        break;
                  }
               }
               if(a>=10)
               /* impostazione flag per visualizzazione errore. */
                  flgers+=1;
            }

         /* E' il secondo argomento numerico sempre preceduto da un'opzione, */
            if(argc==5&&isdigit(**(argv+3))) {
               for(b=0;b<=10;b++) {
                  if(isdigit(*(*(argv+3)+b))) {
                     if(*(*(argv+3)+(b+1))==NUL)
                        break;
                  }
               }
               if(b>=10)
               /* impostazione flag per visualizzazione errore. */
                  flgers+=1;
            }

         /* E' il terzo argomento numerico sempre preceduto da un opzione. */
            if(argc==5&&isdigit(**(argv+4))) {
               for(c=0;c<=10;c++) {
                  if(isdigit(*(*(argv+4)+c))) {
                     if(*(*(argv+4)+(c+1))==NUL)
                        break;
                  }
               }
               if(c>=10)
               /* impostazione flag per visualizzazione errore. */
                  flgers+=1;
            }

         /* Visualizza il messaggio di errore in base allo stato del flag 'flgers' */
         /* Se flgers = 0; nessun errore. Non visualizza nulla. */
         /* Se flgers = 1; Visualizza: [Errore: Valore troppo grande!]. */
         /* Se flgers = 2; Visualizza: [Errore: Valori troppo grandi!]. */
         /* Se flgers = 3; Visualizza: [Errore: Valori troppo grandi!]. */
            if(flgers==1) {

            /* Visualizza:[Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valore troppo grande!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+180;
               return(errorstype(&errscode));
            }
            if(flgers>=2) {

            /* Visualizza:[Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valori troppo grandi!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+210;
               return(errorstype(&errscode));
            }

         /* Controlla la presenza di Switch non richiesti. */
            if(!subopt) {    /* Se lo Switch è assente. */
               if(*(*(argv+1)+2)!=NUL) {

               /* Esecuzione se esistono altri Switch oltre a quello che segue l'opzione. */
               /* Visualizza [Errore: Opzione errata!]. */
                  errscode=ERRSBASE+lang+20;
                  return(errorstype(&errscode));
               }
            }
            else {    /* Se è presente uno Switch. */
               if(*(*(argv+1)+3)!=NUL) {

                  /* Esecuzione se esistono altri Switch oltre a quello che segue l'opzione. */
                  /* Visualizza [Errore: Opzione errata!]. */
                     errscode=ERRSBASE+lang+20;
                     return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per il primo dei tre argomenti numerici. */
            if(!isdigit(**(argv+2))) {

            /* Visualizza [Errore: Argomento errato e/o mancante!]. */
               errscode=ERRSBASE+lang+100;
               return(errorstype(&errscode));
            }
            for(a=0;a<=10;a++) {
               if(isdigit(*(*(argv+2)+a))) {
                  if(*(*(argv+2)+(a+1))==NUL)
                     break;
               }
               if(*(*(argv+2)+(a+1))!=NUL&&!isdigit(*(*(argv+2)+(a+1)))) {

               /* Visualizza [Errore: Argomento errato!]. */
                  errscode=ERRSBASE+lang+90;
                  return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per il secondo dei tre argomenti numerici. */
            if(!isdigit(**(argv+3))) {

            /* Visualizza [Errore: Argomento errato e/o mancante!]. */
               errscode=ERRSBASE+lang+100;
               return(errorstype(&errscode));
            }
            for(b=0;b<=10;b++) {
               if(isdigit(*(*(argv+3)+b))) {
                  if(*(*(argv+3)+(b+1))==NUL)
                     break;
               }
               if(*(*(argv+3)+(b+1))!=NUL&&!isdigit(*(*(argv+3)+(b+1)))) {

               /* Visualizza [Errore: Argomento errato!]. */
                  errscode=ERRSBASE+lang+90;
                  return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per il terzo dei tre argomenti numerici. */
            if(!isdigit(**(argv+4))) {

            /* Visualizza [Errore: Argomento errato e/o mancante!]. */
               errscode=ERRSBASE+lang+100;
               return(errorstype(&errscode));
            }
            for(c=0;c<=10;c++) {
               if(isdigit(*(*(argv+4)+c))) {
                  if(*(*(argv+4)+(c+1))==NUL)
                     break;
               }
               if(*(*(argv+4)+(c+1))!=NUL&&!isdigit(*(*(argv+4)+(c+1)))) {

               /* Visualizza [Errore: Argomento errato!]. */
                  errscode=ERRSBASE+lang+90;
                  return(errorstype(&errscode));
               }
            }
         }
         else {

         /* Se esistono troppi argomenti numerici (2). */
            if(trueswitch()!=NOSWT&&argc>5) {
               if(option!=BASE&&option!=VARS&&option!=CALC&&subopt!=PME) {

               /* Visualizza [Errore: Troppi argomenti!]. */
                  errscode=ERRSBASE+lang+120;
                  return(errorstype(&errscode));
               }
            }
         }
      }
   /* Fine controlli argomenti con opzione. */

      else {

      /* ---------------------------------------------------------- */
      /* Controllo argomenti senza opzione e Switch.                */
      /* Controllo dei valori digitati se esiste un solo argomento. */
         if(argc==2) {

         /* Controllo della lunghezza degli argomenti numerici. */
         /* E' il primo argomento numerico NON preceduto da un'opzione. */
         /* Questo è l'unico argomento numerico previsto. */
            if(argc==2&&isdigit(**(argv+1))) {
               for(a=0;a<=10;a++) {
                  if(isdigit(*(*(argv+1)+a))) {
                     if(*(*(argv+1)+(a+1))==NUL)
                        break;
                  }
               }
               if(a>=10) {

               /* Visualizza:[Errore: Ordine di grandezza superato!]. */
               /* Visualizza [Errore: Valore troppo grande!]. */
                  errscode=ERRSBASE+lang+260;
                  errorstype(&errscode);
                  errscode=ERRSBASE+lang+180;
                  return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per l'unico argomento numerico. (NO OPZIONE) */
         /* Discriminazione delle opzioni per il cambio della lingua (1). */
            if(!isdigit(**(argv+1))&&**(argv+1)!='-'&&**(argv+1)!='I'&&**(argv+1)!='E'
             &&**(argv+1)!='F'&&**(argv+1)!='P'&&**(argv+1)!='D') {

            /* Visualizza [Errore: Opzione e/o Switch errati!]. */
               errscode=ERRSBASE+ERRSHIFT+lang+10;
               (errorstype(&errscode));

            /* Visualizza [Errore: Argomento errato!]. */
               errscode=ERRSBASE+lang+90;
               return(errorstype(&errscode));
            }
            if(isdigit(**(argv+1))) {
               for(a=0;a<=10;a++) {
                  if(isdigit(*(*(argv+1)+a))) {
                     if(*(*(argv+1)+(a+1))==NUL)
                        break;
                  }
                  if(*(*(argv+1)+(a+1))!=NUL&&!isdigit(*(*(argv+1)+(a+1)))) {

                  /* Visualizza [Errore: Argomento errato!]. */
                     errscode=ERRSBASE+lang+90;
                     return(errorstype(&errscode));
                  }
               }
            }

         /* Controllo per lingue non implementate completamente. */
            if(isalpha(**(argv+1))) {
               putchar('\n');
               if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='N') {
                  if(noten) {
                     fmesg=MSGBASE+ENGLISH+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='I'&&*(*(argv+1)+1)=='T') {
                  if(notit) {
                     fmesg=MSGBASE+ITALIANO+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='S') {
                  if(notes) {
                     fmesg=MSGBASE+ESPANOL+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='F'&&*(*(argv+1)+1)=='R') {
                  if(notfr) {
                     fmesg=MSGBASE+FRANCAIS+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='P'&&*(*(argv+1)+1)=='T') {
                  if(notpt) {
                     fmesg=MSGBASE+PORTUGUES+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else {
                  if(*(*(argv+1))=='D'&&*(*(argv+1)+1)=='E') {
                     if(notde) {
                        fmesg=MSGBASE+DEUTCHE+50;
                        filemsg(&fmesg,&self);
                     }
                  }
               }
            }
         }

      /* ----------------------------------------------------------------- */
      /* Controllo argomenti senza opzione e Switch.                       */
      /* Controllo dei valori digitati se esistono due argomenti numerici. */
         if(argc==3) {

         /* Controllo della lunghezza degli argomenti numerici. */
         /* E' il primo argomento numerico NON preceduto da un'opzione. */
         /* Questo è il primo argomento numerico previsto. */
            if(argc==3&&isdigit(**(argv+1))) {
               for(a=0;a<=10;a++) {
                  if(isdigit(*(*(argv+1)+a))) {
                     if(*(*(argv+1)+(a+1))==NUL)
                        break;
                  }
               }
               if(a>=10)
               /* impostazione flag per visualizzazione errore. */
                  flgers+=1;
            }

         /* E' il secondo argomento numerico NON preceduto da un'opzione. */
         /* Questo è l'ultimo argomento numerico previsto. */
            if(argc==3&&isdigit(**(argv+2))) {
               for(b=0;b<=10;b++) {
                  if(isdigit(*(*(argv+2)+b))) {
                     if(*(*(argv+2)+(b+1))==NUL)
                        break;
                  }
               }
               if(b>=10)
               /* impostazione flag per visualizzazione errore. */
                  flgers+=1;
            }

         /* Visualizza il messaggio di errore in base allo stato del flag 'flgers'. */
         /* Se flgers = 0; nessun errore. Non visualizza nulla. */
         /* Se flgers = 1; Visualizza: [Errore: Valore troppo grande!]. */
         /* Se flgers = 2; Visualizza: [Errore: Valori troppo grandi!]. */
            if(flgers==1) {

            /* Visualizza:[Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valore troppo grande!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+180;
               return(errorstype(&errscode));
            }
            if(flgers==2) {

            /* Visualizza:[Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valori troppo grandi!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+210;
               return(errorstype(&errscode));
            }

         /* Validazione dei valori per il primo di due argomenti numerici. */
         /* Discriminazione delle opzioni per il cambio della lingua (2). */
            if(!isdigit(**(argv+1))&&**(argv+1)!='-'&&**(argv+1)!='I'&&**(argv+1)!='E'
             &&**(argv+1)!='F'&&**(argv+1)!='P'&&**(argv+1)!='D') {

            /* Visualizza [Errore: Argomento errato e/o mancante!]. */
               errscode=ERRSBASE+lang+100;
               return(errorstype(&errscode));
            }
            for(a=0;a<=10;a++) {
               if(isdigit(*(*(argv+1)+a))) {
                  if(*(*(argv+1)+(a+1))==NUL)
                     break;
               }
               if(*(*(argv+1)+(a+1))!=NUL&&!isdigit(*(*(argv+1)+(a+1)))) {

               /* Visualizza [Errore: Argomento errato!]. */
                  errscode=ERRSBASE+lang+90;
                  return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per il secondo di due argomenti numerici. */
            if(!isdigit(**(argv+2))) {

            /* Visualizza [Errore: Argomento errato e/o mancante!]. */
               errscode=ERRSBASE+lang+100;
               return(errorstype(&errscode));
            }
            for(b=0;b<=10;b++) {
               if(isdigit(*(*(argv+2)+b))) {
                  if(*(*(argv+2)+(b+1))==NUL)
                     break;
               }
               if(*(*(argv+2)+(b+1))!=NUL&&!isdigit(*(*(argv+2)+(b+1)))) {

               /* Visualizza [Errore: Argomento errato!]. */
                  errscode=ERRSBASE+lang+90;
                  return(errorstype(&errscode));
               }
            }

         /* Controllo per lingue non implementate completamente. */
            if(isalpha(**(argv+1))) {
               putchar('\n');
               if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='N') {
                  if(noten) {
                     fmesg=MSGBASE+ENGLISH+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='I'&&*(*(argv+1)+1)=='T') {
                  if(notit) {
                     fmesg=MSGBASE+ITALIANO+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='S') {
                  if(notes) {
                     fmesg=MSGBASE+ESPANOL+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='F'&&*(*(argv+1)+1)=='R') {
                  if(notfr) {
                     fmesg=MSGBASE+FRANCAIS+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='P'&&*(*(argv+1)+1)=='T') {
                  if(notpt) {
                     fmesg=MSGBASE+PORTUGUES+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else {
                  if(*(*(argv+1))=='D'&&*(*(argv+1)+1)=='E') {
                     if(notde) {
                        fmesg=MSGBASE+DEUTCHE+50;
                        filemsg(&fmesg,&self);
                     }
                  }
               }
            }
         }
         else {

         /* Se esistono troppi argomenti numerici (3). */
            if(argc>3) {
               errscode=ERRSBASE+lang+120;
               return(errorstype(&errscode));
            }
         }
      }
   /* Fine controlli argomenti senza opzione. */

   }

/* -------------------------------------------------------------------------- */
/* Visualizzazione rapida di presentazione ed uso delle opzioni informative. */
   if(argc==1) {
      about(&lang,nprg,verrel);
      return OK;
   }

/* Controllo e conversione parametri se è presente un solo argomento senza opzione. */
   else if(argc==2&&mark!='-') {
      if(isdigit(**(argv+1))) {

      /* Settaggio flag. */
         flg=1;

      /* Conversione parametro. */
         num=(unsigned long)atol(*(argv+1));
         limit=num;

      /* Controllo parametro. */
         if(num>=UL_MAX&&limit>=UL_MAX) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
         /* I due valori sono sempre uguali! */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
      }

   /* Cambio della lingua impostata. */
   /* Impostazione della lingua inglese. */
      else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='N') {
         lang=ENGLISH;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua italiana. */
      else if(*(*(argv+1))=='I'&&*(*(argv+1)+1)=='T') {
         lang=ITALIANO;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua spagnola. */
      else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='S') {
         lang=ESPANOL;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua francese. */
      else if(*(*(argv+1))=='F'&&*(*(argv+1)+1)=='R') {
         lang=FRANCAIS;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua portoghese. */
      else if(*(*(argv+1))=='P'&&*(*(argv+1)+1)=='T') {
         lang=PORTUGUES;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua tedesca. */
      else if(*(*(argv+1))=='D'&&*(*(argv+1)+1)=='E') {
         lang=DEUTCHE;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }
      else if(fsign) {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         printf("ERROR [ASK-LANG] GURU MEDITATION\n\n");
         return GURU;
      }
      else {

      /* Esecuzione se i parametri degli argomenti sono errati. */
      /* Visualizza [Errore: Argomento errato!]. */
         errscode=ERRSBASE+lang+90;
         return(errorstype(&errscode));
      }
   }

/* Controllo e conversione parametri se è presente un'opzione ed un argomento. */
/* Controllo e conversione parametri se sono presenti due argomenti senza opzione. */
   else if(argc==3) {

   /* Accettare due argomenti numerici senza opzione. */
      if(isdigit(**(argv+1))&&isdigit(**(argv+2))) {

      /* Conversione parametri. */
         num=(unsigned long)atol(*(argv+1));
         limit=(unsigned long)atol(*(argv+2));

      /* Controllo parametri. */
      /* Un solo parametro è fuori gamma. */
         if(num>=UL_MAX||limit>=UL_MAX) fler=1;

      /* Entrambi i parametri sono fuori gamma. */
         if(num>=UL_MAX&&limit>=UL_MAX) fler=2;
         if(fler==1) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valori troppo grandi!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+210;
            return(errorstype(&errscode));
         }
      }

   /* Accettare due argomenti in cui il primo è un opzione. */
   /* Accettare un solo argomento numerico per le opzioni che ne richiedono due. */
      else if(!isdigit(**(argv+1))&&isdigit(**(argv+2))) {

      /* Settaggio flag. */
         flg=1;

      /* Discriminazione dell'opzione. */
         if(option!=STAT&&option!=BASE&&option!=VARS&&option!=CALC) {

         /* Accettare solo se l'opzione è compresa tra le seguenti: */
         /* '-S', '-F', '-Y', '-D', '-P', '-Q', '-L', '-N'. */
            if(globoptions()==GLOB2||option==PRIME||option==NSDIV
             ||option==PLIST||option==NPRIM) {

            /* Conversione parametro. */
               num=limit=(unsigned long)atol(*(argv+2));

            /* Controllo parametro. */
               if(num>=UL_MAX||limit>=UL_MAX) {

               /* Visualizza:[Errore: Ordine di grandezza superato!]. */
               /* Visualizza [Errore: Valore troppo grande!]. */
               /* I due valori sono sempre uguali! */
                  errscode=ERRSBASE+lang+260;
                  errorstype(&errscode);
                  errscode=ERRSBASE+lang+180;
                  return(errorstype(&errscode));
               }

            /* Se l'opzione è '-N' setta il Flag. */
               if(option==NPRIM)
                  flprt=1;
            }
         }
         if(option==BASE) {

         /* Esecuzione se manca un solo argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }
      }
      else {

      /* Esecuzione se i parametri degli argomenti sono errati. */
      /* Visualizza [Errore: Argomento errato e/o mancante!]. */
         errscode=ERRSBASE+lang+100;
         return(errorstype(&errscode));
      }
   }

/* Controllo e conversione parametri se sono presenti un'opzione e due argomenti. */
   else if(argc==4) {

   /* Validazione opzioni e controllo parametri. */
      if(trueoptions()<ERRS&&isdigit(**(argv+2))&&isdigit(**(argv+3))) {

      /* Conversione parametri. */
         num=(unsigned long)atol(*(argv+2));
         limit=(unsigned long)atol(*(argv+3));

      /* Controllo parametri. */
         if(num>=UL_MAX||limit>=UL_MAX) fler=1;
         if(num>=UL_MAX&&limit>=UL_MAX) fler=2;
         if(fler==1) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valori troppo grandi!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+210;
            return(errorstype(&errscode));
         }

      /* Correzione della serie numerica, - */
      /* immessa con due argomenti, per l'opzione '-B'. */
         if(option==BASE) {
            nseg=2;
            if((((limit-num)+1)%nseg))
               num+=1;
         }

      /* Visualizza o stampa la serie di numeri primi su più colonne. */
      /* Se l'opzione è '-P' seguita dallo Switch 'T'. */
         if(option==PRIME&&subopt==TBL) {
            if((limit-num+1)>RANGE) {

               /* Visualizza [Errore: Intervallo di valori troppo grande!]. */
               errscode=ERRSBASE+lang+160;
               return(errorstype(&errscode));
            }

         /* Impostazione Flag per visualizzare serie di numeri primi. */
            fldp=0U;

         /* Visualizza per l'opzione '-pT' */
            if(lang==ENGLISH)
               printf("\nPrime numbers from %lu to %lu\n",num,limit);
            else if(lang==ITALIANO)
               printf("\nNumeri primi da %lu a %lu\n",num,limit);
            else if(lang==ESPANOL)
               printf("\nNúmeros primos de %lu a %lu\n",num,limit);
            else if(lang==FRANCAIS)
               printf("\nNombres premiers de %lu à %lu\n",num,limit);
            else if(lang==PORTUGUES)
               printf("Números primos de\n %lu a %lu\n",num,limit);
            else if(lang==DEUTCHE)
               printf("\nPrimzahlen von %lu bis %lu\n",num,limit);
            else {
               printf("ERROR: [LANG-TABS-1] GURU MEDITATION\n\n");
               return GURU;
            }

         /* Chiamata della funzione di visualizzazione a tabella. */
            if(tpcol(num,limit,&lang)==ERROR) {

            /* Visualizza [Errore: Intervallo di valori non valido!]. */
               errscode=ERRSBASE+lang+200;
               return(errorstype(&errscode));
            }
            else
               return OK;
         }

       /* Se l'opzione è '-N' azzera il Flag e visualizza l'intestazione. */
         if(option==NPRIM&&subopt==NOSWT) {

         /* Azzera il Flag per inibire la stampa dei numeri primi. */
            flprt=0;

         /* Visualizza per l'opzione '-N' senza Switch associato. */
            if(lang==ENGLISH) {
               printf("\nList of numbers divisible from %lu to %lu\n",num,limit);
               printf("Any line break indicates the position of a prime number.\n\n");
            }
            else if(lang==ITALIANO) {
               printf("\nLista di numeri divisibili da %lu a %lu\n",num,limit);
               printf("(L'eventuale salto di riga indica la posizione di un numero primo).\n\n");
            }
            else if(lang==ESPANOL) {
               printf("\nLista de números divisibles de %lu a %lu\n",num,limit);
               printf("Cualquier salto de línea indica la posición de un número primo.\n\n");
            }
            else if(lang==FRANCAIS) {
               printf("\nListe des nombres divisibles de %lu à %lu\n",num,limit);
               printf("Tout saut de ligne indique la position d'un nombre premier.\n\n");
            }
            else if(lang==PORTUGUES) {
               printf("\nLista de números divisíveis de %lu a %lu\n",num,limit);
               printf("Qualquer quebra de linha indica a posição de um número primo.\n\n");
            }
            else if(lang==DEUTCHE) {
               printf("\nListe der Zalhlen, die von %lu bis %lu teilbar sind.\n",num,limit);
               printf("Jeder Zeilenumbruch zeigt die Position einer Primzahl an.\n\n");
            }
            else {
               printf("ERROR: [LANG-NO-PRIME] GURU MEDITATION\n\n");
               return GURU;
            }
         }

      /* Visualizza o stampa la serie di numeri divisibili su più colonne. */
      /* Se l'opzione è '-N' seguita dallo Switch 'T'. */
         if(option==NPRIM&&subopt==TBL) {
            if((limit-num+1)>RGTAB) {

               /* Visualizza [Errore: Intervallo di valori troppo grande!]. */
               errscode=ERRSBASE+lang+160;
               return(errorstype(&errscode));
            }

         /* Impostazione Flag per visualizzare serie di numeri divisibili. */
            fldp=1U;

         /* Visualizza per l'opzione '-nT' */
            if(lang==ENGLISH)
               printf("\nNumbers divisilbe from %lu to %lu\n",num,limit);
            else if(lang==ITALIANO)
               printf("\nNumeri divisibili da %lu a %lu\n",num,limit);
            else if(lang==ESPANOL)
               printf("\nNúmeros divisibles de %lu a %lu\n",num,limit);
            else if(lang==FRANCAIS)
               printf("\nNombres divisibles de %lu à %lu\n",num,limit);
            else if(lang==PORTUGUES)
               printf("Números divisíveis de\n %lu a %lu\n",num,limit);
            else if(lang==DEUTCHE)
               printf("\nZahlen,die von %lu bis %lu teilbar sind.\n",num,limit);
            else {
               printf("ERROR: [LANG-TABS-2] GURU MEDITATION\n\n");
               return GURU;
            }

         /* Chiamata della funzione di visualizzazione a tabella. */
            if(tpcol(num,limit,&lang)==ERROR) {

            /* Visualizza [Errore: Intervallo di valori non valido!]. */
               errscode=ERRSBASE+lang+200;
               return(errorstype(&errscode));
            }
            else
               return OK;
         }
      }
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [NOT-ARGS] GURU MEDITATION\n");

      /* Questa segnalazione di errore è solo per uso interno: non dovrebbe mai presentarsi. */
      /* Esecuzione se le opzioni e/o i  parametri sono errati. */
      /* Visualizza [Errore: Opzione e/o argomenti errati!]. */
         errscode=ERRSBASE+lang+110;
         return(errorstype(&errscode));
      }
   }

/* Controllo e conversione se sono presenti un'opzione e tre argomenti. */
   else if(argc==5) {

   /* Validazione opzioni e parametri per l'opzione '-C'. */
      if(trueoptions()==CMP&&isdigit(**(argv+2))
       &&isdigit(**(argv+3))&&isdigit(**(argv+4))) {

      /* Conversione parametri per l'opzione '-C'. */
         num=(unsigned long)atol(*(argv+2));
         com=(unsigned long)atol(*(argv+3));
         tmp=(unsigned short)atoi(*(argv+4));
         limit=((tmp*com)+num)-1;
         if(!tmp)
            tmp=1;

      /* Controllo parametri. */
         if(num>=UL_MAX||com>=UL_MAX||tmp>=RANGE) fler=1;
         if((num>=UL_MAX&&com>=UL_MAX)||tmp>=RANGE) fler=2;
         if(num>=UL_MAX&&com>=UL_MAX&&tmp>=RANGE) fler=3;
         if(fler==1) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valori troppo grandi!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+210;
            return(errorstype(&errscode));
         }
      }

   /* Validazione opzioni e parametri per l'opzione '-B'. */
      else if(trueoptions()==BSS&&isdigit(**(argv+2))
       &&isdigit(**(argv+3))&&isdigit(**(argv+4))) {

      /* Conversione parametri per l'opzione '-B'. */
         num=(unsigned long)atol(*(argv+2));
         limit=(unsigned long)atol(*(argv+3));
         nseg=(unsigned short)atoi(*(argv+4));

      /* Correzione di nseg. */
         if(!nseg) nseg=1;

      /* Controllo parametri. */
         if(num>=UL_MAX||limit>=UL_MAX) fler=1;
         if(num>=UL_MAX&&limit>=UL_MAX) fler=2;
         if(fler==1) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valori troppo grandi!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+210;
            return(errorstype(&errscode));
         }

      /* Correzione della serie numerica, - */
      /* immessa con tre argomenti, per l'opzione '-B'. */
         if(!((limit-num+1)%nseg)) {
            if((nseg%2)) num+=1;
         }
         else {
            if(!(nseg%2)) num+=1;
            else limit-=1;
         }
      }

   /* Validazione opzioni e parametri per le opzioni '-Y', '-S', '-F', '-D', '-K', -V'. */
      else if(((trueoptions()<=TWO&&subopt!=NSWT)||trueoptions()==VRL)
       &&isdigit(**(argv+2))&&isdigit(**(argv+3))&&isdigit(**(argv+4))) {

      /* Conversione parametri per le opzioni '-Y', '-S', '-F', '-D', '-K', -V'. */
         num=(unsigned long)atol(*(argv+2));
         limit=(unsigned long)atol(*(argv+3));
         select=(unsigned long)atol(*(argv+4));

      /* Controllo parametri. */
         if(num>=UL_MAX||limit>=UL_MAX||select>UL_MAX) fler=1;
         if((num>=UL_MAX&&limit>=UL_MAX)||select>UL_MAX) fler=2;
         if(num>=UL_MAX&&limit>=UL_MAX&&select>UL_MAX) fler=3;
         if(fler==1) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza:[Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valori troppo grandi!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+210;
            return(errorstype(&errscode));
         }

      /* Se l'opzione è '-V' */
         if(option==VARS) {
            if((primenum(select))) {

            /* Visualizza un avviso di attenzione per un possibile errore commesso. */
            /* il terzo argomento, fattore discriminante, deve essere un numero primo. */
               fmesg=MSGBASE+lang+60;
               filemsg(&fmesg,&select);
               if(select>=UL_MAX||select<=0)
                  putchar('\r');
            }
         }
      }
      else {

      /*Se l'opzione + Switch è '-pT', '-nT', '-lL' o '-qL'. */
         if(globoptions()==GLOB3&&(subopt==TBL||subopt==LST)) {

         /* Esecuzione se esistono troppi argomenti numerici. */
         /* Visualizza [Errore: Troppi argomenti!]. */
            errscode=ERRSBASE+lang+120;
            return(errorstype(&errscode));
         }

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [NOT-SWT] GURU MEDITATION\n");

      /* Questa segnalazione di errore è solo per uso interno: non dovrebbe mai presentarsi. */
      /* Esecuzione se le opzioni e/o i  parametri sono errati. */
      /* Visualizza [Errore: Opzione e/o argomenti errati!]. */
         errscode=ERRSBASE+lang+110;
         return(errorstype(&errscode));
      }
   }
   else {

   /* Esecuzione se esistono troppi argomenti numerici (2). */
   /* Visualizza [Errore: Troppi argomenti!]. */
      errscode=ERRSBASE+lang+120;
      return(errorstype(&errscode));
   }

/* Controllo dei parametri sui valori limite. */
   if(num>=UL_MAX||num<0||limit>=UL_MAX) {

   /* Visualizza [Errore: Argomenti errati! Valori fuori scala.]. */
      errscode=ERRSBASE+lang+140;
      return(errorstype(&errscode));
   }

/* Tutte le opzioni ad eccezione di '-C'. */
   if(trueoptions()<=FIVE||option==BASE||option==VARS) {
      range=(limit-num)+1;
      if(option==BASE) {

      /* Solo per l'opzione '-B'. */
         if(num>limit) {

         /* Visualizza [Errore: Valori degli argomenti invertiti!]. */
            errscode=ERRSBASE+lang+150;
            return(errorstype(&errscode));
         }
      }
      else {

      /* Per tutte le altre opzioni. */
         if(limit<num) {
            if(option==VARS)
               putchar('\n');

         /* Visualizza [Errore: Valori degli argomenti invertiti!]. */
            errscode=ERRSBASE+lang+150;
            return(errorstype(&errscode));
         }
      }
      if(range>RANGE) {

      /* Visualizza [Errore: Intervallo di valori troppo grande!]. */
         errscode=ERRSBASE+lang+160;
         return(errorstype(&errscode));
      }
   }
   if(nseg>PEL||!nseg) {

   /* Visualizza [Errore: Serie numerica troppo grande!]. */
      errscode=ERRSBASE+lang+170;
      return(errorstype(&errscode));
   }
   if(select>(UL_MAX-1)||!select) {

   /* Visualizza [Errore: Valore selezionato troppo grande o troppo piccolo!]. */
      errscode=ERRSBASE+lang+190;
      return(errorstype(&errscode));
   }

/* Controlla la coerenza e consistenza globale dei parametri inseriti. */
   if(option==BASE) {

   /* Controlla la coerenza di 'range' e 'nseg' sull'opzione '-B'. */
      if(!(primenum(range))) {

      /* Visualizza [Errore: Intervallo di valori non valido!]. */
         errscode=ERRSBASE+lang+200;
         (errorstype(&errscode));

      /* Visualizza [Errore: Serie numerica non valida!]. */
         errscode=ERRSBASE+lang+220;
         return(errorstype(&errscode));
      }
      else {

      /* Verifica e genera la lunghezza e consistenza della serie numerica. */
         if((range%nseg)) {

         /* Visualizza [Errore: Serie numerica non valida!]. */
            errscode=ERRSBASE+lang+220;
            return(errorstype(&errscode));
         }
         else
            lseg=range/nseg;
      }
   }
   if(option==VARS) {

   /* Controlla la coerenza tra 'select' e 'range' sull'opzione '-V'. */
      if(select>range) {
         if((primenum(select)))
            putchar('\n');

      /* Visualizza [Errore: Valore selezionato fuori scala!]. */
         errscode=ERRSBASE+lang+230;
         return(errorstype(&errscode));
      }
   }

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* Opzioni di visualizzazione e stampa sui prospetti di testa e coda.
   Stampa della lista di numeri primi, divisibili e fattori di scomposizione. */

/* Back-up parametri. */
   number=num,limt=limit;

/* Se i parametri sono uguali imposta flag. */
   if(num==limit)
      flags=NFLAG;

/* Controllo opzioni per la stampa del rapporto di testa. */
   else if((trueoptions()<=TWO&&option!=NOPT&&option!=NSDIV)||option>=VARS) {
      if(lang==ENGLISH)
         printf("\nPrime factorization from %lu to %lu\n\n",num,limit);
      else if(lang==ITALIANO)
         printf("\nScomposizione in fattori primi da %lu a %lu\n\n",num,limit);
      else if(lang==ESPANOL)
         printf("\nFactorización prima de %lu a %lu\n\n",num,limit);
      else if(lang==FRANCAIS)
         printf("\nFactorisation première de %lu à %lu\n\n",num,limit);
      else if(lang==PORTUGUES)
         printf("\nFatoração principal de %lu para %lu\n\n",num,limit);
      else if(lang==DEUTCHE)
         printf("\nPrimfaktorzerlegung von %lu bis %lu\n\n",num,limit);
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [LANG-FACTS] GURU MEDITATION\n\n");
         return GURU;
      }
   }
   else if(option==PRIME) {
      if(lang==ENGLISH)
         printf("\nList of prime factors from %lu to %lu\n\n",num,limit);
      else if(lang==ITALIANO)
         printf("\nLista dei fattori primi da %lu a %lu\n\n",num,limit);
      else if(lang==ESPANOL)
         printf("\nLista de factores primos de %lu a %lu\n\n",num,limit);
      else if(lang==FRANCAIS)
         printf("\nListe des facteurs premiers de %lu à %lu\n\n",num,limit);
      else if(lang==PORTUGUES)
         printf("\nLista de factores primos de %lu a %lu\n\n",num,limit);
      else if(lang==DEUTCHE)
         printf("\nListe der Primfaktoren von %lu bis %lu\n\n",num,limit);
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [LANG-PRIME] GURU MEDITATION\n\n");
         return GURU;
      }
   }
   else if(option==BASE) {
      if(nseg<2) limit+=1;
      if(lang==ENGLISH) {
         printf("\nBreakdown of list into %u series.\n",nseg);
         printf("From number %lu to number %lu inclusive.\n",num,limit);
      }
      else if(lang==ITALIANO) {
         printf("\nScomposizione lista in %u serie.\n",nseg);
         printf("Dal numero %lu al numero %lu inclusi.\n",num,limit);
      }
      else if(lang==ESPANOL) {
         printf("\nDesglose de la lista en %u series.\n",nseg);
         printf("Del numéro %lu al numéro %lu inclusive\n",num,limit);
      }
      else if(lang==FRANCAIS) {
         printf("\nRépartition de la liste en %u séries.\n",nseg);
         printf("Du numéro %lu au numéro %lu inclus.\n",num,limit);
      }
      else if(lang==PORTUGUES) {
         printf("\nDivisão da lista em %u series.\n",nseg);
         printf("Do número %lu ao número %lu inclusive.\n",num,limit);
      }
      else if(lang==DEUTCHE) {
         printf("\nAufschlüsselung der Liste in %u Serien.\n",nseg);
         printf("Von Nummer %lu bis einschließlich Nummer %lu\n",num,limit);
      }
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [LANG-SUBLIST] GURU MEDITATION\n\n");
         return GURU;
      }
   }
   else if(option==CALC) {
      if(lang==ENGLISH)
         printf("\nPrime factorization of the values in the list.\n\n");
      else if(lang==ITALIANO)
         printf("\nScomposizione in fattori primi dei valori nella lista.\n\n");
      else if(lang==ESPANOL)
         printf("\nFactorización prima de los números de la lista.\n\n");
      else if(lang==FRANCAIS)
         printf("\nFactorisation première des valeurs de la liste.\n\n");
      else if(lang==PORTUGUES)
         printf("\nFactoração prima dos números da lista.\n\n");
      else if(lang==DEUTCHE)
         printf("\nPrimfaktorzerlegung der Zahlen in der Liste.\n\n");
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [LANG-CALC] GURU MEDITATION\n\n");
         return GURU;
      }
   }
   else {
     if(option!=NSDIV&&option!=PLIST&&option!=NPRIM&&option!=NOPT)
        putchar('\n');
   }

/* Preparazione formato di visualizzazione e stampa per la serie di numeri selezionata. */
   if(trueoptions()<=FOUR||option==VARS||option==CALC) {
     if(limit<=RANGE) {
     /* ncx definsce di quante posizioni deve essere traslato il valore. */
        if(limit>0&&limit<10) ncx=1;
        else if(limit<100) ncx=2;
        else if(limit<1000) ncx=3;
        else if(limit<10000) ncx=4;
        else
           if(limit<=RANGE) ncx=5;
      }
      else {
        if(limit>RANGE&&limit<100000) ncx=5;
        else if(limit<1000000) ncx=6;
        else if(limit<10000000) ncx=7;
        else if(limit<100000000) ncx=8;
        else if(limit<1000000000) ncx=9;
        else
           if(limit<=UL_MAX) ncx=10;
     }
   }

/* -------------------------------------------------------------------------- */
/* Loop esterno primario di calcolo e stampa. */
   do {

   /* Controllo sull'opzione '-B'. */
      if(option==BASE)
         limit=num+(lseg);

   /* ----------------------------- */
   /* Loop interno di stampa liste. */
      while(num<=limit) {

      /* Chiamata della funzione di ricerca dei numeri divisibili.
         Se il numero è primo restituisce zero; se il numero è divisibile -
         restituisce il primo fattore di scomposizione. */
         divs=primenum(num);
         swflag=NFLAG;

      /* ------------------------------------ */
      /* Opzioni di stampa dei numeri primi. */
         if(divs==1) divs=-1;
         if(!divs) {
            if(num<3) hfatt=0;
            if(limit<4) hfatt=0;

         /* Esecuzione se il numero è primo. */
            if(!hflag)
               *pvect=pdist,pdist=1U,pvect++;
            pcount++,psegm++;
            if(num<2) pcount=0;
            if(limit<2) pcount=0;
            hflag=NFLAG;

         /* Salta alla label NOPRT per l'opzione STAT. */
            if(option==STAT&&subopt!=TBL)
               goto NOPRT;

         /* Stampa con le opzioni '-Y', '-S', o '-F'. */
            if(subopt==PME)

            /* Se è presente lo Switch 'P'. */
               printf("> ");
            else {
               if(option!=NOPT&&trueoptions()!=ONE&&trueoptions()!=TREE
                &&option!=VARS&&option!=BASE) {

               /* Se sono presenti gli Switch 'S', 'U', o 'D' o se assenti. */
               /* Stampa con le opzioni: '-Y', '-S', '-F'. */
                  printf("  ");
               }
               else if(trueoptions()==ONE||option==VARS||option==BASE) {

               /* Se è presente lo Switch 'L' abbinato a '-Q' o se assente. */
               /* Stampa con le opzioni '-Q', '-D', -K, '-V' o '-B'. */
                  ;
               }
               else {

               /* Stampa con le opzioni: '-P', '-L' e NOPT. */
                  if(option==PLIST&&subopt==LST) {

                  /* Se l'opzione è '-L' con lo Switch 'L'. */
                  /* Identazione per tutte le serie. */
                     if(limit<10) printf("          ");
                     if(limit>=10&&limit<100) printf("         ");
                     if(limit>=100&&limit<1000) printf("        ");
                     if(limit>=1000&&limit<10000) printf("       ");
                     if(limit>=10000&&limit<100000) printf("      ");
                     if(limit>=100000&&limit<1000000) printf("     ");
                     if(limit>=1000000&&limit<10000000) printf("    ");
                     if(limit>=10000000&&limit<100000000) printf("   ");
                     if(limit>=100000000&&limit<1000000000) printf("  ");
                     if(limit>=1000000000) printf(" ");
                  }
                  else printf(" ");
               }
            }

         /* In tutti i casi con '-Y', '-S' o '-F' + ['S', 'U', 'D' o 'P']. */
            if(trueoptions()==TWO&&(trueswitch()<=TRUESW||subopt==PME)) {
               if(ncx==1) printf("%1lu",num);
               else if(ncx==2) printf("%2lu",num);
               else if(ncx==3) printf("%3lu",num);
               else if(ncx==4) printf("%4lu",num);
               else if(ncx==5) printf("%5lu",num);
               else if(ncx==6) printf("%6lu",num);
               else if(ncx==7) printf("%7lu",num);
               else if(ncx==8) printf("%8lu",num);
               else if(ncx==9) printf("%9lu",num);
               else {
                  if(ncx==10) printf("%10lu",num);
               }
               putchar('\n');
            }

         /* Stampa con le opzioni NOPT, '-P', '-L' o '-C'. */
         /* Nessuno Switch. */
            else if(trueoptions()==TREE||option==CALC||option==NOPT) {
               if(ncx==1) printf("%1lu",num);
               else if(ncx==2) printf("%2lu",num);
               else if(ncx==3) printf("%3lu",num);
               else if(ncx==4) printf("%4lu",num);
               else if(ncx==5) printf("%5lu",num);
               else if(ncx==6) printf("%6lu",num);
               else if(ncx==7) printf("%7lu",num);
               else if(ncx==8) printf("%8lu",num);
               else if(ncx==9) printf("%9lu",num);
               else {
                  if(ncx==10) printf("%10lu",num);
               }
               putchar('\n');
            }

         /* Stampa con l'opzione '-N'. */
            if(option==NPRIM) {
               if(num!=limit) {

               /* Salta una riga se il numero è primo. */
                  if(!flprt)
                     putchar('\n');
               }
               else
                  putchar('\r');
            }
            if(option==BASE)

            /* Stampa con l'opzione '-B'. */
               ;    /* Non fare nulla. */
         }
         else {

         /* ------------------------------------- */
         /* Esecuzione se il numero è divisibile. */

         /* Calcola e memorizza il fattore di scomposizione piu' alto. */
            hfatt=(divs>hfatt)?divs:hfatt;
            if(num<2) hfatt=0;
            if(limit<3) hfatt=0;
            dcount++;
            if(num<4) dcount=0;
            if(limit<4) dcount=0;
            dsegm++,pdist++;
            hflag=LFLAG;

         /* Salta alla label NOPRT per l'opzione STAT. */
            if(option==STAT&&subopt!=TBL)
               goto NOPRT;

         /* Se le opzioni sono NOPT, '-Y', '-S', '-F', '-D', '-K', -
            Se sono presenti gli Switch 'S', 'U' o 'D' -
            controlla e seleziona il relativo stato di attivazione. */
            if(trueoptions()<=TWO&&(option!=NSDIV)) {
               if(subopt==SEL&&divs==select)
                  swflag=LFLAG,selcount++;
               else if(subopt==UPP&&divs>=select)
                  swflag=LFLAG,selcount++;
               else {
                  if(subopt==DOW&&divs<=select)
                     swflag=LFLAG,selcount++;
               }

            /* Chiamata alla funzione di stampa formattata dei fattori -
               di scomposizione se le opzioni sono '-Y', '-S', '-F', '-D', '-K' -
               e NOPT. La funzione stampa i fattori di scomposizione in -
               due modi diversi in base alle opzioni utilizzate. */
               primefact(num,limit);
               if(option==KEYS&&cnt==1);
            }

         /* Stampa con l'opzione '-N'. */
            else if(option==NPRIM) {
               if(ncx==1) printf(" %1lu",num);
               else if(ncx==2) printf(" %2lu",num);
               else if(ncx==3) printf(" %3lu",num);
               else if(ncx==4) printf(" %4lu",num);
               else if(ncx==5) printf(" %5lu",num);
               else if(ncx==6) printf(" %6lu",num);
               else if(ncx==7) printf(" %7lu",num);
               else if(ncx==8) printf(" %8lu",num);
               else if(ncx==9) printf(" %9lu",num);
               else {
                  if(ncx==10) printf(" %10lu",num);
               }
                  putchar('\n');
            }

         /* Stampa con l'opzione '-C'. */
            else if(option==CALC)
               primefact(num,limit);

         /* Stampa con l'opzione '-Q'. */
            else if(option==NSDIV) {

            /* Stampa con l'opzione '-Q'. */
               if(option==NSDIV&&subopt==LST) {

               /* Se l'opzione è '-Q' con lo Switch 'L'. */
               /* Identazione per tutte le serie. */
                  if(limit<10) printf("          ");
                  if(limit>=10&&limit<100) printf("         ");
                  if(limit>=100&&limit<1000) printf("        ");
                  if(limit>=1000&&limit<10000) printf("       ");
                  if(limit>=10000&&limit<100000) printf("      ");
                  if(limit>=100000&&limit<1000000) printf("     ");
                  if(limit>=1000000&&limit<10000000) printf("    ");
                  if(limit>=10000000&&limit<100000000) printf("   ");
                  if(limit>=100000000&&limit<1000000000) printf("  ");
                  if(limit>=1000000000) printf(" ");
               }
               primefact(num,limit);
            }

         /* Stampa con l'opzione '-V' o '-B'. */
            else {
               if(option==VARS) {

               /* Chiamata alla funzione di stampa formattata dei fattori -
                  di scomposizione per l'opzione '-V' se il  parametro di -
                  scomposizione impostato è uguale al valore restituito. */
                  if(divs==select) {
                     primefact(num,limit);
                     seltot++;
                  }
               }
               if(option==BASE) {

               /* Stampa con l'opzione '-B'. */
                  ;    /* Non fare nulla. */
               }
            }
         }

      /* In entrambi i casi, se il valore è divisibile oppure primo, esegui comunque. */

      /* Label. */
         NOPRT:

         if(option==CALC)
            num+=com;
         else
            num++;
      }
      --num,--dsegm;
   /* Fine del loop interno di stampa liste. */
   /* -------------------------------------- */

      if(option==VARS&&!seltot) {
      /* Visualizza < LISTA VUOTA > per l'opzione '-V'. */
         fmesg=MSGBASE+lang+70;
         filemsg(&fmesg,&select);
      }

   /* -------------------------------------------------------------- */
      if(pcount&&dcount) {
      /* Calcolo del minimo del massimo e della media della distanza -
         tra i singoli numeri primi. */
         pvect=mvect;
         for(;(*pvect);pvect++) {
            if(*pvect<3) *pvect=1;
            lpdist=(*pvect<=lpdist)?*pvect:lpdist;
            hpdist=(*pvect>=hpdist)?*pvect:hpdist;
            fdist+=(float)*pvect;
         }
         fdist/=(pcount-1);
         if(fdist-(int)fdist >0.5) fdist+=1;
         if(*pvect<3)
            pmdist=(unsigned short)fdist/2;
         else
            pmdist=(unsigned short)fdist;
         fcom=fdist-(pmdist+1);
         if(fcom>=0.5)
            pmdist++;
      }
      /* ---------------------------------------------------------- */

      /* Esecuzione se è presente l'opzione '-B'. */
      if(option==BASE) {

      /* Memorizza la lista del numero di fattori primi e divisibili -
         per ogni serie numerica generata per la funzione 'statseries()'. */
         *pnprime++=psegm;
         *pndivs++=dsegm;
         npv++;
         if(nseg>1) --limit;

      /* Stampa i parametri delle serie numeriche generate dalla gamma di valori inseriti, */
      /* secondo l'equazione: lunghezza_serie=((limite_serie-base_serie)+1)/numero_serie. */
         if(lang==ENGLISH) {
            printf("\nSeries from %10.1lu to %10.1lu  -  ",(num-lseg),limit);
            printf("Prime numbers = %4.1u   Divisible numbers = %5.1u",psegm,dsegm);
         }
         else if(lang==ITALIANO) {
            printf("\nSerie da %10.1lu a %10.1lu  -  ",(num-lseg),limit);
            printf("Numeri Primi = %4.1u   Numeri divisibili = %5.1u",psegm,dsegm);
         }
         else if(lang==ESPANOL) {
            printf("\nSeries de %10.1lu al %10.1lu  -  ",(num-lseg),limit);
            printf("Números primos = %4.1u   Números divisibles = %5.1u",psegm,dsegm);
         }
         else if(lang==FRANCAIS) {
            printf("\nSéries de %10.1lu á %10.1lu  -  ",(num-lseg),limit);
            printf("Nombres premiers = %4.1u   Nombres divisibles = %5.1u",psegm,dsegm);
         }
         else if(lang==PORTUGUES) {
            printf("\nSéries de %10.1lu a %10.1lu  -  ",(num-lseg),limit);
            printf("Números primos = %4.1u   Números divisíveis = %5.1u",psegm,dsegm);
         }
         else if(lang==DEUTCHE) {
            printf("\nSerien von %10.1lu bis %10.1lu  -  ",(num-lseg),limit);
            printf("Primzahlen = %4.1u   Teilbare Zahlen = %5.1u",psegm, dsegm);
         }
         else {

         /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
         /* delle funzionalità interne, delle opzioni e degli Switch. */
            if(fsign) {
               printf("ERROR [STAT-1] GURU MEDITATION\n\n");
               return GURU;
            }
         }
      /* Calcola il totale dei numeri primi e divisbili per l'opzione '-b' */
      /* Azzera il conteggio parziale per ogni serie calcolata */
         sumprim+=psegm;
         sumdivs+=dsegm;
         psegm=0,dsegm=0;
      }
   }
   while(limt>limit);
   if(flg) putchar('\n');
   if(number==limt&&!flg)
      putchar('\n');

/* Fine loop esterno di calcolo e stampa. */
/* -------------------------------------------------------------------------- */

/* Controlla se il flag è attivato. */
/* Esecuzione se esiste un solo argomento numerico. */
   if(flags)
      return OK;

/* Esecuzione se esiste piu' di un argomento numerico. */
   else {
      if(option!=NOPT&&option!=PLIST&&option!=NSDIV) {
         if(option==BASE)
            putchar('\n');

      /* Validazione delle opzioni per la stampa del tipo di rapporto di coda. */
      /* Rapporto statistico delle opzioni '-S', '-F', '-Y', '-D', '-P', '-N', */
      /* '-K', -B', '-V', '-C', '-T'. */
         hfatt=(!hfatt)?--num:hfatt;
         if(num==1&&limit==2)
            pcount=1;   /* Il due è il numero primo piu piccolo. */
         if(lang==ENGLISH) {
            if(option==STAT)
               printf("%s version %s      Final summary report:\n",NAMEPROG,VERSION);
            else
               printf("\n\n%s version %s      Final summary report:\n",NAMEPROG,VERSION);
            printf("-------------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Selection by number:                   %10.1lu\n",number);
               printf("At number:                             %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Total series of numbers:                    %5.1lu\n",range);
            if(option==CALC) {
               printf("Total numbers selected:                     %5.1u\n",dcount+pcount);
               printf("Selected period:                       %10.1lu\n",com);
            }
            if(option!=DIVS&&option!=KEYS) {
               if(option==BASE)
                  printf("Total prime numbers:                        %5.1u\n",sumprim);
               else
                  printf("Total prime numbers:                        %5.1u\n",pcount);
            }
            if(option!=PRIME) {
               if(option==BASE)
                  printf("Total divisibles numbers:                   %5.1u\n",sumdivs);
               else
                  printf("Total divisibles numbers:                   %5.1u\n",dcount);
            }
            if(option==KEYS)
               printf("Consistent values displayed:                %5.1u\n",cntvis);
            if(option!=PRIME&&option!=BASE) {
               if(!(dcount+pcount))
                  hfatt=0;
               if((dcount+pcount)==1)
                  hfatt=primenum(num);
               if(num==1&&limit==2)
                  hfatt=0;
               if(num==2&&limit==3)
                  hfatt=0;
               printf("Highest initial prime factor:           %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWO&&option!=NSDIV)&&trueswitch()==TRUESW) {
               printf("Prime factor selected:                      %5.1lu\n",select);
               printf("Quantity of selected values:                %5.1u\n",selcount);
            }
            if(trueoptions()==TWO||option==PRIME||option==STAT) {
               printf("Maximum distance between prime numbers:     %5.1u\n",hpdist);
               printf("Average distance between prime numbers:     %5.1u\n\n",pmdist);
               return OK;
            }
            if(option==BASE) {
               statseries(npv);
               printf("Lenght of the number series:                %5.1lu\n",range);
               printf("Number of numerical series:                 %5.1u\n",nseg);
               printf("Numerical range of series:                  %5.1u\n",lseg);
               printf("Average of primes in the series:            %5.1d\n",pmean);
               printf("Average divisibles in the series:           %5.1d\n",dmean);
               printf("Minimum of prime numbers in the series:     %5.1u\n",pmin);
               printf("Maximum of prime numbers in the series:     %5.1u\n",pmax);
               printf("Minimum of divisible numbers in the series: %5.1u\n",dmin);
               printf("Maximum of divisible numbers in the series: %5.1u\n\n",dmax);
               return OK;
            }
            if(option==VARS) {
               printf("Prime factor selected:                      %5.1lu\n",select);
               printf("Total of numbers displayed:                 %5.1u\n\n",seltot);
               return OK;
            }
            if(option==DIVS||option==KEYS||option==CALC)
               printf("\n");
         }
         else if(lang==ITALIANO) {
            if(option==STAT)
               printf("%s %s     Rapporto riassuntivo finale:\n",NAMEPROG,VERSION);
            else
               printf("\n\n%s %s     Rapporto riassuntivo finale:\n",NAMEPROG,VERSION);
            printf("-----------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Selezione dal numero:                %10.1lu\n",number);
               printf("Al numero:                           %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Serie totale di numeri:                   %5.1lu\n",range);
            if(option==CALC) {
               printf("Totale dei valori selezionati:            %5.1u\n",dcount+pcount);
               printf("Periodo selezionato:                 %10.1lu\n",com);
            }
            if(option!=DIVS&&option!=KEYS) {
               if(option==BASE)
                  printf("Totale numeri primi:                      %5.1u\n",sumprim);
               else
                  printf("Totale numeri primi:                      %5.1u\n",pcount);
            }
            if(option!=PRIME) {
               if(option==BASE)
                  printf("Totale dei numeri divisibili:             %5.1u\n",sumdivs);
               else
                  printf("Totale dei numeri divisibili:             %5.1u\n",dcount);
            }
            if(option==KEYS)
               printf("Valori coerenti visualizzati:             %5.1u\n",cntvis);
            if(option!=PRIME&&option!=BASE) {
               if(!(dcount+pcount))
                  hfatt=0;
               if((dcount+pcount)==1)
                  hfatt=primenum(num);
               if(num==1&&limit==2)
                  hfatt=0;
               if(num==2&&limit==3)
                  hfatt=0;
               printf("Fattore primo iniziale più alto:      %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWO&&option!=NSDIV)&&trueswitch()==TRUESW) {
               printf("Fattore primo selezionato:                %5.1lu\n",select);
               printf("Quantità di valori selezionati:           %5.1u\n",selcount);
            }
            if(trueoptions()==TWO||option==PRIME||option==STAT) {
               printf("Distanza massima tra numeri primi:        %5.1u\n",hpdist);
               printf("Distanza media tra numeri primi:          %5.1u\n\n",pmdist);
               return OK;
            }
            if(option==BASE) {
               statseries(npv);
               printf("Lunghezza della serie numerica:           %5.1lu\n",range);
               printf("Numero delle serie numeriche:             %5.1u\n",nseg);
               printf("Intervallo numerico delle serie:          %5.1u\n",lseg);
               printf("Media dei numeri primi delle serie:       %5.1d\n",pmean);
               printf("Media dei n. divsibili delle serie:       %5.1d\n",dmean);
               printf("Minimo di numeri primi nelle serie:       %5.1u\n",pmin);
               printf("Massimo di numeri primi nelle serie:      %5.1u\n",pmax);
               printf("Minimo di numeri divisibili nelle serie:  %5.1u\n",dmin);
               printf("Massimo di numeri divisibili nelle serie: %5.1u\n\n",dmax);
               return OK;
            }
            if(option==VARS) {
               printf("Fattore primo selezionato:                %5.1lu\n",select);
               printf("Totale numeri visualizzati:               %5.1u\n\n",seltot);
               return OK;
            }
            if(option==DIVS||option==KEYS||option==CALC)
               printf("\n");
         }
         else if(lang==ESPANOL) {
            if(option==STAT)
               printf("%s %s          Informe resumido final:\n",NAMEPROG,VERSION);
            else
               printf("\n\n%s %s          Informe resumido final:\n",NAMEPROG,VERSION);
            printf("-----------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Selección por número:                %10.1lu\n",number);
               printf("Al número:                           %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Números totales:                          %5.1lu\n",range);
            if(option==CALC) {
               printf("Total de números seleccionados:           %5.1u\n",dcount+pcount);
               printf("Período seleccionado:                %10.1lu\n",com);
            }
            if(option!=DIVS&&option!=KEYS) {
               if(option==BASE)
                  printf("Números primos totales:                   %5.1u\n",sumprim);
               else
                  printf("Números primos totales:                   %5.1u\n",pcount);
            }
            if(option!=PRIME) {
               if(option==BASE)
                  printf("Números divisibles totales:               %5.1u\n",sumdivs);
               else
                  printf("Números divisibles totales:               %5.1u\n",dcount);
            }
            if(option==KEYS)
               printf("Valores consistentes mostrados:           %5.1u\n",cntvis);
            if(option!=PRIME&&option!=BASE) {
               if(!(dcount+pcount))
                  hfatt=0;
               if((dcount+pcount)==1)
                  hfatt=primenum(num);
               if(num==1&&limit==2)
                  hfatt=0;
               if(num==2&&limit==3)
                  hfatt=0;
               printf("Factor primo inicial más alto:        %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWO&&option!=NSDIV)&&trueswitch()==TRUESW) {
               printf("Factor primo seleccionado:                %5.1lu\n",select);
               printf("Candidad de números seleccionados:        %5.1u\n",selcount);
            }
            if(trueoptions()==TWO||option==PRIME||option==STAT) {
               printf("Distancia maxima entre números primos:    %5.1u\n",hpdist);
               printf("Distancia media entre números primos:     %5.1u\n\n",pmdist);
               return OK;
            }
            if(option==BASE) {
               statseries(npv);
               printf("Longitud de la serie numérica:            %5.1lu\n",range);
               printf("Numero de series numéricas:               %5.1u\n",nseg);
               printf("Rango numérico de series:                 %5.1u\n",lseg);
               printf("Números primos promedio de la serie:      %5.1d\n",pmean);
               printf("Números divisibles promedio de la serie:  %5.1d\n",dmean);
               printf("Mínimo de números primos en la serie:     %5.1u\n",pmin);
               printf("Máximo de números primos en la serie:     %5.1u\n",pmax);
               printf("Minimo de números divisibles en la serie: %5.1u\n",dmin);
               printf("Máximo de números divisibles en la serie: %5.1u\n\n",dmax);
               return OK;
            }
            if(option==VARS) {
               printf("Factor primo seleccionado:                %5.1lu\n",select);
               printf("Total de números mostrados:               %5.1u\n\n",seltot);
               return OK;
            }
            if(option==DIVS||option==KEYS||option==CALC)
               printf("\n");
         }
         else if(lang==FRANCAIS) {
            if(option==STAT)
               printf("%s %s            Rapport de synthèse final:\n",NAMEPROG,VERSION);
            else
               printf("\n\n%s %s            Rapport de synthèse final:\n",NAMEPROG,VERSION);
            printf("----------------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Sélection par numéro :                    %10.1lu\n",number);
               printf("Au numéro :                               %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Chiffres totaux :                              %5.1lu\n",range);
            if(option==CALC) {
               printf("Nombres total sélectionné :                    %5.1u\n",dcount+pcount);
               printf("Période selectionnée :                    %10.1lu\n",com);
            }
            if(option!=DIVS&&option!=KEYS) {
               if(option==BASE)
                  printf("Nombres premiers totaux :                      %5.1u\n",sumprim);
               else
                  printf("Nombres premiers totaux :                      %5.1u\n",pcount);
            }
            if(option!=PRIME) {
               if(option==BASE)
                  printf("Nombres totaux divisibles :                    %5.1u\n",sumdivs);
               else
                  printf("Nombres totaux divisibles :                    %5.1u\n",dcount);
            }
            if(option==KEYS)
               printf("Valeurs cohérentes affichées :                 %5.1u\n",cntvis);
            if(option!=PRIME&&option!=BASE) {
               if(!(dcount+pcount))
                  hfatt=0;
               if((dcount+pcount)==1)
                  hfatt=primenum(num);
               if(num==1&&limit==2)
                  hfatt=0;
               if(num==2&&limit==3)
                  hfatt=0;
               printf("Facteur premier initial le plus élevé :    %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWO&&option!=NSDIV)&&trueswitch()==TRUESW) {
               printf("Facteur premier sélectionné :                  %5.1lu\n",select);
               printf("Quantité de numéros sélectionnés :             %5.1u\n",selcount);
            }
            if(trueoptions()==TWO||option==PRIME||option==STAT) {
               printf("Distance maximale entre nombres premiers :     %5.1u\n",hpdist);
               printf("Distance moyenne entre nombres premiers :      %5.1u\n\n",pmdist);
               return OK;
            }
            if(option==BASE) {
               statseries(npv);
               printf("Longueur de la série de nombres :              %5.1lu\n",range);
               printf("Nombre de séries de nombres :                  %5.1u\n",nseg);
               printf("Gamme numérique de série :                     %5.1u\n",lseg);
               printf("Moyenne des nombres premiers de la série :     %5.1d\n",pmean);
               printf("Moyenne des nombres divisibles de séries :     %5.1d\n",dmean);
               printf("Minimum de nombres premiers dans les série :   %5.1u\n",pmin);
               printf("Maximum de nombres premiers dans les série :   %5.1u\n",pmax);
               printf("Minimum de nombres divisibles dans les série : %5.1u\n",dmin);
               printf("Maximum de nombres divisibles dans les serie : %5.1u\n\n",dmax);
               return OK;
            }
            if(option==VARS) {
               printf("Facteur premier sélectionné :                  %5.1lu\n",select);
               printf("Nombres total affiché :                        %5.1u\n\n",seltot);
               return OK;
            }
            if(option==DIVS||option==KEYS||option==CALC)
               printf("\n");
         }
         else if(lang==PORTUGUES) {
            if(option==STAT)
               printf("%s %s     Relatório resumido final:\n",NAMEPROG,VERSION);
            else
               printf("\n\n%s %s     Relatório resumido final:\n",NAMEPROG,VERSION);
            printf("--------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Seleção por número:               %10.1lu\n",number);
               printf("Para o número:                    %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Números totais:                        %5.1lu\n",range);
            if(option==CALC) {
               printf("Total de números selecionados:         %5.1u\n",dcount+pcount);
               printf("Periodo selecionados:             %10.1lu\n",com);
            }
            if(option!=DIVS&&option!=KEYS) {
               if(option==BASE)
                  printf("Numeros primos totais:                 %5.1u\n",sumprim);
               else
                  printf("Numeros primos totais:                 %5.1u\n",pcount);
            }
            if(option!=PRIME) {
               if(option==BASE)
                  printf("Números divisíveis totais:             %5.1u\n",sumdivs);
               else
                  printf("Números divisíveis totais:             %5.1u\n",dcount);
            }
            if(option==KEYS)
               printf("Valores consistentes exibidos:         %5.1u\n",cntvis);
            if(option!=PRIME&&option!=BASE) {
               if(!(dcount+pcount))
                  hfatt=0;
               if((dcount+pcount)==1)
                  hfatt=primenum(num);
               if(num==1&&limit==2)
                  hfatt=0;
               if(num==2&&limit==3)
                  hfatt=0;
               printf("Maior factor primo inicial:        %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWO&&option!=NSDIV)&&trueswitch()==TRUESW) {
               printf("Factor primo selecionado:              %5.1lu\n",select);
               printf("Quantidade de números selecionados:    %5.1u\n",selcount);
            }
            if(trueoptions()==TWO||option==PRIME||option==STAT) {
               printf("Distância máxima entre núme primos:    %5.1u\n",hpdist);
               printf("Distância media entre núme primos:     %5.1u\n\n",pmdist);
               return OK;
            }
            if(option==BASE) {
               statseries(npv);
               printf("Comprimento da série numérica:         %5.1lu\n",range);
               printf("Número de séries numéricas:            %5.1u\n",nseg);
               printf("Intervalo numérico de séries:          %5.1u\n",lseg);
               printf("Média dos núme divisíveis da série:    %5.1d\n",pmean);
               printf("Média dos números primos da série:     %5.1d\n",dmean);
               printf("Minimo de números primos na série:     %5.1u\n",pmin);
               printf("Máximo de números primos na série:     %5.1u\n",pmax);
               printf("Minimo de números divisíveis na série: %5.1u\n",dmin);
               printf("Máximo de números divisíveis na série: %5.1u\n\n",dmax);
               return OK;
            }
            if(option==VARS) {
               printf("Factor primo selecionado:              %5.1lu\n",select);
               printf("Total de números exibidos:             %5.1u\n\n",seltot);
               return OK;
            }
            if(option==DIVS||option==KEYS||option==CALC)
               printf("\n");
         }
         else if(lang==DEUTCHE) {
            if(option==STAT)
               printf("%s Version %s              Abschlussbericht:\n",NAMEPROG,VERSION);
            else
               printf("\n\n%s Version %s              Abschlussbericht:\n",NAMEPROG,VERSION);
            printf("-----------------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Auswahl nach nummer:                       %10.1lu\n",number);
               printf("Zur nummer:                                %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Gesamtzahlen:                                   %5.1lu\n",range);
            if(option==CALC) {
               printf("Gesamtzahl ausgewählt:                          %5.1u\n",dcount+pcount);
               printf("Ausgewählter Zeitraum:                     %10.1lu\n",com);
            }
            if(option!=DIVS&&option!=KEYS) {
               if(option==BASE)
                  printf("Gesamtzahl der Primzahlen:                      %5.1u\n",sumprim);
               else
                  printf("Gesamtzahl der Primzahlen:                      %5.1u\n",pcount);
            }
            if(option!=PRIME) {
               if(option==BASE)
                  printf("Gesamte teilbare Zahlen:                        %5.1u\n",sumdivs);
               else
                  printf("Gesamte teilbare Zahlen:                        %5.1u\n",dcount);
            }
            if(option==KEYS)
               printf("Konsistente Werte angezeigt:                    %5.1u\n",cntvis);
            if(option!=PRIME&&option!=BASE) {
               if(!(dcount+pcount))
                  hfatt=0;
               if((dcount+pcount)==1)
                  hfatt=primenum(num);
               if(num==1&&limit==2)
                  hfatt=0;
               if(num==2&&limit==3)
                  hfatt=0;
               printf("Höchste anfänglicher Primfaktor:            %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWO&&option!=NSDIV)&&trueswitch()==TRUESW) {
               printf("Ausgewählter Primfactor:                        %5.1lu\n",select);
               printf("Anzahl der ausgewählten numerischen Faktoren:   %5.1u\n",selcount);
            }
            if(trueoptions()==TWO||option==PRIME||option==STAT) {
               printf("Maximaler Abstand zwischen Primzahlen:          %5.1u\n",hpdist);
               printf("Durchschnittlicher Abstand zwischen Primzahlen: %5.1u\n\n",pmdist);
               return OK;
            }
            if(option==BASE) {
               statseries(npv);
               printf("Länge der Zahlenreihe:                          %5.1lu\n",range);
               printf("Anzahl der Nummernserien:                       %5.1u\n",nseg);
               printf("Zahlenbereich der Serie:                        %5.1u\n",lseg);
               printf("Durchschnitt der Primzahlen der Zahlenreihe:    %5.1d\n",pmean);
               printf("Durchschnitt der teilbaren Zahlenzahlenreihen:  %5.1d\n",dmean);
               printf("Mindestmenge an Primzahlen in Zahlenreihen:     %5.1u\n",pmin);
               printf("Maximale Anzahl von Primzahlen in Zahlenreihe:  %5.1u\n",pmax);
               printf("Mindestanzahl teilbaler Zahlen in Zahlenreihen: %5.1u\n",dmin);
               printf("Maxim. Anzahl teilbarer Zahlen in Zahlenreihen: %5.1u\n\n",dmax);
               return OK;
            }
            if(option==VARS) {
               printf("Ausgewählter Primfactor:                        %5.1lu\n",select);
               printf("Gesamtzahl angezeigt:                           %5.1u\n\n",seltot);
               return OK;
            }
            if(option==DIVS||option==KEYS||option==CALC)
               printf("\n");
         }
         else {

         /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
         /* delle funzionalità interne, delle opzioni e degli Switch. */
            if(fsign) {
               printf("ERROR [STAT-2] GURU MEDITATION\n");
            }
            if(lang==ENGLISH) {
               printf("Error: Language not implemented!\n\n");
               return ERROR;
            }
            else if(lang==ITALIANO) {
               printf("Errore: Lingua non implementata!\n\n");
               return ERROR;
            }
            else if(lang==ESPANOL) {
               printf("Error: ¡Idioma no implementado!\n\n");
               return ERROR;
            }
            else if(lang==FRANCAIS) {
               printf("Erreur : Langue non implémentée!\n\n");
               return ERROR;
            }
            else if(lang==PORTUGUES) {
               printf("Erro: Linguagem não implementada!\n\n");
               return ERROR;
            }
            else if(lang==DEUTCHE) {
               printf("Fehler: Sprache nitch implementiert!\n\n");
               return ERROR;
            }
         }
      }
      if(option==NOPT)
         putchar('\n');
   }
   return OK;
}
/* Fine della sezione principale del programma. */


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* ++++++++++++++++++++++++  Inizio funzioni Esterne  +++++++++++++++++++++++ */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */


/* ------------------------------------------------------------------- */
/* Funzioni di stampa intestazione di aiuto delle opzioni e parametri. */
/* ------------------------------------------------------------------- */

/* Funzione about() */
void about(short *flang, char *argz,char *verrez) {
   if(*flang==ENGLISH) {
      printf("\n%s         Version: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2025) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Written by G. B. alias PiErre60\n");
      printf(" with the collaboration of:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("To use: %s --help For extended help.\n",argz);
      printf("     or %s -h     For quick help.\n",argz);
      printf("     or %s -?     For author and license info.\n",argz);
      printf("     or %s -?m    For user manual.\n",argz);
      printf("     or %s -?i    For start user guide.\n\n",argz);
      return;
   }
   if(*flang==ITALIANO) {
      printf("\n%s        Versione: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2025) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Scritto da G. B. alias PiErre60\n");
      printf(" con la collaborazione di:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Usare: %s --help Per aiuto dettagliato.\n",argz);
      printf("     o %s -h     Per aiuto rapido.\n",argz);
      printf("     o %s -?     Per info autore e licenza.\n",argz);
      printf("     o %s -?m    Per manuale d'uso.\n",argz);
      printf("     o %s -?i    Per guida d'uso rapida.\n\n",argz);
      return;
   }
   if(*flang==ESPANOL) {
      printf("\n%s         Versión: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2025) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Escrito por G.B. alias PiErre60\n");
      printf(" con la colaboración de:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Usar: %s --help Para ayuda detallada.\n",argz);
      printf("    o %s -h     Para ayuda rápida.\n",argz);
      printf("    o %s -?     Para info sobre el autor y licencia.\n",argz);
      printf("    o %s -?m    Para el manual de usuario.\n",argz);
      printf("    o %s -?i    Para una guida de usuario rápida.\n\n",argz);
      return;
   }
   if(*flang==FRANCAIS) {
      printf("\n%s        Version : %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2025) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Ecrit par G. B.  alias PiErre60\n");
      printf(" avec la collaboration de :\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Utiliser : %s --help Pour une aide détaillée.\n",argz);
      printf("        ou %s -h     Pour une aide rapide.\n",argz);
      printf("        ou %s -?     Pour informations sur auteur et licence.\n",argz);
      printf("        ou %s -?m    Pour le manuel d'utilisation.\n",argz);
      printf("        ou %s -?i    Pour un guide d'utilisation rapide.\n\n",argz);
      return;
   }
   if(*flang==PORTUGUES) {
      printf("\n%s          Versão: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2025) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Escrito por G.B. alias PiErre60\n");
      printf(" com a colaboração de:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Usar: %s --help Para ajuda detalhada.\n",argz);
      printf("   ou %s -h     Para ajuda rapida.\n",argz);
      printf("   ou %s -?     Para infos sobre autor e licença.\n",argz);
      printf("   ou %s -?m    Para o manual do usuário.\n",argz);
      printf("   ou %s -?i    Para um guia rápido do usuário.\n\n",argz);
      return;
   }
   if(*flang==DEUTCHE) {
      printf("\n%s         Version: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2025) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Geschrieben von G.B. (PiErre60)\n");
      printf(" in Zusammenarbeit mit:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Verwenden: %s --help Für ausführliche Hilfe.\n",argz);
      printf("      oder %s -h     Für schnelle Hilfe. \n",argz);
      printf("      oder %s -?     Für Autoren und Lizenzinformationen.\n",argz);
      printf("      oder %s -?m    Zur Bedienungsanleitung.\n",argz);
      printf("      oder %s -?i    Für die Kurzanleitung.\n\n",argz);
      return;
   }
}
/* Fine della funzione about(). */


/* Funzione quickhelp(). */
void quickhelp(short *flang,char *argz) {
   if(*flang==ENGLISH) {
      printf("\nTo use: %s --help  For extended help,\n",argz);
      printf("     or %s [option] [switch] [num_arg_1] [num_arg_2] [num_arg_3]\n",argz);
      printf("                 for operative mode.\n\n");
      printf("  Options: [-s, -f, -y, -d, -p, -q, -l, -n, -k, -t, -b, -v, -c]\n");
      printf(" Switcher: [P,  S,  U,  D,  L,  T]\n");
      printf("   Locale: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Examples: %s 1234567890\n",argz);
      printf("          %s 1 65535\n",argz);
      printf("          %s -t 32768  98303\n",argz);
      printf("          %s 100 65635 | more\n",argz);
      printf("          %s -l 1 65535 >> $HOME/prime\n",argz);
      printf("          %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("          %s -f 50250 102500\n",argz);
      printf("          %s -k 12345 59999\n",argz);
      printf("          %s -d 1000 9999\n",argz);
      printf("          %s -p 1000 9999\n",argz);
      printf("          %s -nT 100 50000\n",argz);
      printf("          %s -pT 100 50000\n",argz);
      printf("          %s -fS 1234 9999 5\n",argz);
      printf("          %s -b 1001 5000 16\n",argz);
      printf("          %s -c 1001 5000 7\n",argz);
      printf("          %s -v 2500 2999 7\n\n",argz);
      return;
   }
   if(*flang==ITALIANO) {
      printf("\nUsare: %s --help  Per aiuto dettagliato,\n",argz);
      printf("oppure %s [opzione] [segnalatore] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("                per modalità operativa.\n\n");
      printf("      Opzioni: [-s, -f, -y, -d, -p, -q, -l, -n, -k, -t, -b, -v, -c]\n");
      printf("  Segnalatori: [P,  S,  U,  D,  L,  T]\n");
      printf("Lingua locale: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Esempi: %s 1234567890\n",argz);
      printf("        %s 1 65535\n",argz);
      printf("        %s -t 32768  98303\n",argz);
      printf("        %s 100 65635 | more\n",argz);
      printf("        %s -l 1 65535 >> $HOME/prime\n",argz);
      printf("        %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("        %s -f 50250 102500\n",argz);
      printf("        %s -k 12345 59999\n",argz);
      printf("        %s -d 1000 9999\n",argz);
      printf("        %s -p 1000 9999\n",argz);
      printf("        %s -nT 100 50000\n",argz);
      printf("        %s -pT 100 50000\n",argz);
      printf("        %s -fS 1234 9999 5\n",argz);
      printf("        %s -b 1001 5000 16\n",argz);
      printf("        %s -c 1001 5000 7\n",argz);
      printf("        %s -v 2500 2999 7\n\n",argz);
      return;
   }
   if(*flang==ESPANOL) {
      printf("\nUsar: %s --help  Para obtener ayuda detallada,\n",argz);
      printf("    o %s [option] [señalizator] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("               por modo de funcionamiento.\n\n");
      printf("     Opciones: [-s, -f, -y, -d, -p, -q, -l, -n, -k, -t, -b, -v, -c]\n");
      printf("Señalizatores: [P,  S,  U,  D,  L,  T]\n");
      printf(" Idioma local: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Ejemplos: %s 1234567890\n",argz);
      printf("          %s 1 65535\n",argz);
      printf("          %s -t 32768  98303\n",argz);
      printf("          %s 100 65635 | more\n",argz);
      printf("          %s -l 1 65535 >> $HOME/prime\n",argz);
      printf("          %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("          %s -f 50250 102500\n",argz);
      printf("          %s -k 12345 59999\n",argz);
      printf("          %s -d 1000 9999\n",argz);
      printf("          %s -p 1000 9999\n",argz);
      printf("          %s -nT 100 50000\n",argz);
      printf("          %s -pT 100 50000\n",argz);
      printf("          %s -fS 1234 9999 5\n",argz);
      printf("          %s -b 1001 5000 16\n",argz);
      printf("          %s -c 1001 5000 7\n",argz);
      printf("          %s -v 2500 2999 7\n\n",argz);
      return;
   }
   if(*flang==FRANCAIS) {
      printf("\nUtiliser : %s --help  Pour une aide détaillée,\n",argz);
      printf("        ou %s [option] [aiguilleur] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("                    par mode de fonctionnement.\n\n");
      printf(" Possibilités : [-s, -f, -y, -d, -p, -q, -l, -n, -k, -t, -b, -v, -c]\n");
      printf("   Signaleurs : [P,  S,  U,  D,  L,  T]\n");
      printf("Langue locale : [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Exemples : %s 1234567890\n",argz);
      printf("           %s 1 65535\n",argz);
      printf("           %s -t 32768  98303\n",argz);
      printf("           %s 100 65635 | more\n",argz);
      printf("           %s -l 1 65535 >> $HOME/prime\n",argz);
      printf("           %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("           %s -f 50250 102500\n",argz);
      printf("           %s -k 12345 59999\n",argz);
      printf("           %s -d 1000 9999\n",argz);
      printf("           %s -p 1000 9999\n",argz);
      printf("           %s -nT 100 50000\n",argz);
      printf("           %s -pT 100 50000\n",argz);
      printf("           %s -fS 1234 9999 5\n",argz);
      printf("           %s -b 1001 5000 16\n",argz);
      printf("           %s -c 1001 5000 7\n",argz);
      printf("           %s -v 2500 2999 7\n\n",argz);
      return;
   }
   if(*flang==PORTUGUES) {
      printf("\nTo use: %s --help  Para ajuda detalhada,\n",argz);
      printf("     ou %s [option] [sinalizador] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("                 por modo de operação.\n\n");
      printf("       Opções: [-s, -f, -k, -y, -d, -p, -q, -l, -n, -k, -t, -b, -v, -c]\n");
      printf("Sinalizadores: [P,  S,  U,  D,  L,  T]\n");
      printf(" Lingua local: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Exemplos: %s 1234567890\n",argz);
      printf("          %s 1 65535\n",argz);
      printf("          %s -t 32768  98303\n",argz);
      printf("          %s 100 65635 | more\n",argz);
      printf("          %s -l 1 65535 >> $HOME/prime\n",argz);
      printf("          %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("          %s -f 50250 102500\n",argz);
      printf("          %s -k 12345 59999\n",argz);
      printf("          %s -d 1000 9999\n",argz);
      printf("          %s -p 1000 9999\n",argz);
      printf("          %s -nT 100 50000\n",argz);
      printf("          %s -pT 100 50000\n",argz);
      printf("          %s -fS 1234 9999 5\n",argz);
      printf("          %s -b 1001 5000 16\n",argz);
      printf("          %s -c 1001 5000 7\n",argz);
      printf("          %s -v 2500 2999 7\n\n",argz);
      return;
   }
   if(*flang==DEUTCHE) {
      printf("\nVerwenden: %s --help  Für ausführliche Hilfe,\n",argz);
      printf("      oder %s [option] [signalgerber] [zahl_arg_1] [zahl_arg_2] [zahl_arg_3]\n",argz);
      printf("                    natch Betriebsart.\n\n");
      printf("     Optionen: [-s, -f, -k, -y, -d, -p, -q, -l, -n, -k, -t, -b, -v, -c]\n");
      printf("  Signalgeber: [P,  S,  U,  D,  L,  T]\n");
      printf("Landessprache: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Beispiele: %s 1234567890\n",argz);
      printf("           %s 1 65535\n",argz);
      printf("           %s -t 32768  98303\n",argz);
      printf("           %s 100 65635 | more\n",argz);
      printf("           %s -l 1 65535 >> $HOME/prime\n",argz);
      printf("           %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("           %s -f 50250 102500\n",argz);
      printf("           %s -k 12345 59999\n",argz);
      printf("           %s -d 1000 9999\n",argz);
      printf("           %s -p 1000 9999\n",argz);
      printf("           %s -nT 100 50000\n",argz);
      printf("           %s -pT 100 50000\n",argz);
      printf("           %s -fS 1234 9999 5\n",argz);
      printf("           %s -b 1001 5000 16\n",argz);
      printf("           %s -c 1001 5000 7\n",argz);
      printf("           %s -v 2500 2999 7\n\n",argz);
      return;
   }
}
/* Fine della funzione quickhelp(). */


/* ************************************************************************** */
/* Funzione helpfunc() */
void helpfunc(short *flang,char *argz,char *verrez) {

   /* AIUTO ESTESO IN INGLESE, ITALIANO, SPAGNOLO, FRANCESE, PORTOGHESE, TEDESCO */
   if(*flang==ENGLISH) {
      printf("\n%s   Release: %s",argz,verrez);
      printf("\n~© (2010-2025) - F.S.F. GNU/GPL vers.3\n");
      printf("\nTo use: %s      About.\n",argz);
      printf("        %s -?   Author and license information.\n",argz);
      printf("        %s -?m  User manual.\n",argz);
      printf("        %s -?i  Quick start Guide\n",argz);
      printf("        %s -h   Quick help.\n",argz);
      printf("        %s --help  Extended help.\n",argz);
      printf("        %s EN, IT, ES, FR, PT, DE  Local language selection.\n",argz);
      printf("        %s [num_arg]\n",argz);
      printf("        %s [num_arg_1] [num_arg_2]\n",argz);
      printf("        %s [option] [signaler] [num_arg_1] [num_arg_2]\n",argz);
      printf("        %s [option] [signaler] [num_arg_1] [num_arg_2] [num_arg_3]\n",argz);
      printf("\nSynopsis: %s [-s | -f | -y | -d | -n | -p | -k | -t]  [num_value_1] [num_value_2]\n",argz);
      printf("          %s [-l | -q | -n | -p]  [L | T]  [num_value_1] [num_value_2]\n",argz);
      printf("          %s [-s | -f | -y | -d]  [S | U | D]  [num_value_1] [num_value_2] [num_value_3]\n",argz);
      printf("          %s [-b | -v | -c]  [num_value_1] [num_value_2] [num_value_3]\n\n",argz);
      printf("        [num_value_1] = Initial element of the numerical series.\n");
      printf("        [num_value_2] = Final element of the numerical series./Discriminant value for the series.\n");
      printf("        [num_value_3] = Discriminant value for displaying the series.\n");
      printf("\nOptions: -s  Prime factors of a series decomposition displayed individually.\n");
      printf("         -y  Single displayed prime factor of a numerical series.\n");
      printf("         -f  Prime factors of a series displayed in standard notation.\n");
      printf("         -k  Filters out values in a series that have only two prime factors of decomposition.\n");
      printf("         -p  Series of only prime numbers displayed in standard notation.\n");
      printf("         -d  Series of only prime decomposition factors displayed in standard notation.\n");
      printf("         -l  Numerical series of only prime numbers displayed.\n");
      printf("         -q  Numerical series of only displayed prime decomposition factors.\n");
      printf("         -n  Numerical series of divisible values with positional marking of the prime numbers.\n");
      printf("         -t  Statistical report of a given series of values.\n");
      printf("         -b  Decomposition into N numerical series as a function of a given numerical series.\n");
      printf("         -v  Selective series of values for an arbitrary divisibility factor.\n");
      printf("         -c  Series of values defined from A to B positions of N elements.\n");
      printf("\nSpecial options: -clr  Delete the language configuration file.\n");
      printf("                 -rst  Reset to default language. (1)\n");
      printf("                 -rst  Restore the initial mode. (2)\n");
      printf("        (1)(2) - The functionality changes depending on the presence\n");
      printf("                 or absence of the configuration file.\n");
      printf("\nSignalers: P  Marking of the prime numbers of the displayed number series.\n");
      printf("           S  Marking of a prime factor of decomposition in the displayed numerical series.\n");
      printf("           U  Ascending marking from a prime factor indicadedin the displayed number series.\n");
      printf("           D  Descending marking from a prime factor indicated in the displayed number series.\n");
      printf("\nJustified indent display option:\n");
      printf("         -lL  Visualizing a series of only prime numbers.\n");
      printf("         -qL  Displaying a series of divisible numbers and prime factors of decomposition.\n");
      printf("\nTabular view options:\n");
      printf("         -nT  Display in the numerical series only numbers that are divisible into multiple columns.\n");
      printf("         -pT  Display only prime numbers in the numerical series in multiple columns.\n");
      printf("\nExamples: %s 1234567890\n",argz);
      printf("          %s 1 65535\n",argz);
      printf("          %s -t 32768  98303\n",argz);
      printf("          %s 100 65635 | more\n",argz);
      printf("          %s -l 1 65535 >  $HOME/prime\n",argz);
      printf("          %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("          %s -y 1000 75535\n",argz);
      printf("          %s -f 1234 9999\n",argz);
      printf("          %s -k 1234 59999\n",argz);
      printf("          %s -d 1000 9999\n",argz);
      printf("          %s -p 1000 9999\n",argz);
      printf("          %s -nT 100 50000\n",argz);
      printf("          %s -pT 100 50000\n",argz);
      printf("          %s -qL 150 65500\n",argz);
      printf("          %s -fP 1234 39999 5\n",argz);
      printf("          %s -fS 1234 39999 5\n",argz);
      printf("          %s -yS 1234 39999 5\n",argz);
      printf("          %s -sU 12345 39999 13\n",argz);
      printf("          %s -b 1001 5000 16\n",argz);
      printf("          %s -c 1001 5000 7\n",argz);
      printf("          %s -v 2500 2999 7\n\n",argz);
      return;
   }

   /* *********************************************************************** */
   if(*flang==ITALIANO) {
      printf("\n%s   Versione: %s",argz,verrez);
      printf("\n~© (2010-2025) - F.S.F. GNU/GPL vers.3\n");
      printf("\nUsare: %s      Presentazione.\n",argz);
      printf("       %s -?   Informazioni su autore e licenza.\n",argz);
      printf("       %s -?m  Manuale d'uso.\n",argz);
      printf("       %s -?i  Guida d'uso rapida.\n",argz);
      printf("       %s -h   Aiuto rapido.\n",argz);
      printf("       %s --help  Aiuto dettagliato.\n",argz);
      printf("       %s IT, EN, ES, FR, PT, DE  Selezione della lingua locale.\n",argz);
      printf("       %s [arg_num]\n",argz);
      printf("       %s [arg_num_1] [arg_num_2]\n",argz);
      printf("       %s [opzione] [segnalatore] [arg_num_1] [arg_num_2]\n",argz);
      printf("       %s [opzione] [segnalatore] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("\nSinossi: %s [-s | -f | -y | -d | -n | -p | -k | -t]  [val_num_1] [val_num_2]\n",argz);
      printf("         %s [-l | -q | -n | -p]  [L | T]  [val_num_1] [val_num_2]\n",argz);
      printf("         %s [-s | -f | -y | -d]  [S | U | D]  [val_num_1] [val_num_2] [val_num_3]\n",argz);
      printf("         %s [-b | -v | -c]  [val_num_1] [val_num_2] [val_num_3]\n\n",argz);
      printf("       [val_num_1] = Elemento iniziale della serie numerica.\n");
      printf("       [val_num_2] = Elemento finale della serie numerica./Valore discriminante per la serie.\n");
      printf("       [val_num_3] = Valore discriminante per la visualizzazione della serie.\n");
      printf("\nOpzioni: -s  Fattori primi di scomposizione di una serie visualizzati singolarmente.\n");
      printf("         -y  Singolo fattore primo di scomposizione visualizzato di una serie numerica.\n");
      printf("         -f  Fattori primi di scomposizione di una serie visualizzati in notazione standard.\n");
      printf("         -k  Filtra in una serie i valori che hanno solo due fattori primi di scomposizione.\n");
      printf("         -p  Serie di soli numeri primi visualizzati in notazione standard.\n");
      printf("         -d  Serie dei soli fattori primi di scomposizione visualizzati in notazione standard.\n");
      printf("         -l  Serie numerica di soli numeri primi visualizzati.\n");
      printf("         -q  Serie numerica di soli fattori primi di scomposizione visualizzati.\n");
      printf("         -n  Serie numerica di valori divisibili con marcatura posizionale dei numeri primi.\n");
      printf("         -t  Rapporto statistico di una serie di valori indicata.\n");
      printf("         -b  Scomposizione in N serie numeriche in funzione di una serie numerica indicata.\n");
      printf("         -v  Serie selettiva di valori per un fattore arbitrario di divisibilità.\n");
      printf("         -c  Serie di valori definita a partire da A per B posizioni di N elementi.\n");
      printf("\nOpzioni speciali: -clr  Elimina il file di configurazione della lingua.\n");
      printf("                  -rst  Reimposta la lingua predefinita. (1)\n");
      printf("                  -rst  Ripristina la modalità iniziale. (2)\n");
      printf("       (1)(2) - La funzionalità cambia in funzione della presenza o assenza del file di configurazione.\n");
      printf("\nSegnalatori: P  Marcatura dei numeri primi della serie numerica visualizzata.\n");
      printf("             S  Marcatura di un fattore primo di scomposizione nella serie numerica visualizzata.\n");
      printf("             U  Marcatura ascendente da un fattore primo indicato nella serie numerica visualizzata.\n");
      printf("             D  Marcatura discendente da un fattore primo indicato nella serie numerica visualizzata.\n");
      printf("\nOpzioni di visualizzazione di rientro giustificato:\n");
      printf("         -lL  Visualizzazione di una serie di soli numeri primi.\n");
      printf("         -qL  Visualizzazione di una serie di numeri divisibili e fattori primi di scomposizione.\n");
      printf("\nOpzioni di visualizzazione tabellare:\n");
      printf("         -nT  Visualizzazione nella serie numerica dei soli numeri divisibili su più colonne.\n");
      printf("         -pT  Visualizzazione nella serie numerica dei soli numeri primi su più colonne.\n");
      printf("\nEsempi: %s 1234567890\n",argz);
      printf("        %s 1 65535\n",argz);
      printf("        %s -t 32768  98303\n",argz);
      printf("        %s 100 65635 | more\n",argz);
      printf("        %s -l 1 65535 >  $HOME/prime\n",argz);
      printf("        %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("        %s -y 1000 75535\n",argz);
      printf("        %s -f 1234 9999\n",argz);
      printf("        %s -k 1234 59999\n",argz);
      printf("        %s -d 1000 9999\n",argz);
      printf("        %s -p 1000 9999\n",argz);
      printf("        %s -nT 100 50000\n",argz);
      printf("        %s -pT 100 50000\n",argz);
      printf("        %s -qL 150 65500\n",argz);
      printf("        %s -fP 1234 39999 5\n",argz);
      printf("        %s -fS 1234 39999 5\n",argz);
      printf("        %s -yS 1234 39999 5\n",argz);
      printf("        %s -sU 12345 39999 13\n",argz);
      printf("        %s -b 1001 5000 16\n",argz);
      printf("        %s -c 1001 5000 7\n",argz);
      printf("        %s -v 2500 2999 7\n\n",argz);
      return;
   }

   /* *********************************************************************** */
   if(*flang==ESPANOL) {
      printf("\n%s   Versión: %s",argz,verrez);
      printf("\n~© (2010-2025) - F.S.F. GNU/GPL vers.3\n");
      printf("\nUsar: %s      Presentación.\n",argz);
      printf("      %s -?   Información sobre el autor y la licencia.\n",argz);
      printf("      %s -?m  Manual de usuario.\n",argz);
      printf("      %s -?i  Guia de inicio rápido.\n",argz);
      printf("      %s -h   Ayuda rápida.\n",argz);
      printf("      %s --help  Ayuda detallada.\n",argz);
      printf("      %s IT, EN, ES, FR, PT, DE  Selección de idioma local.\n",argz);
      printf("      %s [arg_num]\n",argz);
      printf("      %s [arg_num_1] [arg_num_2]\n",argz);
      printf("      %s [opcion] [señalizador] [arg_num_1] [arg_num_2]\n",argz);
      printf("      %s [opcion] [señalizador] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("\nSinopsis: %s [-s | -f | -y | -d | -n | -p | -k | -t]  [val_num_1] [val_num_2]\n",argz);
      printf("          %s [-l | -q | -n | -p]  [L | T]  [val_num_1] [val_num_2]\n",argz);
      printf("          %s [-s | -f | -y | -d]  [S | U | D]  [val_num_1] [val_num_2] [val_num_3]\n",argz);
      printf("          %s [-b | -v | -c]  [val_num_1] [val_num_2] [val_num_3]\n\n",argz);
      printf("        [val_num_1] = Elemento inicial de la serie numérica.\n");
      printf("        [val_num_2] = Elemento final de la serie numérica./Valor discriminante para la serie.\n");
      printf("        [val_num_3] = Valor discriminante para visualizar la serie.\n");
      printf("\nOpciones: -s  Factores primos de una descomposición en series mostrados individualmente.\n");
      printf("          -y  Factor primo único mostrado de una serie numérica.\n");
      printf("          -f  Factores primos de una serie mostrados en notación estándar.\n");
      printf("          -k  Filtra valores de una serie que tienen solo dos factores primos de descomposición.\n");
      printf("          -p  Serie de únicamente números primos mostrados en notación estándar.\n");
      printf("          -d  Serie de únicamente factores de descomposición primos mostrados en notación estándar.\n");
      printf("          -l  Serie numérica que contiene únicamente números primos.\n");
      printf("          -q  Serie numérica de factores de descomposición primos mostrados únicamente.\n");
      printf("          -n  Serie numérica de valores divisibles con marcaje posicional de los números primos.\n");
      printf("          -t  Informe estadístico de una serie dada de valores.\n");
      printf("          -b  Descomposición en N series numéricas en función de una serie numérica dada.\n");
      printf("          -v  Serie selectiva de valores para un factor de divisibilidad arbitrario.\n");
      printf("          -c  Serie de valores definidos desde las posiciones A hasta B de N elementos.\n");
      printf("\nOpciones especiales: -clr  Eliminal el archivo de configuración de idioma.\n");
      printf("                     -rst  Restablecer el idioma predeterminado. (1)\n");
      printf("                     -rst  Restaura el modo inicial. (2)\n");
      printf("        (1)(2) - La funcionalidad cambia dependiendo de la presencia o ausencia\n");
      printf("                 de archivo de configuracion.\n");
      printf("\nSeñalizadores: P  Marcado de los números primos de la serie de números mostrada.\n");
      printf("               S  Marcado de un factor primo de descomposición en la serie numérica mostrada.\n");
      printf("               U  Marcado ascendente a partir de un factor primo indicado en la serie de números mostrada.\n");
      printf("               D  Marcado descendente a partir de un factor primo indicado en la serie de números mostrada.\n");
      printf("\nOpciones de visualización de sangria justificada:\n");
      printf("          -lL  Visualizzar una serie de sólo números primos.\n");
      printf("          -qL  Visualización de una serie de números divisibles y factores primos de descomposición.\n");
      printf("\nOpciones de vista de tabla:\n");
      printf("          -nT  Mostrar en la serie numérica sólo los números que sean deisibles en varias columnas.\n");
      printf("          -pT  Mostrar sólo números primos en la serie numérica en varias columnas.\n");
      printf("\nEjemplos: %s 1234567890\n",argz);
      printf("          %s 1 65535\n",argz);
      printf("          %s -t 32768  98303\n",argz);
      printf("          %s 100 65635 | more\n",argz);
      printf("          %s -l 1 65535 >  $HOME/prime\n",argz);
      printf("          %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("          %s -y 1000 75535\n",argz);
      printf("          %s -f 1234 9999\n",argz);
      printf("          %s -k 1234 59999\n",argz);
      printf("          %s -d 1000 9999\n",argz);
      printf("          %s -p 1000 9999\n",argz);
      printf("          %s -nT 100 50000\n",argz);
      printf("          %s -pT 100 50000\n",argz);
      printf("          %s -qL 150 65500\n",argz);
      printf("          %s -fP 1234 39999 5\n",argz);
      printf("          %s -fS 1234 39999 5\n",argz);
      printf("          %s -yS 1234 39999 5\n",argz);
      printf("          %s -sU 12345 39999 13\n",argz);
      printf("          %s -b 1001 5000 16\n",argz);
      printf("          %s -c 1001 5000 7\n",argz);
      printf("          %s -v 2500 2999 7\n\n",argz);
      return;
   }

   /* *********************************************************************** */
   if(*flang==FRANCAIS) {
      printf("\n%s   Version : %s",argz,verrez);
      printf("\n~© (2010-2025) - F.S.F. GNU/GPL vers.3\n");
      printf("\nUtiliser : %s      Presentation.\n",argz);
      printf("           %s -?   Informations sur l'auteur et la licence.\n",argz);
      printf("           %s -?m  Manuel d'utilisation.\n",argz);
      printf("           %s -?i  Guide de dèmarrage rapide.\n",argz);
      printf("           %s -h   Aide rapide.\n",argz);
      printf("           %s --help  Aide detaillée.\n",argz);
      printf("           %s IT, EN, ES, FR, PT, DE  Selection de la langue locale.\n",argz);
      printf("           %s [arg_num]\n",argz);
      printf("           %s [arg_num_1] [arg_num_2]\n",argz);
      printf("           %s [option] [aiguilleur] [arg_num_1] [arg_num_2]\n",argz);
      printf("           %s [option] [aiguilleur] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("\nSynopsis : %s [-s | -f | -y | -d | -n | -p | -k | -t]  [val_num_1] [val_num_2]\n",argz);
      printf("           %s [-l | -q | -n | -p]  [L | T]  [val_num_1] [val_num_2]\n",argz);
      printf("           %s [-s | -f | -y | -d]  [S | U | D]  [val_num_1] [val_num_2] [val_num_3]\n",argz);
      printf("           %s [-b | -v | -c]  [val_num_1] [val_num_2] [val_num_3]\n\n",argz);
      printf("         [val_num_1] = Élément initial de la série numerique.\n");
      printf("         [val_num_2] = Élément final de la série numerique./Valeur discriminante pour la série.\n");
      printf("         [val_num_3] = Valeur discriminante pour l'affichage de la série.'\n");
      printf("\nOptions : -s  Facteurs premiers d'une décomposition en série affichés individuellement.\n");
      printf("          -y  Facteur premier affiché unique d'une série numérique.\n");
      printf("          -f  Facteurs premiers d'une série affichés en notation standard.\n");
      printf("          -k  Filtre les valeurs d'une série qui n'ont que deux facteurs premiers de décomposition.\n");
      printf("          -p  Série de nombres premiers uniquement affichée en notation standard.\n");
      printf("          -d  Série de facteurs de décomposition premiers uniquement affichés en notation standard.\n");
      printf("          -l  Série numérique contenant uniquement des nombres premiers affichés.\n");
      printf("          -q  Série numérique des seuls facteurs de décomposition premiers affichés.\n");
      printf("          -n  Série numérique de valeurs divisibles avec marquage positionnel des nombres premiers.\n");
      printf("          -t  Rapport statistique d'une série donnée de valeurs'.\n");
      printf("          -b  Decomposition en N séries numériques en fonction d'une séerie numérique donnée.\n");
      printf("          -v  Série sélective de valeurs pour un facteur de divisibilité arbitraire.\n");
      printf("          -c  Série de valeurs définies de A à B positions de N éléments.\n");
      printf("\nOptions spéciales : -clr  Supprimer le fichier de configuration de langue.\n");
      printf("                    -rst  Réinitialiser la langue par défaut. (1)\n");
      printf("                    -rst  Restaure le mode initial. (2)\n");
      printf("         (1)(2) - La functionnalité change en fonction de la présence ou de l'absence\n");
      printf("                  du fichier de configuration.\n");
      printf("\nSegnaleurs : P  Marquage des nombres premiers de la série de nombres affichée.\n");
      printf("             S  Marquage d'un facteur premier de décomposition dans la série numérique affichée.\n");
      printf("             U  Marquage croissant à partir d'un facteur premier indiqué dans la série de nombres affichée.\n");
      printf("             D  Marquage décroissant à partir d'un facteur premier indiqué dans la série de nombres affichée.\n");
      printf("\nOption d'affichage du retrait justifié :\n");
      printf("         -lL  Visualiser une série composée uniquement de nombres premiers.\n");
      printf("         -qL  affichage d'une série de nombres divisibles et de facteurs premiers de décomposition.\n");
      printf("\nOptions d'affichage du tableau:\n");
      printf("         -nT  Afficher dans la série numérique uniquement les nombres divisibles en plusieur colonnes.\n");
      printf("         -pT  Afficher uniquement les nombres premiers de la série numérique dans plusieurs colonnes.\n");
      printf("\nExemples : %s 1234567890\n",argz);
      printf("           %s 1 65535\n",argz);
      printf("           %s -t 32768  98303\n",argz);
      printf("           %s 100 65635 | more\n",argz);
      printf("           %s -l 1 65535 >  $HOME/prime\n",argz);
      printf("           %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("           %s -y 1000 75535\n",argz);
      printf("           %s -f 1234 9999\n",argz);
      printf("           %s -k 1234 59999\n",argz);
      printf("           %s -d 1000 9999\n",argz);
      printf("           %s -p 1000 9999\n",argz);
      printf("           %s -nT 100 50000\n",argz);
      printf("           %s -pT 100 50000\n",argz);
      printf("           %s -qL 150 65500\n",argz);
      printf("           %s -fP 1234 39999 5\n",argz);
      printf("           %s -fS 1234 39999 5\n",argz);
      printf("           %s -yS 1234 39999 5\n",argz);
      printf("           %s -sU 12345 39999 13\n",argz);
      printf("           %s -b 1001 5000 16\n",argz);
      printf("           %s -c 1001 5000 7\n",argz);
      printf("           %s -v 2500 2999 7\n\n",argz);
      return;
   }

   /* *********************************************************************** */
   if(*flang==PORTUGUES) {
      printf("\n%s   Versão: %s",argz,verrez);
      printf("\n~© (2010-2025) - F.S.F. GNU/GPL vers.3\n");
      printf("\nUsar: %s      Apresentação.\n",argz);
      printf("      %s -?   Informações sobre autor e licença.\n",argz);
      printf("      %s -?m  Manual do usuário.\n",argz);
      printf("      %s -?i  GUia de inicio rápido.\n",argz);
      printf("      %s -h   Ajuda rapida.\n",argz);
      printf("      %s --help  Ajuda detalhada.\n",argz);
      printf("      %s IT, EN, ES, FR, PT, DE  Seleção do idioma local.\n",argz);
      printf("      %s [arg_num]\n",argz);
      printf("      %s [arg_num_1] [arg_num_2]\n",argz);
      printf("      %s [opção] [sinalizador] [arg_num_1] [arg_num_2]\n",argz);
      printf("      %s [opção] [sinalizador] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("\nSinopse: %s [-s | -f | -y | -d | -n | -p | -k | -t]  [val_num_1] [val_num_2]\n",argz);
      printf("         %s [-l | -q | -n | -p]  [L | T]  [val_num_1] [val_num_2]\n",argz);
      printf("         %s [-s | -f | -y | -d]  [S | U | D]  [val_num_1] [val_num_2] [val_num_3]\n",argz);
      printf("         %s [-b | -v | -c]  [val_num_1] [val_num_2] [val_num_3]\n\n",argz);
      printf("       [val_num_1] = Elemento inicial da série numérica.\n");
      printf("       [val_num_2] = Elemento final da série numérica./Valor discriminante para a série.\n");
      printf("       [val_num_3] = Valor discriminante para exibição da série.\n");
      printf("\nOpções: -s  Fatores primos de uma decomposição em série exibidos individualmente.\n");
      printf("        -y  Fator primo único exibido de uma série numérica.\n");
      printf("        -f  Fatores primos de uma série exibidos em notação padrão.\n");
      printf("        -k  Filtra valores em uma série que possuem apenas dois factores primos de decomposição.\n");
      printf("        -p  Série de apenas números primos exibidos em notação padrão.\n");
      printf("        -d  Série de fatores de decomposição apenas primos exibidos em notação padrão.\n");
      printf("        -l  Série numérica de apenas números primos exibidos.\n");
      printf("        -q  Série numéricas de fatores de decomposição primos exibidos apenas.\n");
      printf("        -n  Série numéricas de valores divisíveis com marcação posicional dos números primos.\n");
      printf("        -t  Relatório estatístico de uma determinada série de valores.\n");
      printf("        -b  Decomposição em N séries numéricas em função de uma dada série numérica.\n");
      printf("        -v  Série seletiva de valores para um fator de divisibilidade arbitrário.\n");
      printf("        -c  Série de valores definidos das posições A a B de N elementos.\n");
      printf("\nOpções especiais: -clr  Exclua o arquivo de configuração de idioma.\n");
      printf("                  -rst  Redefinir para o idioma padrão. (1)\n");
      printf("                  -rst  Restaura o modo inicial. (2)\n");
      printf("       (1)(2) - A funcionalidade muda dependendo da presença ou ausência do arquivo de configuração.\n");
      printf("\nSinalizadores: P  Marcação dos números primos da série numérica exibida.\n");
      printf("               S  Marcação de um fator primo de decomposição na série numérica exibida.\n");
      printf("               U  Marcação ascendente a partir de um fator primo indicado na série numérica exibida.\n");
      printf("               D  Marcação decrecendente a partir de um fator primo indicado na série numérica exibida.\n");
      printf("\nOpções de exibição de recuo Justificado:\n");
      printf("        -lL  Visualizando uma série de apenas números primos.\n");
      printf("        -qL  exibindo uma série de números divisiveis e fatore primos de decomposição.\n");
      printf("\nOpções de visualização de tabela:\n");
      printf("        -nT  Exibir na série numérica somente números que são divisíveis em multiplas colunas.\n");
      printf("        -pT  Exibir somente números primos na série numérica em várias colunas.\n");
      printf("\nEsemplos: %s 1234567890\n",argz);
      printf("          %s 1 65535\n",argz);
      printf("          %s -t 32768  98303\n",argz);
      printf("          %s 100 65635 | more\n",argz);
      printf("          %s -l 1 65535 >  $HOME/prime\n",argz);
      printf("          %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("          %s -y 1000 75535\n",argz);
      printf("          %s -f 1234 9999\n",argz);
      printf("          %s -k 1234 59999\n",argz);
      printf("          %s -d 1000 9999\n",argz);
      printf("          %s -p 1000 9999\n",argz);
      printf("          %s -nT 100 50000\n",argz);
      printf("          %s -pT 100 50000\n",argz);
      printf("          %s -qL 150 65500\n",argz);
      printf("          %s -fP 1234 39999 5\n",argz);
      printf("          %s -fS 1234 39999 5\n",argz);
      printf("          %s -yS 1234 39999 5\n",argz);
      printf("          %s -sU 12345 39999 11\n",argz);
      printf("          %s -b 1001 5000 16\n",argz);
      printf("          %s -c 1001 5000 7\n",argz);
      printf("          %s -v 2500 2999 7\n\n",argz);
      return;
   }

   /* *********************************************************************** */
   if(*flang==DEUTCHE) {
      printf("\n%s   Version: %s",argz,verrez);
      printf("\n~© (2010-2025) - F.S.F. GNU/GPL vers.3\n");
      printf("\nVerwenden: %s      Präsentation.\n",argz);
      printf("           %s -?   Autoren und Lizenzinformationen.\n",argz);
      printf("           %s -?m  Benutzerhandbuch.\n",argz);
      printf("           %s -?i  Kurzanleitung.\n",argz);
      printf("           %s -h   Schnelle Hilfe.\n",argz);
      printf("           %s --help  Ausführliche Hilfe.\n",argz);
      printf("           %s IT, EN, ES, FR, PT, DE  Lokale Sprachauswahi.\n",argz);
      printf("           %s [arg_num]\n",argz);
      printf("           %s [arg_num_1] [arg_num_2]\n",argz);
      printf("           %s [option] [signalgeber] [zahl_arg_1] [zahl_arg_2]\n",argz);
      printf("           %s [option] [signalgeber] [zahl_arg_1] [zahl_arg_2] [arg_num_3]\n",argz);
      printf("\nÜberblick: %s [-s | -f | -y | -d | -n | -p | -k | -t]  [numm_wer_1] [numm_wert_2]\n",argz);
      printf("           %s [-l | -q | -n | -p]  [L | T]  [numm_wer_1] [numm_wert_2]\n",argz);
      printf("           %s [-s | -f | -y | -d]  [S | U | D]  [numm_wert_1] [numm_wert_2] [numm_wert_3]\n",argz);
      printf("           %s [-b | -v | -c]  [numm_wert_1] [numm_wert_2] [numm_wert_3]\n\n",argz);
      printf("         [numm_wert_1] = Anfangselement der Zahlenreihe.\n");
      printf("         [numm_wert_2] = Letztes Element der Zahlenreihe./Diskriminantzwert für die Reihe.\n");
      printf("         [numm_wert_3] = Diskriminanzwert zur Darstellung der Reihe.\n");
      printf("\nOptionen: -s  Primfaktoren einer Reihenzerlegung einzeln dargestellt.\n");
      printf("          -y  Einzelner angezeigter Primfaktor einer Zahlenreihe.\n");
      printf("          -f  Primfaktoren einer Reihe dargestellt in Standardnotation.\n");
      printf("          -k  Filtert Werte in einer Reihe, die nur zwei Primfaktoren der Zerlegung haben.\n");
      printf("          -p  Reihe von ausschließlich Primzahlen dargestellt in Standardnotation.\n");
      printf("          -d  Reihe von ausschließlich Primzerlegungsfaktoren angezeigt in Standardnotation.\n");
      printf("          -l  Es werden Zahlenreihen mit ausschließlich angezeigten Primzahlen angezeigt.\n");
      printf("          -q  Zahlenreihe der ausschließlich angezeigten Primzerlegungsfaktoren.\n");
      printf("          -n  Zahlenreihe teilbaler Werte mit Stellenmarkierung der Primzahlen.\n");
      printf("          -t  Statistischer Bericht einer gegebenen Wertereihe.\n");
      printf("          -b  Zerlegung in N Zahlenreihen als Funktion einer gegebenen Zahlenreihe.\n");
      printf("          -v  Selektive Wertereihe für einen beliebigen Teilbarkeitsfaktor.\n");
      printf("          -c  Wertereihe definiert von den Positionen A bis B der N Elemente.\n");
      printf("\nSpezielle Optionen: -clr  Löschen Sie die Sprachkon figurationsdatei.\n");
      printf("                    -rst  Auf Standardsprache zurücksetzen. (1)\n");
      printf("                    -rst  Stellt den Ausgangsmodus wieder her. (2)\n");
      printf("         (1)(2) - Die Funktionalität ändert sich je nach Vorhandensein\n");
      printf("                  oder Fehlen der Konfigurationsdatei.\n");
      printf("\nSignalgeber: P  Markierung der Primzahlen der angezeigten Zahlenreihe.\n");
      printf("             S  Markierung eines Primfaktors der Zeiegung in der angezeigten Zahlenreihe.\n");
      printf("             U  Aufsteigende Markierung ab einem ausgewählten Primfaktor in der angezeigten Zahlenreihe.\n");
      printf("             D  Absteigende Markierung ab einem ausgewählten Primfaktor in der angezeigten Zahlenreihe.\n");
      printf("\nAnzeigeoptionen für Blocksatzeinzug:\n");
      printf("          -lL  Visualisieren einer Reihe die ausschließlich aus Primzahlen besteht.\n");
      printf("          -qL  Anzeige einer Reihe teilbarer Zahlen und Primfaktoren der Zerlegung.\n");
      printf("\nOptionen für die Tabellenansicht:\n");
      printf("          -nT  Zeigen Sie in der Zahlenreihe nur Zahlen an die auf mehrere Spalten aufgeteilt werden können.\n");
      printf("          -pT  In der Zahlenreihe werden in mehreren Spalten nur Primzahlen angezeigt.\n");
      printf("\nBeispiele: %s 1234567890\n",argz);
      printf("           %s 1 65535\n",argz);
      printf("           %s -t 32768  98303\n",argz);
      printf("           %s 100 65635 | more\n",argz);
      printf("           %s -l 1 65535 >  $HOME/prime\n",argz);
      printf("           %s -q 1 65535 >> $HOME/pfact\n",argz);
      printf("           %s -y 1000 75535\n",argz);
      printf("           %s -f 1234 9999\n",argz);
      printf("           %s -k 1234 59999\n",argz);
      printf("           %s -d 1000 9999\n",argz);
      printf("           %s -p 1000 9999\n",argz);
      printf("           %s -nT 100 50000\n",argz);
      printf("           %s -pT 100 50000\n",argz);
      printf("           %s -qL 150 65500\n",argz);
      printf("           %s -fP 1234 39999 5\n",argz);
      printf("           %s -fS 1234 39999 5\n",argz);
      printf("           %s -yS 1234 39999 5\n",argz);
      printf("           %s -sU 12345 39999 11\n",argz);
      printf("           %s -b 1001 5000 16\n",argz);
      printf("           %s -c 1001 5000 7\n",argz);
      printf("           %s -v 2500 2999 7\n\n",argz);
      return;
   }

   /* *********************************************************************** */
}
/* Fine della funzione helpfunc(). */

/* Fine delle funzioni di stampa di aiuto. */


/* -------------- ----- */
/* ---- Contributo ---- */
/* -------------------- */
void contrib(char *fseq1,char *fseq2) {

/* Corpo funzione. */
   printf("%s - %s\n",fseq1,fseq2);
   putchar('\n');
   fprintf(stdout,"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
   fprintf(stdout,"(Un pensiero illuminante)\n");
   fprintf(stdout,"Per portare a compimento progetti al limite dell'incredibile bisogna innanzi-\n");
   fprintf(stdout,"tutto crederci, oltre ad avere anche un pò di fortuna, ma soprattutto occorre\n");
   fprintf(stdout,"estrema concentrazione, dedizione ed impegno nel proprio lavoro, perseverando\n");
   fprintf(stdout,"oltre ogni limite, sempre, qualsiasi cosa succeda...  pregando e sperando che\n");
   fprintf(stdout,"nonostante tutto alla fine ce la possiamo fare... la nazione lo richiede, ora\n");
   fprintf(stdout,"abbiamo questa grande possibilità... quindi (noi) ce la faremo.\n");
   fprintf(stdout,"(16 Luglio 1969 Apollo 11 - NASA, direttore di missione Eugene Francis Kranz)\n");
   fprintf(stdout,"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
   return;
}
/* Fine della funzione contrib(). */

/* Funzione di controllo di speciali gruppi di opzioni. */
short globoptions(void) {

/* Dichiarazione di variabili esterne. */
   extern char option;

/* Corpo funzione. */
   switch(option) {
      case NOPT:         /* Nessuna opzione. Argomento numerico. */
         return NOGOPT;

   /* Non supportano alcuno Switch, e richiedono tre argomenti numerici */
   /* ad eccezione di KEYS e STAT che ne richiedono obbligatoriamente solo due. */
      case KEYS:        /* Opzione '-K'. */
      case STAT:        /* Opzione '-T'. */
      case BASE:        /* Opzione '-B'. */
      case VARS:        /* Opzione '-V'. */
      case CALC:        /* Opzione '-C'. */
         return GLOB1;

   /* Supportano anche gli Switch che richiedono obbligatoriamente tre argomenti. */
   /* L'opzione '-D' (DIVS) non supporta lo Switch 'P' (PME). */
   /* Nessuna opzione supporta lo Switch 'T' (TBL). */
   /* Nessuna opzione supporta lo Switch 'L' (LST). */
      case TINS:         /* Opzione '-Y'. */
      case SYMP:         /* Opzione '-S'. */
      case FORM:         /* Opzione '-F'. */
      case DIVS:         /* Opzione '-D'. */
         return GLOB2;

   /* Supportano anche gli Switch, ma richiedono obbligatoriamente solo due argomenti. */
   /* Le opzioni '-P' (PRIME) ed '-N' (NPRIM) supportano solo lo Switch 'T' (TBL). */
   /* Le opzioni '-L' (PLIST) ed '-Q' (NSDIV) supportano solo lo Switch 'L' (LST). */
      case PRIME:        /* Opzione '-P'. */
      case NPRIM:        /* Opzione '-N'. */
      case PLIST:        /* Opzione '-L'. */
      case NSDIV:        /* Opzione '-Q'. */
         return GLOB3;
   }
   return ERRSG; /* Codice di ritorno se l'opzione esiste ed è errata. */
}
/* Fine della funzione globoptions() */


/* Funzione di controllo delle opzioni e dei gruppi di opzioni. */
short trueoptions(void) {

/* Dichiarazione di variabili esterne. */
   extern char option;

/* Corpo funzione. */
   switch(option) {
      case NOPT:       /* Nessuna opzione. Argomento numerico. */
         return ZERO;
      case DIVS:       /* Opzione '-D'. */
      case NSDIV:      /* Opzione '-Q'. */
      case KEYS:       /* Opzione '-K'. */
         return ONE;
      case TINS:       /* Opzione '-Y'. */
      case SYMP:       /* Opzione '-S'. */
      case FORM:       /* Opzione '-F'. */
         return TWO;
      case PRIME:      /* Opzione '-P'. */
      case PLIST:      /* Opzione '-L'. */
         return TREE;
      case NPRIM:      /* Opzione '-N'. */
         return FOUR;
      case STAT:       /* Opzione '-T'. */
         return FIVE;
      case BASE:       /* Opzione '-B'. */
         return BSS;
      case VARS:       /* Opzione '-V'. */
         return VRL;
      case CALC:       /* Opzione '-C'. */
         return CMP;
      case QHLP:       /* Opzione speciale '-H'. */
      case LINF:       /* Opzione speciale '-?'. */
         return HLP;
      case EHLP:       /* Opzione speciale '--' (HELP). */
         return ISPC;
   }
   return ERRS; /* Codice di ritorno se l'opzione esiste ed è errata. */
}
/* Fine della funzione trueoptions(). */


/* Funzione di controllo dei gruppi di Switch. */
short trueswitch(void) {

/* Dichiarazione di variabili esterne. */
   extern char subopt;

/* Corpo funzione. */
   switch(subopt) {
      case NSWT:         /* Nessuno Switch specificato. */
         return NOSWT;
      case SEL:          /* Switch 'S'. */
      case UPP:          /* Switch 'U'. */
      case DOW:          /* Switch 'D'. */
         return TRUESW;
      case PME:          /* Switch 'P'. */
         return TRUEPM;
      case LST:          /* Switch 'L'. */
         return LISTSW;
      case TBL:          /* Switch 'T'. */
         return NCOLTP;
      case ISW:          /* Switch 'I'. */
      case SSC:          /* Switch 'F'. */
      case MAN:          /* Switch 'M'. */
         return SPECSW;
      case EHL:          /* Switch 'HELP'. */
         return HELPSW;
   }
   return ERRSW; /* Codice di ritorno se lo Switch esiste ed è errato. */
}
/* Fine della funzione trueswitch(). */


/* Funzione di controllo degli Switch in base all'opzione specifica. */
short switcherrs(void) {

/* Dichiarazione di funzioni. */
   short trueoptions(void);
   short trueswitch(void);

/* Dichiarazione di variabili esterne. */
   extern char option,subopt;

/* Corpo funzione. */
/* Se nessuna opzione esiste. */
   if(option==NOPT&&subopt==NSWT)
      return OK;

/* Se le opzioni sono '-S', '-F' o '-Y'. */
/* Se gli Switch sono 'S', 'U', 'D' o 'P'. */
   if(trueoptions()==TWO&&trueswitch()<=TRUEPM)
      return OK;

/* Se l'opzione è '-D'. */
/* Se gli Switch sono 'S', 'U', 'D'. */
   else if(option==DIVS&&trueswitch()<=TRUESW)
      return OK;

/* Se l'opzione è '-K'. */
/* Se gli Switch sono 'S', 'U', 'D'. */
   else if(option==KEYS&&trueswitch()<=TRUESW)
      return OK;

/* Se l'opzione è '-Q'. */
/* Se lo Switch è 'L'. */
   else if(option==NSDIV&&trueswitch()==LISTSW)
      return OK;

/* Se l'opzione è '-L'. */
/* Se lo Switch è 'L'. */
   else if(option==PLIST&&trueswitch()==LISTSW)
      return OK;

/* Se l'opzione è '-P'. */
/* Se lo Switch è 'T'. */
   else if(option==PRIME&&trueswitch()==NCOLTP)
      return OK;

/* Se l'opzione è '-N'. */
/* Se lo Switch è 'T'. */
   else if(option==NPRIM&&trueswitch()==NCOLTP)
      return OK;

/* Se l'opzione speciale è '-?'. */
/* Se gli Switch sono 'I', 'F' o 'M'. */
   else if(option==LINF&&trueswitch()==SPECSW)
      return OK;

/* Se L'opzione speciale è '--'. */
/* Se lo Switch è 'HELP'. */
   else if(option==EHLP&&trueswitch()==HELPSW)
      return OK;

/* Se le opzioni sono '-P', '-N', '-L', '-Q', -K, '-T', '-B', '-V' o '-C'. */
/* Controllo necessario per le opzioni eseguite senza Switch - */
/* -> che lo supportano oppure che non lo supportano. */
   else if(((trueoptions()>=TREE&&trueoptions()<ISPC)&&trueswitch()==NOSWT)
     ||((option==NSDIV||option==KEYS)&&trueswitch()==NOSWT))
      return OK;

/* Se le opzioni sono '-T', '-B', '-V' o '-C'. */
   else if(globoptions()==GLOB1&&trueswitch()==NOSWT)
      return OK;

/* Se le opzioni speciali sono '-H', '--' e '-?'. */
   else if(trueoptions()==HLP&&trueswitch()==NOSWT)
      return OK;

   /* Se nessuna opzione e/o Switch risultano validi. */
      return ERROR;
}
/* Fine della funzione switcherrs(). */


/* Funzione di conversione del codice di errore e stampa della stringa. */
int errorstype(short *ferrscod) {

/* Corpo funzione. */
   switch(*ferrscod-1) {
      case 1000:   /* ENGLISH. */
         fprintf(stderr,"Error: Missing option and switches!\n\n");
         return ERROR;
      case 1001:   /* ITALIANO. */
         fprintf(stderr,"Errore: Opzione e Switch mancanti!\n\n");
         return ERROR;
      case 1002:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Faltan opciones e Switches!\n\n");
         return ERROR;
      case 1003:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Options et Switches manquants !\n\n");
         return ERROR;
      case 1004:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opçoes e Switches ausentes!\n\n");
         return ERROR;
      case 1005:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Optionen und Switches fehlen!\n\n");
         return ERROR;

      case 1010:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong option and switch!\n\n");
         return ERROR;
      case 1011:   /* ITALIANO. */
         fprintf(stderr,"Errore: Opzione e Switch errati!\n\n");
         return ERROR;
      case 1012:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Opción y Switch incorrectos!\n\n");
         return ERROR;
      case 1013:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : mauvaise option et mauvais Switch !\n\n");
         return ERROR;
      case 1014:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opçao e Switch erradas!\n\n");
         return ERROR;
      case 1015:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Falsche Option und Switch!\n\n");
         return ERROR;

      case 1020:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong option!\n\n");
         return ERROR;
      case 1021:   /* ITALIANO. */
         fprintf(stderr,"Errore: Opzione errata!\n\n");
         return ERROR;
      case 1022:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Opción incorrecta!\n\n");
         return ERROR;
      case 1023:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Mauvaise option !\n\n");
         return ERROR;
      case 1024:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opção errada!\n\n");
         return ERROR;
      case 1025:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Falsche Option!\n\n");
         return ERROR;

      case 1030:   /* ENGLISH. */
         fprintf(stderr,"Error: Missing option!\n\n");
         return ERROR;
      case 1031:   /* ITALIANO. */
         fprintf(stderr,"Errore: Opzione mancante!\n\n");
         return ERROR;
      case 1032:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Falta Opción!\n\n");
         return ERROR;
      case 1033:   /* FRANÇAIS. */
         fprintf(stderr,"Error : option manquante !\n\n");
         return ERROR;
      case 1034:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opçao ausente!\n\n");
         return ERROR;
      case 1035:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Fehlende Option!\n\n");
         return ERROR;

      case 1040:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong switch!\n\n");
         return ERROR;
      case 1041:   /* ITALIANO.*/
         fprintf(stderr,"Errore: Switch errato!\n\n");
         return ERROR;
      case 1042:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Switch incorrecto!\n\n");
         return ERROR;
      case 1043:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Mauvais Switch !\n\n");
         return ERROR;
      case 1044:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Switch errado!\n\n");
         return ERROR;
      case 1045:   /* DEUTCHE. */
         fprintf(stderr,"fehler: Falscher Switch!\n\n");
         return ERROR;

      case 1050:   /* ENGLISH. */
         fprintf(stderr,"Error: Invalid switch and option combination!\n\n");
         return ERROR;
      case 1051:   /* ITALIANO. */
         fprintf(stderr,"Errore: Combinazione dell'opzione con Switch non valida!\n\n");
         return ERROR;
      case 1052:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Combinación de opciones no válida con Switch!\n\n");
         return ERROR;
      case 1053:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : combinaison d'option non valide avec Switch !\n\n");
         return ERROR;
      case 1054:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Combinação inválida de opção com Switch!\n\n");
         return ERROR;
      case 1055:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Ungültige Kombination der Option mit Switch!\n\n");
         return ERROR;

      case 1060:   /* ENGLISH. */
         fprintf(stderr,"Error: Missing argument!\n\n");
         return ERROR;
      case 1061:   /* ITALIANO. */
         fprintf(stderr,"Errore: Argomento mancante!\n\n");
         return ERROR;
      case 1062:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Falta tema!\n\n");
         return ERROR;
      case 1063:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Sujet manquant !\n\n");
         return ERROR;
      case 1064:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Topico ausente!\n\n");
         return ERROR;
      case 1065:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Fehlendes Thema!\n\n");
         return ERROR;

      case 1070:   /* ENGLISH. */
         fprintf(stderr,"Error: Missing arguments!\n\n");
         return ERROR;
      case 1071:   /* ITALIANO. */
         fprintf(stderr,"Errore: Argomenti mancanti!\n\n");
         return ERROR;
      case 1072:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Faltan argumentos!\n\n");
         return ERROR;
      case 1073:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Arguments manquants !\n\n");
         return ERROR;
      case 1074:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Argumentos ausentes!\n\n");
         return ERROR;
      case 1075:   /* DEUTCHE. */
         fprintf(stderr,"Errer: Fechlende Argumente!\n\n");
         return ERROR;

      case 1080:   /* ENGLISH. */
         fprintf(stderr,"Error: Missing option, switch and arguments!\n\n");
         return ERROR;
      case 1081:   /* ITALIANO. */
         fprintf(stderr,"Errore: Opzione, Switch ed argomenti mancanti!\n\n");
         return ERROR;
      case 1082:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Faltan opciones, Switches y argumentos!\n\n");
         return ERROR;
      case 1083:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Option,Switch et arguments manquants !\n\n");
         return ERROR;
      case 1084:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opção,Switch e argumentos faltando!\n\n");
         return ERROR;
      case 1085:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Option,Schalter und Argumente fehlen!\n\n");
         return ERROR;

      case 1090:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong argument!\n\n");
         return ERROR;
      case 1091:   /* ITALIANO. */
         fprintf(stderr,"Errore: Argomento errato!\n\n");
         return ERROR;
      case 1092:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Tema incorrecto!\n\n");
         return ERROR;
      case 1093:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : suject incorrect !\n\n");
         return ERROR;
      case 1094:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Tópico incorreto!\n\n");
         return ERROR;
      case 1095:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Falsches Thema!\n\n");
         return ERROR;

      case 1100:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong and/or missing argument!\n\n");
         return ERROR;
      case 1101:   /* ITALIANO. */
         fprintf(stderr,"Errore: Argomento errato e/o mancante!\n\n");
         return ERROR;
      case 1102:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Argumento incorrecto o faltante!\n\n");
         return ERROR;
      case 1103:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : argument incorrect et/ou manquant !\n\n");
         return ERROR;
      case 1104:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Argumento incorreto e/ou ausente!\n\n");
         return ERROR;
      case 1105:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Falsches und/oder fehlendes Argument!\n\n");
         return ERROR;

      case 1110:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong option and/or arguments!\n\n");
         return ERROR;
      case 1111:   /* ITALIANO. */
         fprintf(stderr,"Errore: Opzione e/o argomenti errati!\n\n");
         return ERROR;
      case 1112:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Opción y/o argumentos incorrectos!\n\n");
         return ERROR;
      case 1113:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : option et/ou arguments incorrects !\n\n");
         return ERROR;
      case 1114:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opçao e/ou argumentos incorretos!\n\n");
         return ERROR;
      case 1115:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Falsche Option und/oder Argumente!\n\n");
         return ERROR;

      case 1120:   /* ENGLISH. */
         fprintf(stderr,"Error: Too many arguments!\n\n");
         return ERROR;
      case 1121:   /* ITALIANO. */
         fprintf(stderr,"Errore: Troppi argomenti!\n\n");
         return ERROR;
      case 1122:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Demasiados temas!\n\n");
         return ERROR;
      case 1123:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : trop de suject !\n\n");
         return ERROR;
      case 1124:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Muito tópicos!\n\n");
         return ERROR;
      case 1125:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Zu viele Themen!\n\n");
         return ERROR;

      case 1130:   /* ENGLISH. */
         fprintf(stderr,"Error: No arguments are required!\n\n");
         return ERROR;
      case 1131:   /* ITALIANO. */
         fprintf(stderr,"Errore: Non è richiesto alcun argomento!\n\n");
         return ERROR;
      case 1132:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡No se requieren argumentos!\n\n");
         return ERROR;
      case 1133:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : aucun argument requis !\n\n");
         return ERROR;
      case 1134:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Nenhum argumento é necessário!\n\n");
         return ERROR;
      case 1135:   /* DEUTCHE. */
         fprintf(stderr,"fehler: kein Argument erforderlich!\n\n");
         return ERROR;

      case 1140:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong arguments! Values out of range.\n\n");
         return ERROR;
      case 1141:   /* ITALIANO. */
         fprintf(stderr,"Errore: Argomenti errati! Valori fuori limite.\n\n");
         return ERROR;
      case 1142:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Argumentos incorrectos! Valores fuera de rango.\n\n");
         return ERROR;
      case 1143:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : argumentsincorrects ! Des valeurs hors limites.\n\n");
         return ERROR;
      case 1144:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Argumentos incorrectos! Valores fora da faixa.\n\n");
         return ERROR;
      case 1145:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Falsche Argumente! Werte außerhalb des Bereichs.\n\n");
         return ERROR;

      case 1150:   /* ENGLISH. */
         fprintf(stderr,"Error: Inverted argument values!\n\n");
         return ERROR;
      case 1151:   /* ITALIANO. */
         fprintf(stderr,"Errore: Valori degli argomenti invertiti!\n\n");
         return ERROR;
      case 1152:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Valores de argumento invertidos!\n\n");
         return ERROR;
      case 1153:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : valeurs d'argument inversées !\n\n");
         return ERROR;
      case 1154:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Valores dos argumentos invertidos!\n\n");
         return ERROR;
      case 1155:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Argumentwerte vertauscht!\n\n");
         return ERROR;

      case 1160:   /* ENGLISH. */
         fprintf(stderr,"Error: Range of values too large!\n\n");
         return ERROR;
      case 1161:   /* ITALIANO. */
         fprintf(stderr,"Errore: Intervallo di valori troppo grande!\n\n");
         return ERROR;
      case 1162:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Rango de valores demasiado grande!\n\n");
         return ERROR;
      case 1163:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : plage de valeurs trop grande !\n\n");
         return ERROR;
      case 1164:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Faixa de valores muito grande!\n\n");
         return ERROR;
      case 1165:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Wertebereich zu groß!\n\n");
         return ERROR;

      case 1170:   /* ENGLISH. */
         fprintf(stderr,"Error: Numerical series too large!\n\n");
         return ERROR;
      case 1171:   /* ITALIANO. */
         fprintf(stderr,"Errore: Serie numerica troppo grande!\n\n");
         return ERROR;
      case 1172:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡La serie numérica es demasiado grande!\n\n");
         return ERROR;
      case 1173:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Série de numéros trop grande !\n\n");
         return ERROR;
      case 1174:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: série numérica muito grande!\n\n");
         return ERROR;
      case 1175:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Zahlenreihe zu groß!\n\n");
         return ERROR;

      case 1180:   /* ENGLISH. */
         fprintf(stderr,"Error: Value too large!\n\n");
         return ERROR;
      case 1181:   /* ITALIANO. */
         fprintf(stderr,"Errore: Valore troppo grande!\n\n");
         return ERROR;
      case 1182:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Valor demasiado grande!\n\n");
         return ERROR;
      case 1183:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Valeur trop grande !\n\n");
         return ERROR;
      case 1184:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Valor muito grande!\n\n");
         return ERROR;
      case 1185:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Wert zu groß!\n\n");
         return ERROR;

      case 1190:   /* ENGLISH. */
         fprintf(stderr,"\nError: Selected value too large or too small!\n\n");
         return ERROR;
      case 1191:   /* ITALIANO. */
         fprintf(stderr,"\nErrore: Valore selezionato troppo grande o troppo piccolo!\n\n");
         return ERROR;
      case 1192:   /* ESPAÑOL. */
         fprintf(stderr,"\nError: ¡El valor seleccionado es demasiado grande o demasiado pequeño!\n\n");
         return ERROR;
      case 1193:   /* FRANÇAIS. */
         fprintf(stderr,"\nErreur : valeur sélectionnée trop grande ou trop petite !\n\n");
         return ERROR;
      case 1194:   /* PORTUGÛES. */
         fprintf(stderr,"\nErro: Valor selecionado muito grande ou muito perqueno!\n\n");
         return ERROR;
      case 1195:   /* DEUTCHE. */
         fprintf(stderr,"\nFehler: Ausgewahlter Wert zu groß zu klein!\n\n");
         return ERROR;

      case 1200:   /* ENGLISH. */
         fprintf(stderr,"Error: Invalid value range!\n\n");
         return ERROR;
      case 1201:   /* ITALIANO. */
         fprintf(stderr,"Errore: Intervallo dei valori non valido!\n\n");
         return ERROR;
      case 1202:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Rango de valores no válido!\n\n");
         return ERROR;
      case 1203:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Plage de valeurs non valide !\n\n");
         return ERROR;
      case 1204:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Intervalo de valores inválido!\n\n");
         return ERROR;
      case 1205:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Ungültiger Wertebereich!\n\n");
         return ERROR;

      case 1210:   /* ENGLISH. */
         fprintf(stderr,"Error: Values too large!\n\n");
         return ERROR;
      case 1211:   /* ITALIANO. */
         fprintf(stderr,"Errore: Valori troppo grandi!\n\n");
         return ERROR;
      case 1212:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Valores demasiado grandes!\n\n");
         return ERROR;
      case 1213:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Valeurs trop grandes !\n\n");
         return ERROR;
      case 1214:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Valores muito grandes!\n\n");
         return ERROR;
      case 1215:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Werte zu groß!\n\n");
         return ERROR;

      case 1220:   /* ENGLISH. */
         fprintf(stderr,"Error: Invalid number series!\n\n");
         return ERROR;
      case 1221:   /* ITALIANO. */
         fprintf(stderr,"Errore: Serie numerica non valida!\n\n");
         return ERROR;
      case 1222:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Serie numérica no válida!\n\n");
         return ERROR;
      case 1223:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : série numérique invalide !\n\n");
         return ERROR;
      case 1224:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Série numérica inválida!\n\n");
         return ERROR;
      case 1225:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Ungültige Zahlenreihe!\n\n");
         return ERROR;

      case 1230:   /* ENGLISH. */
         fprintf(stderr,"Error: Selected value out of limit!\n\n");
         return ERROR;
      case 1231:   /* ITALIANO. */
         fprintf(stderr,"Errore: Valore selezionato fuori limite!\n\n");
         return ERROR;
      case 1232:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Valor seleccionado fuera del limite!\n\n");
         return ERROR;
      case 1233:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : valeur sélectionnée hors limite !\n\n");
         return ERROR;
      case 1234:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Valor selecionado fora do limite!\n\n");
         return ERROR;
      case 1235:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Ausgewählter Wert außerhalb des Grenzwertes!\n\n");
         return ERROR;

      case 1240:   /* ENGLISH. */
         fprintf(stderr,"Error: The option does not accept any type of switch!\n\n");
         return ERROR;
      case 1241:   /* ITALIANO. */
         fprintf(stderr,"Errore: L'opzione non accetta alcun tipo di Switch!\n\n");
         return ERROR;
      case 1242:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡La opción no acepta ningún tipo de Switch!\n\n");
         return ERROR;
      case 1243:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : l'option n'accepte aucun type de switch !\n\n");
         return ERROR;
      case 1244:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: A opção não aceita nenhum tipo de Switch!\n\n");
         return ERROR;
      case 1245:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Die Option akzeptiert keine Art von Switch!\n\n");
         return ERROR;

      case 1250:   /* ENGLISH. */
         fprintf(stderr,"Prime factor of decomposition, not present.\n");
         return ERROR;
      case 1251:   /* ITALIANO. */
         fprintf(stderr,"Fattori primi di scomposizione indicati, non presenti.\n");
         return WARNING;
      case 1252:   /* ESPAÑOL. */
         fprintf(stderr,"Factores primos de descomposición, no presentes.\n");
         return WARNING;
      case 1253:   /* FRANÇAIS. */
         fprintf(stderr,"Facteurs premiers de décomposition, absents.\n");
         return WARNING;
      case 1254:   /* PORTUGÛES. */
         fprintf(stderr,"Factores primos de decomposição, ausentes.\n");
         return WARNING;
      case 1255:   /* DEUTCHE. */
         fprintf(stderr,"Primäfaktoren der Zerlegung nicht vorhanden.\n");
         return WARNING;

      case 1260:   /* ENGLISH. */
         fprintf(stderr,"Error: Order of greatness exceeded!\n");
         return ERROR;
      case 1261:   /* ITALIANO. */
         fprintf(stderr,"Errore: Ordine di grandezza superato!\n");
         return ERROR;
      case 1262:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Orden de magnitud excedido!\n");
         return ERROR;
      case 1263:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Ordre de grandeur dépassé !\n");
         return ERROR;
      case 1264:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Ordem de grandeza excedida!\n");
         return ERROR;
      case 1265:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Größenordnung überschritten!\n");
         return ERROR;

   /* Modello di riferimento. */
      case 1290:   /* ENGLISH. */
         fprintf(stderr,"__________________________________________________\r");
         return ERROR;
      case 1291:   /* ITALIANO. */
         fprintf(stderr,"__________________________________________________\r");
         return ERROR;
      case 1292:   /* ESPAÑOL. */
         fprintf(stderr,"__________________________________________________\r");
         return ERROR;
      case 1293:   /* FRANÇAIS. */
         fprintf(stderr,"__________________________________________________\r");
         return ERROR;
      case 1294:   /* PORTUGÛES. */
         fprintf(stderr,"__________________________________________________\r");
         return ERROR;
      case 1295:   /* DEUTCHE. */
         fprintf(stderr,"__________________________________________________\r");
         return ERROR;

   /* Specifici per errori multipli. */
      case 1510:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong option and switch!\n");
         return ERROR;
      case 1511:   /* ITALIANO. */
         fprintf(stderr,"Errore: Opzione e Switch errati!\n");
         return ERROR;
      case 1512:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Opción y Switch incorrectos!\n");
         return ERROR;
      case 1513:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : mauvaise option et mauvais Switch !\n");
         return ERROR;
      case 1514:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opçao e/or Switch errados!\n");
         return ERROR;
      case 1515:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Falsche Option und Switch!\n");
         return ERROR;

      case 1520:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong option!\n");
         return ERROR;
      case 1521:   /* ITALIANO. */
         fprintf(stderr,"Errore: Opzione errata!\n");
         return ERROR;
      case 1522:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Opción incorrecta!\n");
         return ERROR;
      case 1523:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Mauvaise option !\n");
         return ERROR;
      case 1524:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opção errada!\n");
         return ERROR;
      case 1525:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Falsche Option!\n");
         return ERROR;

      case 1540:   /* ENGLISH. */
         fprintf(stderr,"Error: Wrong switch!\n");
         return ERROR;
      case 1541:   /* ITALIANO. */
         fprintf(stderr,"Errore: Switch errato!\n");
         return ERROR;
      case 1542:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Switch incorrecto!\n");
         return ERROR;
      case 1543:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Mauvais Switch !\n");
         return ERROR;
      case 1544:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Switch errado!\n");
         return ERROR;
      case 1545:   /* DEUTCHE. */
         fprintf(stderr,"fehler: Falscher Switch!\n");
         return ERROR;

      case 1550:   /* ENGLISH. */
         fprintf(stderr,"Error: Invalid switch and option combination!\n");
         return ERROR;
      case 1551:   /* ITALIANO. */
         fprintf(stderr,"Errore: Combinazione dell'opzione con Switch non valida!\n");
         return ERROR;
      case 1552:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Combinación de opciones no válida con Switch!\n");
         return ERROR;
      case 1553:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : combinaison d'option non valide avec Switch !\n");
         return ERROR;
      case 1554:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Combinação inválida de opção com Switch!\n");
         return ERROR;
      case 1555:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Ungültige Kombination der Option mit Switch!\n");
         return ERROR;

      case 1740:   /* ENGLISH. */
         fprintf(stderr,"Error: The option does not accept any type of switch!\n");
         return ERROR;
      case 1741:   /* ITALIANO. */
         fprintf(stderr,"Errore: L'opzione non accetta alcun tipo di Switch!\n");
         return ERROR;
      case 1742:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡La opción no acepta ningún tipo de Switch!\n");
         return ERROR;
      case 1743:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : l'option n'accepte aucun type de switch !\n");
         return ERROR;
      case 1744:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: A opção não aceita nenhum tipo de Switch!\n");
         return ERROR;
      case 1745:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Die Option akzeptiert keine Art von Switch!\n");
         return ERROR;
   }

/* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
/* delle funzionalità interne, delle opzioni e degli Switch. */
   if(fsign)
      printf("ERROR [TRASLATION-1] GURU MEDITATION\n\n");
   return GURU;
}
/* Fine della funzione errorstype(). */


/* Funzione di gestione dei msg di conferma/errore. */
int filemsg(short *ffmesgc,unsigned long *fselect) {

/* Corpo funzione. */
   switch(*ffmesgc-1) {
      case 100:   /* ENGLISH. */
         fprintf(stdout,"Ok. The default language will be kept.\n\n");
         return OK;
      case 101:   /* ITALIANO. */
         fprintf(stdout,"Ok. Sarà mantenuta la lingua preimpostata.\n\n");
         return OK;
      case 102:   /* ESPAÑOL. */
         fprintf(stdout,"Ok. Se mantendrá el idioma predeterminado.\n\n");
         return OK;
      case 103:   /* FRANÇAIS. */
         fprintf(stdout,"D'accord. La langue par défaut sera conservée.\n\n");
         return OK;
      case 104:   /* PORTUGÛES. */
         fprintf(stdout,"Ok. O idioma padrão será mantido.\n\n");
         return OK;
      case 105:   /* DEUTCHE. */
         fprintf(stdout,"Okay. Die Standardsprache bleibt erhalten.\n\n");
         return OK;

      case 110:   /* ENGLISH. */
         fprintf(stdout,"The configuration file [.firstlang.cfg] will be created.\n");
         return OK;
      case 111:   /* ITALIANO. */
         fprintf(stdout,"Il file di configurazione [.firstlang.cfg] è stato creato.\n");
         return OK;
      case 112:   /* ESPAÑOL. */
         fprintf(stdout,"El archivo de configuración [.firstlang.cfg] ha sido creado.\n");
         return OK;
      case 113:   /* FRANÇAIS. */
         fprintf(stdout,"Le fishier de configuration [.firstlang.cfg] a été créé.\n");
         return OK;
      case 114:   /* PORTUGÛES. */
         fprintf(stdout,"O arquivo de configuração [.firstlang.cfg] foi criado.\n");
         return OK;
      case 115:   /* DEUTCHE. */
         fprintf(stdout,"Die [.firstlang.cfg]-Konfigur ationsdatei wurde erstellt.\n");
         return OK;

      case 120:   /* ENGLISH. */
         fprintf(stderr,"Error: I can not open file [.firstlang.cfg]!\n");
         return ERROR;
      case 121:   /* ITALIANO. */
         fprintf(stderr,"Errore: Non posso aprire il file [.firstlang.cfg]!\n");
         return ERROR;
      case 122:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡No se puede abrir el archivo [.firstlang.cfg]!\n");
         return ERROR;
      case 123:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : impossible d'ouvrir le fichier [.firstlang.cfg] !\n");
         return ERROR;
      case 124:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Não é possível abrir o arquivo [.firstlang.cfg]!\n");
         return ERROR;
      case 125:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Datei kann nicht geöffnet werden [.firstlang.cfg]!\n");
         return ERROR;

      case 130:   /* ENGLISH. */
         fprintf(stderr,"Error: File [.firstlang.cfg] not saved!\n");
         return ERROR;
      case 131:   /* ITALIANO. */
         fprintf(stderr,"Errore: File [.firstlang.cfg] non salvato!\n");
         return ERROR;
      case 132:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Archivo [.firstlang.cfg] no guardado!\n");
         return ERROR;
      case 133:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : fishier [.firstlang.cfg] non enregistré !\n");
         return ERROR;
      case 134:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Arquivo [.firstlang.cfg] não salvo!\n");
         return ERROR;
      case 135:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Datei [.firstlang.cfg] nicht gespeichert!\n");
         return ERROR;

      case 140:   /* ENGLISH. */
         fprintf(stdout,"Rewrite the configuration file.\n");
         fprintf(stdout,"English language setting.\n");
         return OK;
      case 141:   /* ITALIANO. */
         fprintf(stdout,"File di configurazione modificato.\n");
         fprintf(stdout,"Impostazione per la lingua italiana.\n");
         return OK;
      case 142:   /* ESPAÑOL. */
         fprintf(stdout,"El archivo de configuración cambió.\n");
         fprintf(stdout,"Configuración de idioma español.\n");
         return OK;
      case 143:   /* FRANÇAIS. */
         fprintf(stdout,"Fichier de configuration modifié.\n");
         fprintf(stdout,"Configuration de la langue français.\n");
         return OK;
      case 144:   /* PORTUGÛES. */
         fprintf(stdout,"Arquivo de configuração alterado.\n");
         fprintf(stdout,"Configuração da língua portuguesa.\n");
         return OK;
      case 145:   /* DEUTCHE. */
         fprintf(stdout,"Konfigurationsdatei geändert.\n");
         fprintf(stdout,"Einstellung für deutsche Sprache.\n");
         return OK;

      case 150:   /* ENGLISH. */
         fprintf(stderr,"WARNING:\n");
         fprintf(stderr,"Language not fully implemented.\n");
         fprintf(stderr,"The default language will be kept.\n\n");
         return WARNING;
      case 151:   /* ITALIANO. */
         fprintf(stderr,"AVVISO:\n");
         fprintf(stderr,"Lingua non completamente implementata.\n");
         fprintf(stderr,"Sarà mantenuta la lingua preimpostata.\n\n");
         return WARNING;
      case 152:   /* ESPAÑOL. */
         fprintf(stderr,"NOTIFICO:\n");
         fprintf(stderr,"Idioma no implementado completamente.\n");
         fprintf(stderr,"Se mantendrá el idioma predeterminado.\n\n");
         return WARNING;
      case 153:   /* FRANÇAIS. */
         fprintf(stderr,"JE PRÉVIENS :\n");
         fprintf(stderr,"Langue pas entièrement mise en oeuvre.\n");
         fprintf(stderr,"La langue prédefinie sera conservée.\n\n");
         return WARNING;
      case 154:   /* PORTUGÛES. */
         fprintf(stderr,"EU NOTIFICO:\n");
         fprintf(stderr,"Linguagem não totalmente implementada.\n");
         fprintf(stderr,"O idioma padrão será mantido.\n\n");
         return WARNING;
      case 155:   /* DEUTCHE. */
         fprintf(stderr,"ICH BENACHRICHTIGE:\n");
         fprintf(stderr,"Sprache nicht vollstandig implementier.\n");
         fprintf(stderr,"Die Standardsprache bleibt erhalten.\n\n");
         return WARNING;

      case 160:   /* ENGLISH. */
         fprintf(stdout,"\n CAUTION!\n");
         fprintf(stdout," The discriminant value [%lu],\n",*fselect);
         fprintf(stdout," for the generation of the series\n");
         fprintf(stdout," of factors, is not a prime number!\n");
         fprintf(stdout," The list may be empty.\n");
         return WARNING;
      case 161:   /* ITALIANO. */
         fprintf(stdout,"\n ATTENZIONE!\n");
         fprintf(stdout," Il valore discriminante [%lu],\n",*fselect);
         fprintf(stdout," per la generazione della serie di\n");
         fprintf(stdout," fattori, non è un numero primo!\n");
         fprintf(stdout," La lista potrebbe risultare vuota.\n");
         return WARNING;
      case 162:   /* ESPAÑOL. */
         fprintf(stdout,"\n ¡ATENCIÓN!\n");
         fprintf(stdout," El valor discriminante [%lu],\n",*fselect);
         fprintf(stdout," para generar la serie de factores\n");
         fprintf(stdout," numéricos, no es un número primo!\n");
         fprintf(stdout," La lista puede estar vacia.\n");
         return WARNING;
      case 163:   /* FRANÇAIS. */
         fprintf(stdout,"\n ATTENTION!\n");
         fprintf(stdout," The discriminant value [%lu],\n",*fselect);
         fprintf(stdout," for the generation of the series\n");
         fprintf(stdout," of factors, is not a prime number!\n");
         fprintf(stdout," la liste est peut-être vide.\n");
         return WARNING;
      case 164:   /* PORTUGÛES. */
         fprintf(stdout,"\n ATENÇÃO!\n");
         fprintf(stdout," The discriminant value [%lu],\n",*fselect);
         fprintf(stdout," for the generation of the series\n");
         fprintf(stdout," of factors, is not a prime number!\n");
         fprintf(stdout," A lista pode estar vazia.\n");
         return WARNING;
      case 165:   /* DEUTCHE. */
         fprintf(stdout,"\n AUFMERKSAMKEIT!\n");
         fprintf(stdout," Der Unterscheidungswert [%lu],\n",*fselect);
         fprintf(stdout," zur Erzeugung der Reihe numerischer\n");
         fprintf(stdout," Faktoren ist keine Primzahl!\n");
         fprintf(stdout," Die List ist möglicherweise leer.\n");
         return WARNING;

      case 170:   /* ENGLISH. */
         fprintf(stdout,"\r < EMPTY LIST >\n");
         return OK;
      case 171:   /* ITALIANO. */
         fprintf(stdout,"\r < LISTA VUOTA >\n");
         return OK;
      case 172:   /* ESPAÑOL. */
         fprintf(stdout,"\r < LISTA VACÍA >\n");
         return OK;
      case 173:   /* FRANÇAIS. */
         fprintf(stdout,"\r < LISTE VIDE >\n");
         return OK;
      case 174:   /* PORTUGÛES. */
         fprintf(stdout,"\r < LISTA VAZIA >\n");
         return OK;
      case 175:   /* DEUTCHE. */
         fprintf(stdout,"\r < LEERE LISTE >\n");
         return OK;

      case 190:   /* ENGLISH. */
         fprintf(stderr,"\nSorry, the functionality as not\n");
         fprintf(stderr,"yet been fully implemented in this\n");
         fprintf(stderr,"version of the software.\n\n");
         return ERROR;
      case 191:   /* ITALIANO. */
         fprintf(stderr,"\nMi dispiace, la funzionalità non è\n");
         fprintf(stderr,"ancora stata completamente implementata\n");
         fprintf(stderr,"in questa versione del Software.\n\n");
         return ERROR;
      case 192:   /* ESPAÑOL. */
         fprintf(stderr,"\nLo sientimos, la funcionalidad aún\n");
         fprintf(stderr,"no se ha implementado completamente\n");
         fprintf(stderr,"en esta versión de Software.\n\n");
         return ERROR;
      case 193:   /* FRANÇAIS. */
         fprintf(stderr,"\nDesolé, la fonctionnalité n'a pas\n");
         fprintf(stderr,"encore été entièrement implémentée \n");
         fprintf(stderr,"dans cette version du logiciel.\n\n");
         return ERROR;
      case 194:   /* PORTUGÛES. */
         fprintf(stderr,"\nDesculpe, a funcionalidade ainda\n");
         fprintf(stderr,"não foi totalmente implementada\n");
         fprintf(stderr,"nesta versão do Software.\n\n");
         return ERROR;
      case 195:   /* DEUTCHE. */
         fprintf(stderr,"\nLeider ist die Funktionalität in\n");
         fprintf(stderr,"dieser Version der Software noch\n");
         fprintf(stderr,"nicht vollständig implementiert.\n\n");
         return ERROR;

      case 200:   /* ENGLISH. */
         fprintf(stdout,"\rError: I can't access the user manual file! [.en_lng_man]\n\n");
         return ERROR;
      case 201:   /* ITALIANO. */
         fprintf(stdout,"\rErrore: Non posso accedere al file del manuale d'uso [.it_lng_man]!\n\n");
         return ERROR;
      case 202:   /* ESPAÑOL. */
         fprintf(stdout,"\rError: ¡No puedo acceder al archivo de manual de usuario [.es_lng_man]!\n\n");
         return ERROR;
      case 203:   /* FRANÇAIS. */
         fprintf(stdout,"\rErreur : je ne peux pas accéder au fichier du manuel d'utilisation [.fr_lng_man] !\n\n");
         return ERROR;
      case 204:   /* PORTUGÛES. */
         fprintf(stdout,"\rErro: Não consigo acessar o arquivo do manual do usuário [.pt_lng_man]!\n");
         return ERROR;
      case 205:   /* DEUTCHE. */
         fprintf(stdout,"\rFehler: Auf die Benutzerhandbuchdatei [.de_lng_man] kann nicht zugegriffen werden!\n\n");
         return ERROR;
   }

/* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
/* delle funzionalità interne, delle opzioni e degli Switch. */
   if(fsign)
      printf("ERROR [TRANSLATION-2] GURU MEDITATION\n");
   return GURU;
}
/* Fine della funzione filemsg(). */


unsigned long primenum(unsigned long number) {

/* -------------------------------------------------------------------------- */
/* Funzione di ricerca del fattore primo di scomposizione di un numero. Se il
   numero è divisibile la funzione ritorna il primo 'fattore primo' per il quale
   esso è divisibile; se invece il numero è primo la funzione ritorna lo zero.
   Definizione dell'algoritmo:
   - NUM è il numero da processare, per ricavarne i suoi fattori primi di scom-
     posizione, oppure determinare se il numero stesso sia o meno primo.
   - NBASE è il contatore progressivo per la prova di divisibilità, che si
     determina considerando la parte intera della radice quadrata di NUM.
   - NDIVS è il fattore primo di scomposizione incrementale, inizialmente vale 1,
     poi viene eseguito un ciclo interattivo ed NDIVS viene incrementato ogni
     volta di 1; all'uscita del ciclo, NDIVS assume il ruolo di fattore primo e
     può valere solo 1, 2, 3, 5, 7, 11, 13, 19, 23, 29, 31, 37, ... etc.
   - Nel ciclo si determina se 'NUM modulo di NDIVS' è vero o falso;
     se vero, il ciclo interattivo viene interrotto e viene restiuito NDIVS,
     altrimenti si prosegue fino a che NDIVS è superiore o uguale a NBASE.
   Chiamata della funzione:
   - NDIVS = primenum(NUM); Se NDIVS è inferiore a NUM, allora NUM è divisibile
     per NDIVS; altrimenti se NDIVS è superiore o uguale a NUM, NUM è primo.
   - La funzione restituisce ZDIVS se NUM è 0; UNCL se NUM è 1; NPR se NUM è
     uguale a 2 o qualunque altro primo superiore; NDIVS se NUM è divisibile.
   - NDIVS rappresenta il primo fattore primo di scomposizione di NUM.
   - NPR vale 0; ZDIVS vale 1, UNCL vale 1, NDIVS è superiore o uguale a 2.
   - Utilizzo:
     - if((nbase=primenum(num))) printf("%lu è divisibile per %lu\n",num,nbase);
     - if(!(nbase=primenum(num))) printf("%lu è primo!\n",num);   */
/* -------------------------------------------------------------------------- */
/* L'algoritmo di questa funzione è sottoposto al CopyLeft 1991-2025,
   ed alla GNU Public License version 2 e 3 di Free Software Foundation.
   Rif. http://www.gnu.org/copyleft
        http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
        http://www.gnu.org/licenses/gpl-3.0.html

   Creato da G. B. alias PiErre60 (Italy) [dfact=primenum(number) ~© 1990-1991],
   e successive modifiche ~© 1997-2001-2010-2025.  */
/* -------------------------------------------------------------------------- */

/* Definizione di variabili locali. */
   unsigned long nbase=0UL,ndivs=2UL,divsf=0UL;

/* Corpo funzione. */
   if(number==0) {
      divsf=0;
      return ZDIVS;    /* Lo zero per convenzione è considerato pari¹, non classificabile. */
   }
   if(number==1) {
      divsf=0;
      return UNCL;     /* Il numero uno viene considerato non classificabile, non primo³. */
   }
   if(number==2)
      return NPR;      /* Il due è considerato numero primo². */
   nbase=(unsigned long)sqrt((unsigned long)number);
   nbase++;
   while(nbase>=ndivs) {             /* Ricerca del fattore primo di scomposizione del - */
      if(!(number%ndivs))            /* numero. Se il numero è divisibile, nella - */
         divsf=ndivs,ndivs=nbase;    /* variabile "divsf" è presente un fattore primo - */
      ++ndivs;                       /* valido per il quale esso risulta divisibile. */
   }
   if(!divsf)
      return NPR;     /* Il numero è primo, se uno viene qui considerato primo³. */
   else
      return divsf;   /* Il numero è divisibile: il fattore primo è divsf stesso. */
}

/* ¹ Per convenzione il fattore minimo di scomposizione di zero è considerato pari ad uno. */
/* ² Il due è ovviamente primo poichè è divisibile solo per se stesso e per l'unità. */
/* ³ Il numero uno è indefinito e per convenzione non è considerato primo, poiché -
     è divisibile solo per sè stesso. Qui per praticità viene considerato come lo zero. */

/* Fine della funzione primenum(). */
/* ------------------------------- */


/* Funzione di ricerca e stampa formattata dei fattori di scomposizione. */
void primefact(unsigned long lnum, unsigned long llimt) {

/* Dichiarazione di funzioni. */
   unsigned long primenum(unsigned long);
   short trueoptions(void);
   short trueswitch(void);

/* Dichiarazione di variabili esterne. */
   extern char option, subopt;
   extern unsigned long eval[];
   extern unsigned short swflag;
   extern unsigned short cntvis,cnt;
   extern short ncx;

/* Definizione di variabili e puntatori locali. */
   unsigned long nums,knum;
   unsigned long *peval;
   unsigned short intt=1U;
   unsigned short cfs=0U;

/* Inizializzazione puntatore all'array. */
   peval=eval;

/* Controllo consistenza. */
   if(!(llimt-(lnum-1))) {
      printf("ABORTED!\n");
      return;
   }

/* Corpo funzione. */
/* Se sono presenti e attivi gli Switch 'S', 'U', 'D' o 'P'. */
   if(option!=KEYS&&trueswitch()<=TRUEPM&&!swflag) {
      if(ncx==1) printf("> %1lu = ",lnum);
      else if(ncx==2) printf("> %2lu = ",lnum);
      else if(ncx==3) printf("> %3lu = ",lnum);
      else if(ncx==4) printf("> %4lu = ",lnum);
      else if(ncx==5) printf("> %5lu = ",lnum);
      else if(ncx==6) printf("> %6lu = ",lnum);
      else if(ncx==7) printf("> %7lu = ",lnum);
      else if(ncx==8) printf("> %8lu = ",lnum);
      else if(ncx==9) printf("> %9lu = ",lnum);
      else {
         if(ncx==10) printf("> %10lu = ",lnum);
      }
   }
   else {

   /* Se non è specificato nessun Switch. */
   /* Se le opzioni sono: '-Y', -S', '-F' o '-D'. */
      if(trueoptions()==TWO||option==DIVS||option==NOPT) {
         if(ncx==1) printf("  %1lu = ",lnum);
         else if(ncx==2) printf("  %2lu = ",lnum);
         else if(ncx==3) printf("  %3lu = ",lnum);
         else if(ncx==4) printf("  %4lu = ",lnum);
         else if(ncx==5) printf("  %5lu = ",lnum);
         else if(ncx==6) printf("  %6lu = ",lnum);
         else if(ncx==7) printf("  %7lu = ",lnum);
         else if(ncx==8) printf("  %8lu = ",lnum);
         else if(ncx==9) printf("  %9lu = ",lnum);
         else {
            if(ncx==10) printf("  %10lu = ",lnum);
         }
      }
      else {

      /* Se le opzioni sono: '-P', '-L', '-Q', '-V' o '-C'. */
         if(trueoptions()==TREE||option==NSDIV||option==VARS||option==CALC) {
            if(ncx==1) printf(" %1lu = ",lnum);
            else if(ncx==2) printf(" %2lu = ",lnum);
            else if(ncx==3) printf(" %3lu = ",lnum);
            else if(ncx==4) printf(" %4lu = ",lnum);
            else if(ncx==5) printf(" %5lu = ",lnum);
            else if(ncx==6) printf(" %6lu = ",lnum);
            else if(ncx==7) printf(" %7lu = ",lnum);
            else if(ncx==8) printf(" %8lu = ",lnum);
            else if(ncx==9) printf(" %9lu = ",lnum);
            else {
               if(ncx==10) printf(" %10lu = ",lnum);
            }
         }

      /* Se l'opzione è '-K' non fare nulla */
         else if(option==KEYS);
         else {

         /* Questo blocco non dovrebbe mai esse eseguito */
         /* Se viene eseguito questo blocco si è in presenza di un grave errore */
            if(fsign)
               printf("ERROR [VIEW] GURU MEDITATION\n");
            return;
         }
      }
   }

/* Stampa con l'opzione '-Y'. */
/* Viene visualizzato solo il primo dei fattori primi di scomposizione. */
   if(option==TINS) {
      printf("%lu\n",primenum(lnum));
      return;
   }

/* -------------------------------------------------------------------------- */
/* Calcolo e memorizzazione in array dei fattori di scomposizione del numero. */

/* Azzeramento dell'array. */
   while(*peval)
      *peval++=0UL;
   peval=eval;   /* Ripristino alla base dell' array del puntatore. */
   knum=lnum;

/* Ricerca dei fattori primi e memorizzazione. */
   for(;;) {
      nums=primenum(lnum);

   /* Esecuzione se il numero in ingresso è zero. */
      if(nums==ZDIVS) {
         *peval=nums;
         break;
      }
   /* Esecuzione se il numero in ingresso è uno. */
      if(nums==UNCL) {
         *peval=nums;
         break;
      }

   /* Esecuzione se il numero in ingresso è superiore a uno. */
      if(nums==NPR) {
         *peval=lnum;
         break;
      }
      else {
         *peval++=nums,lnum/=nums;
         if(option==KEYS) {

         /* Conta il numero dei fattori primi di scomposizione */
         /* Resetta il flag globale per il controllo della stampa */
            cfs++,cnt=0;

         /* Se i fattori primi di scomposizione sono superiori a due */
         /* imposta il flag globale cnt per il controllo della stampa */
            if(cfs>1) cnt=1;
            if(cnt==1) {
               break;
            }
         }
      }
   }
   if(option==KEYS) {

   /* Se i fattori primi di scomposizione sono superiori a due */
   /* imposta il flag globale cnt per il controllo della stampa */
      if(cfs>1) cnt=1;
      else cntvis++;
   }
   peval=eval;   /* Ripristino alla base dell' array del puntatore. */
/* Fine della routine di memorizzazione. */

/* -------------------------------------------------------------------- */
/* Stampa dei fattori di scomposizione del numero indicato nella serie. */
   if(option==SYMP) {

   /* -------------------------------- */
   /* Loop di stampa semplificata. */
   /* Esecuzione se l'opzione è SYMP. */
      while(*peval) {
         printf("%lu",*peval++);
         if(*peval)
            printf(" ");
      }
      printf("\n");
      return;
   }
/* Fine loop di stampa semplificata. */

   else {
      if(option==KEYS) {

      /* Se l'opzione è '-K' */
         if(cnt==0) {

         /* Se sono presenti gli Switch 'S', 'U' o 'D' */
            if(trueswitch()==TRUESW&&!swflag) {
               if(ncx==1) printf("> %1lu = ",knum);
               else if(ncx==2) printf("> %2lu = ",knum);
               else if(ncx==3) printf("> %3lu = ",knum);
               else if(ncx==4) printf("> %4lu = ",knum);
               else if(ncx==5) printf("> %5lu = ",knum);
               else if(ncx==6) printf("> %6lu = ",knum);
               else if(ncx==7) printf("> %7lu = ",knum);
               else if(ncx==8) printf("> %8lu = ",knum);
               else if(ncx==9) printf("> %9lu = ",knum);
               else {
                  if(ncx==10) printf("> %10lu = ",knum);
               }
            }
            else {
               if(ncx==1) printf("  %1lu = ",knum);
               else if(ncx==2) printf("  %2lu = ",knum);
               else if(ncx==3) printf("  %3lu = ",knum);
               else if(ncx==4) printf("  %4lu = ",knum);
               else if(ncx==5) printf("  %5lu = ",knum);
               else if(ncx==6) printf("  %6lu = ",knum);
               else if(ncx==7) printf("  %7lu = ",knum);
               else if(ncx==8) printf("  %8lu = ",knum);
               else if(ncx==9) printf("  %9lu = ",knum);
               else {
                  if(ncx==10) printf("  %10lu = ",knum);
               }
            }

         /* ------------------------------------------------------- */
         /* Loop di stampa formattata dei fattori di scomposizione. */
         /* Esecuzione della stampa se l'opzione è KEYS. */
            while(*peval) {
               if(*peval==*(peval+1))
                  intt++;
               else {
                  if(intt==1U) printf("%lu ",*peval);
                  else printf("(%lu^%u) ",*peval,intt);
                  intt=1U;
               }
               peval++;
            }
            printf("\n");
            return;
         }
      }
      else {

      /* ------------------------------------------------------- */
      /* Loop di stampa formattata dei fattori di scomposizione. */
      /* Esecuzione se l'opzione è NOPT, DIVS, NSDIV, FORM, VARS o CALC. */
         while(*peval) {
            if(*peval==*(peval+1))
               intt++;
            else {
               if(intt==1U) printf("%lu ",*peval);
               else printf("(%lu^%u) ",*peval,intt);
               intt=1U;
            }
            peval++;
         }
         printf("\n");
         return;
      }
      /* Fine del loop di stampa formattata dei fattori di scomposizione. */
      /* ---------------------------------------------------------------- */
   }
}
/* Fine della funzione primefact(). */


/* Funzione per il calcolo statistico per le opzioni '-B' e '-V'. */
void statseries(unsigned short seg) {

/* Dichiarazione di variabili esterne. */
   extern unsigned short nprime[],ndivs[];
   extern unsigned short pmin,dmin,pmax,dmax,psum,dsum;
   extern unsigned short pmean,dmean;

/* Definizione di variabili locali. */
   float dcom,pcom;
   unsigned short *dptr,*nptr;

/* Inizializzazione puntatori. */
   dptr=ndivs,nptr=nprime;

/* Corpo funzione. */
   for(;nptr<(nprime+seg);dptr++,nptr++) {
      psum+=*nptr,dsum+=*dptr;
      pmax=(*nptr>pmax)?*nptr:pmax;
      dmax=(*dptr>dmax)?*dptr:dmax;
      pmin=(*nptr<=pmin)?*nptr:pmin;
      dmin=(*dptr<=dmin)?*dptr:dmin;
   }
   pcom=(float)psum/seg,dcom=(float)dsum/seg;
   pmean=(unsigned short)pcom,dmean=(unsigned short)dcom;
   pcom-=(float)pmean,dcom-=(float)dmean;

   /* Arrotondamento all'unità sulla media. */
   if(pcom>=0.5)
      pmean++;
   if(dcom>=0.5)
      dmean++;
   return;
}
/* Fine della funzione statseries().*/


/* Funzione per l'icolonnamento della serie dei numeri primi. */
short tpcol(unsigned long numbas,unsigned long numlim,short *flang) {

/* Dichiarazione di funzioni. */
   unsigned long primenum(unsigned long);

/* Dichiarazione di variabili esterne. */
   extern unsigned short fldp;
   extern short fsign;

/* Definizione di variabili locali. */
   unsigned long numsav,factbas;
	 unsigned long count=0,pcount=0,dcount=0;
	 unsigned int clp=0,col,nc;

/* Inizializzazione di variabili. */
	 numsav=numbas;

/* Corpo funzione. */
   if((numlim-numbas)>RGTAB)
      return ERROR;
   if(numlim<10) col=8,nc=1;
   if(numlim>=10&&numlim<=99) col=8,nc=2;
   if(numlim>=100&&numlim<=999) col=8,nc=3;
   if(numlim>=1000&&numlim<=9999) col=8,nc=4;
   if(numlim>=10000&&numlim<=99999) col=8,nc=5;
   if(numlim>=100000&&numlim<=999999) col=7,nc=6;
   if(numlim>=1000000&&numlim<=9999999) col=4,nc=7;
   if(numlim>=10000000&&numlim<=99999999) col=4,nc=8;
   if(numlim>=100000000&&numlim<=999999999) col=4,nc=9;
   if(numlim>=1000000000) col=4,nc=10;
   putchar('\n');
   while(numsav<=numlim) {
      if(!fldp) {
 	       if(!(factbas=primenum(numsav))) {
 	          if(factbas==ZDIVS||factbas==UNCL)
		           numsav=1UL;
			      if(clp==col) {
			         clp=0;
				       printf("\n");
				    }
   			    if(nc==1) printf(" %1.0lu\t",numsav);
			      if(nc==2) printf(" %2.0lu\t",numsav);
			      if(nc==3) printf(" %3.0lu\t",numsav);
			      if(nc==4) printf(" %4.0lu\t",numsav);
			      if(nc==5) printf(" %5.0lu\t",numsav);
			      if(nc==6) printf(" %6.0lu\t",numsav);
			      if(nc==7) printf(" %7.0lu\t",numsav);
			      if(nc==8) printf(" %8.0lu\t",numsav);
			      if(nc==9) printf(" %9.0lu\t",numsav);
			      if(nc==10) printf(" %10.0lu\t",numsav);
			      pcount++,clp++;
			   }
		  }
		  else {
		     if((factbas=primenum(numsav))) {
		        if(factbas==ZDIVS||factbas==UNCL)
		           numsav=4UL;
			      if(clp==col) {
			         clp=0;
				       printf("\n");
				    }
			      if(nc==1) printf(" %1.0lu\t",numsav);
			      if(nc==2) printf(" %2.0lu\t",numsav);
			      if(nc==3) printf(" %3.0lu\t",numsav);
			      if(nc==4) printf(" %4.0lu\t",numsav);
			      if(nc==5) printf(" %5.0lu\t",numsav);
			      if(nc==6) printf(" %6.0lu\t",numsav);
			      if(nc==7) printf(" %7.0lu\t",numsav);
			      if(nc==8) printf(" %8.0lu\t",numsav);
			      if(nc==9) printf(" %9.0lu\t",numsav);
			      if(nc==10) printf(" %10.0lu\t",numsav);
			      dcount++,clp++;
		     }
		  }
		  numsav++,count++;
	 }
	 if(pcount||dcount)
	    putchar('\n');
	 if(*flang==ENGLISH) {
	    if(numlim<100000) {
	       printf("\n-------------------------\n");
		     printf("Processed numbers: %6.1lu\n",count);
		     printf("From number:       %6.1lu\n",numbas);
		     printf("To number:         %6.1lu\n",numlim);
		     if(!fldp)
		        printf("Prime numbers:     %6.1lu\n\n",pcount);
		     else
		        printf("Divisible numbers: %6.1lu\n\n",dcount);
		  }
		  else {
		     printf("\n-----------------------------\n");
		     printf("Processed numbers:     %6.1lu\n",count);
		     printf("From number:       %10.1lu\n",numbas);
		     printf("To number:         %10.1lu\n",numlim);
		     if(!fldp)
		        printf("Prime numbers:         %6.1lu\n\n",pcount);
		     else
		        printf("Divisible numbers:     %6.1lu\n\n",dcount);
		  }
		  return OK;
	 }
	 if(*flang==ITALIANO) {
	    if(numlim<100000) {
	       printf("\n-------------------------\n");
		     printf("Numeri processati: %6.1lu\n",count);
		     printf("Dal numero:        %6.1lu\n",numbas);
		     printf("Al numero:         %6.1lu\n",numlim);
		     if(!fldp)
		        printf("Numeri primi:      %6.1lu\n\n",pcount);
		     else
		        printf("Numeri divisibili: %6.1lu\n\n",dcount);
		  }
		  else {
		     printf("\n-----------------------------\n");
		     printf("Numeri processati:     %6.1lu\n",count);
		     printf("Dal numero:        %10.1lu\n",numbas);
		     printf("Al numero:         %10.1lu\n",numlim);
		     if(!fldp)
		        printf("Numeri primi:          %6.1lu\n\n",pcount);
		     else
		        printf("Numeri divisibili:     %6.1lu\n\n",dcount);
		  }
		  return OK;
	 }
	 if(*flang==ESPANOL) {
	    if(numlim<100000) {
	       printf("\n---------------------------\n");
		     printf("Números processados: %6.1lu\n",count);
		     printf("Del número:          %6.1lu\n",numbas);
		     printf("Al número:           %6.1lu\n",numlim);
		     if(!fldp)
		        printf("Números primos:      %6.1lu\n\n",pcount);
		     else
		        printf("Números divisibles:  %6.1lu\n\n",dcount);
		  }
		  else {
		     printf("\n-------------------------------\n");
		     printf("Números processados:     %6.1lu\n",count);
		     printf("Del número:          %10.1lu\n",numbas);
		     printf("Al número:           %10.1lu\n",numlim);
		     if(!fldp)
		        printf("Números primos:          %6.1lu\n\n",pcount);
		     else
		        printf("Números divisibles:      %6.1lu\n\n",dcount);
		  }
		  return OK;
	 }
	 if(*flang==FRANCAIS) {
	    if(numlim<100000) {
	       printf("\n---------------------------\n");
		     printf("Numéros traités :    %6.1lu\n",count);
		     printf("Du numéro :          %6.1lu\n",numbas);
		     printf("Au numéro :          %6.1lu\n",numlim);
		     if(!fldp)
		        printf("Nombres premiers :   %6.1lu\n\n",pcount);
		     else
		        printf("Nombres divisibles : %6.1lu\n\n",dcount);
		  }
		  else {
		     printf("\n-------------------------------\n");
		     printf("Numéros traités :        %6.1lu\n",count);
		     printf("Du numéro :          %10.1lu\n",numbas);
		     printf("Au numéro :          %10.1lu\n",numlim);
		     if(!fldp)
		        printf("Nombres premiers :       %6.1lu\n\n",pcount);
		     else
		        printf("Nombres divisibles :     %6.1lu\n\n",dcount);
		  }
		  return OK;
	 }
	 if(*flang==PORTUGUES) {
	    if(numlim<100000) {
	       printf("\n---------------------------\n");
		     printf("Números processados: %6.1lu\n",count);
		     printf("Do número:           %6.1lu\n",numbas);
		     printf("Para o número:       %6.1lu\n",numlim);
		     if(!fldp)
		        printf("Números primos:      %6.1lu\n\n",pcount);
		     else
		        printf("Números divisíveis:  %6.1lu\n\n",dcount);
		  }
		  else {
		     printf("\n-------------------------------\n");
		     printf("Números processados:     %6.1lu\n",count);
		     printf("Do número:           %10.1lu\n",numbas);
		     printf("Para o número:       %10.1lu\n",numlim);
		     if(!fldp)
		        printf("Numeros primos:          %6.1lu\n\n",pcount);
		     else
		        printf("Números divisíveis:      %6.1lu\n\n",dcount);
		  }
		  return OK;
	 }
	 if(*flang==DEUTCHE) {
	    if(numlim<100000) {
	       printf("\n---------------------------\n");
		     printf("Verarbeitete Zahlen: %6.1lu\n",count);
		     printf("Aus der Nummer:      %6.1lu\n",numbas);
		     printf("Zur Nummer:          %6.1lu\n",numlim);
		     if(!fldp)
		        printf("Primzahlen:          %6.1lu\n\n",pcount);
		     else
		        printf("Teilbare Zahlen:     %6.1lu\n\n",dcount);
		  }
		  else {
		     printf("\n-------------------------------\n");
		     printf("Verarbeitete Zahlen:     %6.1lu\n",count);
		     printf("Aus der Nummer:      %10.1lu\n",numbas);
		     printf("Zur Nummer:          %10.1lu\n",numlim);
		     if(!fldp)
		        printf("Primzahlen:              %6.1lu\n\n",pcount);
		     else
		        printf("Teilbare Zahlen:         %6.1lu\n\n",dcount);
		  }
		  return OK;
	 }
	 else {

   /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
   /* delle funzionalità interne, delle opzioni e degli Switch. */
      if(fsign) {
         printf("ERROR [STAT-3] GURU MEDITATION\n\n");
         return GURU;
      }
   }
	 return OK;
}
/* Fine della funzione tpcols(). */


/* Funzione riscrittura del file di configurazione per la lingua. */
short cfglang(short *fllang) {

/* Dichiarazioni di funzioni. */
   int filemsg(short *,unsigned long *);

/* Dichiarazione di variabili esterne. */
   extern short lngdef,lang;
   extern char *pnd,*pnf;
   extern char *pmsl,*pesr;
   extern char *home,*usr;
   extern int ls,lb;
   extern FILE *fp;

/* Definizione di variabili locali. */
   unsigned long fnself;
   char ce;
   short ffmesg;

/* Corpo funzione. */
/* Ottiene il nome dell'utente. */
   ls=strlen(pmsl),lb=strlen(pesr);
   if((usr=getenv("USER"))==NULL) {
     /* Esecuzione se non viene trovato il nome dell'utente. */
     /* Non posso ottenere il nome dell'utente. */
     /* Visualizza [Errore: Non posso aprire il file [.firstlang.cfg]!]. */
      ffmesg=MSGBASE+*fllang+20;
      filemsg(&ffmesg,&fnself);
   }

/* ottiene il percorso della directory dell'utente. */
   struct passwd *pwd=getpwuid(getuid());
   if(pwd==NULL) {
     /* Esecuzione se non viene trovata la path della directory home. */
     /* Non posso ottenere il path della directory home. */
     /* Visualizza [Errore: Non posso aprire il file [.firstlang.cfg]!]. */
      ffmesg=MSGBASE+*fllang+20;
      filemsg(&ffmesg,&fnself);
   }

/* Percorso della directory dell'utente. */
   home=pwd->pw_dir;

/* Apertura di .firstlang.cfg in scrittura. */
   snprintf(pnf,sizeof(nfile),"%s/.firstlang.cfg",home);
   if((fp=fopen(pnf,WRITE))==NULL) {

   /* Esecuzione se il file di configurazione non si può aprire. */
   /* Visualizza [Errore: Non posso aprire il file [.firstlang.cfg]!]. */
      ffmesg=MSGBASE+*fllang+20;
      filemsg(&ffmesg,&fnself);

   /* Visualizza [Ok. Sarà mantenuta la lingua preimpostata.]. */
      ffmesg=MSGBASE+*fllang+0;
      if(filemsg(&ffmesg,&fnself)==OK)
         return ERROR;
   }
   else {

   /* Controllo congruenza codice lingua. */
      if(!*fllang||*fllang>6)
         *fllang=lngdef;

   /* Memorizzazione del nuovo stato del flag per la selezione della lingua. */
      pmsl=LANG; fputs(pmsl,fp);   /* Stringa identificativa iniziale. */
      ce=fputc(*fllang,fp);        /* Flag impostazione lingua. */
      pesr=ENDL; fputs(pesr,fp);   /* Stringa identificativa finale. */
      if(ce==EOF) {

      /* Esecuzione in caso in cui il file non sia salvato. */
      /* Visualizza [Errore: File [.firstlang.cfg] non salvato!]. */
         ffmesg=MSGBASE+*fllang+30;
         filemsg(&ffmesg,&fnself);
      }

   /* Visualizza [File di configurazione modificato.]. */
   /* Visualizza [Impostazione per la lingua italiana.]. */
   /* Oppure: */
   /* Visualizza [Rewrite the configuration file.]. */
   /* Visualizza [English language setting.]. */
      ffmesg=MSGBASE+*fllang+40;
      filemsg(&ffmesg,&fnself);
      fclose(fp);
   }
   if(ce!=EOF) {
      printf("+++Ok.\n\n");
      return OK;
   }
   printf("---K.O.\n\n");
   return ERROR;
}
/* Fine della funzione cfglang(). */

/* END. */
