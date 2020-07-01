# Precompiled-OpenSSL-Windows
Precompiled OpenSSL for Windows (Include Static and Dynamic Library).

This is a copy from: https://www.npcglib.org/~stathis/blog/precompiled-openssl/ (you can download .7zip files in this url) 

Just use the OpenSSL project of your Visual Studio version.

If you want use OpenSSL as Static Library just link static library files (.lib) with your project.

Library versions in lib/ dir:
* libcryptoMD.lib
* libcryptoMDd.lib
* libcryptoMT.lib
* libcryptoMTd.lib
* libsslMD.lib
* libsslMDd.lib
* libsslMT.lib
* libsslMTd.lib

Libs PATH: 
* x86: openssl-X-vsX/lib
* x64: openssl-X-vsX/lib64

Headers PATH:
* x86: openssl-X-vsX/include
* x64: openssl-X-vsX/include64

Bins PATH:
* x86: openssl-X-vsX/bin
* x64: openssl-X-vsX/bin64

-----
I compile many different versions of OpenSSL with MSVC. I have written a batch script to ease this process. To use it you basically need the source code, Cygwin and Microsoft Visual Studio. I use these builds to subsequently compile other libraries, e.g. Qt4 and Qt5. The main difference from the official release is that I patch the sources to allow compiling libraries with filenames that reflect the compile configuration, which makes it easier to use later. It is best to use the latest version always.

Please note that the OpenSSL Project (http://www.openssl.org) is the only official source of OpenSSL.

These builds are created for my own personal use, they are custom, unsupported and experimental and therefore you are utilizing them at your own risk. My builds are not endorsed by The OpenSSL Project in any way. I build these in the context of my own work and spare time, I do NOT charge any money, I do NOT make any money … and NO I do NOT accept any donations!

If you really like OpenSSL, if it has helped you or your company in any way, or you are feeling like giving back anyway, then please donate directly to the OpenSSL Project: https://www.openssl.org/support/donations.html. The developers and countless contributors deserve it!

If you are looking for older builds, go to the Precompiled OpenSSL (Past Builds) page, but you are strongly encouraged to only use the latest.

OpenSSL v1.1.0e (stable)

Updated: 17 Jan 2017
Source Code: ftp://ftp.openssl.org/source/openssl-1.1.0e.tar.gz
Batch Script: build-openssl-1.1.0e.bat
Patches: [patch]
Custom suffixes (MD for dynamic libraries and MT for static libraries + “d” for debug builds)
Notes:
All statically built libraries link against the Static Runtimes (/MT instead of /MD).
Build Instructions:
Download the build-openssl batch file and all listed patches (place them in the same directory).
Download and decompress the official sources in their own directory.
Check and modify the configuration options in the batch script.
Patch the sources: build-openssl-1.1.0e.bat patch
Build everything: build-openssl-1.1.0e.bat build all
Package: build-openssl-1.1.0e.bat package all
Precompiled OpenSSL
Compiler	Download	Size	Arch	Build	Link	Notes
MSVC 2015	openssl-1.1.0e-vs2015.7z [md5]	15.7 MB	x86 (32-bit)
x64 (64-bit)	debug
release	shared
static	
MSVC 2013	openssl-1.1.0e-vs2013.7z [md5]	14.1 MB	x86 (32-bit)
x64 (64-bit)	debug
release	shared
static	
MSVC 2012	openssl-1.1.0e-vs2012.7z [md5]	14 MB	x86 (32-bit)
x64 (64-bit)	debug
release	shared
static	
MSVC 2010	openssl-1.1.0e-vs2010.7z [md5]	14.1 MB	x86 (32-bit)
x64 (64-bit)	debug
release	shared
static	
MSVC 2008	openssl-1.1.0e-vs2008.7z [md5]	13.9 MB	x86 (32-bit)
x64 (64-bit)	debug
release	shared
static	
