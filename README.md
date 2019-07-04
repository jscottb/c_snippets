# c_snippets
Repository for old Bob Stout Snippets collection.

Welcome to The Snippets Collection

Please observe freeware/copyright notice in snippets.(c)

read.me		Last minute information and instructions
file_id.diz		File info for BBS's
snippets.txt		General information about SNIPPETS
snippets.(c)		SNIPPETS freeware notice
snippets.ndx		SNIPPETS index - this file
snippets.wc		Count of SNIPPETS files
missing.txt		Rationale of files deleted since last SNIPPETS
nonmsdos.txt		List of universal SNIPPETS functions
dosfuncs.txt		List of MS/PC-DOS-specific SNIPPETS functions
pdn.lst	Janis Kracht	List of PDN sites
make.ini	Jim Nutt	Master file for NDMAKE
ansiscrn.h		Macros for ANSI.SYS screen control
cast.h	Bob Stout	Cast any object to any type
dd_struc.h	Wayne Hamilton	TC/TC++/BC++ DOS file time/date macros
hilobyte.h		Extract high, low bytes from an int
pi.h		Useful definitions using PI
portable.h	Scott Ladd	Write portable code for various PC compilers
round.h	Dave Knapp	Rounding macros
scrnmacs.h	Jerry Houston	Macros for direct video work
c_lines.awk	Dan Kozak	AWK program to count lines of C code
8087_sav.asm	Jeffrey Nonken	Saves/restores 80x87 environment
coldboot.asm	David Nugent	Reliable cold/warm boot
cpucheck.asm		Determine type of CPU in use
hires.asm		Switch to 43/50 line mode on EGA/VGA
ndpcheck.asm		Determine presence of coprocessor
strecpy.asm	L. Satenstein	Like strcpy, but returns pointer to NUL
a2e.c	Bob Stout	ASCII <=> EBCDIC conversions
addhndls.c	Doug Burger 
Bob Jarvis	Allow more than 20 open files under DOS 3+ 
addpath.c	Bob Stout	Add directories to path in AUTOEXEC.BAT
amalloc.c	Paul Schlyter	Multi-dimensional array allocate ( <64K on PC)
ansiflen.c	Bob Jarvis	ANSI-compliant file size function
ansiload.c	Bob Jarvis	Detect ANSI.SYS
ansiself.c	Thad Smith	Self-replicating program in ANSI C
ansisys.c		Detect ANSI.SYS
approx.c	John Rex	Fuzzy string search
assignpr.c	Bob Stout	Multiple printer support
atr2ansi.c	Bob Stout	Build ANSI.SYS command string, given attribute
bascnvrt.c	Bob Stout	Convert radix of a numeric string
bastrngs.c	Bob Stout	BASIC-like string functions
bitarray.c		Bit array functions
bitcnt_1.c	Ratko Tomic	Count bits in a number (fast, clever)
bitcnt_2.c		Count bits in a number (fascinating)
bitfiles.c	Aare Tali	Bit I/O for buffered (fopen'ed) files
bitops.c	Bob Stout	Small bit array macros
bitstrng.c	J. Blauth	Format numeric value as string of bits
bstr_i.c	Bob Stout	Convert binary string to int
break.c	Bob Stout	Control DOS "SET BREAK=" status
bresnham.c	Brian Dessent	Draw lines and circles
calsupp.c	Ray McVay	Calendar support funtions
cant.c	Bob Stout	An fopen() replacement with error trapping
changprn.c	Bob Stout	Change the standard printer device
checkexe.c	Bob Jarvis	Checksum protection for executable files
checksum.c	Bob Stout	Calculate checksum
chgext.c	Bob Stout	Change/add a file name extension
clock.c	Jon Guthrie	On-screen clock generator
combin.c	Thad Smith III	Compute combinations without overflow
commafmt.c	Bob Stout	Add thousands separators to numeric strings
compiler.c		Test for popular PC compilers & versions
crc-16.c		Calculated 16-bit CRC
crc-16f.c		Fast 16-bit CRC
crc_32.c	Gary S. Brown	Table lookup 32-bit CRC
crypt.c	Bob Stout	S-Coder data encryption from DDJ
ctrlprnt.c	Bob Stout	Print a line, displaying Ctrl characters
cubic.c	Ross Cottrell	Solve cubic equations
cursor.c	Bill Wilkie	Cursor management/manipulation
dbl2long.c	Ross Cottrell	Rounds doubles to longs
dblround.c	Ross Cottrell	Rounds a double to nearest whole number
doscopy.c	Peter Yard	Copy a file
droptime.c	Thor Johnson	Give up time slices to Win, OS/2, etc.
drvalid.c	Bob Stout	Benignly validate disk drives
drvs.c	David Gersic	Checks for valid disk drives, local or remote
dspdtst.c		I/O benchmark - MSC/TC/ZTC/Watcom
editgets.c	Jon Burchmore 
Bob Stout	Get an input string with editing functions 
eng.c	David Harmon	Floating point value -> engineering notation
errfix.c	Bob Jarvis	Redirect stderr to a file
eval.c	Bob Stout	Simple arithmetic expression evaluator
factoryl.c	Bob Stout	Factorial, combinations, permutations
faskbhit.c	D. Goodenough	Fast kbhit() and kbflush()
favail.c	Bob Stout	How many more files may be fopen'ed?
fcompare.c	Bob Stout	Compare 2 files for equality
fcopy.c	Bob Jarvis	Copy a file
ferrorf.c	Mark Devlin	Formatted error messages
files.c	Matthew Hunt	Determine number of FILE set in CONFIG.SYS
fmtmoney.c	Bob Stout	Format US dollar amounts into text strings
fndislot.c	Bob Stout	Locate an unused user interrupt vector
format.c	Bob Stout	Use DOS format to format a diskette
fpswitch.c		Demo how to use function pointer arrays
fscanbin.c	Ray Gardner	Scan binary fields via format string
fsize.c	Bob Stout	Return true apparent size of buffered file
fsm.c		Demonstrates a finite state machine
getdcwd.c	Bob Jarvis	Get current working directory for given drive
getkey.c	Bob Stout	Get extended key codes
getseg.c	Bob Stout	Get segment and offset of any object
getstrng.c	Ron Sires	Safe gets() for input string of unknown length
glbl_env.c	Peter Thomas	Update & remove global environment variables
grafline.c	David Harmon	Demo of PC line drawing characters
hexorint.c	Bob Stout	Auto-convert hex or decimal strings
howdy.c		Obfuscated C code
hstr_i.c	Bob Stout	Convert hex string to int
hugeread.c	Bob Stout	Read & write huge data using far pointers
hugesort.c	Ray Gardner	Quicksort using huge pointers
initvars.c	Ray Gardner	Read data into variables
iscons.c	Bob Stout	Does a FILE * refer to the console?
isfopen.c	Bob Stout	Is a FILE * in use?
isisbn.c	Maynard Hogg	Validate ISBN (book) numbers
isnetdr.c	Bob Dolan	Determine is a drive is local or remote
ispow2.c		Is a number an integral power of 2?
isqrt.c		Integer square root
isramdsk.c	Bob Stout	Determine if a drive is a RAM disk
isshare.c	Mike Ratledge	Determine if file sharing is enabled
isshift.c	Jeff Dunlop	Determine if a shift key is pressed
iswprot.c	Bob Stout 
Wayne King	Determine is a floppy is write protected 
isxkbrd.c	Ed Kowalski	Detects extended (101+ key) keyboard
jdn.c	Paul Schlyter 
Ray Gardner	Julian Day Number computation 
joystick.c	Bob Stout	Joystick support functions
kb_data.c	Dan Kozak	Keyboard status determination
keylocks.c		Caps/Num lock set/clear functions
keywatch.c	Robert Mashlan	Demonstrates capturing keyboard interrupt
lbitops.c	Scott Dudley	Large bit array macros
ldfloor.c	Ray Gardner	Long double floor
ll_msort.c	Ray Gardner	Linked list mergesort
ll_qsort.c	Jon Guthrie	Linked list quicksort
lsary.c	Bob Stout	Read a directory into a linked list
ltoa.c	Bob Stout	Convert long to a string
ltostr.c	Thad Smith III	Convert long to a string
lv1ws.c	Bob Stout	Convert whitespace strings to single spaces
mainmain.c		Obfuscated C code
mcb_env.c		Modify master environment using MCB's
mdalloc.c	Blair Haukedal	Multi-dimentional array alloction
memavail.c	Thor Johnson	Report available DOS memory
memrev.c	Ray Gardner	Assymetrical memory swap
mkdirs.c	Bob Stout	Build directory tree (deep mkdir())
moon_age.c	M. Jones	Determine the phase of the moons for any date
msb2ieee.c	Jeffrey Foy	Convert MSBIN format to/from IEEE float
noctrlc.c		Traps Ctrl-C, Ctrl-Break, Ctrl-Alt-Del
noreset.c		Traps Ctrl-Alt-Del
ord_text.c	Bob Stout	Format ordinal numbers in English
os_id.h	David Gibbs	Header for determining PC OS's
os_id.c	David Gibbs	Determine PC OS
pcnvrt.c	Bob Stout	Convert Pascal strings to C
perm_idx.c	Thad Smith III	Determine permutation index
pfopen.c	David Engel	Open a file anywhere
pluraltx.c	Bob Stout	How to print proper plurals
prtoggle.c	Bob Stout	Tee stdio to stdprn
prtscrn.c	Bob Stout	Invoke BIOS print screen function
prtstat.c	Bob Stout	Determine printer status
pushdir.c	Bob Stout	Stack-oriented CHDIR functions
rand1.c	Phil Linttell	Random number generator
rand2.c	E. Schneider	Random number generator
reboot.c	Bob Stout	Simple PC reboot function in C
redir.c	F. Piette	Demonstrates output redirection
rg_isort.c	Ray Gardner	Insertion sort function
rg_qsort.c1	Ray Gardner	Non-Recursive ANSI quicksort function
rg_qsort.c2	Ray Gardner	Recursive ANSI quicksort function
rg_rand.c	Ray Gardner	Minimal random number generator
rg_ssort.c	Ray Gardner	ANSI quicksort-compatible shellsort function
rmallws.c	Bob Stout	Remove all whitespace from a string
rmlead.c	Bob Stout	Remove leading whitespace from a string
rmtrail.c	Bob Stout	Remove trailing whitespace from a string
rndmize.c		How to seed ANSI random number generator
scanfrac.c	Thad Smith III	Scans/converts text fractions
scroll.c	Bob Stout	Scroll screen function
setenvar.c	Bob Stout	Set DOS master environment *legally*
shel2dos.c	Bob Stout	Shell to DOS from a running program
soundex.c	Bob Jarvis	Standard English soundex
speed.c		Benchmark to calculate I/O performance
spin.c		Demo of how to make various text "spinners"
srchfile.c	Bob Stout	Search files for text, forwards & backwards
sstrcpy.c	Ray Gardner	Overlapping strcpy() & strcat() work-alikes
stats.c	Bob Stout	Analyze file statistics
stptok.c	Ray Gardner	Improved tokenizing function
str27seg.c	Bob Stout	Convert numeric string to 7-segment displays
strftime.c	Jim Nutt 
Rob Duff	Non-locale version of ANSI strftime() 
strrepl.c	Gilles Kohl	Replace substrings
strrev.c	Bob Stout	Reverse a string in place using XOR swapping
strsort.c	Ray Gardner	(Shell) Sort a string array
strucfil.c	Lynn Nash	Read/write structures to/from a file
style.c		Suggested coding style guidelines
tabtrick.c		Demo using printf() for columnar formatting
timegetc.c	Bob Jarvis	Wait specified time for a keypress
toascii.c		EBCDIC-ASCII conversion arrays
tp6tod.c	Thad Smith III	Convert TP 6-byte reals to C doubles
translat.c	Jerry Coffin	Translate string w/ C-style escape sequences
trim.c	Bob Stout	Trim leading, trailing, & embedded spaces
truename.c	gk	Normalize filename using undocumented DOS
unix2dos.c	Bob Stout	Convert Unix-style pathnames to DOS-style
vfname.c	Sid Rogers	Validate DOS-legal file names
video.c	Jeff Dunlop	C video information functions
wb_fcopy.c	Walter Bright	Fast file copy/append
weird.c		Obfuscated C code
whicharc.c	Heinz Ozwirk 
David Gersic	Determine which archiver used on a packed file 
windchil.c		Compute wind chill factor
wordwrap.c	Robert Morgan	Simple CRT word wrap demonstration
xstrcat.c		String concatenation funct
xstrcmp.c	S. Offermann	Compare strings using DOS wildcards
c_prec.txt		Operator precedence/associativity in C / C++
storage.typ	Jeff Galbraith	C storage types crib sheet
rtlftrul.txt		Right-left rule for reading C
ptr_help.txt	Ted Jensen	Helpful hints on pointers
c_port.txt	Joseph Carnage	How to write portable C code
enums.txt		Helpful hints for enums
which_c.txt	Bob Stout	Guidelines for choosing a PC C compiler
resource.lst	J-Mag Guthrie	C/C++ resources (books, magazines, vendors)
environ.txt	Bob Stout	Notes on changing the master environment
sharing.txt	Mike Ratledge	How to check if file sharing is active
evsavres.txt		How to blank/restore EGA/VGA screen
ansisys.txt		Chart of ANSI screen control codes
vt100.txt	Jon Guthrie	Chart of VT-100 escape codes
vio.h		Direct screen package
vio.asm		" " "
scrnsave.c	Bob Stout	Save and restore text screens
int2e.asm		Access command processor "back door"
ccomcall.c		C "glue" to use Int 2Eh
dirent.h		POSIX compliant header
rfind1st.c		Compiler-independent find first/next functions
posixdir.c		opendir(), readdir(), seekdir(), closedir()
posix_ls.c		Directory lister demo
match.h		Header file
match.c		Portable source including optional test code
match.doc		Documentation for Match.C
dirmask.c	Bob Stout	Complex pattern matching (calls patmat())
patmat.c	Sreenath Chary	String pattern matching
fln_fix.c	Bob Stout	Crunch dot directories, verify DOS-valid paths
flnorm.c	Bob Stout	Full file name normalization
uclock.h	David L. Fox	Microsecond timing function header
uclock.c	" " "	Microsecond resolution timing functions
sound.h	Bob Stout	Sound functions header
sound.c	" "	Speaker control functions
mktone.c	" "	Tone generation functions
playlib.c	Lynn R. Lively	Background music package
playdemo.c	Bob Stout	Demo of backgroud music package
getcmt.c	Greg Messer	Extract comments from C/C++ source files
testcmt.c	" "	Test file for above
scaldate.h	Ray Gardner	Scalar ("Julian") date header
scaldate.c	Ray Gardner	Scalar ("Julian") date functions
daynum.c	Bob Stout	Return statistics about a given date
cal.c	Bob Stout	Calendar using Scaldate.C
x00api.h		C header w/ prototype declarations
x00api.c		C access functions
prnspool.h		C header w/ prototype declarations
prnspool.c		PRINT.COM spool queue functions
printq.c		Demo program for above
strat.h		C header w/ prototypes and enum'ed constants
strat.c		C functions
w_wrap.h		C header w/ prototypes and enum'ed constants
w_wrap.c		C functions
center.c		Center a wrapped line
dos5boot.h		Header for boot sector access
absdiskc.c		C read and write functions
absdisk.asm		Low-level code for disk I/O, DOS 2-5
mouse.h	Bob Jarvis	Header w/ prototypes
mouse.c	Bob Jarvis	Essential mouse stuff
scrnpick.c	Ray McVay	Demo, retrieves text from screen using mouse
xfile.h		Header w/ prototypes
xfile.c		Contains xopen(), xclose(), xgetline()
xtest.c		Demo for above
getopt3.c		AT&T compatible getopt(3)
getopts.h	Bob Stout	Header for Getopts.C
getopts.c	Bob Stout	Scan command line for switches
pbmsrch.c	Jerry Coffin	Pratt-Boyer-Moore string search
bmhsrch.c	Ray Gardner	Case-sensitive Boyer-Moore-Horspool search
bmhisrch.c	Thad Smith	Case-insensitive Boyer-Moore-Horspool search
bmhasrch.c	Ray Gardner	Case-insensitive BMH search w/ accented chars
ext_keys.h		Header to define extended key codes
ext_keys.c		A getch() work-alike for extended keyboards
doansi.h		Header file
doansi_1.c		Portable intepreter
doansi_2.c		OS-specific support functions
tasker.txt		Description of Tasker functions
tasker.h		Header, structs, and prototypes
tasker.c		Detect multitasker and give up time slices
biport.h	Bob Stout	Header to port Borland _geninterrupt()
biport.c	Bob Stout	Port Borland code using pseudovariables
fmemops.c	Bob Stout	Emulate MSC's _fmemxxx() in BC++ & ZTC++
ftime.h	Jeff Dunlop	BC++-style file date/time struct & prototypes
ftime.c	Jeff Dunlop	BC++-style file date/time functions
msc_peek.c	Bob Stout	Add peek/poke to MSC
pmerge.c	Bob Stout	Portable fnmerge(), _makepath() equivalents
psplit.c	Bob Stout	Portable fnsplit(), _splitpath() equivalents
strdup.c	Bob Stout	Portable strdup()
strupr.c	Bob Stout	Portable strupr() strlwr()
vidport.c	Bob Stout	Portable gotoxy(), clrscr() equivalents, etc.
big_mall.h	Bob Stout	Portably allocate memory > 64Kb
except.doc		Information on programs below
cctrap.asm		Int 23h (Ctrl-C) trap
cbtrap.asm		Int 1Bh (Ctrl-Break) trap
trapflag.asm		Trap & flag Ints 23h & 1Bh
trapdemo.c		Demo of TRAPFLAG.ASM
cerrinst.asm		Install DOS critical error handler
cerrtrap.asm		DOS critical error handler
iostutor.txt		Tutorial for following demo code
myio.h		Header for Myio.Cpp
myio.cpp		Simple I/O class
mystream.h		iostream Interface for class Myio
mystream.cpp		ios Interface implementation
myline.h		Simple line input classes
myline.cpp		Implementation of myLine classes
myiodemo.cpp		myio Loopback demo
myio.mak		Makefile for Iostutor.Txt demo files
str.doc		Information on the string class
str.h		C++ header
str.cpp		Simple, portable C++ string class
mem.txt		Information on the Mem package
toolkit.h		Compiler-independent portability header
mem.h		Mem package header
mem.c		Mem package code
2dlife.c	Jon Guthrie	2-D Life program
bigfac.c	Carl Declerck	Do large factorials using ASCII multiply
bincomp.c	Ray Gardner	Binary file comparison utility
bordcolr.c	Bob Jarvis	Set border color
c_cmnt.c	Thad Smith	Extract comments from a C source file
cdir.c	Lynn R. Lively	Like DOS CHDIR except changes drives as well
chbytes.c	Bob Stout	Edit binary files in place
chmod.c	Bob Stout	Change DOS file attributes - wildcards, etc.
cmdline.c		Demonstation how to access command line args
commconv.c	Jari Laaksonen	Convert C++ style comments to C style
cursize.c	Bob Jarvis	Set the cursor size
do.c		Specify multiple command line commands
dossort.c	Robert Mashlan	DOS SORT work-alike
drivsrch.c	Marty Connely	Search for physical/logical drives
dspclock.c	Mike Jones	On-screen TSR clock
factor.c	Ray Gardner	Print prime factorization of a number (double)
filcount.c	Bob Stout	Count files/directories
flopcopy.c	Bob Stout	Copy a floppy to a HD subdirectory
fraction.c	Thad Smith	Convert a real number to an integer ratio
getvol.c	Bob Stout	Retrieve a disk volume label
head.c		Unix head work-alike
hexdump.c	Paul Edwards	Hex/ASCII file dump utility
ifactor.c	Ray Gardner	Print prime factorization of a number (long)
inchcvrt.c	Bob Stout	Convert inches to feet/inches and fractions
kbflip.c	Bob Stout	Set/clear Caps/Num/Scroll locks
killff.c	Jerry Gore 
Erik VanRiper	Strip FF characters from text files 
log.c	Robert Sprawls	Utility to log working time
lsd.c	Bob Stout	DOS DIR enhanced work-alike
lzhuf.c	Yoshi	Compression used in LHARC & LHA
maze_1.c	Jon Guthrie	Maze generator
maze_2.c		Obfuscated maze generator
maze_3.c		Cute maze generator. Run, then enter size.
morse.c	Mike Dodd	Convert strings to morse code
mterm.c	David Harmon	Micro terminal (comm) program - use with X00
mv.c	Ray McVay	Move files
palndrom.c	Dan Hoey	Self-replicating palindrome - try it!
permute1.c	Dave Chapman	Permute strings
permute2.c	Jon Guthrie	Permute strings
pi.c		Calculate PI to 60,000 digits or more
pr.c		Print a file with headers & breaks
query.c	Bob Stout	Timed query w/default for batch files
rdxcnvrt.c	Bob Stout	Convert between number bases
remtab.c	Robert Mashlan	Convert tabs to spaces
rm_all.c	Bob Stout	Remove all files - now supports recursion
roman.c	Jim Walsh	Convert Arabic number to Roman numeral
setimeto.c	Bob Stout	Set a file's time/datestamp to match another's
setvol.c	Bob Stout	Set, change, or kill a disk volume label
split.c	Bob Stout	Split large text files into smaller ones
stripeof.c	Bob Stout	Strip ^Z characters from DOS text files
stub.c	Bob Stout	Truncate .OBJ (and other) files
sunriset.c	Paul Schlyter	Computes length of day at any place on Earth
tail.c	Joe Huffman 
Ruurd Pels	Print last n (default = 5) lines of a file 
todaybak.c	Bob Stout	Back up today's files to a floppy
touch.c	Ray L. McVay	TC/TC++/BC++ set file time/date stamp
treedir.c	Bob Stout	Recursive directory lister
uuencode.c	Don Kneller	Unix uuencode
uudecode.c	John Lots	Unix uudecode
wc.c	Jay Elkes	Like Unix wc, counts lines, words, chars
where.c		Search for a file
jgrep.c	Jerry Coffin	Simple and portable
grep.c	DECUS 
"Real" grep - free with some strings 
http://www.cs.umu.se/~isak/Snippets/ - English version - May 6 1997 - Isak Jonsson <isak@cs.umu.se> - DTD validated
