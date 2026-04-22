/* firstnum          Release 1.09a-20260319
   ----------------------------------------
   ~© (2010-2026) F.S.F. GNU/GPL Vers.3
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
   Debug ed Update minori        11-12-2000
   Release 1.3c-build            13-12-2000
   Ultima Release Amiga*         14-12-2000
   Primo Porting GNU/Linux       13-08-2010
   Primo Update (Release 1.04)   21-08-2010
   Secondo Update (Release 1.05) 03-02-2019
   Terzo Update (Release 1.05a)  29-08-2020
   Release 1.05a (beta)          12-09-2020
   Release 1.07a (beta)          18-12-2020
   Release 1.07b (beta)          19-03-2024
   Release 1.08a (stabile)       27-12-2024
   Release 1.08b (primo update)  31-03-2025
   Release 1.08c (update&debug)  07-12-2025
   Release 1.09a (stabile)       19-03-2026
   ----------------------------------------
   Release pubblica GNU-CC       30-03-2025
   Primo Update pubblico         31-03-2025
   Ultimo Update pubblico        22-04-2026
   ----------------------------------------
   Compilato in origine con:
   Lattice®-SAS® C MC680x0  Vers. 5.05
   per i computers Commodore-AMIGA®
   ----------------------------------------
   Portato e ricompilato in C std.99 per
   UNIX®/POSIX SYS V e GNU/Linux®
   con GNU-CC (C Compiler) Vers. >= 4.4.5
   Opzioni compilazione:
   -std=c99 Firstnum109a.c -o firstnum -lm
   (per la versione finale corrente).
   ----------------------------------------
   Prima Release (stabile) AMIGA:     1.3c
   *Ultima Release (stabile) AMIGA:   1.3c
   Prima Release (porting) GNU/GCC:   1.3d
   Prima Release (stabile) GNU-GCC:   1.04
   Seconda Release (stabile) GNU-GCC: 1.08b
   Ultima Release (stabile) GNU-GCC:  1.09a
   ----------------------------------------

   NOME UFFICIALE DEL PROGRAMMA
   DEFINITO ALLA RIGA 147 = "firstnum"

   VERSIONE DEL CODICE ATTUALE E DEL
   RILASCIO ALLA RIGA 149 = "1.09a"
   ED ALLA RIGA 151 = "1.09a-20260319"

   LINGUAGGIO PRE-IMPOSTATO = ENGLISH
   ALLA RIGA: 333 = [ENGLISH/ITALIANO/ESPANOL/FRANCAIS/PORTUGUES/DEUTCHE]
   ALLE RIGHE: 339 -> 344 = [FLAG IMPLEMEMTAZIONE PARZIALE DI UNA LINGUA] */

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
   Questo Software è distribuito sotto licenza (F.S.F.) GNU/GPLv3
   Il programma viene fornito «così com'è» senza nessuna forma di garanzia
   esplicita o implicita. L'autore «declina ogni responsabilità» a seguito
   di eventuali danni diretti e/o indiretti di qualsiasi natura, senza al-
   cuna eccezione, derivanti dall'uso di questo Software.
   L'utilizzo  del presente Software  implica sempre la «tacita e completa
   accettazione» dei rispettivi termini di licenza.
   Il programma è adatto solo per uso didattico e/o divulgativo.
   Nota:  Il codice di questo programma  è stato ampiamente controllato ed
   ogni funzionalità  è stata singolarmente testata a fondo, per garantire
   la correttezza dei risultati forniti, sono inoltre stati fatti dei test
   rigorosi su diverse serie di numeri, presi come campioni significativi,
   utilizzando come paragone di riferimento valori ottenuti da  fonti note
   e certificate per verificarne la correttezza. Riferimenti:
    - OEIS (Online Encyclopedia of Integer Sequences).
    - Tables of Prime-Counting Function.
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
#define ZUDV      1UL     /* Convenzione per il numero zero. */
#define UNDV      1UL     /* Convenzione per il numero uno. */
#define LFLAG     0U      /* Condizione disattiva dei Flag. */
#define HFLAG     1U      /* Condizione attiva dei Flag. */
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
#define TEST      448     /* Codice per l'opzione speciale «TEST» */
#define READ      "r"     /* Lettura dal file. */
#define WRITE     "w"     /* Scrittura sul file. */
#define NUL       '\0'    /* Carattere nullo. */

/* ---------------------------------------------------------- */
#define NAMEPROG "firstnum"  /* Nome ufficiale del programma. */
/* ---------------------------------------------------------- */
#define VERSION  "1.09a"   /* Versione attuale del programma. */
/* ---------------------------------------------------------- */
#define RELEASE  "1.09a-20260319"    /* Versione di Rilascio. */
/* ---------------------------------------------------------- */

/* Funzione globopts(). */
#define NOGLOP 0      /* Opzione NOPT (ZERO=nessuna opzione). */
#define GLOB0  250    /* Serie di opzioni: '-L' + '-J' + '-E' + '-Q'. */
#define ERRSL  909    /* Condizione di errore: nessuna serie di opzioni valida. */

/* Funzione globoptions(). */
#define NOGOPT 0      /* Opzione NOPT (ZERO=nessuna opzione). */
#define GLOB1  300    /* Serie di opzioni: '-G' + '-T' + '-B' + '-V' + '-C'. */
#define GLOB2  400    /* Serie di opzioni: '-Y' + '-S' + '-F' + '-D' + '-K'. */
#define GLOB3  500    /* Serie di opzioni: '-P' + '-L' + '-Q' + '-N'. */
#define ERRSG  909    /* Condizione di errore: nessuna serie di opzioni valida. */

/* Funzione trueoptions(). */
#define ZERO   0      /* Opzione NOPT (ZERO=nessuna opzione). */
#define ONEY   10     /* Serie di opzioni: '-D' + '-Q' + '-K' + '-E'. */
#define TWOS   20     /* Serie di opzioni: '-Y' + '-S' + '-F' + '-A'. */
#define THRE   30     /* Serie di opzioni: '-P' + '-L' + '-G' + '-J'. */
#define NPM    50     /* Opzione '-N'. */
#define STT    60     /* Opzione '-T'. */
#define BSS    70     /* Opzione '-B'. */
#define VRS    80     /* Opzione '-V'. */
#define CLC    90     /* Opzione '-C'. */
#define INFO   100    /* Opzioni speciali QuickHelp e Info: '-H', '-?'. */
#define HLP    200    /* Opzione speciale HELP: '--'. */
#define ERRS   999    /* Condizione di errore: nessuna opzione valida. */

/* Funzione trueswitch(). */
#define NOSWT   0     /* Switch NSWT (NOSWT=nessuno Switch). */
#define TRUESW  1     /* Gruppo di Switch: 'S', 'U', 'D'. */
#define TRUEPM  2     /* Solo Switch 'P'. */
#define LISTSW  3     /* Solo Switch 'L'. */
#define NCOLTP  4     /* Solo Switch 'T'. */
#define PNCPOS  5     /* Solo Switch 'N'. */
#define CNTPRM  6     /* Solo Switch 'C'. */
#define TABCNT  7     /* Solo Switch 'B'. */
#define ROWPOS  8     /* Solo Switch 'R'. */
#define DVSVAL  9     /* Solo Switch 'V'. */
#define DRWSPC  10    /* Solo Switch speciale 'W'. */
#define SPECSW  20    /* Gruppo di Switch speciali '?I', '?F', '?M', '?O'. */
#define HELPSW  30    /* Solo Switch speciale '--HELP'. */
#define ERRSW   99    /* Condizione di errore: nessun Switch valido. */

/* Opzioni. */
#define NOPT   '\0'   /* Nessuna opzione usata. */
#define LINF   '?'    /* Opzione per Info. */
#define EHLP   '-'    /* Opzione speciale per Help. */
#define QHLP   'h'    /* Opzione Quick Help. */
#define SYMP   's'    /* Opzione che ottiene i singoli fattori primi e di scomposizione. */
#define TINS   'y'    /* Opzione che ottiene il primo fattore di scomposizione e numeri primi. */
#define FORM   'f'    /* Opzione che ottiene i fattori di scomposizione ed i numeri primi. */
#define ALLDP  'a'    /* Opzione che ottiene liste di fattori primi e di scomposizione. */
#define PRIME  'p'    /* Opzione che ottiene e visualizza solo i fattori primi. */
#define DIVS   'd'    /* Opzione che ottiene e visualizza solo i fattori di scomposizione. */
#define PLIST  'l'    /* Opzione che ottiene solo liste di fattori primi. */
#define NSDIV  'q'    /* Opzione che ottiene solo liste di fattori di scomposizione. */
#define GEMS   'g'    /* Opzione che ottiene serie di numeri primi gemelli. */
#define KEYS   'k'    /* Opzione che ottiene serie di due fattori di scomposizione. */
#define PJUMS  'j'    /* Opzione che ottiene liste di numeri primi gemelli. */
#define LKEYS  'e'    /* Opzione che ottiene liste di due fattori di scomposizione. */
#define NPRIM  'n'    /* Opzione che ottiene solo serie di numeri dispari divisibili. */
#define STAT   't'    /* Opzione che ottiene statistiche su serie di numeriche. */
#define BASE   'b'    /* Opzione che ottiene statistiche scorporando in sotto-serie numeriche. */
#define VARS   'v'    /* Opzione che ottiene serie numeriche con un fattore di scomposizione specifico. */
#define CALC   'c'    /* Opzione che ottiene serie numeriche definite da delta ed elementi specificati. */

/* Switch. */
#define NSWT   '\0'   /* Nessuno Switch usato. */
#define PAGE   '0'    /* Switch speciale abbinato a '-?M'. */
#define NPAG   '1'    /* Switch speciale abbinato a '-?M'. */
#define SSC    'f'    /* Switch speciale_1: opzione '-?F', contributo nascosto. */
#define MAN    'm'    /* Switch speciale_2: opzione '-?M', manuale su file. */
#define ISW    'i'    /* Switch speciale_3: opzione '-?I', manuale integrato. */
#define RIO    'o'    /* Switch speciale 4: opzione '-?O', guida rapida alle opzioni. */
#define EHL    'h'    /* Switch speciale 5: opzione '--HELP'. */
#define DRW    'w'    /* Switch speciale 6: opzione non completamente definita. */
#define TBL    't'    /* Switch di predisposizione incolonnamento. */
#define LST    'l'    /* Switch di giustificazione-1, per opzioni '-A', '-L', '-Q', '-J', '-E'. */
#define POS    'n'    /* Switch di stampa della posizione cardinale dei numeri primi. */
#define CNT    'c'    /* Switch di stampa dei numeri primi dalla serie di posizioni cardinali. */
#define DVS    'v'    /* Switch di stampa dei divisori dei numeri della serie. */
#define RNC    'r'    /* Switch di giustificazione-2, per l'opzione '-L'. */
#define TCN    'b'    /* Switch di giustificazione-3, per l'opzione '-L' . */
#define PME    'p'
#define SEL    's'
#define UPP    'u'    /* Da PME a DOW, Switch di selezione/marcatura nella lista. */
#define DOW    'd'

/* Limiti. */
#define NIM     65535U        /* Inizializzazioni variabili al valore massimo. */
#define AEL     63U
#define PEL     1023U         /* AEL, PEL e MEL. Elementi di array statici. */
#define MEL     8191U
#define LMAX    16U           /* Dimensione array nome file per info locale. */
#define NMAX    255U          /* Dimensione array percorso/nomefile selezione lingua. */
#define RANGE   65536U        /* Limite massimo di elementi per una serie. */
#define RGTAB   262144U       /* Limite massimo di elementi per una serie in una tabella. */
#define RGCNT   4096U         /* Limite massimo di elementi di posizione per una serie. */
#define UL_MAX  4294967296UL  /* Limite massimo di calcolo di un numero primo. */
#define CT_MAX  203280221UL   /* Limite massimo di calcolo della posizione. */
#define LANG    "FLANG="
#define ENDL    "_END"

/* Locale. */
#define NOTL   1   /* Costanti di presenza per manuali e lingue. */
#define YESL   0
#define ENFM   ".en_lng_man\0"
#define ITFM   ".it_lng_man\0"
#define ESFM   ".es_lng_man\0"   /* Manuali di riferimento in vaie lingue. */
#define FRFM   ".fr_lng_man\0"
#define PTFM   ".pt_lng_man\0"
#define DEFM   ".de_lng_man\0"
#define TBPR   ".tabprime_4294967296.txt"   /* File catalog per riferimento numero/posizione. */
#define TBCT   ".tabcount_203280221.txt"

/* Fine definizioni interne. */


/* ---------------------- */
/* Dichiarazioni globali. */
/* ---------------------- */

/* Funzioni. */
unsigned long primenum(unsigned long);   /* Funzione di ricerca del numero primo. */
int divfactors(unsigned long);           /* funzione per il calcolo dei valori di divisibilità. */
int errorstype(short *);                 /* Funzione per la gestione degli errori. */
int filemsg(short *,unsigned long *);    /* Funzione per la gestione dei msg di conferma/errore. */
short cfglang(short *);                  /* Funzione per il cambio della lingua (EN-IT-ES-FR-PT-DE). */
short globopts(void);                    /* Funzione per la gestione(1) di un gruppo di opzioni. */
short globoptions(void);                 /* Funzione per la gestione(2) di gruppi di opzioni. */
short trueoptions(void);                 /* Funzione per la gestione delle opzioni e dei gruppi. */
short trueswitch(void);                  /* Funzione per la gestione dei gruppi di Switch. */
short switcherrs(void);                  /* Funzione per il controllo degli Switch sulle opzioni. */
short tpcol(unsigned long,unsigned long,short *);   /* Funzione di visualizzazione a più colonne. */
void primefact(unsigned long,unsigned long);   /* Funzione di scomposizione in fattori primi e stampa. */
void statseries(unsigned short);         /* Funzione per la gestione statistica. */
void about(short *,char *,char *);       /* Funzione per info iniziali di aiuto e presentazione. */
void quickhelp(short *,char *);          /* Funzione per aiuto rapido. */
void helpfunc(short *,char *,char *);    /* Funzione per aiuto dettagliato. */
void contrib(char *,char *);             /* Funzione contributo occultato. */

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
unsigned long select=1UL;
unsigned long bpos=0UL;
unsigned short column=1U;
unsigned short swflag=HFLAG,fldp=0U;
unsigned short pmin=NIM,dmin=NIM;
unsigned short pmax,dmax;
unsigned short psum,dsum;
unsigned short dmean,pmean;
unsigned short keycnt=0U,cnt=0U,fgem=0U,fprec=0U;
static short lang;
short errscode=0;
short fmesg=0,fsign=0,ncx=1,ncz=1;
char mpos[32],mprm[32];
char option=NOPT;
char subopt=NSWT;
char flgopt=NSWT;
char *verrel=VERSION,*relrel=RELEASE;
char *nprg=NAMEPROG;
char *pnd,*pnf;
char *pesr,*pmsl,*pmpos,*pmprm;
char *usr,*home,*lngm,*pfdr,*pflm;
int lb=0,ls=0,ne=0;
FILE *fp,*fp0,*fp1;
DIR *dp;

/* ---------------------- */
/* Default scelta lingua. */
/* ---------------------- */
static short lngdef=ENGLISH;  /* Selezione lingua default. (ENGLISH, ITALIANO, [ALTRE LINGUE]). */

/* --------------------------- */
/* Segnalazione per lingua non - */
/* completamente implementata.  */
/* --------------------------- */
static short noten=YESL;
static short notit=YESL;   /* Imposta il flag per la visualizzazione del messaggio - */
static short notes=YESL;   /* della lingua non completamente implementata. */
static short notfr=NOTL;   /* YESL = implementazione completa della lingua. */
static short notpt=NOTL;   /* NOTL = implementazione parziale della lingua. */
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
   int divfactors(unsigned long);
   int errorstype(short *);
   int filemsg(short *,unsigned long *);
   short globopts(void);
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

/* Dichiarazione di variabili staticche. */
   extern short lngdef,lang,ncx,ncz;
   extern short noten,notit,notes,notfr,notpt,notde;

/* Dichiarazione di vettori e variabili esterne. */
   extern unsigned long select;
   extern unsigned short column;
   extern unsigned short pmax,dmax,pmin,dmin,keycnt;
   extern unsigned short dmean,pmean,swflag,fldp,fgem,fprec;
   extern unsigned short nprime[],ndivs[],mvect[];
   extern short errscode,fmesg,fsign;
   extern char mpos[],mprm[];
   extern char nfile[],nfdir[],nflgm[],nfman[];
   extern char option,subopt,flgopt;
   extern char *pnd,*pnf,*verrel,*relrel,*nprg;
   extern char *pesr,*pmsl,*pmpos,*pmprm;
   extern char *usr,*home,*lngm,*pfdr,*pflm;
   extern int lb,ls;

/* Dichiarazioni di variabili e puntatori locali. */
   float fdist=0.0,tdist=0.0,fcom=0.0;
   unsigned long num=1UL,limit=1UL,number=1UL,cntbas=1UL,cntlim=1UL;
   unsigned long limt=1UL,com=1UL,tmp=1UL,gtmp=1UL,nppos=1UL,ppos=1UL;
   unsigned long divs=0UL,hfatt=0UL,range=1UL,self=0UL,nprec=2UL;
   unsigned long delf=0UL,base=2UL,cntmp=0U,pprm=1UL,pcnt=1UL;
   unsigned long orig=2UL,cnttmp=0UL,lmtmp=0UL,dstmp=0UL,nccnt=1UL;
   unsigned long cntl=0UL,cntb=0UL,cnta=0UL;
   unsigned short psegm=0U,dsegm=0U,nseg=1U,lseg=0U,sumprim=0U,sumdivs=0U;
   unsigned short selcount=0U,fler=0U,gemcnt=0U,oddcnt=0U,tmpdst=1U;
   unsigned short pcount=0U,dcount=0U,seltot=0U,neld=1U;
   unsigned short npv=0U,nph=0U,npa=0U,ctup=1U,ctdw=1U,ctal=1U;
   unsigned short pdist=0U,hpdist=0U,lpdist=0U,pmdist=0U,flprt=0U;
   unsigned short eflag=LFLAG,mflag=HFLAG,inflag=HFLAG,ndflag=LFLAG;
   unsigned short *pnprime,*pndivs,*pvect;
   char mark=NUL,lask[2],lasklng[12],laskdef[24];
   char stpos[16],*pstpos;
   char cmd[64],*pcmd;
   char esr[5],msl[6],nd[16];
   char w=NUL,x=NUL,y=NUL,z=NUL,X=NUL,chm=NUL;
   char *prog=NAMEPROG,*rels=RELEASE,*plask,*plaskdef,ce=EOF;
   char *plaskln0,*plaskln1,*plaskln2,*plaskln3,*plaskln4;
   short flg=0,flgm=0,flgers=0,tflg=0;
   int ctl=0,chsum=0,a=0,b=0,c=0,i=0;
   for(i=0;i<AEL;++i) cmd[i]=NUL,eval[i]=NUL;
   for(i=0;i<PEL;++i) nprime[i]=NUL,ndivs[i]=NUL;
   for(i=0;i<MEL;++i) mvect[i]=NUL;

/* Inizializzazione di variabili static. */
   lang=lngdef;

/* Inizializzazione del Flag di DEBUG. */
/* Può essere tenuto disattivato, ma è preferibile tenerlo attivato. */
   fsign=1;   /* Se fsign = 1 allora i 'mesg-rif-errors' per debug sono attivi, altrimenti no. */

/* Inizializzazione puntatori. */
   pnprime=nprime; pndivs=ndivs; pvect=mvect;
   plaskdef=laskdef; plaskln0=lasklng;
   plask=lask;
   pesr=esr; pmsl=msl;
   pnd=nd; pnf=nfile;
   lngm=nflgm; pfdr=nfdir;
   pflm=nfman; pcmd=cmd;
   pmpos=mpos; pmprm=mprm;

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
      plaskdef="DEUTCHE (Standard)";   /* Tedesco - Tedesco. */
      plaskln0="ENGLISH";              /* Tedesco - Inglese. */
      plaskln1="ITALIANO";             /* Tedesco - Italiano. */
      plaskln2="ESPAÑOL";              /* Tedesco - Spagnolo. */
      plaskln3="FRANÇAIS";             /* Tedesco - Francese. */
      plaskln4="PORTUGÛES";            /* Tedesco - Portoghese. */
   }
   else {

   /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
   /* delle funzionalità interne, delle opzioni e degli Switch. */
      if(fsign) {
         printf("ERROR [LOCAL] GURU MEDITATION\n\n");
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
         printf("ERROR [ASK-LOC] GURU MEDITATION\n\n");
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

   /* ------------------------------------------------------------------------- */
   /* Esecuzione in caso il file di configurazione sia assente o inaccessibile. */
   /* Visualizza [Ok. Il file predefinito [.firstlang.cfg] è stato creato.]. */
      fmesg=MSGBASE+lang+10;
      filemsg(&fmesg,&self);

   /* Apertura di .firstlang.cfg in scrittura. */
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
      fseek(fp0,-5L,SEEK_END);   /* Sposta l'offest di inizio file. */
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

      /* Se è presente l'opzione '-CLR' senza altri argomenti. */
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

            /* Eliminazione del file di configurazione della lingua locale. */
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

      /* Se è presente l'opzione '-RST' senza altri argomenti. */
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
                  printf("ERROR [INFO-VER] GURU MEDITATION\n\n");
               return GURU;
            }
            printf("~© (2010-2026) - GNU/GPL vers.3\n");
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
                  printf("ERROR [INFO-AUTH] GURU MEDITATION\n\n");
               return GURU;
            }
            printf("\n");
            if(lang==ENGLISH) {
               printf("Legal notes:\n");
               printf(" This software  is distribuited under the  GNU/\n");
               printf("GPLv3 license of Free Software Foundation (FSF)\n");
               printf("«as is», without any form of implicit or expli-\n");
               printf("cit warranty.\n");
               printf(" The author declines all responsibility for any\n");
               printf("direct and/or indirect damages of any kind, wi-\n");
               printf("thout exception, arising  from the use of  this\n");
               printf("Software.\n");
               printf(" This Software is suitable only for educational\n");
               printf("or informational use; its use outside the terms\n");
               printf("of the license is not permitted, except for spe-\n");
               printf("cific exceptions.\n");
               printf(" The author declares that the code of this pro-\n");
               printf("gram, version 109a-20260309, has been  extensi-\n");
               printf("vely tested to consistently ensure correct res-\n");
               printf("ults comparable with those of authoritative and\n");
               printf("certified sources.\n");
               printf("Main references:\n");
               printf(" - Online Encyclopedia of Integer Sequences.\n");
               printf(" - Tables of Prime-Counting Function.\n");
               printf(" Use of this Software implies tacit and comple-\n");
               printf("te acceptance of the above license terms.\n");
               printf("For other references:\n");
               printf(" https://fsf.org/licenses/\n");
               printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
               printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
           }
           else if(lang==ITALIANO) {
               printf("Note legali:\n");
               printf(" Questo Software è distribuito sotto licenza\n");
               printf("GNU/GPLv3 di Free Software Foundation  (FSF)\n");
               printf("«così com'è», senza alcuna forma di garanzia\n");
               printf("implicita e/o esplicita.\n");
               printf(" L'autore declina ogni responsabilità  a se-\n");
               printf("guito di eventuali danni diretti o indiretti\n");
               printf("di qualsiasi natura, senza alcuna eccezione,\n");
               printf("derivanti dall'uso di questo Software.\n");
               printf(" Il presente Software è adatto solo  per uso\n");
               printf("didattico o informativo; non ne è consentito\n");
               printf("l'utilizzo al di fuori dei termini della li-\n");
               printf("cenza d'uso, salvo particolari eccezioni.\n");
               printf(" Il codice  del presente programma (Versione\n");
               printf("109a-20260309), è stato ampiamente testato a\n");
               printf("garanzia  di risultati corretti  comparabili\n");
               printf("con quelli di fonti autorevoli e certificate.\n");
               printf("Riferimenti principali:\n");
               printf(" - Online Encyclopedia of Integer Sequences.\n");
               printf(" - Tables of Prime-Counting Function.\n");
               printf(" L'utilizzo del presente Software implica la\n");
               printf("tacita e completa accettazione  dei suddetti\n");
               printf("termini della licenza d'uso.\n");
               printf("Per altri riferimenti:\n");
               printf(" https://fsf.org/licenses/\n");
               printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
               printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
            }
            else if(lang==ESPANOL) {
               printf("Notas legales:\n");
               printf(" Este software se distribuye bajo la  licencia\n");
               printf("GNU/GPLv3 de la Free Software Foundation (FSF)\n");
               printf(" «tal cual», sin ninguna forma de garantía im-\n");
               printf("plícita y/o explicita.\n");
               printf(" El autor declina toda responsabilidad por cu-\n");
               printf("alquier dãno, directo o indirecto, de cualqui-\n");
               printf("quier tipo, sin excepción alguna, derivado del\n");
               printf("uso de este Software.\n");
               printf(" El presente  software  solo es apto  para uso\n");
               printf("didáctico o informativo, no se permite su  uso\n");
               printf("fuera de los términos  de la licencia de  uso,\n");
               printf("salvo excepciones particulares.\n");
               printf(" El autor declara  que el código  de este pro-\n");
               printf("grama, en la versión 109a-20260309 ha sido am-\n");
               printf("pliamente probado para garantizar siempre  re-\n");
               printf("sultados correctos comparables  con los de fu-\n");
               printf("entes autorizadas y certificadas.\n");
               printf("Referencias principales:\n");
               printf(" - Online Encyclopedia of Integer Sequences.\n");
               printf(" - Tables of Prime-Counting Function.\n");
               printf(" El uso de  este Software  implica la  acepta-\n");
               printf("ción tácita y completa del los términos de li-\n");
               printf("cencia mencionados anterioremente.\n");
               printf("Para otras referencias:\n");
               printf(" https://fsf.org/licenses/\n");
               printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
               printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
            }
            else if(lang==FRANCAIS) {
               printf("Notes légales :\n");
               printf(" Ce logiciel est distribué sous la  licence\n");
               printf("GNU/GPLv3  de la  Free Software  Foundation\n");
               printf("« tel quel », sans aucune forme de garantie\n");
               printf("implicite et/ou explicite.\n");
               printf(" L'auteur décline toute responsabilité pour\n");
               printf("tout dommage direct ou indirect, de quelque\n");
               printf("nature que ce soit, san  aucune  exception,\n");
               printf("découlant de l'utilisation de ce logicel.\n");
               printf(" Ce logiciel ne convient qu'à un usage  di-\n");
               printf("dactique ou informatif ; son utilisation en\n");
               printf("dehors des  termes de la licence  n'est pas\n");
               printf("autorisée, sauf exceptions particulières.\n");
               printf(" L'auteur  déclare  que le code  de ce pro-\n");
               printf("gramme, dans la version 109a-20260309 a été\n");
               printf("largement testé  pour garantir toujour  des\n");
               printf("résultats corrects et comparables à ceux de\n");
               printf("sources faisant autorité et certifiées.\n");
               printf("Références principales :\n");
               printf(" - Online Encyclopedia of Integer Sequences.\n");
               printf(" - Tables of Prime-Counting Function.\n");
               printf("L'utilisation de ce logiciel implique l'ac-\n");
               printf("ceptation tacite et complète  des termes de\n");
               printf("la licence ci-dessus.\n");
               printf("Pour d'autres références :\n");
               printf(" https://fsf.org/licenses/\n");
               printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
               printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
            }
            else if(lang==PORTUGUES) {
               printf("Notas Legais: \n");
               printf(" Este software  é distribuído  sob a licença\n");
               printf("GNU/GPLv3 da Free Software Foundation  (FSF)\n");
               printf("«tal como está» sem qualquer forma de garan-\n");
               printf("tia implícita e/ou explícita.\n");
               printf(" O autor  declina qualquer  responsabilidade\n");
               printf("por eventuais danos  diretos ou indiretos de\n");
               printf("qualquer tipo, sem qualquier exceção, decor-\n");
               printf("rentes do uso deste software.\n");
               printf(" O presente software é adequado apenas  para\n");
               printf("uso didático ou informativo; não é permitida\n");
               printf("a sua utilização fora dos termos da  licença\n");
               printf("de uso, salvo exceções particulares.\n");
               printf(" O autor declara que o código deste programa,\n");
               printf("na versão 109a-20260309, foi amplamente tes-\n");
               printf("tado para garantir sempre resultados  corre-\n");
               printf("tos comparáveis aos de fontes  autorizadas e\n");
               printf("certificadas.\n");
               printf("Réfêrencias principais:\n");
               printf(" - Online Encyclopedia of Integer Sequences.\n");
               printf(" - Tables of Prime-Counting Function.\n");
               printf("O uso deste Software implica a aceitação tá-\n");
               printf("cita e integral dos termos da licença acima.\n");
               printf("Para outras referências:\n");
               printf(" https://fsf.org/licenses/\n");
               printf(" https://www.gnu.org/licenses/gpl-3.0.html\n");
               printf(" https://fsf.org/licenses/fdl.html\n");
               printf(" https://www.gnu.org/copyleft\n\n");
            }
            else if(lang==DEUTCHE) {
               printf("Rechtliche Hinweise: \n");
               printf(" Diese Software  wird unter  der GNU/GPLv3-\n");
               printf("Lizenz der  Free Software Foundation  (FSF)\n");
               printf("„wie besehen“  und ohne jegliche  ausdrück-\n");
               printf("liche oder stillschweigende  Gewährleistung\n");
               printf("verbreitet.\n");
               printf(" Der Autor  übernimmt keinerlei Haftung für\n");
               printf("direkte  oder indirekte  Schäden  jeglicher\n");
               printf("Art, die ohne Ausnahme aus der Natzung die-\n");
               printf("ser Software entstehen.\n");
               printf(" Diese Software  ist nur für  Bildungs oder\n");
               printf("informationszwecke  geeignet; eine  Nutzung\n");
               printf("außerhalb der Lizenzbedingungen ist, vorbe-\n");
               printf("haltlich besonderer Ausnahmen, nicht  nicht\n");
               printf("gestattet.\n");
               printf(" Der Autor  erklärt, dass  der Code  dieses\n");
               printf("Progamms  in der Version 109a-20260309  um-\n");
               printf("fassend  getestet wurde,  um stets korrekte\n");
               printf("Ergebnisse zu gewährleisten, die mit  denen\n");
               printf("maßgeblicher und zertifizierter Quellen ver-\n");
               printf("gleichbar sind.\n");
               printf("Wichtigste referenzen:\n");
               printf(" - Online Encyclopedia of Integer Sequences.\n");
               printf(" - Tables of Prime-Counting Function.\n");
               printf("Die Nutzung dieser Software setzt die stil-\n");
               printf("lschweigende und vollständige Akzeptanz der\n");
               printf("oben genannten Lizenzbedingungen voraus.\n");
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
                  printf("ERROR [INFO-LAW] GURU MEDITATION\n\n");
               return GURU;
            }

         /* Uscita forzata. */
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
               contrib(prog,rels);
               putchar('\n');
               return OK;
            }
            else if(subopt==MAN) {    /* Switch 'M'. */
               if(flgopt!=NSWT) {
                  if(flgopt!=PAGE&&flgopt!=NPAG) {

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

                  /* Se la Directory esiste aggiunge il nome del file al percorso. */
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
                           closedir(dp);
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
               if(lang==ENGLISH) {
                  printf("\n =======================================================================\n");
                  printf("                   %s v.%s   -   Quick Guide.\n",nprg,verrel);
                  printf("  This program  allows the decomposition  of natural numbers  into their\n");
                  printf(" prime factors. It searches for prime numbers and allows  for the detec-\n");
                  printf(" tion of certain characteristics  of their distribution. The program  is\n");
                  printf(" structured to be executed from a Shell and behaves similarly to a  sys-\n");
                  printf(" tem command. It features  many options that differentiate  both its vi-\n");
                  printf(" sualization and operating mode. It is possible to define series of num-\n");
                  printf(" bers to be decomposed into prime factors, search for prime numbers wit-\n");
                  printf(" hin them, or highlight particular properties. Each specified series can\n");
                  printf(" have a maximum width of 65535 elements, while the highest number decom-\n");
                  printf(" posable into prime factors, for which a correct result  is provided, is\n");
                  printf(" 4294967295.\n");
                  printf("  The program has purely educational purposes; it can also be used  when\n");
                  printf(" one needs to know the prime factors of a composite number, or to  check\n");
                  printf(" if a specific value  is prime or not. The algorithm  that generates the\n");
                  printf(" prime factors (prime numbers and decomposition factors) has been exten-\n");
                  printf(" sively tested and  always provides absolutely exact results  consistent\n");
                  printf(" with the context.\n");
                  printf("  The algorithm  used is an optimized «brute force» method,  implemented\n");
                  printf(" in an internal function. The function  calculates  whether a number  is\n");
                  printf(" prime or not, returning zero  if it is prime  or the value of the valid\n");
                  printf(" prime decomposition factor obtained. A variant of this function is used\n");
                  printf(" in the 'first' program; the latter, acting only  on  odd values, is not\n");
                  printf(" designed to return the values of the prime factors.\n");
                  printf("  This Software is provided  «as is», without any form of express or im-\n");
                  printf(" plied warranty. Furthermore, the author declines all responsibility for\n");
                  printf(" any direct and/or indirect damages of any kind, without exception, ari-\n");
                  printf(" sing from the use of this Software.\n");
                  printf("  Notes: The code of this program has been extensively checked and every\n");
                  printf(" functionality has been meticulously tested to guarantee the correctness\n");
                  printf(" of the results provided; additionally, comparison tests were  performed\n");
                  printf(" on some reference numerical series against results provided by reliable\n");
                  printf(" and known sources. Main references:\n");
                  printf(" - OEIS (Online Encyclopedia of Integer Sequences).\n");
                  printf(" - Tables produced with Prime-Counting Function.\n\n");
                  printf(" Examples of main functionalities:\n\n");
                  printf(" %s 911\n",nprg);
                  printf(" Displays itself and all its  prime decomposition factors  if the number\n");
                  printf(" is composite; otherwise, only itself if it is a prime number, as  shown\n");
                  printf(" in this example: 911 (this is a prime number).\n\n");
                  printf(" %s -y 4096\n",nprg);
                  printf(" Displays itself  and  the first decomposition factor  as shown  in this\n");
                  printf(" example: 4096 = 2 (the number is divisible by two).\n\n");
                  printf(" %s -s 4500\n",nprg);
                  printf(" Displays itself and its  prime decomposition factors  in single format,\n");
                  printf(" possibly repeated  for each  prime factor, in the  following  exemplary\n");
                  printf(" way: 4500 = 2 2 3 3 5 5 5\n");
                  printf(" Note: 2 2 3 3 5 5 5 corresponds to 2 x 2 x 2 x 3 x 3 x 5 x 5 x 5\n\n");
                  printf(" %s -f 123456\n",nprg);
                  printf(" Displays itself and its prime decomposition factors in exponential for-\n");
                  printf(" mat as shown in the example: 123456 = (2^6) 3 643\n");
                  printf(" Note: (2^6) 3 643  should be read as two to the sixth power times three\n");
                  printf(" times six hundred and forty-three.\n\n");
                  printf(" %s 1000 9999\n",nprg);
                  printf(" The numbers  1000 and 9999  represent the minimum  and maximum extremes\n");
                  printf(" included  in the indicated numerical series  to be computed. The speci-\n");
                  printf(" fied extremes are part of the series, whose length will be:\n");
                  printf(" (9999 - 1000 + 1) = 9000. It displays all numbers within the series and\n");
                  printf(" all their prime decomposition factors,  also highlighting the  sequence\n");
                  printf(" of all  prime numbers  contained  therein, as  shown  in the  following\n");
                  printf(" example (partial list):\n");
                  printf("  1000 = (2^3) (5^3)\n");
                  printf("  1001 = 7 11 13\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  1007 = 19 53\n");
                  printf("  1008 = (2^4) (3^2) 7\n");
                  printf("  1009\n");
                  printf("  1010 = 2 5 101\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  9996 = (2^2) 3 (7^2) 17\n");
                  printf("  9997 = 13 769\n");
                  printf("  9998 = 2 4999\n");
                  printf("  9999 = (3^2) 11 101\n\n");
                  printf(" %s -y 123456 123499\n",nprg);
                  printf(" Displays  a sequence  consisting of  the number itself  followed by the\n");
                  printf(" first decomposition factor. If the number is prime, obviously no decom-\n");
                  printf(" position factor is displayed, as in the following example \n");
                  printf(" (partial list):\n");
                  printf("   123456 = 2\n");
                  printf("   123457\n");
                  printf("   123458 = 2\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   123461 = 13\n");
                  printf("   123462 = 2\n");
                  printf("   123463 = 331\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   123478 = 2\n");
                  printf("   123479\n");
                  printf("   123480 = 2\n");
                  printf("   123481 = 19\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   123497 = 11\n");
                  printf("   123498 = 2\n");
                  printf("   123499\n\n");
                  printf(" %s -s 123456 123499\n",nprg);
                  printf(" Displays all numbers  of the  indicated series  in sequence,  each fol-\n");
                  printf(" lowed  by all its  prime decomposition factors. If a  number  is prime,\n");
                  printf(" nothing  is displayed  after the number  itself. The prime factors  are\n");
                  printf(" all displayed individually, even repeated multiple times  if necessary.\n");
                  printf(" Each prime factor is separated from the previous one by a space.\n");
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
                  printf(" ...\n");
                  printf("   123497 = 11 103 109\n");
                  printf("   123498 = 2 3 3 3 2287\n");
                  printf("   123499\n\n");
                  printf(" %s -f 1000 1110\n",nprg);
                  printf(" Displays all numbers of the indicated series in sequence, each followed\n");
                  printf(" by  all its prime factors. If a number  is prime, nothing  is displayed\n");
                  printf(" after the  number  itself. It is  similar to the -s  option, difference\n");
                  printf(" that each repeated prime decomposition factor  is displayed with  expo-\n");
                  printf(" nential notation; example: [1000 = (2^3) (5^3)]\n");
                  printf(" instead of: [1000 = 2 2 2 5 5 5].\n");
                  printf(" '-f' is the option that generates this function.\n");
                  printf(" '1000' and '1110' are the minimum and maximum extremes of the series to\n");
                  printf(" be computed and displayed.\n\n");
                  printf(" %s -fS 1000 1110 17\n",nprg);
                  printf(" Displays the sequence  and all decomposition factors  of each number in\n");
                  printf(" the series, including prime numbers, highlighting  the  first divisible\n");
                  printf(" factor of each number  in the series  that matches the one indicated as\n");
                  printf(" the discriminant.\n");
                  printf(" '-fS' indicate the option and the marker respectively.\n");
                  printf(" '1000 and 1110' constitute the minimum and maximum values of the series.\n");
                  printf(" '17'  is the discriminant prime factor, which refers to the 'S'  marker\n");
                  printf(" if specified.\n");
                  printf(" In addition to the marker above, the '-f'  option also accepts the fol-\n");
                  printf(" lowing discrimination markers: 'P' (Prime), 'U' (Up), and 'D' (Down).\n");
                  printf(" In the example shown here (partial list):\n\n");
                  printf(" Prime factor decomposition from 1000 to 1110\n\n");
                  printf("   1000 = (2^3) (5^3)\n");
                  printf("   1001 = 7 11 13\n");
                  printf("   1002 = 2 3 167\n");
                  printf(" > 1003 = 17 59\n");
                  printf("   1004 = (2^2) 251\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   1008 = (2^4) (3^2) 7\n");
                  printf("   1009\n");
                  printf("   1010 = 2 5 101\n");
                  printf("   1011 = 3 337\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf(" the number 1003  is preceded  by the symbol  '>'  because  its  initial\n");
                  printf(" prime decomposition factor is exactly 17.\n");
                  printf(" A summary statistical report on the calculated series follows:\n\n");
                  printf("\n %s %s             Final Summary Report:\n",nprg,verrel);
                  printf(" ------------------------------------------------\n");
                  printf(" Series from number:                         1000\n");
                  printf(" At number:                                  1110\n");
                  printf(" Total series of numbers:                     111\n");
                  printf(" Total prime numbers:                          18\n");
                  printf(" Total composite numbers:                      93\n");
                  printf(" Highest initial prime factor:                 29\n");
                  printf(" Selected prime factor:                        17\n");
                  printf(" Quantity of selected values:                   2\n");
                  printf(" Maximum distance between two primes:          18\n");
                  printf(" Average distance between two primes:           4\n\n");
                  printf(" Almost all options display  a final statistical report, except  for the\n");
                  printf(" '-l', '-q', '-j', '-e', and '-a' options which do not include it.\n");
                  printf(" Each option displays a different statistical report based on the compu-\n");
                  printf(" tation performed and the chosen visualization.\n");
                  printf(" The options '-y', '-s', '-f' also accept the following markers:\n");
                  printf(" 'P' (Prime) highlights all prime numbers in the series with '>'.\n");
                  printf(" 'S' (Select) highlights the indicated prime factor with '>'.\n");
                  printf(" 'U' (Up) highlights with '>' all prime factors greater than or equal to\n");
                  printf(" the one indicated as the reference prime factor.\n");
                  printf(" 'D' (Down) highlights with '>'  all prime factors less than or equal to\n");
                  printf(" the one indicated as the reference prime factor.\n\n");
                  printf(" In addition  to the specific markers  mentioned  above:  'S', 'P', 'U',\n");
                  printf(" and 'D', there are  also some functional Switches  that are specific to\n");
                  printf(" the following options: '-d', '-p', '-n', '-l', and '-q'.\n\n");
                  printf(" The markers above: 'P', 'S', 'U', and 'D', can be applied indifferently\n");
                  printf(" to the following options: '-y', '-s', and '-f'.\n");
                  printf(" The options '-d' and '-k' only accept the 'S', 'U', and 'D' markers.\n");
                  printf(" All other options  do not accept markers, but  only specific functional\n");
                  printf(" or visualization Switches listed below.\n");
                  printf(" The options '-b', '-c', and '-v' do not accept any marker or Switch.\n");
                  printf(" In addition  to the aforementioned markers, there are  also toggles re-\n");
                  printf(" ferred to as Switches. A Switch associated with an option allows chang-\n");
                  printf(" ing some of its properties, such as visualization or even functionality.\n");
                  printf(" Switch 'L' can only be applied to options '-l', '-q', '-j', '-e', '-a'.\n");
                  printf(" Switch 'T' can only be applied to options '-n' and '-p'.\n");
                  printf(" Switch 'N' can only be applied to options '-l' and '-p'.\n");
                  printf(" Switch 'R' can only be applied to option '-l'.\n");
                  printf(" Switch 'C' can only be applied to options '-l' and '-p'.\n");
                  printf(" Switch 'B' can only be applied to option '-l'.\n");
                  printf(" Switch 'V' can only be applied to options '-d' and '-q'.\n");
                  printf(" Switch 'W' can only be applied to option '-d'.\n");
                  printf(" These options are detailed below.\n\n");
                  printf(" %s -d 12344 12388\n",nprg);
                  printf(" Displays only composite numbers with all their prime factors within the\n");
                  printf(" indicated series, as occurs for the '-f' option, but here prime numbers\n");
                  printf(" are ignored.\n");
                  printf(" Example (Partial list):\n");
                  printf("   12344 = (2^3) 1543\n");
                  printf("   12345 = 3 5 823\n");
                  printf("   12346 = 2 6173\n");
                  printf("   12348 = (2^2) (3^2) (7^3)\n");
                  printf("   12349 = 53 233\n");
                  printf("   12350 = 2 (5^2) 13 19\n");
                  printf("   12351 = 3 23 179\n");
                  printf("   12352 = (2^6) 193\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf(" As can be seen, the prime number 12347 is completely ignored.\n\n");
                  printf(" %s -n 12324 12348\n",nprg);
                  printf(" Displays only odd composite numbers  of the indicated series  and their\n");
                  printf(" decomposition factors. It is similar to the '-d'  option,  which is one\n");
                  printf(" of the four options  providing a selective visualization filter, as are\n");
                  printf(" the other two filter options: '-p' and '-k'.\n");
                  printf(" In the example shown below:\n");
                  printf("  12325 = (5^2) 17 29\n");
                  printf("  12327 = 3 7 587\n");
                  printf("  12331 = 11 19 59\n");
                  printf("  12333 = 3 4111\n");
                  printf("  12335 = 5 2467\n");
                  printf("  12337 = (13^2) 73\n");
                  printf("  12339 = (3^3) 457\n");
                  printf("  12341 = 7 41 43\n");
                  printf("  12345 = 3 5 823\n");
                  printf(" one can observe how the list of odd composite numbers and their respec-\n");
                  printf(" tive decomposition factors for the indicated series is shown.\n\n");
                  printf(" %s -p 99 999\n",nprg);
                  printf(" Displays only the sequence of all prime numbers included in the indica-\n");
                  printf(" ted series. It is the complementary option to '-d'.\n");
                  printf(" Example (partial list):\n");
                  printf("  101\n");
                  printf("  103\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  757\n");
                  printf("  761\n");
                  printf("  769\n");
                  printf("  773\n");
                  printf("  787\n");
                  printf("  797\n");
                  printf("  809\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  991\n");
                  printf("  997\n\n");
                  printf(" %s -k 115 145\n",nprg);
                  printf(" Displays a list of composite numbers where the prime decomposition fac-\n");
                  printf(" tors are  always and only two.  It is similar to the '-d'  option, with\n");
                  printf(" the only difference being that  only composite numbers  having  exactly\n");
                  printf(" two divisors are displayed.\n");
                  printf(" Example (partial list):\n");
                  printf("   115 = 5 23\n");
                  printf("   118 = 2 59\n");
                  printf("   119 = 7 17\n");
                  printf("   121 = (11^2)\n");
                  printf("   122 = 2 61\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   141 = 3 47\n");
                  printf("   142 = 2 71\n");
                  printf("   143 = 11 13\n");
                  printf("   145 = 5 29\n\n");
                  printf(" %s -g 10000 10500\n",nprg);
                  printf(" Displays twin prime numbers from a list. This option is similar  to the\n");
                  printf(" '-j'  option but additionally displays a final statistical report.\n");
                  printf(" Example (complete list):\n\n");
                  printf(" Twin prime numbers highlighted, from 10000 to 10500\n\n");
                  printf("  10007 ⋄ 10009\n");
                  printf("  10037 ⋄ 10039\n");
                  printf("  10067 ⋄ 10069\n");
                  printf("  10091 ⋄ 10093\n");
                  printf("  10139 ⋄ 10141\n");
                  printf("  10271 ⋄ 10273\n");
                  printf("  10301 ⋄ 10303\n");
                  printf("  10331 ⋄ 10333\n");
                  printf("  10427 ⋄ 10429\n");
                  printf("  10457 ⋄ 10459\n\n");
                  printf("\n %s %s             Final Summary Report:\n",nprg,verrel);
                  printf(" ------------------------------------------------\n");
                  printf(" Series from number:                        10000\n");
                  printf(" At number:                                 10500\n");
                  printf(" Total series of numbers:                     501\n");
                  printf(" Total prime numbers:                          55\n");
                  printf(" Twin primes (Pairs):                          10\n");
                  printf(" Maximum distance between two primes:          28\n");
                  printf(" Average distance between two primes:           5\n\n");
                  printf(" %s -t 1 65535\n",nprg);
                  printf(" Displays only a statistical report  of aggregate data referring  to the\n");
                  printf(" indicated series of values.\n");
                  printf(" The report  includes entries indicating the  total number of  processed\n");
                  printf(" values, the number of prime factors and composite numbers in the series,\n");
                  printf(" the highest initial decomposition factor, the maximum distance  between\n");
                  printf(" two primes, and more.\n");
                  printf(" Example:\n\n");
                  printf(" %s %s             Final Summary Report:\n",nprg,verrel);
                  printf(" ------------------------------------------------\n");
                  printf(" Selection from number:                         1\n");
                  printf(" To number:                                 65535\n");
                  printf(" Total series of numbers:                   65535\n");
                  printf(" Total prime numbers:                        6542\n");
                  printf(" Total composite numbers:                   58992\n");
                  printf(" Highest initial prime factor:                251\n");
                  printf(" Maximum distance between two primes:          72\n");
                  printf(" Average distance between two primes:           6\n\n");
                  printf(" %s -b 1000 5000 5\n",nprg);
                  printf(" Displays aggregate data of value series from a specified interval,\n");
                  printf(" divided into contiguous sub-lists of arbitrary width. It also\n");
                  printf(" displays a series of summary statistical data.\n");
                  printf(" '-b' is the option that generates this function.\n");
                  printf(" '1000 and 5000' constitute the minimum and maximum values of the series.\n");
                  printf(" '5' indicates the number of subdivisions of the series.\n");
                  printf(" (If the number of subdivisions into sub-lists is not specified, it is\n");
                  printf(" always considered equal to two).\n");
                  printf(" Example (complete list):\n\n");
                  printf(" List decomposition into 5 series.\n");
                  printf(" From number 1000 to number 5000 inclusive.\n\n");
                  printf(" Series from 1000 to 1799 - Prime Numbers 110 - Composite Numbers 690\n");
                  printf(" Series from 1800 to 2599 - Prime Numbers 100 - Composite Numbers 700\n");
                  printf(" Series from 2600 to 3399 - Prime Numbers 100 - Composite Numbers 700\n");
                  printf(" Series from 3400 to 4199 - Prime Numbers  96 - Composite Numbers 704\n");
                  printf(" Series from 4200 to 4999 - Prime Numbers  95 - Composite Numbers 705\n\n");
                  printf("\n %s %s             Final Summary Report:\n",nprg,verrel);
                  printf(" ------------------------------------------------\n");
                  printf(" Selection from number:                      1000\n");
                  printf(" To number:                                  4999\n");
                  printf(" Total prime numbers:                         501\n");
                  printf(" Total composite numbers:                    3499\n");
                  printf(" Numerical series length:                    4000\n");
                  printf(" Number of numerical series:                    5\n");
                  printf(" Series numerical interval:                   800\n");
                  printf(" Average primes in series:                    100\n");
                  printf(" Average composite in series:                 700\n");
                  printf(" Minimum primes in series:                     95\n");
                  printf(" Maximum primes in series:                    110\n");
                  printf(" Minimum composite in series:                 690\n");
                  printf(" Maximum composite in series:                 705\n\n");
                  printf(" %s -v 2500 2999 7\n",nprg);
                  printf(" Displays a selective list of composite numbers with their prime factors\n");
                  printf(" from a  specified interval. The indicated  prime factor  determines the\n");
                  printf(" formation of the displayed series.\n");
                  printf(" '-v' is the option; '2500 2999' is  the interval  of the  specified se-\n");
                  printf(" ries; '7' is the prime factor that determines the formation of the list\n");
                  printf(" itself.\n");
                  printf(" In the example reported here we obtain (partial list):\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  2527 = 7 (19^2)\n");
                  printf("  2569 = 7 367\n");
                  printf("  2597 = (7^2) 53\n");
                  printf("  2611 = 7 373\n");
                  printf("  2639 = 7 13 29\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -c 100001 5000 25\n",nprg);
                  printf(" Displays a selective list from a series  with their prime factors, with\n");
                  printf(" an interval of undetermined width of N elements, a period, and an init-\n");
                  printf(" ial value indicated.\n");
                  printf(" '-c' is the option that generates this function.\n");
                  printf(" '100001' is the initial value of the series.\n");
                  printf(" '5000' is the period between the values of the series.\n");
                  printf(" '25' is the number of elements in the list to be displayed.\n");
                  printf(" The indicated example generates the following series (partial list):\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  110001 = 3 37 991\n");
                  printf("  115001\n");
                  printf("  120001 = (7^2) 31 79\n");
                  printf("  125001 = (3^2) 17 19 43\n");
                  printf("  130001 = 71 1831\n");
                  printf("  135001 = 127 1063\n");
                  printf("  140001 = 3 23 2029\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -l 10000 75000\n",nprg);
                  printf(" Displays a clean list of prime numbers only, without any other distrac-\n");
                  printf(" ting elements at the beginning or end. Prime numbers are displayed  one\n");
                  printf(" per line. This form of visualization is useful for producing long lists\n");
                  printf(" to be redirected to files for subsequent processing.\n");
                  printf(" Visualization example (partial list):\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  74797\n");
                  printf("  74821\n");
                  printf("  74827\n");
                  printf("  74831\n");
                  printf("  74843\n");
                  printf("  74857\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  74897\n");
                  printf("  74903\n");
                  printf("  74923\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -q 10000 75000\n",nprg);
                  printf(" Displays a clean list of all composite numbers included in the  indica-\n");
                  printf(" ted series with all their prime decomposition factors, in a  manner si-\n");
                  printf(" milar to option '-f'  but without any distracting elements at the begin\n");
                  printf(" ning or end. This form  of visualization is useful  for producing  long\n");
                  printf(" formatted lists to be redirected to files for subsequent processing.\n");
                  printf(" Visualization example (partial list):\n");
                  printf(" ...\n");
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
                  printf(" ...\n");
                  printf("  74995 = 5 53 283\n");
                  printf("  74996 = (2^2) 18749\n");
                  printf("  74997 = (3^2) 13 641\n");
                  printf("  74998 = 2 7 11 487\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -qL 1000001 1065535 >> path/filename\n",nprg);
                  printf(" %s -lL 1000001 1065535 >> path/filename\n",nprg);
                  printf(" %s -eL 1000001 1065535 >> path/filename\n",nprg);
                  printf(" %s -jL 1000001 1065535 >> path/filename\n",nprg);
                  printf(" Append to the indicated file, or generate it  if it doesn't exist, res-\n");
                  printf(" pectively a pure list of all series values with all their prime factors\n");
                  printf(" ('-q'), or a list of all prime numbers in the series ('-l').\n\n");
                  printf(" %s -qL 98765 98770\n",nprg);
                  printf(" Displays a list  of composite numbers  and their prime factors  without\n");
                  printf(" initial header and  final statistical report. Furthermore, a particular\n");
                  printf(" justification  is performed that allows  adding more lists to  a single\n");
                  printf(" file seamlessly when using redirection.\n");
                  printf(" Visualization example (complete list):\n");
                  printf("       98765 = 5 19753\n");
                  printf("       98766 = 2 (3^3) 31 59\n");
                  printf("       98767 = 283 349\n");
                  printf("       98768 = (2^4) 6173\n");
                  printf("       98769 = 3 11 41 73\n");
                  printf("       98770 = 2 5 7 17 83\n\n");
                  printf(" %s -lL 987654321 987654399\n",nprg);
                  printf(" Displays solely a list of prime numbers without initial header  and fi-\n");
                  printf(" nal statistical report. Furthermore, a particular justification is per-\n");
                  printf(" formed that allows adding more lists to a  single file  seamlessly when\n");
                  printf(" using redirection.\n");
                  printf(" Visualization example (complete list):\n");
                  printf("   987654323\n");
                  printf("   987654337\n");
                  printf("   987654347\n");
                  printf("   987654359\n");
                  printf("   987654361\n");
                  printf("   987654377\n");
                  printf("   987654379\n");
                  printf("   987654383\n\n");
                  printf(" %s -eL 987654 987699\n",nprg);
                  printf(" Displays solely a list of composite numbers with only two divisors, op-\n");
                  printf(" tion similar to '-k'  and '-e'  with a particular indentation  suitable\n");
                  printf(" for concatenating multiple lists to a file.\n");
                  printf(" Visualization example (complete list):\n");
                  printf("      987661 = 191 5171\n");
                  printf("      987671 = 389 2539\n");
                  printf("      987673 = 433 2281\n");
                  printf("      987683 = 17 58099\n");
                  printf("      987689 = 23 42943\n");
                  printf("      987695 = 5 197539\n");
                  printf("      987699 = 3 329233\n\n");
                  printf(" %s -jL 5500000 5501500\n",nprg);
                  printf(" Displays solely twin prime numbers, without any initial header or final\n");
                  printf(" statistical report. Furthermore, a particular justification  is perfor-\n");
                  printf(" med that  allows concatenating  more lists  of twin primes  in a single\n");
                  printf(" file seamlessly when using redirection.\n");
                  printf(" Visualization example (complete list):\n");
                  printf("  5500277 ⋄    5500279\n");
                  printf("  5500667 ⋄    5500669\n");
                  printf("  5500721 ⋄    5500723\n");
                  printf("  5501057 ⋄    5501059\n");
                  printf("  5501141 ⋄    5501143\n");
                  printf("  5501231 ⋄    5501233\n");
                  printf("  5501399 ⋄    5501401\n\n");
                  printf(" %s -pN 5000 5100\n",nprg);
                  printf(" %s -pC 670 681\n",nprg);
                  printf(" %s -lN 5000 5100\n",nprg);
                  printf(" %s -lR 5000 5100\n",nprg);
                  printf(" %s -lC 670 681\n",nprg);
                  printf(" The options '-pN', '-pC', '-lN', '-lR', and '-lC'  display, along  with\n");
                  printf(" prime numbers, their cardinal position. The  cardinal position  of each\n");
                  printf(" prime number is displayed to its right in parentheses.\n");
                  printf(" The '-pN'  option also  displays  a final statistical report, while the\n");
                  printf(" '-lN' option displays nothing beyond the list itself, making it  suita-\n");
                  printf(" ble for obtaining lists up to 65535 elements in files.\n");
                  printf(" The '-lR' option is similar to '-lN'  but maintains consistent indenta-\n");
                  printf(" tion for concatenating multiple lists to files via redirection.\n");
                  printf(" The '-pC' and '-lC'  options allow obtaining lists of prime numbers  by\n");
                  printf(" specifying their cardinal position.\n");
                  printf(" Visualization example (complete list):\n\n");
                  printf(" Series of prime numbers from position 670 to position 681\n");
                  printf(" Corresponding series from number 5003 to number 5099\n");
                  printf(" (With visualization of the corresponding cardinal position.)\n\n");
                  printf("  5003  (670)\n");
                  printf("  5009  (671)\n");
                  printf("  5011  (672)\n");
                  printf("  5021  (673)\n");
                  printf("  5023  (674)\n");
                  printf("  5039  (675)\n");
                  printf("  5051  (676)\n");
                  printf("  5059  (677)\n");
                  printf("  5077  (678)\n");
                  printf("  5081  (679)\n");
                  printf("  5087  (680)\n");
                  printf("  5099  (681)\n\n");
                  printf("\n %s %s             Final Summary Report:\n",nprg,verrel);
                  printf(" ------------------------------------------------\n");
                  printf(" Selection from cardinal position:            670\n");
                  printf(" To cardinal position:                        681\n");
                  printf(" Series from number:                         5003\n");
                  printf(" To number:                                  5099\n");
                  printf(" Total numbers in series:                      97\n");
                  printf(" Total prime numbers:                          12\n");
                  printf(" Maximum distance between two primes:          18\n");
                  printf(" Average distance between two primes:           9\n\n");
                  printf(" %s -fS 1000 9999 3 | less\n",nprg);
                  printf(" Uses a pipe with the system command 'less' to view one page  or line at\n");
                  printf(" a time. The '-fS' option allows highlighting the indicated first decom-\n");
                  printf(" position factor.\n\n");
                  printf(" Switch 'T' can be associated with options '-n' and '-p' to obtain a ta-\n");
                  printf(" bular visualization, as shown in the examples below.\n");
                  printf(" The '-nT' and '-pT' options allow computing numerical series with leng-\n");
                  printf(" ths up to 262144 elements at a time.\n\n");
                  printf(" %s -nT 99 999\n",nprg);
                  printf(" Displays only the sequence  of odd composite numbers, of the  indicated\n");
                  printf(" series, arranged in multiple columns.\n");
                  printf(" Example (Partial list):\n");
                  printf("   99   105   111   115   117   119   121   123   125   129   133   135\n");
                  printf("  141   143   145   147   153   155   159   161   165   169   171   175\n");
                  printf("  177   183   185   187   189   195   201   203   205   207   209   213\n");
                  printf("  215   217   219   221   225   231   235   237   243   245   247   249\n");
                  printf("  253   255   259   261   265   267   273   275   279   285   287   289\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf("  845   847   849   851   855   861   865   867   869   871   873   875\n");
                  printf("  879   885   889   891   893   895   897   899   901   903   905   909\n");
                  printf("  913   915   917   921   923   925   927   931   933   935   939   943\n");
                  printf("  945   949   951   955   957   959   961   963   965   969   973   975\n");
                  printf("  979   981   985   987   989   993   995   999\n\n");
                  printf(" %s -pT 99 999\n",nprg);
                  printf(" Displays only the sequence of all prime numbers of the indicated series,\n");
                  printf(" arranged in multiple columns. Example (Partial list):\n");
                  printf("  101   103   107   109   113   127   131   137   139   149   151   157\n");
                  printf("  163   167   173   179   181   191   193   197   199   211   223   227\n");
                  printf("  229   233   239   241   251   257   263   269   271   277   281   283\n");
                  printf("  293   307   311   313   317   331   337   347   349   353   359   367\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf("  673   677   683   691   701   709   719   727   733   739   743   751\n");
                  printf("  757   761   769   773   787   797   809   811   821   823   827   829\n");
                  printf("  839   853   857   859   863   877   881   883   887   907   911   919\n");
                  printf("  929   937   941   947   953   967   971   977   983   991   997\n\n");
                  printf(" Functional Switches 'V',  'W',  and 'R', when associated  with specific\n");
                  printf(" options '-p'  and '-q',  allow generating  all divisibility values  for\n");
                  printf(" each number in the series. These Switches  can only be applied  as fol-\n");
                  printf(" lows: '-dV', '-dW', '-qV', and '-qR'. Although for some numbers divisi-\n");
                  printf(" bility factors are equivalent to decomposition factors, the  two funct-\n");
                  printf(" ions are different. In this function, all divisors  are considered, in-\n");
                  printf(" cluding even ones, not just  prime decomposition factors. Many  numbers\n");
                  printf(" return multiple divisibility values that  can be displayed  across mul-\n");
                  printf(" tiple lines. Switch 'W' can be used instead of 'V' as it allows varying\n");
                  printf(" the  initial justification  via a third argument  with values between 0\n");
                  printf(" and 8.\n\n");
                  printf(" %s -dV 12320 12330\n",nprg);
                  printf(" %s -dW 12320 12330 0\n",nprg);
                  printf(" Display all divisibility values for each number in the series, even  on\n");
                  printf(" multiple lines.\n");
                  printf(" Visualization example (complete list):\n\n");
                  printf(" Divisibility values for each number\n");
                  printf(" in the series indicated from 12320 to 12330\n\n");
                  printf("  12320 = 2 4 5 7 8 10 11 14 16 20 22 28 32 35 40 44 55 56 70 77 80 88 1\n");
                  printf(" 10 112 140 154 160 176 220 224 280 308 352 385 440 560 616 770 880 1120\n");
                  printf(" 1232 1540 1760 2464 3080 6160\n");
                  printf("  12321 = 3 9 37 111 333 1369 4107\n");
                  printf("  12322 = 2 61 101 122 202 6161\n");
                  printf("  12324 = 2 3 4 6 12 13 26 39 52 78 79 156 158 237 316 474 948 1027 2054\n");
                  printf(" 3081 4108 6162\n");
                  printf("  12325 = 5 17 25 29 85 145 425 493 725 2465\n");
                  printf("  12326 = 2 6163\n");
                  printf("  12327 = 3 7 21 587 1761 4109\n");
                  printf("  12328 = 2 4 8 23 46 67 92 134 184 268 536 1541 3082 6164\n");
                  printf("  12330 = 2 3 5 6 9 10 15 18 30 45 90 137 274 411 685 822 1233 1370 2055\n");
                  printf(" 2466 4110 6165\n\n");
                  printf("\n %s %s             Final Summary Report:\n",nprg,verrel);
                  printf(" ------------------------------------------------\n");
                  printf(" Series from number:                        12320\n");
                  printf(" To number:                                 12330\n");
                  printf(" Total numbers in series:                      11\n");
                  printf(" Total composite numbers:                       9\n\n");
                  printf(" Options with relative Switches '-qV' and '-qR' are complementary to op-\n");
                  printf(" tions '-pV' and '-pW', as they do not display header or footer layouts,\n");
                  printf(" making  them suitable  for creating  concatenated lists  seamlessly  in\n");
                  printf(" files.\n\n");
                  printf(" Listed below are all the allowed combinations between options, markers,\n");
                  printf(" and Switches, along with the required number of arguments.\n");
                  printf(" Realistic reference values  are used  in the examples. Each series  can\n");
                  printf(" contain up  to 65536  elements. The absolute  maximum value  analyzable\n");
                  printf(" is: 4294967295.\n");
                  printf(" Example of calculating  a series with  the maximum number  of elements:\n");
                  printf(" (150000 + 65536 - 1) = 215535, or: (500000 - 65536 + 1) = 434465\n");
                  printf(" %s -f 150000 215535\n",nprg);
                  printf(" %s -f 434465 500000\n\n",nprg);
                  printf(" Complete list of options with markers and functional Switches.\n");
                  printf(" %s 1234567890\n",nprg);
                  printf(" %s 1234567890 1234567890\n",nprg);
                  printf(" %s 12345 54321\n",nprg);
                  printf(" %s -t 987654321 987667890\n",nprg);
                  printf(" %s -y 1 65535\n",nprg);
                  printf(" %s -s 1 65535\n",nprg);
                  printf(" %s -f 1 65535\n",nprg);
                  printf(" %s -a 1 65535\n",nprg);
                  printf(" %s -aL 10000 75535\n",nprg);
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
                  printf(" %s -dS 10000 500000 7\n",nprg);
                  printf(" %s -dU 10000 500000 13\n",nprg);
                  printf(" %s -dD 10000 500000 3\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -kS 35000 100535 23\n",nprg);
                  printf(" %s -kU 35000 100535 19\n",nprg);
                  printf(" %s -kD 35000 100535 11\n",nprg);
                  printf(" %s -g 10000 75000\n",nprg);
                  printf(" %s -p 4050000 4099999\n",nprg);
                  printf(" %s -pT 450000 499999\n",nprg);
                  printf(" %s -pN 15000 25000\n",nprg);
                  printf(" %s -pC 100 4195\n",nprg);
                  printf(" %s -n 4050000 4099999\n",nprg);
                  printf(" %s -nT 450000 499999\n",nprg);
                  printf(" %s -dV 29000 29030\n",nprg);
                  printf(" %s -dW 29000 29300\n",nprg);
                  printf(" %s -qV 45000 45500\n",nprg);
                  printf(" %s -qR 34000 99535 >> path/filename\n",nprg);
                  printf(" %s -l 774579999 774629999\n",nprg);
                  printf(" %s -lL 745599 796699 >> path/filename\n",nprg);
                  printf(" %s -lN 50000 100000\n",nprg);
                  printf(" %s -lR 59999 119999 >> path/filename\n",nprg);
                  printf(" %s -lC 1000 5095\n",nprg);
                  printf(" %s -lB 5000 9095 >> path/filename\n",nprg);
                  printf(" %s -j 1999 65999\n",nprg);
                  printf(" %s -jL 500 65999 >> path/filename\n",nprg);
                  printf(" %s -q 774579999 774629999\n",nprg);
                  printf(" %s -qL 7450999 7499999 >> path/filename\n",nprg);
                  printf(" %s -e 255000 257999\n",nprg);
                  printf(" %s -eL 255000 257999 >> path/filename\n",nprg);
                  printf(" %s -b 5050000 5099999\n",nprg);
                  printf(" %s -b 9050000 9115000 20\n",nprg);
                  printf(" %s -c 1111111 123 40 > path/filename\n",nprg);
                  printf(" %s -v 9000000 9065534 7\n",nprg);
                  printf(" %s -h\n",nprg);
                  printf(" %s -?\n",nprg);
                  printf(" %s -?I\n",nprg);
                  printf(" %s -?M\n",nprg);
                  printf(" %s -?O\n",nprg);
                  printf(" %s -?M0\n",nprg);
                  printf(" %s -?M1\n",nprg);
                  printf(" %s -?F\n",nprg);
                  printf(" %s --help\n\n",nprg);
                  printf(" Notes:\n");
                  printf(" Although options, markers, and Switches can be written in either lower-\n");
                  printf(" case or uppercase, it is advisable to write the option in lowercase and\n");
                  printf(" the marker in uppercase. The marker, when needed, must always  be writ-\n");
                  printf(" ten after the option: it is not possible  to place a marker  before the\n");
                  printf(" option. Only some options allow the use of a marker.\n");
                  printf(" Each option must be preceded by a horizontal dash, otherwise  it is re-\n");
                  printf(" cognized as a numerical argument, except in the case of EN, IT, ES, FR,\n");
                  printf(" PT, and DE, which are  specific options  for setting the local language\n");
                  printf(" and therefore «should be used as they are» without a dash.\n");
                  printf(" The program features  a relatively sophisticated  input error notifica-\n");
                  printf(" tion system with self-explanatory properties that facilitate learning.\n");
                  printf(" =======================================================================\n\n");
               }
               else if(lang==ITALIANO) {
                  printf("\n =======================================================================\n");
                  printf("                  %s v.%s   -   Guida rapida.\n",nprg,verrel);
                  printf("  Questo programma permette di scomporre i numeri naturali nei loro fat-\n");
                  printf(" tori primi. Ricerca i numeri primi e permette di rilevare alcune carat-\n");
                  printf(" teristiche  della loro  distribuzione.  Il programma è strutturato  per\n");
                  printf(" essere eseguito da una Shell e si presenta in modo simile ad un comando\n");
                  printf(" di sistema. Dispone di molte opzioni che ne differenziano sia la visua-\n");
                  printf(" lizzazione sia il modo operativo. E' possibile definire serie di numeri\n");
                  printf(" da scomporre nei loro fattori primi oppure di ricercarvi all'interno di\n");
                  printf(" esse i relativi numeri primi o evidenziarne particolari proprietà. Ogni\n");
                  printf(" serie indicata può avere un'ampiezza massima di 65535 elementi, mentre,\n");
                  printf(" il numero più alto, scomponibile in fattori primi, di cui viene fornito\n");
                  printf(" un risultato corretto, è 4294967295.\n");
                  printf("  Il programma ha solamente una  finalità  didattica, può inoltre essere\n");
                  printf(" usato quando serve conoscere i fattori primi di scomposizione di un nu-\n");
                  printf(" mero divisibile, oppure sapere se un  determinato valore  è primo o no.\n");
                  printf(" L'algoritmo che genera i fattori primi (numeri primi e fattori di scom-\n");
                  printf(" posizione) è stato  ampiamente testato  e fornisce sempre assolutamente\n");
                  printf(" risultati esatti e coerenti al contesto.\n");
                  printf("  L'algoritmo usato è  «brute force»  ottimizzato, è implementato in una\n");
                  printf(" funzione interna. La funzione calcola  se un numero è primo  oppure no,\n");
                  printf(" restituendo zero se è primo oppure il valore del fattore primo di scom-\n");
                  printf(" posizione valido ottenuto. Una variante, di tale funzione è, utilizzata\n");
                  printf(" nel programma first, quest'ultima agendo solo su dei valori dispari non\n");
                  printf(" è predisposta a restituire i valori dei fattori primi di scomposizione.\n");
                  printf("  Il presente Software viene fornito «così com'è», senza alcuna forma di\n");
                  printf(" garanzia esplicita o implicita. L'autore inoltre declina ogni responsa-\n");
                  printf(" bilità a seguito di eventuali danni diretti e/o indiretti, di qualsiasi\n");
                  printf(" tipo, senza alcuna eccezione, derivanti dall'uso di questo Software.\n");
                  printf("  Note:  Il codice di questo programma è stato largamente controllato ed\n");
                  printf(" ogni sua funzionalità  è stata minuziosamente testata  per garantire la\n");
                  printf(" correttezza dei risultati forniti, inoltre sono stati fatti dei Test di\n");
                  printf(" comparazione su alcune serie numeriche di riferimento, con i  risultati\n");
                  printf(" forniti da fonti affidabili e note. Riferimenti principali:\n");
                  printf(" - OEIS (Online Encyclopedia of Integer Sequences).\n");
                  printf(" - Tabelle prodotte con Prime-Counting Function.\n\n");
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
                  printf(" ...\n");
                  printf("  1007 = 19 53\n");
                  printf("  1008 = (2^4) (3^2) 7\n");
                  printf(" 1009\n");
                  printf("  1010 = 2 5 101\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  9996 = (2^2) 3 (7^2) 17\n");
                  printf("  9997 = 13 769\n");
                  printf("  9998 = 2 4999\n");
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
                  printf(" ...\n");
                  printf("   123461 = 13\n");
                  printf("   123462 = 2\n");
                  printf("   123463 = 331\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   123478 = 2\n");
                  printf("   123479\n");
                  printf("   123480 = 2\n");
                  printf("   123481 = 19\n");
                  printf(" ...\n");
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
                  printf(" -fS'  indicano rispettivamente l'opzione ed il marcatore.\n");
                  printf(" '1000 e 1110'  costituiscono i valori minimo e massimo della serie.\n");
                  printf(" '17'  è il fattore primo di scomposizione discriminante, che fa riferi-\n");
                  printf(" mento al marcatore 'S' eventualmente specificato.\n");
                  printf(" Oltre al marcatore sopra indicato, l'opzione '-f' accetta anche i segu-\n");
                  printf(" enti marcatori di discriminazione: 'P' (Prime), 'U' (Up) e 'D' (Down).\n");
                  printf(" Nell'esempio qui riportato (lista parziale):\n\n");
                  printf(" Scomposizione in fattori primi da 1000 a 1110\n\n");
                  printf("   1000 = (2^3) (5^3)\n");
                  printf("   1001 = 7 11 13\n");
                  printf("   1002 = 2 3 167\n");
                  printf(" > 1003 = 17 59\n");
                  printf("   1004 = (2^2) 251\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   1008 = (2^4) (3^2) 7\n");
                  printf("   1009\n");
                  printf("   1010 = 2 5 101\n");
                  printf("   1011 = 3 337\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf(" il numero primo  1003  è preceduto dal simbolo  '>'  perché il suo ini-\n");
                  printf(" ziale fattore primo di scomposizione è appunto 17.\n");
                  printf(" Fa seguito un rapporto statistico riassuntivo sulla serie calcolata:\n\n");
                  printf("\n %s %s     Rapporto riassuntivo finale:\n",nprg,verrel);
                  printf(" -----------------------------------------------\n");
                  printf(" Serie dal número:                          1000\n");
                  printf(" Al numero:                                 1110\n");
                  printf(" Serie totale di numeri:                     111\n");
                  printf(" Totale numeri primi:                         18\n");
                  printf(" Totale dei numeri divisibili:                93\n");
                  printf(" Fattore primo iniziale più alto:             29\n");
                  printf(" Fattore primo selezionato:                   17\n");
                  printf(" Quantità di valori selezionati:               2\n");
                  printf(" Distanza massima tra due numeri primi:       18\n");
                  printf(" Distanza media tra due numeri primi:          4\n\n");
                  printf(" Quasi tutte le opzioni visualizzano un rapporto statistico finale, sal-\n");
                  printf(" vo per le opzioni '-l', '-q', '-j', '-e' ed '-a', che non lo prevedono.\n");
                  printf(" Ogni opzione  visualizza  un  rapporto statistico  diverso  in funzione\n");
                  printf(" della computazione effettuata e della visualizzazione prescelta.\n");
                  printf(" Le opzioni '-y', '-s', '-f' accettano anche i seguenti marcatori:\n");
                  printf(" 'P' (Prime)  evidenzia con '>'  tutti i numeri primi nella serie.\n");
                  printf(" 'S' (Select) evidenzia con '>'  il fattore primo indicato.\n");
                  printf(" 'U' (Up)  evidenzia con '>'  tutti i fattori primi maggiori  o uguali a\n");
                  printf(" quello indicato come fattore primo di riferimento.\n");
                  printf(" 'D' (Down)  evidenzia con '>'  tutti i fattori primi minori  o uguali a\n");
                  printf(" quello indicato come fattore primo di riferimento.\n\n");
                  printf(" Oltre ai marcatori specifici, indicati qui sopra:  'S', 'P', 'U' e 'D',\n");
                  printf(" ci sono anche alcuni Switches funzionali  che sono specifici per le se-\n");
                  printf(" guenti opzioni: '-d', '-p', '-n', -l' e '-q'.\n\n");
                  printf(" I marcatori sopra indicati: 'P', S', 'U' e 'D', possono essere applica-\n");
                  printf(" ti indifferentemente alle seguenti opzioni: '-y', '-s' ed '-f'.\n");
                  printf(" Le opzioni '-d' e '-k' accettano solo i marcatori 'S', 'U', e 'D'.\n");
                  printf(" Tutte le altre opzioni non accettano marcatori, ma solo Switch  funzio-\n");
                  printf(" nali o di visualizzazione specifici riportati qui in seguito.\n");
                  printf(" Le opzioni '-b', '-c' e '-v' non accettano alcun marcatore nè Switch.\n");
                  printf(" Oltre ai suddetti marcatori ci sono anche dei commutatori indicati come\n");
                  printf(" Switches. Uno Switch associato ad una opzione permette di cambiarne al-\n");
                  printf(" cune proprietà quali la visualizzazione o addirittura la funzionalità.\n");
                  printf(" Lo Switch 'L' può essere applicato solo alle opzioni '-l', '-q', '-j',\n");
                  printf(" '-e' ed '-a',\n");
                  printf(" Lo Switch 'T' puo essere applicato solo alle opzioni '-n' e '-p'.\n");
                  printf(" Lo Switch 'N' puo essere applicato solo alle opzioni '-l' e '-p'.\n");
                  printf(" Lo Switch 'R' puo essere applicato solo all'opzione '-l'\n");
                  printf(" Lo Switch 'C' puo essere applicato solo alle opzioni '-l' e '-p'.\n");
                  printf(" Lo Switch 'B' puo essere applicato solo all'opzione '-l'\n");
                  printf(" Lo Switch 'V' puo essere applicato solo alle opzioni '-d' e '-q'.\n");
                  printf(" Lo Switch 'W' puo essere applicato solo all'opzione '-d'.\n");
                  printf(" Queste opzioni sono riportate in seguito.\n\n");
                  printf(" %s -d 12344 12388\n",nprg);
                  printf(" Visualizza solo  i numeri divisibili con tutti i loro  fattori primi di\n");
                  printf(" scomposizione compresi nella serie indicata, come avvene  per l'opzione\n");
                  printf(" '-f', ma qui i numeri primi sono ignorati.\n");
                  printf(" Esempio (Lista parziale):\n");
                  printf("   12344 = (2^3) 1543\n");
                  printf("   12345 = 3 5 823\n");
                  printf("   12346 = 2 6173\n");
                  printf("   12348 = (2^2) (3^2) (7^3)\n");
                  printf("   12349 = 53 233\n");
                  printf("   12350 = 2 (5^2) 13 19\n");
                  printf("   12351 = 3 23 179\n");
                  printf("   12352 = (2^6) 193\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf(" Come si può notare il numero primo 12347 viene completamente ignorato.\n\n");
                  printf(" %s -n 12324 12348\n",nprg);
                  printf(" Visualizza solo i numeri divisibili dispari, della serie indicata, ed i\n");
                  printf(" loro fattori di scomposizione. È simile all'opzione '-d' che è una del-\n");
                  printf(" le quattro opzioni che forniscono un filtro selettivo della visualizza-\n");
                  printf(" zione, come lo sono le altre due opzioni di filtro: '-p' e '-k'.\n");
                  printf(" Nell'esempio qui sotto riportato:\n");
                  printf("  12325 = (5^2) 17 29\n");
                  printf("  12327 = 3 7 587\n");
                  printf("  12331 = 11 19 59\n");
                  printf("  12333 = 3 4111\n");
                  printf("  12335 = 5 2467\n");
                  printf("  12337 = (13^2) 73\n");
                  printf("  12339 = (3^3) 457\n");
                  printf("  12341 = 7 41 43\n");
                  printf("  12345 = 3 5 823\n");
                  printf(" si può osservare come viene mostrata la lista di numeri divisibili dis-\n");
                  printf(" pari ed i rispettivi fattori di scomposizione della serie indicata.\n\n");
                  printf(" %s -p 99 999\n",nprg);
                  printf(" Visualizza solo  la successione di tutti i numeri primi  compresi nella\n");
                  printf(" serie indicata. E' l'opzione complementare alla '-d'.\n");
                  printf(" Esempio (lista parziale):\n");
                  printf("  101\n");
                  printf("  103\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  757\n");
                  printf("  761\n");
                  printf("  769\n");
                  printf("  773\n");
                  printf("  787\n");
                  printf("  797\n");
                  printf("  809\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  991\n");
                  printf("  997\n\n");
                  printf(" %s -k 115 145\n",nprg);
                  printf(" Visualizza una lista di numeri divisibili dove i fattori primi di scom-\n");
                  printf(" posizione sono sempre e solamente due. È simile all'opzione '-d' con la\n");
                  printf(" sola differenza che  vengono visualizzati solo i numeri divisibili  che\n");
                  printf(" hanno esattamente solo due divisori.\n");
                  printf(" Esempio (lista parziale):\n");
                  printf("   115 = 5 23\n");
                  printf("   118 = 2 59\n");
                  printf("   119 = 7 17\n");
                  printf("   121 = (11^2)\n");
                  printf("   122 = 2 61\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   141 = 3 47\n");
                  printf("   142 = 2 71\n");
                  printf("   143 = 11 13\n");
                  printf("   145 = 5 29\n\n");
                  printf(" %s -g 10000 10500\n",nprg);
                  printf(" Visualizza i numeri primi gemelli da una lista. Questa opzione è simile\n");
                  printf(" all'opzione '-j' ma in più visualizza un rapporto statistico finale.\n");
                  printf(" Esempio (lista completa):\n\n");
                  printf(" Numeri primi gemelli evidenziati, da 10000 a 10500\n\n");
                  printf("  10007 ⋄ 10009\n");
                  printf("  10037 ⋄ 10039\n");
                  printf("  10067 ⋄ 10069\n");
                  printf("  10091 ⋄ 10093\n");
                  printf("  10139 ⋄ 10141\n");
                  printf("  10271 ⋄ 10273\n");
                  printf("  10301 ⋄ 10303\n");
                  printf("  10331 ⋄ 10333\n");
                  printf("  10427 ⋄ 10429\n");
                  printf("  10457 ⋄ 10459\n\n");
                  printf("\n %s %s     Rapporto riassuntivo finale:\n",nprg,verrel);
                  printf(" -----------------------------------------------\n");
                  printf(" Serie dal numero:                         10000\n");
                  printf(" Al numero:                                10500\n");
                  printf(" Serie totale di numeri:                     501\n");
                  printf(" Totale numeri primi:                         55\n");
                  printf(" Numeri primi gemelli (Coppie):               10\n");
                  printf(" Distanza massima tra due numeri primi:       28\n");
                  printf(" Distanza media tra due numeri primi:          5\n\n");
                  printf(" %s -t 1 65535\n",nprg);
                  printf(" Visualizza solo un rapporto statistico dei dati aggregati riferiti alla\n");
                  printf(" serie di valori indicata.\n");
                  printf(" Il rapporto comprende alcune voci che indicano il numero totale dei va-\n");
                  printf(" lori processati, il numero fattori primi e dei numeri divisibili  della\n");
                  printf(" serie, dell'iniziale  fattore di scomposizione piu alto, della  massima\n");
                  printf(" distanza tra due numeri primi, ed altro ancora.\n");
                  printf(" Esempio:\n\n");
                  printf(" %s %s     Rapporto riassuntivo finale:\n",nprg,verrel);
                  printf(" -----------------------------------------------\n");
                  printf(" Selezione dal numero:                         1\n");
                  printf(" Al numero:                                65535\n");
                  printf(" Serie totale di numeri:                   65535\n");
                  printf(" Totale numeri primi:                       6542\n");
                  printf(" Totale dei numeri divisibili:             58992\n");
                  printf(" Fattore primo iniziale più alto:            251\n");
                  printf(" Distanza massima tra due numeri primi:       72\n");
                  printf(" Distanza media tra due numeri primi:          6\n\n");
                  printf(" %s -b 1000 5000 5\n",nprg);
                  printf(" Visualizza i dati aggregati  delle serie di valori  da un intervallo di\n");
                  printf(" valori specificato suddivise in sotto-liste contigue  di ampiezza arbi-\n");
                  printf(" traria. Visualizza inoltre una serie di dati statistici riassuntivi.\n");
                  printf(" '-b'  è l'opzione che genera questa funzione.\n");
                  printf(" '1000 e 5000'  costituiscono i valori minimo e massimo della serie.\n");
                  printf(" '5'  indica il numero di suddivisioni della serie.\n");
                  printf(" (Se il numero  di suddivisioni in sotto-liste  non è specificato, viene\n");
                  printf(" considerato sempre uguale a due).\n");
                  printf(" Esempio (lista completa):\n\n");
                  printf(" Scomposizione lista in 5 serie.\n");
                  printf(" Dal numero 1000 al numero 5000 inclusi.\n\n");
                  printf(" Serie da  1000 a  1799 - Numeri Primi  110 - Numeri Divisibili  690\n");
                  printf(" Serie da  1800 a  2599 - Numeri Primi  100 - Numeri Divisibili  700\n");
                  printf(" Serie da  2600 a  3399 - Numeri Primi  100 - Numeri Divisibili  700\n");
                  printf(" Serie da  3400 a  4199 - Numeri Primi   96 - Numeri Divisibili  704\n");
                  printf(" Serie da  4200 a  4999 - Numeri Primi   95 - Numeri Divisibili  705\n\n");
                  printf("\n %s %s     Rapporto riassuntivo finale:\n",nprg,verrel);
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
                  printf(" ...\n");
                  printf("  2527 = 7 (19^2)\n");
                  printf("  2569 = 7 367\n");
                  printf("  2597 = (7^2) 53\n");
                  printf("  2611 = 7 373\n");
                  printf("  2639 = 7 13 29\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -c 100001 5000 25\n",nprg);
                  printf(" Visualizza  una lista selettiva da una serie  con i loro fattori primi,\n");
                  printf(" con un intervallo di ampiezza non determinata di N elementi, un periodo\n");
                  printf(" ed un valore iniziale indicati.\n");
                  printf(" '-c' è l'opzione che genera questa funzione.\n");
                  printf(" '100001' è il valore iniziale della serie.\n");
                  printf(" '5000' è il periodo tra i valori della serie.\n");
                  printf(" '25' è il numero di elementi della lista da visualizzare.\n");
                  printf(" L'esempio indicato genera la seguente serie (lista parziale):\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  110001 = 3 37 991\n");
                  printf("  115001\n");
                  printf("  120001 = (7^2) 31 79\n");
                  printf("  125001 = (3^2) 17 19 43\n");
                  printf("  130001 = 71 1831\n");
                  printf("  135001 = 127 1063\n");
                  printf("  140001 = 3 23 2029\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -l 10000 75000\n",nprg);
                  printf(" Visualizza  una lista pulita  di soli numeri primi  senza nessun  altro\n");
                  printf(" elemento di disturbo, sia in testa che coda. I numeri primi sono visua-\n");
                  printf(" lizzati uno per riga. Questa forma di visualizzazione  è utile per pro-\n");
                  printf(" durre lunghe liste da redirigere su file, per successive  elaborazioni.\n");
                  printf(" Esempio di visualizzazione (lista parziale):\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  74797\n");
                  printf("  74821\n");
                  printf("  74827\n");
                  printf("  74831\n");
                  printf("  74843\n");
                  printf("  74857\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  74897\n");
                  printf("  74903\n");
                  printf("  74923\n");
                  printf(" ...\n");
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
                  printf(" ...\n");
                  printf("  74995 = 5 53 283\n");
                  printf("  74996 = (2^2) 18749\n");
                  printf("  74997 = (3^2) 13 641\n");
                  printf("  74998 = 2 7 11 487\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -qL 1000001 1065535 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -lL 1000001 1065535 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -eL 1000001 1065535 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -jL 1000001 1065535 >> percorso/nome_del_file\n",nprg);
                  printf(" Accodano al file indicato, o lo generano se non esiste, rispettivanente\n");
                  printf(" una lista pura  di tutti i valori della serie  con tutti i loro fattori\n");
                  printf(" primi di scomposizione ('-q'), oppure una lista di tutti i numeri primi\n");
                  printf(" compresi nella serie ('-l').\n\n");
                  printf(" %s -qL 98765 98770\n",nprg);
                  printf(" Visualizza  una lista  di numeri divisibili  ed i loro fattori primi di\n");
                  printf(" scomposizione senza intestazione iniziale e rapposto statistico finale.\n");
                  printf(" Inoltre, viene effettuata una particolare giustificazione  che permette\n");
                  printf(" di aggiungere  più liste in un unico file senza soluzione di continuità\n");
                  printf(" quando si usa la redirezione.\n");
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
                  printf(" colare giustificazione che permette di aggiungere più liste in un unico\n");
                  printf(" file senza soluzione di continuità quando si usa la redirezione.\n");
                  printf(" Esempio di visualizzazione (lista completa):\n");
                  printf("   987654323\n");
                  printf("   987654337\n");
                  printf("   987654347\n");
                  printf("   987654359\n");
                  printf("   987654361\n");
                  printf("   987654377\n");
                  printf("   987654379\n");
                  printf("   987654383\n\n");
                  printf(" %s -eL 987654 987699\n",nprg);
                  printf(" Visualizza unicamente una lista di numeri divisibili con solamente  due\n");
                  printf(" divisori, Opzione simile a '-k' ed '-e' con una particolare indentazio-\n");
                  printf(" ne adatta alla concatenazione di più liste su file.\n");
                  printf(" Esempio di visualizzazione (lista completa):\n");
                  printf("      987661 = 191 5171\n");
                  printf("      987671 = 389 2539\n");
                  printf("      987673 = 433 2281\n");
                  printf("      987683 = 17 58099\n");
                  printf("      987689 = 23 42943\n");
                  printf("      987695 = 5 197539\n");
                  printf("      987699 = 3 329233\n\n");
                  printf(" %s -jL 5500000 5501500\n",nprg);
                  printf(" Visualizza unicamente i numeri primi gemelli, senza alcuna intestazione\n");
                  printf(" iniziale  né rapporto statistico  finale. Viene inoltre effettuata  una\n");
                  printf(" particolare  giustificazione che permette  di concatenare più  liste di\n");
                  printf(" numeri primi gemelli  in un unico file  senza  soluzione  di continuità\n");
                  printf(" quando si usa la redirezione.\n");
                  printf(" Esempio di visualizzazione (lista completa):\n");
                  printf("  5500277 ⋄    5500279\n");
                  printf("  5500667 ⋄    5500669\n");
                  printf("  5500721 ⋄    5500723\n");
                  printf("  5501057 ⋄    5501059\n");
                  printf("  5501141 ⋄    5501143\n");
                  printf("  5501231 ⋄    5501233\n");
                  printf("  5501399 ⋄    5501401\n\n");
                  printf(" %s -pN 5000 5100\n",nprg);
                  printf(" %s -pC 670 681\n",nprg);
                  printf(" %s -lN 5000 5100\n",nprg);
                  printf(" %s -lR 5000 5100\n",nprg);
                  printf(" %s -lC 670 681\n",nprg);
                  printf(" Le opzioni  '-pN', '-pC', '-lN', '-lR' e '-lC'  visualizzano insieme ai\n");
                  printf(" numeri primi anche la loro posizione cardinale.\n");
                  printf(" La posizione cardinale di ogni numero primo viene visualizzata alla sua\n");
                  printf(" destra le parentesi tonde.\n");
                  printf(" L'opzione '-pN'  visualizza anche un rapporto statistico finale, mentre\n");
                  printf(" l'opzione '-lN'  non visualizza nulla oltre che la lista stessa, perciò\n");
                  printf(" è adatta per ottenere liste su file fino a 65535 elementi.\n");
                  printf(" L'opzione '-lR' è simile all'opzione '-lN', ma in più mantiene un iden-\n");
                  printf(" tazione coerente  che permette di concatenare più liste su file, ognuna\n");
                  printf(" sempre con un massimo di 65536 elementi, tramite la redirezione.\n");
                  printf(" Le opzioni '-pC' ed '-lC', simili alle precedenti, invece permettono di\n");
                  printf(" ottenere liste di numeri primi indicandone la loro posizione cardinale.\n");
                  printf(" Esempio di visualizzazione (lista completa):\n\n");
                  printf(" Serie di numeri primi dalla posizione 670 alla posizione 681\n");
                  printf(" Serie corrispondente dal numero 5003 al numero 5099\n");
                  printf(" (Con visualizzazione della corrispondente posizione cardinale.)\n\n");
                  printf("  5003  (670)\n");
                  printf("  5009  (671)\n");
                  printf("  5011  (672)\n");
                  printf("  5021  (673)\n");
                  printf("  5023  (674)\n");
                  printf("  5039  (675)\n");
                  printf("  5051  (676)\n");
                  printf("  5059  (677)\n");
                  printf("  5077  (678)\n");
                  printf("  5081  (679)\n");
                  printf("  5087  (680)\n");
                  printf("  5099  (681)\n\n");
                  printf("\n %s %s     Rapporto riassuntivo finale:\n",nprg,verrel);
                  printf(" -----------------------------------------------\n");
                  printf(" Selezione dalla posizione cardinale:        670\n");
                  printf(" Alla posizione cardinale:                   681\n");
                  printf(" Serie dal numero:                          5003\n");
                  printf(" Al numero:                                 5099\n");
                  printf(" Totale dei numeri della serie:               97\n");
                  printf(" Totale dei numeri primi:                     12\n");
                  printf(" Distanza massima tra due numeri primi:       18\n");
                  printf(" Distanza media tra due numeri primi:          9\n\n");
                  printf(" %s -fS 1000 9999 3 | less\n",nprg);
                  printf(" Utilizza una pipe con il comando di sistema 'less' per visualizzare una\n");
                  printf(" pagina o una riga per volta. L'opzione '-fS' permette di evidenziare il\n");
                  printf(" primo fattore di scomposizione indicato.\n\n");
                  printf(" Alle opzioni '-n' e '-p'  è associabile lo Switch 'T'  per ottenere una\n");
                  printf(" visualizzazione tabellare, come mostrato negli esempi sotto riportati.\n");
                  printf(" Le opzioni '-nT' e '-pT'  permettono di computare delle serie numeriche\n");
                  printf(" con lunghezza fino a 262144 elementi per volta.\n\n");
                  printf(" %s -nT 99 999\n",nprg);
                  printf(" Visualizza solo la successione dei numeri dispari divisibili, della se-\n");
                  printf(" rie indicata, disposti su più colonne.\n");
                  printf(" Esempio (Lista parziale):\n");
                  printf("   99   105   111   115   117   119   121   123   125   129   133   135\n");
                  printf("  141   143   145   147   153   155   159   161   165   169   171   175\n");
                  printf("  177   183   185   187   189   195   201   203   205   207   209   213\n");
                  printf("  215   217   219   221   225   231   235   237   243   245   247   249\n");
                  printf("  253   255   259   261   265   267   273   275   279   285   287   289\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf("  845   847   849   851   855   861   865   867   869   871   873   875\n");
                  printf("  879   885   889   891   893   895   897   899   901   903   905   909\n");
                  printf("  913   915   917   921   923   925   927   931   933   935   939   943\n");
                  printf("  945   949   951   955   957   959   961   963   965   969   973   975\n");
                  printf("  979   981   985   987   989   993   995   999\n\n");
                  printf(" %s -pT 99 999\n",nprg);
                  printf(" Visualizza solo  la successione di tutti i numeri primi della serie in-\n");
                  printf(" dicata, disposti su più colonne. Esempio (Lista parziale):\n");
                  printf("  101   103   107   109   113   127   131   137   139   149   151   157\n");
                  printf("  163   167   173   179   181   191   193   197   199   211   223   227\n");
                  printf("  229   233   239   241   251   257   263   269   271   277   281   283\n");
                  printf("  293   307   311   313   317   331   337   347   349   353   359   367\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf("  673   677   683   691   701   709   719   727   733   739   743   751\n");
                  printf("  757   761   769   773   787   797   809   811   821   823   827   829\n");
                  printf("  839   853   857   859   863   877   881   883   887   907   911   919\n");
                  printf("  929   937   941   947   953   967   971   977   983   991   997\n\n");
                  printf(" Gli Switch funzionali 'V', 'W' e 'R', permettono, quando associati alle\n");
                  printf(" specifiche opzioni '-p' e '-q'  di generare per ogni numero della serie\n");
                  printf(" tutti i valori di divisibilità. Tali Switch funzionali  si possono solo\n");
                  printf(" applicare alle suddette opzioni esclusivamente nel modo seguente: '-dV'\n");
                  printf(" '-dW', '-qV' e '-qR'. Sebbene per alcuni numeri i fattori  di divisibi-\n");
                  printf(" lità  siano  equivalenti  ai fattori di scomposizione, per ovvi motivi,\n");
                  printf(" tuttavia  le due funzioni  sono differenti. In questa funzione  vengono\n");
                  printf(" considerati tutti i divisori del numero, anche quelli  pari, non solo i\n");
                  printf(" fattori primi di scomposizione. Molti numeri ritornano molteplici valo-\n");
                  printf(" ri di divisibilità  che possono essere visualizzati anche su più righe.\n");
                  printf(" Lo Switch 'W'  in tale caso può essere utilizzato in sostituzione dello\n");
                  printf(" Switch 'V' in quanto  permette di variarne la  giustificazione iniziale\n");
                  printf(" tramite un terzo argomento con valori compresi tra 0 ed 8.\n\n");
                  printf(" %s -dV 12320 12330\n",nprg);
                  printf(" %s -dW 12320 12330 0\n",nprg);
                  printf(" Visualizzano tutti i valori di divisibilità per ogni numero della serie\n");
                  printf(" anche su piu righe.\n");
                  printf(" Esempio di visualizzazione (lista completa):\n\n");
                  printf(" Valori di divisibilità per ogni numero\n");
                  printf(" della serie indicata da 12320 a 12330\n\n");
                  printf("  12320 = 2 4 5 7 8 10 11 14 16 20 22 28 32 35 40 44 55 56 70 77 80 88 1\n");
                  printf(" 10 112 140 154 160 176 220 224 280 308 352 385 440 560 616 770 880 1120\n");
                  printf(" 1232 1540 1760 2464 3080 6160\n");
                  printf("  12321 = 3 9 37 111 333 1369 4107\n");
                  printf("  12322 = 2 61 101 122 202 6161\n");
                  printf("  12324 = 2 3 4 6 12 13 26 39 52 78 79 156 158 237 316 474 948 1027 2054\n");
                  printf(" 3081 4108 6162\n");
                  printf("  12325 = 5 17 25 29 85 145 425 493 725 2465\n");
                  printf("  12326 = 2 6163\n");
                  printf("  12327 = 3 7 21 587 1761 4109\n");
                  printf("  12328 = 2 4 8 23 46 67 92 134 184 268 536 1541 3082 6164\n");
                  printf("  12330 = 2 3 5 6 9 10 15 18 30 45 90 137 274 411 685 822 1233 1370 2055\n");
                  printf(" 2466 4110 6165\n\n");
                  printf("\n %s %s     Rapporto riassuntivo finale:\n",nprg,verrel);
                  printf(" -----------------------------------------------\n");
                  printf(" Serie dal numero:                         12320\n");
                  printf(" Al numero:                                12330\n");
                  printf(" Totale dei numeri della serie:               11\n");
                  printf(" Totale dei numeri divisibili:                 9\n\n");
                  printf(" Le opzioni, con relativi Switch, '-qV' e '-qR'  sono complementari alle\n");
                  printf(" opzioni, con relativi Switch, '-pV' e '-pW'  in quanto non visualizzano\n");
                  printf(" alcun prospetto nè di testa nè di coda, risultando adatte alla creazio-\n");
                  printf(" ne di liste concatenate senza soluzione di continuità su file.\n\n");
                  printf(" Qui di seguito  sono riportate  tutte le combinazioni  che sono ammesse\n");
                  printf(" tra le varie opzioni ed i relativi marcatori e Switch, oltre  al numero\n");
                  printf(" di argomenti richiesto. Negli esempi sono utilizzati  valori di riferi-\n");
                  printf(" mento realistici. Ogni serie può contenere fino ad un massimo di  65536\n");
                  printf(" elementi. Il valore massimo assoluto analizzabile è: 4294967295\n");
                  printf(" Esempio di calcolo di una serie con il massimo numero di elementi:\n");
                  printf(" (150000 + 65536 - 1) = 215535,  oppure: (500000 - 65536 + 1) = 434465\n");
                  printf(" %s -f 150000 215535\n",nprg);
                  printf(" %s -f 434465 500000\n\n",nprg);
                  printf(" Lista completa delle opzioni con marcatori e Switch funzionali.\n");
                  printf(" %s 1234567890\n",nprg);
                  printf(" %s 1234567890 1234567890\n",nprg);
                  printf(" %s 12345 54321\n",nprg);
                  printf(" %s -t 987654321 987667890\n",nprg);
                  printf(" %s -y 1 65535\n",nprg);
                  printf(" %s -s 1 65535\n",nprg);
                  printf(" %s -f 1 65535\n",nprg);
                  printf(" %s -a 1 65535\n",nprg);
                  printf(" %s -aL 10000 75535\n",nprg);
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
                  printf(" %s -dS 10000 500000 7\n",nprg);
                  printf(" %s -dU 10000 500000 13\n",nprg);
                  printf(" %s -dD 10000 500000 3\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -kS 35000 100535 23\n",nprg);
                  printf(" %s -kU 35000 100535 19\n",nprg);
                  printf(" %s -kD 35000 100535 11\n",nprg);
                  printf(" %s -g 10000 75000\n",nprg);
                  printf(" %s -p 4050000 4099999\n",nprg);
                  printf(" %s -pT 450000 499999\n",nprg);
                  printf(" %s -pN 15000 25000\n",nprg);
                  printf(" %s -pC 100 4195\n",nprg);
                  printf(" %s -n 4050000 4099999\n",nprg);
                  printf(" %s -nT 450000 499999\n",nprg);
                  printf(" %s -dV 29000 29030\n",nprg);
                  printf(" %s -dW 29000 29300\n",nprg);
                  printf(" %s -qV 45000 45500\n",nprg);
                  printf(" %s -qR 34000 99535 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -l 774579999 774629999\n",nprg);
                  printf(" %s -lL 745599 796699 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -lN 50000 100000\n",nprg);
                  printf(" %s -lR 59999 119999 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -lC 1000 5095\n",nprg);
                  printf(" %s -lB 5000 9095 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -j 1999 65999\n",nprg);
                  printf(" %s -jL 500 65999 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -q 774579999 774629999\n",nprg);
                  printf(" %s -qL 7450999 7499999 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -e 255000 257999\n",nprg);
                  printf(" %s -eL 255000 257999 >> percorso/nome_del_file\n",nprg);
                  printf(" %s -b 5050000 5099999\n",nprg);
                  printf(" %s -b 9050000 9115000 20\n",nprg);
                  printf(" %s -c 1111111 123 40 > percorso/nome_del_file\n",nprg);
                  printf(" %s -v 9000000 9065534 7\n",nprg);
                  printf(" %s -h\n",nprg);
                  printf(" %s -?\n",nprg);
                  printf(" %s -?I\n",nprg);
                  printf(" %s -?M\n",nprg);
                  printf(" %s -?O\n",nprg);
                  printf(" %s -?M0\n",nprg);
                  printf(" %s -?M1\n",nprg);
                  printf(" %s -?F\n",nprg);
                  printf(" %s --help\n\n",nprg);
                  printf(" Note:\n");
                  printf(" Sebbene le opzioni, i marcatori e gli Switch si possono scrivere indif-\n");
                  printf(" ferentemente sia in minuscolo  che maiuscolo, è consigliabile  tuttavia\n");
                  printf(" scrivere l'opzione in minuscolo, ed il marcatore in maiuscolo.\n");
                  printf(" Il marcatore, quando serve, deve sempre  essere scritto dopo l'opzione:\n");
                  printf(" non è possibile anteporre un marcatore all'opzione. Solo alcune opzioni\n");
                  printf(" permettono l'uso di un marcatore. Ogni opzione  deve essere preceduta a\n");
                  printf(" sua volta dal trattino orrizzontale, altrimenti viene riconosciuta come\n");
                  printf(" argomento numerico, salvo nel caso di EN, IT, ES, FR, PT e DE, che sono\n");
                  printf(" opzioni  paricolari  per l'impostazione  della lingua  locale  e quindi\n");
                  printf(" «vanno usate così come sono» senza anteporvi il trattino.\n");
                  printf(" Il programma è dotato di un sistema di notifica degli errori di digita-\n");
                  printf(" zione delle opzioni e dei parametri relativamente sofisticato, con pro-\n");
                  printf(" prietà autoesplicative che ne facilitano l'apprendimento.\n");
                  printf(" =======================================================================\n\n");
               }
               else if(lang==ESPANOL) {
                  printf(" =======================================================================\n");
                  printf("                   %s v.%s   -   Guía rápida.\n",nprg,verrel);
                  printf("  Este programa  permite la descomposición  de números naturales  en sus\n");
                  printf(" factores primos. Busca números primos  y permite la  detección de cier-\n");
                  printf(" tas características de su distribución. El programa  está  estructurado\n");
                  printf(" para ejecutarse  desde una Shell  y se comporta de  manera similar a un\n");
                  printf(" comando del sistema. Presenta muchas opciones  que diferencian tanto su\n");
                  printf(" visualización como su modo de operación. Es posible  definir  series de\n");
                  printf(" números para descomponer los en factores primos, buscar  números primos\n");
                  printf(" en ellas  o resaltar propiedades particulares. Cada serie  especificada\n");
                  printf(" puede tener un ancho máximo de 65535  elementos, mientras que el número\n");
                  printf(" más alto descomponible en factores primos, para el cual  se proporciona\n");
                  printf(" un resultado correcto, es 4294967295.\n");
                  printf("  El programa  tiene  fines  puramente educativos; también  puede usarse\n");
                  printf(" cuando se necesita conocer los factores primos  de un número compuesto,\n");
                  printf(" o para comprobar si un valor específico es primo o no. El algoritmo que\n");
                  printf(" genera los factores primos (números primos y factores de descomposición)\n");
                  printf(" ha sido probado extensamente y siempre proporciona resultados absoluta-\n");
                  printf(" mente exactos y coherentes con el contexto.\n");
                  printf("  El algoritmo utilizado es un método de «fuerza bruta»  optimizado, im-\n");
                  printf(" plementado en una función interna. La función  calcula si  un número es\n");
                  printf(" primo o no, devolviendo cero si es primo  o el valor del factor de des-\n");
                  printf(" composición primo válido obtenido. Una variante de esta función se uti-\n");
                  printf(" liza en el programa 'first'; este último, al  actuar solo sobre valores\n");
                  printf(" impares, no está diseñado para devolver los factores primos.\n");
                  printf("  Este Software se proporciona «tal cual», sin ninguna forma de garantía\n");
                  printf(" expresa o implícita. Además, el autor declina toda responsabilidad  por\n");
                  printf(" cualquier daño directo y/o indirecto  de cualquier tipo, sin excepción,\n");
                  printf(" derivado del uso de este Software.\n");
                  printf(" Notas: El código  de este programa  ha sido  revisado exhaustivamente y\n");
                  printf(" cada funcionalidad  ha sido probada  meticulosamente para garantizar la\n");
                  printf(" corrección de los resultados proporcionados; además, se realizaron prue-\n");
                  printf(" bas de comparación  en algunas series numéricas  de referencia frente a\n");
                  printf(" resultados proporcionados por fuentes fiables y conocidas.\n");
                  printf(" Referencias principales:\n");
                  printf(" - OEIS (Enciclopedia en Línea de Secuencias de Enteros).\n");
                  printf(" - Tablas producidas con la Función de Conteo de Números Primos.\n\n");
                  printf(" Ejemplos de funcionalidades principales:\n\n");
                  printf(" %s 911\n",nprg);
                  printf(" Muestra el número y  todos sus factores de descomposición primos  si el\n");
                  printf(" número es compuesto; de lo contrario, solo el número  si es primo, como\n");
                  printf(" se muestra en este ejemplo: 911 (este es un número primo).\n\n");
                  printf(" %s -y 4096\n",nprg);
                  printf(" Muestra el número y el primer factor de descomposición  como se muestra\n");
                  printf(" en este ejemplo: 4096 = 2 (el número es divisible por dos).\n\n");
                  printf(" %s -s 4500\n",nprg);
                  printf(" Muestra el número y sus factores primos en formato simple, posiblemente\n");
                  printf(" repetidos para cada factor primo, de la siguiente manera ejemplar:\n");
                  printf(" 4500 = 2 2 3 3 5 5 5\n");
                  printf(" Nota: 2 2 3 3 5 5 5 corresponde a 2 x 2 x 3 x 3 x 5 x 5 x 5\n\n");
                  printf(" %s -f 123456\n",nprg);
                  printf(" Muestra el número y sus factores primos en formato exponencial  como se\n");
                  printf(" muestra en el ejemplo: 123456 = (2^6) 3 643\n");
                  printf(" Nota: (2^6) 3 643 debe leerse como dos a la sexta potencia por tres por\n");
                  printf(" seiscientos cuarenta y tres.\n\n");
                  printf(" %s 1000 9999\n",nprg);
                  printf(" Los números 1000 y 9999 representan los extremos mínimo y máximo inclu-\n");
                  printf(" idos en la serie numérica indicada para ser calculada. Los extremos es-\n");
                  printf(" pecificados forman parte de la serie, cuya longitud será:\n");
                  printf(" (9999 - 1000 + 1) = 9000. Muestra  todos los números dentro de la serie\n");
                  printf(" y todos  sus factores de  descomposición primos, resaltando  también la\n");
                  printf(" secuencia de todos  los números primos  contenidos en ella, como se mu-\n");
                  printf(" estra en el siguiente ejemplo (lista parcial):\n");
                  printf("  1000 = (2^3) (5^3)\n");
                  printf("  1001 = 7 11 13\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  1007 = 19 53\n");
                  printf("  1008 = (2^4) (3^2) 7\n");
                  printf("  1009\n");
                  printf("  1010 = 2 5 101\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  9996 = (2^2) 3 (7^2) 17\n");
                  printf("  9997 = 13 769\n");
                  printf("  9998 = 2 4999\n");
                  printf("  9999 = (3^2) 11 101\n\n");
                  printf(" %s -y 123456 123499\n",nprg);
                  printf(" Muestra una secuencia  que consiste en el propio número  seguido por el\n");
                  printf(" primer factor de descomposición. Si el número  es primo, obviamente  no\n");
                  printf(" se muestra ningún factor de descomposición, como en el ejemplo siguien-\n");
                  printf(" te (lista parcial):\n");
                  printf("   123456 = 2\n");
                  printf("   123457\n");
                  printf("   123458 = 2\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   123461 = 13\n");
                  printf("   123462 = 2\n");
                  printf("   123463 = 331\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   123478 = 2\n");
                  printf("   123479\n");
                  printf("   123480 = 2\n");
                  printf("   123481 = 19\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   123497 = 11\n");
                  printf("   123498 = 2\n");
                  printf("   123499\n\n");
                  printf(" %s -s 123456 123499\n",nprg);
                  printf(" Muestra todos los números  de la serie  indicada en secuencia, cada uno\n");
                  printf(" seguido por todos sus  factores de descomposición primos. Si un  número\n");
                  printf(" es primo, no se muestra nada después del propio número.\n");
                  printf(" Los factores primos se muestran individualmente, incluso repetidos var-\n");
                  printf(" ias veces si es necesario. Cada factor primo se separa del anterior por\n");
                  printf(" un espacio.\n");
                  printf(" Ejemplo (lista parcial):\n");
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
                  printf(" ...\n");
                  printf("   123497 = 11 103 109\n");
                  printf("   123498 = 2 3 3 3 2287\n");
                  printf("   123499\n\n");
                  printf(" %s -f 1000 1110\n",nprg);
                  printf(" Muestra todos los números  de la serie indicada  en secuencia, cada uno\n");
                  printf(" seguido por todos sus factores primos. Si un número es primo, no se mu-\n");
                  printf(" estra nada después del número.\n");
                  printf(" Es similar a la opción -s, con la diferencia de que cada factor de des-\n");
                  printf(" composición primo repetido se muestra con notación exponencial;\n");
                  printf(" ejemplo: [1000 = (2^3) (5^3)] en lugar de: [1000 = 2 2 2 5 5 5].\n");
                  printf(" '-f' es la opción que genera esta función. '1000' y '1110'  son los ex-\n");
                  printf(" tremos mínimo y máximo de la serie a calcular y mostrar.\n\n");
                  printf(" %s -fS 1000 1110 17\n",nprg);
                  printf(" Muestra la secuencia y todos los factores de descomposición de cada nú-\n");
                  printf(" mero en la serie, incluidos los primos, resaltando el primer factor di-\n");
                  printf(" visible de cada  número  en la serie que coincida  con el indicado como\n");
                  printf(" discriminante.\n");
                  printf(" '-fS' indican la opción y el marcador respectivamente.\n");
                  printf(" '1000 y 1110' constituyen los valores mínimo y máximo.\n");
                  printf(" '17' es el  factor primo discriminante, que se refiere  al marcador 'S'\n");
                  printf(" si se especifica.\n");
                  printf(" Además del marcador anterior, la opción '-f' también acepta los siguien-\n");
                  printf(" tes marcadores de discriminación: 'P' (Primo), 'U'\n");
                  printf(" (Arriba) y 'D' (Abajo).\n");
                  printf(" En el ejemplo mostrado (lista parcial):\n\n");
                  printf(" Descomposición en factores primos del 1000 al 1110\n\n");
                  printf("   1000 = (2^3) (5^3)\n");
                  printf("   1001 = 7 11 13\n");
                  printf("   1002 = 2 3 167\n");
                  printf(" > 1003 = 17 59\n");
                  printf("   1004 = (2^2) 251\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   1008 = (2^4) (3^2) 7\n");
                  printf("   1009\n");
                  printf("   1010 = 2 5 101\n");
                  printf("   1011 = 3 337\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf(" el número 1003  está precedido por el símbolo '>' porque su primer fac-\n");
                  printf(" tor de descomposición primo es exactamente 17.\n");
                  printf(" Sigue un informe estadístico resumido sobre la serie calculada:\n\n");
                  printf("\n %s %s            Informe final resumido:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf(" Serie del número:                            1000\n");
                  printf(" Al numero:                                   1110\n");
                  printf(" Números totales de la serie:                  111\n");
                  printf(" Números primos totales:                        18\n");
                  printf(" Números divisibles totales:                    93\n");
                  printf(" Factor primo inicial más alto:                 29\n");
                  printf(" Factor primo seleccionado:                     17\n");
                  printf(" Candidad de números seleccionados:              2\n");
                  printf(" Distancia maxima entre dos números primos:     18\n");
                  printf(" Distancia media entre dos números primos:       6\n\n");
                  printf(" Casi todas las opciones muestran un  informe estadístico final, excepto\n");
                  printf(" las opciones '-l', '-q', '-j', '-e' y '-a' que no lo incluyen. Cada op-\n");
                  printf(" ción muestra un informe estadístico diferente basado en el cálculo rea-\n");
                  printf(" lizado y la visualización elegida.\n");
                  printf(" Las opciones '-y', '-s', '-f' también aceptan los siguientes marcadores:\n");
                  printf(" 'P' (Primo) resalta todos los números primos de la serie con '>'.\n");
                  printf(" 'S' (Select) resalta el factor primo indicado con '>'.\n");
                  printf(" 'U' (Up) resalta con '>' todos los factores primos mayores o iguales al\n");
                  printf(" indicado como factor primo de referencia.\n");
                  printf(" 'D' (Down) resalta con '>' todos los factores primos  menores o iguales\n");
                  printf(" al de referencia.\n\n");
                  printf(" Además de los marcadores específicos mencionados: 'S', 'P', 'U' y  'D',\n");
                  printf(" también hay algunos Switches  funcionales específicos para las siguien-\n");
                  printf(" tes opciones: '-d', '-p', '-n', '-l' y '-q'.\n\n");
                  printf(" Los marcadores anteriores: 'P', 'S', 'U' y 'D', pueden aplicarse indis-\n");
                  printf(" tintamente a las siguientes opciones: '-y', '-s' y '-f'.\n");
                  printf(" Las opciones '-d' y '-k' solo aceptan los marcadores 'S', 'U' y 'D'.\n");
                  printf(" Todas las demás opciones no aceptan marcadores, sino solo Switches fun-\n");
                  printf(" cionales o de visualización específicos listados abajo.\n");
                  printf(" Las opciones '-b', '-c' y '-v' no aceptan ningún marcador o Switch.\n");
                  printf(" Además de los marcadores mencionados, también hay conmutadores  denomi-\n");
                  printf(" nados Switches. Un  'Switch'  asociado  con una opción  permite cambiar\n");
                  printf(" algunas de sus propiedades, como la visualización o incluso la  funcio-\n");
                  printf(" nalidad.\n");
                  printf(" El Switch 'L' solo puede aplicarse a las opciones '-l', '-q', '-j',\n");
                  printf(" '-e', '-a'.\n");
                  printf(" El Switch 'T' solo puede aplicarse a las opciones '-n' y '-p'.\n");
                  printf(" El Switch 'N' solo puede aplicarse a las opciones '-l' y '-p'.\n");
                  printf(" El Switch 'R' solo puede aplicarse a la opción '-l'.\n");
                  printf(" El Switch 'C' solo puede aplicarse a las opciones '-l' y '-p'.\n");
                  printf(" El Switch 'B' solo puede aplicarse a la opción '-l'.\n");
                  printf(" El Switch 'V' solo puede aplicarse a las opciones '-d' y '-q'.\n");
                  printf(" El Switch 'W' solo puede aplicarse a la opción '-d'.\n");
                  printf(" Estas opciones se detallan a continuación.\n\n");
                  printf(" %s -d 12344 12388\n",nprg);
                  printf(" Muestra solo números compuestos con todos sus factores primos dentro de\n");
                  printf(" la serie indicada, como ocurre con la opción '-f', pero aquí se ignoran\n");
                  printf(" los números primos.\n");
                  printf(" Ejemplo (lista parcial):\n");
                  printf("   12344 = (2^3) 1543\n");
                  printf("   12345 = 3 5 823\n");
                  printf("   12346 = 2 6173\n");
                  printf("   12348 = (2^2) (3^2) (7^3)\n");
                  printf("   12349 = 53 233\n");
                  printf("   12350 = 2 (5^2) 13 19\n");
                  printf("   12351 = 3 23 179\n");
                  printf("   12352 = (2^6) 193\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf(" Como se puede ver, el número primo 12347 es completamente ignorado.\n\n");
                  printf(" %s -n 12324 12348\n",nprg);
                  printf(" Muestra solo números compuestos impares de la serie indicada y sus fac-\n");
                  printf(" tores de descomposición. Es similar a la opción '-d', que es una de las\n");
                  printf(" cuatro opciones que proporcionan un filtro de  visualización selectiva,\n");
                  printf(" al igual que las otras dos: '-p' y '-k'.\n");
                  printf(" En el ejemplo:\n");
                  printf("  12325 = (5^2) 17 29\n");
                  printf("  12327 = 3 7 587\n");
                  printf("  12331 = 11 19 59\n");
                  printf("  12333 = 3 4111\n");
                  printf("  12335 = 5 2467\n");
                  printf("  12337 = (13^2) 73\n");
                  printf("  12339 = (3^3) 457\n");
                  printf("  12341 = 7 41 43\n");
                  printf("  12345 = 3 5 823\n");
                  printf(" se observa cómo se muestra la lista de números compuestos impares y sus\n");
                  printf(" respectivos factores de descomposición para la serie indicada.\n\n");
                  printf(" %s -p 99 999\n",nprg);
                  printf(" Muestra solo  la secuencia de todos los números primos  incluidos en la\n");
                  printf(" serie indicada. Es la opción complementaria a '-d'.\n");
                  printf(" Ejemplo (lista parcial):\n");
                  printf("  101\n");
                  printf("  103\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  757\n");
                  printf("  761\n");
                  printf("  769\n");
                  printf("  773\n");
                  printf("  787\n");
                  printf("  797\n");
                  printf("  809\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  991\n");
                  printf("  997\n\n");
                  printf(" %s -k 115 145\n",nprg);
                  printf(" Muestra una lista de números compuestos donde los factores de descompo-\n");
                  printf(" sición primos son siempre y solo dos. Es similar a la opción '-d',  con\n");
                  printf(" la única diferencia de que solo se muestran  los números compuestos que\n");
                  printf(" tienen exactamente dos divisores.\n");
                  printf(" Ejemplo (lista parcial):\n");
                  printf("   115 = 5 23\n");
                  printf("   118 = 2 59\n");
                  printf("   119 = 7 17\n");
                  printf("   121 = (11^2)\n");
                  printf("   122 = 2 61\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("   141 = 3 47\n");
                  printf("   142 = 2 71\n");
                  printf("   143 = 11 13\n");
                  printf("   145 = 5 29\n\n");
                  printf(" %s -g 10000 10500\n",nprg);
                  printf(" Muestra números primos gemelos de una lista.\n");
                  printf(" Esta opción es similar a la opción '-j' pero además  muestra un informe\n");
                  printf(" estadístico final.\n");
                  printf(" Ejemplo (lista completa):\n\n");
                  printf(" Primos gemelos resaltados, del 10000 al 10500\n\n");
                  printf("  10007 ⋄ 10009\n");
                  printf("  10037 ⋄ 10039\n");
                  printf("  10067 ⋄ 10069\n");
                  printf("  10091 ⋄ 10093\n");
                  printf("  10139 ⋄ 10141\n");
                  printf("  10271 ⋄ 10273\n");
                  printf("  10301 ⋄ 10303\n");
                  printf("  10331 ⋄ 10333\n");
                  printf("  10427 ⋄ 10429\n");
                  printf("  10457 ⋄ 10459\n\n");
                  printf("\n %s %s            Informe final resumido:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf(" Serie del número:                           10000\n");
                  printf(" Al numero:                                  10500\n");
                  printf(" Números totales de la serie:                  501\n");
                  printf(" Números primos totales:                        55\n");
                  printf(" Números primos gemelos (Pares):                10\n");
                  printf(" Distancia maxima entre dos números primos:     28\n");
                  printf(" Distancia media entre dos números primos:       9\n\n");
                  printf(" %s -t 1 65535\n",nprg);
                  printf(" Muestra solo un  informe estadístico de datos agregados  referidos a la\n");
                  printf(" serie de valores indicada.\n");
                  printf(" El informe incluye entradas que indican el total de valores procesados,\n");
                  printf(" el número de factores primos y números compuestos  en la serie, el fac-\n");
                  printf(" tor de descomposición inicial  más alto, la distancia máxima  entre dos\n");
                  printf(" primos, y más.\n");
                  printf(" Ejemplo:\n\n");
                  printf(" %s %s                  Informe resumido:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf(" Selección desde el número:                      1\n");
                  printf(" Al número:                                  65535\n");
                  printf(" Números totales de la serie:                65535\n");
                  printf(" Números primos totales:                      6542\n");
                  printf(" Números divisibles totales:                 58992\n");
                  printf(" Factor primo inicial más alto:                251\n");
                  printf(" Distancia maxima entre dos números primos:     72\n");
                  printf(" Distancia media entre dos números primos:      10\n\n");
                  printf(" %s -b 1000 5000 5\n",nprg);
                  printf(" Muestra datos agregados de series de valores de un  intervalo especifi-\n");
                  printf(" cado, divididos  en  sublistas contiguas  de ancho arbitrario.  También\n");
                  printf(" muestra una serie de datos estadísticos resumidos.\n");
                  printf(" '-b' es la opción que genera esta función.\n");
                  printf(" '1000 y 5000' constituyen los valores mínimo y máximo de la serie.\n");
                  printf(" '5' indica el número de subdivisiones de la serie.\n");
                  printf(" (Si no se especifica el  número de subdivisiones  en sublistas, siempre\n");
                  printf(" se considera igual a dos).\n");
                  printf(" Ejemplo (lista completa):\n\n");
                  printf(" Descomposición de la lista en 5 series.\n");
                  printf(" Del numéro 1000 al numéro 4999 inclusive.\n\n");
                  printf(" Series del  1000 al  1799 - Números primos 110 - Números divisibles 690\n");
                  printf(" Series del  1800 al  2599 - Números primos 100 - Números divisibles 700\n");
                  printf(" Series del  2600 al  3399 - Números primos 100 - Números divisibles 700\n");
                  printf(" Series del  3400 al  4199 - Números primos  96 - Números divisibles 704\n");
                  printf(" Series del  4200 al  4999 - Números primos  95 - Números divisibles 705\n\n");
                  printf("\n %s %s            Informe final resumido:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf(" Selección desde el número:                   1000\n");
                  printf(" Al número:                                   4999\n");
                  printf(" Números primos totales:                       501\n");
                  printf(" Números divisibles totales:                  3499\n");
                  printf(" Longitud de la serie numérica:               4000\n");
                  printf(" Numero de series numéricas:                     5\n");
                  printf(" Rango numérico de series:                     800\n");
                  printf(" Números primos promedio de la serie:          100\n");
                  printf(" Números divisibles promedio de la serie:      700\n");
                  printf(" Mínimo de números primos en las series:        95\n");
                  printf(" Máximo de números primos en las series:       110\n");
                  printf(" Minimo de números divisibles en las series:   690\n");
                  printf(" Máximo de números divisibles en las series:   705\n\n");
                  printf(" %s -v 2500 2999 7\n",nprg);
                  printf(" Muestra una lista selectiva de números compuestos con sus factores pri-\n");
                  printf(" mos a partir de un intervalo especificado. El factor primo indicado de-\n");
                  printf(" termina la formación de la serie mostrada.\n");
                  printf(" '-v' es la opción;\n");
                  printf(" '2500 2999' es el intervalo de la serie especificada;\n");
                  printf(" '7' es el factor primo que determina la formación de la propia lista.\n");
                  printf(" En el ejemplo reportado aquí obtenemos (lista parcial):\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  2527 = 7 (19^2)\n");
                  printf("  2569 = 7 367\n");
                  printf("  2597 = (7^2) 53\n");
                  printf("  2611 = 7 373\n");
                  printf("  2639 = 7 13 29\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -c 100001 5000 25\n",nprg);
                  printf(" Muestra una lista selectiva  de una serie  con sus factores primos, con\n");
                  printf(" un intervalo de ancho indeterminado de N elementos, un periodo y un va-\n");
                  printf(" lor inicial indicados.\n");
                  printf(" '-c' es la opción que genera esta función.\n");
                  printf(" '100001' es el valor inicial de la serie.\n");
                  printf(" '5000' es el periodo entre los valores de la serie.\n");
                  printf(" '25' es el número de elementos en la lista a mostrar.\n");
                  printf(" El ejemplo indicado genera la serie siguiente (lista parcial):\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  110001 = 3 37 991\n");
                  printf("  115001\n");
                  printf("  120001 = (7^2) 31 79\n");
                  printf("  125001 = (3^2) 17 19 43\n");
                  printf("  130001 = 71 1831\n");
                  printf("  135001 = 127 1063\n");
                  printf("  140001 = 3 23 2029\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -l 10000 75000\n",nprg);
                  printf(" Muestra una  lista limpia  solo de números primos, sin ningún otro ele-\n");
                  printf(" mento distractor al principio o al final.\n");
                  printf(" Los números primos se muestran uno por línea. Esta forma  de visualiza-\n");
                  printf(" ción es útil para producir listas largas  para ser redirigidas a archi-\n");
                  printf(" vos para su procesamiento posterior.\n");
                  printf(" Ejemplo de visualización (lista parcial):\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  74797\n");
                  printf("  74821\n");
                  printf("  74827\n");
                  printf("  74831\n");
                  printf("  74843\n");
                  printf("  74857\n");
                  printf(" ...\n");
                  printf(" ...\n");
                  printf("  74897\n");
                  printf("  74903\n");
                  printf("  74923\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -q 10000 75000\n",nprg);
                  printf(" Muestra una lista limpia  de todos los números compuestos  incluidos en\n");
                  printf(" la serie indicada con  todos sus factores  de descomposición primos, de\n");
                  printf(" manera similar a la opción '-f' pero sin elementos distractores al prin-\n");
                  printf(" cipio o al final.\n");
                  printf(" Esta forma  de visualización  es útil  para producir listas formateadas\n");
                  printf(" largas para ser redirigidas a archivos para su procesamiento posterior.\n");
                  printf(" Ejemplo de visualización (lista parcial):\n");
                  printf(" ...\n");
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
                  printf(" ...\n");
                  printf("  74995 = 5 53 283\n");
                  printf("  74996 = (2^2) 18749\n");
                  printf("  74997 = (3^2) 13 641\n");
                  printf("  74998 = 2 7 11 487\n");
                  printf(" ...\n");
                  printf(" ...\n\n");
                  printf(" %s -qL 1000001 1065535 >> ruta/nombrearchivo\n",nprg);
                  printf(" %s -lL 1000001 1065535 >> ruta/nombrearchivo\n",nprg);
                  printf(" %s -eL 1000001 1065535 >> ruta/nombrearchivo\n",nprg);
                  printf(" %s -jL 1000001 1065535 >> ruta/nombrearchivo\n",nprg);
                  printf(" Añade al  archivo indicado, o lo genera  si  no existe, respectivamente\n");
                  printf(" una lista pura de todos los valores de la serie con  todos sus factores\n");
                  printf(" primos '-q', o una lista de todos los números primos de la serie '-l'.\n\n");
                  printf(" %s -qL 98765 98770\n",nprg);
                  printf(" Muestra una lista de números compuestos y sus factores primos sin enca-\n");
                  printf(" bezado inicial ni informe estadístico final. Además se realiza una jus-\n");
                  printf(" tificación particular  que permite añadir más listas a un  solo archivo\n");
                  printf(" sin interrupciones al usar redirección.\n");
                  printf(" Ejemplo de visualización (lista completa):\n");
                  printf("       98765 = 5 19753\n");
                  printf("       98766 = 2 (3^3) 31 59\n");
                  printf("       98767 = 283 349\n");
                  printf("       98768 = (2^4) 6173\n");
                  printf("       98769 = 3 11 41 73\n");
                  printf("       98770 = 2 5 7 17 83\n\n");
                  printf(" %s -lL 987654321 987654399\n",nprg);
                  printf(" Muestra únicamente una lista de  números primos  sin encabezado inicial\n");
                  printf(" ni informe estadístico final. Además, se realiza una justificación par-\n");
                  printf(" ticular que permite  añadir más listas  a un solo archivo sin interrup-\n");
                  printf(" ciones al usar redirección.\n");
                  printf(" Ejemplo de visualización (lista completa):\n");
                  printf("   987654323\n");
                  printf("   987654337\n");
                  printf("   987654347\n");
                  printf("   987654359\n");
                  printf("   987654361\n");
                  printf("   987654377\n");
                  printf("   987654379\n");
                  printf("   987654383\n\n");
                  printf(" %s -eL 987654 987699\n",nprg);
                  printf(" Muestra únicamente una lista de  números divisibles  con solo dos divi-\n");
                  printf(" sores, opción similar a '-k' y '-e' pero con un  formato especial  ade-\n");
                  printf(" cuada para concatenar múltiples listas en un archivo.\n");
                  printf(" Ejemplo de visualización (lista completa):\n");
                  printf("      987661 = 191 5171\n");
                  printf("      987671 = 389 2539\n");
                  printf("      987673 = 433 2281\n");
                  printf("      987683 = 17 58099\n");
                  printf("      987689 = 23 42943\n");
                  printf("      987695 = 5 197539\n");
                  printf("      987699 = 3 329233\n\n");
                  printf(" %s -jL 5500000 5501500\n",nprg);
                  printf(" Muestra  únicamente  números primos gemelos, sin encabezado  inicial ni\n");
                  printf(" informe estadístico final. Además, se realiza  una justificación parti-\n");
                  printf(" cular que  permite  concatenar más listas  de primos gemelos en un solo\n");
                  printf(" archivo sin interrupciones al usar redirección.\n");
                  printf(" Ejemplo de visualización (lista completa):\n");
                  printf("  5500277 ⋄    5500279\n");
                  printf("  5500667 ⋄    5500669\n");
                  printf("  5500721 ⋄    5500723\n");
                  printf("  5501057 ⋄    5501059\n");
                  printf("  5501141 ⋄    5501143\n");
                  printf("  5501231 ⋄    5501233\n");
                  printf("  5501399 ⋄    5501401\n\n");
                  printf(" %s -pN 5000 5100\n",nprg);
                  printf(" %s -pC 670 681\n",nprg);
                  printf(" %s -lN 5000 5100\n",nprg);
                  printf(" %s -lR 5000 5100\n",nprg);
                  printf(" %s -lC 670 681\n",nprg);
                  printf(" Las opciones '-pN', '-pC', '-lN', '-lR' y '-lC' muestran, junto con los\n");
                  printf(" números primos, su posición cardinal.\n");
                  printf(" La posición cardinal de cada número primo se muestra a su derecha entre\n");
                  printf(" paréntesis.\n");
                  printf(" La opción '-pN' también muestra un  informe estadístico final, mientras\n");
                  printf(" que la opción '-lN' no muestra nada más allá de la propia lista, lo que\n");
                  printf(" la hace adecuada para obtener listas de hasta 65535 elementos en archi-\n");
                  printf(" vos.\n");
                  printf(" La opción '-lR' es similar a '-lN' pero mantiene una sangria consisten-\n");
                  printf(" te para concatenar múltiples listas en archivos mediante redirección.\n");
                  printf(" Las opciones  '-pC' y '-lC'  permiten obtener  listas de números primos\n");
                  printf(" especificando su posición cardinal.\n");
                  printf(" Ejemplo de visualización (lista completa):\n\n");
                  printf(" Serie de números primos desde la posición 670 a la posición 681\n");
                  printf(" Serie correspondiente del número 5003 al número 5099\n");
                  printf(" (Con visualización de la posición cardinal correspondiente.)\n\n");
                  printf("  5003  (670)\n");
                  printf("  5009  (671)\n");
                  printf("  5011  (672)\n");
                  printf("  5021  (673)\n");
                  printf("  5023  (674)\n");
                  printf("  5039  (675)\n");
                  printf("  5051  (676)\n");
                  printf("  5059  (677)\n");
                  printf("  5077  (678)\n");
                  printf("  5081  (679)\n");
                  printf("  5087  (680)\n");
                  printf("  5099  (681)\n\n");
                  printf("\n %s %s            Informe final resumido:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf(" Selección desde la posición cardinal:         670\n");
                  printf(" Hasta la posición cardinal:                   681\n");
                  printf(" Serie del número:                            5003\n");
                  printf(" Al número:                                   5099\n");
                  printf(" Números totales de la serie:                   97\n");
                  printf(" Números primos totales:                        12\n");
                  printf(" Distancia maxima entre dos números primos:     18\n");
                  printf(" Distancia media entre dos números primos:       9\n\n");
                  printf(" %s -fS 1000 9999 3 | less\n",nprg);
                  printf(" Utiliza una «tubería» (pipe) con el comando del sistema 'less' para ver\n");
                  printf(" una página o línea a la vez. La opción '-fS' permite resaltar el primer\n");
                  printf(" factor de descomposición indicado.\n\n");
                  printf(" El Switch 'T' puede asociarse con las opciones '-n' y '-p' para obtener\n");
                  printf(" una visualización tabular, como se muestra en los ejemplos siguientes.\n");
                  printf(" Las opciones '-nT' y '-pT'  permiten calcular series numéricas con lon-\n");
                  printf(" gitudes de hasta 262144 elementos a la vez.\n\n");
                  printf(" %s -nT 99 999\n",nprg);
                  printf(" Muestra solo la secuencia de números compuestos impares de la serie\n");
                  printf(" indicada, dispuestos en múltiples columnas.\n");
                  printf(" Ejemplo (parcial):\n");
                  printf("   99   105   111   115   117   119   121   123   125   129   133   135\n");
                  printf("  141   143   145   147   153   155   159   161   165   169   171   175\n");
                  printf("  177   183   185   187   189   195   201   203   205   207   209   213\n");
                  printf("  215   217   219   221   225   231   235   237   243   245   247   249\n");
                  printf("  253   255   259   261   265   267   273   275   279   285   287   289\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf("  845   847   849   851   855   861   865   867   869   871   873   875\n");
                  printf("  879   885   889   891   893   895   897   899   901   903   905   909\n");
                  printf("  913   915   917   921   923   925   927   931   933   935   939   943\n");
                  printf("  945   949   951   955   957   959   961   963   965   969   973   975\n");
                  printf("  979   981   985   987   989   993   995   999\n\n");
                  printf(" %s -pT 99 999\n",nprg);
                  printf(" Muestra solo la secuencia de todos los números primos de la serie indi-\n");
                  printf(" cada, dispuestos en múltiples columnas.\n");
                  printf(" Ejemplo (lista parcial):\n");
                  printf("  101   103   107   109   113   127   131   137   139   149   151   157\n");
                  printf("  163   167   173   179   181   191   193   197   199   211   223   227\n");
                  printf("  229   233   239   241   251   257   263   269   271   277   281   283\n");
                  printf("  293   307   311   313   317   331   337   347   349   353   359   367\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf(" ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...\n");
                  printf("  673   677   683   691   701   709   719   727   733   739   743   751\n");
                  printf("  757   761   769   773   787   797   809   811   821   823   827   829\n");
                  printf("  839   853   857   859   863   877   881   883   887   907   911   919\n");
                  printf("  929   937   941   947   953   967   971   977   983   991   997\n\n");
                  printf(" Los Switches funcionales 'V', 'W' y  'R', cuando se asocian  con opcio-\n");
                  printf(" nes específicas '-p' y  '-q', permiten generar todos los valores de di-\n");
                  printf(" visibilidad para cada número en la serie.\n");
                  printf(" Estos Switches  solo pueden  aplicarse  de la siguiente  manera: '-dV',\n");
                  printf(" '-dW', '-qV' y '-qR'. Aunque para algunos números los factores de divi-\n");
                  printf(" sibilidad  son equivalentes a  los factores de  descomposición, las dos\n");
                  printf(" funciones son diferentes. En esta función, se consideran  todos los di-\n");
                  printf(" visores, incluidos  los pares, no solo los  factores de  descomposición\n");
                  printf(" primos. Muchos números devuelven múltiples valores de divisibilidad que\n");
                  printf(" pueden mostrarse en varias líneas. El Switch 'W'  puede usarse en lugar\n");
                  printf(" de 'V', ya que permite variar la justificación inicial mediante un ter-\n");
                  printf(" cer argumento con valores entre 0 y 8.\n\n");
                  printf(" %s -dV 12320 12330\n",nprg);
                  printf(" %s -dW 12320 12330 0\n",nprg);
                  printf(" Muestra todos los valores de divisibilidad para cada número en la serie,\n");
                  printf(" incluso en varias líneas.\n");
                  printf(" Ejemplo de visualización (completa):\n\n");
                  printf(" Valores de divisibilidad para cada número\n");
                  printf(" en la serie indicada de 12320 a 12330\n\n");
                  printf("  12320 = 2 4 5 7 8 10 11 14 16 20 22 28 32 35 40 44 55 56 70 77 80 88 1\n");
                  printf(" 10 112 140 154 160 176 220 224 280 308 352 385 440 560 616 770 880 1120\n");
                  printf(" 1232 1540 1760 2464 3080 6160\n");
                  printf("  12321 = 3 9 37 111 333 1369 4107\n");
                  printf("  12322 = 2 61 101 122 202 6161\n");
                  printf("  12324 = 2 3 4 6 12 13 26 39 52 78 79 156 158 237 316 474 948 1027 2054\n");
                  printf(" 3081 4108 6162\n");
                  printf("  12325 = 5 17 25 29 85 145 425 493 725 2465\n");
                  printf("  12326 = 2 6163\n");
                  printf("  12327 = 3 7 21 587 1761 4109\n");
                  printf("  12328 = 2 4 8 23 46 67 92 134 184 268 536 1541 3082 6164\n");
                  printf("  12330 = 2 3 5 6 9 10 15 18 30 45 90 137 274 411 685 822 1233 1370 2055\n");
                  printf(" 2466 4110 6165\n\n");
                  printf("\n %s %s            Informe final resumido:\n",nprg,verrel);
                  printf(" -------------------------------------------------\n");
                  printf(" Serie del número:                           12320\n");
                  printf(" Al número:                                  12330\n");
                  printf(" Números totales de la serie:                   11\n");
                  printf(" Números divisibles totales:                     9\n");
                  printf(" Divisor inicial más alto:                       5\n\n");
                  printf(" Las opciones con sus Switches  '-qV' y  '-qR' son complementarias a las\n");
                  printf(" opciones '-pV' y  '-pW', ya que no muestran encabezados o pies de pági-\n");
                  printf(" na, siendo adecuadas para crear  listas concatenadas en archivos. Abajo\n");
                  printf(" se enumeran todas  las combinaciones  permitidas entre opciones, marca-\n");
                  printf(" dores y Switches, junto con el número de argumentos. En los ejemplos se\n");
                  printf(" utilizan valores de referencia realistas. Cada serie puede contener has-\n");
                  printf(" ta 65536 elementos. El valor absoluto máximo analizable es: 4294967295.\n");
                  printf(" Ejemplo de cálculo de una serie con el máximo número de elementos:\n");
                  printf(" (150000 + 65536 - 1) = 215535, o: (500000 - 65536 + 1) = 434465\n");
                  printf(" %s -f 150000 215535\n",nprg);
                  printf(" %s -f 434465 500000\n\n",nprg);
                  printf(" Lista completa de opciones con marcadores y Switches funcionales.\n");
                  printf(" %s 1234567890\n",nprg);
                  printf(" %s 1234567890 1234567890\n",nprg);
                  printf(" %s 12345 54321\n",nprg);
                  printf(" %s -t 987654321 987667890\n",nprg);
                  printf(" %s -y 1 65535\n",nprg);
                  printf(" %s -s 1 65535\n",nprg);
                  printf(" %s -f 1 65535\n",nprg);
                  printf(" %s -a 1 65535\n",nprg);
                  printf(" %s -aL 10000 75535\n",nprg);
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
                  printf(" %s -dS 10000 500000 7\n",nprg);
                  printf(" %s -dU 10000 500000 13\n",nprg);
                  printf(" %s -dD 10000 500000 3\n",nprg);
                  printf(" %s -k 135535 201070\n",nprg);
                  printf(" %s -kS 35000 100535 23\n",nprg);
                  printf(" %s -kU 35000 100535 19\n",nprg);
                  printf(" %s -kD 35000 100535 11\n",nprg);
                  printf(" %s -g 10000 75000\n",nprg);
                  printf(" %s -p 4050000 4099999\n",nprg);
                  printf(" %s -pT 450000 499999\n",nprg);
                  printf(" %s -pN 15000 25000\n",nprg);
                  printf(" %s -pC 100 4195\n",nprg);
                  printf(" %s -n 4050000 4099999\n",nprg);
                  printf(" %s -nT 450000 499999\n",nprg);
                  printf(" %s -dV 29000 29030\n",nprg);
                  printf(" %s -dW 29000 29300\n",nprg);
                  printf(" %s -qV 45000 45500\n",nprg);
                  printf(" %s -qR 34000 99535 >> ruta/archivo\n",nprg);
                  printf(" %s -l 774579999 774629999\n",nprg);
                  printf(" %s -lL 745599 796699 >> ruta/archivo\n",nprg);
                  printf(" %s -lN 50000 100000\n",nprg);
                  printf(" %s -lR 59999 119999 >> ruta/archivo\n",nprg);
                  printf(" %s -lC 1000 5095\n",nprg);
                  printf(" %s -lB 5000 9095 >> ruta/archivo\n",nprg);
                  printf(" %s -j 1999 65999\n",nprg);
                  printf(" %s -jL 500 65999 >> ruta/archivo\n",nprg);
                  printf(" %s -q 774579999 774629999\n",nprg);
                  printf(" %s -qL 7450999 7499999 >> ruta/archivo\n",nprg);
                  printf(" %s -e 255000 257999\n",nprg);
                  printf(" %s -eL 255000 257999 >> ruta/archivo\n",nprg);
                  printf(" %s -b 5050000 5099999\n",nprg);
                  printf(" %s -b 9050000 9115000 20\n",nprg);
                  printf(" %s -c 1111111 123 40 > ruta/archivo\n",nprg);
                  printf(" %s -v 9000000 9065534 7\n",nprg);
                  printf(" %s -h\n",nprg);
                  printf(" %s -?\n",nprg);
                  printf(" %s -?I\n",nprg);
                  printf(" %s -?M\n",nprg);
                  printf(" %s -?O\n",nprg);
                  printf(" %s -?M0\n",nprg);
                  printf(" %s -?M1\n",nprg);
                  printf(" %s -?F\n",nprg);
                  printf(" %s --help\n\n",nprg);
                  printf(" Notas:\n");
                  printf(" Aunque las opciones, marcadores y Switches pueden escribirse  en minús-\n");
                  printf(" culas o mayúsculas, se aconseja  escribir la opción  en minúsculas y el\n");
                  printf(" marcador en mayúsculas.\n");
                  printf(" El marcador, cuando se necesite, debe escribirse siempre  después de la\n");
                  printf(" opción: no es posible colocar un marcador antes de la opción. Solo  al-\n");
                  printf(" gunas opciones  permiten el uso de un marcador. Cada opción  debe estar\n");
                  printf(" precedida por un guion horizontal, de lo contrario se reconoce  como un\n");
                  printf(" argumento numérico, excepto en el caso de EN, IT, ES, FR, PT y  DE, que\n");
                  printf(" son opciones específicas para configurar el idioma local y, por lo tan-\n");
                  printf(" to, «deben usarse tal cual» sin guion.\n");
                  printf(" El programa cuenta con un sistema de notificación de errores de entrada\n");
                  printf(" relativamente sofisticado con propiedades explicativas que facilitan el\n");
                  printf(" aprendizaje.\n");
                  printf(" =======================================================================\n\n");
               }
               else if(lang==FRANCAIS) {
                  printf("\n ========================================\n");
                  printf(" IL N'Y PAS DE MANUEL RAPIDE EN FRANÇAIS,\n");
                  printf("   SEULEMENT EN ANGLAIS ET EN ITALIEN.\n");
                  printf(" ========================================\n\n");
                  return WARNING;
               }
               else if(lang==PORTUGUES) {
                  printf("\n =====================================\n");
                  printf(" NÁ0 HÁ UM MANUAL RÁPIDO EM PORTUGÛES,\n");
                  printf("      APENS EM INGLES E ITALIANO.\n");
                  printf(" =====================================\n\n");
                  return WARNING;
               }
               else if(lang==DEUTCHE) {
                  printf("\n =============================================\n");
                  printf(" EINE KURZANLEITUNG AUF DEUTSCH GIBT ES NUCHT,\n");
                  printf("       NUR AUF ENGLISCH UND ITALIENISCH.\n");
                  printf(" =============================================\n\n");
                  return WARNING;
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

         /* Guida rapida alle opzioni integrata, Very Good! */
            else if(subopt==RIO) {    /* Switch 'O'. */
               if(*(*(argv+1)+3)!=NUL) {

               /* Visualizza [Errore: Opzione errata!]. */
                  errscode=ERRSBASE+lang+20;
                  return(errorstype(&errscode));
               }
               else {

               /* Guida rapida. */
               /* Opzioni divise su dieci colonne per classi di funzionalità ed utilizzo. */
                  if(lang==ENGLISH)
                     printf("\n  Quick reference table of options.\n");
                  else if(lang==ITALIANO)
                     printf("\n  Tabella di riferimento rapido delle opzioni.\n");
                  else if(lang==ESPANOL)
                     printf("\n  Tabla de riferencia rápida de opciones.\n");
                  else if(lang==FRANCAIS)
                     printf("\n  Tableau de référence rapide des options.\n");
                  else if(lang==PORTUGUES)
                     printf("\n  Tabela de referência rápida de opções.\n");
                  else {
                     if(lang==DEUTCHE)
                        printf("\n  Kurzübersicht der Optionen.\n");
                  }
                  printf(" ·---------------------------------------------------------·\n");
                  printf(" | /  |  00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09   |\n");
                  printf(" |----|----------------------------------------------------|\n");
                  printf(" | 00 |  -h    -    -    - --help  -    -    -    -    -   |\n");
                  printf(" | 01 |  -?   -?O   -  -?M  -?M0   -   -?I  -?M1  -   -?F  |\n");
                  printf(" | 02 |  -a   -aL   -    -    -    -    -    -    -    -   |\n");
                  printf(" | 03 |  -y    -    -    -    -    -   -yP  -yS  -yU  -yD  |\n");
                  printf(" | 04 |  -s    -    -    -    -    -   -sP  -sS  -sU  -sD  |\n");
                  printf(" | 05 |  -f    -    -    -    -    -   -fP  -fS  -fU  -fD  |\n");
                  printf(" | 06 |  -d    -   -dV   -   -dW   -    -   -dS  -dU  -dD  |\n");
                  printf(" | 07 |  -p    -   -pN  -pC   -   -pT   -    -    -    -   |\n");
                  printf(" | 08 |  -l   -lL  -lN   -   -lR   -    -    -    -    -   |\n");
                  printf(" | 09 |   -    -    -   -lC  -lB   -    -    -    -    -   |\n");
                  printf(" | 10 |  -n    -    -    -        -nT   -    -    -    -   |\n");
                  printf(" | 11 |  -q   -qL  -qV   -   -qR   -    -    -    -    -   |\n");
                  printf(" | 12 |  -t    -    -    -    -    -    -    -    -    -   |\n");
                  printf(" | 13 |  -g    -    -    -    -    -    -    -    -    -   |\n");
                  printf(" | 14 |  -j   -jL   -    -    -    -    -    -    -    -   |\n");
                  printf(" | 15 |  -k    -    -    -    -    -    -   -kS  -kU  -kD  |\n");
                  printf(" | 16 |  -e   -eL   -    -    -    -    -    -    -    -   |\n");
                  printf(" | 17 |  -b    -    -    -    -    -    -    -    -    -   |\n");
                  printf(" | 18 |  -c    -    -    -    -    -    -    -    -    -   |\n");
                  printf(" | 19 |  -v    -    -    -    -    -    -    -    -    -   |\n");
                  printf(" ·---------------------------------------------------------·\n\n");
                  return OK;
               }
            }

         /* ------------------------------------------------------- */
            else {
            /* Se gli Switch sono diversi da: 'F', 'M', 'I' ed 'O'. */
               if(trueswitch()==SPECSW&&subopt!=NUL) {

               /* Esecuzione se lo Switch non è valido. */
               /* Visualizza [Errore: Switch errato!]. */
                  errscode=ERRSBASE+lang+40;
                  return(errorstype(&errscode));
               }
            }
         }
         else {

         /* Esecuzione se all'opzione seguono argomenti. */
            if((mark=='-'&&option=='?')&&argc!=2) {

            /* Esecuzione se lo Switch dell'opzione '-?' è errato */
               if(argc>2&&trueswitch()==ERRSW) {

               /* Visualizza [Errore: Switch errato!]. */
                  errscode=ERRSBASE+ERRSHIFT+lang+40;
                  errorstype(&errscode);
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

            /* Esecuzione se l'opzione non è valida. */
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

      /* Se l'opzione estesa è: '--HELP' oppure '--TEST'. */
         if(mark=='-'&&option=='-') {
            if(subopt==NSWT) {

            /* Esecuzione se l'opzione estesa non esiste. */
            /* Visualizza [Errore: Opzione mancante!]. */
               errscode=ERRSBASE+lang+30;
               return(errorstype(&errscode));
            }
            w=(char)tolower((int)argv[1][2]);
            x=(char)tolower((int)argv[1][3]);
            y=(char)tolower((int)argv[1][4]);
            z=(char)tolower((int)argv[1][5]);
            X=(char)tolower((int)argv[1][6]);
            chsum=(int)(w+x+y+z+X);   /* somma i codici dei caratteri digitati. */
            if(chsum==HELP) {         /* HELP=425, X=0. */
               if((w==104&&x==101&&y==108&&z==112)&&argc==2) {
                  helpfunc(&lang,nprg,relrel);
                  return OK;
               }
               else {

               /* Esecuzione se è presente uno o più argomenti. */
                  if(argc>2) {

                  /* Visualizza [Errore: Non è richiesto alcun argomento!]. */
                     errscode=ERRSBASE+lang+130;
                     return(errorstype(&errscode));
                  }
               }
            }
            else if(chsum==TEST) {         /* TEST=448, X=0. */
               if((w==116&&x==101&&y==115&&z==116)&&argc==3) {
                  num=atol(*(argv+2));
                  if(num>UL_MAX) {

                  /* Visualizza [Errore: Ordine di grandezza superato!]. */
                  /* Visualizza [Errore: Valore troppo grande!]. */
                     errscode=ERRSBASE+lang+260;
                     errorstype(&errscode);
                     errscode=ERRSBASE+lang+180;
                     return(errorstype(&errscode));
                  }
                  if(lang==ITALIANO) {
                     printf("\nTest della funzione primenum():\n");
                     printf("Il valore %lu restituisce %lu\n\n",num,primenum(num));
                     return OK;
                  }
                  else {
                     printf("Testing the primenum() function:\n");
                     printf("The value %lu returns %lu\n\n",num,primenum(num));
                     return OK;
                  }
               }
               else {

               /* Esecuzione se manca solo l'argomento numerico. */
                  if(argc<=2) {

                  /* Visualizza [Errore: Argomento mancante!]. */
                     errscode=ERRSBASE+lang+60;
                     return(errorstype(&errscode));
                  }

               /* Esecuzione se sono presenti troppi argomenti. */
                  else {

                  /* Visualizza [Errore: Troppi Argomenti!]. */
                     errscode=ERRSBASE+lang+120;
                     return(errorstype(&errscode));
                  }
               }
            }
            else {

            /* Esecuzione se l'opzione non corrisponde. */
               if(*(*(argv+1)+6)!=NUL) {

               /* Visualizza [Errore: Opzione errata!]. */
                  errscode=ERRSBASE+lang+20;
                  return(errorstype(&errscode));
               }

            /* Visualizza [Errore: Opzione errata!]. */
               errscode=ERRSBASE+lang+20;
               return(errorstype(&errscode));
            }
         }

      /* -------------------------------------------------------------*/
      /* ------------------------------------------------------------ */
      /* LBLERR_1 >> Errori su opzioni, Switch ed argomenti - INIZIO. */
      /* Segnalazione di errore, aggiuntiva a LBLERR_0. */
         if(trueoptions()==ZERO&&trueswitch()==NOSWT&&*(argv+2)==NULL) {

         /* Esecuzione se mancano l'opzione lo Switch e gli argomenti numerici. */
         /* Visualizza [Errore: Opzione, Switch ed argomenti mancanti!]. */
            errscode=ERRSBASE+lang+80;
            return(errorstype(&errscode));
         }
         if(trueoptions()==ZERO&&trueswitch()==NOSWT&&*(argv+2)!=NULL&&argc>=5) {

         /* Esecuzione se mancano solo l'opzione e lo Switch ed è presente carattere '-'. */
         /* Visualizza [Errore: Opzione e Switch mancanti!]. */
            errscode=ERRSBASE+lang+0;
            return(errorstype(&errscode));
         }
         if(argc>=2&&trueoptions()<ERRS) {
            if((trueswitch()>NOSWT&&trueswitch()<ERRSW)&&(isalpha(argv[1][3]))) {

            /* Esecuzione se è presente uno Switch ed è composto da più caratteri. */
            /* Visualizza [Errore: Switch errato!]. */
               errscode=ERRSBASE+lang+40;
               return(errorstype(&errscode));
            }
         }
         if(trueoptions()>ZERO&&trueoptions()<ERRS&&switcherrs()==ERROR&&argc>5) {

         /* Esecuzione se sono presenti sia l'opzione che uno Switch non valido - */
         /* e se sono presenti piu di tre argomenti numerici. */
         /* Visualizza [Errore: Troppi Argomenti!]. */
            errscode=ERRSBASE+ERRSHIFT+lang+120;
            errorstype(&errscode);
         }

      /* ---------------------------------------------------------- */
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

            /* Per opzioni che richiedono almeno un argomento */
            /* con esclusione di '-H', '-?' e '--'. */
               if(option!=LINF&&option!=QHLP&&option!=EHLP) {

               /* Se corrispondono alle seguenti opzioni: '-G', -T', '-B', '-V' e '-C'. */
                  if(globoptions()==GLOB1&&trueswitch()>NOSWT) {

                  /* Esecuzione se l'opzione non richiede alcun Switch. */
                  /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+240;
                     errorstype(&errscode);
                  }

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-P', '-Q', '-L', '-N', '-G', -J', '-K', '-E' e '-A'. */
                  if(trueoptions()>ZERO&&trueoptions()<STT) {
                     if(trueswitch()>=ERRSW&&globoptions()!=GLOB1) {

                     /* Esecuzione se lo Switch non è valido. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+40;
                        errorstype(&errscode);
                     }
                     else if((trueswitch()<ERRSW&&globoptions()!=GLOB1)
                      &&(option!=PRIME)) {

                     /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                     /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+50;
                        errorstype(&errscode);
                     }
                     else {

                     /* Se non corrispondono alle seguenti opzioni: */
                     /*'-G', -T', '-B', '-V', '-C', '-Y', '-S', '-F', '-D' e '-K'. */
                        if((globoptions()!=GLOB1&&globoptions()!=GLOB2)
                         ||(option==ALLDP&&subopt!=LST)) {

                        /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                        /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+50;
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
                  else {

                  /* Se corrispondono al seguente set di opzioni: */
                  /* '-Y', '-S', '-F', '-D', '-P', '-G', '-N', '-L', '-J', '-E', '-Q', '-K', - */
                  /* '-A', '-T', '-B', '-V' e '-C'. */
                     if(trueoptions()>=INFO) {

                     /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
                     /* Visualizza [Errore: Opzione e Switch errati!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+10;
                        errorstype(&errscode);
                     }
                  }
               }
            }
            else {
               if((trueswitch()<ERRSW&&(globoptions()!=GLOB1&&globoptions()!=GLOB2)
                &&(trueswitch()==TRUESW||trueswitch()==TRUEPM))) {

               /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
               /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                  errscode=ERRSBASE+ERRSHIFT+lang+50;
                  errorstype(&errscode);
               }
               if((option==PLIST&&(subopt==POS||subopt==CNT))
                ||(option==PRIME&&subopt==TBL)) {

               /* Esecuzione se l'opzione richiede altri argomenti numerici. */
               /* Visualizza [Errore: Argomenti mancanti!]. */
                  errscode=ERRSBASE+lang+70;
                  return(errorstype(&errscode));
               }
            }

         /* Esecuzione se l'opzione richiede altri argomenti numerici. */
         /* Visualizza [Errore: Argomenti mancanti!]. */
            errscode=ERRSBASE+lang+70;
            return(errorstype(&errscode));
         }

      /* -------------------------------------------------------------------- */
      /* Se è presente solo l'opzione senza nessun Switch e nessun argomento. */
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
                  if(trueoptions()>ONEY&&trueoptions()<THRE) {
                     if(option!=TINS&&option!=SYMP&&option!=FORM) {

                     /* Esecuzione se l'opzione richiede altri argomenti numerici. */
                     /* Visualizza [Errore: Argomenti mancanti!]. */
                        errscode=ERRSBASE+lang+70;
                        return(errorstype(&errscode));
                     }

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

      /* ----------------------------------------------------------------- */
      /* Per le altre opzioni non processate. */
      /* Se è presente solo l'opzione e lo Switch, senza nessun argomento. */
         if((trueoptions()!=ZERO&&trueswitch()!=NOSWT)
          &&(option!=PRIME&&(subopt!=POS&&subopt!=CNT))&&argc==2) {

         /* Esecuzione se mancano solo gli argomenti numerici. */
         /* Visualizza [Errore: Argomenti mancanti!]. */
            errscode=ERRSBASE+lang+70;
            return(errorstype(&errscode));
         }
         if(option==PRIME&&(subopt==POS||subopt==CNT)&&argc==2) {

         /* Esecuzione se manca solo l'argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* ---------------------------------------------------------------------- */
      /* Se opzione e Switch sono entrambi presenti con tre argomenti numerici. */
         if(trueoptions()!=ZERO&&trueswitch()!=NOSWT&&(argc>=5)) {

         /* Se corrisponde all'opzione '-A' con Switch non compatibile. */
            if(option==ALLDP&&(trueswitch()<SPECSW
             &&(subopt!=LST&&subopt!=TBL&&subopt!=POS&&subopt!=RNC))) {

            /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
            /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
               errscode=ERRSBASE+ERRSHIFT+lang+50;
               errorstype(&errscode);
               if(option==ALLDP&&(trueswitch()==TRUESW||trueswitch()==TRUEPM
                ||trueswitch()==CNTPRM||trueswitch()==TABCNT
                ||trueswitch()==DVSVAL||trueswitch()==DRWSPC)) {

               /* Esecuzione se lo Switch non è valido. */
               /* Visualizza [Errore: Switch errato!]. */
                  errscode=ERRSBASE+ERRSHIFT+lang+40;
                  errorstype(&errscode);
               }
               putchar('\n');
               return ERROR;
            }
            if((option==ALLDP&&subopt==LST)||(option==DIVS&&subopt==DVS)
             ||(option==NSDIV&&subopt==RNC)) {

            /* Esecuzione se sono presenti troppi argomenti. */
            /* Visualizza [Errore: Troppi Argomenti!]. */
               errscode=ERRSBASE+lang+120;
               return(errorstype(&errscode));
            }

         /* Verifica la combinazione di tutte le opzioni con i relativi Switch. */
            if(switcherrs()==ERROR) {

            /* Per opzioni che richiedono almeno un argomento, con esclusione di '-H', '-?' e '--'. */
               if(option!=LINF&&option!=QHLP&&option!=EHLP) {

               /* Se corrispondono alle seguenti opzioni: '-G', -T', '-B', '-V' e '-C'. */
                  if(globoptions()==GLOB1&&trueswitch()<ERRSW) {

                  /* Esecuzione se l'opzione non richiede alcun Switch. */
                     if(option==GEMS||option==STAT) {

                     /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+240;
                        errorstype(&errscode);

                     /* Visualizza [Errore: Troppi Argomenti!]. */
                        errscode=ERRSBASE+lang+120;
                        return(errorstype(&errscode));
                     }
                     else{
                        if(argc>5) {

                        /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+240;
                           errorstype(&errscode);

                        /* Visualizza [Errore: Troppi Argomenti!]. */
                           errscode=ERRSBASE+lang+120;
                           return(errorstype(&errscode));
                        }
                        else {

                        /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                           errscode=ERRSBASE+lang+240;
                           return(errorstype(&errscode));
                        }
                     }
                  }

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-P', '-Q', '-L', '-N', -G', '-J', '-K', '-E', e '-A'. */
                  if((trueoptions()>ZERO&&trueoptions()<STT)&&globoptions()!=GLOB1) {
                     if(trueswitch()>=ERRSW) {

                     /* Esecuzione se lo Switch non è valido. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+lang+40;
                        return(errorstype(&errscode));
                     }
                     else if(trueswitch()<ERRSW) {

                     /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                     /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+50;
                        errorstype(&errscode);

                     /* Esecuzione se lo Switch non è valido. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+lang+40;
                        return(errorstype(&errscode));
                     }
                     else {

                     /* Se lo Switch è in formato non conforme. */
                        if(trueoptions()<ERRS&&switcherrs()==ERROR) {

                        /* Esecuzione se lo Switch non è valido. */
                        /* Visualizza [Errore: Switch errato!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+40;
                           errorstype(&errscode);
                        }
                     }

                  /* Se l'opzione non esiste e lo Switch è valido. */
                     if(trueoptions()>=ERRS&&trueswitch()<ERRSW) {

                     /* Esecuzione se l'opzione non appartiene al set in presenza di Switch valido. */
                     /* Visualizza [Errore: Opzione errata!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+20;
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

            /* Se corrispondono alle seguenti opzioni: '-G', -T'. */
               if((option==GEMS||option==STAT)&&trueswitch()>=ERRSW) {

               /* Esecuzione se l'opzione non richiede alcun Switch. */
               /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                  errscode=ERRSBASE+lang+240;
                  return(errorstype(&errscode));
               }

            /* Se sono presenti opzioni che richiedono solo due argomenti. */
               if((option==PRIME&&(subopt==POS||subopt==CNT))||((globoptions()==GLOB3
                &&(option!=NSDIV||subopt!=RNC)) &&(option!=ALLDP&&option!=STAT
                &&option!=PRIME&&option!=NPRIM))) {

               /* Esecuzione se sono presenti troppi argomenti. */
               /* Visualizza [Errore: Troppi Argomenti!]. */
                  errscode=ERRSBASE+lang+120;
                  return(errorstype(&errscode));
               }

            /* Esecuzione per tutti gli altri casi di errore. */
                if(trueswitch()>ERRS)
                return(putchar('\n'));
            }
         }

      /* ------------------------------------------------------------- */
      /* Se opzione e Switch sono entrambi presenti con due argomenti. */
         if(trueoptions()!=ZERO&&trueswitch()!=NOSWT&&(argc==4)) {

         /* Verifica la combinazione di tutte le opzioni con i relativi Switch. */
            if(switcherrs()==ERROR) {

            /* Per opzioni che richiedono almeno un argomento, con esclusione di '-H', '-?' e '--'. */
               if(option!=LINF&&option!=QHLP&&option!=EHLP) {

               /* Se corrispondono alle seguenti opzioni: '-G', -T', '-B', '-V' e '-C'. */
                  if(globoptions()==GLOB1&&trueswitch()!=ERRSW) {
                     if(option==GEMS||option==STAT) {

                     /* Esecuzione se l'opzione non richiede alcun Switch. */
                     /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+240;
                        errorstype(&errscode);

                     }
                     if(option==BASE||option==VARS||option==CALC) {

                     /* Esecuzione se l'opzione non richiede alcun Switch. */
                     /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+240;
                        errorstype(&errscode);

                     /* Visualizza [Errore: Argomento mancante!]. */
                        errscode=ERRSBASE+lang+60;
                        return(errorstype(&errscode));
                     }
                  }

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-P', '-Q', '-L', '-N', '-G', -J', '-K', '-E', e '-A'. */
                  if(trueoptions()>ZERO&&trueoptions()<STT&&globoptions()!=GLOB1) {
                     if(trueswitch()>=ERRSW) {

                     /* Esecuzione se lo Switch non è valido. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+40;
                        errorstype(&errscode);
                        putchar('\n');
                        return ERROR;
                     }
                     else {

                     /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                     /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+50;
                        errorstype(&errscode);
                        if(trueswitch()<ERRSW) {

                        /* Esecuzione se lo Switch non è valido. */
                        /* Visualizza [Errore: Switch errato!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+40;
                           errorstype(&errscode);
                           putchar('\n');
                           return ERROR;
                        }
                        return(putchar('\n'));

                     /* Se lo Switch è in formato non conforme. */
                        if(trueoptions()<ERRS&&trueswitch()>=ERRSW) {

                        /* Esecuzione se lo Switch non è valido. */
                        /* Visualizza [Errore: Switch errato!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+40;
                           errorstype(&errscode);
                           putchar('\n');
                           return ERROR;
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
                  /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+50;
                     errorstype(&errscode);
                  }
                  else {

                  /* Se corrispondono alle seguenti opzioni: */
                  /* '-Y', '-S', '-F', '-D', '-P', '-G', -N, '-L', '-J', '-E', '-Q', '-K', - */
                  /* '-T', '-B', '-V' e '-C'. */
                     if(trueoptions()>=INFO) {

                     /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
                     /* Visualizza [Errore: Opzione e Switch errati!]. */
                        errscode=ERRSBASE+lang+10;
                        return(errorstype(&errscode));
                     }
                  }
               }
               if(globoptions()==GLOB2&&(option!=BASE&&option!=STAT)) {

               /* Esecuzione se manca un solo argomento numerico. */
               /* Visualizza [Errore: Argomento mancante!]. */
                  errscode=ERRSBASE+lang+60;
                  return(errorstype(&errscode));
               }
               else return(putchar('\n'));
            }
            else {

            /* Se l'opzione è '-A' e gli Switch sono 'P', 'S', 'U' o 'D'. */
               if(option==ALLDP&&(trueswitch()==TRUESW||trueswitch()==TRUEPM)) {

               /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
               /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                  errscode=ERRSBASE+ERRSHIFT+lang+50;
                  errorstype(&errscode);

               /* Esecuzione se lo Switch non è valido. */
               /* Visualizza [Errore: Switch errato!]. */
                  errscode=ERRSBASE+ERRSHIFT+lang+40;
                  errorstype(&errscode);
                  putchar('\n');
                  return ERROR;
               }

            /* Se le opzioni sono diverse da '-P', '-N', '-L', '-Q', '-J', '-E', */
            /* '-A', '-T', -B' e '-D'. */
               if((globoptions()!=GLOB3&&(option!=BASE&&option!=STAT)
                &&(subopt!=PME&&subopt!=LST&&subopt!=CNT&&subopt!=DVS))) {

               /* Esecuzione se manca un solo argomento numerico. */
               /* Visualizza [Errore: Argomento mancante!]. */
                  errscode=ERRSBASE+lang+60;
                  return(errorstype(&errscode));
               }
               else {

               /* Se una delle opzioni è presente nei due gruppi di globoptions(): */
               /* '-G', '-T', '-B', '-V', '-C'. */
                  if(globoptions()==GLOB1) {

                  /* Esecuzione se lo Switch non è previsto dall'opzione. */
                  /* Visualizza [Errore: l'opzione non accetta alcun tipo di Switch!]. */
                     errscode=ERRSBASE+lang+240;
                     return(errorstype(&errscode));
                  }
               }
            }
         }

      /* ----------------------------------------------------------------- */
      /* Se opzione e Switch sono entrambi presenti con un solo argomento. */
         if(trueoptions()!=ZERO&&trueswitch()!=NOSWT&&(argc==3)) {

         /* Verifica la combinazione di tutte le opzioni con i relativi Switch. */
            if(switcherrs()==ERROR) {

            /* Per opzioni che richiedono almeno un argomento, con esclusione di '-H', '-?' e '--'. */
               if(option!=LINF&&option!=QHLP&&option!=EHLP) {

               /* Se corrispondono alle seguenti opzioni: '-G', -T', '-B', '-V' e '-C'. */
                  if(globoptions()==GLOB1&&trueswitch()>NOSWT&&trueswitch()<ERRSW) {

                  /* Esecuzione se l'opzione non richiede alcun Switch. */
                  /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+240;
                     errorstype(&errscode);
                  }

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-P', '-Q', -L', '-N', '-G', -J', '-K', '-E', e '-A'. */
                  if(trueoptions()>ZERO&&trueoptions()<STT&&globoptions()!=GLOB1) {
                     if(trueswitch()>=ERRSW) {

                     /* Esecuzione se lo Switch non è valido. */
                     /* Visualizza [Errore: Switch errato!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+40;
                        errorstype(&errscode);
                     }
                     else {
                        if(globoptions()!=GLOB1) {

                        /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
                        /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                           errscode=ERRSBASE+ERRSHIFT+lang+50;
                           errorstype(&errscode);
                        }

                     /* Se lo Switch è in formato non conforme. */
                        if(trueoptions()<ERRS&&trueswitch()>=ERRSW) {

                        /* Esecuzione se lo Switch non è valido. */
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
                  else {
                     if(trueoptions()<ERRS&&trueswitch()>=ERRSW) {

                     /* Esecuzione se l'opzione non richiede alcun Switch. */
                     /* Visualizza [Errore: L'opzione non accetta alcun tipo di Switch!]. */
                        errscode=ERRSBASE+ERRSHIFT+lang+240;
                        errorstype(&errscode);
                     }
                  }

               /* Se corrispondono alle seguenti opzioni: */
               /* '-Y', '-S', '-F', '-D', '-P', '-G', -N, '-L', '-J', '-E', '-Q', '-K', */
               /* '-T', '-B', '-V' e '-C'. */
                  if(trueoptions()>=INFO&&trueswitch()>=ERRSW) {

                  /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
                  /* Visualizza [Errore: Opzione e Switch errati!]. */
                     errscode=ERRSBASE+ERRSHIFT+lang+10;
                     errorstype(&errscode);
                  }
               }
               if(trueswitch()>NOSWT&&trueswitch()<ERRSW
                &&(globoptions()==GLOB1||globoptions()==GLOB2)
                &&(option!=GEMS&&option!=STAT&&option!=BASE)) {

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

            /* Se l'opzione è '-A' e gli Switch sono 'P', 'S', 'U' o 'D' */
               if(option==ALLDP&&(trueswitch()==TRUESW||trueswitch()==TRUEPM)) {

               /* Esecuzione se l'opzione e lo Switch sono incompatibili. */
               /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
                  errscode=ERRSBASE+ERRSHIFT+lang+50;
                  errorstype(&errscode);
               }

            /* Se corrispondono alle seguenti opzioni: */
            /* '-Y', '-S', '-F', '-T', '-D', '-L', '-K', '-G', '-B', '-C' e '-V'. */
               if(((option!=BASE&&globoptions()!=GLOB3)&&(subopt!=PME&&subopt!=LST))
                &&((option==DIVS&&subopt!=DVS)||(option==NSDIV&&subopt!=RNC))) {

               /* Esecuzione se mancano due o più argomenti numerici. */
               /* Visualizza [Errore: Argomenti mancanti!]. */
                  errscode=ERRSBASE+lang+70;
                  return(errorstype(&errscode));
               }
               else {

               /* Se le opzioni sono '-A', '-P', con relativi Switch */
                  if(globopts()==GLOB0||(option==ALLDP)||(option==PRIME&&subopt==TBL)
                   ||(option==NPRIM&&subopt==TBL)||(option==PRIME
                   &&(subopt!=POS&&subopt!=CNT))) {

                  /* Esecuzione se manca un solo argomento numerico. */
                  /* Visualizza [Errore: Argomento mancante!]. */
                     errscode=ERRSBASE+lang+60;
                     return(errorstype(&errscode));
                  }
               }
            }
         }

      /* ------------------------------------------------------------------------------------- */
      /* Se sono presenti solo l'opzione '-C' o l'opzione '-V' senza Switch con due argomenti. */
         if((trueoptions()==CLC||trueoptions()==VRS)&&trueswitch()==NOSWT&&argc==4) {

         /* Esecuzione se manca un solo argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* ----------------------------------------------------------------------------------- */
      /* Se è presente l'opzione '-C' o l'opzione '-V' senza Switch e con un solo argomento. */
         if((trueoptions()==CLC||trueoptions()==VRS)&&trueswitch()==NOSWT&&(argc==3)) {

         /* Esecuzione se mancano due o più argomenti numerici. */
         /* Visualizza [Errore: Argomenti mancanti!]. */
            errscode=ERRSBASE+lang+70;
            return(errorstype(&errscode));
         }

      /* ------------------------------------------------------------------------------------- */
      /* Se è presente l'opzione '-A' senza Switch e con un solo argomento. */
         if(option==ALLDP&&trueswitch()==NOSWT&&argc==3) {

         /* Esecuzione se manca un argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* ------------------------------------------------------------------------------------- */
      /* Se è presente l'opzione '-D', '-Q', '-K' o '-E' senza Switch e con un solo argomento. */
         if(trueoptions()==ONEY&&trueswitch()==NOSWT&&(argc==3)) {

         /* Esecuzione se manca un argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* ----------------------------------------------------------------------------------- */
      /* Se è presente l'opzione '-P' o l'opzione '-L' senza Switch e con un solo argomento. */
         if(trueoptions()==THRE&&trueswitch()==NOSWT&&(argc==3)) {

         /* Esecuzione se manca un argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* ---------------------------------------------------------------------------------- */
      /* Se è presente l'opzione '-N' o l'opzione 'T' senza Switch e con un solo argomento. */
         if((trueoptions()==NPM||trueoptions()==STT)&&trueswitch()==NOSWT&&(argc==3)) {

         /* Esecuzione se manca un argomento numerico. */
         /* Visualizza [Errore: Argomento mancante!]. */
            errscode=ERRSBASE+lang+60;
            return(errorstype(&errscode));
         }

      /* ------------------------------------------------------------------------ */
      /* Esecuzione se le condizioni si sono verificate, valido per tutte le - */
      /* combinazioni di opzioni, Switch con numero di argomenti inferiore a tre. */
         if(trueoptions()>=ERRS&&trueswitch()>=ERRSW) {

         /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
         /* Visualizza [Errore: Opzione e Switch errati!]. */
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

         /* Esecuzione se lo Switch non è valido. */
         /* Visualizza [Errore: Switch errato!]. */
            errscode=ERRSBASE+lang+40;
            return(errorstype(&errscode));
         }
         if(switcherrs()>=ERROR&&trueoptions()!=TWOS) {

         /* Esecuzione se lo Switch è usato con un opzione errata. */
         /* Visualizza [Errore: Combinazione dell'opzione con Switch non valida!]. */
            errscode=ERRSBASE+lang+50;
            return(errorstype(&errscode));
         }
         if(switcherrs()<ERROR&&trueoptions()<QHLP&&argc==2) {

         /* Esecuzione se mancano due o più argomenti numerici. */
         /* Visualizza [Errore: Argomenti mancanti!]. */
            errscode=ERRSBASE+lang+70;
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
               if((option==PRIME||option==PLIST)
                &&(subopt==CNT||subopt==TCN)&&(a>=9||(atol(*(argv+2))>CT_MAX))) {

               /* Visualizza [Errore: Ordine di grandezza superato!]. */
               /* Visualizza [Errore: Valore troppo grande!]. */
                  errscode=ERRSBASE+lang+260;
                  errorstype(&errscode);
                  errscode=ERRSBASE+lang+180;
                  return(errorstype(&errscode));
               }
               else {
                  if(a>=10) {

                  /* Visualizza [Errore: Ordine di grandezza superato!]. */
                  /* Visualizza [Errore: Valore troppo grande!]. */
                     errscode=ERRSBASE+lang+260;
                     errorstype(&errscode);
                     errscode=ERRSBASE+lang+180;
                     return(errorstype(&errscode));
                  }
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
               if((option==PRIME||option==PLIST)
                &&(subopt==CNT||subopt==TCN)&&(a>=9||(atol(*(argv+2)))>CT_MAX)) {

               /* impostazione flag (1) per visualizzazione errore. */
                  flgers+=1;
               }
               else {

               /* impostazione flag (2) per visualizzazione errore. */
                  if(a>=10) flgers+=1;
               }
            }

         /* E' il secondo argomento numerico sempre preceduto da un'opzione. */
            if(argc==4&&isdigit(**(argv+3))) {
               for(b=0;b<=10;b++) {
                  if(isdigit(*(*(argv+3)+b))) {
                     if(*(*(argv+3)+(b+1))==NUL)
                        break;
                  }
               }
               if((option==PRIME||option==PLIST)
                &&(subopt==CNT||subopt==TCN)&&(a>=9||(atol(*(argv+3)))>CT_MAX)) {

               /* impostazione flag (3) per visualizzazione errore. */
                  flgers+=1;
               }
               else {

               /* impostazione flag (4) per visualizzazione errore. */
                  if(b>=10) flgers+=1;
               }
            }

         /* Visualizza il messaggio di errore in base allo stato del flag 'flgers'. */
         /* Se flgers = 0; nessun errore. Non visualizza nulla. */
         /* Se flgers = 1; Visualizza: [Errore: Valore troppo grande!]. */
         /* Se flgers = 2; Visualizza: [Errore: Valori troppo grandi!]. */
            if(flgers==1) {

            /* Visualizza [Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valore troppo grande!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+180;
               return(errorstype(&errscode));
            }
            if(flgers==2) {

            /* Visualizza [Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valori troppo grandi!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+210;
               return(errorstype(&errscode));
            }

         /* Controlla la presenza di Switch errati o spuri nell'opzione. */
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
            if(!(isdigit(**(argv+2)))) {

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
            if(!(isdigit(**(argv+3)))) {

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

         /* ------------------------------------------ */
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

         /* E' il secondo argomento numerico sempre preceduto da un'opzione. */
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

         /* Visualizza il messaggio di errore in base allo stato del flag 'flgers'. */
         /* Se flgers = 0; nessun errore. Non visualizza nulla. */
         /* Se flgers = 1; Visualizza: [Errore: Valore troppo grande!]. */
         /* Se flgers = 2; Visualizza: [Errore: Valori troppo grandi!]. */
         /* Se flgers = 3; Visualizza: [Errore: Valori troppo grandi!]. */
            if(flgers==1) {

            /* Visualizza [Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valore troppo grande!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+180;
               return(errorstype(&errscode));
            }
            if(flgers>=2) {

            /* Visualizza [Errore: Ordine di grandezza superato!]. */
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

         /* ------------------------------------------ */
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
   /* ------------------------------------- */

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

               /* Visualizza [Errore: Ordine di grandezza superato!]. */
               /* Visualizza [Errore: Valore troppo grande!]. */
                  errscode=ERRSBASE+lang+260;
                  errorstype(&errscode);
                  errscode=ERRSBASE+lang+180;
                  return(errorstype(&errscode));
               }
            }

         /* Validazione dei valori per l'unico argomento numerico (NO OPZIONE). */
         /* Discriminazione delle opzioni per il cambio della lingua (1). */
            if(!isdigit(**(argv+1))&&**(argv+1)!='-'&&**(argv+1)!='I'&&**(argv+1)!='E'
             &&**(argv+1)!='F'&&**(argv+1)!='P'&&**(argv+1)!='D') {

            /* Esecuzione se l'opzione e lo Switch non appartengono al set. */
            /* Visualizza [Errore: Opzione e Switch errati!]. */
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
               if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='N'&&*(*(argv+1)+2)==NUL) {
                  if(noten) {
                     fmesg=MSGBASE+ENGLISH+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='I'&&*(*(argv+1)+1)=='T'&&*(*(argv+1)+2)==NUL) {
                  if(notit) {
                     fmesg=MSGBASE+ITALIANO+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='S'&&*(*(argv+1)+2)==NUL) {
                  if(notes) {
                     fmesg=MSGBASE+ESPANOL+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='F'&&*(*(argv+1)+1)=='R'&&*(*(argv+1)+2)==NUL) {
                  if(notfr) {
                     fmesg=MSGBASE+FRANCAIS+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='P'&&*(*(argv+1)+1)=='T'&&*(*(argv+1)+2)==NUL) {
                  if(notpt) {
                     fmesg=MSGBASE+PORTUGUES+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else {
                  if(*(*(argv+1))=='D'&&*(*(argv+1)+1)=='E'&&*(*(argv+1)+2)==NUL) {
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

            /* Visualizza [Errore: Ordine di grandezza superato!]. */
            /* Visualizza [Errore: Valore troppo grande!]. */
               errscode=ERRSBASE+lang+260;
               errorstype(&errscode);
               errscode=ERRSBASE+lang+180;
               return(errorstype(&errscode));
            }
            if(flgers==2) {

            /* Visualizza [Errore: Ordine di grandezza superato!]. */
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
               if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='N'&&*(*(argv+1)+2)==NUL) {
                  if(noten) {
                     fmesg=MSGBASE+ENGLISH+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='I'&&*(*(argv+1)+1)=='T'&&*(*(argv+1)+2)==NUL) {
                  if(notit) {
                     fmesg=MSGBASE+ITALIANO+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='S'&&*(*(argv+1)+2)==NUL) {
                  if(notes) {
                     fmesg=MSGBASE+ESPANOL+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='F'&&*(*(argv+1)+1)=='R'&&*(*(argv+1)+2)==NUL) {
                  if(notfr) {
                     fmesg=MSGBASE+FRANCAIS+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else if(*(*(argv+1))=='P'&&*(*(argv+1)+1)=='T'&&*(*(argv+1)+2)==NUL) {
                  if(notpt) {
                     fmesg=MSGBASE+PORTUGUES+50;
                     filemsg(&fmesg,&self);
                  }
               }
               else {
                  if(*(*(argv+1))=='D'&&*(*(argv+1)+1)=='E'&&*(*(argv+1)+2)==NUL) {
                     if(notde) {
                        fmesg=MSGBASE+DEUTCHE+50;
                        filemsg(&fmesg,&self);
                     }
                  }
               }
            }
         }
         else {

         /* ------------------------------------------ */
         /* Se esistono troppi argomenti numerici (3). */
            if(argc>3) {
               errscode=ERRSBASE+lang+120;
               return(errorstype(&errscode));
            }
         }
      }
   /* Fine controlli argomenti senza opzione. */
   /* --------------------------------------- */

   }

/* ------------------------------------------------------------------------- */
/* Visualizzazione rapida di presentazione ed uso delle opzioni informative. */
   if(argc==1) {
      about(&lang,nprg,verrel);
      return OK;
   }

/* -------------------------------------------------------------------------------- */
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

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
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
      else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='N'&&*(*(argv+1)+2)==NUL) {
         lang=ENGLISH;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua italiana. */
      else if(*(*(argv+1))=='I'&&*(*(argv+1)+1)=='T'&&*(*(argv+1)+2)==NUL) {
         lang=ITALIANO;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua spagnola. */
      else if(*(*(argv+1))=='E'&&*(*(argv+1)+1)=='S'&&*(*(argv+1)+2)==NUL) {
         lang=ESPANOL;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua francese. */
      else if(*(*(argv+1))=='F'&&*(*(argv+1)+1)=='R'&&*(*(argv+1)+2)==NUL) {
         lang=FRANCAIS;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua portoghese. */
      else if(*(*(argv+1))=='P'&&*(*(argv+1)+1)=='T'&&*(*(argv+1)+2)==NUL) {
         lang=PORTUGUES;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }

   /* Impostazione della lingua tedesca. */
      else if(*(*(argv+1))=='D'&&*(*(argv+1)+1)=='E'&&*(*(argv+1)+2)==NUL) {
         lang=DEUTCHE;
         if(!cfglang(&lang))
            return OK;
         else
            return ERROR;
      }
      else if((*(*(argv+1))!='E'&&*(*(argv+1)+1)!='N')||(*(*(argv+1))!='I'&&*(*(argv+1)+1)!='T')
       ||(*(*(argv+1))!='E'&&*(*(argv+1)+1)!='S')||(*(*(argv+1))!='F'&&*(*(argv+1)+1)!='R')
       ||(*(*(argv+1))!='P'&&*(*(argv+1)+1)!='T')||(*(*(argv+1))!='D'&&*(*(argv+1)+1)!='E')) {

      /* Esecuzione se l'opzione e/o gli argomenti non sono conformi. */
      /* Visualizza [Errore: Opzione e/o argomenti errati!]. */
         errscode=ERRSBASE+lang+110;
         return(errorstype(&errscode));
      }
      else {
      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign) {
            printf("ERROR [ASK-LANG] GURU MEDITATION\n\n");
            return GURU;
         }
      }
   }

/* ------------------------------------------------------------------------------- */
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

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
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
         /* '-S', '-F', '-Y', '-D', '-P', '-G', '-Q', '-L', '-J', -N'. */
            if(globoptions()==GLOB2||(trueoptions()==THRE||option==NSDIV
             ||option==NPRIM||option==PLIST)) {

            /* Conversione parametro. */
               if(option==PRIME&&subopt==CNT)
                  cntbas=(cntlim=(unsigned long)atol(*(argv+2)));
               else num=(limit=(unsigned long)atol(*(argv+2)));

            /* Controllo parametro. */
               if(num>=UL_MAX||limit>=UL_MAX) {

               /* Visualizza [Errore: Ordine di grandezza superato!]. */
               /* Visualizza [Errore: Valore troppo grande!]. */
               /* I due valori sono sempre uguali! */
                  errscode=ERRSBASE+lang+260;
                  errorstype(&errscode);
                  errscode=ERRSBASE+lang+180;
                  return(errorstype(&errscode));
               }

            /* Se l'opzione è '-N' setta il Flag che discrimina i numeri primi. */
               if(option==NPRIM)
                  flprt=1,putchar('\n');
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

/* ------------------------------------------------------------------------------ */
/* Controllo e conversione parametri se sono presenti un'opzione e due argomenti. */
   else if(argc==4) {

   /* Validazione opzioni e controllo parametri. */
      if(trueoptions()<ERRS&&isdigit(**(argv+2))&&isdigit(**(argv+3))) {

         if(subopt==CNT||subopt==TCN) {

         /* Conversione parametri. */
            cntbas=(unsigned long)atol(*(argv+2));
            cntlim=(unsigned long)atol(*(argv+3));

         /* Controllo parametri. */
            if(num>=CT_MAX||cntlim>CT_MAX) fler=1;
            if(num>=CT_MAX&&cntlim>CT_MAX) fler=2;
         }
         else {

         /* Conversione parametri. */
            num=(unsigned long)atol(*(argv+2));
            limit=(unsigned long)atol(*(argv+3));

         /* Controllo parametri. */
            if(num>=UL_MAX||limit>=UL_MAX) fler=1;
            if(num>=UL_MAX&&limit>=UL_MAX) fler=2;
         }

         /* Controlla la consistenza dei valori */
         if(fler==1) {

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valori troppo grandi!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+210;
            return(errorstype(&errscode));
         }
         if(option==PJUMS||option==GEMS||option==STAT) {
            if(num==limit) {

            /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
               errscode=ERRSBASE+lang+200;
               return(errorstype(&errscode));
            }
         }
         if(option==PLIST&&(subopt==CNT||subopt==TCN||subopt==POS||subopt==RNC)) {
            if((num==limit)&&(cntbas==cntlim)) {

            /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
               errscode=ERRSBASE+lang+200;
               return(errorstype(&errscode));
            }
         }
         if(option==GEMS&&(num>2&&num==limit-1)) {

         /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
            errscode=ERRSBASE+lang+200;
            return(errorstype(&errscode));
         }

         if(option==GEMS&&(num<0||limit<3)) {

         /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
            errscode=ERRSBASE+lang+200;
            return(errorstype(&errscode));
         }
         if((option==NPRIM)&&(num<0||limit<4)) {

        /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
            errscode=ERRSBASE+lang+200;
            return(errorstype(&errscode));
         }

      /* Correzione della serie numerica risultante, - */
      /* immessa con due argomenti, per l'opzione '-B'. */
         if(option==BASE) {
            if(num>limit) {

            /* Visualizza [Errore: Valori degli argomenti invertiti!]. */
               errscode=ERRSBASE+lang+150;
               return(errorstype(&errscode));
            }
            else {
               if(num==limit) {

               /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
                  errscode=ERRSBASE+lang+200;
                  return(errorstype(&errscode));
               }
               if((limit-num)<=3) {

               /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
                  errscode=ERRSBASE+lang+200;
                  return(errorstype(&errscode));
               }
            }

         /* Correzione della serie numerica risultante. */
            nseg=2;
            if(nseg>1) --limit;
            if(num<=2) num=2;
            if((((limit-num)+1)%nseg))
               num+=1;
            if((((limit-num)+1)%nseg))
               num-=2;
            if((((limit-num)+1)%nseg))
               num+=1;
         }

      /* Visualizza o stampa la serie di numeri primi su più colonne. */
      /* Se l'opzione è '-P' seguita dallo Switch 'T'. */
         if(option==PRIME&&subopt==TBL) {
            if(limit<num) {

            /* Visualizza [Errore: Valori degli argomenti invertiti!]. */
               errscode=ERRSBASE+lang+150;
               return(errorstype(&errscode));
            }
            if((limit-num+1)>RGTAB) {

               /* Visualizza [Errore: Intervallo dei valori immessi troppo grande!]. */
               errscode=ERRSBASE+lang+160;
               return(errorstype(&errscode));
            }

         /* Impostazione Flag per visualizzare serie di numeri primi. */
            fldp=0U;

         /* Visualizza per l'opzione '-pT'. */
            if(lang==ENGLISH)
               printf("\nPrime numbers from %lu to %lu\n",num,limit);
            else if(lang==ITALIANO)
               printf("\nNumeri primi da %lu a %lu\n",num,limit);
            else if(lang==ESPANOL)
               printf("\nNúmeros primos de %lu a %lu\n",num,limit);
            else if(lang==FRANCAIS)
               printf("\nNombres premiers de %lu à %lu\n",num,limit);
            else if(lang==PORTUGUES)
               printf("\nNúmeros primos de %lu a %lu\n",num,limit);
            else if(lang==DEUTCHE)
               printf("\nPrimzahlen von %lu bis %lu\n",num,limit);
            else {
               printf("ERROR: [LANG-TABS_1] GURU MEDITATION\n\n");
               return GURU;
            }

         /* Chiamata della funzione di visualizzazione a tabella. */
            if(tpcol(num,limit,&lang)==ERROR) {

            /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
               errscode=ERRSBASE+lang+200;
               return(errorstype(&errscode));
            }
            else return OK;
         }

      /* Visualizza o stampa una serie di numeri primi sulla base della loro posizione cardinale. */
      /* Se le opzioni '-P' ed '-L' sono seguite dallo Switch 'C'. */
         if((option==PRIME||option==PLIST)&&(subopt==CNT||subopt==TCN)) {
            if(cntlim<cntbas) {

            /* Visualizza [Errore: Valori degli argomenti invertiti!]. */
               errscode=ERRSBASE+lang+150;
               return(errorstype(&errscode));
            }
            if((cntlim-cntbas+1)>RGCNT) {

               /* Visualizza [Errore: Intervallo dei valori immessi troppo grande!]. */
               errscode=ERRSBASE+lang+160;
               return(errorstype(&errscode));
            }
         }

       /* Se l'opzione è '-N' azzera il Flag e visualizza l'intestazione. */
         if(option==NPRIM&&subopt==NOSWT&&(limit-num)<=65535) {

         /* Azzera il Flag per inibire la stampa dei numeri primi. */
            flprt=0;

         /* Visualizza per l'opzione '-N' senza Switch associato. */
            if(lang==ENGLISH) {
               printf("\nList of odd divisible numbers from %lu to %lu\n",num,limit);
               printf("(Asterisks indicates the position of a prime number.)\n\n");
            }
            else if(lang==ITALIANO) {
               printf("\nLista di numeri dispari divisibili da %lu a %lu\n",num,limit);
               printf("(Gli asterischi indicano la posizione di un numero primo.)\n\n");
            }
            else if(lang==ESPANOL) {
               printf("\nLista de números impares divisibles de %lu a %lu\n",num,limit);
               printf("(Los asteriscos indican la posición de un número primo.)\n\n");
            }
            else if(lang==FRANCAIS) {
               printf("\nListe des nombres impairs divisibles de %lu à %lu\n",num,limit);
               printf("(Les astérisques indiquent la position d'un nombre premier.)\n\n");
            }
            else if(lang==PORTUGUES) {
               printf("\nLista de números impares divisíveis de %lu a %lu\n",num,limit);
               printf("(Os asteriscos indicam a posição de um número primo.)\n\n");
            }
            else if(lang==DEUTCHE) {
               printf("\nListe der ungeraden teilbaren Zalhlen von %lu bis %lu\n",num,limit);
               printf("(Sternchen kennzeichnen die Position einer Primzahl.)\n\n");
            }
            else {
               printf("ERROR: [NOT-LANG_N] GURU MEDITATION\n\n");
               return GURU;
            }
         }

      /* Visualizza o stampa la serie di numeri divisibili su più colonne. */
      /* Se l'opzione è '-N' seguita dallo Switch 'T'. */
         if(option==NPRIM&&subopt==TBL) {

            if(limit<num) {

            /* Visualizza [Errore: Valori degli argomenti invertiti!]. */
               errscode=ERRSBASE+lang+150;
               return(errorstype(&errscode));
            }
            if((limit-num+1)>RGTAB) {

               /* Visualizza [Errore: Intervallo dei valori immessi troppo grande!]. */
               errscode=ERRSBASE+lang+160;
               return(errorstype(&errscode));
            }

         /* Impostazione Flag per visualizzare serie di numeri divisibili. */
            fldp=1U;

         /* Visualizza per l'opzione '-nT'. */
            if(lang==ENGLISH)
               printf("\nOdd divisible numbers from %lu to %lu\n",num,limit);
            else if(lang==ITALIANO)
               printf("\nNumeri divisibili dispari da %lu a %lu\n",num,limit);
            else if(lang==ESPANOL)
               printf("\nNúmeros impares divisibles de %lu a %lu\n",num,limit);
            else if(lang==FRANCAIS)
               printf("\nNombres impairs divisibles de %lu à %lu\n",num,limit);
            else if(lang==PORTUGUES)
               printf("\nNúmeros ímpares divisíveis de %lu a %lu\n",num,limit);
            else if(lang==DEUTCHE)
               printf("\nUngerade teilbare Zahlen von %lu bis %lu\n",num,limit);
            else {
               printf("ERROR: [NOT-LANG_T] GURU MEDITATION\n\n");
               return GURU;
            }

         /* Chiamata della funzione di visualizzazione a tabella. */
            if(tpcol(num,limit,&lang)==ERROR) {

            /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
               errscode=ERRSBASE+lang+200;
               return(errorstype(&errscode));
            }
            else return OK;
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

/* -------------------------------------------------------------------- */
/* Controllo e conversione se sono presenti un'opzione e tre argomenti. */
   else if(argc==5) {

   /* Validazione opzioni e parametri per l'opzione '-C'. */
      if(trueoptions()==CLC&&isdigit(**(argv+2))
       &&isdigit(**(argv+3))&&isdigit(**(argv+4))) {

      /* Conversione parametri per l'opzione '-C'. */
         num=(unsigned long)atol(*(argv+2));
         com=(unsigned long)atol(*(argv+3));
         tmp=(unsigned short)atoi(*(argv+4));
         limit=((tmp*com)+num)-1;
         if(!tmp)
            tflg=1,tmp=1;   /* Discrimina per zero elementi. */

      /* Controllo parametri. */
         if(num>=UL_MAX||com>=UL_MAX||tmp>=RANGE) fler=1;
         if((num>=UL_MAX&&com>=UL_MAX)||tmp>=RANGE) fler=2;
         if(num>=UL_MAX&&com>=UL_MAX&&tmp>=RANGE) fler=3;
         if(fler==1) {

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valori troppo grandi!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+210;
            return(errorstype(&errscode));
         }
         if(num>limit&&tmp>1) {

         /* Visualizza [Errore: Argomenti errati! Valori fuori limite!]. */
            errscode=ERRSBASE+lang+140;
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

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valori troppo grandi!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+210;
            return(errorstype(&errscode));
         }
         if(num>limit) {

         /* Visualizza [Errore: Valori degli argomenti invertiti!]. */
            errscode=ERRSBASE+lang+150;
            return(errorstype(&errscode));
         }
         else {
            if(num==limit) {

            /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
               errscode=ERRSBASE+lang+200;
               return(errorstype(&errscode));
            }
            if((limit-num)<=3||nseg<2) {
               if(nseg<2) {

               /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
                  errscode=ERRSBASE+lang+200;
                  return(errorstype(&errscode));
               }

            /* Visualizza [Errore: Serie numerica non valida!]. */
               errscode=ERRSBASE+lang+220;
               return(errorstype(&errscode));
            }
         }

      /* Correzione della serie numerica risultante, - */
      /* immessa con tre argomenti, per l'opzione '-B'. */
         if(nseg>1) {
            --limit;
            if(num<=2) num=2;
            if((((limit-num)+1)%nseg))
               num+=1;
            if((((limit-num)+1)%nseg))
               num-=2;
            if((((limit-num)+1)%nseg))
               num+=1;
         }
      }

   /* Validazione opzioni e parametri per le opzioni '-Y', '-S', '-F', '-D', '-K', -V'. */
      else if(((trueoptions()<=TWOS&&subopt!=NSWT)||trueoptions()==VRS)
       &&isdigit(**(argv+2))&&isdigit(**(argv+3))&&isdigit(**(argv+4))) {

      /* Conversione parametri per le opzioni '-Y', '-S', '-F', '-D', '-K', -V'. */
         num=(unsigned long)atol(*(argv+2));
         limit=(unsigned long)atol(*(argv+3));
         if(subopt!=DRW)
            select=(unsigned long)atol(*(argv+4));
         else {
            column=(unsigned short)atol(*(argv+4));
            if(column<1) column=0;
            if(column>8) column=8;
          }

      /* Controllo parametri. */
         if(num>=UL_MAX||limit>=UL_MAX||select>UL_MAX) fler=1;
         if((num>=UL_MAX&&limit>=UL_MAX)||select>UL_MAX) fler=2;
         if(num>=UL_MAX&&limit>=UL_MAX&&select>UL_MAX) fler=3;
         if(fler==1) {

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
         /* Visualizza [Errore: Valore troppo grande!]. */
            errscode=ERRSBASE+lang+260;
            errorstype(&errscode);
            errscode=ERRSBASE+lang+180;
            return(errorstype(&errscode));
         }
         if(fler>=2) {

         /* Visualizza [Errore: Ordine di grandezza superato!]. */
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
      if(argc>5) {

      /* ----------------------------------------------------- */
      /* Esecuzione se esistono troppi argomenti numerici (2). */
      /* Visualizza [Errore: Troppi argomenti!]. */
         errscode=ERRSBASE+lang+120;
         return(errorstype(&errscode));
      }
   }

/* ------------------------------------------ */
/* Controllo dei parametri sui valori limite. */
   if(num>=UL_MAX||num<0||limit>=UL_MAX) {

   /* Visualizza [Errore: Argomenti errati! Valori fuori limite.]. */
      errscode=ERRSBASE+lang+140;
      return(errorstype(&errscode));
   }

/* -------------------------------------- */
/* Tutte le opzioni ad eccezione di '-C'. */
   if(trueoptions()<=STT||option==BASE||option==VARS) {
      range=(limit-num)+1;

   /* Solo per l'opzione '-B'. */
      if(option==BASE) {
         if((num<2||limit<2)&&nseg<2) {

            /* Visualizza [Errore: Argomenti errati! Valori fuori limite.]. */
            errscode=ERRSBASE+lang+140;
            return(errorstype(&errscode));
         }
         if((num>limit||limit<3)&&nseg>1) {

         /* Visualizza [Errore: Argomenti errati! Valori fuori limite.]. */
            errscode=ERRSBASE+lang+140;
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

      /* Visualizza [Errore: Intervallo dei valori immessi troppo grande!]. */
         errscode=ERRSBASE+lang+160;
         return(errorstype(&errscode));
      }
   }

/* ------------------------------------------------------ */
   if(nseg>PEL||!nseg) {

   /* Visualizza [Errore: Serie numerica troppo grande!]. */
      errscode=ERRSBASE+lang+170;
      return(errorstype(&errscode));
   }

/* --------------------------------------------------------------------------- */
   if(select>(UL_MAX-1)||!select) {

   /* Visualizza [Errore: Valore selezionato troppo grande o troppo piccolo!]. */
      errscode=ERRSBASE+lang+190;
      return(errorstype(&errscode));
   }

/* ------------------------------------------------------------------- */
/* Controlla la coerenza e consistenza globale dei parametri inseriti. */
   if(option==BASE) {

   /* Controlla la coerenza di 'range' e 'nseg' sull'opzione '-B'. */
      if(!(primenum(range))) {

      /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
         errscode=ERRSBASE+ERRSHIFT*lang+200;
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

/* ------------------------------------------------------------------ */
   if(option==VARS) {

   /* Controlla se range è diverso da uno. */
   /* Con range = 1 i valori sono uguali. */
      if(range<=1) {

      /* Visualizza [Errore: Intervallo dei valori immessi non valido!]. */
         errscode=ERRSBASE+lang+200;
         return(errorstype(&errscode));
      }

   /* Controlla la coerenza tra 'select' e 'range' sull'opzione '-V'. */
      if(select>range) {
         if((primenum(select)))
            putchar('\n');

      /* Visualizza [Errore: Valore selezionato fuori limite!]. */
         errscode=ERRSBASE+lang+230;
         return(errorstype(&errscode));
      }
   }

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* Opzioni di visualizzazione e stampa sui prospetti di testa e coda.         */
/* Stampa della lista di numeri primi, divisibili e fattori di scomposizione. */

/* Back-up parametri. */
   number=num,limt=limit;

/* Se i parametri sono uguali imposta il flag. */
/* Considera equivalente ad un solo parametro. */
   if(option!=CALC) {
      if(num==limit)
         eflag=HFLAG;
   }
   else {
      if(tmp<=1)
         eflag=HFLAG;
      if(number>=limt)
         eflag=HFLAG;
   }

   /* Stampa una riga vuota iniziale. */
   if(option==NOPT)
      putchar('\n');

/* ------------------------------------------------------- */
/* Controllo opzioni per la stampa del rapporto di testa. */
/* Se le opzioni sono '-Y', '-S', '-F', '-D', '-K' e '-V'. */
   else if((trueoptions()<=TWOS&&(subopt!=DVS&&subopt!=DRW&&subopt!=RNC)
    &&(option!=NOPT&&option!=LKEYS&&option!=NSDIV&&option!=ALLDP))
    ||(option==VARS)) {

      /* Stampa i relativi messaggi di intestazione. */
      if(lang==ENGLISH) {
         printf("\nPrime factorization from %lu to %lu\n",num,limit);
         if(option==KEYS)
            printf("(Numerical series with two decomposition factors.)\n\n");
         else if(option==VARS)
            printf("(Series defined by the decomposition factor %lu)\n\n",select);
         else if(option==DIVS)
            printf("(Numerical series composed only of divisible numbers.)\n\n");
         else putchar('\n');
      }
      else if(lang==ITALIANO) {
         printf("\nScomposizione in fattori primi da %lu a %lu\n",num,limit);
         if(option==KEYS)
            printf("(Serie numerica con due valori di scomposizione.)\n\n");
         else if(option==VARS)
            printf("(Serie definita dal fattore di scomposizione %lu)\n\n",select);
         else if(option==DIVS)
            printf("(Serie numerica composta solo da numeri divisibili.)\n\n");
         else putchar('\n');
      }
      else if(lang==ESPANOL) {
         printf("\nFactorización prima de %lu a %lu\n",num,limit);
         if(option==KEYS)
            printf("(Serie numérica con dos factores de descomposición.)\n\n");
         else if(option==VARS)
            printf("(Series definidas por el factor de descomposición %lu)\n\n",select);
         else if(option==DIVS)
            printf("(Series numéricas compuestas únicamente por números divisibles.)\n\n");
         else putchar('\n');
      }
      else if(lang==FRANCAIS) {
         printf("\nFactorisation première de %lu à %lu\n",num,limit);
         if(option==KEYS)
            printf("(Séries numériques à deux facteurs de décomposition.)\n\n");
         else if(option==VARS)
            printf("(Série définie par le facteur de décomposition %lu)\n\n",select);
         else if(option==DIVS)
            printf("(Série numérique composée uniquement de nombres divisibles.)\n\n");
         else putchar('\n');
      }
      else if(lang==PORTUGUES) {
         printf("\nFatoração principal de %lu para %lu\n",num,limit);
         if(option==KEYS)
            printf("(Série numérica com dois fatores de decomposição.)\n\n");
         else if(option==VARS)
            printf("(Séries definidas pelo fator de decomposição %lu)\n\n",select);
         else if(option==DIVS)
            printf("(Séries numéricas compostas apenas por numéros divisíveis.)\n\n");
         else putchar('\n');
      }
      else if(lang==DEUTCHE) {
         printf("\nPrimfaktorzerlegung von %lu bis %lu\n",num,limit);
         if(option==KEYS)
            printf("(Numerische Reihe mit zwei Zerlegungsfaktoren.)\n\n");
         else if(option==VARS)
            printf("(Reihe definiert durch den Zerlegungsfaktor %lu)\n\n",select);
         else if(option==DIVS)
            printf("(Zahlenreihen die nur aus teilbaren Zahlen bestehen.)\n\n");
         else putchar('\n');
      }
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [LANG-FACTS] GURU MEDITATION\n\n");
         return GURU;
      }
   }
   else if(option==PRIME&&subopt!=CNT&&argc>3) {
      if(lang==ENGLISH) {
         printf("\nSeries of prime numbers from %lu to %lu\n",num,limit);
         if(subopt==POS)
            printf("(With display of the corresponding cardinal position.)\n\n");
         else putchar('\n');
      }
      else if(lang==ITALIANO) {
         printf("\nSerie di fattori primi da %lu a %lu\n",num,limit);
         if(subopt==POS)
            printf("(Con visualizzazione della corrispondente posizione cardinale.)\n\n");
         else putchar('\n');
      }
      else if(lang==ESPANOL) {
         printf("\nSerie de números primos de %lu a %lu\n",num,limit);
         if(subopt==POS)
            printf("(Con visualización de la posición cardinal correspondiente.)\n\n");
         else putchar('\n');
      }
      else if(lang==FRANCAIS) {
         printf("\nSuite des nombres premiers de %lu à %lu\n",num,limit);
         if(subopt==POS)
            printf("(Avec affichage de la position cardinale correspondante.)\n\n");
         else putchar('\n');
      }
      else if(lang==PORTUGUES) {
         printf("\nSèrie de números primos de %lu a %lu\n",num,limit);
         if(subopt==POS)
            printf("(Com exibição da posição cardinal correspondente.)\n\n");
         else putchar('\n');
      }
      else if(lang==DEUTCHE) {
         printf("\nVolge von Primezahlen von %lu bis %lu\n",num,limit);
         if(subopt==POS)
            printf("(Mit Anzeige der entsprechenden Kardinalstelle.)\n\n");
         else putchar('\n');
      }
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [LANG-PRIME] GURU MEDITATION\n\n");
         return GURU;
      }
   }
   else if(option==GEMS) {
      if(lang==ENGLISH)
         printf("\nTwin prime numbers highlighted, from %lu to %lu\n\n",num,limit);
      else if(lang==ITALIANO)
         printf("\nNumeri primi gemelli evidenziati, da %lu a %lu\n\n",num,limit);
      else if(lang==ESPANOL)
         printf("\nNúmeros primos gemelos resaltados, de %lu a %lu\n\n",num,limit);
      else if(lang==FRANCAIS)
         printf("\nNombres premiers jumeaux mis en évidence, de %lu à %lu\n\n",num,limit);
      else if(lang==PORTUGUES)
         printf("\nNúmeros primos gêmeos destacados, de %lu a %lu\n\n",num,limit);
      else if(lang==DEUTCHE)
         printf("\nHervorgehobene Zwillingsprimzahlen, von %lu bis %lu\n\n",num,limit);
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
         printf("\nDescomposición de la lista en %u series.\n",nseg);
         printf("Del numéro %lu al numéro %lu inclusive.\n",num,limit);
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
            printf("ERROR [LANG-SUBLST] GURU MEDITATION\n\n");
         return GURU;
      }
   }

/* ------------------------------------------------------------------------- */
   else if(option==CALC) {
      if(lang==ENGLISH) {
         printf("\nPrime factorization of the given series.\n");
         printf("(The displayed series is filtered by the value %lu)\n\n",com);
      }
      else if(lang==ITALIANO) {
         printf("\nScomposizione in fattori primi della serie indicata.\n");
         printf("(La serie visualizzata è filtrata dal valore %lu)\n\n",com);
      }
      else if(lang==ESPANOL) {
         printf("\nFactorización prima de la serie dada.\n");
         printf("(La serie mostrada esta filtrada por el valor %lu)\n\n",com);
      }
      else if(lang==FRANCAIS) {
         printf("\nFactorisation première de la série donnée.\n");
         printf("(La série affichée est filtrée par la valeur %lu)\n\n",com);
      }
      else if(lang==PORTUGUES) {
         printf("\nFatoração prima da serie dada.\n");
         printf("(A série exibida é filtrada pelo valor %lu)\n\n",com);
      }
      else if(lang==DEUTCHE) {
         printf("\nPrimfaktorzerlegung der gegebenen Reihe.\n");
         printf("(Die angezeigte Reihe wird nach dem Wert %lu gefiltert.)\n\n",com);
      }
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [LANG-CALC] GURU MEDITATION\n\n");
         return GURU;
      }
   }
   else {

   /* ---------------------------------------------------------- */
   /* Esclude '-L', '-Q', '-N', -J', '-E'. */
      if(option!=NSDIV&&option!=PLIST&&option!=PJUMS&&option!=LKEYS
       &&option!=NPRIM&&option!=NOPT&&option!=ALLDP
       &&subopt!=DVS&&subopt!=DRW)
         putchar('\n');
   }

/* ------------------------------------------------------------ */
   if((option==DIVS&&(subopt==DVS||subopt==DRW))&&argc>2&&num>1) {
      if(lang==ENGLISH) {
         printf("\nDivisibility values for each number\n");
         printf("in the series indicated from %lu to %lu \n",num,limit);
      }
      else if(lang==ITALIANO) {
         printf("\nValori di divisibilità per ogni numero\n");
         printf("della serie indicata da %lu a %lu \n",num,limit);
      }
      else if(lang==ESPANOL) {
         printf("\nValores de divisibilidad para cada número\n");
         printf("de la serie indicada de %lu a %lu \n",num,limit);
      }
      else if(lang==FRANCAIS) {
         printf("\nValeurs de divisibilité pour chaque nombre\n");
         printf("de la série indiquée de %lu à %lu \n",num,limit);
      }
      else if(lang==PORTUGUES) {
         printf("\nValores de divisibilidade para cada número\n");
         printf("na série indicada de %lu a %lu \n",num,limit);
      }
      else if(lang==DEUTCHE) {
         printf("\nTeilbarkeitswerte für jede Zahl\n");
         printf("in der Reihe von %lu bis %lu \n",num,limit);
      }
      else {

      /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
      /* delle funzionalità interne, delle opzioni e degli Switch. */
         if(fsign)
            printf("ERROR [LANG-DVS] GURU MEDITATION\n\n");
         return GURU;
      }
      if(num>=100000000)
         printf("Please wait...\n\n");
      else printf("\n");
   }

/* ------------------------------------------------------------------------- */
/* Conversione dalla posizione cardinale -> al numero primo corrispondente.  */
   if((option==PRIME||option==PLIST)&&(subopt==CNT||subopt==TCN)) {
      if(cntlim!=cntbas) eflag=0;
      if(cntbas<1) cntbas=1;
      cntmp=cntbas;
      num=1;

   /* Determinazione del punto base per l'ottenimento del valore - */
   /* cardinale di posizione del numero primo all'interno del file - */
   /* contenente una serie di valori di posizione precalcolati. */
      ne=1,base=cntbas;
      while((base=(base/10))>10)
         ne++;
      base*=pow(10,ne);
      if(cntbas>10000)
         delf=cntbas/10000;
      if(cntbas>10000) {
         ne=1;

      /* Se la Directory esiste aggiunge la sottodirectory al percorso. */
         snprintf(pfdr,sizeof(nfdir),"%s/.fnl/",home);
         if((dp=opendir(pfdr))==NULL) {

         /* Esecuzione se il percorso della Directory non si può aprire. */
         /* visualizza [Errore: Non posso accedere al file [.tabcount_203280221.txt]!]. */
            snprintf(pnf,sizeof(nfile),"%s"TBCT,pfdr);
            fmesg=MSGBASE+lang+20;
            filemsg(&fmesg,&self);
            putchar('\n');
            return ERROR;
         }
         else {

         /* Se la Directory esiste aggiunge il nome del file al percorso. */
            snprintf(pnf,sizeof(nfile),"%s"TBCT,pfdr);

         /* Aperura del file con serie di valori cardinali di posizione precalcolati. */
         /* Il file '.tabcount_203280221.txt' deve essere generato dal comando 'prmcat'. */
            if((fp1=fopen(pnf,READ))==NULL) {

            /* Esecuzione se il file di configurazione non si può aprire. */
            /* Visualizza [Errore: Non posso aprire il file [.tabcount_203280221.txt]!]. */
               fmesg=MSGBASE+lang+20;
               filemsg(&fmesg,&self);
               putchar('\n');
               return ERROR;
            }
            else {

            /* Scorre le righe del file con numeri primi precalcolati ogni 10000 posizioni. */
               while(ne<=delf) {

               /* Posizionamento al numero primo corretto. */
                  pmprm=mprm;
                  fgets(pmprm,31,fp1),ne++;
               }
               pmprm=mprm;
               fclose(fp1);
               closedir(dp);
            }
         }
         pmprm=mprm;

      /* Estrazione del valore di offest associato al posizionamento precalcolato. */
         pmprm=mprm;
         while(*pmprm!='\x20') pmprm++;
         pmprm++;
         pprm=atol(pmprm);
         num=pprm;

      /* Estrazione del valore cardinale di posizionamento precalcolato associato al - */
      /* valore di offest con incrementi di 100000 step riferito al primo precedente. */
         while(*pmprm!='(') pmprm++;
         pmprm++;
         pcnt=atol(pmprm)+1;
      }

   /* Trova il numero primo della posizione specificata - */
   /* dal valore iniziale selezionato di una serie. */
      for(cntmp=pcnt;cntmp<=cntbas;cntmp++) {
         num++;
         while((primenum(num))!=NPR) num++;
      }
      cntbas=cntmp-1;
      number=num;

   /* Trova il numero primo della posizione specificata - */
   /* dal valore terminale selezionato di una serie. */
      limit=num;
      for(;cntmp<=cntlim;cntmp++) {
         limit++;
         while((primenum(limit))!=NPR) limit++;
      }
      cntlim=cntmp-1;
      range=(limit-num)+1;

   /* --------------------------------------- */
      if((option==PRIME&&subopt==CNT)&&argc>3) {
         if(lang==ENGLISH) {
            printf("Series of prime numbers from %lu to %lu\n",cntbas,cntlim);
            printf("Corresponding series from prime number %lu to the prime number %lu\n",num,limit);
            printf("(With display of the corresponding cardinal position.)\n\n");
         }
         else if(lang==ITALIANO) {
            printf("Serie di numeri primi dalla posizione %lu alla posizione %lu\n",cntbas,cntlim);
            printf("Serie corrispondente dal numero primo %lu al numero primo %lu\n",num,limit);
            printf("(Con visualizzazione della corrispondente posizione cardinale.)\n\n");
         }
         else if(lang==ESPANOL) {
            printf("Series de números primos de %lu a %lu\n",cntbas,cntlim);
            printf("Series correspondientes desde el número primo %lu hasta el número primo %lu\n",num,limit);
            printf("(Con visualización de la posición cardinal correspondiente.)\n\n");
         }
         else if(lang==FRANCAIS) {
            printf("Suite des nombres premiers de %lu à %lu\n",cntbas,cntlim);
            printf("Série correspondante du nombre premier %lu au nombre premier %lu\n",num,limit);
            printf("(Avec affichage de la position cardinale correspondante.)\n\n");
         }
         else if(lang==PORTUGUES) {
            printf("Sèries de números primos de %lu a %lu\n",cntbas,cntlim);
            printf("Séries correspondentes do número primo %lu ao número primo %lu\n",num,limit);
            printf("(Com exibição da posição cardinal correspondente.)\n\n");
         }
         else if(lang==DEUTCHE) {
            printf("Volge von Primezahlen von %lu bis %lu\n",cntbas,cntlim);
            printf("Entsprechende Zahlenreihe von der Primzahl %lu bis zur Primzahl %lu\n",num,limit);
            printf("(Mit Anzeige der entsprechenden Kardinalstelle.)\n\n");
         }
      }
   }

/* ------------------------------------------------------------------------------------ */
/* Preparazione formato di visualizzazione e stampa per la serie di numeri selezionata. */
   if(trueoptions()<=NPM||option==VARS||option==CALC) {
     if(limit<=RANGE) {

     /* 'ncx' definsce di quante posizioni deve essere traslato il valore. */
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
        else {
           if(limit<=UL_MAX) ncx=10;
        }
     }
   }

/* ------------------------------------------ */
/* Loop esterno primario di calcolo e stampa. */
   do {

   /* Controllo sull'opzione '-B'. */
   /* Imposta il limite della prima serie. */
      if(option==BASE)
         limit=num+(lseg);

   /* Controllo sulle opzioni '-DV' e '-DW'.  */
   /* Permette di impostare un solo parametro. */
      if(option==DIVS&&(subopt==DVS||subopt==DRW)) {
         if(argc==3)
            limit=num;
      }

   /* Controllo sull'opzione '-N' */
   /* Imposta il limite minimo inferiore. */
      if(option==NPRIM)
         if(num<3) num=0;   /* valori validi da 0 a 2.  */

   /* Controllo sulle opzioni '-P' ed '-L' con Switch 'N', 'R', 'C', 'B'. */
   /* Ottiene la posizione di origine per l'inizio - */
   /* della stampa della posizione del primo attuale. */
      if(((option==PRIME||option==PLIST)&&(subopt==POS||subopt==RNC||subopt==CNT))
       ||(option==PLIST&&subopt==TCN)) {
         if(!num||num==1)
            num=2,number=2;
         if(!limit||limit==1)
            limit=2,limt=2;
         limt=number-1;

      /* Determinazione del punto base per l'ottenimento del valore - */
      /* cardinale di posizione del numero primo all'interno del file - */
      /* contenente una serie di valori di posizione precalcolati. */
         if(subopt==POS||subopt==RNC||subopt==CNT||subopt==TCN) {
            ne=1,base=num;
            while((base=(base/10))>10)
               ne++;
            base*=pow(10,ne);
            if(num>100000)
               delf=num/100000;
         }

      /* Ottenimento del valore di posizione cardinale di prossimità di un numero primo. */
         if((subopt==POS||subopt==RNC||subopt==CNT||subopt==TCN)&&num>100000) {
            ne=1;

         /* Se la Directory esiste aggiunge la sottodirectory al percorso. */
            snprintf(pfdr,sizeof(nfdir),"%s/.fnl/",home);
            if((dp=opendir(pfdr))==NULL) {

            /* Esecuzione se il percorso della Directory non si può aprire. */
            /* visualizza [Errore: Non posso accedere al file [.tabprime_4294967296.txt]!]. */
               snprintf(pnf,sizeof(nfile),"%s"TBPR,pfdr);
               fmesg=MSGBASE+lang+20;
               filemsg(&fmesg,&self);
               putchar('\n');
               return ERROR;
            }
            else {

            /* Se la Directory esiste aggiunge il nome del file al percorso. */
               snprintf(pnf,sizeof(nfile),"%s"TBPR,pfdr);

            /* Aperura del file con serie di valori cardinali di posizione precalcolati. */
            /* Il file '.tabprime_4294967296.txt' deve essere generato dal comando 'poscat'. */
               if((fp1=fopen(pnf,READ))==NULL) {

               /* Esecuzione se il file di configurazione non si può aprire. */
               /* Visualizza [Errore: Non posso aprire il file [.tabprime_4294967296.txt]!]. */
                  fmesg=MSGBASE+lang+20;
                  filemsg(&fmesg,&self);
                  putchar('\n');
                  return ERROR;
               }
               else {

               /* Scorre le righe del file con valori cardinali di posizione precalcolati. */
                  while(ne<=delf) {

                  /* Posizionamento al valore cardinale di posizione corretto. */
                     pmpos=mpos;
                     fgets(pmpos,31,fp1),ne++;
                  }
                  pmpos=mpos;
                  fclose(fp1);
                  closedir(dp);
               }
            }

         /* Estrazione del valore cardinale di posizionamento precalcolato associato al - */
         /* valore di offest con incrementi di 100000 step riferito al primo precedente. */
            pmpos=mpos;
            while(*pmpos!='(') pmpos++;
            pmpos++;
            ppos=atol(pmpos)+1;
         }

      /* Calcolo dei valori cardinali di posizione - */
      /* che precedono il punto di inizio prescelto. */
         if(num>100000)
            orig=delf*100000+1;
         while(orig<=limt) {
            if(primenum(orig)==NPR)
               ppos++;
            orig++;
         }
         if(subopt==CNT||subopt==TCN)
            ppos=cntbas;
      }

   /* Calcolo dell'ultima posizione cardinale della serie. */
   /* richiesta per la giustificazione di stampa dell'opzione '-LR'. */
      cnttmp=ppos,lmtmp=limt+1;
      for(;lmtmp<limit;lmtmp++) {
         if(primenum(lmtmp)==NPR)
            cnttmp++;
      }
      if(primenum(limit)!=NPR)
         cnttmp-=1;
      if((option==PLIST&&(subopt==RNC||subopt==POS))
       ||(option==PRIME&&subopt==POS))
         cntlim=cnttmp;
      nccnt=ppos;

  /* Calcolo della differenza di caratteri stampati tra - */
  /* la posizione cardinale iniziale e quella finale della serie. */
     cntl=cntlim,cntb=cntbas;
     while((cntl/=10)>0) ctup++;
     while((cntb/=10)>0) ctdw++;
     nph=ctup-ctdw;

   /* ----------------------------- */
   /* Loop interno di stampa liste. */
      while(num<=limit) {

      /* Chiamata della funzione di ricerca dei numeri divisibili. */
      /* Se il numero è primo restituisce zero; se il numero è divisibile - */
      /* restituisce il primo fattore di scomposizione. */
         divs=primenum(num);
         swflag=HFLAG;

      /* ------------------------------------------------------------------------- */
      /* Preparazione formato di visualizzazione e stampa per la serie selezionata - */
      /* delle posizioni cardinali associate ai numeri primi della serie indicata. */
         if(((option==PRIME||option==PLIST)&&(subopt==POS||subopt==CNT))
          ||(option==PLIST&&(subopt==POS||subopt==CNT||subopt==RNC||subopt==TCN))) {
            if(cntlim<=RGCNT) {

            /* 'ncz' definsce di quante posizioni deve essere traslato il valore. */
               if(nccnt>0&&nccnt<10) ncz=1;
               else if(nccnt<100) ncz=2;
               else if(nccnt<1000) ncz=3;
               else {
                  if(nccnt<=RGCNT) ncz=4;
               }
            }
            else {
               if(nccnt>RGCNT&&nccnt<10000) ncz=4;
               else if(nccnt<100000) ncz=5;
               else if(nccnt<1000000) ncz=6;
               else if(nccnt<10000000) ncz=7;
               else if(nccnt<100000000) ncz=8;
               else {
                  if(nccnt<=CT_MAX) ncz=9;
               }
            }
         }

      /* ----------------------------------- */
      /* Opzioni di stampa dei numeri primi. */
         if(divs==1) divs=-1;   /* Riconduce a zero. */

      /* Inizio Loop per i numeri primi. */
      /* Se il numero è primo allora divs = NPR. */
         if(!divs) {
            if(num<3) hfatt=0;
            if(limit<4) hfatt=0;

         /* Esecuzione se il numero è primo. */
            if(!mflag) {
               if(inflag)
                  if(number>2&&(primenum(number)==NPR)) pdist+=1;
               *pvect=pdist,pdist=1U,pvect++;
               if(inflag) {
                  if(number==0||number==1) mvect[0]=1,pvect=mvect+1;
                  if(number==2) mvect[0]=1,mvect[1]=2,pvect=mvect+2;
                  inflag=LFLAG;
               }
            }
            if(num!=limit) {
               tmpdst=1;
               ndflag=HFLAG;
            }
            pcount++,psegm++;
            if(num<2) pcount=0;
            if(limit<2) pcount=0;
            mflag=HFLAG;
            nppos++;

         /* Salta alla label NOPRT per l'opzione STAT. */
            if(option==STAT&&subopt!=TBL)
               goto NOPRT;

         /* Stampa con le opzioni '-Y', '-S', o '-F'. */
            if(subopt==PME)

            /* Se è presente lo Switch 'P'. */
               printf("> ");
            else {

            /* Se è presente lo Switch 'L' abbinato a '-Q' o se assente. */
            /* Con le opzioni '-Q', '-D', '-K', '-E', '-V' o '-B'. */
               if(trueoptions()==ONEY||option==VARS||option==BASE);   /* Non fare nulla. */

            /* Stampa con le opzioni: '-A', -Y', '-S', '-F', '-C', '-N'.  */
               if(trueoptions()!=ONEY&&trueoptions()!=THRE&&option!=ALLDP
                &&option!=NOPT&&option!=VARS&&option!=BASE) {

               /* Se sono presenti gli Switch 'S', 'U', o 'D' o se assenti. */
               /* Stampa con le opzioni: -Y', '-S', '-F'. */
                  printf("  ");
               }
               else {

               /* Stampa con le opzioni: '-P', '-L', '-G', '-J' e NOPT. */
                  if((trueoptions()==THRE)||(option==ALLDP&&subopt==LST)
                   ||(option==NOPT&&subopt==NSWT)) {

                  /* Se le opzioni sono '-G' e '-J'.  */
                     if(option==GEMS||option==PJUMS) {

                     /* Separa in coppie evidenziate i numeri primi gemelli. */
                        if(limit<5&&(num-nprec)==1) {
                           gtmp=num,fgem=0,fprec=0;
                           nprec=num;
                        }
                        else if(limit>4&&(num-nprec)>2) {
                           gtmp=num,fgem=0,fprec=1;
                           nprec=num,++num;
                           continue;
                        }
                        else {
                           ++gemcnt,fgem=1,fprec=0;
                           if(num<3) nprec=2,gtmp=num;
                           if(num==3) nprec=3,num=5,gtmp=nprec;
                           if(num>2&&num<8) gtmp=nprec;
                        }
                        nprec=num;
                     }

                  /* Giustificazione di stampa per le serie di opzioni - */
                  /* che usano gli Switch 'L' 'R' e 'B'. */
                     if(((option==ALLDP||option==PLIST||option==PJUMS)&&subopt==LST)
                      ||(option==PLIST&&(subopt==RNC||subopt==TCN))) {
                        if(option==PLIST&&(subopt==LST||subopt==RNC||subopt==TCN))
                           printf(" ");

                     /* Stampa se le opzioni sono '-A', -L' e '-J' con lo Switch 'L'. */
                     /* Stampa se l'opzione è '-L' con lo Switch 'R' oppure 'B'. */
                        if(limit<10) printf("         ");
                        if(limit>=10&&limit<100) printf("        ");
                        if(limit>=100&&limit<1000) printf("       ");
                        if(limit>=1000&&limit<10000) printf("      ");
                        if(limit>=10000&&limit<100000) printf("     ");
                        if(limit>=100000&&limit<1000000) printf("    ");
                        if(limit>=1000000&&limit<10000000) printf("   ");
                        if(limit>=10000000&&limit<100000000) printf("  ");
                        if(limit>=100000000&&limit<1000000000) printf(" ");
                        if(limit>=1000000000);
                     }

                  /* Se l'opzione è '-L' senza lo Switch 'L'. */
                  /* Giustificazione di stampa per le serie che non usano lo Switch 'L'. */
                     else printf(" ");
                  }
               }
               if(option==ALLDP)
                  printf(" ");
            }

         /* Stampa in tutti i casi con '-Y', '-S' o '-F' + ['S', 'U', 'D' o 'P']. */
            if(trueoptions()==TWOS&&(trueswitch()<=TRUESW||subopt==PME||subopt==LST)) {
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

         /* Stampa con le opzioni NOPT, '-P', '-L', '-G', '-J' o '-C'. */
         /* Nessuno Switch. */
            else {
               if((trueoptions()==THRE&&option!=GEMS&&option!=PJUMS)
                ||option==CALC||option==NOPT) {
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

               /* Stampa il riferimento posizionale del numero primo attuale. */
                  if(((option==PRIME||option==PLIST)&&(subopt==POS||subopt==CNT))
                   ||(option==PLIST&&(subopt==POS||subopt==CNT||subopt==RNC||subopt==TCN))) {
                     printf("  ");
                     if(option==PLIST&&(subopt==RNC||subopt==TCN)) {

                     /* Stampa se sono presenti gli Switch 'N' e 'C' all'opzione '-P'. */
                     /* Stampa se sono presenti gli Switch 'N', 'R', 'C' e 'B' all'opzione '-L'. */
                        for(nph=9;nph>ncz;nph--)
                           printf(" ");
                     }
                     else {
                        if((option==PRIME||option==PLIST)&&(subopt==POS||subopt==CNT)) {

                        /* Stampa se sono presenti gli Switch 'N' e 'C' alle opzioni '-P' e '-L'. */
                           if(nph==9) printf("         ");
                           else if(nph==8) printf("        ");
                           else if(nph==7) printf("       ");
                           else if(nph==6) printf("      ");
                           else if(nph==5) printf("     ");
                           else if(nph==4) printf("    ");
                           else if(nph==3) printf("   ");
                           else if(nph==2) printf("  ");
                           else {
                              if(nph==1) printf(" ");
                           }

                        /* Calcolo della differenza di caratteri stampati tra - */
                        /* la posizione cardinale attuale della serie. */
                           cnta=nccnt,ctal=1U;
                           while((cnta/=10)>0) ctal++;
                           npa=(ctal-ctdw);

                        /* Effettua la giustificazione. */
                           for(i=0;i<npa;i++)
                              putchar('\x08');
                        }
                     }

                  /* Stampa la posizione cardinale associata al numero primo - */
                  /* se sono presenti le opzioni '-PN', '-PC', '-LN', '-LR', -LC' e '-LB'. */
                  /* La posizione cardinale viene stampata come stringa e non come valore - */
                  /* perchè il valore viene racchiuso tra le parentesi tonde. */
                     if(nccnt!=ppos)
                        return(printf("Error: Incongruent cardinal position.\n\n"));
                     pstpos=stpos;
                     snprintf(pstpos,sizeof(stpos),"(%ld)",ppos);
                     printf("%s",pstpos);
                     ++ppos,++nccnt;
                  }
                  putchar('\n');
               }
            }
            if(option==GEMS||option==PJUMS) {

            /* Stampa solo se i numeri primi sono gemelli. */
               if(fgem) {
                  if(option==PJUMS&&subopt==LST)
                     printf(" ");

               /* Stampa per il primo numero gemello. */
                  if(ncx==1) printf("%1lu",gtmp);
                  else if(ncx==2) printf("%2lu",gtmp);
                  else if(ncx==3) printf("%3lu",gtmp);
                  else if(ncx==4) printf("%4lu",gtmp);
                  else if(ncx==5) printf("%5lu",gtmp);
                  else if(ncx==6) printf("%6lu",gtmp);
                  else if(ncx==7) printf("%7lu",gtmp);
                  else if(ncx==8) printf("%8lu",gtmp);
                  else if(ncx==9) printf("%9lu",gtmp);
                  else {
                     if(ncx==10) printf("%10lu",gtmp);
                  }
                  fgem=0,printf(" ⋄ ");

               /* Giustificazione di stampa con lo Switch 'L'. */
                  if((option==PLIST||option==PJUMS)&&subopt==LST) {
                     if(limit<10) printf("         ");
                     if(limit>=10&&limit<100) printf("        ");
                     if(limit>=100&&limit<1000) printf("       ");
                     if(limit>=1000&&limit<10000) printf("      ");
                     if(limit>=10000&&limit<100000) printf("     ");
                     if(limit>=100000&&limit<1000000) printf("    ");
                     if(limit>=1000000&&limit<10000000) printf("   ");
                     if(limit>=10000000&&limit<100000000) printf("  ");
                     if(limit>=100000000&&limit<1000000000) printf(" ");
                     if(limit>=1000000000);
                  }

               /* Stampa il secondo numero gemello. */
                  if(num<=2) {
                     if(ncx==1) printf("%1lu",num+1);
                     else if(ncx==2) printf("%2lu",num+1);
                     else if(ncx==3) printf("%3lu",num+1);
                     else if(ncx==4) printf("%4lu",num+1);
                     else if(ncx==5) printf("%5lu",num+1);
                     else if(ncx==6) printf("%6lu",num+1);
                     else if(ncx==7) printf("%7lu",num+1);
                     else if(ncx==8) printf("%8lu",num+1);
                     else if(ncx==9) printf("%9lu",num+1);
                     else {
                        if(ncx==10) printf("%10lu",num+1);
                     }
                  }
                  else {
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
                  }
                  putchar('\n');
               }
               else putchar('\r');
            }

         /* Esegui con l'opzione '-N'. */
            if(option==NPRIM) {
               if(num!=limit) {

               /* Salta una riga se il numero è primo. */
                  if(!flprt)
                     printf("\r");
               }
               else putchar('\r');
            }

         /* Stampa con l'opzione '-B'. */
            if(option==BASE);   /* Non fare nulla. */
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
            mflag=LFLAG;

         /* Conta i numeri divisibili in coda nella serie dopo l'ultimo primo. */
         /* Valore richiesto per il calcolo della distanza media dei numeri primi. */
            if(ndflag&&primenum(num)!=NPR) {
               if(num!=limit)
                  tmpdst++;
               else *pvect=tmpdst;
               ndflag=HFLAG;
            }

         /* Salta alla label NOPRT per l'opzione STAT. */
            if(option==STAT&&subopt!=TBL) {

            /* Salto diretto alla Label NOPRT: */
               goto NOPRT;
            }

         /* Calcola i valori di divisibilità di ogni numero della serie indicata. */
         /* Se l'opzione è '-D' e gli Switch sono 'V' o 'W' oppure - */
         /* se l'opzione è '-Q' e gli Switch sono 'V' o 'R'. */
            if((option==DIVS&&(subopt==DVS||subopt==DRW))
             ||(option==NSDIV&&(subopt==DVS||subopt==RNC))) {

            /* Chiamata alla funzione di stampa dei valori di divisibilità - */
            /* di un numero della serie indicata. Ad ogni chiamata vengono - */
            /* calcolati e stampati tutti i valori di un singolo numero. */
               if(num>4253024256||limit>4253024256) {

                /* Visualizza [Errore: Argomenti errati! Valori fuori limite.]. */
                   errscode=ERRSBASE+lang+140;
                   return(errorstype(&errscode));
               }
               else {

               /* Esegui se l'opzione è '-Q' e lo Switch è 'R'. */
                  if(option==NSDIV&&subopt==RNC) {

                  /* Giustificazione di stampa con lo Switch 'L'. */
                     if(limit<10) printf("         ");
                     if(limit>=10&&limit<100) printf("        ");
                     if(limit>=100&&limit<1000) printf("       ");
                     if(limit>=1000&&limit<10000) printf("      ");
                     if(limit>=10000&&limit<100000) printf("     ");
                     if(limit>=100000&&limit<1000000) printf("    ");
                     if(limit>=1000000&&limit<10000000) printf("   ");
                     if(limit>=10000000&&limit<100000000) printf("  ");
                     if(limit>=100000000&&limit<1000000000) printf(" ");
                     if(limit>=1000000000);
                  }
                  if((divfactors(num))==OK);
                  else {

                  /* Visualizza [Errore: Serie numerica non valida!]. */
                     errscode=ERRSBASE+lang+220;
                     return(errorstype(&errscode));
                  }
               }
            }

         /* Se le opzioni sono NOPT, '-Y', '-S', '-F', '-D', '-K', - */
         /* se sono presenti gli Switch 'P', 'S', 'U' o 'D', - */
         /* controlla e seleziona il relativo stato di attivazione. */
            else if((trueoptions()<=TWOS&&(option!=ALLDP&&option!=NSDIV))
             ||(option==DIVS&&(subopt!=DVS&&subopt!=DRW))
             ||(option==KEYS)) {

            /* Incrementa il conteggio di valori statistici. */
               if(subopt==SEL&&divs==select)
                  swflag=LFLAG,selcount++;
               else if(subopt==DOW&&divs<=select)
                  swflag=LFLAG,selcount++;
               else {
                  if(subopt==UPP&&divs>=select)
                     swflag=LFLAG,selcount++;
               }

            /* Chiamata alla funzione di stampa formattata dei fattori primi di - */
            /* scomposizione se le opzioni sono '-Y', '-S', '-F', '-D', '-K', - */
            /* o NOPT. La funzione stampa i fattori primi di scomposizione in - */
            /* tre modi diversi, in base alle opzioni utilizzate: (-Y, -S, -F). */
               primefact(num,limit);
            }

         /* Stampa con l'opzione '-N'. */
            else if(option==NPRIM) {
               if(!(num%2)) {
                  goto NOPRT;
               }
               primefact(num,limit);
               oddcnt++,dstmp++;
            }

         /* Stampa con l'opzione '-C'. */
            else if(option==CALC)
               primefact(num,limit);

         /* Stampa con le opzioni '-A' e '-Q' con o senza Switch 'L' e - */
         /* se non sono presenti gli Switch 'V' e 'R' con l'opzione '-Q'. */
            else if(option==ALLDP||(option==NSDIV&&(subopt!=DVS&&subopt!=RNC))) {

            /* Esegui se le opzioni sono '-A' o '-Q' con lo Switch 'L'. */
               if((option==ALLDP||option==NSDIV)&&subopt==LST) {

               /* Giustificazione di stampa con lo Switch 'L'. */
                  if(limit<10) printf("         ");
                  if(limit>=10&&limit<100) printf("        ");
                  if(limit>=100&&limit<1000) printf("       ");
                  if(limit>=1000&&limit<10000) printf("      ");
                  if(limit>=10000&&limit<100000) printf("     ");
                  if(limit>=100000&&limit<1000000) printf("    ");
                  if(limit>=1000000&&limit<10000000) printf("   ");
                  if(limit>=10000000&&limit<100000000) printf("  ");
                  if(limit>=100000000&&limit<1000000000) printf(" ");
                  if(limit>=1000000000);
               }
               primefact(num,limit);
            }

         /* Stampa con l'opzione '-V' o '-B'. */
            else {
               if(option==VARS) {

               /* Chiamata alla funzione di stampa formattata dei fattori - */
               /* di scomposizione per l'opzione '-V' se il  parametro di - */
               /* scomposizione impostato è uguale al valore restituito. */
                  if(divs==select) {
                     primefact(num,limit);
                     seltot++;
                  }
               }

            /* Stampa con l'opzione '-B'. */
               if(option==BASE);    /* Non fare nulla. */
            }
         }

      /* Corregge il salto di riga delle coppie di numri primi gemelli. */
         if(option==GEMS||option==PJUMS) {

         /* Non fare nulla. */
            if(!fgem);
            else putchar('\r');
         }

      /* In entrambi i casi, se il valore è divisibile oppure primo, esegui comunque. */
         if(option==LKEYS);   /* non fare nulla. */

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

      if(((option==DIVS||option==NSDIV)&&!dcount)||((option==KEYS||option==LKEYS)&&!keycnt)
       ||((option==PRIME||option==PLIST)&&!pcount)||((option==GEMS||option==PJUMS)&&!gemcnt)
       ||(option==VARS&&!seltot)||(option==NPRIM&&!dcount)||(option==CALC&&!(dcount+pcount))) {
         if((option==DIVS&&subopt==DVS)&&num<4) {

         /* Visualizza < LISTA VUOTA > per l'opzione -dV */
            fmesg=MSGBASE+lang+70;
            filemsg(&fmesg,&select);
         }
         if(((option==NSDIV||option==DIVS)&&limt<4)
          ||(option==CALC&&(number<2&&limt<2)&&com&&!tflg)) {

         /* Salto diretto alla Label NOLV: */
            goto NOLV;
         }

      /* Visualizza < LISTA VUOTA > per le opzioni: */
      /* '-D', '-P', '-N', '-L', '-Q', '-K', '-E', '-G', '-J', '-V'. */
         fmesg=MSGBASE+lang+70;
         filemsg(&fmesg,&select);
      }
      if((option==PJUMS&&!gemcnt)||(option==LKEYS&&!keycnt))
         putchar('\n');

      /* Label. */
      NOLV:

   /* ---------------------------------------------------------------- */
      if(pcount&&dcount) {

      /* Calcolo del minimo del massimo e della media della distanza - */
      /* tra i singoli numeri primi della serie indicata. */
         pvect=mvect;
         for(;(*pvect);pvect++) {
            lpdist=(*pvect<=lpdist)?*pvect:lpdist;
            hpdist=(*pvect>=hpdist)?*pvect:hpdist;
            tdist+=(float)*pvect;
         }
         for(neld=0;mvect[neld]!=0;neld++);
         if(tdist>40&&neld>12)
            fdist=tdist/(neld-1);
         else
            fdist=tdist/neld;
         if(neld<3) pmdist=1;
         if((int)fdist<4)
            pmdist=1;
         if(fdist-(int)fdist >0.5) fdist+=1;
            pmdist=(unsigned short)fdist;
         fcom=fdist-(pmdist+1);
         if(fcom>=0.5)
            pmdist+=1;

      /* Aggiustamenti specifici */
         if((number==0||number==1)&&(limit==3||limit==7))
            hpdist=2,pmdist=1;
      }

   /* Aggiustamento di alcuni valori statistici per l'opzione '-g' con - */
   /* riferimento a serie particolari con termine <5 oppure con inizio a 0 ed 1 */
      if(option==GEMS) {
         if(option==GEMS&&limit==5)
            hpdist=1,pmdist=1;
         if((number==0||number==1)&&limit>=5) {
            if(limit!=(primenum(num)))
               pcount+=1;
         }
         if((number==2||number==3)&&(limit!=3&&limit!=4))
            pcount+=1;
      }

      /* ---------------------------------------- */
      /* Esecuzione se è presente l'opzione '-B'. */
      if(option==BASE) {
         if(nseg<2) dsegm+=1;

      /* Memorizza la lista del numero di fattori primi e divisibili - */
      /* per ogni serie numerica generata per la funzione 'statseries()'. */
         *pnprime++=psegm;
         *pndivs++=dsegm;
         npv++;
         if(nseg>1) --limit;
         if(((num-lseg)==2&&limit==4)   /* Correzione disallineamento valori. */
          ||((num-lseg)==3&&limit==4)
          ||((num-lseg)==5&&limit==6))
            psegm-=1,dsegm+=1;

      /* --------------------------------------------------------------------------------- */
      /* Stampa i parametri delle serie numeriche generate dalla gamma di valori inseriti, - */
      /* secondo l'equazione: lunghezza_serie=((limite_serie-base_serie)+1)/numero_serie. */
         if(lang==ENGLISH) {
            if((num-lseg)<100000&&limit<100000)
               printf("\nSeries from %5.1lu to %5.1lu - ",(num-lseg),limit);
            else
               printf("\nSeries from %10.1lu to %10.1lu - ",(num-lseg),limit);
            printf("Prime numbers %4.1u - Divisible numbers %5.1u",psegm,dsegm);
         }
         else if(lang==ITALIANO) {
            if((num-lseg)<100000&&limit<100000)
               printf("\nSerie da %5.1lu a %5.1lu - ",(num-lseg),limit);
            else
               printf("\nSerie da %10.1lu a %10.1lu - ",(num-lseg),limit);
            printf("Numeri Primi %4.1u - Numeri divisibili %5.1u",psegm,dsegm);
         }
         else if(lang==ESPANOL) {
            if((num-lseg)<100000&&limit<100000)
               printf("\nSeries del %5.1lu al %5.1lu - ",(num-lseg),limit);
            else
               printf("\nSeries del %10.1lu al %10.1lu - ",(num-lseg),limit);
            printf("Números primos %4.1u - Números divisibles %5.1u",psegm,dsegm);
         }
         else if(lang==FRANCAIS) {
            if((num-lseg)<100000&&limit<100000)
               printf("\nSéries de %5.1lu à %5.1lu - ",(num-lseg),limit);
            else
               printf("\nSéries de %10.1lu à %10.1lu - ",(num-lseg),limit);
            printf("Nombres premiers %4.1u - Nombres divisibles %5.1u",psegm,dsegm);
         }
         else if(lang==PORTUGUES) {
            if((num-lseg)<100000&&limit<100000)
               printf("\nSéries de %5.1lu a %5.1lu - ",(num-lseg),limit);
            else
               printf("\nSéries de %10.1lu a %10.1lu - ",(num-lseg),limit);
            printf("Números primos %4.1u - Números divisíveis %5.1u",psegm,dsegm);
         }
         else if(lang==DEUTCHE) {
            if((num-lseg)<100000&&limit<100000)
               printf("\nSerien von %5.1lu bis %5.1lu - ",(num-lseg),limit);
            else
               printf("\nSerien von %10.1lu bis %10.1lu - ",(num-lseg),limit);
            printf("Primzahlen %4.1u - Teilbare Zahlen %5.1u",psegm, dsegm);
         }
         else {

         /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
         /* delle funzionalità interne, delle opzioni e degli Switch. */
            if(fsign) {
               printf("ERROR [LANG-STAT] GURU MEDITATION\n\n");
               return GURU;
            }
         }

      /* Calcola il totale dei numeri primi e divisbili per l'opzione '-b'. */
      /* Azzera il conteggio parziale per ogni serie calcolata. */
         sumprim+=psegm;
         sumdivs+=dsegm;
         psegm=0,dsegm=0;
      }
   }
   while(limt>limit);   /* ciclo esterno do while. */

/* Se presente un solo argomento invece di due. */
   if(flg) putchar('\n');

/* Se sono presenti due argomenti numerici coincidenti. */
   if(number==limt&&!flg) {
      if(option!=LKEYS)   /* Esclude '-E'. */
         putchar('\n');
   }

/* Uscita forzata per l'opzione '-A'. */
   if(option==ALLDP)
      return OK;

/* Fine loop esterno di calcolo e stampa. */
/* -------------------------------------- */

/* -------------------------------- */
/* Controlla se il flag è attivato. */
/* Esecuzione se esiste un solo argomento numerico. */
   if(eflag) {
      if(option==CALC) {
         if(limit>1||!com||tflg)
            putchar('\n');
      }

   /* Eccezione per due argomenti coincidenti. */
      if(option==PRIME&&(subopt==POS||subopt==CNT)&&!flg)
         putchar('\n');

   /* Ritorna sempre qui per uno o due argomenti coincidenti. */
      return OK;
   }

/* -------------------------------------------------- */
/* Esecuzione se esiste più di un argomento numerico. */
   else {
      if(option!=NOPT&&option!=PLIST&&option!=LKEYS&&option!=PJUMS&&option!=NSDIV) {
         if(option==BASE||option==GEMS)
            putchar('\n');

      /* Validazione delle opzioni per la stampa del tipo di rapporto di coda. */
      /* Rapporto statistico delle opzioni '-S', '-F', '-Y', '-D', '-P', '-N', - */
      /* '-K', '-G', -B', '-V', '-C', '-T'. */
         hfatt=(!hfatt)?--num:hfatt;
         if(num==1&&limit==2)   /* Il due è il numero primo piu piccolo. */
            pcount=1;
         if(option==BASE)   /* Correzione disallineamento valore. */
            if(nseg==1) range+=1;
         if(lang==ENGLISH) {
            if(option==STAT)
               printf("%s %s                    Summary report:\n",NAMEPROG,VERSION);
            else {
               if(option!=GEMS) printf("\n");
               printf("\n%s %s              Final summary report:\n",NAMEPROG,VERSION);
            }
            printf("-------------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Selection by number:                   %10.1lu\n",number);
               if(option==BASE)
                  printf("Up to number:                          %10.1lu\n",limit);
               else
                  printf("At number:                             %10.1lu\n",limit);
            }
            if(option==CALC)
               printf("Start of series from number:           %10.1lu\n",number);
            if(option==PRIME&&subopt==CNT) {
               printf("Selection from the cardinal position:   %9.1lu\n",cntbas);
               printf("Up to the cardinal position:            %9.1lu\n",cntlim);
            }
            if(option==KEYS||(option!=BASE&&option!=CALC
             &&option!=VARS&&option!=STAT)) {
               printf("Series from number:                    %10.1lu\n",number);
               printf("At number:                             %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Total numbers in the series:                %5.1lu\n",range);
            if(option==CALC) {
               printf("Selected period:                       %10.1lu\n",com);
               printf("Total numbers selected:                     %5.1u\n",dcount+pcount);
            }
            if(option!=DIVS&&option!=KEYS&&option!=NPRIM) {
               if(option==BASE)
                  printf("Total prime numbers:                        %5.1u\n",sumprim);
               else
                  printf("Total prime numbers:                        %5.1u\n",pcount);
            }
            if(option!=PRIME&&option!=GEMS) {
               if(option==BASE)
                  printf("Total divisibles numbers:                   %5.1u\n",sumdivs);
               else
                  printf("Total divisibles numbers:                   %5.1u\n",dcount);
            }
            if(option==NPRIM) {
               printf("Odd divisible numbers displayed:            %5.1u\n\n",oddcnt);
               return OK;
            }
            if(option==GEMS)
               printf("Twin prime numbers (Pairs):                 %5.1u\n",gemcnt);
            if(option==KEYS)
               printf("Consistent values displayed:                %5.1u\n",keycnt);
            if(option!=PRIME&&option!=BASE&&option!=VARS
             &&option!=GEMS) {
               if(!(dcount+pcount)) hfatt=0;
               if((dcount+pcount)==1) hfatt=primenum(num);
               if(num==1&&limit==2) hfatt=0;
               if(num==2&&limit==3) hfatt=0;
               if(option==DIVS&&(subopt==DVS||subopt==DRW))
                  printf("Highest initial divisor:                %9.1lu\n",hfatt);
               else
                  printf("Highest initial prime factor:           %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWOS&&option!=NSDIV)
             &&trueswitch()==TRUESW) {
               printf("Prime factor selected:                      %5.1lu\n",select);
               printf("Quantity of selected values:                %5.1u\n",selcount);
            }
            if(trueoptions()==TWOS||option==PRIME
             ||option==STAT||(option==GEMS&&limit>4)) {
               if((limit-number)>1&&((number<=1&&limit>3)
                ||(number>1&&limit>2))) {
                  printf("Maximum distance between two primes:        %5.1u\n",hpdist);
                  printf("Average distance between two primes:        %5.1u\n\n",pmdist);
                  return OK;
               }
               else {
                  putchar('\n');
                  return OK;
               }
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
            if(option==DIVS||option==KEYS||option==CALC||option==GEMS)
               putchar('\n');
         }
         else if(lang==ITALIANO) {
            if(option==STAT)
               printf("%s %s            Rapporto riassuntivo:\n",NAMEPROG,VERSION);
            else {
               if(option!=GEMS) printf("\n");
               printf("\n%s %s     Rapporto riassuntivo finale:\n",NAMEPROG,VERSION);
            }
            printf("-----------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Selezione dal numero:                %10.1lu\n",number);
               if(option==BASE)
                  printf("Fino al numero:                      %10.1lu\n",limit);
               else
                  printf("Al numero:                           %10.1lu\n",limit);
            }
            if(option==CALC)
               printf("Inizio serie dal numero:             %10.1lu\n",number);
            if(option==PRIME&&subopt==CNT) {
               printf("Selezione dalla posizione cardinale:  %9.1lu\n",cntbas);
               printf("Fino alla posizione cardinale:        %9.1lu\n",cntlim);
            }
            if(option==KEYS||(option!=BASE&&option!=CALC
             &&option!=VARS&&option!=STAT)) {
               printf("Serie dal numero:                    %10.1lu\n",number);
               printf("Al numero:                           %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Totale dei numeri della serie:            %5.1lu\n",range);
            if(option==CALC) {
               printf("Periodo selezionato:                 %10.1lu\n",com);
               printf("Totale dei valori selezionati:            %5.1u\n",dcount+pcount);
            }
            if(option!=DIVS&&option!=KEYS&&option!=NPRIM) {
               if(option==BASE)
                  printf("Totale dei numeri primi:                  %5.1u\n",sumprim);
               else
                  printf("Totale dei numeri primi:                  %5.1u\n",pcount);
            }
            if(option!=PRIME&&option!=GEMS) {
               if(option==BASE)
                  printf("Totale dei numeri divisibili:             %5.1u\n",sumdivs);
               else
                  printf("Totale dei numeri divisibili:             %5.1u\n",dcount);
            }
            if(option==NPRIM) {
               printf("Numeri divisibili dispari visualizzati:   %5.1u\n\n",oddcnt);
               return OK;
            }
            if(option==GEMS)
               printf("Numeri primi gemelli (Coppie):            %5.1u\n",gemcnt);
            if(option==KEYS)
               printf("Valori coerenti visualizzati:             %5.1u\n",keycnt);
            if(option!=PRIME&&option!=BASE&&option!=VARS
             &&option!=GEMS) {
               if(!(dcount+pcount)) hfatt=0;
               if((dcount+pcount)==1) hfatt=primenum(num);
               if(num==1&&limit==2) hfatt=0;
               if(num==2&&limit==3) hfatt=0;
               if(option==DIVS&&(subopt==DVS||subopt==DRW))
                  printf("Divisore iniziale più alto:           %9.1lu\n",hfatt);
               else
                  printf("Fattore primo iniziale più alto:      %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWOS&&option!=NSDIV)
             &&trueswitch()==TRUESW) {
               printf("Fattore primo selezionato:                %5.1lu\n",select);
               printf("Quantità di valori selezionati:           %5.1u\n",selcount);
            }
            if(trueoptions()==TWOS||option==PRIME
             ||option==STAT||(option==GEMS&&limit>4)) {
               if((limit-number)>1&&((number<=1&&limit>3)
                ||(number>1&&limit>2))) {
                  printf("Distanza massima tra due numeri primi:    %5.1u\n",hpdist);
                  printf("Distanza media tra due numeri primi:      %5.1u\n\n",pmdist);
                  return OK;
               }
               else {
                  putchar('\n');
                  return OK;
               }
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
            if(option==DIVS||option==KEYS||option==CALC||option==GEMS)
               putchar('\n');
         }
         else if(lang==ESPANOL) {
            if(option==STAT)
               printf("%s %s                  Informe resumido:\n",NAMEPROG,VERSION);
            else {
               if(option!=GEMS) printf("\n");
               printf("\n%s %s            Informe final resumido:\n",NAMEPROG,VERSION);
            }
            printf("-------------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Selección desde el número:             %10.1lu\n",number);
               if(option==BASE)
                  printf("Hasta el número:                       %10.1lu\n",limit);
               else
                  printf("Al número:                             %10.1lu\n",limit);
            }
            if(option==CALC)
               printf("Inicio de serie a partir del número:   %10.1lu\n",number);
            if(option==PRIME&&subopt==CNT) {
               printf("Selección desde la posición cardinal:   %9.1lu\n",cntbas);
               printf("Hasta la posición cardinal:             %9.1lu\n",cntlim);
            }
            if(option==KEYS||(option!=BASE&&option!=CALC
             &&option!=VARS&&option!=STAT)) {
               printf("Serie del número:                      %10.1lu\n",number);
               printf("Al número:                             %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Números totales de la serie:                %5.1lu\n",range);
            if(option==CALC) {
               printf("Período seleccionado:                  %10.1lu\n",com);
               printf("Total de números seleccionados:             %5.1u\n",dcount+pcount);
            }
            if(option!=DIVS&&option!=KEYS&&option!=NPRIM) {
               if(option==BASE)
                  printf("Números primos totales:                     %5.1u\n",sumprim);
               else
                  printf("Números primos totales:                     %5.1u\n",pcount);
            }
            if(option!=PRIME&&option!=GEMS) {
               if(option==BASE)
                  printf("Números divisibles totales:                 %5.1u\n",sumdivs);
               else
                  printf("Números divisibles totales:                 %5.1u\n",dcount);
            }
            if(option==NPRIM) {
               printf("Numeros divisibles impares mostrados:       %5.1u\n\n",oddcnt);
               return OK;
            }
            if(option==GEMS)
               printf("Números primos gemelos (Pares):             %5.1u\n",gemcnt);
            if(option==KEYS)
               printf("Valores consistentes mostrados:             %5.1u\n",keycnt);
            if(option!=PRIME&&option!=BASE&&option!=VARS
             &&option!=GEMS) {
               if(!(dcount+pcount)) hfatt=0;
               if((dcount+pcount)==1) hfatt=primenum(num);
               if(num==1&&limit==2) hfatt=0;
               if(num==2&&limit==3) hfatt=0;
               if(option==DIVS&&(subopt==DVS||subopt==DRW))
                  printf("Divisor inicial más alto:               %9.1lu\n",hfatt);
               else
                  printf("Factor primo inicial más alto:          %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWOS&&option!=NSDIV)
             &&trueswitch()==TRUESW) {
               printf("Factor primo seleccionado:                  %5.1lu\n",select);
               printf("Candidad de números seleccionados:          %5.1u\n",selcount);
            }
            if(trueoptions()==TWOS||option==PRIME
             ||option==STAT||(option==GEMS&&limit>4)) {
               if((limit-number)>1&&((number<=1&&limit>3)
                ||(number>1&&limit>2))) {
                  printf("Distancia maxima entre dos números primos:  %5.1u\n",hpdist);
                  printf("Distancia media entre dos números primos:   %5.1u\n\n",pmdist);
                  return OK;
               }
               else {
                  putchar('\n');
                  return OK;
               }
            }
            if(option==BASE) {
               statseries(npv);
               printf("Longitud de la serie numérica:              %5.1lu\n",range);
               printf("Numero de series numéricas:                 %5.1u\n",nseg);
               printf("Rango numérico de series:                   %5.1u\n",lseg);
               printf("Números primos promedio de la serie:        %5.1d\n",pmean);
               printf("Números divisibles promedio de la serie:    %5.1d\n",dmean);
               printf("Mínimo de números primos en las series:     %5.1u\n",pmin);
               printf("Máximo de números primos en las series:     %5.1u\n",pmax);
               printf("Minimo de números divisibles en las series: %5.1u\n",dmin);
               printf("Máximo de números divisibles en las series: %5.1u\n\n",dmax);
               return OK;
            }
            if(option==VARS) {
               printf("Factor primo seleccionado:                  %5.1lu\n",select);
               printf("Total de números mostrados:                 %5.1u\n\n",seltot);
               return OK;
            }
            if(option==DIVS||option==KEYS||option==CALC||option==GEMS)
               putchar('\n');
         }
         else if(lang==FRANCAIS) {
            if(option==STAT)
               printf("%s %s                  Rapport de synthèse:\n",NAMEPROG,VERSION);
            else {
               if(option!=GEMS) printf("\n");
               printf("\n%s %s            Rapport de synthèse final:\n",NAMEPROG,VERSION);
            }
            printf("----------------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Sélection dal numéro :                    %10.1lu\n",number);
               if(option==BASE)
                  printf("Jusqu'au numéro :                         %10.1lu\n",limit);
               else
                  printf("Au numéro :                               %10.1lu\n",limit);
            }
            if(option==CALC)
               printf("Début de la série à partir du numéro :    %10.1lu\n",number);
            if(option==PRIME&&subopt==CNT) {
               printf("Sélection à partir de la position :        %9.1lu\n",cntbas);
               printf("Jusqu'à la position cardinale :            %9.1lu\n",cntlim);
            }
            if(option==KEYS||(option!=BASE&&option!=CALC
             &&option!=VARS&&option!=STAT)) {
               printf("Serie à partir du numéro :                %10.1lu\n",number);
               printf("Au numero :                               %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Nombre total de titres dans la série :         %5.1lu\n",range);
            if(option==CALC) {
               printf("Période selectionnée :                    %10.1lu\n",com);
               printf("Nombres total sélectionné :                    %5.1u\n",dcount+pcount);
            }
            if(option!=DIVS&&option!=KEYS&&option!=NPRIM) {
               if(option==BASE)
                  printf("Nombres premiers totaux :                      %5.1u\n",sumprim);
               else
                  printf("Nombres premiers totaux :                      %5.1u\n",pcount);
            }
            if(option!=PRIME&&option!=GEMS) {
               if(option==BASE)
                  printf("Nombres totaux divisibles :                    %5.1u\n",sumdivs);
               else
                  printf("Nombres totaux divisibles :                    %5.1u\n",dcount);
            }
            if(option==NPRIM) {
               printf("Nombres divisibles impairs affichés :          %5.1u\n\n",oddcnt);
               return OK;
            }
            if(option==GEMS)
               printf("Nombres premiers jumeaux (paires) :            %5.1u\n",gemcnt);
            if(option==KEYS)
               printf("Valeurs cohérentes affichées :                 %5.1u\n",keycnt);
            if(option!=PRIME&&option!=BASE&&option!=VARS
             &&option!=GEMS) {
               if(!(dcount+pcount)) hfatt=0;
               if((dcount+pcount)==1) hfatt=primenum(num);
               if(num==1&&limit==2) hfatt=0;
               if(num==2&&limit==3) hfatt=0;
               if(option==DIVS&&(subopt==DVS||subopt==DRW))
                  printf("Diviseur initial le plus élevé :           %9.1lu\n",hfatt);
               else
                  printf("Facteur premier initial le plus élevé :    %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWOS&&option!=NSDIV)
             &&trueswitch()==TRUESW) {
               printf("Facteur premier sélectionné :                  %5.1lu\n",select);
               printf("Quantité de numéros sélectionnés :             %5.1u\n",selcount);
            }
            if(trueoptions()==TWOS||option==PRIME
             ||option==STAT||(option==GEMS&&limit>4)) {
               if((limit-number)>1&&((number<=1&&limit>3)
                ||(number>1&&limit>2))) {
                  printf("Distance maximale entre nombres premiers :     %5.1u\n",hpdist);
                  printf("Distance moyenne entre nombres premiers :      %5.1u\n\n",pmdist);
                  return OK;
               }
               else {
                  putchar('\n');
                  return OK;
               }
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
            if(option==DIVS||option==KEYS||option==CALC||option==GEMS)
               putchar('\n');
         }
         else if(lang==PORTUGUES) {
            if(option==STAT)
               printf("%s %s             Relatório resumido:\n",NAMEPROG,VERSION);
            else {
               if(option!=GEMS) printf("\n");
               printf("\n%s %s       Relatório resumido final:\n",NAMEPROG,VERSION);
            }
            printf("----------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Seleção por número:                 %10.1lu\n",number);
               if(option==BASE)
                  printf("Até o número:                       %10.1lu\n",limit);
               else
                  printf("Ao número:                          %10.1lu\n",limit);
            }
            if(option==CALC)
               printf("Início da série a partir do número: %10.1lu\n",number);
            if(option==PRIME&&subopt==CNT) {
               printf("Seleção a partir da posição:         %9.1lu\n",cntbas);
               printf("Até a posição cardinal:              %9.1lu\n",cntlim);
            }
            if(option==KEYS||(option!=BASE&&option!=CALC
             &&option!=VARS&&option!=STAT)) {
               printf("Série a partir do número:           %10.1lu\n",number);
               printf("Ao numero:                          %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Número total de itens na série:          %5.1lu\n",range);
            if(option==CALC) {
               printf("Periodo selecionados:               %10.1lu\n",com);
               printf("Total de números selecionados:           %5.1u\n",dcount+pcount);
            }
            if(option!=DIVS&&option!=KEYS&&option!=NPRIM) {
               if(option==BASE)
                  printf("Numeros primos totais:                   %5.1u\n",sumprim);
               else
                  printf("Numeros primos totais:                   %5.1u\n",pcount);
            }
            if(option!=PRIME&&option!=GEMS) {
               if(option==BASE)
                  printf("Números divisíveis totais:               %5.1u\n",sumdivs);
               else
                  printf("Números divisíveis totais:               %5.1u\n",dcount);
            }
            if(option==NPRIM) {
               printf("Números ímpares divisívies exibidos:     %5.1u\n\n",oddcnt);
               return OK;
            }
            if(option==GEMS)
               printf("Números primos gêmeos (pares):           %5.1u\n",gemcnt);
            if(option==KEYS)
               printf("Valores consistentes exibidos:           %5.1u\n",keycnt);
            if(option!=PRIME&&option!=BASE&&option!=VARS
             &&option!=GEMS) {
               if(!(dcount+pcount)) hfatt=0;
               if((dcount+pcount)==1) hfatt=primenum(num);
               if(num==1&&limit==2) hfatt=0;
               if(num==2&&limit==3) hfatt=0;
               if(option==DIVS&&(subopt==DVS||subopt==DRW))
                  printf("Divisor inicial mais alto:           %9.1lu\n",hfatt);
               else
                  printf("Maior factor primo inicial:          %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWOS&&option!=NSDIV)
             &&trueswitch()==TRUESW) {
               printf("Factor primo selecionado:                %5.1lu\n",select);
               printf("Quantidade de números selecionados:      %5.1u\n",selcount);
            }
            if(trueoptions()==TWOS||option==PRIME
             ||option==STAT||(option==GEMS&&limit>4)) {
               if((limit-number)>1&&((number<=1&&limit>3)
                ||(number>1&&limit>2))) {
                  printf("Distância máxima entre números primos:   %5.1u\n",hpdist);
                  printf("Distância media entre números primos:    %5.1u\n\n",pmdist);
                  return OK;
               }
               else {
                  putchar('\n');
                  return OK;
               }
            }
            if(option==BASE) {
               statseries(npv);
               printf("Comprimento da série numérica:           %5.1lu\n",range);
               printf("Número de séries numéricas:              %5.1u\n",nseg);
               printf("Intervalo numérico de séries:            %5.1u\n",lseg);
               printf("Média dos núme divisíveis da série:      %5.1d\n",pmean);
               printf("Média dos números primos da série:       %5.1d\n",dmean);
               printf("Minimo de números primos na série:       %5.1u\n",pmin);
               printf("Máximo de números primos na série:       %5.1u\n",pmax);
               printf("Minimo de números divisíveis na série:   %5.1u\n",dmin);
               printf("Máximo de números divisíveis na série:   %5.1u\n\n",dmax);
               return OK;
            }
            if(option==VARS) {
               printf("Factor primo selecionado:                %5.1lu\n",select);
               printf("Total de números exibidos:               %5.1u\n\n",seltot);
               return OK;
            }
            if(option==DIVS||option==KEYS||option==CALC||option==GEMS)
               putchar('\n');
         }
         else if(lang==DEUTCHE) {
            if(option==STAT)
               printf("%s %s             Zusammenfassender Bericht:\n",NAMEPROG,VERSION);
            else {
               if(option!=GEMS) printf("\n");
               printf("\n%s %s                      Abschlussbericht:\n",NAMEPROG,VERSION);
            }
            printf("-----------------------------------------------------\n");
            if(option==STAT||option==VARS||option==BASE) {
               printf("Auswahl aus Nummer:                        %10.1lu\n",number);
               if(option==BASE)
                  printf("Bis zur Nummer:                            %10.1lu\n",limit);
               else
                  printf("Unter der Nummer:                          %10.1lu\n",limit);
            }
            if(option==CALC)
               printf("Beginn der Serie ab Nummer:                %10.1lu\n",number);
            if(option==PRIME&&subopt==CNT) {
               printf("Auswahl aus der Kardinalposition:           %9.1lu\n",cntbas);
               printf("Bis zur Kardinalposition:                   %9.1lu\n",cntlim);
            }
            if(option==KEYS||(option!=BASE&&option!=CALC
             &&option!=VARS&&option!=STAT)) {
               printf("Serie ab Nummer:                           %10.1lu\n",number);
               printf("Bis zur Nummer:                            %10.1lu\n",limit);
            }
            if(option!=BASE&&option!=CALC)
               printf("Gesamtzahlen in der Reihe:                      %5.1lu\n",range);
            if(option==CALC) {
               printf("Ausgewählter Zeitraum:                     %10.1lu\n",com);
               printf("Gesamtzahl ausgewählt:                          %5.1u\n",dcount+pcount);
            }
            if(option!=DIVS&&option!=KEYS&&option!=NPRIM) {
               if(option==BASE)
                  printf("Gesamtzahl der Primzahlen:                      %5.1u\n",sumprim);
               else
                  printf("Gesamtzahl der Primzahlen:                      %5.1u\n",pcount);
            }
            if(option!=PRIME&&option!=GEMS) {
               if(option==BASE)
                  printf("Gesamte teilbare Zahlen:                        %5.1u\n",sumdivs);
               else
                  printf("Gesamte teilbare Zahlen:                        %5.1u\n",dcount);
            }
            if(option==NPRIM) {
               printf("Angezeigte ungerade teilbare Zalhen:            %5.1u\n\n",oddcnt);
               return OK;
            }
            if(option==GEMS)
               printf("Zwillingsprimzahlen (paare):                    %5.1u\n",gemcnt);
            if(option==KEYS)
               printf("Konsistente Werte angezeigt:                    %5.1u\n",keycnt);
            if(option!=PRIME&&option!=BASE&&option!=VARS
             &&option!=GEMS) {
               if(!(dcount+pcount)) hfatt=0;
               if((dcount+pcount)==1) hfatt=primenum(num);
               if(num==1&&limit==2) hfatt=0;
               if(num==2&&limit==3) hfatt=0;
               if(option==DIVS&&(subopt==DVS||subopt==DRW))
                  printf("Höchster anfängsteiler:                     %9.1lu\n",hfatt);
               else
                  printf("Höchste anfänglicher Primfaktor:            %9.1lu\n",hfatt);
            }
            if((trueoptions()<=TWOS&&option!=NSDIV)
             &&trueswitch()==TRUESW) {
               printf("Ausgewählter Primfactor:                        %5.1lu\n",select);
               printf("Anzahl der ausgewählten numerischen Faktoren:   %5.1u\n",selcount);
            }
            if(trueoptions()==TWOS||option==PRIME
             ||option==STAT||(option==GEMS&&limit>4)) {
               if((limit-number)>1&&((number<=1&&limit>3)
                ||(number>1&&limit>2))) {
                  printf("Maximaler Abstand zwischen Primzahlen:          %5.1u\n",hpdist);
                  printf("Durchschnittlicher Abstand zwischen Primzahlen: %5.1u\n\n",pmdist);
                  return OK;
               }
               else {
                  putchar('\n');
                  return OK;
               }
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
            if(option==DIVS||option==KEYS||option==CALC||option==GEMS)
               putchar('\n');
         }
         else {

         /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
         /* delle funzionalità interne, delle opzioni e degli Switch. */
            if(fsign) {
               printf("ERROR [NOT_LNG] GURU MEDITATION\n");
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
      printf("~© (2010-2026) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Written by G. B. alias PiErre60\n");
      printf(" with the collaboration of:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("To use: %s --help For extended help.\n",argz);
      printf("     or %s --help | less  (Alternative view.)\n",argz);
      printf("     or %s -h     For quick help.\n",argz);
      printf("     or %s -?     For author and license info.\n",argz);
      printf("     or %s -?I    For start user guide.\n",argz);
      printf("     or %s -?M    For user manual.\n",argz);
      printf("     or %s -?O    For options reference table.\n\n",argz);
      return;
   }
   if(*flang==ITALIANO) {
      printf("\n%s        Versione: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2026) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Scritto da G. B. alias PiErre60\n");
      printf(" con la collaborazione di:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Usare: %s --help Per ottenere un aiuto dettagliato.\n",argz);
      printf("     o %s --help | less  (Visualizzazione alternativa.)\n",argz);
      printf("     o %s -h     Per ottenere un aiuto rapido.\n",argz);
      printf("     o %s -?     Per info autore e licenza.\n",argz);
      printf("     o %s -?I    Per guida d'uso rapida.\n",argz);
      printf("     o %s -?M    Per manuale d'uso.\n",argz);
      printf("     o %s -?O    Per tabella di riferimento opzioni.\n\n",argz);
      return;
   }
   if(*flang==ESPANOL) {
      printf("\n%s         Versión: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2026) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Escrito por G.B. alias PiErre60\n");
      printf(" con la colaboración de:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Usar: %s --help Para ayuda detallada.\n",argz);
      printf("    o %s --help | less  (Visión alternativa.)\n",argz);
      printf("    o %s -h     Para ayuda rápida.\n",argz);
      printf("    o %s -?     Para info sobre el autor y licencia.\n",argz);
      printf("    o %s -?I    Para una guida de usuario rápida.\n",argz);
      printf("    o %s -?M    Para el manual de usuario.\n",argz);
      printf("    o %s -?O    Para la tabla de referencia de opciones.\n\n",argz);
      return;
   }
   if(*flang==FRANCAIS) {
      printf("\n%s        Version : %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2026) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Ecrit par G. B.  alias PiErre60\n");
      printf(" avec la collaboration de :\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Utiliser : %s --help Pour une aide détaillée.\n",argz);
      printf("        ou %s --help | less  (Point de vue alternatif.)\n",argz);
      printf("        ou %s -h     Pour une aide rapide.\n",argz);
      printf("        ou %s -?     Pour informations sur auteur et licence.\n",argz);
      printf("        ou %s -?I    Pour un guide d'utilisation rapide.\n",argz);
      printf("        ou %s -?M    Pour le manuel d'utilisation.\n",argz);
      printf("        ou %s -?O    Pour tabeleau de réference des options.\n\n",argz);
      return;
   }
   if(*flang==PORTUGUES) {
      printf("\n%s          Versão: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2026) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Escrito por G.B. alias PiErre60\n");
      printf(" com a colaboração de:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Usar: %s --help Para ajuda detalhada.\n",argz);
      printf("   ou %s --help | less  (Visão alternativa.)\n",argz);
      printf("   ou %s -h     Para ajuda rapida.\n",argz);
      printf("   ou %s -?     Para infos sobre autor e licença.\n",argz);
      printf("   ou %s -?I    Para um guia rápido do usuário.\n",argz);
      printf("   ou %s -?M    Para o manual do usuário.\n",argz);
      printf("   ou %s -?O    Para a tabela de referência de opções.\n\n",argz);
      return;
   }
   if(*flang==DEUTCHE) {
      printf("\n%s         Version: %s\n",argz,verrez);
      printf("-------------------------------\n");
      printf("~© (2010-2026) - GNU/GPL vers.3\n");
      printf(" (FSF) Free Software Foundation\n");
      printf("Geschrieben von G.B. (PiErre60)\n");
      printf(" in Zusammenarbeit mit:\n");
      printf(" A. F. F. alias Ferro811\n\n");
      printf("Verwenden: %s --help Für ausführliche Hilfe.\n",argz);
      printf("      oder %s --help | less  (Alternative Sichtweise.)\n",argz);
      printf("      oder %s -h     Für schnelle Hilfe.\n",argz);
      printf("      oder %s -?     Für Autoren und Lizenzinformationen.\n",argz);
      printf("      oder %s -?I    Für die Kurzanleitung.\n",argz);
      printf("      oder %s -?M    Zur Bedienungsanleitung.\n",argz);
      printf("      oder %s -?O    Zur Optionsreferenztabelle.\n\n",argz);
      return;
   }
}
/* Fine della funzione about(). */


/* --------------------- */
/* Funzione quickhelp(). */
void quickhelp(short *flang,char *argz) {
   if(*flang==ENGLISH) {
      printf("\nTo use: %s --help  For extended help,\n",argz);
      printf("     or %s --help | less  For an alternative help display mode.\n",argz);
      printf("     or %s [option] [marker/switch] [num_arg_1] [num_arg_2] [num_arg_3]\n",argz);
      printf("                 For operative mode.\n\n");
      printf(" Options: [-a] [-s, -f, -y] [-d, -q] [-p, -l] [-n] [-k, -e] [-g, -j] [-t] [-b, -v, -c]\n");
      printf(" Markers: [P, S, U, D]\n");
      printf("Switches: [T] [L] [V, W] [N, R] [C, B] [I, M, O]\n");
      printf("  Locale: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Examples: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("          %s -t 32768  98303              %s -a 16385  81920 \n",argz,argz);
      printf("          %s 100 65635 | more             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("          %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("          %s -f 50250 102500              %s -k 12345 59999\n",argz,argz);
      printf("          %s -g 12345 69999               %s -p 1000 9999\n",argz,argz);
      printf("          %s -d 1000 9999                 %s -j 5000 70000\n",argz,argz);
      printf("          %s -e 5000 70000                %s -l 1535 65000\n",argz,argz);
      printf("          %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("          %s -pN 200 65735                %s -lN 200 65735\n",argz,argz);
      printf("          %s -lR 500 66000                %s -pC 100 4195\n",argz,argz);
      printf("          %s -lC 100 4195                 %s -lB 100 4195\n",argz,argz);
      printf("          %s -fS 123 9999 5               %s -b 1001 5000 16\n",argz,argz);
      printf("          %s -c 1001 5000 7               %s -v 2500 2999 7\n",argz,argz);
      printf("          %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("          %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("          %s -dV 200 230                  %s -dW 2900 2930\n",argz,argz);
      printf("          %s -qR 34000 99535              less < $HOME/pcont\n\n",argz);
      return;
   }
   if(*flang==ITALIANO) {
      printf("\nUsare: %s --help  Per aiuto dettagliato,\n",argz);
      printf("     o %s --help | less  Per modo di visualizzazione alternativo dell'aiuto.\n",argz);
      printf("oppure %s [opzione] [marcatore/commutatore] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("                Per modalità operativa.\n\n");
      printf("      Opzioni: [-a] [-s, -f, -y] [-d, -q] [-p, -l] [-n] [-k, -e] [-g, -j] [-t] [-b, -v, -c]\n");
      printf("    Marcatori: [P, S, U, D]\n");
      printf("  Commutatori: [T] [L] [V, W] [N, R] [C, B] [I, M, O]\n");
      printf("Lingua locale: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Esempi: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("        %s -t 32768  98303              %s -a 16385  81920 \n",argz,argz);
      printf("        %s 100 65635 | more             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("        %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("        %s -f 50250 102500              %s -k 12345 59999\n",argz,argz);
      printf("        %s -g 12345 69999               %s -p 1000 9999\n",argz,argz);
      printf("        %s -d 1000 9999                 %s -j 5000 70000\n",argz,argz);
      printf("        %s -e 5000 70000                %s -l 1535 65000\n",argz,argz);
      printf("        %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("        %s -pN 200 65735                %s -lN 200 65735\n",argz,argz);
      printf("        %s -lR 500 66000                %s -pC 100 4195\n",argz,argz);
      printf("        %s -lC 100 4195                 %s -lB 100 4195\n",argz,argz);
      printf("        %s -fS 123 9999 5               %s -b 1001 5000 16\n",argz,argz);
      printf("        %s -c 1001 5000 7               %s -v 2500 2999 7\n",argz,argz);
      printf("        %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("        %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("        %s -dV 200 230                  %s -dW 2900 2930\n",argz,argz);
      printf("        %s -qR 34000 99535              less < $HOME/pcont\n\n",argz);
      return;
   }
   if(*flang==ESPANOL) {
      printf("\nUsar: %s --help  Para obtener ayuda detallada,\n",argz);
      printf("    o %s --help | less  Para una forma alternativa de mostrar la ayuda.\n",argz);
      printf("    o %s [option] [marcador/interruptor] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("               Por modo de funcionamiento.\n\n");
      printf("     Opciones: [-a] [-s, -f, -y] [-d, -q] [-p, -l] [-n] [-k, -e] [-g, -j] [-t] [-b, -v, -c]\n");
      printf("   Marcadores: [P, S, U, D]\n");
      printf("Interruptores: [T] [L] [V, W] [N, R] [C, B] [I, M, O]\n");
      printf(" Idioma local: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Ejemplos: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("          %s -t 32768  98303              %s -a 16385  81920 \n",argz,argz);
      printf("          %s 100 65635 | more             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("          %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("          %s -f 50250 102500              %s -k 12345 59999\n",argz,argz);
      printf("          %s -g 12345 69999               %s -p 1000 9999\n",argz,argz);
      printf("          %s -d 1000 9999                 %s -j 5000 70000\n",argz,argz);
      printf("          %s -e 5000 70000                %s -l 1535 65000\n",argz,argz);
      printf("          %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("          %s -pN 200 65735                %s -lN 200 65735\n",argz,argz);
      printf("          %s -lR 500 66000                %s -pC 100 4195\n",argz,argz);
      printf("          %s -lC 100 4195                 %s -lB 100 4195\n",argz,argz);
      printf("          %s -fS 123 9999 5               %s -b 1001 5000 16\n",argz,argz);
      printf("          %s -c 1001 5000 7               %s -v 2500 2999 7\n",argz,argz);
      printf("          %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("          %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("          %s -dV 200 230                  %s -dW 2900 2930\n",argz,argz);
      printf("          %s -qR 34000 99535              less < $HOME/pcont\n\n",argz);
      return;
   }
   if(*flang==FRANCAIS) {
      printf("\nUtiliser : %s --help  Pour une aide détaillée.\n",argz);
      printf("        ou %s --help | less  Pour une autre façon d'afficher d'aide.\n",argz);
      printf("        ou %s [option] [signaleur/interrupteur] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("                    Par mode de fonctionnement.\n\n");
      printf(" Possibilités : [-a] [-s, -f, -y] [-d, -q] [-p, -l] [-n] [-k, -e] [-g, -j] [-t] [-b, -v, -c]\n");
      printf("    Marqueurs : [P, S, U, D]\n");
      printf("Interrupteurs : [T] [L] [V, W] [N, R] [C, B] [I, M, O]\n");
      printf("Langue locale : [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Exemples : %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("           %s -t 32768  98303              %s -a 16385  81920 \n",argz,argz);
      printf("           %s 100 65635 | more             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("           %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("           %s -f 50250 102500              %s -k 12345 59999\n",argz,argz);
      printf("           %s -g 12345 69999               %s -p 1000 9999\n",argz,argz);
      printf("           %s -d 1000 9999                 %s -j 5000 70000\n",argz,argz);
      printf("           %s -e 5000 70000                %s -l 1535 65000\n",argz,argz);
      printf("           %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("           %s -pN 200 65735                %s -lN 200 65735\n",argz,argz);
      printf("           %s -lR 500 66000                %s -pC 100 4195\n",argz,argz);
      printf("           %s -lC 100 4195                 %s -lB 100 4195\n",argz,argz);
      printf("           %s -fS 123 9999 5               %s -b 1001 5000 16\n",argz,argz);
      printf("           %s -c 1001 5000 7               %s -v 2500 2999 7\n",argz,argz);
      printf("           %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("           %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("           %s -dV 200 230                  %s -dW 2900 2930\n",argz,argz);
      printf("           %s -qR 34000 99535              less < $HOME/pcont\n\n",argz);
      return;
   }
   if(*flang==PORTUGUES) {
      printf("\nTo use: %s --help  Para ajuda detalhada.\n",argz);
      printf("     ou %s --help | less  Para uma forma alternativa de exibir a ajuda.\n",argz);
      printf("     ou %s [option] [sinalizador/interruptor] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("                 Por modo de operação.\n\n");
      printf("       Opções: [-a] [-s, -f, -y] [-d, -q] [-p, -l] [-n] [-k, -e] [-g, -j] [-t] [-b, -v, -c]\n");
      printf("   Marcadores: [P, S, U, D]\n");
      printf("Interruptores: [T] [L] [V, W] [N, R] [C, B] [I, M, O]\n");
      printf(" Lingua local: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Exemplos: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("          %s -t 32768  98303              %s -a 16385  81920 \n",argz,argz);
      printf("          %s 100 65635 | more             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("          %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("          %s -f 50250 102500              %s -k 12345 59999\n",argz,argz);
      printf("          %s -g 12345 69999               %s -p 1000 9999\n",argz,argz);
      printf("          %s -d 1000 9999                 %s -j 5000 70000\n",argz,argz);
      printf("          %s -e 5000 70000                %s -l 1535 65000\n",argz,argz);
      printf("          %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("          %s -pN 200 65735                %s -lN 200 65735\n",argz,argz);
      printf("          %s -lR 500 66000                %s -pC 100 4195\n",argz,argz);
      printf("          %s -lC 100 4195                 %s -lB 100 4195\n",argz,argz);
      printf("          %s -fS 123 9999 5               %s -b 1001 5000 16\n",argz,argz);
      printf("          %s -c 1001 5000 7               %s -v 2500 2999 7\n",argz,argz);
      printf("          %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("          %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("          %s -dV 200 230                  %s -dW 2900 2930\n",argz,argz);
      printf("          %s -qR 34000 99535              less < $HOME/pcont\n\n",argz);
      return;
   }
   if(*flang==DEUTCHE) {
      printf("\nVerwenden: %s --help  Für ausführliche Hilfe.\n",argz);
      printf("      oder %s --help | less  Für eine alternative Art der Hilfeanzeige.\n",argz);
      printf("      oder %s [option] [signalgerber/shalten] [zahl_arg_1] [zahl_arg_2] [zahl_arg_3]\n",argz);
      printf("                    Natch Betriebsart.\n\n");
      printf("     Optionen: [-a] [-s, -f, -y] [-d, -q] [-p, -l] [-n] [-k, -e] [-g, -j] [-t] [-b, -v, -c]\n");
      printf(" Markierungen: [P, S, U, D]\n");
      printf("      Shalter: [T] [L] [V, W] [N, R] [C, B] [I, M, O]\n");
      printf("Landessprache: [IT, EN, ES, FR, PT, DE]\n\n");
      printf("Beispiele: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("           %s -t 32768  98303              %s -a 16385  81920 \n",argz,argz);
      printf("           %s 100 65635 | more             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("           %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("           %s -f 50250 102500              %s -k 12345 59999\n",argz,argz);
      printf("           %s -g 12345 69999               %s -p 1000 9999\n",argz,argz);
      printf("           %s -d 1000 9999                 %s -j 5000 70000\n",argz,argz);
      printf("           %s -e 5000 70000                %s -l 1535 65000\n",argz,argz);
      printf("           %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("           %s -pN 200 65735                %s -lN 200 65735\n",argz,argz);
      printf("           %s -lR 500 66000                %s -pC 100 4195\n",argz,argz);
      printf("           %s -lC 100 4195                 %s -lB 100 4195\n",argz,argz);
      printf("           %s -fS 123 9999 5               %s -b 1001 5000 16\n",argz,argz);
      printf("           %s -c 1001 5000 7               %s -v 2500 2999 7\n",argz,argz);
      printf("           %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("           %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("           %s -dV 200 230                  %s -dW 2900 2930\n",argz,argz);
      printf("           %s -qR 34000 99535              less < $HOME/pcont\n\n",argz);
      return;
   }
}
/* Fine della funzione quickhelp(). */


/* ***************************************************************************** */
/* Funzione helpfunc(). */
void helpfunc(short *flang,char *argz,char *verrez) {

   /* AIUTO ESTESO IN INGLESE, ITALIANO, SPAGNOLO, FRANCESE, PORTOGHESE, TEDESCO */
   if(*flang==ENGLISH) {
      printf("\n%s   Release: %s",argz,verrez);
      printf("\n~© (2010-2026) - F.S.F. GNU/GPL vers.3\n");
      printf("\nTo use: %s      About.\n",argz);
      printf("        %s -?   Author and license information.\n",argz);
      printf("        %s -?M  User manual.\n",argz);
      printf("        %s -?I  Quick start Guide\n",argz);
      printf("        %s -?O  Reference table for options.\n",argz);
      printf("        %s -h   Quick help.\n",argz);
      printf("        %s --help  This detailed help.\n",argz);
      printf("        %s --help | less  Detailed help (Alternative view).\n",argz);
      printf("        %s EN, IT, ES, FR, PT, DE  Local language selection.\n",argz);
      printf("        %s [num_arg]\n",argz);
      printf("        %s [num_arg_1] [num_arg_2]\n",argz);
      printf("        %s [option] [marker/switch] [num_arg_1] [num_arg_2]\n",argz);
      printf("        %s [option] [marker/switch] [num_arg_1] [num_arg_2] [num_arg_3]\n",argz);
      printf("\n Options: [-a]  [-s, -f, -y]  [-d, -q]  [-p, -l]  [-n]  [-k, -e]  [-g, -j]  [-t]  [-b, -v, -c]");
      printf("\n Markers: [P, S, U, D]  [T]");
      printf("\nSwitches: [L]  [V, W]  [N, R]  [C, B]  [I, M, O]\n");
      printf("\nSynopsis: %s [-a | -f | -s | -y | -d | -p | -n | -k | -g | -j | -e | -t]  [num_value_1] [num_value_2]\n",argz);
      printf("          %s [-a | -p | -n | -l | -q | -j | -e]  [L | T | N | R | C | B]  [num_value_1] [num_value_2]\n",argz);
      printf("          %s [-f | -s | -y | -d | -k]  [P | S | U | D]  [[num_value_1] [num_value_2]] [num_value_3]\n",argz);
      printf("          %s [-b | -v | -c]  [num_value_1] [num_value_2] [num_value_3]\n\n",argz);
      printf("        [num_value_1] = Initial element of the numerical series.\n");
      printf("        [num_value_2] = Final element of the numerical series./Discriminant value for the series.\n");
      printf("        [num_value_3] = Discriminant value for displaying the series.\n");
      printf("\nOptions: -a  Series of prime numbers and their decomposition factors displayed in standard notation.\n");
      printf("         -s  Prime factors of a series decomposition displayed individually.\n");
      printf("         -y  Single displayed prime factor of a numerical series.\n");
      printf("         -f  Prime factors of a series displayed in standard notation.\n");
      printf("         -p  Series of only prime numbers displayed in standard notation.\n");
      printf("         -d  Series of only prime decomposition factors displayed in standard notation.\n");
      printf("         -k  Filters out values in a series that have only two prime factors of decomposition.\n");
      printf("         -g  Filters out in a series only the twin primes displayed in pairs.\n");
      printf("         -l  Numerical series of only prime numbers, displayed without statistical relationship.\n");
      printf("         -q  Numerical series of only prime factor of decomposition, without statistical relationship.\n");
      printf("         -e  Series of value with two decomposition factors, displayed without statistical relationship.\n");
      printf("         -j  Serie of only twin prime numbers, displayed without statistical relationship.\n");
      printf("         -n  Numerical series of divisible values with positional marking of the prime numbers.\n");
      printf("         -t  Statistical report of the indicated numerical series.\n");
      printf("         -b  Decomposition into N numerical series as a function of a given numerical series.\n");
      printf("         -v  Selective series of values for an arbitrary divisibility factor.\n");
      printf("         -c  Series of values defined from A to B positions of N elements.\n");
      printf("\nSpecial options: -clr  Delete the language configuration file.\n");
      printf("                 -rst  Reset to default language. (1)\n");
      printf("                 -rst  Restore the initial mode. (2)\n");
      printf("        (1)(2) - The functionality changes depending on the presence\n");
      printf("                 or absence of the configuration file.\n");
      printf("\nMarkers: P  Marking of the prime numbers of the displayed number series.\n");
      printf("         S  Marking of a prime factor of decomposition in the displayed numerical series.\n");
      printf("         U  Ascending marking from a prime factor indicadedin the displayed number series.\n");
      printf("         D  Descending marking from a prime factor indicated in the displayed number series.\n");
      printf("\nSwitches: L  Changes the justification of the list, suitable for appending series to files.\n");
      printf("          N  It allows you to visualize the cardinal position of prime numbers.\n");
      printf("          C  It allow you to find the prime numbers corresponding to their cardinal position.\n");
      printf("          R  Similar to N o V, but suitable for generating series queued to files.\n");
      printf("          B  Similar to C, but suitable for generating series queued to files.\n");
      printf("          V  Allow you to calculate and display all the divisibility factors of a number.\n");
      printf("          W  Identical to V, with the addition of the ability to choose the justification.\n");
      printf("\nJustified indent display options:\n");
      printf("         -lL  Visualizing a series of only prime numbers.\n");
      printf("         -qL  Displaying a series of divisible numbers and prime factors of decomposition.\n");
      printf("         -eL  Displaying a series of values with only two factorizations.\n");
      printf("         -jL  Visualization of a series of twin prime numbers.\n");
      printf("\nTabular view options:\n");
      printf("         -nT  Display in the numerical series only numbers that are divisible into multiple columns.\n");
      printf("         -pT  Display only prime numbers in the numerical series in multiple columns.\n");
      printf("\nAdditional location display options:\n");
      printf("         -pC  Visualizing a prime number by indicating its cardinal position.\n");
      printf("         -lC  Displaying prime numbers from a given set of cardinal positions.\n");
      printf("         -lB  Display of prime numbers and their cardinal positions from a given series.\n");
      printf("         -lR  Display of the indicated series of prime numbers and their respective cardinal positions.\n");
      printf("         -pN  Display the cardinal position of a given prime number.\n");
      printf("         -lN  Displaying of the cardinal position of the prime numbers of the given series.\n");
      printf("\nOptions for additional features:\n");
      printf("         -dV  Display the divisibility factors of each number in the specified series.\n");
      printf("         -qV  Displays a list of divisibility factors for each number; suitable for lists in files.\n");
      printf("         -dW  Displays the list of divisibility factors; allows the justification to be changed.\n");
      printf("         -qR  Displays the list of divisibility factors; suitable for series queued to file.\n");
      printf("\nExamples: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("          %s -t 32768  98303              %s -a 16385  81920\n",argz,argz);
      printf("          %s 100 65635 | less             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("          %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("          %s -l 10 65545 > $HOME/prime    %s -q 10 65545 > $HOME/pfact\n",argz,argz);
      printf("          %s -y 1000 75535                %s -f 1234 9999\n",argz,argz);
      printf("          %s -k 1234 59999                %s -g 1000 50000\n",argz,argz);
      printf("          %s -d 1000 9999                 %s -p 1000 9999\n",argz,argz);
      printf("          %s -j 5000 70000                %s -e 5000 70000\n",argz,argz);
      printf("          %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("          %s -pN 200 65735                %s -pC 100 4195\n",argz,argz);
      printf("          %s -lC 100 4195                 %s -lL 100 65000\n",argz,argz);
      printf("          %s -lN 100 65000                %s -qL 150 65500\n",argz,argz);
      printf("          %s -jL 150 65675                %s -eL 150 65675\n",argz,argz);
      printf("          %s -fP 1234 39999 5             %s -fS 1234 39999 5\n",argz,argz);
      printf("          %s -yS 1234 39999 5             %s -sU 12345 39999 13\n",argz,argz);
      printf("          %s -b 1001 5000 16              %s -c 1001 5000 7\n",argz,argz);
      printf("          %s -v 2500 2999 7               %s -lB 1000 5095\n",argz,argz);
      printf("          %s -dV 290 2900                 %s -qV 29000 94535\n",argz,argz);
      printf("          %s -dW 2900 29300               %s -qR 34000 99535\n",argz,argz);
      printf("          %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("          %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("          less < $HOME/pcont\n\n");
      return;
   }

   /* *********************************************************************** */
   if(*flang==ITALIANO) {
      printf("\n%s   Versione: %s",argz,verrez);
      printf("\n~© (2010-2026) - F.S.F. GNU/GPL vers.3\n");
      printf("\nUsare: %s      Presentazione.\n",argz);
      printf("       %s -?   Informazioni su autore e licenza.\n",argz);
      printf("       %s -?M  Manuale d'uso.\n",argz);
      printf("       %s -?I  Guida d'uso rapida.\n",argz);
      printf("       %s -?O  Tabella di riferimento per le opzioni.\n",argz);
      printf("       %s -h   Aiuto rapido.\n",argz);
      printf("       %s --help  Questo aiuto dettagliato.\n",argz);
      printf("       %s --help | less  Aiuto dettagliato (Visualizzazione alternativa).\n",argz);
      printf("       %s IT, EN, ES, FR, PT, DE  Selezione della lingua locale.\n",argz);
      printf("       %s [arg_num]\n",argz);
      printf("       %s [arg_num_1] [arg_num_2]\n",argz);
      printf("       %s [opzione] [marcatore/commutatore] [arg_num_1] [arg_num_2]\n",argz);
      printf("       %s [opzione] [marcatore/commutatore] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("\n    Opzioni: [-a]  [-s, -f, -y]  [-d, -q]  [-p, -l]  [-n]  [-k, -e]  [-g, -j]  [-t]  [-b, -v, -c]");
      printf("\n  Marcatori: [P, S, U, D]");
      printf("\nCommutatori: [T]  [L]  [V, W]  [N, R]  [C, B]  [I, M, O]\n");
      printf("\nSinossi: %s [-a | -f | -s | -y | -d | -p | -n | -k | -g | -j | -e | -t]  [val_num_1] [val_num_2]\n",argz);
      printf("         %s [-a | -p | -n | -l | -q | -j | -e]  [L | T | N | R | C | B]  [val_num_1] [val_num_2]\n",argz);
      printf("         %s [-f | -s | -y | -d | -k]  [P | S | U | D]  [[val_num_1] [val_num_2]] [val_num_3]\n",argz);
      printf("         %s [-b | -v | -c]  [val_num_1] [val_num_2] [val_num_3]\n\n",argz);
      printf("       [val_num_1] = Elemento iniziale della serie numerica.\n");
      printf("       [val_num_2] = Elemento finale della serie numerica./Valore discriminante per la serie.\n");
      printf("       [val_num_3] = Valore discriminante per la visualizzazione della serie.\n");
      printf("\nOpzioni: -a  Serie di numeri primi e fattori di scomposizione visualizzati in notazione standard.\n");
      printf("         -s  Fattori primi di scomposizione di una serie visualizzati singolarmente.\n");
      printf("         -y  Singolo fattore primo di scomposizione visualizzato di una serie numerica.\n");
      printf("         -f  Fattori primi di scomposizione di una serie visualizzati in notazione standard.\n");
      printf("         -p  Serie di soli numeri primi visualizzati in notazione standard.\n");
      printf("         -d  Serie dei soli fattori primi di scomposizione visualizzati in notazione standard.\n");
      printf("         -k  Filtra in una serie i valori che hanno solo due fattori primi di scomposizione.\n");
      printf("         -g  Filtra in una serie solo i numeri primi gemelli visualizzandoli in coppie.\n");
      printf("         -l  Serie numerica di soli numeri primi, visualizzati senza rapporto statistico.\n");
      printf("         -q  Serie numerica di soli fattori primi di scomposizione, senza rapporto statistico.\n");
      printf("         -e  Serie di valori con due fattori di scomposizione, visualizzati senza rapporto statistico.\n");
      printf("         -j  Serie di soli numeri primi gemelli, visualizzati senza rapporto statistico.\n");
      printf("         -n  Serie numerica di valori divisibili con marcatura posizionale dei numeri primi.\n");
      printf("         -t  Rapporto statistico di una serie numerica indicata.\n");
      printf("         -b  Scomposizione in N serie numeriche in funzione di una serie numerica indicata.\n");
      printf("         -v  Serie selettiva di valori per un fattore arbitrario di divisibilità.\n");
      printf("         -c  Serie di valori definita a partire da A per B posizioni di N elementi.\n");
      printf("\nOpzioni speciali: -clr  Elimina il file di configurazione della lingua.\n");
      printf("                  -rst  Reimposta la lingua predefinita. (1)\n");
      printf("                  -rst  Ripristina la modalità iniziale. (2)\n");
      printf("       (1)(2) - La funzionalità cambia in funzione della presenza o assenza del file di configurazione.\n");
      printf("\nMarcatori: P  Marcatura dei numeri primi della serie numerica visualizzata.\n");
      printf("           S  Marcatura di un fattore primo di scomposizione nella serie numerica visualizzata.\n");
      printf("           U  Marcatura ascendente da un fattore primo indicato nella serie numerica visualizzata.\n");
      printf("           D  Marcatura discendente da un fattore primo indicato nella serie numerica visualizzata.\n");
      printf("\nCommutatori: L  Cambia la giustificazione della lista, indicato per accodamenti delle serie su file.\n");
      printf("             N  Permette di visualizzare la posizione cardinale dei numeri primi.\n");
      printf("             C  Permette di trovare i numeri primi corrispondenti alla loro posizione cardinale.\n");
      printf("             R  Simile a N o V, ma adatto per generare serie in accodamento su file.\n");
      printf("             B  Simile a C, ma adatto a generare serie in accodamento su file.\n");
      printf("             V  Permette di calcolare e visualizzare tutti i fattori di divisibilità di un numero.\n");
      printf("             W  Identico a V, con in più la possibilità di modificare a scelta la giustificazione.\n");
      printf("\nOpzioni di visualizzazione a rientro giustificato:\n");
      printf("         -lL  Visualizzazione di una serie di soli numeri primi.\n");
      printf("         -qL  Visualizzazione di una serie di numeri divisibili e fattori primi di scomposizione.\n");
      printf("         -eL  Visualizzazione di una serie di valori con solo due fattori di scomposizione.\n");
      printf("         -jL  Visualizzazione di una serie di numeri primi gemelli.\n");
      printf("\nOpzioni di visualizzazione tabellare:\n");
      printf("         -nT  Visualizzazione nella serie numerica dei soli numeri divisibili su più colonne.\n");
      printf("         -pT  Visualizzazione nella serie numerica dei soli numeri primi su più colonne.\n");
      printf("\nOpzioni di visualizzazione supplementare della posizione:\n");
      printf("         -pC  Visualizzazione di un numero primo indicando la sua posizione cardinale.\n");
      printf("         -lC  Visualizzazione dei numeri primi da una serie indicata di posizioni cardinali.\n");
      printf("         -lB  Visualizzazione di numeri primi e relative posizioni cardinali da una serie indicata.\n");
      printf("         -lR  Visualizzazione della serie indicata di numeri primi e rispettive posizioni cardinali.\n");
      printf("         -pN  Visualizzazione della posizione cardinale di un numero primo indicato.\n");
      printf("         -lN  Visualizzazione della posizione cardinale dei numeri primi della serie indicata.\n");
      printf("\nOpzioni per funzionalità supplementari:\n");
      printf("         -dV  Visualizza i fattori di divisibilità di ogni numero della serie indicata.\n");
      printf("         -qV  Visualizza una lista dei fattori di divisibilità per ogni numero; indicata per liste su file.\n");
      printf("         -dW  Visualizza la lista dei fattori di divisibilità; permette la modifica della giustificazione.\n");
      printf("         -qR  Visualizza la lista dei fattori di divisibilità; indicata per le serie in accodamento su file.\n");
      printf("\nEsempi: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("        %s -t 32768  98303              %s -a 16385  81920\n",argz,argz);
      printf("        %s 100 65635 | less             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("        %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("        %s -l 10 65545 > $HOME/prime    %s -q 10 65545 > $HOME/pfact\n",argz,argz);
      printf("        %s -y 1000 75535                %s -f 1234 9999\n",argz,argz);
      printf("        %s -k 1234 59999                %s -g 1000 50000\n",argz,argz);
      printf("        %s -d 1000 9999                 %s -p 1000 9999\n",argz,argz);
      printf("        %s -j 5000 70000                %s -e 5000 70000\n",argz,argz);
      printf("        %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("        %s -pN 200 65735                %s -pC 100 4195\n",argz,argz);
      printf("        %s -lC 100 4195                 %s -lL 100 65000\n",argz,argz);
      printf("        %s -lN 100 65000                %s -qL 150 65500\n",argz,argz);
      printf("        %s -jL 150 65675                %s -eL 150 65675\n",argz,argz);
      printf("        %s -fP 1234 39999 5             %s -fS 1234 39999 5\n",argz,argz);
      printf("        %s -yS 1234 39999 5             %s -sU 12345 39999 13\n",argz,argz);
      printf("        %s -b 1001 5000 16              %s -c 1001 5000 7\n",argz,argz);
      printf("        %s -v 2500 2999 7               %s -lB 1000 5095\n",argz,argz);
      printf("        %s -dV 290 2900                 %s -qV 29000 94535\n",argz,argz);
      printf("        %s -dW 2900 29300               %s -qR 34000 99535\n",argz,argz);
      printf("        %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("        %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("        less < $HOME/pcont\n\n");
      return;
   }

   /* *********************************************************************** */
   if(*flang==ESPANOL) {
      printf("\n%s   Versión: %s",argz,verrez);
      printf("\n~© (2010-2026) - F.S.F. GNU/GPL vers.3\n");
      printf("\nUsar: %s      Presentación.\n",argz);
      printf("      %s -?   Información sobre el autor y la licencia.\n",argz);
      printf("      %s -?M  Manual de usuario.\n",argz);
      printf("      %s -?I  Guia de inicio rápido.\n",argz);
      printf("      %s -?O  Tabla de referencia para opciones.\n",argz);
      printf("      %s -h   Ayuda rápida.\n",argz);
      printf("      %s --help  Esta ayuda detallada.\n",argz);
      printf("      %s --help | less  Ayuda detallada (vista alternativa).\n",argz);
      printf("      %s IT, EN, ES, FR, PT, DE  Selección de idioma local.\n",argz);
      printf("      %s [arg_num]\n",argz);
      printf("      %s [arg_num_1] [arg_num_2]\n",argz);
      printf("      %s [opcion] [marcador/interruptor] [arg_num_1] [arg_num_2]\n",argz);
      printf("      %s [opcion] [marcador/interruptor] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("\n     Opciones: [-a]  [-s, -f, -y]  [-d, -q]  [-p, -l]  [-n]  [-k, -e]  [-g, -j]  [-t]  [-b, -v, -c]");
      printf("\n   Marcadores: [P, S, U, D]");
      printf("\nInterruptores: [T]  [L]  [V, W]  [N, R]  [C, B]  [I, M, O]\n");
      printf("\nSinopsis: %s [-a | -f | -s | -y | -d | -p | -n | -k | -g | -j | -e | -t]  [val_num_1] [val_num_2]\n",argz);
      printf("          %s [-a | -p | -n | -l | -q | -j | -e]  [L | T | N | R | C | B]  [val_num_1] [val_num_2]\n",argz);
      printf("          %s [-f | -s | -y | -d | -k]  [P | S | U | D]  [[val_num_1] [val_num_2]] [val_num_3]\n",argz);
      printf("          %s [-b | -v | -c]  [val_num_1] [val_num_2] [val_num_3]\n\n",argz);
      printf("        [val_num_1] = Elemento inicial de la serie numérica.\n");
      printf("        [val_num_2] = Elemento final de la serie numérica./Valor discriminante para la serie.\n");
      printf("        [val_num_3] = Valor discriminante para visualizar la serie.\n");
      printf("\nOpciones: -a  Serie de números primos y sus factores de descomposición mostrados en notación estándar.\n");
      printf("          -s  Factores primos de una descomposición en series mostrados individualmente.\n");
      printf("          -y  Factor primo único mostrado de una serie numérica.\n");
      printf("          -f  Factores primos de una serie mostrados en notación estándar.\n");
      printf("          -p  Serie de únicamente números primos mostrados en notación estándar.\n");
      printf("          -d  Serie de únicamente factores de descomposición primos mostrados en notación estándar.\n");
      printf("          -k  Filtra valores de una serie que tienen solo dos factores primos de descomposición.\n");
      printf("          -g  Filtra únicamente los primos gemelos en una serie mostrándolos en pares.\n");
      printf("          -l  Serie numérica que contiene únicamente números primos,sin relación estadística.\n");
      printf("          -q  Serie numérica de sólo factores primos de descomposición, sin relación estadística.\n");
      printf("          -e  Serie de valores con dos factores de descomposición, mostrados sin relación estadistica.\n");
      printf("          -j  Serie de sólo primos gemelos, mostrada sin relación estadistica.\n");
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
      printf("\nMarcadores: P  Marcado de los números primos de la serie de números mostrada.\n");
      printf("            S  Marcado de un factor primo de descomposición en la serie numérica mostrada.\n");
      printf("            U  Marcado ascendente a partir de un factor primo indicado en la serie de números mostrada.\n");
      printf("            D  Marcado descendente a partir de un factor primo indicado en la serie de números mostrada.\n");
      printf("\nInterruptores: L  Modifica la justificación de la lista, adecuada para adjuntar series a archivos.\n");
      printf("               N  Permite visualizar la posición cardinal de los números primos.\n");
      printf("               C  Permite encontrar los números primos que corresponden a su posición cardinal.\n");
      printf("               R  Similar a N o V, pero adecuado para generar series que se adjuntan a los archivos.\n");
      printf("               B  Similar a C, pero adecuado para generar series que se adjuntan a los archivos.\n");
      printf("               V  Permite calcular y mostrar todos los factores de divisibilidad de un número.\n");
      printf("               W  Idéntico a V, con la adición de la posibilidad de elegir la justificación.\n");
      printf("\nOpciones de visualización de espaciado justificado:\n");
      printf("          -lL  Visualizzar una serie de sólo números primos.\n");
      printf("          -qL  Visualización de una serie de números divisibles y factores primos de descomposición.\n");
      printf("          -eL  Visualización de una serie de valores con solo dos factorizaciones.\n");
      printf("          -jL  Visualización de una serie de números primos gemelos.\n");
      printf("\nOpciones de vista de tabla:\n");
      printf("          -nT  Mostrar en la serie numérica sólo los números que sean deisibles en varias columnas.\n");
      printf("          -pT  Mostrar sólo números primos en la serie numérica en varias columnas.\n");
      printf("\nOpciones de visualización de ubicación adicionales:\n");
      printf("          -pC  Visualizar un número primo indicando su posición cardinal.\n");
      printf("          -lC  Visualización de números primos de un conjunto dado de posiciones cardinales.\n");
      printf("          -lB  Visualización de números primos y sus posiciones cardinales de una serie dada.\n");
      printf("          -lR  Visualización de la serie indicada de números primos y sus respectivas posiciones cardinales.\n");
      printf("          -pN  Visualización de la posición cardinal de un número primo dado.\n");
      printf("          -lN  Visualización de la posición cardinal de los números primos de la serie dada.\n");
      printf("\nOpciones para funciones adicionales:\n");
      printf("          -dV  Muestra los factores de divisibilidad de cada número en la serie especificada.\n");
      printf("          -qV  Muestra una lista de factores de divisibilidad para cada número; adecuada para listas en archivos.\n");
      printf("          -dW  Muestra la lista de factores de divisibilidad; permite cambiar la justificación.\n");
      printf("          -qR  Muestra la lista de factores de divisibilidad; adecuada para series en cola para archivar.\n");
      printf("\nEjemplos: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("          %s -t 32768  98303              %s -a 16385  81920\n",argz,argz);
      printf("          %s 100 65635 | less             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("          %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("          %s -l 10 65545 > $HOME/prime    %s -q 10 65545 > $HOME/pfact\n",argz,argz);
      printf("          %s -y 1000 75535                %s -f 1234 9999\n",argz,argz);
      printf("          %s -k 1234 59999                %s -g 1000 50000\n",argz,argz);
      printf("          %s -d 1000 9999                 %s -p 1000 9999\n",argz,argz);
      printf("          %s -j 5000 70000                %s -e 5000 70000\n",argz,argz);
      printf("          %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("          %s -pN 200 65735                %s -pC 100 4195\n",argz,argz);
      printf("          %s -lC 100 4195                 %s -lL 100 65000\n",argz,argz);
      printf("          %s -lN 100 65000                %s -qL 150 65500\n",argz,argz);
      printf("          %s -jL 150 65675                %s -eL 150 65675\n",argz,argz);
      printf("          %s -fP 1234 39999 5             %s -fS 1234 39999 5\n",argz,argz);
      printf("          %s -yS 1234 39999 5             %s -sU 12345 39999 13\n",argz,argz);
      printf("          %s -b 1001 5000 16              %s -c 1001 5000 7\n",argz,argz);
      printf("          %s -v 2500 2999 7               %s -lB 1000 5095\n",argz,argz);
      printf("          %s -dV 290 2900                 %s -qV 29000 94535\n",argz,argz);
      printf("          %s -dW 2900 29300               %s -qR 34000 99535\n",argz,argz);
      printf("          %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("          %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("          less < $HOME/pcont\n\n");
      return;
   }

   /* *********************************************************************** */
   if(*flang==FRANCAIS) {
      printf("\n%s   Version : %s",argz,verrez);
      printf("\n~© (2010-2026) - F.S.F. GNU/GPL vers.3\n");
      printf("\nUtiliser : %s      Presentation.\n",argz);
      printf("           %s -?   Informations sur l'auteur et la licence.\n",argz);
      printf("           %s -?M  Manuel d'utilisation.\n",argz);
      printf("           %s -?I  Guide de dèmarrage rapide.\n",argz);
      printf("           %s -?O  Tableau de référence des options.\n",argz);
      printf("           %s -h   Aide rapide.\n",argz);
      printf("           %s --help  Cette aide déttaillée.\n",argz);
      printf("           %s --help | less  Aide detaillée (affichage alternatif).\n",argz);
      printf("           %s IT, EN, ES, FR, PT, DE  Selection de la langue locale.\n",argz);
      printf("           %s [arg_num]\n",argz);
      printf("           %s [arg_num_1] [arg_num_2]\n",argz);
      printf("           %s [option] [segnaleur/interrupteur] [arg_num_1] [arg_num_2]\n",argz);
      printf("           %s [option] [segnaleur/interrupteur] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("\n      Options : [-a]  [-s, -f, -y]  [-d, -q]  [-p, -l]  [-n]  [-k, -e]  [-g, -j]  [-t]  [-b, -v, -c]");
      printf("\n    Marqueurs : [P, S, U, D]");
      printf("\nInterrupteurs : [T]  [L]  [V, W]  [N, R]  [C, B]  [I, M, O]\n");
      printf("\nSynopsis : %s [-a | -f | -s | -y | -d | -p | -n | -k | -g | -j | -e | -t]  [val_num_1] [val_num_2]\n",argz);
      printf("           %s [-a | -p | -n | -l | -q | -j | -e]  [L | T | N | R | C | B]  [val_num_1] [val_num_2]\n",argz);
      printf("           %s [-f | -s | -y | -d | -k]  [P | S | U | D]  [[val_num_1] [val_num_2]] [val_num_3]\n",argz);
      printf("           %s [-b | -v | -c]  [val_num_1] [val_num_2] [val_num_3]\n\n",argz);
      printf("         [val_num_1] = Élément initial de la série numerique.\n");
      printf("         [val_num_2] = Élément final de la série numerique./Valeur discriminante pour la série.\n");
      printf("         [val_num_3] = Valeur discriminante pour l'affichage de la série.'\n");
      printf("\nOptions : -a  Série de nombres premiers et leurs facteurs de décomposition présentés en notation standard.\n");
      printf("          -s  Facteurs premiers d'une décomposition en série affichés individuellement.\n");
      printf("          -y  Facteur premier affiché unique d'une série numérique.\n");
      printf("          -f  Facteurs premiers d'une série affichés en notation standard.\n");
      printf("          -p  Série de nombres premiers uniquement affichée en notation standard.\n");
      printf("          -d  Série de facteurs de décomposition premiers uniquement affichés en notation standard.\n");
      printf("          -k  Filtre les valeurs d'une série qui n'ont que deux facteurs premiers de décomposition.\n");
      printf("          -g  Filtrer uniquement les nombres premiers jumeaux d'une série en les affichant par paires.\n");
      printf("          -l  Série numérique contenant uniquement des nombres premiers, sans relation statistique.\n");
      printf("          -e  Série de valeurs avec deux facteurs de décomposition, affichées sans relation statistique.\n");
      printf("          -q  Série numérique des seuls facteurs de décomposition premiers affichés sans rapport statistique.\n");
      printf("          -j  serie composée uniquement de nombres premiers jumeaux, affichés sans relation statistique.\n");
      printf("          -n  Série numérique de valeurs divisibles avec marquage positionnel des nombres premiers.\n");
      printf("          -t  Rapport statistique de la série numérique indiquée.\n");
      printf("          -b  Decomposition en N séries numériques en fonction d'une séerie numérique donnée.\n");
      printf("          -v  Série sélective de valeurs pour un facteur de divisibilité arbitraire.\n");
      printf("          -c  Série de valeurs définies de A à B positions de N éléments.\n");
      printf("\nOptions spéciales : -clr  Supprimer le fichier de configuration de langue.\n");
      printf("                    -rst  Réinitialiser la langue par défaut. (1)\n");
      printf("                    -rst  Restaure le mode initial. (2)\n");
      printf("         (1)(2) - La functionnalité change en fonction de la présence ou de l'absence\n");
      printf("                  du fichier de configuration.\n");
      printf("\n Marqueurs : P  Marquage des nombres premiers de la série de nombres affichée.\n");
      printf("             S  Marquage d'un facteur premier de décomposition dans la série numérique affichée.\n");
      printf("             U  Marquage croissant à partir d'un facteur premier indiqué dans la série de nombres affichée.\n");
      printf("             D  Marquage décroissant à partir d'un facteur premier indiqué dans la série de nombres affichée.\n");
      printf("\nInterrupteurs : L  Modifie la justification de la liste, ce qui est adapté à l'ajout de séries aux fichiers.\n");
      printf("                N  Il permet de visualiser la position cardinale des nombres premiers.\n");
      printf("                C  Il permet de trouver les nombres premiers correspondant à leur position cardinale.\n");
      printf("                R  Similaire à N ou V, mais adapté à la génération de séries ajoutées aux fichiers.\n");
      printf("                B  Similaire à C, mais adapté à la génération de séries ajoutées à des fichiers.\n");
      printf("                V  Permet de calculer et d'afficher tous les facteurs de divisibilité d'un nombre.\n");
      printf("                W  Identique à V, avec en plus la possibilité de choisir la justification.\n");
      printf("\nOption d'affichage du retrait justifié :\n");
      printf("         -lL  Visualiser une série composée uniquement de nombres premiers.\n");
      printf("         -qL  Affichage d'une série de nombres divisibles et de facteurs premiers de décomposition.\n");
      printf("         -eL  Affichage d'une série de valeurs avec seulement deux factorisations.\n");
      printf("         -jL  Visualisation d'une série de nombres premiers jumeaux.\n");
      printf("\nOptions d'affichage du tableau:\n");
      printf("         -nT  Afficher dans la série numérique uniquement les nombres divisibles en plusieur colonnes.\n");
      printf("         -pT  Afficher uniquement les nombres premiers de la série numérique dans plusieurs colonnes.\n");
      printf("\nOptions d'affichage de localisation supplémentaires:\n");
      printf("         -pC  Visualiser un nombre premier en indiquant sa position cardinale.\n");
      printf("         -lC  Affichage des nombre premiers à partir d'un ensemble donné de positions cardinales.\n");
      printf("         -lB  Affichage des nombre premiers et de leurs position cardinales dans une série donnée.\n");
      printf("         -lR  Affichage de la série de nombres premiers indiquée et de leurs positions cardinales respectives.\n");
      printf("         -pN  Affichage la position cardinale d'un nombre premier donné.\n");
      printf("         -lN  Affichage de la position cardinale des nombres premiers de la série donnée.\n");
      printf("\nOptions pour des fonctionnalités supplémentaires:\n");
      printf("         -dV  Afficher les facteurs de divisibilité de chaque nombre de la série spécifiée.\n");
      printf("         -qV  Affiche la liste des facteurs de divisibilité de chaque nombre ; convient aux listes contenues dans des fichiers.\n");
      printf("         -dW  Affiche la liste des facteurs de divisibilité ; permet de modifier la justification.\n");
      printf("         -qR  Affiche la liste des facteurs de divisibilité ; convient aux séries mises en file d'attente dans un fichier.\n");
      printf("\nExemples : %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("           %s -t 32768  98303              %s -a 16385  81920\n",argz,argz);
      printf("           %s 100 65635 | less             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("           %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("           %s -l 10 65545 > $HOME/prime    %s -q 10 65545 > $HOME/pfact\n",argz,argz);
      printf("           %s -y 1000 75535                %s -f 1234 9999\n",argz,argz);
      printf("           %s -k 1234 59999                %s -g 1000 50000\n",argz,argz);
      printf("           %s -d 1000 9999                 %s -p 1000 9999\n",argz,argz);
      printf("           %s -j 5000 70000                %s -e 5000 70000\n",argz,argz);
      printf("           %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("           %s -pN 200 65735                %s -pC 100 4195\n",argz,argz);
      printf("           %s -lC 100 4195                 %s -lL 100 65000\n",argz,argz);
      printf("           %s -lN 100 65000                %s -qL 150 65500\n",argz,argz);
      printf("           %s -jL 150 65675                %s -eL 150 65675\n",argz,argz);
      printf("           %s -fP 1234 39999 5             %s -fS 1234 39999 5\n",argz,argz);
      printf("           %s -yS 1234 39999 5             %s -sU 12345 39999 13\n",argz,argz);
      printf("           %s -b 1001 5000 16              %s -c 1001 5000 7\n",argz,argz);
      printf("           %s -v 2500 2999 7               %s -lB 1000 5095\n",argz,argz);
      printf("           %s -dV 290 2900                 %s -qV 29000 94535\n",argz,argz);
      printf("           %s -dW 2900 29300               %s -qR 34000 99535\n",argz,argz);
      printf("           %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("           %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("           less < $HOME/pcont\n\n");
      return;
   }

   /* *********************************************************************** */
   if(*flang==PORTUGUES) {
      printf("\n%s   Versão: %s",argz,verrez);
      printf("\n~© (2010-2026) - F.S.F. GNU/GPL vers.3\n");
      printf("\nUsar: %s      Apresentação.\n",argz);
      printf("      %s -?   Informações sobre autor e licença.\n",argz);
      printf("      %s -?M  Manual do usuário.\n",argz);
      printf("      %s -?I  GUia de inicio rápido.\n",argz);
      printf("      %s -?O  Tabela de referência para opções.\n",argz);
      printf("      %s -h   Ajuda rapida.\n",argz);
      printf("      %s --help  Esta ajuda detalhada.\n",argz);
      printf("      %s --help | less  Ajuda detalhada (Visualização alternativa).\n",argz);
      printf("      %s IT, EN, ES, FR, PT, DE  Seleção do idioma local.\n",argz);
      printf("      %s [arg_num]\n",argz);
      printf("      %s [arg_num_1] [arg_num_2]\n",argz);
      printf("      %s [opção] [sinalizador/interruptor] [arg_num_1] [arg_num_2]\n",argz);
      printf("      %s [opção] [sinalizador/interruptor] [arg_num_1] [arg_num_2] [arg_num_3]\n",argz);
      printf("\n       Opções: [-a]  [-s, -f, -y]  [-d, -q]  [-p, -l]  [-n]  [-k, -e]  [-g, -j]  [-t]  [-b, -v, -c]");
      printf("\n   Marcadores: [P, S, U, D]");
      printf("\nInterruptores: [T]  [L]  [V, W]  [N, R]  [C, B]  [I, M, O]\n");
      printf("\nSinopse: %s [-a | -f | -s | -y | -d | -p | -n | -k | -g | -j | -e | -t]  [val_num_1] [val_num_2]\n",argz);
      printf("         %s [-a | -p | -n | -l | -q | -j | -e]  [L | T | N | R | C | B]  [val_num_1] [val_num_2]\n",argz);
      printf("         %s [-f | -s | -y | -d -k]  [P | S | U | D]  [[val_num_1] [val_num_2]] [val_num_3]\n",argz);
      printf("         %s [-b | -v | -c]  [val_num_1] [val_num_2] [val_num_3]\n\n",argz);
      printf("       [val_num_1] = Elemento inicial da série numérica.\n");
      printf("       [val_num_2] = Elemento final da série numérica./Valor discriminante para a série.\n");
      printf("       [val_num_3] = Valor discriminante para exibição da série.\n");
      printf("\nOpções: -a  Série de números primos e seus fatores de decomposição, apresentados em notação padrão.\n");
      printf("        -s  Fatores primos de uma decomposição em série exibidos individualmente.\n");
      printf("        -y  Fator primo único exibido de uma série numérica.\n");
      printf("        -f  Fatores primos de uma série exibidos em notação padrão.\n");
      printf("        -p  Série de apenas números primos exibidos em notação padrão.\n");
      printf("        -d  Série de fatores de decomposição apenas primos exibidos em notação padrão.\n");
      printf("        -k  Filtra valores em uma série que possuem apenas dois factores primos de decomposição.\n");
      printf("        -g  Filtre apenas os números primos gêmeos em uma série, exibindo-os em pares.\n");
      printf("        -l  Série numérica de apenas números primos, exibidos exibida sem relação estatistica.\n");
      printf("        -q  Série numérica contenendo apenas fatores de decomposição primos exibida sem razão estatistica.\n");
      printf("        -e  Série de valores com dois fatores de decomposição, apresentados sem regação estatistica.\n");
      printf("        -j  Série composta apenas por números primos gêmeos, exibida sem relação estatistica.\n");
      printf("        -n  Série numéricas de valores divisíveis com marcação posicional dos números primos.\n");
      printf("        -t  Relatório estatístico de uma determinada série de valores.\n");
      printf("        -b  Decomposição em N séries numéricas em função de uma dada série numérica.\n");
      printf("        -v  Série seletiva de valores para um fator de divisibilidade arbitrário.\n");
      printf("        -c  Série de valores definidos das posições A a B de N elementos.\n");
      printf("\nOpções especiais: -clr  Exclua o arquivo de configuração de idioma.\n");
      printf("                  -rst  Redefinir para o idioma padrão. (1)\n");
      printf("                  -rst  Restaura o modo inicial. (2)\n");
      printf("       (1)(2) - A funcionalidade muda dependendo da presença ou ausência do arquivo de configuração.\n");
      printf("\nMarcadores: P  Marcação dos números primos da série numérica exibida.\n");
      printf("            S  Marcação de um fator primo de decomposição na série numérica exibida.\n");
      printf("            U  Marcação ascendente a partir de um fator primo indicado na série numérica exibida.\n");
      printf("            D  Marcação decrecendente a partir de um fator primo indicado na série numérica exibida.\n");
      printf("\nInterruptores: L  Altera o alinhamento da lista, tornando-a adequada para adicionar séries a arquivos.\n");
      printf("               N  Permite visualizar a posição cardinal dos números primos.\n");
      printf("               C  Permite encontrar os números primos correspondentes à sua posição cardinal.\n");
      printf("               R  Semelhante a N ou V, mas adequado para gerar séries anexadas a arquivos.\n");
      printf("               B  Semelhante a C, mas adequado para gerar séries anexadas a arquivos.\n");
      printf("               V  Permite calcular e exibir todos os fatores de divisibilidade de um número.\n");
      printf("               W  Idêntico ao V, com a adição da possibilidade de escolher a justificativa.\n");
      printf("\nOpções de exibição com recuo justificado:\n");
      printf("        -lL  Visualizando uma série de apenas números primos.\n");
      printf("        -qL  Exibindo uma série de números divisiveis e fatore primos de decomposição.\n");
      printf("        -eL  Exibição de uma série de valores com apenas duas fatorações.\n");
      printf("        -jL  Visualização de uma série del números primos gemeos.\n");
      printf("\nOpções de visualização de tabela:\n");
      printf("        -nT  Exibir na série numérica somente números que são divisíveis em multiplas colunas.\n");
      printf("        -pT  Exibir somente números primos na série numérica em várias colunas.\n");
      printf("\nOpções adicionais de exibição de localização:\n");
      printf("        -pC  Visualizar um número primo indicando sua posição cardinal.\n");
      printf("        -lC  Exibição de números primos a partir de um conjunto dado de posições cardinais.\n");
      printf("        -lB  Exibição dos números primos e suas posições cardinais em uma determinada série.\n");
      printf("        -lR  Exibição da série indicada de números primos e suas respectivas posições cardinais.\n");
      printf("        -pN  Exibe a posição cardinal de um determinado número primo.\n");
      printf("        -lN  Exibição da posição cardinal dos números primos da série dada.\n");
      printf("\nOpções para recursos adicionais:\n");
      printf("        -dV  Exibe os fatores de divisibilidade de cada número na série especificada.\n");
      printf("        -qV  Exibe uma lista dos fatores de divisibilidade de cada número; adequado para listas em arquivos.\n");
      printf("        -dW  Exibe a lista de fatores de divisibilidade; permite alterar o alinhamento do texto.\n");
      printf("        -qR  Exibe a lista de fatores de divisibilidade; adequado para séries armazenadas em fila de arquivos.\n");
      printf("\nExemplos: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("          %s -t 32768  98303              %s -a 16385  81920\n",argz,argz);
      printf("          %s 100 65635 | less             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("          %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("          %s -l 10 65545 > $HOME/prime    %s -q 10 65545 > $HOME/pfact\n",argz,argz);
      printf("          %s -y 1000 75535                %s -f 1234 9999\n",argz,argz);
      printf("          %s -k 1234 59999                %s -g 1000 50000\n",argz,argz);
      printf("          %s -d 1000 9999                 %s -p 1000 9999\n",argz,argz);
      printf("          %s -j 5000 70000                %s -e 5000 70000\n",argz,argz);
      printf("          %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("          %s -pN 200 65735                %s -pC 100 4195\n",argz,argz);
      printf("          %s -lC 100 4195                 %s -lL 100 65000\n",argz,argz);
      printf("          %s -lN 100 65000                %s -qL 150 65500\n",argz,argz);
      printf("          %s -jL 150 65675                %s -eL 150 65675\n",argz,argz);
      printf("          %s -fP 1234 39999 5             %s -fS 1234 39999 5\n",argz,argz);
      printf("          %s -yS 1234 39999 5             %s -sU 12345 39999 13\n",argz,argz);
      printf("          %s -b 1001 5000 16              %s -c 1001 5000 7\n",argz,argz);
      printf("          %s -v 2500 2999 7               %s -lB 1000 5095\n",argz,argz);
      printf("          %s -dV 290 2900                 %s -qV 29000 94535\n",argz,argz);
      printf("          %s -dW 2900 29300               %s -qR 34000 99535\n",argz,argz);
      printf("          %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("          %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("          less < $HOME/pcont\n\n");
      return;
   }

   /* *********************************************************************** */
   if(*flang==DEUTCHE) {
      printf("\n%s   Version: %s",argz,verrez);
      printf("\n~© (2010-2026) - F.S.F. GNU/GPL vers.3\n");
      printf("\nVerwenden: %s      Präsentation.\n",argz);
      printf("           %s -?   Autoren und Lizenzinformationen.\n",argz);
      printf("           %s -?M  Benutzerhandbuch.\n",argz);
      printf("           %s -?I  Kurzanleitung.\n",argz);
      printf("           %s -?O  Referenztabelle für Optionen.\n",argz);
      printf("           %s -h   Schnelle Hilfe.\n",argz);
      printf("           %s --help  Diese detaillierte Hilfe.\n",argz);
      printf("           %s --help | less  Detaillierte Hilfe (Alternative Ansicht).\n",argz);
      printf("           %s IT, EN, ES, FR, PT, DE  Lokale Sprachauswahi.\n",argz);
      printf("           %s [arg_num]\n",argz);
      printf("           %s [arg_num_1] [arg_num_2]\n",argz);
      printf("           %s [option] [signalgeber/shalten] [zahl_arg_1] [zahl_arg_2]\n",argz);
      printf("           %s [option] [signalgeber/shalten] [zahl_arg_1] [zahl_arg_2] [arg_num_3]\n",argz);
      printf("\n    Optionen: [-a]  [-s, -f, -y]  [-d, -q]  [-p, -l]  [-n]  [-k, -e]  [-g, -j]  [-t]  [-b, -v, -c]");
      printf("\nMarkierungen: [P, S, U, D]");
      printf("\n     Shalter: [T]  [L]  [V, W]  [N, R]  [C, B]  [I, M, O]\n");
      printf("\nÜberblick: %s [-a | -f | -s | -y | -d | -p | -n | -k | -g | -j | -e | -t]  [numm_wer_1] [numm_wert_2]\n",argz);
      printf("           %s [-a | -p | -n | -l | -q | -j | -e]  [L | T | N | R | C | B]  [numm_wer_1] [numm_wert_2]\n",argz);
      printf("           %s [-f | -s | -y | -d | -k]  [P | S | U | D]  [[numm_wert_1] [numm_wert_2]] [numm_wert_3]\n",argz);
      printf("           %s [-b | -v | -c]  [numm_wert_1] [numm_wert_2] [numm_wert_3]\n\n",argz);
      printf("         [numm_wert_1] = Anfangselement der Zahlenreihe.\n");
      printf("         [numm_wert_2] = Letztes Element der Zahlenreihe./Diskriminantzwert für die Reihe.\n");
      printf("         [numm_wert_3] = Diskriminanzwert zur Darstellung der Reihe.\n");
      printf("\nOptionen: -a  Reihen von Prinzahlen und ihren Zerlengungsfaktoren in Standardnotation.\n");
      printf("          -s  Primfaktoren einer Reihenzerlegung einzeln dargestellt.\n");
      printf("          -y  Einzelner angezeigter Primfaktor einer Zahlenreihe.\n");
      printf("          -f  Primfaktoren einer Reihe dargestellt in Standardnotation.\n");
      printf("          -p  Reihe von ausschließlich Primzahlen dargestellt in Standardnotation.\n");
      printf("          -d  Reihe von ausschließlich Primzerlegungsfaktoren angezeigt in Standardnotation.\n");
      printf("          -k  Filtert Werte in einer Reihe, die nur zwei Primfaktoren der Zerlegung haben.\n");
      printf("          -g  Filtert nur Zwillingsprimzahlen in einer Folge heraus, indem ihr sie paarweise anzeigt.\n");
      printf("          -l  Numerische Reihe ausschließlich von Primezahlen, dargestellt ohne statistischen Zusammenhang.\n");
      printf("          -q  Numerische Reihe nur der Primfaktorzerlegungsfactoren, dargestellt ohne statistisches Verhältnis.\n");
      printf("          -e  Werterehie mit zwei Zerlegungsfaktoren, dargestellt ohne statistische Beziehung.\n");
      printf("          -j  Reiche von ausschließlich Zwillingsprimzahlen, dargestellt ohne statistische Beziehung.\n");
      printf("          -n  Zahlenreihe teilbaler Werte mit Stellenmarkierung der Primzahlen.\n");
      printf("          -t  Statistischer Bericht der angegebeden Zahlenreihe.\n");
      printf("          -b  Zerlegung in N Zahlenreihen als Funktion einer gegebenen Zahlenreihe.\n");
      printf("          -v  Selektive Wertereihe für einen beliebigen Teilbarkeitsfaktor.\n");
      printf("          -c  Wertereihe definiert von den Positionen A bis B der N Elemente.\n");
      printf("\nSpezielle Optionen: -clr  Löschen Sie die Sprachkon figurationsdatei.\n");
      printf("                    -rst  Auf Standardsprache zurücksetzen. (1)\n");
      printf("                    -rst  Stellt den Ausgangsmodus wieder her. (2)\n");
      printf("         (1)(2) - Die Funktionalität ändert sich je nach Vorhandensein\n");
      printf("                  oder Fehlen der Konfigurationsdatei.\n");
      printf("\nMarkierungen: P  Markierung der Primzahlen der angezeigten Zahlenreihe.\n");
      printf("              S  Markierung eines Primfaktors der Zeiegung in der angezeigten Zahlenreihe.\n");
      printf("              U  Aufsteigende Markierung ab einem ausgewählten Primfaktor in der angezeigten Zahlenreihe.\n");
      printf("              D  Absteigende Markierung ab einem ausgewählten Primfaktor in der angezeigten Zahlenreihe.\n");
      printf("\nShalter: L  Ändert die Ausrichtung der Liste, geeignet zum Anhängen von Serien an Datein.\n");
      printf("         N  Es ermöglicht Ihnen, die Kardinalposition von Primzahlen zu visualisieren.\n");
      printf("         C  Es ermöglicht Ihnen, die Primzahlen zu finden, die ihrer Kardinalposition entsprechen.\n");
      printf("         R  Ähnlich wie N oder V, aber geeignet zur Erzeugung von Serien, die an Dateien angehängt werden.\n");
      printf("         B  Ähnlich wie C, aber geeignet zur Erzegung von Serien, die an Dateien angehängt werden.\n");
      printf("         V  Ermöglicht die Berechnung und Anzeige aller Teilbarkeitsfaktoren einer Zahl.\n");
      printf("         W  Identisch mit V, mit dem zusätzlichen Vorteil, die Begründung auswählen zu können.\n");
      printf("\nAnzeigeoptionen für Blocksatz:\n");
      printf("          -lL  Visualisieren einer Reihe die ausschließlich aus Primzahlen besteht.\n");
      printf("          -qL  Anzeige einer Reihe teilbarer Zahlen und Primfaktoren der Zerlegung.\n");
      printf("          -eL  Anzeige einer Reihe von Werten mit nur zwei Faktorisierungen.\n");
      printf("          -jL  Visualisierung einer Reihe von Zwillingsprimzahelen.\n");
      printf("\nOptionen für die Tabellenansicht:\n");
      printf("          -nT  Zeigen Sie in der Zahlenreihe nur Zahlen an die auf mehrere Spalten aufgeteilt werden können.\n");
      printf("          -pT  In der Zahlenreihe werden in mehreren Spalten nur Primzahlen angezeigt.\n");
      printf("\nZusätzliche Standortanzeigeoptionen:\n");
      printf("          -pC  Eine Primzahl visualisieren, indem man ihre Kardinalstelle angibt.\n");
      printf("          -lC  Anzeige von Primzahlen aus einer gegebenen Menge von Kardinalstellen.\n");
      printf("          -lR  Anzeige der angegebenen Primzahlfolge und ihrer jeweiligen Kardinalstellen.\n");
      printf("          -lB  Anzeige der Primzahlen und ihrer Kardinalpositionen aus einer gegebenen Zahlenreihe.\n");
      printf("          -pN  Anzeige der Kardinalposition der gegebenen Primzahl.\n");
      printf("          -lN  Anzeige der Kardinalposition der Primzahlen der gegebenen Reihe.\n");
      printf("\nOptionen für zusätzliche Funktionen:\n");
      printf("          -dV  Anzeige der Teilbarkeitsfaktoren jeder Zahl in der angegebeden Reihe.\n");
      printf("          -qV  Zeigt eine Liste der Teilbarkeitsfaktoren für jede Zahl an; geeignet für Listen in Datein.\n");
      printf("          -dW  Zeigt die Liste der Teilbarkeitsfaktoren an; ermöglicht die Änderung der Begründung.\n");
      printf("          -qR  Zeigt die Liste der Teilbarkeitsfaktoren an; geeignet für in einer Datei gespeicherte Reihen.\n");
      printf("\nBeispiele: %s 1234567890                   %s 1 65535\n",argz,argz);
      printf("           %s -t 32768  98303              %s -a 16385  81920\n",argz,argz);
      printf("           %s 100 65635 | less             %s -aL 1 65535 > $HOME/prime\n",argz,argz);
      printf("           %s -lL 1 65535 > $HOME/pfact    %s -qL 1 65535 > $HOME/pfact\n",argz,argz);
      printf("           %s -l 10 65545 > $HOME/prime    %s -q 10 65545 > $HOME/pfact\n",argz,argz);
      printf("           %s -y 1000 75535                %s -f 1234 9999\n",argz,argz);
      printf("           %s -k 1234 59999                %s -g 1000 50000\n",argz,argz);
      printf("           %s -d 1000 9999                 %s -p 1000 9999\n",argz,argz);
      printf("           %s -j 5000 70000                %s -e 5000 70000\n",argz,argz);
      printf("           %s -nT 100 50000                %s -pT 100 50000\n",argz,argz);
      printf("           %s -pN 200 65735                %s -pC 100 4195\n",argz,argz);
      printf("           %s -lC 100 4195                 %s -lL 100 65000\n",argz,argz);
      printf("           %s -lN 100 65000                %s -qL 150 65500\n",argz,argz);
      printf("           %s -jL 150 65675                %s -eL 150 65675\n",argz,argz);
      printf("           %s -fP 1234 39999 5             %s -fS 1234 39999 5\n",argz,argz);
      printf("           %s -yS 1234 39999 5             %s -sU 12345 39999 13\n",argz,argz);
      printf("           %s -b 1001 5000 16              %s -c 1001 5000 7\n",argz,argz);
      printf("           %s -v 2500 2999 7               %s -lB 1000 5095\n",argz,argz);
      printf("           %s -dV 290 2900                 %s -qV 29000 94535\n",argz,argz);
      printf("           %s -dW 2900 29300               %s -qR 34000 99535\n",argz,argz);
      printf("           %s -lL 1 65535 >> $HOME/prime   %s -qL 1 65535 >> $HOME/pfact\n",argz,argz);
      printf("           %s -lR 1 65535 >> $HOME/pcont   %s -lB 100 900 >> $HOME/cprim\n",argz,argz);
      printf("           less < $HOME/pcont\n\n");
      return;
   }

   /* *********************************************************************** */
}
/* Fine della funzione helpfunc(). */

/* Fine delle funzioni di stampa di aiuto. */


/* -------------- ----- */
/* ---- Contributo ---- */
/* ----- nascosto ----- */
/* -------------------- */
void contrib(char *fnpr,char *frel) {

/* Corpo funzione. */
   printf("%s - %s\n",fnpr,frel);
   putchar('\n');
   fprintf(stdout,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
   fprintf(stdout,"(Un pensiero illuminante)\n");
   fprintf(stdout," Per portare a compimento progetti al limite dell'incredibile, occorre\n");
   fprintf(stdout,"anzitutto crederci, oltre ad avere anche un po' di fortuna, ma soprat-\n");
   fprintf(stdout,"tutto occorre estrema concentrazione, dedizione ed impegno nel proprio\n");
   fprintf(stdout,"lavoro, perseverando oltre ogni limite, sempre, qualsiasi cosa succeda\n");
   fprintf(stdout,"pregando  e sperando che, nonostante tutto, alla fine  ce la  possiamo\n");
   fprintf(stdout,"fare, la nazione lo richiede, ora abbiamo questa grande possibilità...\n");
   fprintf(stdout,"quindi (noi) ce la faremo!\n");
   fprintf(stdout,"(Mercoledì, 16 Luglio 1969, Houston (Texas, U.S.A.))\n");
   fprintf(stdout,"(- NASA - Centro di Controllo Missioni del programma spaziale APOLLO)\n");
   fprintf(stdout,"Direttore di missione APOLLO-11 Eugene Francis Kranz\n");
   fprintf(stdout,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
   return;
}
/* Fine della funzione contrib(). */


/* -------------------------------------------------- */
/* Funzione di controllo(1) per un gruppo di opzioni. */
short globopts(void) {

/* Dichiarazione di variabili esterne. */
   extern char option;

/* Corpo funzione. */
   switch(option) {
      case NOPT:         /* Nessuna opzione. Argomento numerico. */
         return NOGLOP;

   /* Supportano lo Switch 'L' e richiedono due argomenti numerici. */
      case PLIST:        /* Opzione '-L'. */
      case NSDIV:        /* Opzione '-Q'. */
      case PJUMS:        /* Opzione '-J'. */
      case LKEYS:        /* Opzione '-E'. */
         return GLOB0;
   }
   return ERRSL; /* Codice di ritorno se l'opzione esiste ed è errata. */
}
/* Fine della funzione globopts(). */


/* ------------------------------------------------------- */
/* Funzione di controllo(2) di speciali gruppi di opzioni. */
short globoptions(void) {

/* Dichiarazione di variabili esterne. */
   extern char option;

/* Corpo funzione. */
   switch(option) {
      case NOPT:         /* Nessuna opzione. Argomento numerico. */
         return NOGOPT;

   /* Non supportano alcuno Switch, e richiedono due o tre argomenti numerici. */
      case GEMS:        /* Opzione '-G'. */
      case STAT:        /* Opzione '-T'. */
      case BASE:        /* Opzione '-B'. */
      case VARS:        /* Opzione '-V'. */
      case CALC:        /* Opzione '-C'. */
         return GLOB1;

   /* Supportano anche gli Switch che richiedono obbligatoriamente tre argomenti. */
   /* Le opzioni '-D' (DIVS) e '-K' (KEYS) non supportano lo Switch 'P' (PME). */
   /* Nessuna opzione supporta lo Switch 'T' (TBL). */
   /* Nessuna opzione supporta lo Switch 'L' (LST). */
   /* Nessuna opzione supporta lo Switch 'C' (CNT). */
      case TINS:         /* Opzione '-Y'. */
      case SYMP:         /* Opzione '-S'. */
      case FORM:         /* Opzione '-F'. */
      case DIVS:         /* Opzione '-D'. */
      case KEYS:         /* Opzione '-K'. */
         return GLOB2;

   /* Supportano anche gli Switch, ma richiedono obbligatoriamente solo due argomenti. */
   /* L'opzione '-P' (PRIME) supporta gli Switch 'T' (TBL), 'N' (NPR) e 'C' (CNT). */
   /* L'opzione '-N' (NPRIM) supporta solo lo Switch 'T' (TBL). */
   /* L'opzione '-A' (ALLDP) supporta solo lo Switch 'L' (LST). */
   /* Le opzioni '-L' (PLIST) ed '-Q' (NSDIV) supportano solo lo Switch 'L' (LST). */
   /* Le opzioni '-J' (PJUMS) ed '-E' (LKEYS) supportano solo lo Switch 'L' (LST). */
      case PRIME:        /* Opzione '-P'. */
      case NPRIM:        /* Opzione '-N'. */
      case PLIST:        /* Opzione '-L'. */
      case NSDIV:        /* Opzione '-Q'. */
      case PJUMS:        /* Opzione '-J'. */
      case LKEYS:        /* Opzione '-E'. */
      case ALLDP:        /* Opzione '-A'. */
         return GLOB3;
   }
   return ERRSG; /* Codice di ritorno se l'opzione esiste ed è errata. */
}
/* Fine della funzione globoptions(). */


/* ------------------------------------------------------------ */
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
      case LKEYS:      /* Opzione '-E'. */
         return ONEY;
      case TINS:       /* Opzione '-Y'. */
      case SYMP:       /* Opzione '-S'. */
      case FORM:       /* Opzione '-F'. */
      case ALLDP:      /* Opzione '-A'. */
         return TWOS;
      case PRIME:      /* Opzione '-P'. */
      case PLIST:      /* Opzione '-L'. */
      case GEMS:       /* Opzione '-G'. */
      case PJUMS:      /* Opzione '-J'. */
         return THRE;
      case NPRIM:      /* Opzione '-N'. */
         return NPM;
      case STAT:       /* Opzione '-T'. */
         return STT;
      case BASE:       /* Opzione '-B'. */
         return BSS;
      case VARS:       /* Opzione '-V'. */
         return VRS;
      case CALC:       /* Opzione '-C'. */
         return CLC;
      case QHLP:       /* Opzione speciale '-H'. */
      case LINF:       /* Opzione speciale '-?'. */
         return INFO;
      case EHLP:       /* Opzione speciale '--' (HELP). */
         return HLP;
   }
   return ERRS; /* Codice di ritorno se l'opzione esiste ed è errata. */
}
/* Fine della funzione trueoptions(). */


/* ------------------------------------------- */
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
      case POS:          /* Switch 'N'. */
         return PNCPOS;
      case CNT:          /* Switch 'C'. */
         return CNTPRM;
      case TCN:          /* Switch 'B'. */
         return TABCNT;
      case RNC:          /* Switch 'R'. */
         return ROWPOS;
      case DVS:          /* Switch 'V'. */
         return DVSVAL;
      case DRW:          /* Switch 'W'. */
         return DRWSPC;
      case ISW:          /* Switch 'I'. */
      case SSC:          /* Switch 'F'. */
      case MAN:          /* Switch 'M'. */
      case RIO:          /* Switch 'O'. */
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
   short globopts(void);
   short trueoptions(void);
   short trueswitch(void);

/* Dichiarazione di variabili esterne. */
   extern char option,subopt;

/* Corpo funzione. */
/* Se nessuna opzione esiste. */
   if(option==NOPT&&subopt==NSWT)
      return OK;

/* Se le opzioni sono: '-S', '-F' o '-Y'. */
/* Se gli Switch sono: 'S', 'U', 'D' o 'P'. */
   else if(trueoptions()==TWOS&&trueswitch()<=TRUEPM)
      return OK;

/* Se l'opzione è: '-A'. */
/* Se lo Switch è 'L'. */
   else if(option==ALLDP&&trueswitch()==LISTSW)
      return OK;

/* Se l'opzione è: '-D'. */
/* Se lo SWitch è: 'W'. */
   else if(option==DIVS&&trueswitch()==DRWSPC)
      return OK;

/* Se l'opzione è: '-Q'. */
/*Se lo Switch è : 'R'. */
   else if(option==NSDIV&&trueswitch()==ROWPOS)
      return OK;

/* Se le opzioni sono: '-D' o '-K'. */
/* Se gli Switch sono: 'S', 'U' o 'D'. */
   else if((option==DIVS||option==KEYS)
    &&trueswitch()<=TRUESW)
      return OK;

/* Se le opzioni sono: '-D' o '-Q'. */
/* Se lo Switch è 'V'. */
   if((option==DIVS||option==NSDIV)
    &&trueswitch()==DVSVAL)
      return OK;

/* Se le opzioni sono: '-L', '-Q', '-J' o '-E'. */
   else if(globopts()==GLOB0&&trueswitch()==LISTSW)
      return OK;

/* Se l'opzione è: '-P'. */
/* Se gli Switch sono 'T', 'N' o 'C'. */
   else if(option==PRIME&&(trueswitch()==LISTSW
    ||trueswitch()==PNCPOS||trueswitch()==NCOLTP
    ||trueswitch()==CNTPRM))
      return OK;

/* Se l'opzione è '-L'. */
/* Se gli Switch sono 'L', 'N', 'R', 'C' o 'B'. */
   else if(option==PLIST&&(trueswitch()==PNCPOS
    ||trueswitch()==ROWPOS||trueswitch()==CNTPRM
    ||trueswitch()==TABCNT))
      return OK;

/* Se le opzioni sono '-P' o '-L'. */
/* Se lo Switch è 'N'. */
   else if((option==PRIME||option==PLIST)
    &&trueswitch()==PNCPOS)
     return OK;

/* Se l'opzione è '-N'. */
/* Se lo Switch è 'T'. */
   else if(option==NPRIM&&trueswitch()==NCOLTP)
      return OK;

/* Se l'opzione speciale è: '-?'. */
/* Se gli Switch sono 'I', 'F' o 'M'. */
   else if(option==LINF&&trueswitch()==SPECSW)
      return OK;

/* Se L'opzione speciale è: '--'. */
/* Se lo Switch è 'HELP'. */
   else if(option==EHLP&&trueswitch()==HELPSW)
      return OK;

/* Se le opzioni sono:  '-P', '-N', '-L', '-Q', - */
/* -> '-K', '-G', '-J', '-E', '-T', '-B', '-V' o '-C'. */
/* Controllo necessario per le opzioni eseguite senza Switch - */
/* -> che lo supportano oppure che non lo supportano. */
   else if(((trueoptions()>=THRE&&trueoptions()<HLP)
    &&trueswitch()==NOSWT)||((option==NSDIV||option==KEYS
    ||option==GEMS||option==LKEYS||option==ALLDP)
    &&trueswitch()==NOSWT))
      return OK;

/* Se le opzioni sono: -T', '-B', '-V' o '-C'. */
   else if(globoptions()==GLOB1&&trueswitch()==NOSWT)
      return OK;

/* Se le opzioni speciali sono: '-H', '--' e '-?'. */
   else if(trueoptions()==INFO&&trueswitch()==NOSWT)
      return OK;

   /* Se nessuna opzione e/o Switch risultano validi. */
   else
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
         fprintf(stderr,"Erreur : Mauvaise option et mauvais Switch !\n\n");
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
         fprintf(stderr,"Erreur : Combinaison d'option non valide avec Switch !\n\n");
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
         fprintf(stderr,"Erreur : Option, Switch et arguments manquants !\n\n");
         return ERROR;
      case 1084:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Opção, Switch e argumentos faltando!\n\n");
         return ERROR;
      case 1085:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Option, Schalter und Argumente fehlen!\n\n");
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
         fprintf(stderr,"Erreur : Suject incorrect !\n\n");
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
         fprintf(stderr,"Erreur : Argument incorrect et/ou manquant !\n\n");
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
         fprintf(stderr,"Erreur : Option et/ou arguments incorrects !\n\n");
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
         fprintf(stderr,"Erreur : Trop de suject !\n\n");
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
         fprintf(stderr,"Erreur : Aucun argument requis !\n\n");
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
         fprintf(stderr,"Erreur : Arguments incorrects ! Des valeurs hors limites.\n\n");
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
         fprintf(stderr,"Erreur : Valeurs d'argument inversées !\n\n");
         return ERROR;
      case 1154:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Valores dos argumentos invertidos!\n\n");
         return ERROR;
      case 1155:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Argumentwerte vertauscht!\n\n");
         return ERROR;

      case 1160:   /* ENGLISH. */
         fprintf(stderr,"Error: Range of values entered too large!\n\n");
         return ERROR;
      case 1161:   /* ITALIANO. */
         fprintf(stderr,"Errore: Intervallo dei valori immessi troppo grande!\n\n");
         return ERROR;
      case 1162:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡El rango de valores ingresados es demasiado grande!\n\n");
         return ERROR;
      case 1163:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : La plage de valeurs saisie est trop large !\n\n");
         return ERROR;
      case 1164:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: O intervalo de valores inserido é muito grande!\n\n");
         return ERROR;
      case 1165:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Der eingegebene Wertebereich ist zu groß!\n\n");
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
         fprintf(stderr,"\nErreur : Valeur sélectionnée trop grande ou trop petite !\n\n");
         return ERROR;
      case 1194:   /* PORTUGÛES. */
         fprintf(stderr,"\nErro: Valor selecionado muito grande ou muito perqueno!\n\n");
         return ERROR;
      case 1195:   /* DEUTCHE. */
         fprintf(stderr,"\nFehler: Ausgewahlter Wert zu groß zu klein!\n\n");
         return ERROR;

      case 1200:   /* ENGLISH. */
         fprintf(stderr,"Error: Invalid range of values entered!\n\n");
         return ERROR;
      case 1201:   /* ITALIANO. */
         fprintf(stderr,"Errore: Intervallo dei valori immessi non valido!\n\n");
         return ERROR;
      case 1202:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Rango de valores ingresado no válido!\n\n");
         return ERROR;
      case 1203:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Plage de valeurs saisie invalide !\n\n");
         return ERROR;
      case 1204:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Intervalo de valores inserido inválido!\n\n");
         return ERROR;
      case 1205:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Ungültiger Wertebereich eingegeben!\n\n");
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
         fprintf(stderr,"Erreur : Série numérique invalide !\n\n");
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
         fprintf(stderr,"Erreur : Valeur sélectionnée hors limite !\n\n");
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
         fprintf(stderr,"Erreur : L'option n'accepte aucun type de Switch !\n\n");
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

      case 1270:   /* ENGLISH. */
         fprintf(stderr,"Error: \n");
         return ERROR;
      case 1271:   /* ITALIANO. */
         fprintf(stderr,"Errore: \n");
         return ERROR;
      case 1272:   /* ESPAÑOL. */
         fprintf(stderr,"Error: \n");
         return ERROR;
      case 1273:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : \n");
         return ERROR;
      case 1274:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: \n");
         return ERROR;
      case 1275:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: \n");
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
         fprintf(stderr,"Erreur : Mauvaise option et mauvais Switch !\n");
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
         fprintf(stderr,"Erreur : Combinaison d'option non valide avec Switch !\n");
         return ERROR;
      case 1554:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Combinação inválida de opção com Switch!\n");
         return ERROR;
      case 1555:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Ungültige Kombination der Option mit Switch!\n");
         return ERROR;

      case 1620:   /* ENGLISH. */
         fprintf(stderr,"Error: Too many arguments!\n");
         return ERROR;
      case 1621:   /* ITALIANO. */
         fprintf(stderr,"Errore: Troppi argomenti!\n");
         return ERROR;
      case 1622:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Demasiados temas!\n");
         return ERROR;
      case 1623:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Trop de suject !\n");
         return ERROR;
      case 1624:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Muito tópicos!\n");
         return ERROR;
      case 1625:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Zu viele Themen!\n");
         return ERROR;

      case 1700:   /* ENGLISH. */
         fprintf(stderr,"Error: Invalid range of values entered!\n");
         return ERROR;
      case 1701:   /* ITALIANO. */
         fprintf(stderr,"Errore: Intervallo dei valori immessi non valido!\n");
         return ERROR;
      case 1702:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡Rango de valores ingresado no válido!\n");
         return ERROR;
      case 1703:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Plage de valeurs saisie invalide !\n");
         return ERROR;
      case 1704:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Intervalo de valores inserido inválido!\n");
         return ERROR;
      case 1705:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Ungültiger Wertebereich eingegeben!\n");
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
         fprintf(stderr,"Erreur : L'option n'accepte aucun type de Switch !\n");
         return ERROR;
      case 1744:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: A opção não aceita nenhum tipo de Switch!\n");
         return ERROR;
      case 1745:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Die Option akzeptiert keine Art von Switch!\n");
         return ERROR;

   /* Modello di riferimento. */
      case 1990:   /* ENGLISH. */
         fprintf(stderr,"Error: ___________________________________________\r");
         return ERROR;
      case 1991:   /* ITALIANO. */
         fprintf(stderr,"Errore: __________________________________________\r");
         return ERROR;
      case 1992:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ___________________________________________\r");
         return ERROR;
      case 1993:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : _________________________________________\r");
         return ERROR;
      case 1994:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: ____________________________________________\r");
         return ERROR;
      case 1995:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: __________________________________________\r");
         return ERROR;
   }

/* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
/* delle funzionalità interne, delle opzioni e degli Switch. */
   if(fsign)
      printf("ERROR [TRASLATION] GURU MEDITATION\n\n");
   return GURU;
}
/* Fine della funzione errorstype(). */


/* Funzione di gestione dei msg di conferma/errore. */
int filemsg(short *ffmesgc,unsigned long *fselect) {

/* dichiarazione di variabili esterne. */
   extern char *pnf;

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
         fprintf(stdout,"English language setting.\n");
         return OK;
      case 111:   /* ITALIANO. */
         fprintf(stdout,"Il file di configurazione [.firstlang.cfg] è stato creato.\n");
         fprintf(stdout,"Impostazione per la lingua italiana.\n");
         return OK;
      case 112:   /* ESPAÑOL. */
         fprintf(stdout,"El archivo de configuración [.firstlang.cfg] ha sido creado.\n");
         fprintf(stdout,"Configuración del idioma español.\n");
         return OK;
      case 113:   /* FRANÇAIS. */
         fprintf(stdout,"Le fishier de configuration [.firstlang.cfg] a été créé.\n");
         fprintf(stdout,"Configuration de la langue français.\n");
         return OK;
      case 114:   /* PORTUGÛES. */
         fprintf(stdout,"O arquivo de configuração [.firstlang.cfg] foi criado.\n");
         fprintf(stdout,"Configuração da língua portuguesa.\n");
         return OK;
      case 115:   /* DEUTCHE. */
         fprintf(stdout,"Die [.firstlang.cfg]-Konfigur ationsdatei wurde erstellt.\n");
         fprintf(stdout,"Einstellung für deutsche Sprache.\n");
         return OK;

      case 120:   /* ENGLISH. */
         fprintf(stderr,"Error: I can not open file [%s]!\n",pnf);
         return ERROR;
      case 121:   /* ITALIANO. */
         fprintf(stderr,"Errore: Non posso aprire il file [%s]!\n",pnf);
         return ERROR;
      case 122:   /* ESPAÑOL. */
         fprintf(stderr,"Error: ¡No se puede abrir el archivo [%s]!\n",pnf);
         return ERROR;
      case 123:   /* FRANÇAIS. */
         fprintf(stderr,"Erreur : Impossible d'ouvrir le fichier [%s] !\n",pnf);
         return ERROR;
      case 124:   /* PORTUGÛES. */
         fprintf(stderr,"Erro: Não é possível abrir o arquivo [%s]!\n",pnf);
         return ERROR;
      case 125:   /* DEUTCHE. */
         fprintf(stderr,"Fehler: Datei kann nicht geöffnet werden [%s]!\n",pnf);
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
         fprintf(stderr,"Erreur : Fishier [.firstlang.cfg] non enregistré !\n");
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
         fprintf(stdout,"\rErreur : Je ne peux pas accéder au fichier du manuel d'utilisation [.fr_lng_man] !\n\n");
         return ERROR;
      case 204:   /* PORTUGÛES. */
         fprintf(stdout,"\rErro: Não consigo acessar o arquivo do manual do usuário [.pt_lng_man]!\n");
         return ERROR;
      case 205:   /* DEUTCHE. */
         fprintf(stdout,"\rFehler: Auf die Benutzerhandbuchdatei [.de_lng_man] kann nicht zugegriffen werden!\n\n");
         return ERROR;

      /* Modello di riferimento. */
      case 900:   /* ENGLISH. */
         fprintf(stderr,"ENGLISH\r");
         return OK|ERROR|WARNING;
      case 901:   /* ITALIANO. */
         fprintf(stderr,"ITALIANO\r");
         return OK|ERROR|WARNING;
      case 902:   /* ESPAÑOL. */
         fprintf(stderr,"ESPAÑOL\r");
         return OK|ERROR|WARNING;
      case 903:   /* FRANÇAIS. */
         fprintf(stderr,"FRANÇAIS\r");
         return OK|ERROR|WARNING;
      case 904:   /* PORTUGÛES. */
         fprintf(stderr,"PORTUGÛES\r");
         return OK|ERROR|WARNING;
      case 905:   /* DEUTCHE. */
         fprintf(stderr,"DEUTCHE\r");
         return OK|ERROR|WARNING;
   }

/* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
/* delle funzionalità interne, delle opzioni e degli Switch. */
   if(fsign)
      printf("ERROR [TRANSLATION] GURU MEDITATION\n");
   return GURU;
}
/* Fine della funzione filemsg(). */


unsigned long primenum(unsigned long number) {

/* -------------------------------------------------------------------------- */
/* Funzione di ricerca del fattore primo di scomposizione di un numero. Se il
   numero è divisibile la funzione ritorna il primo 'fattore primo' per il quale
   esso è divisibile; se invece il numero è primo la funzione ritorna lo zero.
   Definizione dell'algoritmo:
   - NUMBER  è il numero da processare, per ricavarne i suoi fattori primi di
     scomposizione, oppure determinare se il numero stesso sia o meno primo.
   - NDIVF è il fattore primo di scomposizione incrementale, inizialmente vale 2,
     poi viene eseguito un ciclo interattivo ed NDIVF viene incrementato di 1
     se inferiore a 4, altrimenti viene incrementato di 2 unità partendo da 3,
     in tale modo vengono considerati solo numeri dispari: 3. 5, 7, 9, 11, etc,
     all'uscita del ciclo, NDIVF assume il ruolo di fattore primo attuale di
     scomposizione e può valere solo 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
     37, 41, 43 ... etc.
   - Nel ciclo si determina se 'NUMBER modulo di NDIVF' è vero o falso;
     se modulo da resto zero (vero), il ciclo interattivo viene interrotto e
     viene restiuito NDIVF, altrimenti si prosegue fino a che NDIVF * NDIVF
      è superiore a NUMBER, in tal caso NUMBER viene restituito NPR.
   Chiamata della funzione:
   - NDIVF = primenum(NUM); Se NDIVF è inferiore a radice di NUM, allora NUM
     è divisibile per NDIVF; altrimenti se NDIVF è superiore o uguale a radice
   - di NUM, allora NUM è primo.
   - La funzione restituisce ZUDV se NUM è 0; UNDV se NUM è 1; NPR se NUM è
     uguale a 2 o qualunque altro numero primo superiore; DIVSF invece se NUM
     è un qualunque numero divisibile: DIVSF è il fattore primo di scomposizione
     di NUM; se la funzione è in un ciclo NUM è anche NUMBER / DIVSF.
   - NPR vale 0; ZUDV vale 1, NDIVF è invece un numero superiore o uguale a 2.
   - Esempio di utilizzo:
     - if((ndivf=primenum(num))) printf("%lu è divisibile per %lu\n",num,ndivf);
     - if(!(ndivf=primenum(num))) printf("%lu è primo!\n",num);   */
/* -------------------------------------------------------------------------- */
/* L'algoritmo di questa funzione è sottoposto al CopyLeft 1991-2026,
   ed alla GNU Public License version 2 e 3 di Free Software Foundation.
   Rif. http://www.gnu.org/copyleft
        http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
        http://www.gnu.org/licenses/gpl-3.0.html

   Creato da G. B. alias PiErre60 (Italy) [dfact=primenum(number) ~© 1990-1991],
   e successive modifiche ~© 1997-2001-2010-2026.  */
/* -------------------------------------------------------------------------- */

/* Definizione di variabili locali. */
   unsigned long ndivf=2UL,divsf=0UL;

/* Corpo funzione. */
   if(number==0) {
      divsf=0;
      return ZUDV;    /* Lo zero per convenzione è considerato pari, non classificabile¹. */
   }
   if(number==1) {
      divsf=0;
      return UNDV;    /* Il numero uno viene considerato non classificabile, non primo³. */
   }
   if(number==2)
      return NPR;      /* Il due è considerato numero primo². */
   while((ndivf*ndivf)<=number) {          /* Ricerca del fattore primo di scomposizione del - */
      if(ndivf>3) ++ndivf;                 /* numero. Se il numero è divisibile, nella - */
      if(!(number%ndivf))                  /* variabile "divsf" è presente un fattore primo - */
         divsf=ndivf,ndivf=number/ndivf;   /* valido per il quale esso risulta divisibile. */
      ++ndivf;
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

/* Fine della funzione primenum(). */
/* ------------------------------- */


/* ---------------------------------------------------------------------- */
/* Funzione di calcolo e stampa dei fattori di divisibilità di un numero. */
int divfactors(unsigned long dfnum) {

/* -------------------------------------------------------------------- */
/* Funzione di ricerca e stampa dei valori di divisibilità di un numero
   della serie indicata. I valori di divisibilità di un numero non sono
   quasi mai necessariamente numeri primi, anzi nella maggior parte dei
   casi sono valori a loro volta divisibili ulteriormente. La funzione
   si avvale anche del contributo della funzione primenum() che ricerca
   il primo fattore di scomposizione, quindi sulla base di questo si
   determina la sequenza di ciclo per trovare tutti gli altri valori
   intermedi. Ad ogni chiamata sono calcolati tutti i valori di divisi-
   bilità di un determinato numero. Ogni valore viene memorizzato in un
   Array. all'uscita del ciclo, quando l'ultimo valore è stato trovato,
   tale Array contenente tutti i valori di divisibilità viene stampato.
   La funzione richiede un solo parametro, cioè il numero da computare.
   Nel seguente esempio viene mostato il risultato di stampa della
   funzione per il numero 123456, i valori di divisibilità sono molti
   e vengono qui stampati su due righe.
   123456 = 2 3 4 6 8 12 16 24 32 48 64 96 192 643 1286 1929 2572 3858
            5144 7716 10288 15432 20576 30864 41152 61728
   La funzione calcola i valori di divisibilità tra 4 e 4253024256.
   Valori inferiori o superiori non vengono accettati.  */
/* -------------------------------------------------------------------- */
/* By G. B. alias PiErre60 (Italy) - [state=divfactors(number) ~© 2026] */
/* -------------------------------------------------------------------- */

/* Dichiarazione di funzioni. */
   unsigned long primenum(unsigned long);

/* Dichiarazione di variabili esterne. */
   extern unsigned short column;

/* Dichiarazione di Array locale. */
   unsigned long adivs[512];

/* Dichiarazione di variabili e puntatori locali. */
   unsigned long *padivs,dfdiv=0,pzdiv=0;
   unsigned int dcnt=0,dne=0,cne=0;
   short col;

/* Limiti dei valori in ingresso. */
   if(dfnum<2||dfnum>4253024256)
      return ERROR;

/* Calcolo dei valori di divisibilità */
/* del numero attuale della serie indicata. */
   padivs=adivs;
   if(subopt==DRW&&column>0) {
      for(col=column;col>=1;col--)
         printf(" ");
   }
   if(option==NSDIV) printf(" ");
   printf(" %lu = ",dfnum);
   dfdiv=primenum(dfnum);
   pzdiv=dfnum/dfdiv;
   for(dcnt=dfdiv;dcnt<=pzdiv;dcnt++) {

   /* Trova il valore di divisibilità. */
      if(!(dfnum%dcnt)) {
         *padivs=dcnt;
         padivs++,dne++;
      }
   }

/* Stampa dei valori di divisibilità */
/* del numero attuale della serie indicata. */
   padivs=adivs;
   for(cne=0;cne<dne;cne++)
     printf("%lu ",*padivs++);
   printf("\n");
   return OK;
}
/* Fine della funzione divfactors. */


/* --------------------------------------------------------------------- */
/* Funzione di ricerca e stampa formattata dei fattori di scomposizione. */
void primefact(unsigned long lnum, unsigned long llimt) {

/* Dichiarazione di funzioni. */
   unsigned long primenum(unsigned long);
   short trueoptions(void);
   short trueswitch(void);

/* Dichiarazione di variabili esterne. */
   extern char option,subopt;
   extern unsigned long eval[];
   extern unsigned short swflag;
   extern unsigned short keycnt,cnt,fgem;
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
   if(option!=KEYS&&option!=LKEYS&&trueswitch()<=TRUEPM&&!swflag) {
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
      if(trueoptions()==TWOS||option==DIVS||option==NOPT) {
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

      /* Se le opzioni sono: '-N', '-P', '-G', '-L', '-Q', '-V' o '-C'. */
         if(trueoptions()==THRE||option==NSDIV||option==VARS
          ||option==CALC||option==NPRIM) {
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

      /* Se l'opzione è '-K' oppure '-E' non fare nulla. */
         else if(option==KEYS||option==LKEYS);
         else {

         /* Questo blocco non dovrebbe mai esse eseguito. */
         /* Se viene eseguito questo blocco si è in presenza di un grave errore. */
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
      if(nums==ZUDV) {
         *peval=nums;
         break;
      }
   /* Esecuzione se il numero in ingresso è uno. */
      if(nums==UNDV) {
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
         if(option==KEYS||option==LKEYS) {

         /* Conta il numero dei fattori primi di scomposizione. */
         /* Resetta il flag globale per il controllo della stampa. */
            cfs++,cnt=0;

         /* Se i fattori primi di scomposizione sono superiori a due - */
         /* imposta il flag globale cnt per il controllo della stampa. */
            if(cfs>1) cnt=1;
            if(cnt==1)
               break;
         }
      }
   }
   if(option==KEYS||option==LKEYS) {

   /* Se i fattori primi di scomposizione sono superiori a due - */
   /* imposta il flag globale cnt per il controllo della stampa. */
      if(cfs>1) cnt=1;
      else keycnt++;
   }
   peval=eval;   /* Ripristino alla base dell' array del puntatore. */
/* Fine della routine di memorizzazione. */

/* -------------------------------------------------------------------- */
/* Stampa dei fattori di scomposizione del numero indicato nella serie. */
   if(option==SYMP) {

   /* ------------------------------- */
   /* Loop di stampa semplificata. */
   /* Esecuzione se l'opzione è SYMP. */
      while(*peval) {
         printf("%lu",*peval++);
         if(*peval)
            printf(" ");
      }
      putchar('\n');
      return;
   }
/* Fine loop di stampa semplificata. */

   else {

   /* Se l'opzione è '-K' oppure '-E'. */
      if(option==KEYS||option==LKEYS) {
         if(cnt==0) {

         /* Se l'opzione è 'E' con lo Switch 'L' */
            if(option==LKEYS&&subopt==LST) {

            /* Giustificazione di stampa con lo Switch 'L'. */
               if(llimt<10) printf("         ");
               if(llimt>=10&&llimt<100) printf("        ");
               if(llimt>=100&&llimt<1000) printf("       ");
               if(llimt>=1000&&llimt<10000) printf("      ");
               if(llimt>=10000&&llimt<100000) printf("     ");
               if(llimt>=100000&&llimt<1000000) printf("    ");
               if(llimt>=1000000&&llimt<10000000) printf("   ");
               if(llimt>=10000000&&llimt<100000000) printf("  ");
               if(llimt>=100000000&&llimt<1000000000) printf(" ");
               if(llimt>=1000000000);
            }

         /* Se sono presenti gli Switch 'S', 'U' o 'D'. */
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

         /* Se sono assenti gli Switch 'S', 'U' o 'D'. */
            else {
               if(option==KEYS) printf(" ");
               if(ncx==1) printf(" %1lu = ",knum);
               else if(ncx==2) printf(" %2lu = ",knum);
               else if(ncx==3) printf(" %3lu = ",knum);
               else if(ncx==4) printf(" %4lu = ",knum);
               else if(ncx==5) printf(" %5lu = ",knum);
               else if(ncx==6) printf(" %6lu = ",knum);
               else if(ncx==7) printf(" %7lu = ",knum);
               else if(ncx==8) printf(" %8lu = ",knum);
               else if(ncx==9) printf(" %9lu = ",knum);
               else {
                  if(ncx==10) printf(" %10lu = ",knum);
               }
            }

         /* ------------------------------------------------------- */
         /* Loop di stampa formattata dei fattori di scomposizione. */
         /* Esecuzione della stampa se l'opzione è KEYS o LKEYS. */
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
            putchar('\n');
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
         putchar('\n');
         return;
      }
      /* Fine del loop di stampa formattata dei fattori di scomposizione. */
      /* ---------------------------------------------------------------- */
   }
}
/* Fine della funzione primefact(). */


/* -------------------------------------------------------------- */
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


/* ----------------------------------------------------------------------- */
/* Funzione per l'icolonnamento della serie dei numeri primi e divisibili. */
short tpcol(unsigned long numbas,unsigned long numlim,short *flang) {

/* Dichiarazione di funzioni. */
   unsigned long primenum(unsigned long);   /* Ricerca del numero primo. */
   int filemsg(short *,unsigned long *);    /* Gestione dei msg di conferma/errore. */

/* Dichiarazione di variabili esterne. */
   extern unsigned long select;
   extern unsigned short fldp;
   extern short fsign,lang,fmesg;

/* Definizione di variabili locali. */
   unsigned long numsav,factbas;
   unsigned long count=0,pcount=0,dcount=0,dstamp=0;
   unsigned int clp=99,col=1,nc=1;

/* Inizializzazione di variabili. */
   numsav=numbas;

/* Corpo funzione. */
   if((numlim-numbas)>RGTAB)
      return ERROR;
   if(numlim<10) col=19,nc=1;
   if(numlim>=10&&numlim<=99) col=19,nc=2;
   if(numlim>=100&&numlim<=999) col=16,nc=3;
   if(numlim>=1000&&numlim<=9999) col=14,nc=4;
   if(numlim>=10000&&numlim<=99999) col=12,nc=5;
   if(numlim>=100000&&numlim<=999999) col=11,nc=6;
   if(numlim>=1000000&&numlim<=9999999) col=10,nc=7;
   if(numlim>=10000000&&numlim<=99999999) col=9,nc=8;
   if(numlim>=100000000&&numlim<=999999999) col=8,nc=9;
   if(numlim>=1000000000) col=7,nc=10;
   putchar('\n');
   while(numsav<=numlim) {

   /* Discrimina e stampa solo i valori dispari. */
   /* Stampa tabellare per l'opzione '-nT'. */
      if(option==NPRIM&&!(numsav%2)) {
         numsav++,count++,++dcount;
         continue;
      }

      if(!fldp) {
         if(!(factbas=primenum(numsav))) {
            if(factbas==ZUDV||factbas==UNDV)
               numsav=1UL;
            if(clp==99) {
               if(numsav<10000000&&numlim>=10000000)
                  clp=0,printf(" ");
               if(numsav>=10000000)
                  clp=0,printf(" ");
               else clp=0;
            }
            if(clp==col) {
               clp=0; putchar('\n');
               if(numsav<10000000&&numlim>=10000000)
                  printf(" ");
               if(numsav>=10000000)
                  printf(" ");
            }
            if(nc==1) printf(" %1.0lu  ",numsav);
            if(nc==2) printf(" %2.0lu  ",numsav);
            if(nc==3) printf(" %3.0lu  ",numsav);
            if(nc==4) printf(" %4.0lu  ",numsav);
            if(nc==5) printf(" %5.0lu  ",numsav);
            if(nc==6) printf(" %6.0lu  ",numsav);
            if(nc==7) printf(" %7.0lu  ",numsav);
            if(nc==8) printf(" %8.0lu  ",numsav);
            if(nc==9) printf(" %9.0lu  ",numsav);
            if(nc==10) printf(" %10.0lu  ",numsav);
            pcount++,clp++;
         }
      }
      else {
         if((factbas=primenum(numsav))) {
            if(factbas==ZUDV||factbas==UNDV)
               numsav=4UL;
            if(clp==99) {
               if(numsav<10000000&&numlim>=10000000)
                  clp=0,printf(" ");
               if(numsav>=10000000)
                  clp=0,printf(" ");
               else clp=0;
            }
            if(clp==col) {
               clp=0; putchar('\n');
               if(numsav<10000000&&numlim>=10000000)
                  printf(" ");
               if(numsav>=10000000)
                  printf(" ");
            }
            if(nc==1) printf(" %1.0lu  ",numsav);
            if(nc==2) printf(" %2.0lu  ",numsav);
            if(nc==3) printf(" %3.0lu  ",numsav);
            if(nc==4) printf(" %4.0lu  ",numsav);
            if(nc==5) printf(" %5.0lu  ",numsav);
            if(nc==6) printf(" %6.0lu  ",numsav);
            if(nc==7) printf(" %7.0lu  ",numsav);
            if(nc==8) printf(" %8.0lu  ",numsav);
            if(nc==9) printf(" %9.0lu  ",numsav);
            if(nc==10) printf(" %10.0lu  ",numsav);
            dcount++,clp++,dstamp++;
         }
      }
      numsav++,count++;
   }
   if(pcount||dcount)
      putchar('\n');
   else {

   /* Visualizza < LISTA VUOTA > per l'opzione '-P'. */
      fmesg=MSGBASE+lang+70;
      filemsg(&fmesg,&select);
   }
   if(numbas==0||numbas==2) dcount-=1;   /* Esclude 0 e 2. */
   if(*flang==ENGLISH) {
      if(numlim<100000) {
         printf("\n--------------------------\n");
         printf("Series from number: %6.1lu\n",numbas);
         printf("To number:          %6.1lu\n",numlim);
         printf("Processed numbers:  %6.1lu\n",count);
         if(!fldp)
            printf("Prime numbers:      %6.1lu\n\n",pcount);
         else {
            printf("Divisible numbers:  %6.1lu\n",dcount);
            printf("Numbers shown:      %6.1lu\n\n",dstamp);
         }
      }
      else {
         printf("\n------------------------------\n");
         printf("Series from number: %10.1lu\n",numbas);
         printf("To number:          %10.1lu\n",numlim);
         printf("Processed numbers:      %6.1lu\n",count);
         if(!fldp)
            printf("Prime numbers:          %6.1lu\n\n",pcount);
         else {
            printf("Divisible numbers:      %6.1lu\n",dcount);
            printf("Numbers shown:          %6.1lu\n\n",dstamp);
         }
      }
      return OK;
   }
   if(*flang==ITALIANO) {
      if(numlim<100000) {
         printf("\n-------------------------\n");
         printf("Serie dal numero:  %6.1lu\n",numbas);
         printf("Al numero:         %6.1lu\n",numlim);
         printf("Numeri processati: %6.1lu\n",count);
         if(!fldp)
            printf("Numeri primi:      %6.1lu\n\n",pcount);
         else {
            printf("Numeri divisibili: %6.1lu\n",dcount);
            printf("Numeri mostrati:   %6.1lu\n\n",dstamp);
         }
      }
      else {
         printf("\n-----------------------------\n");
         printf("Serie dal numero:  %10.1lu\n",numbas);
         printf("Al numero:         %10.1lu\n",numlim);
         printf("Numeri processati:     %6.1lu\n",count);
         if(!fldp)
         printf("Numeri primi:          %6.1lu\n\n",pcount);
         else {
            printf("Numeri divisibili:     %6.1lu\n",dcount);
            printf("Numeri mostrati:       %6.1lu\n\n",dstamp);
         }
      }
      return OK;
   }
   if(*flang==ESPANOL) {
      if(numlim<100000) {
         printf("\n-----------------------------\n");
         printf("Serie desde el número: %6.1lu\n",numbas);
         printf("Al número:             %6.1lu\n",numlim);
         printf("Números processados:   %6.1lu\n",count);
         if(!fldp)
            printf("Números primos:        %6.1lu\n\n",pcount);
         else {
            printf("Números divisibles:    %6.1lu\n",dcount);
            printf("Números mostrados:     %6.1lu\n\n",dstamp);
         }
      }
      else {
         printf("\n---------------------------------\n");
         printf("Serie desde el número: %10.1lu\n",numbas);
         printf("Al número:             %10.1lu\n",numlim);
         printf("Números processados:       %6.1lu\n",count);
         if(!fldp)
            printf("Números primos:            %6.1lu\n\n",pcount);
         else {
            printf("Números divisibles:        %6.1lu\n",dcount);
            printf("Números mostrados:         %6.1lu\n\n",dstamp);
         }
      }
      return OK;
   }
   if(*flang==FRANCAIS) {
      if(numlim<100000) {
         printf("\n---------------------------------\n");
         printf("Série à partir du numéro : %6.1lu\n",numbas);
         printf("Au numéro :                %6.1lu\n",numlim);
         printf("Numéros traités :          %6.1lu\n",count);
         if(!fldp)
            printf("Nombres premiers :         %6.1lu\n\n",pcount);
         else {
            printf("Nombres divisibles :       %6.1lu\n",dcount);
            printf("Chiffres affichés :        %6.1lu\n\n",dstamp);
         }
      }
      else {
         printf("\n-------------------------------------\n");
         printf("Série à partir du numéro : %10.1lu\n",numbas);
         printf("Au numéro :                %10.1lu\n",numlim);
         printf("Numéros traités :              %6.1lu\n",count);
         if(!fldp)
            printf("Nombres premiers :             %6.1lu\n\n",pcount);
         else {
            printf("Nombres divisibles :           %6.1lu\n",dcount);
            printf("Chiffres affichés :            %6.1lu\n\n",dstamp);
         }
      }
      return OK;
   }
   if(*flang==PORTUGUES) {
      if(numlim<100000) {
         printf("\n--------------------------------\n");
         printf("Série a partir do número: %6.1lu\n",numbas);
         printf("Para o número:            %6.1lu\n",numlim);
         printf("Números processados:      %6.1lu\n",count);
         if(!fldp)
            printf("Números primos:           %6.1lu\n\n",pcount);
         else {
            printf("Números divisíveis:       %6.1lu\n",dcount);
            printf("Números apresentados:     %6.1lu\n\n",dstamp);
         }
      }
      else {
         printf("\n------------------------------------\n");
         printf("Série a partir do número: %10.1lu\n",numbas);
         printf("Para o número:            %10.1lu\n",numlim);
         printf("Números processados:          %6.1lu\n",count);
         if(!fldp)
            printf("Numeros primos:               %6.1lu\n\n",pcount);
         else {
            printf("Números divisíveis:           %6.1lu\n",dcount);
            printf("Números apresentados:         %6.1lu\n\n",dstamp);
         }
      }
      return OK;
   }
   if(*flang==DEUTCHE) {
      if(numlim<100000) {
         printf("\n---------------------------\n");
         printf("Serie ab Nummer:     %6.1lu\n",numbas);
         printf("Zur Nummer:          %6.1lu\n",numlim);
         printf("Verarbeitete Zahlen: %6.1lu\n",count);
         if(!fldp)
            printf("Primzahlen:          %6.1lu\n\n",pcount);
         else {
            printf("Teilbare Zahlen:     %6.1lu\n",dcount);
            printf("Angezeigte Zahlen:   %6.1lu\n\n",dstamp);
         }
      }
      else {
         printf("\n-------------------------------\n");
         printf("Serie ab Nummer:     %10.1lu\n",numbas);
         printf("Zur Nummer:          %10.1lu\n",numlim);
         printf("Verarbeitete Zahlen:     %6.1lu\n",count);
         if(!fldp)
            printf("Primzahlen:              %6.1lu\n\n",pcount);
         else {
            printf("Teilbare Zahlen:         %6.1lu\n",dcount);
            printf("Angezeigte Zahlen:       %6.1lu\n\n",dstamp);
         }
      }
      return OK;
   }
   else {

   /* Lista di segnali per Debug e codici di errore per incompleta implementazione - */
   /* delle funzionalità interne, delle opzioni e degli Switch. */
      if(fsign) {
         printf("ERROR [IQ_STAT] GURU MEDITATION\n\n");
         return GURU;
      }
   }
   return OK;
}
/* Fine della funzione tpcols(). */


/* -------------------------------------------------------------- */
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
