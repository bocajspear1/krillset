all:
	mips64-linux-gnuabi64-gcc -o /tmp/out/test.mips64 /opt/test.c
	mips-linux-gnu-gcc -o /tmp/out/test.mips32 /opt/test.c
	mipsel-linux-gnu-gcc -o /tmp/out/test.mipsel /opt/test.c
	aarch64-linux-gnu-gcc -o /tmp/out/test.aarch64 /opt/test.c
	arm-linux-gnueabi-gcc -o /tmp/out/test.arm /opt/test.c
	gcc -no-pie -m64 -o /tmp/out/test.x86-64 /opt/test.c
	gcc -no-pie -m32 -o /tmp/out/test.x86 /opt/test.c

	mips64-linux-gnuabi64-gcc -static -o /tmp/out/test-static.mips64 /opt/test.c
	mips-linux-gnu-gcc -static -o /tmp/out/test-static.mips32 /opt/test.c
	mipsel-linux-gnu-gcc -static -o /tmp/out/test-static.mipsel /opt/test.c
	aarch64-linux-gnu-gcc -static -o /tmp/out/test-static.aarch64 /opt/test.c
	arm-linux-gnueabi-gcc -static -o /tmp/out/test-static.arm /opt/test.c
	gcc -m64 -static -o /tmp/out/test-static.x86-64 /opt/test.c
	gcc -m32 -static -o /tmp/out/test-static.x86 /opt/test.c

	i686-w64-mingw32-gcc-win32 /opt/test-win.c -o /tmp/out/test.x86.exe -lws2_32 
	i686-w64-mingw32-gcc-win32 /opt/test-dll.c -shared -o /tmp/out/test.x86.dll -lws2_32
	x86_64-w64-mingw32-gcc-win32 /opt/test-win.c -o /tmp/out/test.x86-64.exe -lws2_32
	x86_64-w64-mingw32-gcc-win32 /opt/test-dll.c -shared -o /tmp/out/test.x86-64.dll -lws2_32

	x86_64-w64-mingw32-gcc-win32 /opt/test-tiny-win.c -o /tmp/out/test-tiny.x86-64.exe -lws2_32
	i686-w64-mingw32-gcc-win32 /opt/test-tiny-win.c -o /tmp/out/test-tiny.x86.exe -lws2_32 

	GOOS=linux GOARCH=386 go build -o /tmp/out/test-go.x86 test.go
	GOOS=linux GOARCH=amd64 go build -o /tmp/out/test-go.x64 test.go
	GOOS=windows GOARCH=386 go build -o /tmp/out/test-go.x86.exe test-win.go
	GOOS=windows GOARCH=amd64 go build -o /tmp/out/test-go.x64.exe test-win.go
