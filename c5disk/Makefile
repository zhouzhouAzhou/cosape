test:
	gcc design_file_delete.c -o design_file_delete
	echo "********start to run design_disk_write_read.exe******"
	design_file_delete.exe
	echo "********end to run design_file_delete.exe******"

all:
	gcc veri_disk_write.c -o veri_disk_write
	echo "********please to run veri_disk_write.exe******"

	gcc veri_disk_read.c -o veri_disk_read
	echo "********please to run veri_disk_read.exe******"

	gcc veri_disk_write.c -o veri_disk_write
	echo "********please to run veri_disk_write.exe******"
	veri_disk_write.exe

	gcc veri_disk_read.c -o veri_disk_read
	echo "********please to run veri_disk_read.exe******"
	veri_disk_read.exe

	gcc design_disk_write_read.c -o design_disk_write_read
	echo "********start to run design_disk_write_read.exe******"
	design_disk_write_read.exe
	echo "********end to run design_disk_write_read.exe******"


clean:
	del -f *.exe
