@echo off
setlocal

if not exist build mkdir build
pushd build

set code_path=../
set third_party_path=../third_party/

set output=main.exe
:: GENERAL COMPILER FLAGS
set compiler=               -nologo &:: Suppress Startup Banner
set compiler=%compiler%     -Oi     &:: Use assembly intrinsics where possible
set compiler=%compiler%     -MD     &:: Include CRT library in the executable (Dynamic link to match raylib.lib)
set compiler=%compiler%     -Gm-    &:: Disable minimal rebuild
set compiler=%compiler%     -GR-    &:: Disable runtime type info (C++)
set compiler=%compiler%     -EHa-   &:: Disable exception handling (C++)
set compiler=%compiler%		
:: DEBUG VARIABLES
:: set debug=		  			-FC &:: Produce the full path of the source code file
:: set debug=%debug% 			-Zi &:: Produce debug information (seperate PDB file, Use Z7 for embedding debug info into .obj file)
:: COMMON LINKER SWITCHES
set link=					-opt:ref				&:: Remove unused functions
set link=%link%		 		-incremental:no			&:: Perform full link each time
:: WIN32 PLATFORM LIBRARIES
set win32_libs=				user32.lib
set win32_libs=%win32_libs% Gdi32.lib
set win32_libs=%win32_libs% Winmm.lib
set win32_libs=%win32_libs% kernel32.lib
set win32_libs=%win32_libs% opengl32.lib
set win32_libs=%win32_libs% shell32.lib
set win32_libs=%win32_libs% Comdlg32.lib
:: THIRD PARTY LIBRARIES
set third_party_lib_path=%third_party_path%raylib/lib
set third_party_libs=raylib.lib

cl -Od %compiler% %defines% %debug% %code_path%main.c /Fe:%output%  %third_party_libs% %win32_libs% /link %link% /LIBPATH:%third_party_lib_path%

popd build
