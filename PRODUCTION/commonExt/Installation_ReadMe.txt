0.0.1
cedric.bilat@he-arc.ch

Les API Bilat constitués de :

	Pour Windows (visual,intelWin,mingw):
		.h
		.lib
		.a
		.dll

	Pour Linux (gcc,intelLinux)
		.h
		.so (pour gcc, intelinux :.so joue role .lib)

	se localise dans le workspace ici:

workspaceRoot
	ProjetXXX1
	ProjetXXX2
	ProjetXXX3
	ProjetXXX4
	PRODUCTION
		commonExt
			<ICI on a :
			Pour Windows (visual,intelWin,mingw)
				.h
				.lib
				.a
			Pour Linux (gcc, intelLinux)
				.h	>
		Deploy
			bin
				<ICI on a :
				Pour Windows (visual,intelWin)
					.dll
				Pour Linux (gcc, mingw, intelLinux)
					.so	>
		Manager
			private
				<makefile>
		
Notes:

		(N1) Dans commonExt
				.h
				.lib
		(N2) Dans Deploy\bin
				.dll
				.so
		
		(N3) MinGW fonctionne sous windows mais avec politique gcc linux

	