#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *target_file)
{
	int fd;
	struct stat st;
	struct dirent de;
	char buf[512], *p;
	int file_count = 0;

	if ((fd = open(path, 0)) < 0)
	{
		fprintf(2, "ERROR: cannot open %s\n", path);
		return;
	}

	strcpy(buf, path);
	p = buf + strlen(buf);
	*p++ = '/';
	while (read(fd, &de, sizeof(de)) == sizeof(de))
	{
		if (de.inum == 0)
			continue;
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if (stat(buf, &st) < 0){
			fprintf(2, "ERROR: cannot stat %s\n", buf);
		}
		switch (st.type){
		case T_FILE:
			if (strcmp(target_file, de.name) == 0) {
				printf("%s\n", buf);
				file_count++;
			}
			break;
		case T_DIR:
			if ((strcmp(de.name, ".") != 0) && (strcmp(de.name, "..") != 0)) {
				find(buf, target_file);
			}
		}
	}
	close(fd);
  
	if (file_count == 0) {
		fprintf(2, "ERROR: do not find the given file\n");
	}
	return;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(2, "Usage: find [path] [expression]\n");
		exit(1);
	}
	find(argv[1], argv[2]);
	exit(0);
}