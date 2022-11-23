test:
	gcc Prime_Process.c -o Prime_Process
	echo "********start to run Prime_Process.exe******"
	Prime_Process.exe
	echo "********end to run Prime_Process.exe******"


all:
	gcc main.c -lpthread -o main
	echo "********start to run main.exe******"
	main.exe
	echo "********end to run main.exe******"

	gcc Prime_Thread.c -lpthread -o Prime_Thread
	echo "********start to run Prime_Thread.exe******"
	Prime_Thread.exe
	echo "********end to run Prime_Thread.exe******"

	gcc Prime_Process1.c -o Prime_Process1
	echo "********start to run Prime_Process1.exe******"
	Prime_Process1.exe
	echo "********end to run Prime_Process1.exe******"

	gcc Prime_Process2.c -o Prime_Process2
	echo "********start to run Prime_Process2.exe******"
	Prime_Process2.exe
	echo "********end to run Prime_Process2.exe******"

clean:
	del -f *.exe
